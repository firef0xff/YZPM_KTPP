#include <reports/exsemplars/y09102.h>
#include <xl_operations.h>
#include "functions.h"

namespace rep
{

Y09102::Y09102 (int set): rep::Report("Загрузка оборудования по сводным группам",set),
    DB(0),path(""),use_listing(false),lists_by_file(0),object(""),element(""),type(""),template_path(""),
    cur_lists(0),templ("Y09102.xlt")
{
    params[REPORT_PATH];
    params[REPORT_LIST_COUNT] = "10";
    params[REPORT_USE_LISTING] = REP_TRUE;
}
Y09102::~Y09102()
{}

Y09102::Y09102(const Y09102 &r):rep::Report(r),
    DB(0),path(""),use_listing(false),lists_by_file(0),object(""),element(""),type(""),template_path(""),
    cur_lists(0),templ("Y09102.xlt")
{

}

void Y09102::Build(void)
{
    cur_lists = 0;
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
    //этап 1 получить список деталей с количеством
    std::string drop_step_1 = "drop temporary table if exists `manufacture`.`step_1`";
//    std::string drop_step_2 = "drop temporary table if exists `manufacture`.`step_2`";

    std::stringstream create_step_1;
//    std::stringstream create_step_2;
    //step1
{
    create_step_1   <<  "create temporary table if not exists `manufacture`.`step_1` as "
                        "select "
                        "a1.zakaz, "
                        "a.part_no, "
                        "`b`.`det_id` as det_id, "
                        "sum(IFNULL(`c`.`kol_using`,`d`.`kol`)) as kol "
                        "from `manufacture`.`parts` a "
                        "join `manufacture`.`zakaz_list` a1      on `a1`.`zak_id` = `a`.`zak_id` "
                        "join `manufacture`.`marsh_lists` b      on `b`.`part_id` = `a`.`part_id` "
                        "left join `manufacture`.`det_tree` c 		on `c`.`det_idc` = `b`.`det_id` "
                        "left join `manufacture`.`part_content` d on `d`.`det_id` = `b`.`det_id` ";

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

    create_step_1 << "group by `b`.`det_id`";
}
    //этап 2 получить нормы для деталей с оборудованием
    std::stringstream sql;
    sql << "select "
           "g1.npodr as cex_name, "
           "g2.npodr as utch_name, "
           "c.cex, "
           "c.utch, "
           "f.name as obo_group, "
           "a.zakaz as zakaz_no, "
           "a.part_no as part_no, "
           "c.oboID, "
           "ROUND(sum(IFNULL(`d`.`tsht`*`d`.`ksht`*`d`.`krop`/`d`.`kolod`*a.kol,0)),3) as tsht, "
           "e.ksme "
           "from `manufacture`.`step_1` a "
           "join `manufacture`.`operation_list` c   on `c`.`det_id` = `a`.`det_id` "
           "join `manufacture`.`operation_norms` d  on `d`.`OpUUID` = `c`.`OpUUID` "
           "left join `equipment`.`obor_list` e     on `e`.`oboID` = `c`.`oboID` "
           "left join `equipment`.`obor_groups` e1  on `e1`.`oboID` = `e`.`oboID` "
           "left join `equipment`.`groups` f        on `f`.`group_id` = `e1`.`group_id` "
           "left join `catalogs`.`podr_list` g1     on `g1`.`cex` = `c`.`cex` and `g1`.`utch` = '' "
           "left join `catalogs`.`podr_list` g2     on `g2`.`cex` = `c`.`cex` and `g2`.`utch` = `c`.`utch` "
           "group by c.cex,c.utch,f.name, c.oboID, a.zakaz, a.part_no";

}

}
