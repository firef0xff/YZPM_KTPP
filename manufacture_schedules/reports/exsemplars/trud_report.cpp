#include <reports/exsemplars/trud_report.h>

#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/gregorian/gregorian_io.hpp>
#include <xl_operations.h>
#include <iostream>

#include "functions.h"

namespace bgreg = boost::gregorian;

namespace rep
{

TrudReport::TrudReport (int set): rep::Report("Отчет о трудозатратах",set),
    DB(0),path(""),use_listing(false),lists_by_file(0),object(""),element(""),type(""),template_path(""),
    cur_lists(0),templ("manufacture_forms.xlt"),date_from(""),date_to(""),surcharge(false)
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
    params["Доплатные"] = REP_FALSE;
}
TrudReport::~TrudReport()
{}

TrudReport::TrudReport(const TrudReport &r):rep::Report(r),
    DB(0),path(""),use_listing(false),lists_by_file(0),object(""),element(""),type(""),template_path(""),
    cur_lists(0),templ("manufacture_forms.xlt"),date_from(""),date_to(""),surcharge(false)
{

}

void TrudReport::Build(void)
{
    cur_lists = 0;
    ParseParams();
    LoadSettings();
    BuildReport();
}
boost::shared_ptr<rep::Report> TrudReport::SelfCopy (void) const
{
    return boost::shared_ptr<rep::Report>(new TrudReport(*this));
}

void TrudReport::ParseParams(void)
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
void TrudReport::LoadSettings()
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


