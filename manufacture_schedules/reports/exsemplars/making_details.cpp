#include "making_details.h"


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
    CalcData():req(0.0),mk(0.0),br(0.0),umk(0.0)
    {}
    double req;
    double mk;
    double br;
    double umk;
    void reset()
    {
        req = mk = br = umk = 0.0;
    }
    void inc(const rep::MakingDetails::Data &r)
    {
        req+=r.trud_req;
        mk+=r.trud_maked;
        br+=r.trud_broken;
        umk+=r.trud_unmaked;
    }
};

}

namespace rep
{

MakingDetails::MakingDetails (int set): rep::Report("Ведомость изготовления деталей",set),
    DB(0),path(""),use_listing(false),lists_by_file(0),object(""),element(""),type(""),template_path(""),
    cur_lists(0),templ("manufacture_forms.xlt"),date_from(""),date_to(""),
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
    params["Ограничить выбранным объектом"] = REP_TRUE;
}
MakingDetails::~MakingDetails()
{}

MakingDetails::MakingDetails(const MakingDetails &r):rep::Report(r),
    DB(0),path(""),use_listing(false),lists_by_file(0),object(""),element(""),type(""),template_path(""),
    cur_lists(0),templ("manufacture_forms.xlt"),date_from(""),date_to(""),
    use_objects(false)
{

}

void MakingDetails::Build(void)
{
    cur_lists = 0;
    ParseParams();
    LoadSettings();
    BuildReport();
}
boost::shared_ptr<rep::Report> MakingDetails::SelfCopy (void) const
{
    return boost::shared_ptr<rep::Report>(new MakingDetails(*this));
}

void MakingDetails::ParseParams(void)
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
void MakingDetails::LoadSettings()
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


