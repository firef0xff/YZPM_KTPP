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
    params["Производственный признак"];
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
    pp = params["Производственный признак"];
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
                       "IFNULL(`a`.`kol_det`,0) as kol_det "

                       "from `manufacture`.`marsh_lists` a "
                       "join `manufacture`.`det_names` b on `b`.`det_id` = `a`.`det_id` "

                       "where `a`.`part_id` = '" << part_id << "' "
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
                       ") engine = MYISAM "
                       "as "
                       "select "
                       "`a`.`det_id` as det_id, "
                       "`b`.`obmid` as obm_id, "
                       "`b`.`ei` as ei, "
                       "`b`.`nrm` * `a`.`kol_det` as norm "
                       "from `manufacture`.`step_1` a "
                       "join `manufacture`.`det_info` b on `a`.`det_id` = `b`.`det_id`";


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
            "CONVERT(`b`.`obd`, CHAR)                                   as obd, "
            "CONVERT(`a`.`ei`, CHAR)                                    as ei_kode, "
            "CONVERT(round(sum(`a`.`norm`),3), CHAR)                    as norm, "
            "CONVERT(IFNULL(concat(`c`.`nama`,' ',`c`.`goma`),IFNULL(`b`.`name`,'')), CHAR)    as nama, "
            "CONVERT(IFNULL(concat(`c`.`prma`,' ',`c`.`gopr`),''), CHAR)               as prma, "
            "CONVERT(IFNULL(`d`.`snameei`,''), CHAR)                    as ei_name "
            "from `manufacture`.`step_2` a "
            "join `manufacture`.`det_names` b on `b`.`det_id` = `a`.`obm_id` "
            "left join `manufacture`.`materials` c on `c`.`obmid` = `a`.`obm_id` "
            "left join `catalogs`.`dimensionality` d on `d`.`kodei` = `a`.`ei` "
            "where b.obd != '000000000000000'";

    if (!pp.empty())
        sql <<  "where b.pp = '"<<pp<<"' ";
    sql <<  "GROUP BY `b`.`id`,`a`.`ei` order by `b`.`obd`";
}

    DB->SendCommand(drop_step_1.c_str());
    DB->SendCommand(create_step_1.str().c_str());
    DB->SendCommand(drop_step_2.c_str());
    DB->SendCommand(create_step_2.str().c_str());
    DB->SendCommand(insert_step_2.str().c_str());

    TADOQuery *rez = DB->SendSQL(sql.str().c_str());

    DB->SendCommand(drop_step_1.c_str());
    DB->SendCommand(drop_step_2.c_str());

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
            size_t start_row = 5, end_row = 35, row_size = 1,
                    template_row = 5;
            size_t template_page = 15;
            size_t max_page_no=0;

            size_t file_no = 0;

            std::string pp_name;
            if (!pp.empty())
            {
                TADOQuery *rez2 = DB->SendSQL(("select `a`.`napp` as pp_name from `catalogs`.`proizv_prizn` a where `a`.`pp` = '"+pp+"'").c_str() );
                if (rez2)
                {
                    if (rez2->RecordCount)
                    {
                        pp_name = (rez2->FieldByName("pp_name")->Value.operator AnsiString()).c_str();
                    }
                    delete rez2;
                }
            }
            //подсчет строк
            size_t need_rows(0);

            DataList data;
            for (rez->First(); !rez->Eof; rez->Next())
            {
                ReportData tmp;

                tmp.obd     = VinToGost(rez->FieldByName("obd")->Value.operator AnsiString()).c_str();
                tmp.ei_kode = (rez->FieldByName("ei_kode")->Value.operator AnsiString()).c_str();
                tmp.ei_name = (rez->FieldByName("ei_name")->Value.operator AnsiString()).c_str();
                tmp.norm    = (rez->FieldByName("norm")->Value.operator AnsiString()).c_str();
                tmp.nama    = (rez->FieldByName("nama")->Value.operator AnsiString()).c_str();
                tmp.prma    = (rez->FieldByName("prma")->Value.operator AnsiString()).c_str();

                ++need_rows;
                data.push_back(tmp);
            }
            std::stringstream sql1;
            sql1 << "select "
                    "CONVERT(IFNULL(a.kol,''), CHAR) kol, "
                    "b.obd, "
                    "b.name "
                    "from `manufacture`.`part_content` a "
                    "join `manufacture`.`det_names` b on a.det_id = b.det_id "
                    "where a.part_id = '"<<part_id<<"'";
            TADOQuery *rez3 = DB->SendSQL(sql1.str().c_str());
            HeadList heads;
            if (rez3)
            {
                for (rez3->First(); !rez3->Eof; rez3->Next())
                {
                    ReportHead tmp;
                    tmp.obd    = VinToGost(rez3->FieldByName("obd")->Value.operator AnsiString()).c_str();
                    tmp.name    = (rez3->FieldByName("name")->Value.operator AnsiString()).c_str();
                    tmp.kol    = (rez3->FieldByName("kol")->Value.operator AnsiString()).c_str();

                    ++need_rows;
                    heads.push_back(tmp);
                }
                delete rez3;
            }

            //пробежаться по списку структур, заполнить шаблон
            max_page_no = need_rows/(end_row-start_row);
            if (need_rows%(end_row-start_row))
            {
                ++max_page_no;
            }

            size_t pp_no(0);
            size_t page_no(0);
            bool first = true;
            for (DataList::const_iterator it = data.begin(), end = data.end() ; it!=end; ++it)
            {
                ++pp_no;
                const ReportData &lnk = *it;

                size_t cur_row_size = 1;
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
                    page_no++;
                    xl.SetActiveSheet(xl.GetSheet(cur_lists));
                    std::stringstream buf;
                    buf<<page_no;
                    xl.Set_Sheet_Name(xl.GetSheet(cur_lists),("ЕЗ-"+buf.str()).c_str());

                    // почистить лист
                    // копирование
                    xl.Range_Copy(xl.GetRows(xl.GetSheet(cur_lists+template_page), 15, 24));
                    // вставка
                    xl.Sheet_activate();
                    xl.Range_Paste(xl.GetRows(5, 14));

                    //заполнить шапку

                    xl.toCells(1,   4,  pp_name.c_str() );
                    xl.toCells(1,   8,  page_no         );
                    xl.toCells(1,   10, max_page_no     );
                    xl.toCells(2,   6,  zakaz.c_str()   );
                    xl.toCells(2,   8,  part_no.c_str() );


                    size_t ofset(0);
                    if (first)
                    {
                        for (HeadList::const_iterator it = heads.begin(), end = heads.end(); it!=end; ++it)
                        {
                            const ReportHead &lnk1 = *it;
                            //вставить строку в отчет
                            // копирование
                            xl.Range_Copy(xl.GetRows(xl.GetSheet(cur_lists+template_page), 3, 3));
                            // вставка
                            xl.Sheet_activate();
                            xl.Range_Paste(xl.GetRows(3 + ofset, 3 + ofset));

                            xl.toCells(3 + ofset,     3,  lnk1.obd.c_str()    );
                            xl.toCells(3 + ofset,     4,  lnk1.name.c_str()   );
                            xl.toCells(3 + ofset,     7,  lnk1.kol.c_str()    );
                        }
                    }

                    //вставить строку в отчет
                    // копирование
                    xl.Range_Copy(xl.GetRows(xl.GetSheet(cur_lists+template_page), 4, 4));
                    // вставка
                    xl.Sheet_activate();
                    xl.Range_Paste(xl.GetRows(start_row + ofset - 1, start_row + ofset - 1));

                    cur_row = start_row + ofset;
                    first = false;
                }

                //вставить строку в отчет
                // копирование
                xl.Range_Copy(xl.GetRows(xl.GetSheet(cur_lists+template_page), template_row, template_row + row_size - 1));
                // вставка
                xl.Sheet_activate();
                xl.Range_Paste(xl.GetRows(cur_row, cur_row + row_size-1));

                xl.toCells(cur_row,     2,  lnk.obd.c_str()     );
                xl.toCells(cur_row,     3,  lnk.prma.c_str()    );
                xl.toCells(cur_row,     4,  lnk.nama.c_str()    );

                xl.toCells(cur_row,     6,  lnk.norm.c_str()    );
                xl.toCells(cur_row,     7,  lnk.ei_name.c_str() );

                ++cur_row;
            }
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
