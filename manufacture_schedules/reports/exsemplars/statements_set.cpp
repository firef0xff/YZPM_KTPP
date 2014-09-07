#include "statements_set.h"
#include <xl_operations.h>

namespace rep
{
StatementsSet::StatementsSet (int set): rep::Report("Набор ведомостей материалов",set),
    DB(0),path(""),use_listing(false),lists_by_file(0),object(""),element(""),type(""),template_path(""),
    cur_lists(0),templ("manufacture_forms.xlt"),
    build_all(false),build_cooperation(false),build_forging(false),build_litho(false),build_stamping(false)
{
    params[REPORT_PATH];
    params[REPORT_LIST_COUNT] = "10";
    params[REPORT_USE_LISTING] = REP_TRUE;
}
StatementsSet::~StatementsSet()
{}

StatementsSet::StatementsSet(const StatementsSet &r):rep::Report(r),
    DB(0),path(""),use_listing(false),lists_by_file(0),object(""),element(""),type(""),template_path(""),
    cur_lists(0),templ("manufacture_forms.xlt"),
    build_all(false),build_cooperation(false),build_forging(false),build_litho(false),build_stamping(false)
{

}

void StatementsSet::Build(void)
{
    cur_lists = 0;
    ParseParams();
    LoadSettings();
    BuildReport();
}
boost::shared_ptr<rep::Report> StatementsSet::SelfCopy (void) const
{
    return boost::shared_ptr<rep::Report>(new StatementsSet(*this));
}

void StatementsSet::ParseParams(void)
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
void StatementsSet::LoadSettings()
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
void StatementsSet::BuildReport()
{
    //получить список маршрутных листов по заданию
    std::stringstream sql;
    sql <<  "select `a`.`det_id`, `c`.`obd`, `c`.`name`,`d`.`zakaz`,`b`.`part_no`,`a`.`kol` "
                "from `manufacture`.`part_content` a "
                "join `manufacture`.`parts` b on `b`.`part_id` = `a`.`part_id` "
                "join `manufacture`.`det_names` c on `c`.`det_id` = `a`.`det_id` "
                "join `manufacture`.`zakaz_list` d on `d`.`zak_id` = `b`.`zak_id` ";

    if (type == "1")
    {//запуск
        sql << "where `b`.`zap_id` = '"<< object <<"' ";
    }
    else if (type == "2")
    {//заказ
        sql << "where `b`.`zap_id` = '"<< object <<"' and `b`.`zak_id` = '"<< element <<"' ";
    }
    else if (type == "4")
    {//партия
        sql << "where `b`.`part_id` = '"<< object <<"' ";
    }
    else
        throw std::runtime_error("Не известный тип объекта");
    sql << "order by d.zakaz, b.part_no ";

    TADOQuery *rez = DB->SendSQL(sql.str().c_str());
    if (rez)
    {
        if (rez->RecordCount)
        {
            for (rez->First(); !rez->Eof; rez->Next())
            {
                ObectData obj;
                obj.det_id =    (rez->FieldByName("det_id")->Value.operator AnsiString()).c_str();
                obj.obd =       (rez->FieldByName("obd")->Value.operator AnsiString()).c_str();
                obj.name =      (rez->FieldByName("name")->Value.operator AnsiString()).c_str();

                obj.zakaz =     (rez->FieldByName("zakaz")->Value.operator AnsiString()).c_str();
                obj.part_no =   (rez->FieldByName("part_no")->Value.operator AnsiString()).c_str();
                obj.izd_kol =   rez->FieldByName("kol")->Value;

                if (build_all)
                    BuildDataAll(obj);
                if (build_cooperation)
                    BuildDataCooperation(obj);
                if (build_forging)
                    BuildDataForging(obj);
                if (build_litho)
                    BuildDataLitho(obj);
                if (build_stamping)
                    BuildDataStamping(obj);
            }
        }
        delete rez;
    }
    else
    {
        throw std::runtime_error("Ошибка соединения с базой данных");
    }
}

void BuildDataAll           (std::string det_id, std::string obd, std::string name,
                             std::string zakaz, std::string part_no, int izd_kol)
{}
void BuildDataCooperation   (std::string det_id, std::string obd, std::string name,
                             std::string zakaz, std::string part_no, int izd_kol)
{}
void BuildDataForging       (std::string det_id, std::string obd, std::string name,
                             std::string zakaz, std::string part_no, int izd_kol)
{}
void BuildDataLitho         (std::string det_id, std::string obd, std::string name,
                             std::string zakaz, std::string part_no, int izd_kol)
{}
void BuildDataStamping      (std::string det_id, std::string obd, std::string name,
                             std::string zakaz, std::string part_no, int izd_kol)
{}

}
