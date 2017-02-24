#include <reports/exsemplars/y09102.h>
#include "functions.h"
#include "boost/lexical_cast.hpp"

namespace rep
{

Y09102::Y09102 (int set): rep::Report("Загрузка оборудования по сводным группам",set),
    DB(0),path(""),use_listing(false),lists_by_file(0),object(""),element(""),type(""),template_path(""),
    cur_lists(0),templ("Y09102.xlt"),template_page(1),sm(1),page_no(0)
{
    params[REPORT_PATH];
    params[REPORT_LIST_COUNT] = "10";
	params[REPORT_USE_LISTING] = REP_TRUE;
	params["Количество смен"] = "22";
}
Y09102::~Y09102()
{}

Y09102::Y09102(const Y09102 &r):rep::Report(r),
    DB(0),path(""),use_listing(false),lists_by_file(0),object(""),element(""),type(""),template_path(""),
    cur_lists(0),templ("Y09102.xlt"),template_page(1),sm(1),page_no(0)
{

}

void Y09102::Build(void)
{
    cur_lists = 0;
    file_no = 0;
    page_no = 0;
    ParseParams();
    LoadSettings();
    BuildReport();
}
boost::shared_ptr<rep::Report> Y09102::SelfCopy (void) const
{
    return boost::shared_ptr<rep::Report>(new Y09102(*this));
}

void Y09102::ParseParams(void)
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

    if (object.empty())
        throw std::runtime_error("Не указан объект для построения отчета");
    if (type.empty())
		throw std::runtime_error("Не указан тип объекта для отчета");

