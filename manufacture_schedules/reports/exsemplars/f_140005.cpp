#include <reports/exsemplars/f_140005.h>
#include <xl_operations.h>
#include "functions.h"

namespace rep
{

F140005::F140005 (int set): rep::Report("План производства: Форма 140005",set),
    DB(0),path(""),use_listing(false),lists_by_file(0),object(""),element(""),type(""),template_path(""),
    cur_lists(0),templ("manufacture_forms.xlt")
{
    params[REPORT_PATH];
    params[REPORT_LIST_COUNT] = "10";
    params[REPORT_USE_LISTING] = REP_TRUE;
    params["Цех"];
    params["Участок"];
}
F140005::~F140005()
{}

F140005::F140005(const F140005 &r):rep::Report(r),
    DB(0),path(""),use_listing(false),lists_by_file(0),object(""),element(""),type(""),template_path(""),
    cur_lists(0),templ("manufacture_forms.xlt")
{

}

void F140005::Build(void)
{
    cur_lists = 0;
    ParseParams();
    LoadSettings();
    BuildReport();
}
boost::shared_ptr<rep::Report> F140005::SelfCopy (void) const
{
    return boost::shared_ptr<rep::Report>(new F140005(*this));
}

void F140005::ParseParams(void)
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

    ceh = params["Цех"];
    utch = params["Участок"];
}
void F140005::LoadSettings()
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
void F140005::BuildReport()
{
    //получить список маршрутных листов по заданию
    std::stringstream sql;
    sql << "select "
        << "a.part_id, "
        << "a.part_no, "
        << "b.zakaz "
        << "from manufacture.parts a "
        << "join manufacture.zakaz_list b on b.zak_id = a.zak_id ";
    if (type == "1")
    {//запуск
        sql << "where a.zap_id = '"<< object <<"'";
    }
    else if (type == "2")
    {//заказ
        sql << "where a.zap_id = '"<< object <<"' and a.zak_id = '"<< element <<"'";
    }
    else if (type == "4")
    {//партия
        sql << "where a.part_id = '"<< object <<"'";
    }
    else
        throw std::runtime_error("Не известный тип объекта");

    sql << "order by b.zakaz, a.part_no ";

    TADOQuery *rez = DB->SendSQL(sql.str().c_str());
    if (rez)
    {
        if (rez->RecordCount)
        {
            std::string part_id =   (rez->FieldByName("part_id")->Value.operator AnsiString()).c_str();
            std::string zakaz =     (rez->FieldByName("zakaz")->Value.operator AnsiString()).c_str();
            std::string part_no =   (rez->FieldByName("part_no")->Value.operator AnsiString()).c_str();
            BuildData(part_id,zakaz,part_no);
        }
        delete rez;
    }
    else
    {
        throw std::runtime_error("Ошибка соединения с базой данных");
    }
}
void F140005::BuildData      (std::string part_id, std::string zakaz, std::string part_no)
{
    std::string drop_step_1 = "drop temporary table if exists `manufacture`.`step_1`";
    std::string drop_step_2 = "drop temporary table if exists `manufacture`.`step_2`";
    std::string drop_step_3 = "drop temporary table if exists `manufacture`.`step_3`";

    std::stringstream create_step_1;
    std::stringstream create_step_2;
    std::stringstream create_step_3;
    std::stringstream sql;
{
    create_step_1   << "create temporary table if not exists `manufacture`.`step_1` as "
                       "select "
                       "`a`.`det_id`as det_id, "
                       "`a`.`sp_id` as sp_id, "
                       "`a`.`list_no` as ml_no, "
                       "`b`.`obd`   as obd, "
                       "`b`.`name`  as name, "
                       "sum(IFNULL(`c`.`kol_using`,`d`.`kol`)) as kol, "
                       "IFNULL(concat(TRIM(e.pm),' ',TRIM(e.napr)),'') as pm, "
                       "IFNULL(ROUND(e.nrm-e.masd,3),'') as ost, "
                       "if (left(concat(e.pm,' ',e.napr),4)='0303'or right(concat(e.pm,' ',e.napr),4)='0303',1,2) as prizn, "
                       "IFNULL(`f1`.`nama`,IFNULL(`f2`.`name`,'')) nama, "
                       "IFNULL(`f1`.`prma`,'') prma "

                       "from `manufacture`.`marsh_lists` a "
                       "join `manufacture`.`det_names` b on `b`.`det_id` = `a`.`det_id` "
                       "left join `manufacture`.`det_tree` c on `c`.`det_idc` = `a`.`det_id` "
                       "left join `manufacture`.`part_content` d on `d`.`det_id` = `a`.`det_id` "
                       "join `manufacture`.`det_info` e on `e`.`det_id` = `a`.`det_id` "
                       "left join `manufacture`.`materials` f1 on `f1`.`obmid` = `e`.`obmid` "
                       "left join `manufacture`.`det_names` f2 on `f2`.`det_id` = `e`.`obmid` "

                       "where `a`.`part_id` = '" << part_id << "' "
                       "group by `a`.`det_id`";

    //получить нормы для деталей
    create_step_2   << "create temporary table if not exists `manufacture`.`step_2` as "
                       "select "
                       "`a`.`det_id` as det_id, "
                       "IFNULL(ROUND(sum(`c`.`tpz`/`c`.`kolod`),3),0) as tpz, "
                       "IFNULL(ROUND(sum(`c`.`tsht`*`c`.`ksht`*`c`.`krop`/`c`.`kolod`),3),0) as tsht "
                       "from `manufacture`.`marsh_lists` a "
                       "join `manufacture`.`operation_list` b on `b`.`det_id` = `a`.`det_id` "
                       "left join `manufacture`.`operation_norms`c on `c`.`OpUUID` = `b`.`OpUUID` "

                       "where `a`.`part_id` = '"<<part_id <<"' ";
    if (!ceh.empty())
    {
        create_step_2 << " and `b`.`cex` = '"<< ceh <<"' ";
        if (!utch.empty())
            create_step_2 << " and `b`.`utch` = '"<< utch <<"' ";
    }
    create_step_2 <<   "group by `a`.`det_id` ";

    create_step_3 <<    "create temporary table if not exists `manufacture`.`step_3` as "
                        "select "
                        "`a`.`det_id` as det_id, "
                        "IFNULL(max(`c`.`order_id`),'') as order_no "
                        "from `manufacture`.`marsh_lists` a "
                        "join `manufacture`.`operation_list` b on `b`.`det_id` = `a`.`det_id` "
                        "left join `manufacture`.`orders` c on `c`.`operation_id` = `b`.`OpUUID` "

                        "where (`b`.`det_id`,`b`.`opr`) in "
                            "( "
                                "select "
                                "`a`.`det_id` as det_id, "
                                "max(`b`.`opr`) as opr "
                                "from `manufacture`.`marsh_lists` a "
                                "join `manufacture`.`operation_list` b on `b`.`det_id` = `a`.`det_id` "

                                "where `a`.`part_id` = '"<< part_id <<"' "
                                "group by `a`.`det_id` "
                            ") "
                        "group by `a`.`det_id` ";


    sql <<  "select "
            "`a`.`ml_no`, "
            "`a`.`obd`, "
            "`a`.`name`, "
            "`a`.`kol`, "
            "`a`.`pm`, "
            "`a`.`ost`, "
            "`a`.`prizn`, "
            "`a`.`nama`, "
            "`a`.`prma`, "
            "`b`.`tpz`, "
            "`b`.`tsht`, "
            "`b`.`tpz` * `a`.`kol` as tpz_part, "
            "`b`.`tsht`* `a`.`kol` as tsht_part, "
            "`c`.`order_no` "
            "from `manufacture`.`step_1` a "
            "join `manufacture`.`step_2` b on `b`.`det_id` = `a`.`det_id` "
            "join `manufacture`.`step_3` c on `c`.`det_id` = `a`.`det_id` "
            "order by `a`.`prizn`,`a`.`sp_id`,`a`.`obd`";

}

    DB->SendCommand(drop_step_1.c_str());
    DB->SendCommand(create_step_1.str().c_str());
    DB->SendCommand(drop_step_2.c_str());
    DB->SendCommand(create_step_2.str().c_str());
    DB->SendCommand(drop_step_3.c_str());
    DB->SendCommand(create_step_3.str().c_str());

    TADOQuery *rez = DB->SendSQL(sql.str().c_str());

    DB->SendCommand(drop_step_1.c_str());
    DB->SendCommand(drop_step_2.c_str());
    DB->SendCommand(drop_step_3.c_str());
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
            size_t start_row = 4, end_row = 55, row_size = 2, template_row = 5,template_empty_row = 8,template_final_row = 10;
            size_t template_page = 3;
            size_t max_page_no=0;
            //подсчет строк
            for (rez->First(); !rez->Eof; rez->Next())
            {
                //считать все данные в структуры спрогнозировать разметку
            }
            //пробежаться по списку структур, заполнить шаблон

            for (rez->First(); !rez->Eof; rez->Next())
            {
                //считать данные
                std::string part_no =   (rez->FieldByName("part_no")->Value.operator AnsiString()).c_str();
                std::string list_no =   (rez->FieldByName("list_no")->Value.operator AnsiString()).c_str();
                std::string zakaz =     (rez->FieldByName("zakaz")->Value.operator AnsiString()).c_str();
                std::string det_name =  (rez->FieldByName("det_name")->Value.operator AnsiString()).c_str();
                std::string det_code =  VinToGost(rez->FieldByName("det_code")->Value.operator AnsiString()).c_str();
                std::string kol =       (rez->FieldByName("kol")->Value.operator AnsiString()).c_str();

                new_page = new_page + (cur_row + row_size > end_row);//проанализировать количестко оставшихся строк

                if (new_page)
                {
                    if (cur_lists)
                    {
                        if (use_listing && !path.empty())
                        {//проверяем количество страниц, если выставлена опция
                            TrimFile(xl,path,"",cur_lists,lists_by_file,teml_file);
                        }
                    }
                    new_page = false;
                    //создать страницу
                    xl.Sheet_Copy(xl.GetSheet(cur_lists+template_page), xl.GetSheet(cur_lists+1), Variant().NoParam());
                    cur_lists++ ;
                    xl.SetActiveSheet(xl.GetSheet(cur_lists));
                    std::stringstream buf;
                    buf<<cur_lists;
                    xl.Set_Sheet_Name(xl.GetSheet(cur_lists),("Ярлыки лист-"+buf.str()).c_str());

                    cur_row = start_row;
                }
                //добавить строку если нужно
                size_t column_ofset = 0;
                if (add_row)
                {
                    //вставить строку в отчет
                    // копирование
                    xl.Range_Copy(xl.GetRows(xl.GetSheet(cur_lists+template_page), template_row, template_row + row_size - 1));
                    // вставка
                    xl.Sheet_activate();
                    xl.Range_Paste(xl.GetRows(cur_row, cur_row + row_size));
                }
                else
                {
                    column_ofset = 8;
                }

                xl.toCells(cur_row+4,     column_ofset+4,  zakaz.c_str()    );
                xl.toCells(cur_row+4,     column_ofset+6,  part_no.c_str()  );
                xl.toCells(cur_row+4,     column_ofset+8,  list_no.c_str()  );
                xl.toCells(cur_row+6,     column_ofset+2,  det_name.c_str() );
                xl.toCells(cur_row+8,     column_ofset+4,  kol.c_str()      );
                xl.toCells(cur_row+10,    column_ofset+3,  det_code.c_str() );

                add_row = !add_row;
                if (add_row)
                {
                    cur_row += row_size;
                }
            }

            if (!path.empty())//закрываем Excel в зависимости от опции сохранения в файл
            {
                SaveFile(xl,path + "(" + zakaz + " - " + part_no + ")" ,"",cur_lists);
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

}

}