void MakingDetails::BuildReport()
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
        "opr     char(4) NOT NULL default '', "
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
    TADOQuery *rez = DB->SendSQL("select "
        "convert(`a`.`request`, char) request, "
        "convert(min(`a`.`maked`), char)  maked, "
        "convert(max(`a`.`broken`), char) broken, "
        "convert(max(`a`.`unmaked`), char) unmaked, "
        "convert(`a`.`cex`, char) cex, "
        "convert(`a`.`utch`, char) utch, "
        "round(sum(`a`.`trud_request`),3) as trud_request, "
        "round(sum(`a`.`trud_maked`),3) as trud_maked, "
        "round(sum(`a`.`trud_broken`),3) as trud_broken, "
        "round(sum(`a`.`trud_unmaked`),3) as trud_unmaked, "
        "convert(`a`.`vz`, char) vz, "
        "convert(`b`.`det_id`, char) det_id, "
        "convert(`b`.`obd`, char) obd, "
        "convert(`b`.`name`, char) name, "
        "convert(`b`.`part_no`, char) part_no, "
        "convert(`b`.`zakaz`, char) zakaz "
        "from `tmp2` `a` "
        "join `tmp4` `b` on `a`.`det_id` = `b`.`det_id` "
        "group by `a`.`cex`,`a`.`utch`,`a`.`det_id` "
        "order by `a`.`cex`,`b`.`zakaz`,`b`.`part_no`,`a`.`utch`,`b`.`obd`");

    TADOQuery * rez1 = DB->SendSQL(
            "select convert(`a`.`det_id`, char) det_id,convert(cex, char) cex,convert(utch, char) utch, "
            "GROUP_CONCAT(' ',`a`.`oprid`,' - ',round(`a`.`trud_unmaked`,3)) timing "
            "from tmp2 a where a.trud_unmaked > 0 "
            "group by det_id,cex,utch order by det_id,opr ");


    DB->SendCommand("drop temporary table if exists tmp1");
    DB->SendCommand("drop temporary table if exists tmp2");
    DB->SendCommand("drop temporary table if exists tmp3");
    DB->SendCommand("drop temporary table if exists tmp4");

    typedef std::map<const std::string, std::string> CacheType;
    CacheType cache;
    if (rez1)
    {
        for (rez1->First(); !rez1->Eof; rez1->Next())
        {
            std::string id = (rez1->FieldByName("det_id")->Value.operator AnsiString()).c_str();
            std::string cex = (rez1->FieldByName("cex")->Value.operator AnsiString()).c_str();
            std::string utch = (rez1->FieldByName("utch")->Value.operator AnsiString()).c_str();
            std::string prim = (rez1->FieldByName("timing")->Value.operator AnsiString()).c_str();
            cache[id+cex+utch] = prim;
        }
        delete rez1;
    }

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
            size_t start_row = 5, end_row = 60, row_size = 2, template_row = 3,
                    templ_header = 6, templ_foter = 7;
            size_t template_page = 10;

            size_t list_count(0);

            CexData cex_data;
            std::string cur_cex("");
            std::string cur_zak("");
            std::string cur_utch("");

            for (rez->First(); !rez->Eof; rez->Next())
            {
                Data tmp;
                tmp.det_id  =   (rez->FieldByName("det_id")->Value.operator AnsiString()).c_str();
                tmp.cex     =   (rez->FieldByName("cex")->Value.operator AnsiString()).c_str();
                tmp.utch    =   (rez->FieldByName("utch")->Value.operator AnsiString()).c_str();
                tmp.zakaz   =   (rez->FieldByName("zakaz")->Value.operator AnsiString()).c_str();
                tmp.part    =   (rez->FieldByName("part_no")->Value.operator AnsiString()).c_str();

                tmp.vz      =   (rez->FieldByName("vz")->Value.operator AnsiString()).c_str();
                tmp.obd     =   VinToGost(rez->FieldByName("obd")->Value.operator AnsiString()).c_str();
                tmp.name    =   (rez->FieldByName("name")->Value.operator AnsiString()).c_str();

                tmp.kol_req     =   (rez->FieldByName("request")->Value.operator AnsiString()).c_str();
                tmp.kol_maked   =   (rez->FieldByName("maked")->Value.operator AnsiString()).c_str();
                tmp.kol_broken  =   (rez->FieldByName("broken")->Value.operator AnsiString()).c_str();
                tmp.kol_unmaked =   (rez->FieldByName("unmaked")->Value.operator AnsiString()).c_str();

                tmp.trud_req        =   rez->FieldByName("trud_request")->Value.operator double();
                tmp.trud_maked      =   rez->FieldByName("trud_maked")->Value.operator double();
                tmp.trud_broken     =   rez->FieldByName("trud_broken")->Value.operator double();
                tmp.trud_unmaked    =   rez->FieldByName("trud_unmaked")->Value.operator double();

                bool need_switch = (cur_row + row_size > end_row);
                bool t2 = (!cur_cex.empty() && cur_cex!=tmp.cex);
                new_page = new_page + need_switch + t2;
                if (t2)
                {
                    ++cur_row;
                    ++cur_row;
                    ++cur_row;

                    cur_zak = tmp.zakaz + tmp.part;
                    cur_utch = tmp.utch;
                }
                if (new_page)
                {
                    new_page = false;
                    cur_cex = tmp.cex;
                    cur_row = start_row;
                    ++list_count;
                    if (t2||!(list_count-1))
                    {
                        ++cur_row;
                    }
                }
                if (!cur_zak.empty() && cur_zak!=tmp.zakaz + tmp.part)
                {
                    cur_row+=3;
                }
                else if (!cur_utch.empty() && cur_utch!=tmp.utch)
                {
                    cur_row+=2;
                }
                cur_zak = tmp.zakaz + tmp.part;
                cur_utch = tmp.utch;
                cur_row+=row_size;
                cex_data.insert(CexDataItem(tmp.cex, tmp));
            }
            //расчитать кол - во страниц для цеха
            new_page = true;

            //считать данные подсчитать колво страниц
            //разбить на цеха
            //вывести данные
            size_t file_no = 0;

            cur_cex = "";
            cur_zak = "";
            cur_utch = "";

            CalcData cex_calc;
            CalcData zak_calc;
            CalcData utch_calc;
            size_t list_no(0);
            for (CexData::const_iterator it = cex_data.begin(); it!=cex_data.end(); ++it)
            {
                const Data &lnk = it->second;

                bool need_switch = (cur_row + row_size > end_row);

                bool t2 = (!cur_cex.empty() && cur_cex!=lnk.cex);

                new_page = new_page + need_switch + t2;//проанализировать количестко оставшихся строк

                if (t2)
                {
                    //Итого по цеху
                    // копирование
                    xl.Range_Copy(xl.GetRows(xl.GetSheet(cur_lists+template_page), templ_foter, templ_foter));
                    // вставка
                    xl.Sheet_activate();
					xl.Range_Paste(xl.GetRows(cur_row, cur_row));

                    xl.toCells(cur_row,     3,  "УЧАСТКУ"    );
					xl.toCells(cur_row,     7,  utch_calc.req);
					xl.toCells(cur_row,     8,  utch_calc.mk );
                    xl.toCells(cur_row,     9,  utch_calc.br );
                    xl.toCells(cur_row,     10, utch_calc.umk);
                    ++cur_row;

                    // копирование
                    xl.Range_Copy(xl.GetRows(xl.GetSheet(cur_lists+template_page), templ_foter, templ_foter));
                    // вставка
                    xl.Sheet_activate();
					xl.Range_Paste(xl.GetRows(cur_row, cur_row));

                    xl.toCells(cur_row,     3,  "ЗАКАЗУ"    );
                    xl.toCells(cur_row,     7,  zak_calc.req);
                    xl.toCells(cur_row,     8,  zak_calc.mk );
                    xl.toCells(cur_row,     9,  zak_calc.br );
                    xl.toCells(cur_row,     10, zak_calc.umk);
                    ++cur_row;

                    // копирование
                    xl.Range_Copy(xl.GetRows(xl.GetSheet(cur_lists+template_page), templ_foter, templ_foter));
                    // вставка
                    xl.Sheet_activate();
					xl.Range_Paste(xl.GetRows(cur_row, cur_row));

                    xl.toCells(cur_row,     3,  "ЦЕХУ"    );
                    xl.toCells(cur_row,     7,  cex_calc.req);
                    xl.toCells(cur_row,     8,  cex_calc.mk );
                    xl.toCells(cur_row,     9,  cex_calc.br );
                    xl.toCells(cur_row,     10, cex_calc.umk);
                    ++cur_row;

                    cex_calc.reset();
                    zak_calc.reset();
                    utch_calc.reset();
                    cur_zak = lnk.zakaz + lnk.part;
                    cur_utch = lnk.utch;
                }

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


                    xl.toCells(1, 11,   lnk.cex.c_str()     );
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
                    xl.Range_Paste(xl.GetRows(5, 10));

                    cur_row = start_row;


                    if (t2||!(cur_lists-1))
                    {
                        //вставить строку в отчет
                        // копирование
                        xl.Range_Copy(xl.GetRows(xl.GetSheet(cur_lists+template_page), templ_header, templ_header));
                        // вставка
                        xl.Sheet_activate();
                        xl.Range_Paste(xl.GetRows(cur_row, cur_row));

                        xl.toCells(cur_row, 7,   lnk.zakaz.c_str()   );
                        xl.toCells(cur_row, 9,   lnk.part.c_str()   );
                        xl.toCells(cur_row, 11,   lnk.utch.c_str()   );

                        ++cur_row;
                    }
                }

                if (!cur_zak.empty() && cur_zak!=lnk.zakaz + lnk.part)
                {
                    // копирование
                    xl.Range_Copy(xl.GetRows(xl.GetSheet(cur_lists+template_page), templ_foter, templ_foter));
                    // вставка
                    xl.Sheet_activate();
                    xl.Range_Paste(xl.GetRows(cur_row, cur_row));

                    xl.toCells(cur_row,     3,  "УЧАСТКУ"    );
                    xl.toCells(cur_row,     7,  utch_calc.req);
                    xl.toCells(cur_row,     8,  utch_calc.mk );
                    xl.toCells(cur_row,     9,  utch_calc.br );
                    xl.toCells(cur_row,     10, utch_calc.umk);
                    ++cur_row;

                    // копирование
                    xl.Range_Copy(xl.GetRows(xl.GetSheet(cur_lists+template_page), templ_foter, templ_foter));
                    // вставка
                    xl.Sheet_activate();
					xl.Range_Paste(xl.GetRows(cur_row, cur_row));

                    xl.toCells(cur_row,     3,  "ЗАКАЗУ"    );
                    xl.toCells(cur_row,     7,  zak_calc.req);
                    xl.toCells(cur_row,     8,  zak_calc.mk );
                    xl.toCells(cur_row,     9,  zak_calc.br );
                    xl.toCells(cur_row,     10, zak_calc.umk);
                    ++cur_row;

                    //вставить строку в отчет
                    // копирование
                    xl.Range_Copy(xl.GetRows(xl.GetSheet(cur_lists+template_page), templ_header, templ_header));
                    // вставка
                    xl.Sheet_activate();
                    xl.Range_Paste(xl.GetRows(cur_row, cur_row));
                    xl.toCells(cur_row, 7,   lnk.zakaz.c_str()   );
                    xl.toCells(cur_row, 9,   lnk.part.c_str()   );
                    xl.toCells(cur_row, 11,   lnk.utch.c_str()   );

                    ++cur_row;
                    zak_calc.reset();
                    utch_calc.reset();
                }
                else if (!cur_utch.empty() && cur_utch!=lnk.utch)
                {
                    // копирование
                    xl.Range_Copy(xl.GetRows(xl.GetSheet(cur_lists+template_page), templ_foter, templ_foter));
                    // вставка
                    xl.Sheet_activate();
                    xl.Range_Paste(xl.GetRows(cur_row, cur_row));

                    xl.toCells(cur_row,     3,  "УЧАСТКУ"    );
                    xl.toCells(cur_row,     7,  utch_calc.req);
                    xl.toCells(cur_row,     8,  utch_calc.mk );
                    xl.toCells(cur_row,     9,  utch_calc.br );
                    xl.toCells(cur_row,     10, utch_calc.umk);
                    ++cur_row;

                    //вставить строку в отчет
                    // копирование
                    xl.Range_Copy(xl.GetRows(xl.GetSheet(cur_lists+template_page), templ_header, templ_header));
                    // вставка
                    xl.Sheet_activate();
                    xl.Range_Paste(xl.GetRows(cur_row, cur_row));
                    xl.toCells(cur_row, 7,   lnk.zakaz.c_str()  );
                    xl.toCells(cur_row, 9,   lnk.part.c_str()   );
                    xl.toCells(cur_row, 11,  lnk.utch.c_str()   );

                    ++cur_row;
                    utch_calc.reset();
                }

                cur_zak = lnk.zakaz + lnk.part;
                cur_utch = lnk.utch;


                //вставить строку в отчет
                // копирование
                xl.Range_Copy(xl.GetRows(xl.GetSheet(cur_lists+template_page), template_row, template_row + row_size - 1));
                // вставка
                xl.Sheet_activate();
				xl.Range_Paste(xl.GetRows(cur_row, cur_row + row_size-1));

                xl.toCells(cur_row,     1,  lnk.vz.c_str() );
                xl.toCells(cur_row+1,   1,  "" );

                xl.toCells(cur_row,     2,  lnk.obd.c_str() );
                xl.toCells(cur_row+1,   2,  lnk.name.c_str());

                xl.toCells(cur_row,     7,  lnk.kol_req.c_str()     );
                xl.toCells(cur_row,     8,  lnk.kol_maked.c_str()   );
                xl.toCells(cur_row,     9,  lnk.kol_broken.c_str()  );
                xl.toCells(cur_row,     10, lnk.kol_unmaked.c_str() );

                xl.toCells(cur_row+1,   7,  lnk.trud_req      );
                xl.toCells(cur_row+1,   8,  lnk.trud_maked    );
                xl.toCells(cur_row+1,   9,  lnk.trud_broken   );
                xl.toCells(cur_row+1,   10, lnk.trud_unmaked  );

                xl.toCells(cur_row,     11, cache[lnk.det_id+lnk.cex+lnk.utch].c_str() );

                cex_calc.inc(lnk);
                zak_calc.inc(lnk);
                utch_calc.inc(lnk);

				cur_row+=row_size;
            }

            {
            //Итого по цеху
            // копирование
            xl.Range_Copy(xl.GetRows(xl.GetSheet(cur_lists+template_page), templ_foter, templ_foter));
            // вставка
            xl.Sheet_activate();
            xl.Range_Paste(xl.GetRows(cur_row, cur_row));

            xl.toCells(cur_row,     3,  "УЧАСТКУ"    );
            xl.toCells(cur_row,     7,  utch_calc.req);
            xl.toCells(cur_row,     8,  utch_calc.mk );
            xl.toCells(cur_row,     9,  utch_calc.br );
            xl.toCells(cur_row,     10, utch_calc.umk);
            ++cur_row;

            // копирование
            xl.Range_Copy(xl.GetRows(xl.GetSheet(cur_lists+template_page), templ_foter, templ_foter));
            // вставка
            xl.Sheet_activate();
            xl.Range_Paste(xl.GetRows(cur_row, cur_row));

            xl.toCells(cur_row,     3,  "ЗАКАЗУ"    );
            xl.toCells(cur_row,     7,  zak_calc.req);
            xl.toCells(cur_row,     8,  zak_calc.mk );
            xl.toCells(cur_row,     9,  zak_calc.br );
            xl.toCells(cur_row,     10, zak_calc.umk);
            ++cur_row;

            // копирование
            xl.Range_Copy(xl.GetRows(xl.GetSheet(cur_lists+template_page), templ_foter, templ_foter));
            // вставка
            xl.Sheet_activate();
            xl.Range_Paste(xl.GetRows(cur_row, cur_row));

            xl.toCells(cur_row,     3,  "ЦЕХУ"    );
            xl.toCells(cur_row,     7,  cex_calc.req);
            xl.toCells(cur_row,     8,  cex_calc.mk );
            xl.toCells(cur_row,     9,  cex_calc.br );
            xl.toCells(cur_row,     10, cex_calc.umk);
            ++cur_row;
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