	sm = boost::lexical_cast<double>(params["Количество смен"]);

}
void Y09102::LoadSettings()
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
void Y09102::BuildReport()
{
    //получить список маршрутных листов по заданию
    //этап 1 получить список деталей
    std::string drop_step_1 = "drop temporary table if exists `manufacture`.`step_1`";
    std::stringstream create_step_1;
    //step1
{
    create_step_1   <<  "create temporary table if not exists `manufacture`.`step_1` as "
                        "select "
                        "a1.zakaz, "
                        "a.part_no, "
                        "`b`.`det_id` as det_id "
                        "from `manufacture`.`parts` a "
                        "join `manufacture`.`zakaz_list` a1      on `a1`.`zak_id` = `a`.`zak_id` "
                        "join `manufacture`.`marsh_lists` b      on `b`.`part_id` = `a`.`part_id` ";

    if (type == "1")
    {//запуск
       create_step_1 << "where a.zap_id = '"<< object <<"'";
    }
    else if (type == "2")
    {//заказ
       create_step_1 << "where a.zap_id = '"<< object <<"' and a.zak_id = '"<< element <<"'";
    }
    else if (type == "4")
    {//партия
       create_step_1 << "where a.part_id = '"<< object <<"'";
    }
    else
       throw std::runtime_error("Не известный тип объекта");
}
    //этап 2 получить нормы для деталей с оборудованием
    std::stringstream sql;
    sql << "select "

           "CONVERT(g1.npodr, CHAR)     as cex_name, "
//           "CONVERT(g2.npodr, CHAR)     as utch_name, "
//           "CONVERT(c.cex, CHAR)        as cex, "
//           "CONVERT(c.utch, CHAR)       as utch, "
           "CONVERT(IFNULL(f.name, 'Неизвестная группа'), CHAR)       as obo_group, "
           "CONVERT(a.zakaz, CHAR)      as zakaz_no, "
           "CONVERT(a.part_no, CHAR)    as part_no, "
           "CONVERT(c.oboID, CHAR)      as oboid, "

           "CONVERT(ROUND(sum( "
           "if (`c`.`cex` = '03' and `c`.`utch` = '04', "
           "IFNULL(`d`.`tsht`*ceil(d1.kol_request/ifnull(`h`.`kdz`,1))/d1.kol_request*d1.kol_request+if(d1.kol_request>0,`d`.`tpz`,0),0), "
           "IFNULL(`d`.`tsht`*`d`.`ksht`*`d`.`krop`/`d`.`kolod`*d1.kol_request+if(d1.kol_request>0,`d`.`tpz`,0),0))),3),DECIMAL(40,6)) as plan, "

           "CONVERT(ROUND(sum( "
           "if (`c`.`cex` = '03' and `c`.`utch` = '04', "
           "IFNULL(`d`.`tsht`*ceil(d1.kol_request/ifnull(`h`.`kdz`,1))/d1.kol_request*(d1.kol_request - d1.kol_maked)+if((d1.kol_request - d1.kol_maked)>0,`d`.`tpz`,0),0), "
           "IFNULL(`d`.`tsht`*`d`.`ksht`*`d`.`krop`/`d`.`kolod`*(d1.kol_request - d1.kol_maked)+if((d1.kol_request - d1.kol_maked)>0,`d`.`tpz`,0),0))),3),DECIMAL(40,6)) as deficit, "

           "CONVERT(e.ksme,DECIMAL(40,6)) as ksm "

           "from `manufacture`.`step_1` a "
           "join `manufacture`.`operation_list` c   on `c`.`det_id` = `a`.`det_id` "
           "join `manufacture`.`operation_norms` d  on `d`.`OpUUID` = `c`.`OpUUID` "
           "join `manufacture`.`orders` d1  on `d1`.`operation_id` = `c`.`OpUUID` "

           /*left*/" join `equipment`.`obor_list` e     on `e`.`oboID` = `c`.`oboID` "
           "left join `equipment`.`obor_groups` e1  on `e1`.`oboID` = `e`.`oboID` "
           "left join `equipment`.`groups` f        on `f`.`group_id` = `e1`.`group_id` "

           "left join `catalogs`.`podr_list` g1     on `g1`.`cex` = `c`.`cex` and `g1`.`utch` = '' "
           "left join `catalogs`.`podr_list` g2     on `g2`.`cex` = `c`.`cex` and `g2`.`utch` = `c`.`utch` "
           "left join `manufacture`.`det_info` h    on `h`.`det_id` = `a`.`det_id` "
           "group by c.cex,c.utch,f.name, c.oboID, a.zakaz, a.part_no";

    DB->SendCommand(drop_step_1.c_str());
    DB->SendCommand(create_step_1.str().c_str());
    TADOQuery *rez = DB->SendSQL(sql.str().c_str());
    DB->SendCommand(drop_step_1.c_str());

    if (rez)
    {
        if (rez->RecordCount)
        {
            typedef std::map<const std::string, Data> RecordData;
            std::map<const std::string, RecordData> rep_data;

            for (rez->First(); !rez->Eof; rez->Next())
            {
                std::string cex_name    =   (rez->FieldByName("cex_name")->Value.operator AnsiString()).c_str();
                std::string obo_group   =   (rez->FieldByName("obo_group")->Value.operator AnsiString()).c_str();
                std::string zakaz_no    =   (rez->FieldByName("zakaz_no")->Value.operator AnsiString()).c_str();
                std::string part_no     =   (rez->FieldByName("part_no")->Value.operator AnsiString()).c_str();
                std::string oboid       =   (rez->FieldByName("oboid")->Value.operator AnsiString()).c_str();

                double plan     =   rez->FieldByName("plan")->Value.operator double();
                double deficit  =   rez->FieldByName("deficit")->Value.operator double();
                double ksm      =   rez->FieldByName("ksm")->Value.operator double();

                Data &lnk = rep_data[cex_name][obo_group];
                lnk.AddRow(oboid, zakaz_no+" "+part_no, ksm, plan, deficit);
            }

            if (rep_data.size())
            {
                //включаем ексель
                cExcel xl;
                xl.Connect();
                xl.Visible(false);
                xl.DisplayAlerts(false);


                OpenTemplate(xl, template_path + templ);

                size_t row = 0;
                size_t empty_row_tmpl = 5;
                size_t group_row_tmpl = 3;
                size_t data_row_tmpl = 6;
                for (std::map<const std::string, RecordData>::const_iterator it_1 = rep_data.begin(); it_1!=rep_data.end(); ++it_1)
                {
                    const RecordData &lnk = it_1->second;

                    CheckList(xl, row, 1);

                    // копирование
                    xl.Range_Copy(xl.GetRows(xl.GetSheet(cur_lists+template_page), empty_row_tmpl, empty_row_tmpl));
                    // вставка
                    xl.Sheet_activate();
                    xl.Range_Paste(xl.GetRows(row, row));

                    xl.toCells(row, 1, it_1->first.c_str());//добавлям строчку цеха

                    ++row;

                    for (RecordData::const_iterator it_2 = lnk.begin(); it_2!=lnk.end(); ++it_2)
                    {

                        const std::string &group = it_2->first;

                        const Data &lnk = it_2->second;

                        size_t rows_count = lnk.getRowsCount();
                        CheckList(xl, row, rows_count);

                        // копирование
                        xl.Range_Copy(xl.GetRows(xl.GetSheet(cur_lists+template_page), group_row_tmpl, group_row_tmpl));
                        // вставка
                        xl.Sheet_activate();
                        xl.Range_Paste(xl.GetRows(row, row));

                        if (rows_count > 1)
                        {
                            // копирование
                            xl.Range_Copy(xl.GetRows(xl.GetSheet(cur_lists+template_page), data_row_tmpl, data_row_tmpl));
                            xl.Sheet_activate();
                            for (size_t ofset = 1; ofset < rows_count; ++ofset)
                            {
                                xl.Range_Paste(xl.GetRows(row+ofset, row+ofset));
                            }
                        }
                        //добавляем данные по группе

                        xl.toCells(row, 1, group.c_str()         );
						xl.toCells(row, 3, lnk.getOboCount()     );
						xl.toCells(row, 4, lnk.getKsm()          );
						xl.toCells(row, 5, lnk.getPlanLoad()     );
						xl.toCells(row, 6, lnk.getDificitLoad()  );
						xl.toCells(row, 7, lnk.getMaximimLoad(sm));
						xl.toCells(row, 8, lnk.getDelta(sm)      );
						xl.toCells(row, 9, ""                    );

                        std::list<std::string> dt = lnk.getZakazStrings();
                        size_t ofset = 1;
                        for (std::list<std::string>::const_iterator it = dt.begin(); it!=dt.end(); ++it)
                        {
                            const std::string &s = *it;
                            xl.toCells(row + ofset, 1, s.c_str());
                            ++ofset;
                        }

                        row += rows_count;
                    }
                }

                if (!path.empty())//закрываем Excel в зависимости от опции сохранения в файл
                {
                    SaveFile(xl,path ,"",cur_lists,file_no);
                    xl.Book_Close(xl.GetBook(1));
                    xl.Disconnect();
                }
                else
                {
                    RemoveTemplates(xl,cur_lists);
                    xl.Visible(true);
                }
            }
        }
        delete rez;
    }
    else
    {
        throw std::runtime_error("Ошибка соединения с базой данных");
    }
}

