#include "making_summary.h"

#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/gregorian/gregorian_io.hpp>
#include <xl_operations.h>
#include <iostream>

#include "functions.h"

namespace bgreg = boost::gregorian;
namespace
{
struct CalcData
{
    CalcData():req(0.0),mk(0.0),br(0.0),umk(0.0),cnt(0),print(false)
    {
    }
    double req;
    double mk;
    double br;
    double umk;
    void reset()
    {
        req = mk = br = umk = 0.0;
        cnt = 0;
        print = false;
    }
    void inc(const rep::MakingSummary::Data &r)
    {
        req+=r.trud_req;
        mk+=r.trud_maked;
        br+=r.trud_broken;
        umk+=r.trud_unmaked;
        ++cnt;
    }

    void CheckPrint (void)
    {
        print = cnt > 1;
    }
    bool Print (void)
    {
        return print;
    }
    bool used (bool check = true)
    {
        return check*cnt;
    }
private:
    size_t cnt;
    bool print;
};
}
namespace rep
{

MakingSummary::MakingSummary (int set): rep::Report("Укрупненная ведомость изготовления деталей.",set),
    DB(0),path(""),use_listing(false),lists_by_file(0),object(""),element(""),type(""),template_path(""),
    cur_lists(0),templ("manufacture_forms.xlt"),date_from(""),date_to(""),use_podr(false),use_oper(false),no_duplicate(false),
    use_objects(false)
{
    params[REPORT_PATH];
    params[REPORT_LIST_COUNT] = "10";
    params[REPORT_USE_LISTING] = REP_TRUE;


    bgreg::date now = bgreg::day_clock::local_day();

    std::stringstream f_day;
    f_day.fill('0');
    f_day.width(2);
    f_day<<1<<".";
    f_day.width(2);
    f_day<<(int)now.month()<<"."<<(int)now.year();

    now += bgreg::months(1);
    std::stringstream l_day;
    l_day.fill('0');
    l_day.width(2);
    l_day<<1<<".";
    l_day.width(2);
    l_day<<(int)now.month()<<"."<<(int)now.year();

    params["Начало периода"]=f_day.str().c_str();
    params["Окончание периода"]=l_day.str().c_str();
    params["Показывать завершенные"] = REP_TRUE;
    params["Показывать не завершенные"] = REP_TRUE;
    params["Группировка по подразделению"] = REP_TRUE;
    params["Группировка по операциям"] = REP_TRUE;
    params["Исключить повторения"] = REP_FALSE;
    params["Ограничить выбранным объектом"] = REP_FALSE;
}
MakingSummary::~MakingSummary()
{}

MakingSummary::MakingSummary(const MakingSummary &r):rep::Report(r),
    DB(0),path(""),use_listing(false),lists_by_file(0),object(""),element(""),type(""),template_path(""),
    cur_lists(0),templ("manufacture_forms.xlt"),date_from(""),date_to(""),use_podr(false),use_oper(false),no_duplicate(false),
    use_objects(false)
{

}

void MakingSummary::Build(void)
{
    cur_lists = 0;
    ParseParams();
    LoadSettings();
    BuildReport();
}
boost::shared_ptr<rep::Report> MakingSummary::SelfCopy (void) const
{
    return boost::shared_ptr<rep::Report>(new MakingSummary(*this));
}

void MakingSummary::ParseParams(void)
{
    DB = ReportList::Instance().DbConnection();
    if (!DB)
        throw std::runtime_error("Отсутствует соединение с базой данных");

    //парсинг входных параметров отчета
    path = params[REPORT_PATH];
    use_listing = params[REPORT_USE_LISTING] == REP_TRUE;

    std::string s_tmp = params[REPORT_LIST_COUNT];
    std::stringstream s;
    s << s_tmp;
    s >> lists_by_file;

    if (!lists_by_file && !s_tmp.empty())
        throw std::runtime_error("Количество станиц на файл должно быть числом");

    //переменные указывающие на цель отчета
    object = params[REPORT_OBJECT_ID];
    type   = params[REPORT_OBJECT_TYPE];
    element = params[REPORT_ELEMENT_ID];

    show_maked = params["Показывать завершенные"] != REP_FALSE && params["Показывать завершенные"] != REP_NULL;
    show_un_maked = params["Показывать не завершенные"] != REP_FALSE && params["Показывать не завершенные"] != REP_NULL;
    use_podr = params["Группировка по подразделению"] != REP_FALSE && params["Группировка по подразделению"] != REP_NULL;
    use_oper = params["Группировка по операциям"] != REP_FALSE && params["Группировка по операциям"] != REP_NULL;
    no_duplicate = params["Исключить повторения"] != REP_FALSE && params["Исключить повторения"] != REP_NULL;
    use_objects = params["Ограничить выбранным объектом"] != REP_FALSE && params["Ограничить выбранным объектом"] != REP_NULL;
    //    if (object.empty())
//        throw std::runtime_error("Не указан объект для построения отчета");
//    if (type.empty())
//        throw std::runtime_error("Не указан тип объекта для отчета");
    date_to = params["Окончание периода"];
    date_from = params["Начало периода"];

    try
    {
        TDateTime(date_to.c_str());
        TDateTime(date_from.c_str());
    }
    catch (...)
    {
        throw ("Неверный формат даты");
    }
}
void MakingSummary::LoadSettings()
{
    //считать переменные из бд
    TADOQuery *rez = DB->SendSQL("select value from administration.settings where property='template'");
    if (rez)
    {
        template_path = rez->FieldByName("Value")->Value.operator AnsiString().Trim().c_str();
        delete rez;
        rez = 0;
    }
    else
    {
        throw std::runtime_error("Не задан путь к шаблонам");
    }
}

void MakingSummary::BuildReport()
{
    //получить список маршрутных листов по заданию
    if (use_objects)
    {
        DB->SendCommand("drop temporary table if exists tmp0");
        DB->SendCommand("create temporary table if not exists tmp0 "
                        "( "
                        "det_id bigint(20) unsigned not null, "
                        "key det_id(`det_id`) "
                        ")engine = MEMORY");


        std::stringstream prepare_sql;
        prepare_sql << "insert into tmp0 (det_id) select distinct "
            << "c.det_id "
            << "from manufacture.parts a "
            << "join manufacture.zakaz_list b on b.zak_id = a.zak_id "
            << "join manufacture.marsh_lists c on c.part_id = a.part_id ";
        if (type == "1")
        {//запуск
            prepare_sql << "where a.zap_id = '"<< object <<"'";
        }
        else if (type == "2")
        {//заказ
            prepare_sql << "where a.zap_id = '"<< object <<"' and a.zak_id = '"<< element <<"'";
        }
        else if (type == "4")
        {//партия
            prepare_sql << "where a.part_id = '"<< object <<"'";
        }
        else
            throw std::runtime_error("Не известный тип объекта");
        DB->SendCommand(prepare_sql.str().c_str());
    }


    std::string sql_date_from = AnsiString(TDateTime(date_from.c_str()).FormatString("yyyy-mm-dd")).c_str();
    std::string sql_date_to = AnsiString(TDateTime(date_to.c_str()).FormatString("yyyy-mm-dd")).c_str();
    std::string mod;

    DB->SendCommand("drop temporary table if exists tmp1");
    DB->SendCommand("create temporary table if not exists tmp1 "
                    "( "
                    "order_id bigint(20) unsigned not null, "
                    "operation_id bigint(20) unsigned not null, "
                    "request int(10) unsigned not null default 0, "
                    "maked   int(10) unsigned not null default 0, "
                    "broken  int(10) unsigned not null default 0, "
                    "unmaked int(10) unsigned not null default 0, "
                    "key opuud(`operation_id`) "
                    ")engine = MEMORY");
    std::stringstream step1;
    step1<<
            "insert into tmp1 (order_id,operation_id,request,maked,broken,unmaked) "
            "select "
            "`a`.`order_id`, "
            "`a`.`operation_id`, "
            "`a`.`kol_request` request, "
            "ifnull(sum(`b`.`maked`),0) maked, "
            "ifnull(sum(`b`.`broken`),0) broken, "
            "(`a`.`kol_request` - ifnull(sum(`b`.`maked`),0)) unmaked "
            "from `manufacture`.`orders` `a` "
            "left join `manufacture`.`orders_history` `b` on `a`.`order_id` = `b`.`order_id` and `b`.`date` <= '"<<sql_date_to<<"' "
            "where "
            "'"<<sql_date_from<<"' <= `a`.`creation_date` and `a`.`creation_date` <= '"<<sql_date_to<<"' or '"<<sql_date_from<<"' > `a`.`creation_date` and `a`.`closed_date` is null "
            "group by `a`.`order_id` having true";
    if (show_maked && !show_un_maked)
    {
        step1<< " and maked+broken = request ";
        mod = "ЗАВЕРШЕННЫЕ";
    }
    if (!show_maked && show_un_maked)
    {
        step1<< " and maked+broken < request ";
        mod = "НЕ ЗАВЕРШЕННЫЕ";
    }

    DB->SendCommand(step1.str().c_str());
    DB->SendCommand("drop temporary table if exists tmp2");
    DB->SendCommand("create temporary table if not exists tmp2 "
        "( "
        "det_id bigint(20) unsigned not null, "
        "cex     char(2) NOT NULL, "
        "utch    char(2) NOT NULL, "
        "oprid   char(2) NOT NULL, "
        "request     int(10) unsigned not null default 0, "
        "maked       int(10) unsigned not null default 0, "
        "broken      int(10) unsigned not null default 0, "
        "unmaked     int(10) unsigned not null default 0, "
        "trud_request    double unsigned not null default 0, "
        "trud_maked      double unsigned not null default 0, "
        "trud_broken     double unsigned not null default 0, "
        "trud_unmaked    double unsigned not null default 0, "
        "vz      smallint(6) DEFAULT NULL NOT NULL default 0, "
        "key det(`det_id`), "
        "key cex(`cex`), "
        "key utch(`utch`) "
        ")engine = MEMORY");
    std::stringstream tmp2;
    tmp2 << "insert into tmp2 (request,maked,broken,unmaked,cex,utch,oprid,trud_request,trud_maked,trud_broken,trud_unmaked,det_id,vz) "
            "select "
            "`a`.`request`, "
            "min(`a`.`maked`)  maked, "
            "max(`a`.`broken`) broken, "
            "max(`a`.`unmaked`)unmaked, "
            "`b`.`cex`, "
            "`b`.`utch`, "
            "`b`.`oprid`, "
            "round(sum(if (`b`.`cex` = '03' and `b`.`utch` = '04', "
                "IFNULL(`c`.`tsht`*ceil(`a`.`request`/`d`.`kdz`)/`a`.`request`*`a`.`request`+if(`a`.`request`>0,`c`.`tpz`,0),0), "
                "IFNULL(`c`.`tsht`*`c`.`ksht`*`c`.`krop`/`c`.`kolod`*`a`.`request`+if(`a`.`request`>0,`c`.`tpz`,0),0) "
                ")),3) as trud_request, "
            "round(sum(if (`b`.`cex` = '03' and `b`.`utch` = '04', "
                "IFNULL(`c`.`tsht`*ceil(`a`.`request`/`d`.`kdz`)/`a`.`request`*`a`.`maked`+if(`a`.`maked`>0,`c`.`tpz`,0),0), "
                "IFNULL(`c`.`tsht`*`c`.`ksht`*`c`.`krop`/`c`.`kolod`*`a`.`maked`+if(`a`.`maked`>0,`c`.`tpz`,0),0) "
                ")),3) as trud_maked, "
            "round(sum(if (`b`.`cex` = '03' and `b`.`utch` = '04', "
                "IFNULL(`c`.`tsht`*ceil(`a`.`request`/`d`.`kdz`)/`a`.`request`*`a`.`broken`+if(`a`.`broken`>0,`c`.`tpz`,0),0), "
                "IFNULL(`c`.`tsht`*`c`.`ksht`*`c`.`krop`/`c`.`kolod`*`a`.`broken`+if(`a`.`broken`>0,`c`.`tpz`,0),0) "
                ")),3) as trud_broken, "
            "round(sum(if (`b`.`cex` = '03' and `b`.`utch` = '04', "
                "IFNULL(`c`.`tsht`*ceil(`a`.`request`/`d`.`kdz`)/`a`.`request`*`a`.`unmaked`+if(`a`.`unmaked`>0,`c`.`tpz`,0),0), "
                "IFNULL(`c`.`tsht`*`c`.`ksht`*`c`.`krop`/`c`.`kolod`*`a`.`unmaked`+if(`a`.`unmaked`>0,`c`.`tpz`,0),0) "
                ")),3) as trud_unmaked, "
            "`d`.`det_id`, "
            "`d`.`vz` "
            "from `tmp1` `a` "
            "join `manufacture`.`operation_list` `b` on `b`.`OpUUID` = `a`.`operation_id` "
            "join `manufacture`.`operation_norms` `c` on `c`.`OpUUID` = `a`.`operation_id` "
            "join `manufacture`.`det_info` `d` on `d`.`det_id` = `b`.`det_id` ";
    if (use_objects)
    {
        tmp2 << "join `tmp0` `e` on `e`.`det_id` = `b`.`det_id` ";
    }
    tmp2 <<"group by `d`.`det_id`,`b`.`cex`,`b`.`utch`,`b`.`oprid`";
    DB->SendCommand(tmp2.str().c_str());
    if (use_objects)
    {
        DB->SendCommand("drop temporary table if exists tmp0");
    }

    DB->SendCommand("drop temporary table if exists tmp3");
    DB->SendCommand("create temporary table if not exists tmp3 "
        "( "
        "det_id bigint(20) unsigned not null, "
        "key det(`det_id`) "
        ")engine = MEMORY");
    DB->SendCommand("insert into tmp3 (det_id) "
        "select distinct `det_id` from `tmp2`");

    DB->SendCommand("drop temporary table if exists tmp4");
    DB->SendCommand("create temporary table if not exists tmp4 "
        "( "
        "det_id bigint(20) unsigned NOT NULL, "
        "part_no int(10) unsigned NOT NULL, "
        "zakaz varchar(6) NOT NULL, "
        "obd varchar(100) NOT NULL, "
        "name varchar(255) NOT NULL, "
        "key det(`det_id`), "
        "key obd(`obd`) "
        ")engine = MEMORY");
    DB->SendCommand("insert into tmp4 (det_id,part_no,zakaz,obd,name) "
        "select "
        "`a`.`det_id`, "
        "`c`.`part_no`, "
        "`d`.`zakaz`, "
        "`e`.`obd`, "
        "`e`.`name` "
        "from `manufacture`.`marsh_lists` `a` "
        "join `tmp3` `b` on `a`.`det_id` = `b`.`det_id` "
        "join `manufacture`.`parts` `c` on `c`.`part_id` = `a`.`part_id` "
        "join `manufacture`.`zakaz_list` `d` on `d`.`zak_id` = `c`.`zak_id` "
        "join `manufacture`.`det_names` `e` on `a`.`det_id` = `e`.`det_id`");

    std::stringstream sql;
    sql <<"select "
          "round(sum(`a`.`trud_request`),3) as trud_request, "
          "round(sum(`a`.`trud_maked`),3) as trud_maked, "
          "round(sum(`a`.`trud_broken`),3) as trud_broken, "
          "round(sum(`a`.`trud_unmaked`),3) as trud_unmaked, "

          "convert(`a`.`cex`, char) cex, "
          "convert(`a`.`utch`, char) utch, "
          "convert(`b`.`part_no`, char) part_no, "
          "convert(`b`.`zakaz`, char) zakaz, "
          "convert(concat(`c`.`OprID`,' ',`c`.`name`), char) oper "

          "from `tmp2` `a` "
          "join `tmp4` `b` on `a`.`det_id` = `b`.`det_id` "
          "join `equipment`.`opr_names` `c` on `a`.`oprid` = `c`.`OprID` "
          "group by `b`.`zakaz`,`b`.`part_no`" ;

    if (use_podr)
        sql <<",`a`.`cex`,`a`.`utch` ";
    if (use_oper)
        sql <<",`a`.`oprid` ";

    sql << "order by `b`.`zakaz`,`b`.`part_no`";

    if (use_podr)
        sql <<",`a`.`cex`,`a`.`utch` ";
    if (use_oper)
        sql <<",`a`.`oprid` ";


    TADOQuery *rez = DB->SendSQL(sql.str().c_str());
    DB->SendCommand("drop temporary table if exists tmp1");
    DB->SendCommand("drop temporary table if exists tmp2");
    DB->SendCommand("drop temporary table if exists tmp3");
    DB->SendCommand("drop temporary table if exists tmp4");

    if (rez)
    {
        if (rez->RecordCount)
        {
            //включаем ексель
            cExcel xl;
            xl.Connect();
            xl.Visible(false);
            xl.DisplayAlerts(false);

            std::string teml_file = template_path + templ;

            OpenTemplate(xl, teml_file);

            bool new_page = true;
            size_t cur_row = 0;
            size_t start_row = 4, end_row = 60, row_size = 1, template_row = 5;
            size_t template_page = 11;


            size_t list_count(0);

            CexData cex_data;
            std::string cur_cex("");
            std::string cur_utch("");

            std::string cur_zak("");
            std::string cur_part("");

			CalcData cex_calc;
            CalcData utch_calc;
            CalcData zak_calc;
            CalcData part_calc;


			for (rez->First(); !rez->Eof; rez->Next())
            {
                Data tmp;
                tmp.cex     =   (rez->FieldByName("cex")->Value.operator AnsiString()).c_str();
                tmp.utch    =   (rez->FieldByName("utch")->Value.operator AnsiString()).c_str();
                tmp.zakaz   =   (rez->FieldByName("zakaz")->Value.operator AnsiString()).c_str();
                tmp.part    =   (rez->FieldByName("part_no")->Value.operator AnsiString()).c_str();
                tmp.oper    =   (rez->FieldByName("oper")->Value.operator AnsiString()).c_str();

                tmp.trud_req        =   rez->FieldByName("trud_request")->Value.operator double();
                tmp.trud_maked      =   rez->FieldByName("trud_maked")->Value.operator double();
                tmp.trud_broken     =   rez->FieldByName("trud_broken")->Value.operator double();
                tmp.trud_unmaked    =   rez->FieldByName("trud_unmaked")->Value.operator double();


                if (!cur_zak.empty() && cur_zak!=tmp.zakaz)
                {
                    zak_calc.CheckPrint();//итог по заказу
                    part_calc.CheckPrint();//итог по партии
                    if (use_podr)
                    {
                        cex_calc.CheckPrint(); //по цеху
                        if(use_oper)
                        {
                            utch_calc.CheckPrint();// по участку
                        }
                    }
                }
                else if (!cur_part.empty() && cur_part!=tmp.part)
                {
                    part_calc.CheckPrint(); //итог по партии
                    if (use_podr)
                    {
                        cex_calc.CheckPrint(); //по цеху
                        if(use_oper)
                        {
                            utch_calc.CheckPrint(); // по участку
                        }
                    }
                }
                else if (use_podr)
                {
                    if( !cur_cex.empty() && cur_cex!=tmp.cex)
                    {
                        cex_calc.CheckPrint();//по цеху
                        if(use_oper)
                        {
                            utch_calc.CheckPrint(); // по участку
                        }
                    }
                    else if (use_oper && !cur_utch.empty() && cur_utch!=tmp.utch)
                    {
                        utch_calc.CheckPrint(); // по участку
                    }
                }

                if (cex_calc.Print())
                    ++cur_row;
                if (utch_calc.Print())
                    ++cur_row;
                if (zak_calc.Print())
                    ++cur_row;
                if (part_calc.Print())
                    ++cur_row;

                bool need_switch = (cur_row + row_size > end_row);
                new_page = new_page + need_switch;
                if (new_page)
                {
                    new_page = false;
                    cur_row = start_row;
                    ++list_count;
                }

                if (cex_calc.Print())
                    cex_calc.reset();
                if (utch_calc.Print())
                    utch_calc.reset();
                if (zak_calc.Print())
                    zak_calc.reset();
                if (part_calc.Print())
                    part_calc.reset();

                cur_cex  = tmp.cex;
                cur_utch = tmp.utch;
                cur_zak  = tmp.zakaz;
                cur_part = tmp.part;

                if (use_podr)
                {
                    cex_calc.inc(tmp);
                    if (use_oper)
                        utch_calc.inc(tmp);
                }

                zak_calc.inc(tmp);
                part_calc.inc(tmp);

                cur_row+=row_size;
                cex_data.insert(CexDataItem(tmp.zakaz, tmp));
            }
            //расчитать кол - во страниц для цеха
            new_page = true;

            //считать данные подсчитать колво страниц
            //разбить на цеха
            //вывести данные
            size_t file_no = 0;

            cur_cex = "";
            cur_utch = "";
            cur_zak = "";
            cur_part = "";

            cex_calc.reset();
            utch_calc.reset();
            zak_calc.reset();
            part_calc.reset();

            size_t list_no(0);
            for (CexData::const_iterator it = cex_data.begin(); it!=cex_data.end(); ++it)
            {
                const Data &lnk = it->second;

                if (!cur_zak.empty() && cur_zak!=lnk.zakaz)
                {
                    zak_calc.CheckPrint();//итог по заказу
                    part_calc.CheckPrint();//итог по партии
                    if (use_podr)
                    {
                        cex_calc.CheckPrint(); //по цеху
                        if(use_oper)
                        {
                            utch_calc.CheckPrint();// по участку
                        }
                    }
                }
                else if (!cur_part.empty() && cur_part!=lnk.part)
                {
                    part_calc.CheckPrint(); //итог по партии
                    if (use_podr)
                    {
                        cex_calc.CheckPrint(); //по цеху
                        if(use_oper)
                        {
                            utch_calc.CheckPrint(); // по участку
                        }
                    }
                }
                else if (use_podr)
                {
                    if( !cur_cex.empty() && cur_cex!=lnk.cex)
                    {
                        cex_calc.CheckPrint();//по цеху
                        if(use_oper)
                        {
                            utch_calc.CheckPrint(); // по участку
                        }
                    }
                    else if (use_oper && !cur_utch.empty() && cur_utch!=lnk.utch)
                    {
                        utch_calc.CheckPrint(); // по участку
                    }
                }

                size_t need_rows(0);
                if (cex_calc.Print())
                    ++need_rows;
                if (utch_calc.Print())
                    ++need_rows;
                if (zak_calc.Print())
                    ++need_rows;
                if (part_calc.Print())
                    ++need_rows;

                bool need_switch = (cur_row + row_size + need_rows> end_row);
                new_page = new_page + need_switch;
                if (new_page)
                {
                    new_page = false;
                    cur_cex = lnk.cex;

                    if (cur_lists)
                    {
                        if (use_listing && !path.empty())
                        {//проверяем количество страниц, если выставлена опция
                            TrimFile(xl,path,"",cur_lists,lists_by_file,teml_file,file_no);
                        }
                    }
                    //создать страницу
                    xl.Sheet_Copy(xl.GetSheet(cur_lists+template_page), xl.GetSheet(cur_lists+1), Variant().NoParam());
                    cur_lists++ ;
                    list_no++;
                    xl.SetActiveSheet(xl.GetSheet(cur_lists));
                    std::stringstream buf;
                    buf<<list_no;
                    xl.Set_Sheet_Name(xl.GetSheet(cur_lists),("Лист-"+buf.str()).c_str());


                    xl.toCells(1, 13,   list_no             );
                    xl.toCells(1, 15,   list_count          );
                    xl.toCells(1, 3,    Now().FormatString("dd.mm.yyyy")   );
                    xl.toCells(2, 5,    date_from.c_str()   );
                    xl.toCells(2, 8,    date_to.c_str()     );
                    xl.toCells(2, 11,   mod.c_str()         );

                    // почистить лист
                    // копирование
                    xl.Range_Copy(xl.GetRows(xl.GetSheet(cur_lists+template_page), 15, 20));
                    // вставка
                    xl.Sheet_activate();
                    xl.Range_Paste(xl.GetRows(4, 10));

                    cur_row = start_row;
                }

                if (utch_calc.Print())
                {
                    // копирование
                    xl.Range_Copy(xl.GetRows(xl.GetSheet(cur_lists+template_page), template_row, template_row));
                    // вставка
                    xl.Sheet_activate();
                    xl.Range_Paste(xl.GetRows(cur_row, cur_row));

                    xl.toCells(cur_row,     6,   "ИТОГО"      );
                    xl.toCells(cur_row,     10,  utch_calc.req);
                    xl.toCells(cur_row,     11,  utch_calc.mk );
                    xl.toCells(cur_row,     12,  utch_calc.br );
                    xl.toCells(cur_row,     14,  utch_calc.umk);
                    ++cur_row;
                    utch_calc.reset();
                }
                if (cex_calc.Print())
                {
                    // копирование
                    xl.Range_Copy(xl.GetRows(xl.GetSheet(cur_lists+template_page), template_row, template_row));
                    // вставка
                    xl.Sheet_activate();
                    xl.Range_Paste(xl.GetRows(cur_row, cur_row));

                    xl.toCells(cur_row,     4,   "ИТОГО"     );
                    xl.toCells(cur_row,     10,  cex_calc.req);
                    xl.toCells(cur_row,     11,  cex_calc.mk );
                    xl.toCells(cur_row,     12,  cex_calc.br );
                    xl.toCells(cur_row,     14,  cex_calc.umk);
                    ++cur_row;
                    cex_calc.reset();
                    utch_calc.reset();
                }
                if (part_calc.Print())
                {
                    // копирование
                    xl.Range_Copy(xl.GetRows(xl.GetSheet(cur_lists+template_page), template_row, template_row));
                    // вставка
                    xl.Sheet_activate();
                    xl.Range_Paste(xl.GetRows(cur_row, cur_row));

                    xl.toCells(cur_row,     3,   "ИТОГО"      );
                    xl.toCells(cur_row,     10,  part_calc.req);
                    xl.toCells(cur_row,     11,  part_calc.mk );
                    xl.toCells(cur_row,     12,  part_calc.br );
                    xl.toCells(cur_row,     14,  part_calc.umk);
                    ++cur_row;
                    part_calc.reset();
                    cex_calc.reset();
                    utch_calc.reset();
                }
                if (zak_calc.Print())
                {
                    // копирование
                    xl.Range_Copy(xl.GetRows(xl.GetSheet(cur_lists+template_page), template_row, template_row));
                    // вставка
                    xl.Sheet_activate();
                    xl.Range_Paste(xl.GetRows(cur_row, cur_row));

                    xl.toCells(cur_row,     1,   "ИТОГО"     );
                    xl.toCells(cur_row,     10,  zak_calc.req);
                    xl.toCells(cur_row,     11,  zak_calc.mk );
                    xl.toCells(cur_row,     12,  zak_calc.br );
                    xl.toCells(cur_row,     14,  zak_calc.umk);
                    ++cur_row;
                    zak_calc.reset();
                    part_calc.reset();
                    cex_calc.reset();
                    utch_calc.reset();
                }

                cur_cex  = lnk.cex;
                cur_utch = lnk.utch;
                cur_zak  = lnk.zakaz;
                cur_part = lnk.part;

                //вставить строку в отчет
                // копирование
                xl.Range_Copy(xl.GetRows(xl.GetSheet(cur_lists+template_page), template_row, template_row + row_size - 1));
                // вставка
                xl.Sheet_activate();
                xl.Range_Paste(xl.GetRows(cur_row, cur_row + row_size-1));


                if (!zak_calc.used(no_duplicate))
                    xl.toCells(cur_row,     1,  lnk.zakaz.c_str());

                if (!part_calc.used(no_duplicate))
                    xl.toCells(cur_row,     3,  lnk.part.c_str() );

                if (use_podr)
                {
                    if (!cex_calc.used(no_duplicate))
                        xl.toCells(cur_row,     4,  lnk.cex.c_str() );
                    if (!utch_calc.used(no_duplicate))
                        xl.toCells(cur_row,     6, lnk.utch.c_str() );
                }
                if (use_oper)
                {
                    xl.toCells(cur_row,     7,  lnk.oper.c_str() );
                }

                xl.toCells(cur_row,   10,  lnk.trud_req      );
                xl.toCells(cur_row,   11,  lnk.trud_maked    );
                xl.toCells(cur_row,   12,  lnk.trud_broken   );
                xl.toCells(cur_row,   14,  lnk.trud_unmaked   );

                if (use_podr)
                {
                    cex_calc.inc(lnk);
                    if (use_oper)
                        utch_calc.inc(lnk);
                }

                zak_calc.inc(lnk);
                part_calc.inc(lnk);

                cur_row+=row_size;
            }
            zak_calc.CheckPrint();//итог по заказу
            part_calc.CheckPrint();//итог по партии
            if (use_podr)
            {
                cex_calc.CheckPrint(); //по цеху
                if(use_oper)
                {
                    utch_calc.CheckPrint();// по участку
                }
            }
            if (utch_calc.Print())
            {
                // копирование
                xl.Range_Copy(xl.GetRows(xl.GetSheet(cur_lists+template_page), template_row, template_row));
                // вставка
                xl.Sheet_activate();
                xl.Range_Paste(xl.GetRows(cur_row, cur_row));

                xl.toCells(cur_row,     6,   "ИТОГО"      );
                xl.toCells(cur_row,     10,  utch_calc.req);
                xl.toCells(cur_row,     11,  utch_calc.mk );
                xl.toCells(cur_row,     12,  utch_calc.br );
                xl.toCells(cur_row,     14,  utch_calc.umk);
                ++cur_row;
                utch_calc.reset();
            }
            if (cex_calc.Print())
            {
                // копирование
                xl.Range_Copy(xl.GetRows(xl.GetSheet(cur_lists+template_page), template_row, template_row));
                // вставка
                xl.Sheet_activate();
                xl.Range_Paste(xl.GetRows(cur_row, cur_row));

                xl.toCells(cur_row,     4,   "ИТОГО"     );
                xl.toCells(cur_row,     10,  cex_calc.req);
                xl.toCells(cur_row,     11,  cex_calc.mk );
                xl.toCells(cur_row,     12,  cex_calc.br );
                xl.toCells(cur_row,     14,  cex_calc.umk);
                ++cur_row;
                cex_calc.reset();
            }
            if (part_calc.Print())
            {
                // копирование
                xl.Range_Copy(xl.GetRows(xl.GetSheet(cur_lists+template_page), template_row, template_row));
                // вставка
                xl.Sheet_activate();
                xl.Range_Paste(xl.GetRows(cur_row, cur_row));

                xl.toCells(cur_row,     3,   "ИТОГО"      );
                xl.toCells(cur_row,     10,  part_calc.req);
                xl.toCells(cur_row,     11,  part_calc.mk );
                xl.toCells(cur_row,     12,  part_calc.br );
                xl.toCells(cur_row,     14,  part_calc.umk);
                ++cur_row;
                part_calc.reset();
            }
            if (zak_calc.Print())
            {
                // копирование
                xl.Range_Copy(xl.GetRows(xl.GetSheet(cur_lists+template_page), template_row, template_row));
                // вставка
                xl.Sheet_activate();
                xl.Range_Paste(xl.GetRows(cur_row, cur_row));

                xl.toCells(cur_row,     1,   "ИТОГО"     );
                xl.toCells(cur_row,     10,  zak_calc.req);
                xl.toCells(cur_row,     11,  zak_calc.mk );
                xl.toCells(cur_row,     12,  zak_calc.br );
                xl.toCells(cur_row,     14,  zak_calc.umk);
                ++cur_row;
                zak_calc.reset();
            }


            if (!path.empty())//закрываем Excel в зависимости от опции сохранения в файл
            {
                SaveFile(xl,path,"",cur_lists,file_no);
                xl.Book_Close(xl.GetBook(1));
                xl.Disconnect();
            }
            else
            {
                RemoveTemplates(xl,cur_lists);
                xl.Visible(true);
            }
        }
        delete rez;
    }
    else
    {
        throw std::runtime_error("Ошибка соединения с базой данных");
    }
}
}
