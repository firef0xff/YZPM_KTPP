#include "manufacturing_details.h"

namespace rep
{
ManufacturingDetails::ManufacturingDetails (int set): rep::Report("Перечень выдаваемой документации",set),
    DB(0),path(""),use_listing(false),lists_by_file(0),object(""),element(""),type(""),template_path(""),
    cur_lists(0),templ("manufacture_forms.xlt")
{
    params[REPORT_PATH];
    params[REPORT_LIST_COUNT] = "10";
    params[REPORT_USE_LISTING] = REP_TRUE;
}
ManufacturingDetails::~ManufacturingDetails()
{}

ManufacturingDetails::ManufacturingDetails(const ManufacturingDetails &r):rep::Report(r),
    DB(0),path(""),use_listing(false),lists_by_file(0),object(""),element(""),type(""),template_path(""),
    cur_lists(0),templ("manufacture_forms.xlt")
{}

void ManufacturingDetails::Build(void)
{
    cur_lists = 0;
    ParseParams();
    LoadSettings();
    BuildReport();
}
boost::shared_ptr<rep::Report> ManufacturingDetails::SelfCopy (void) const
{
    return boost::shared_ptr<rep::Report>(new ManufacturingDetails(*this));
}

void ManufacturingDetails::ParseParams(void)
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
void ManufacturingDetails::LoadSettings()
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
void ManufacturingDetails::BuildReport()
{
    //получить список маршрутных листов по заданию
    std::stringstream sql;
    sql <<  "select `a`.`det_id`, `c`.`obd`, `c`.`name`,`d`.`zakaz`,`b`.`part_no`,`a`.`kol`,`b`.`part_id` "
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
            ObectData obj;
            for (rez->First(); !rez->Eof; rez->Next())
            {
                DataList data;
                cur_lists = 0;
                obj.det_id =    (rez->FieldByName("det_id")->Value.operator AnsiString()).c_str();
                obj.part_id =   (rez->FieldByName("part_id")->Value.operator AnsiString()).c_str();
                obj.obd =       (rez->FieldByName("obd")->Value.operator AnsiString()).c_str();
                obj.name =      (rez->FieldByName("name")->Value.operator AnsiString()).c_str();

                obj.zakaz =     (rez->FieldByName("zakaz")->Value.operator AnsiString()).c_str();
                obj.part_no =   (rez->FieldByName("part_no")->Value.operator AnsiString()).c_str();
                obj.izd_kol =   rez->FieldByName("kol")->Value;

                BuildData(&data, obj);
                DataToExcel(data, obj);
            }
        }
        delete rez;
    }
    else
    {
        throw std::runtime_error("Ошибка соединения с базой данных");
    }
}

void ManufacturingDetails::BuildData   (DataList *data, const ObectData &obj)
{

    DB->SendCommand(std::string("Call `manufacture`.GetContent(0,0,0,"+obj.det_id+",0)").c_str());

    std::string sql = " select `a`.`det_id`, `a`.`obd`, `a`.`name` "
                      " from `manufacture`.`det_names` a "
                      " join `manufacture`.`output` b on a.det_id = b.det_id "
                      " join `manufacture`.`marsh_lists` c on `a`.`det_id` = `c`.`det_id` "
                      " and `c`.`part_id` = '" + obj.part_id + "'"
                      " order by `a`.`obd` "  ;

    TADOQuery *rez = DB->SendSQL(sql.c_str());

    if (rez)
    {
        if (rez->RecordCount)
        {
            for (rez->First(); !rez->Eof; rez->Next())
            {
                ReportData item;
                item.det_id = (rez->FieldByName("det_id")->Value.operator AnsiString()).c_str();
                item.obd = VinToGost(rez->FieldByName("obd")->Value.operator AnsiString()).c_str();
                item.name = (rez->FieldByName("name")->Value.operator AnsiString()).c_str();
				data->insert(std::make_pair(item.obd, item));
			}
		}
        delete rez;
    }
}

void ManufacturingDetails::DataToExcel    (const DataList &data, const ObectData &obj)
{
    if (!data.empty())
    {
        //включаем ексель
        cExcel xl;
        xl.Connect();
        xl.Visible(false);
        xl.DisplayAlerts(false);

        std::string teml_file = template_path + templ;
        std::string file_name = path + "(" + obj.zakaz + " - " + obj.part_no + ")";
        std::string title = "Перечень выдаваемой документации";

        OpenTemplate(xl, teml_file);

        bool new_page = true;
        size_t cur_row = 0;
        size_t row_size = 1, start_row = 4, end_row = 53,
                template_row = 4;
        size_t template_page = 18;
        size_t max_page_no=0;

        size_t file_no = 0;

        //подсчет строк
        size_t need_rows(row_size * data.size());
        max_page_no = need_rows/(end_row-start_row);
        if (need_rows%(end_row-start_row))
        {
            ++max_page_no;
        }

        size_t list_no(0);
        for (DataList::const_iterator it = data.begin(), end = data.end() ; it!=end; ++it)
        {
            const ReportData &lnk = it->second;

            CheckList(new_page, row_size, start_row, end_row, template_page, max_page_no, file_name, teml_file,
                      title, obj, cur_row, file_no, list_no, xl);

            //вставить строку в отчет
            // копирование
            xl.Range_Copy(xl.GetRows(xl.GetSheet(cur_lists+template_page), template_row, template_row + row_size - 1));
            // вставка
            xl.Sheet_activate();
            xl.Range_Paste(xl.GetRows(cur_row, cur_row + row_size-1));
            //вывод инфо

            xl.toCells(cur_row,     2,  lnk.obd.c_str());
            xl.toCells(cur_row,     4,  lnk.name.c_str());
            cur_row += row_size;
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
}

void ManufacturingDetails::CheckList   (bool &new_page,
                                 const size_t row_size,
                                 const size_t start_row,
                                 const size_t end_row,
                                 const size_t template_page,
                                 const size_t max_page_no,

                                 const std::string &file_name,
                                 const std::string &teml_file,

                                 const std::string &title,

                                 const ObectData &obj,

                                 size_t &cur_row,
                                 size_t &file_no,
                                 size_t &list_no,
                                 cExcel &xl)
{
    new_page = new_page + (cur_row + row_size > end_row);//проанализировать количестко оставшихся строк

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
        list_no++;
        xl.SetActiveSheet(xl.GetSheet(cur_lists));
        std::stringstream buf;
        buf<<list_no;
        xl.Set_Sheet_Name(xl.GetSheet(cur_lists),("Лист-"+buf.str()).c_str());

        //заполнить шапку
        xl.toCells(1,   5,  Now().FormatString("dd.mm.yyyy"));
        xl.toCells(1,   2,  title.c_str());
        xl.toCells(2,   2,  VinToGost(obj.obd.c_str()));
        xl.toCells(2,   4,  obj.name.c_str());
        xl.toCells(2,   7,  obj.zakaz.c_str());
        xl.toCells(2,   10, obj.part_no.c_str());

        xl.toCells(1, 8, list_no);
        xl.toCells(1, 10, max_page_no);

        cur_row = start_row;
    }
}

}