void Y09102::CheckList (cExcel &xl, size_t &row, size_t row_size)
{

    const size_t start_row = 4, end_row = 58;

    bool new_page = !row + (row + row_size > end_row);//проанализировать количестко оставшихся строк

    if (new_page)
    {
        if (cur_lists)
        {
            if (use_listing && !path.empty())
            {//проверяем количество страниц, если выставлена опция
                TrimFile(xl,path,"",cur_lists,lists_by_file,template_path + templ,file_no);
            }
        }

        //создать страницу
        xl.Sheet_Copy(xl.GetSheet(cur_lists+template_page), xl.GetSheet(cur_lists+1), Variant().NoParam());
        cur_lists++ ;
        page_no++;
        xl.SetActiveSheet(xl.GetSheet(cur_lists));
        std::stringstream buf;
        buf<<page_no;
        xl.Set_Sheet_Name(xl.GetSheet(cur_lists),("ФY09102-"+buf.str()).c_str());

        // почистить лист
        // копирование
        xl.Range_Copy(xl.GetRows(xl.GetSheet(cur_lists+template_page), 7, 9));
        // вставка
        xl.Sheet_activate();
        xl.Range_Paste(xl.GetRows(4, 6));

        //заполнить шапку

        xl.toCells(2,   1,   Now().FormatString("dd.mm.yyyy")           );

        row = start_row;
    }
}

}
