#include <reports/exsemplars/zakaz_trud_report.h>

#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/gregorian/gregorian_io.hpp>
#include <xl_operations.h>
#include <iostream>

#include "functions.h"

namespace bgreg = boost::gregorian;

namespace rep
{

ZakazTrudReport::ZakazTrudReport (int set): rep::Report("Отчет о трудозатратах по заказам",set),
    DB(0),path(""),use_listing(false),lists_by_file(0),object(""),element(""),type(""),template_path(""),
    cur_lists(0),templ("manufacture_forms.xlt"),date_from(""),date_to(""),use_zakaz_group(false),surcharge(false)
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
    params["Группировать по заказам"] = REP_TRUE;
    params["Доплатные"] = REP_FALSE;
}
ZakazTrudReport::~ZakazTrudReport()
{}

ZakazTrudReport::ZakazTrudReport(const ZakazTrudReport &r):rep::Report(r),
    DB(0),path(""),use_listing(false),lists_by_file(0),object(""),element(""),type(""),template_path(""),
    cur_lists(0),templ("manufacture_forms.xlt"),date_from(""),date_to(""),use_zakaz_group(false),surcharge(false)
{

}

void ZakazTrudReport::Build(void)
{
    cur_lists = 0;
    ParseParams();
    LoadSettings();
    BuildReport();
}
boost::shared_ptr<rep::Report> ZakazTrudReport::SelfCopy (void) const
{
    return boost::shared_ptr<rep::Report>(new ZakazTrudReport(*this));
}

void ZakazTrudReport::ParseParams(void)
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

//    if (object.empty())
//        throw std::runtime_error("Не указан объект для построения отчета");
//    if (type.empty())
//        throw std::runtime_error("Не указан тип объекта для отчета");
    date_to = params["Окончание периода"];
    date_from = params["Начало периода"];
    use_zakaz_group = params["Группировать по заказам"] != REP_FALSE && params["Группировать по заказам"] != REP_NULL;
    surcharge = params["Доплатные"] != REP_FALSE && params["Доплатные"] != REP_NULL;
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
void ZakazTrudReport::LoadSettings()
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


