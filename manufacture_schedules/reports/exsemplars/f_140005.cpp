#include <reports/exsemplars/f_140005.h>
#include <xl_operations.h>

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
            for (rez->First(); !rez->Eof; rez->Next())
            {
                std::string part_id =   (rez->FieldByName("part_id")->Value.operator AnsiString()).c_str();
                std::string zakaz =     (rez->FieldByName("zakaz")->Value.operator AnsiString()).c_str();
                std::string part_no =   (rez->FieldByName("part_no")->Value.operator AnsiString()).c_str();
                BuildData(part_id,zakaz,part_no);
            }
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
    cur_lists = 0;
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
                       "`b`.`sp_id` as sp_id, "
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
            "trim(`a`.`pm`) as pm, "
			"CONVERT(`a`.`ost`, CHAR) as ost, "
            "`a`.`prizn`, "
            "`a`.`nama`, "
            "`a`.`prma`, "
			"CONVERT(`b`.`tpz`, DECIMAL(40,6)) as tpz, "
			"CONVERT(`b`.`tsht`, DECIMAL(40,6)) as tsht, "
			"CONVERT(`b`.`tpz` * `a`.`kol`, DECIMAL(40,6)) as tpz_part, "
            "CONVERT(`b`.`tsht`* `a`.`kol`, DECIMAL(40,6)) as tsht_part, "
            "CONVERT (`c`.`order_no`, CHAR) as  order_no "
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
            std::string file_name = path + "(" + zakaz + " - " + part_no + ")";

            OpenTemplate(xl, teml_file);

            bool new_page = true;
            size_t cur_row = 0;
            size_t start_row = 4, end_row = 53, row_size = 2,
                    template_row = 5,
                    template_empty_row = 8,
                    template_final_row = 10,
                    template_summary_row = 12;
            size_t template_page = 3;
			size_t max_page_no=0;

            size_t file_no = 0;

            //подсчет строк
            int last_prizn(-1);
            size_t need_rows(0);

            DataList data;
            for (rez->First(); !rez->Eof; rez->Next())
            {
                ReportData tmp;
                tmp.ml_no = (rez->FieldByName("ml_no")->Value.operator AnsiString()).c_str();
                tmp.obd   = VinToGost(rez->FieldByName("obd")->Value.operator AnsiString()).c_str();
                tmp.name  = (rez->FieldByName("name")->Value.operator AnsiString()).c_str();
                tmp.kol   = (rez->FieldByName("kol")->Value.operator AnsiString()).c_str();
                tmp.ost   = (rez->FieldByName("ost")->Value.operator AnsiString()).c_str();
                tmp.prizn = rez->FieldByName("prizn")->Value.operator int();
                tmp.nama  = (rez->FieldByName("nama")->Value.operator AnsiString()).c_str();
                tmp.prma  = (rez->FieldByName("prma")->Value.operator AnsiString()).c_str();
                tmp.tpz         = rez->FieldByName("tpz")->Value.operator double();
                tmp.tsht        = rez->FieldByName("tsht")->Value.operator double();
                tmp.tpz_part    = rez->FieldByName("tpz_part")->Value.operator double();
                tmp.tsht_part   = rez->FieldByName("tsht_part")->Value.operator double();
                tmp.order_no    = (rez->FieldByName("order_no")->Value.operator AnsiString()).c_str();
                tmp.SetPm((rez->FieldByName("pm")->Value.operator AnsiString()).c_str());

                //считать все данные в структуры спрогнозировать разметку

                //правила построения
                //при смене признака вставляется доп строчка
                //группировать по вхождениям детали пока не буду, но возможно потребуется в будущем
                need_rows += tmp.Rows();
                if (last_prizn != tmp.prizn)
                {
                    need_rows += 1;
                    last_prizn = tmp.prizn;
                }
                data.push_back(tmp);
            }
            //пробежаться по списку структур, заполнить шаблон
            max_page_no = need_rows/(end_row-start_row);
            if (need_rows%(end_row-start_row))
            {
                ++max_page_no;
            }

            size_t pp_no(0);
            double tsht_summary(0);
            for (DataList::const_iterator it = data.begin(), end = data.end() ; it!=end; ++it)
            {

                ++pp_no;
                const ReportData &lnk = *it;

                size_t cur_row_size = lnk.Rows() + (last_prizn != lnk.prizn ? 2 : 0);
                new_page = new_page + (cur_row + cur_row_size > end_row);//проанализировать количестко оставшихся строк

                if (new_page)
                {
                    if (cur_lists)
                    {
                        if (use_listing && !path.empty())
                        {//проверяем количество страниц, если выставлена опция
                            TrimFile(xl,file_name,"",cur_lists,lists_by_file,teml_file,file_no);
                        }
                    }
                    new_page = false;
                    //создать страницу
                    xl.Sheet_Copy(xl.GetSheet(cur_lists+template_page), xl.GetSheet(cur_lists+1), Variant().NoParam());
                    cur_lists++ ;
                    xl.SetActiveSheet(xl.GetSheet(cur_lists));
                    std::stringstream buf;
                    buf<<cur_lists;
                    xl.Set_Sheet_Name(xl.GetSheet(cur_lists),("Ф140005-"+buf.str()).c_str());

                    // почистить лист
                    // копирование
                    xl.Range_Copy(xl.GetRows(xl.GetSheet(cur_lists+template_page), 14, 23));
                    // вставка
                    xl.Sheet_activate();
                    xl.Range_Paste(xl.GetRows(4, 13));

                    //заполнить шапку

                    xl.toCells(1,   3,   Now().FormatString("dd.mm.yyyy")           );
                    xl.toCells(1,   10,  (ceh+utch).c_str()                         );
                    xl.toCells(1,   12,  (std::string("Заказ ") + zakaz).c_str()    );
                    xl.toCells(1,   13,  (std::string("Партия ") + part_no).c_str() );
                    xl.toCells(1,   17,  cur_lists                                  );
                    xl.toCells(1,   20,  max_page_no                                );

                    cur_row = start_row;
                }

                if (last_prizn != lnk.prizn)
                {
                    //вставка пустой строки
                    // копирование
                    xl.Range_Copy(xl.GetRows(xl.GetSheet(cur_lists+template_page), template_empty_row, template_empty_row));
                    // вставка
                    xl.Sheet_activate();
                    xl.Range_Paste(xl.GetRows(cur_row, cur_row));

                    // копирование
                    xl.Range_Copy(xl.GetRows(xl.GetSheet(cur_lists+template_page), template_empty_row, template_empty_row));
                    // вставка
                    xl.Sheet_activate();
                    xl.Range_Paste(xl.GetRows(cur_row+1, cur_row+1));

                    //напишем в этой строке что-то
                    switch(lnk.prizn)
                    {
                    case 1:
                        {
                            xl.toCells(cur_row+1, 1, "Детати кот. сборок и кот. сборки");
                            break;
                        }
                    case 2:
                        {
                            xl.toCells(cur_row+1, 1, "Оригинальные, заим., обезлич. детали");
                            break;
                        }
                    default:
                        break;
                    }

                    cur_row += 2;
                    last_prizn = lnk.prizn;
                }

                //вставить строку в отчет
                // копирование
                xl.Range_Copy(xl.GetRows(xl.GetSheet(cur_lists+template_page), template_row, template_row + row_size - 1));
                // вставка
                xl.Sheet_activate();
                xl.Range_Paste(xl.GetRows(cur_row, cur_row + row_size));

                for (size_t i = 0; i < lnk.Rows() - row_size; ++i)
                {
                    // копирование
                    xl.Range_Copy(xl.GetRows(xl.GetSheet(cur_lists+template_page), template_row+1, template_row +1));
                    // вставка
                    xl.Sheet_activate();
                    xl.Range_Paste(xl.GetRows(cur_row + row_size + i, cur_row + row_size + i));
                }

                // копирование
                xl.Range_Copy(xl.GetRows(xl.GetSheet(cur_lists+template_page), template_final_row, template_final_row));
                // вставка
                xl.Sheet_activate();
                xl.Range_Paste(xl.GetRows(cur_row + lnk.Rows(), cur_row + lnk.Rows()));

                xl.toCells(cur_row,     1,  pp_no               );
                xl.toCells(cur_row,     2,  lnk.obd.c_str()     );
                xl.toCells(cur_row+1,   2,  lnk.name.c_str()    );
                xl.toCells(cur_row,     6,  lnk.kol.c_str()     );
                xl.toCells(cur_row,     7,  lnk.nama.c_str()    );
                xl.toCells(cur_row+1,   7,  lnk.prma.c_str()    );
                xl.toCells(cur_row,     8,  lnk.tsht            );
                xl.toCells(cur_row+1,   8,  lnk.tsht_part       );
                tsht_summary += lnk.tsht_part;
                xl.toCells(cur_row,     9,  lnk.ml_no.c_str()   );
                xl.toCells(cur_row+1,   9,  lnk.order_no.c_str());
                xl.toCells(cur_row,     14, lnk.ost.c_str()     );

                size_t ofset(0);
                for (std::list<std::string>::const_iterator it2 = lnk.pm.begin(); it2!=lnk.pm.end(); ++it2)
                {
                    xl.toCells(cur_row+ofset,   11, it2->c_str() );
                    ++ofset;
                }

                cur_row += lnk.Rows();
            }

            // копирование
            xl.Range_Copy(xl.GetRows(xl.GetSheet(cur_lists+template_page), template_summary_row, template_summary_row));
            // вставка
            xl.Sheet_activate();
            xl.Range_Paste(xl.GetRows(cur_row+1, cur_row+1));

            xl.toCells(cur_row+1,   8, tsht_summary );

            if (!path.empty())//закрываем Excel в зависимости от опции сохранения в файл
            {
                SaveFile(xl,file_name ,"",cur_lists,file_no);
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
