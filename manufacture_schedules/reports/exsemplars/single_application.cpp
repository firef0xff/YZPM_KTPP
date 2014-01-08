#include <reports/exsemplars/single_application.h>
#include <xl_operations.h>

namespace rep
{

SingleApplication::SingleApplication (int set): rep::Report("Материальная ведомость: Единичная заявка",set),
    DB(0),path(""),use_listing(false),lists_by_file(0),object(""),element(""),type(""),template_path(""),
    cur_lists(0),templ("manufacture_forms.xlt")
{
    params[REPORT_PATH];
    params[REPORT_LIST_COUNT] = "10";
    params[REPORT_USE_LISTING] = REP_TRUE;
}
SingleApplication::~SingleApplication()
{}

SingleApplication::SingleApplication(const SingleApplication &r):rep::Report(r),
    DB(0),path(""),use_listing(false),lists_by_file(0),object(""),element(""),type(""),template_path(""),
    cur_lists(0),templ("manufacture_forms.xlt")
{

}

void SingleApplication::Build(void)
{
    cur_lists = 0;
    ParseParams();
    LoadSettings();
    BuildReport();
}
boost::shared_ptr<rep::Report> SingleApplication::SelfCopy (void) const
{
    return boost::shared_ptr<rep::Report>(new SingleApplication(*this));
}

void SingleApplication::ParseParams(void)
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
}
void SingleApplication::LoadSettings()
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
void SingleApplication::BuildReport()
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
void SingleApplication::BuildData      (std::string part_id, std::string zakaz, std::string part_no)
{
    cur_lists = 0;
    std::string drop_step_1 = "drop temporary table if exists `manufacture`.`step_1`";
    std::string drop_step_2 = "drop temporary table if exists `manufacture`.`step_2`";


    std::stringstream create_step_1;
    std::stringstream create_step_2;
    std::stringstream insert_step_2;
    std::stringstream sql;
{
    create_step_1   << "create temporary table if not exists `manufacture`.`step_1` as "
                       "select "
                       "`b`.`id`as id, "
                       "`a`.`det_id`as det_id, "
                       "`b`.`sp_id` as sp_id, "

                       "`b`.`obd`   as obd, "
                       "`b`.`name`  as name, "
                       "sum(IFNULL(`c`.`kol_using`,`d`.`kol`)) as kol_det "

                       "from `manufacture`.`marsh_lists` a "
                       "join `manufacture`.`det_names` b on `b`.`det_id` = `a`.`det_id` "
                       "left join `manufacture`.`det_tree` c on `c`.`det_idc` = `a`.`det_id` "
                       "left join `manufacture`.`part_content` d on `d`.`det_id` = `a`.`det_id` "

                       "where `a`.`part_id` = ' << part_id << ' "
                       "group by `a`.`det_id` ";

    //получить нормы для деталей
    create_step_2   << "create temporary table if not exists `manufacture`.`step_2` "
                       "( "
                       "    det_id bigint(20) unsigned not null, "
                       "    obm_id  bigint(20) unsigned, "
                       "    ei  char(3), "
                       "    norm double, "
                       "    key `det_id`(`det_id`), "
                       "    key `obm_id`(`obm_id`), "
                       "    key `ei`(`ei`) "
                       ") engine = myiasm "
                       "as "
                       "select "
                       "`a`.`det_id`, "
                       "`b`.`obmid`, "
                       "`b`.`ei`, "
                       "`b`.`nrm` * `a`.`kol_det` as norm "
                       "from `manufacture`.`step_1` a "
                       "join `manufacture`.`det_info` b ";


    insert_step_2 <<    "insert into `manufacture`.`step_2` (`det_id`,`obm_id`,`ei`,`norm`) "
                        "select "
                        "`b`.`det_idp`   as det_id, "
                        "`b`.`det_idc`   as obm_id, "
                        "`b`.`ei`        as ei, "
                        "`b`.`kol_using`  as norm "
                        "from `manufacture`.`step_1` a "
                        "join `manufacture`.`det_tree` b on `a`.`det_id` = `b`.`det_idp` "
                        "join `manufacture`.`det_names` c on `c`.`det_id` = `b`.`det_idc` "
                        "where `c`.`sp_id` in (5,6,7,9) ";



    sql <<  "select "
            "`b`.`obd` as obd, "
            "`a`.`ei` as ei_kode, "
            "round(sum(`a`.`norm`),3) as norm, "
            "IFNULL(`c`.`nama`,IFNULL(`b`.`name`,'')) as nama, "
            "IFNULL(`c`.`prma`,'') prma, "
            "IFNULL(`d`.`snameei`,'') ei_name "
            "from `manufacture`.`step_2` a "
            "join `manufacture`.`det_names` b on `b`.`det_id` = `a`.`obm_id` "
            "left join `manufacture`.`materials` c on `c`.`obmid` = `a`.`obm_id` "
            "left join `catalogs`.`dimensionality` d on `d`.`kodei` = `a`.`ei` ";

    if (!pp.empty())
        sql <<  "where b.pp = '05' ";
    sql <<  "GROUP BY `b`.`id`,`a`.`ei` ";
}

    DB->SendCommand(drop_step_1.c_str());
    DB->SendCommand(create_step_1.str().c_str());
    DB->SendCommand(drop_step_2.c_str());
    DB->SendCommand(create_step_2.str().c_str());

    if (!group_by_obd)
    {
        DB->SendCommand(drop_step_3.c_str());
        DB->SendCommand(insert_step_2.str().c_str());
        DB->SendCommand(drop_step_4.c_str());
        DB->SendCommand(create_step_4.str().c_str());
    }

    TADOQuery *rez = DB->SendSQL(sql.str().c_str());

    DB->SendCommand(drop_step_1.c_str());
    DB->SendCommand(drop_step_2.c_str());
    if (!group_by_obd)
    {
        DB->SendCommand(drop_step_3.c_str());
        DB->SendCommand(drop_step_4.c_str());
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
            std::string file_name = path + "(" + zakaz + " - " + part_no + ")";

            OpenTemplate(xl, teml_file);

            bool new_page = true;
            size_t cur_row = 0;
            size_t start_row = 4, end_row = 62, row_size = 2,
                    template_row = 5,
                    template_empty_row = 8,
                    template_final_row = 10,
                    template_summary_row = 12;
            size_t template_page = 1;
            size_t max_page_no=0;

            size_t file_no = 0;

            //подсчет строк
            int last_prizn(-1);
            size_t need_rows(0);

            DataList data;
            for (rez->First(); !rez->Eof; rez->Next())
            {
                ReportData tmp;

                tmp.obd     = VinToGost(rez->FieldByName("obd")->Value.operator AnsiString()).c_str();
                tmp.name    = (rez->FieldByName("name")->Value.operator AnsiString()).c_str();
                tmp.kol_det = (rez->FieldByName("kol_det")->Value.operator AnsiString()).c_str();
                tmp.kol_zag = (rez->FieldByName("kol_zag")->Value.operator AnsiString()).c_str();
                tmp.mass    = rez->FieldByName("mass")->Value.operator double();
                tmp.norm    = rez->FieldByName("norm")->Value.operator double();
                tmp.prizn   = rez->FieldByName("prizn")->Value.operator int();
                tmp.vz      = (rez->FieldByName("vz")->Value.operator AnsiString()).c_str();
                tmp.razz    = (rez->FieldByName("razz")->Value.operator AnsiString()).c_str();
                tmp.nama    = (rez->FieldByName("nama")->Value.operator AnsiString()).c_str();
                tmp.prma    = (rez->FieldByName("prma")->Value.operator AnsiString()).c_str();

                tmp.trud        = rez->FieldByName("trud")->Value.operator double();
                tmp.trud_part   = rez->FieldByName("trud_part")->Value.operator double();

                if (!group_by_obd)
                {
                    tmp.ml_no       = (rez->FieldByName("ml_no")->Value.operator AnsiString()).c_str();
                    tmp.order_no    = (rez->FieldByName("order_no")->Value.operator AnsiString()).c_str();
                }
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
            double trud_summary(0);
            double mass_summary(0);
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
                    xl.Set_Sheet_Name(xl.GetSheet(cur_lists),("Ф140003-"+buf.str()).c_str());

                    // почистить лист
                    // копирование
                    xl.Range_Copy(xl.GetRows(xl.GetSheet(cur_lists+template_page), 14, 23));
                    // вставка
                    xl.Sheet_activate();
                    xl.Range_Paste(xl.GetRows(4, 13));

                    //заполнить шапку

                    xl.toCells(1,   3,   Now().FormatString("dd.mm.yyyy")   );
                    xl.toCells(1,   9,  (ceh+utch).c_str()                  );
                    xl.toCells(1,   11,  zakaz.c_str()                      );
                    xl.toCells(1,   13,  part_no.c_str()                    );

                    buf.str("");
                    buf<<cur_lists<<"/"<<max_page_no;

                    xl.toCells(1,   16,  buf.str().c_str()                  );
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

                xl.toCells(cur_row,     1,  lnk.vz.c_str()      );
                xl.toCells(cur_row,     2,  lnk.obd.c_str()     );
                xl.toCells(cur_row+1,   2,  lnk.name.c_str()    );

                xl.toCells(cur_row,     5,  lnk.kol_zag.c_str() );
                xl.toCells(cur_row+1,   5,  lnk.kol_det.c_str() );

                xl.toCells(cur_row,     6,  lnk.razz.c_str()    );

                xl.toCells(cur_row,     7,  lnk.nama.c_str()    );
                xl.toCells(cur_row+1,   7,  lnk.prma.c_str()    );

                xl.toCells(cur_row,     8,  lnk.mass            );
                xl.toCells(cur_row+1,   8,  lnk.norm            );
                mass_summary += lnk.norm;

                xl.toCells(cur_row,     9,  lnk.trud            );
                xl.toCells(cur_row+1,   9,  lnk.trud_part       );
                trud_summary += lnk.trud_part;

                xl.toCells(cur_row,     10, lnk.ml_no.c_str()   );
                xl.toCells(cur_row+1,   10, lnk.order_no.c_str());

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

            xl.toCells(cur_row+1,   8, mass_summary );
            xl.toCells(cur_row+1,   9, trud_summary );

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