void ZakazTrudReport::BuildReport()
{
    //получить список маршрутных листов по заданию
    DB->SendCommand("drop temporary table if EXISTS `tmp`");
    DB->SendCommand(
    "create temporary table if not exists `tmp` "
    "( "
    "det_id bigint(20) unsigned NULL, "
    "surch_id bigint(20) unsigned NULL, "
    "maked int(10) unsigned NOT NULL, "
    "broken int(10) unsigned NOT NULL, "
    "cex varchar(10) NOT NULL, "
    "tab_no int(11) NOT NULL, "
    "trud double not null default 0.0, "
    "date datetime  NOT NULL, "

    "key det_id (`det_id`), "
    "key surch_id (`surch_id`), "
    "key tab_no (`tab_no`), "
    "key date (`date`) "
    ")engine = MEMORY ");

    std::stringstream sql;
    if (!surcharge)
    {
        sql <<//основные наряды
        "insert into tmp "
        "select "
        "    c1.det_id as det_id, "
        "    NULL as surch_id, "
        "    a.maked as maked, "
        "    a.broken as broken, "
        "    e.cex  as cex, "
        "    a.tab_no as tab_no, "
        "    if (e.cex = '03' and e.utch = '04', "
        "    IFNULL(`c`.`tsht`*ceil(`b`.`kol_request`/`c1`.`kdz`)/`b`.`kol_request`*`a`.`maked`+`c`.`tpz`,0), "
        "    IFNULL(`c`.`tsht`*`c`.`ksht`*`c`.`krop`/`c`.`kolod`*a.maked+`c`.`tpz`,0) "
        "    ) as trud, "
        "    a.date "
        "from `manufacture`.`orders_history` a "
        "    join `manufacture`.`orders` b on b.order_id = a.order_id "
        "    join `manufacture`.`operation_norms` c on c.OpUUID = b.operation_id "
        "    join `manufacture`.`operation_list` e on e.OpUUID = b.operation_id "
        "    join `manufacture`.`det_info` c1 on c1.det_id = e.det_id "
        "where '"<<AnsiString(TDateTime(date_from.c_str()).FormatString("yyyy-mm-dd")).c_str() <<"' <= a.date and a.date < '"
                 <<AnsiString(TDateTime(date_to.c_str()).FormatString("yyyy-mm-dd")).c_str()<<"'";
    }
    else
    {
        sql <<//доплатные
        "insert into tmp "
        "select "
        "    NULL as det_id, "
        "    a.surcharge_id as surch_id,"
        "    a.kol_maked as maked, "
        "    a.kol_broken as broken, "
        "    b.cex  as cex, "
        "    b.tab_no as tab_no, "
        "    if (b.cex = '03' and b.utch = '04', "
        "    IFNULL(`b`.`tsht`*`a`.`kol_maked`+`b`.`tpz`,0), "
        "    IFNULL(`b`.`tsht`*`a`.`kol_maked`+`b`.`tpz`,0) "
        "    ) as trud, "
        "    a.creation_date "
        "from `manufacture`.`orders` a "
        "    join `manufacture`.`surcharge` b on b.record_id = a.surcharge_id "
        "where '"<<AnsiString(TDateTime(date_from.c_str()).FormatString("yyyy-mm-dd")).c_str() <<"' <= a.creation_date and a.creation_date < '"
                 <<AnsiString(TDateTime(date_to.c_str()).FormatString("yyyy-mm-dd")).c_str()<<"'";
    }
    DB->SendCommand(sql.str().c_str());

    sql.str("");
    if (!surcharge)
    {
        sql <<
        "select "
        "d.zakaz, "
        "sum(a.maked) as maked, "
        "sum(a.broken) as broken, "
        "a.tab_no, "
        "round(sum(a.trud),3) as trud, "
        "IFNULL(concat(e.family, ' ',Upper(left(e.name,1)),'.', Upper(left(e.otch,1)),'.'),'') fio, "
        " '' reason "
        "from tmp a "
        "    join `manufacture`.`marsh_lists`   b on b.det_id = a.det_id "
        "    join `manufacture`.`parts`         c on c.part_id = b.part_id "
        "    join `manufacture`.`zakaz_list`    d on d.zak_id = c.zak_id "
        "    left join `manufacture`.`workers` e on e.tab_no = a.tab_no and e.date_from <= a.date and IF(e.date_to != 0, a.date < e.date_to, 1) ";
        if (use_zakaz_group)
            sql << "group by d.zakaz,e.family,a.tab_no";
        else
            sql << "group by e.family,a.tab_no,d.zakaz";
    }
    else
    {
        sql<<
            " select "
            "c.zakaz, "
            "sum(a.maked) as maked, "
            "sum(a.broken) as broken, "
            "b.tab_no, "
            "round(sum(a.trud),3) as trud, "
            "IFNULL(concat(e.family, ' ',Upper(left(e.name,1)),'.', Upper(left(e.otch,1)),'.'),'') fio, "
            " b.reason reason "
            "from tmp a "
            "    join `manufacture`.`surcharge` b on b.record_id = a.surch_id "
            "    join `manufacture`.`zakaz_list` c on c.zak_id = b.zak_id "
            "    left join `manufacture`.`workers` e on e.tab_no = b.tab_no and e.date_from <= a.date and IF(e.date_to != 0, a.date < e.date_to, 1) ";
        if (use_zakaz_group)
            sql << "group by c.zakaz,e.family,b.tab_no";
        else
            sql << "group by e.family,b.tab_no,c.zakaz";
    }
	TADOQuery *rez = DB->SendSQL(sql.str().c_str());
	DB->SendCommand("drop temporary table if EXISTS `tmp`");

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
            size_t start_row = 4, end_row = 43, row_size = 1, template_row = 4;
            size_t template_page = 9;

            size_t max_rows = (end_row - start_row)*2;
            size_t cur_rows(0);
            size_t list_count(0);

            CexData cex_data;
            std::string cur_mark("");

            for (rez->First(); !rez->Eof; rez->Next())
            {
                Data tmp;
                tmp.zakaz   =   (rez->FieldByName("zakaz")->Value.operator AnsiString()).c_str();
                tmp.tab_no  =   (rez->FieldByName("tab_no")->Value.operator AnsiString()).c_str();
                tmp.fio     =   (rez->FieldByName("fio")->Value.operator AnsiString()).c_str();
                tmp.trud    =   rez->FieldByName("trud")->Value.operator double();
                tmp.reason     =   (rez->FieldByName("reason")->Value.operator AnsiString()).c_str();

                std::string mark;
                if (use_zakaz_group)
                {
                    mark = tmp.zakaz;
                }
                else
                {
                    mark = tmp.fio+tmp.tab_no;
                }
                if (cur_mark != mark)
                {
                    cur_mark = mark;
                    ++cur_rows;
                }
                ++cur_rows;
                cex_data.insert(CexDataItem(mark, tmp));
            }
            //расчитать кол - во страниц для цеха
            size_t curr_page_count = cur_rows/max_rows;
            if (cur_rows%max_rows)
                ++curr_page_count;

            list_count += curr_page_count;

            //считать данные подсчитать колво страниц
            //вывести данные
            size_t file_no = 0;

            size_t column_ofset = 0;

            cur_mark = "";

            double sum_trud(0.0);
            size_t page_no(0);
            for (CexData::const_iterator it = cex_data.begin(); it!=cex_data.end(); ++it)
            {
                const Data &lnk = it->second;

                bool need_switch = (cur_row + row_size > end_row);

                bool t1 = need_switch*column_ofset;

                std::string mark;
                std::string mark_type;
                if (use_zakaz_group)
                {
                    mark = lnk.zakaz;
                    mark_type = "заказу";
                }
                else
                {
                    mark = lnk.fio+lnk.tab_no;
                    mark_type = "робочему";
                }
                bool t2 = (!cur_mark.empty() && cur_mark!=mark);

                new_page = new_page + t1;// + t2;//проанализировать количестко оставшихся строк

                if (t2)
                {
                    //Итого по цеху
                    if (!column_ofset)
                    {
                        // копирование
                        xl.Range_Copy(xl.GetRows(xl.GetSheet(cur_lists+template_page), template_row, template_row + row_size - 1));
                        // вставка
                        xl.Sheet_activate();
                        xl.Range_Paste(xl.GetRows(cur_row, cur_row + row_size-1));
                    }
                    xl.toCells(cur_row,     column_ofset+3,  std::string("Итого по "+mark_type).c_str());
                    if (!column_ofset)
                        xl.toCells(cur_row,     column_ofset+6,  sum_trud   );
                    else
                        xl.toCells(cur_row,     column_ofset+8,  sum_trud   );

                    sum_trud = 0;
                    ++cur_row;
                }
                cur_mark = mark;

                if(need_switch)
                {
                    column_ofset = 8;
                    cur_row = start_row;
                }
                if (new_page)
                {
                    column_ofset = 0;
                    new_page = false;

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
                    page_no++;
                    xl.SetActiveSheet(xl.GetSheet(cur_lists));
                    std::stringstream buf;
                    buf<<page_no;
                    xl.Set_Sheet_Name(xl.GetSheet(cur_lists),("Трудозатраты-"+buf.str()).c_str());


                    xl.toCells(1, 17,   page_no             );
                    xl.toCells(1, 19,   list_count          );
                    xl.toCells(2, 2,    Now().FormatString("dd.mm.yyyy")   );
                    xl.toCells(2, 7,    date_from.c_str()   );
                    xl.toCells(2, 11,   date_to.c_str()     );

                    if (!surcharge)
                        xl.toCells(2, 15,   "Основные наряды"     );
                    else
                        xl.toCells(2, 15,   "Доплатные наряды"    );

                    cur_row = start_row;
                }

                if (!column_ofset)
                {
                    //вставить строку в отчет
                    // копирование
                    xl.Range_Copy(xl.GetRows(xl.GetSheet(cur_lists+template_page), template_row, template_row + row_size - 1));
                    // вставка
                    xl.Sheet_activate();
                    xl.Range_Paste(xl.GetRows(cur_row, cur_row + row_size-1));
                }

                xl.toCells(cur_row,     column_ofset+1,  lnk.zakaz.c_str() );
                xl.toCells(cur_row,     column_ofset+2,  lnk.tab_no.c_str() );
                xl.toCells(cur_row,     column_ofset+3,  lnk.fio.c_str()    );
                if (!column_ofset)
                    xl.toCells(cur_row,     column_ofset+6,  lnk.trud       );
                else
                    xl.toCells(cur_row,     column_ofset+8,  lnk.trud       );

                sum_trud += lnk.trud;
                ++cur_row;
            }
            if (!column_ofset)
            {
                // копирование
                xl.Range_Copy(xl.GetRows(xl.GetSheet(cur_lists+template_page), template_row, template_row + row_size - 1));
                // вставка
                xl.Sheet_activate();
                xl.Range_Paste(xl.GetRows(cur_row, cur_row + row_size-1));
            }
            std::string mark_type;
            if (use_zakaz_group)
            {
                mark_type = "заказу";
            }
            else
            {
                mark_type = "робочему";
            }
            xl.toCells(cur_row,     column_ofset+3,  std::string("Итого по "+mark_type).c_str());
            if (!column_ofset)
                xl.toCells(cur_row,     column_ofset+6,  sum_trud   );
            else
                xl.toCells(cur_row,     column_ofset+8,  sum_trud   );




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