void TrudReport::BuildReport()
{
    //получить список маршрутных листов по заданию
    std::stringstream sql;
    if (!surcharge)
    {
        sql <<
        "select "
        "CONVERT(sum(a.maked), CHAR) as maked, "
        "CONVERT(sum(a.broken), CHAR) as broken, "
        "CONVERT(e.cex, CHAR) as cex, "
        "CONVERT(IFNULL(concat(d.family, ' ',Upper(left(d.name,1)),'.', Upper(left(d.otch,1)),'.'),''), CHAR) as fio, "
        "CONVERT(a.tab_no, CHAR) as tab_no, "
        "CONVERT(round(sum(if (e.cex = '"<< "03" <<"' and e.utch = '"<< "04" <<"', "
        "IFNULL(`c`.`tsht`*ceil(`b`.`kol_request`/`c1`.`kdz`)/`b`.`kol_request`*`a`.`maked`+`c`.`tpz`,0), "
        "IFNULL(`c`.`tsht`*`c`.`ksht`*`c`.`krop`/`c`.`kolod`*a.maked+`c`.`tpz`,0) "
        ")),3), DECIMAL(40,6)) as trud "
        "from `manufacture`.`orders_history` a "
        "join `manufacture`.`orders` b on b.order_id = a.order_id "
        "join `manufacture`.`operation_norms` c on c.OpUUID = b.operation_id "
        "join `manufacture`.`operation_list` e on e.OpUUID = b.operation_id "
        "join `manufacture`.`det_info` c1 on c1.det_id = e.det_id "
        "left join `manufacture`.`workers` d on d.tab_no = a.tab_no and d.date_from <= a.date and IF(d.date_to != 0, a.date < d.date_to, 1) "
        "where '"<<AnsiString(TDateTime(date_from.c_str()).FormatString("yyyy-mm-dd")).c_str() <<"' <= a.date and a.date < '"
                 <<AnsiString(TDateTime(date_to.c_str()).FormatString("yyyy-mm-dd")).c_str()<<"'";

        sql << "group by e.cex,a.tab_no,d.family ";
    }
    else
    {
        sql <<
        "select "
        "CONVERT(sum(a.kol_maked), CHAR) as maked, "
        "CONVERT(sum(a.kol_broken), CHAR) as broken, "
        "CONVERT(b.cex, CHAR) as cex, "
        "CONVERT(IFNULL(concat(d.family, ' ',Upper(left(d.name,1)),'.', Upper(left(d.otch,1)),'.'),''), CHAR) as fio, "
        "CONVERT(b.tab_no, CHAR) as tab_no, "
        "CONVERT(round(sum(if (b.cex = '"<< "03" <<"' and b.utch = '"<< "04" <<"', "
        "    IFNULL(`b`.`tsht`*`a`.`kol_maked`+`b`.`tpz`,0), "
        "    IFNULL(`b`.`tsht`*`a`.`kol_maked`+`b`.`tpz`,0) "
        ")),3), DECIMAL(40,6)) as trud "
        "from `manufacture`.`orders` a "
        "join `manufacture`.`surcharge` b on b.record_id = a.surcharge_id "
        "left join `manufacture`.`workers` d on d.tab_no = b.tab_no and d.date_from <= a.creation_date and IF(d.date_to != 0, a.creation_date < d.date_to, 1) "
        "where '"<<AnsiString(TDateTime(date_from.c_str()).FormatString("yyyy-mm-dd")).c_str() <<"' <= a.creation_date and a.creation_date < '"
                 <<AnsiString(TDateTime(date_to.c_str()).FormatString("yyyy-mm-dd")).c_str()<<"'";

        sql << "group by b.cex,b.tab_no,d.family ";
    }

    TADOQuery *rez = DB->SendSQL(sql.str().c_str());
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
            size_t start_row = 4, end_row = 60, row_size = 1, template_row = 4;
            size_t template_page = 8;

            size_t max_rows = (end_row - start_row)*2;
            size_t cur_rows(0);
            size_t list_count(0);

            CexData cex_data;
            std::string cur_cex("");

            for (rez->First(); !rez->Eof; rez->Next())
            {
                Data tmp;
                tmp.cex     =   (rez->FieldByName("cex")->Value.operator AnsiString()).c_str();
                tmp.tab_no  =   (rez->FieldByName("tab_no")->Value.operator AnsiString()).c_str();
                tmp.fio     =   (rez->FieldByName("fio")->Value.operator AnsiString()).c_str();
                tmp.trud    =   rez->FieldByName("trud")->Value.operator double();

                if (cur_cex != tmp.cex)
                {
                    cur_cex = tmp.cex;
                    //расчитать кол - во страниц для цеха
                    size_t curr_page_count = cur_rows/max_rows;
                    if (cur_rows%max_rows)
                        ++curr_page_count;

                    list_count += curr_page_count;
                }
                ++cur_rows;
                cex_data.insert(CexDataItem(tmp.cex, tmp));
            }
            //расчитать кол - во страниц для цеха
            size_t curr_page_count = cur_rows/max_rows;
            if (cur_rows%max_rows)
                ++curr_page_count;

            list_count += curr_page_count;

            //считать данные подсчитать колво страниц
            //разбить на цеха
            //вывести данные
            size_t file_no = 0;

            size_t column_ofset = 0;

            cur_cex = "";
            double sum_trud_ceh(0.0);
            size_t page_no(0);
            for (CexData::const_iterator it = cex_data.begin(); it!=cex_data.end(); ++it)
            {
                const Data &lnk = it->second;

                bool need_switch = (cur_row + row_size > end_row);

                bool t1 = need_switch*column_ofset;

                bool t2 = (!cur_cex.empty() && cur_cex!=lnk.cex);

                new_page = new_page + t1 + t2;//проанализировать количестко оставшихся строк

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
                    xl.toCells(cur_row,     column_ofset+2,  "Итого по цеху"    );
                    if (!column_ofset)
                        xl.toCells(cur_row,     column_ofset+5,  sum_trud_ceh   );
                    else
                        xl.toCells(cur_row,     column_ofset+7,  sum_trud_ceh   );

                    sum_trud_ceh = 0;
                    ++cur_row;
                }

                if(need_switch)
                {
                    column_ofset = 7;
                    cur_row = start_row;
                }
                if (new_page)
                {
                    column_ofset = 0;
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
                    page_no++;
                    xl.SetActiveSheet(xl.GetSheet(cur_lists));
                    std::stringstream buf;
                    buf<<page_no;
                    xl.Set_Sheet_Name(xl.GetSheet(cur_lists),("Трудозатраты-"+buf.str()).c_str());


                    xl.toCells(1, 12,   lnk.cex.c_str()     );
                    xl.toCells(1, 15,   page_no             );
                    xl.toCells(1, 17,   list_count          );
                    xl.toCells(2, 2,    Now().FormatString("dd.mm.yyyy")   );
                    xl.toCells(2, 6,    date_from.c_str()   );
                    xl.toCells(2, 9,    date_to.c_str()     );

                    if (!surcharge)
                        xl.toCells(2, 12,   "Основные наряды"     );
                    else
                        xl.toCells(2, 12,   "Доплатные наряды"    );

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

                xl.toCells(cur_row,     column_ofset+1,  lnk.tab_no.c_str() );
                xl.toCells(cur_row,     column_ofset+2,  lnk.fio.c_str()    );
                if (!column_ofset)
                    xl.toCells(cur_row,     column_ofset+5,  lnk.trud       );
                else
                    xl.toCells(cur_row,     column_ofset+7,  lnk.trud       );

                sum_trud_ceh += lnk.trud;
                ++cur_row;
            }
            // копирование
            xl.Range_Copy(xl.GetRows(xl.GetSheet(cur_lists+template_page), template_row, template_row + row_size - 1));
            // вставка
            xl.Sheet_activate();
            xl.Range_Paste(xl.GetRows(cur_row, cur_row + row_size-1));

            xl.toCells(cur_row,     column_ofset+2,  "Итого по цеху"    );
            if (!column_ofset)
                xl.toCells(cur_row,     column_ofset+5,  sum_trud_ceh   );
            else
                xl.toCells(cur_row,     column_ofset+7,  sum_trud_ceh   );




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
