#include <reports/exsemplars/materaials_detail.h>
#include <xl_operations.h>

namespace rep
{

MaterialsDetail::MaterialsDetail (int set): rep::Report("Материальная ведомость: Подетальная",set),
    DB(0),path(""),use_listing(false),lists_by_file(0),object(""),element(""),type(""),template_path(""),
    cur_lists(0),templ("manufacture_materials.xlt")
{
    params[REPORT_PATH];
    params[REPORT_LIST_COUNT] = "10";
    params[REPORT_USE_LISTING] = REP_TRUE;
    params["Производственный признак"];
    params["Исключить материал спецификации"]=REP_TRUE;
}
MaterialsDetail::~MaterialsDetail()
{}

MaterialsDetail::MaterialsDetail(const MaterialsDetail &r):rep::Report(r),
    DB(0),path(""),use_listing(false),lists_by_file(0),object(""),element(""),type(""),template_path(""),
    cur_lists(0),templ("manufacture_materials.xlt")
{

}

void MaterialsDetail::Build(void)
{
    cur_lists = 0;
    ParseParams();
    LoadSettings();
    BuildReport();
}
boost::shared_ptr<rep::Report> MaterialsDetail::SelfCopy (void) const
{
    return boost::shared_ptr<rep::Report>(new MaterialsDetail(*this));
}

void MaterialsDetail::ParseParams(void)
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
    disable_sp = params["Исключить материал спецификации"]!=REP_NULL&&params["Исключить материал спецификации"]!=REP_FALSE;
}
void MaterialsDetail::LoadSettings()
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
void MaterialsDetail::BuildReport()
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
void MaterialsDetail::BuildData      (std::string part_id, std::string zakaz, std::string part_no)
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
            "CONVERT(`a1`.`obd`, CHAR)                                  as obd, "
            "CONVERT(`a1`.`name`, CHAR)                                 as name, "
            "CONVERT(sum(`a1`.`kol_det`), char)                         as kol_det, "
            "CONVERT(`b`.`obd`, CHAR)                                   as obm, "
            "CONVERT(round(sum(`a`.`norm`),3), decimal(40,6))           as norm, "
            "CONVERT(trim(concat(IFNULL(`c`.`nama`,IFNULL(`b`.`name`,'')),' ', IFNULL(`c`.`prma`,''))), CHAR) as material, "
            "CONVERT(`a`.`ei`, CHAR)                                    as ei_kode, "
            "CONVERT(IFNULL(`d`.`snameei`,''), CHAR)                    as ei_name, "

            "CONVERT(IFNULL(`e`.`vz`,''), CHAR)                         as vz, "
            "CONVERT(IFNULL(`e`.`razz`,''), CHAR)                       as razz, "
            "CONVERT(IFNULL(`e`.`masz`,''), CHAR)                       as masz, "
            "CONVERT(IFNULL(`e`.`masz`,''), CHAR)                       as masd, "
            "CONVERT(IFNULL(ceil(sum(`a1`.`kol_det`/`e`.`kdz`)),''), CHAR)         as kol_zag, "
            "CONVERT(IFNULL(`e`.`kdz`,''), CHAR)                        as kdz, "

            "CONVERT(IFNULL(round(sum(`e`.`masd`)/sum(`a`.`norm`),3),''), CHAR) as kim "

            "from `manufacture`.`step_2` a "
            "join `manufacture`.`step_1` a1 on `a`.`det_id` = `a1`.`det_id` "
            "join `manufacture`.`det_names` b on `b`.`det_id` = `a`.`obm_id` "
            "left join `manufacture`.`materials` c on `c`.`obmid` = `a`.`obm_id` "
            "left join `catalogs`.`dimensionality` d on `d`.`kodei` = `a`.`ei` "
            "left join `manufacture`.`det_info` e on `e`.`det_id`=`a`.`det_id` and `e`.`obmid` = `a`.`obm_id` ";
    if (!pp.empty())
        sql <<  "where b.pp = '"<<pp<<"' ";
    sql <<  "group by `b`.`id`,`a`.`ei`, `a1`.`obd` order by `b`.`obd`,`a`.`ei`,`a1`.`obd` ";
}

    DB->SendCommand(drop_step_1.c_str());
    DB->SendCommand(create_step_1.str().c_str());
    DB->SendCommand(drop_step_2.c_str());
    DB->SendCommand(create_step_2.str().c_str());
    if (!disable_sp)
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
            size_t start_row = 4, end_row = 53, row_size = 1,
                    template_row = 6,
                    template_group_start_row = 5,
                    template_group_end_row = 7;
            size_t template_page = 2;
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
            std::string obm_old,ei_old;
            for (rez->First(); !rez->Eof; rez->Next())
            {
                ReportData tmp;

                tmp.obd     = VinToGost(rez->FieldByName("obd")->Value.operator AnsiString()).c_str();
                tmp.name    = (rez->FieldByName("name")->Value.operator AnsiString()).c_str();
                tmp.kol_det = (rez->FieldByName("kol_det")->Value.operator AnsiString()).c_str();

                tmp.obm      = VinToGost(rez->FieldByName("obm")->Value.operator AnsiString()).c_str();
                tmp.norm     = rez->FieldByName("norm")->Value.operator double();
                tmp.material = (rez->FieldByName("material")->Value.operator AnsiString()).c_str();

                tmp.ei_name = (rez->FieldByName("ei_name")->Value.operator AnsiString()).c_str();
                tmp.vz      = (rez->FieldByName("vz")->Value.operator AnsiString()).c_str();
                tmp.razz    = (rez->FieldByName("razz")->Value.operator AnsiString()).c_str();
                tmp.masz    = (rez->FieldByName("masz")->Value.operator AnsiString()).c_str();
                tmp.masz    = (rez->FieldByName("masd")->Value.operator AnsiString()).c_str();

                tmp.kol_zag = (rez->FieldByName("kol_zag")->Value.operator AnsiString()).c_str();
                tmp.kdz     = (rez->FieldByName("kdz")->Value.operator AnsiString()).c_str();
                tmp.kim     = (rez->FieldByName("kim")->Value.operator AnsiString()).c_str();

                ++need_rows;
                if (obm_old!=tmp.obd)
                {
                    ++need_rows;
                    obm_old=tmp.obd;
                    ei_old = "";
                }
                else if (ei_old != tmp.ei_name)
                {
                    ++need_rows;
                    ei_old = tmp.ei_name;
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
            std::map<const std::string, double> summary;
            std::string last_obm = "";
            for (DataList::const_iterator it = data.begin(), end = data.end() ; it!=end; ++it)
            {
                ++pp_no;
                const ReportData &lnk = *it;

                size_t cur_row_size = last_obm==lnk.obm?1:2+summary.size();
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
                    xl.Set_Sheet_Name(xl.GetSheet(cur_lists),("ЕЗ-"+buf.str()).c_str());

                    // почистить лист
                    // копирование
                    xl.Range_Copy(xl.GetRows(xl.GetSheet(cur_lists+template_page), 14, 18));
                    // вставка
                    xl.Sheet_activate();
                    xl.Range_Paste(xl.GetRows(4, 8));

                    //заполнить шапку
                    buf.str("");
                    buf<<cur_lists<<"/"<<max_page_no;
                    xl.toCells(1,   5,  pp_name.c_str()  );
                    xl.toCells(1,   10, buf.str().c_str());
                    xl.toCells(1,   4,  zakaz.c_str()    );
                    xl.toCells(1,   8,  part_no.c_str()  );

                    cur_row = start_row;
                }

                if (last_obm != lnk.obm)
                {
                    //подвести итог
                    if (!last_obm.empty())
                    {
                        for (std::map<const std::string, double>::const_iterator it = summary.begin(); it!=summary.end(); ++it )
                        {
                            //вставить строку в отчет
                            // копирование
                            xl.Range_Copy(xl.GetRows(xl.GetSheet(cur_lists+template_page), template_group_end_row, template_group_end_row));
                            // вставка
                            xl.Sheet_activate();
                            xl.Range_Paste(xl.GetRows(cur_row, cur_row + row_size-1));

                            xl.toCells(cur_row,     9,  it->second          );
                            xl.toCells(cur_row,     10, it->first.c_str()   );

                            ++cur_row;
                        }
                    }

                    summary.clear();

                    //начать новый раздел
                    //вставить строку в отчет
                    // копирование
                    xl.Range_Copy(xl.GetRows(xl.GetSheet(cur_lists+template_page), template_group_start_row, template_group_start_row));
                    // вставка
                    xl.Sheet_activate();
                    xl.Range_Paste(xl.GetRows(cur_row, cur_row + row_size-1));

                    xl.toCells(cur_row,     1,  lnk.obm.c_str()     );
                    xl.toCells(cur_row,     2,  lnk.material.c_str());

                    last_obm = lnk.obm;
                    ++cur_row;
                }

                //вставить строку в отчет
                // копирование
                xl.Range_Copy(xl.GetRows(xl.GetSheet(cur_lists+template_page), template_row, template_row + row_size - 1));
                // вставка
                xl.Sheet_activate();
                xl.Range_Paste(xl.GetRows(cur_row, cur_row + row_size-1));

                xl.toCells(cur_row,     1,  lnk.obd.c_str()     );
                xl.toCells(cur_row,     2,  lnk.name.c_str()    );
                xl.toCells(cur_row,     3,  lnk.kol_det.c_str() );
                xl.toCells(cur_row,     4,  lnk.masd.c_str()    );

                xl.toCells(cur_row,     5,  lnk.vz.c_str()      );
                xl.toCells(cur_row,     6,  lnk.razz.c_str()    );
                xl.toCells(cur_row,     7,  lnk.kol_zag.c_str() );
                xl.toCells(cur_row,     8,  lnk.masz.c_str()    );

                xl.toCells(cur_row,     9,  lnk.norm            );
                xl.toCells(cur_row,     10, lnk.ei_name.c_str() );
                xl.toCells(cur_row,     11, lnk.kim.c_str()     );

                summary[lnk.ei_name]+=lnk.norm;

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
