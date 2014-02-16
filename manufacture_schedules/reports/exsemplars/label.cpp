#include <reports/exsemplars/label.h>
#include <xl_operations.h>
#include "functions.h"

namespace rep
{

Lable::Lable (int set): rep::Report("Ярлыки на детали",set),
    DB(0),path(""),use_listing(false),lists_by_file(0),object(""),element(""),type(""),template_path(""),
    cur_lists(0),templ("manufacture_forms.xlt")
{
    params[REPORT_PATH];
    params[REPORT_LIST_COUNT] = "10";
    params[REPORT_USE_LISTING] = REP_TRUE;
}
Lable::~Lable()
{}

Lable::Lable(const Lable &r):rep::Report(r),
    DB(0),path(""),use_listing(false),lists_by_file(0),object(""),element(""),type(""),template_path(""),
    cur_lists(0),templ("manufacture_forms.xlt")
{

}

void Lable::Build(void)
{
    cur_lists = 0;
    ParseParams();
    LoadSettings();
    BuildReport();
}
boost::shared_ptr<rep::Report> Lable::SelfCopy (void) const
{
    return boost::shared_ptr<rep::Report>(new Lable(*this));
}

void Lable::ParseParams(void)
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
void Lable::LoadSettings()
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


void Lable::BuildReport()
{
    //получить список маршрутных листов по заданию
    std::stringstream sql;
    sql << "select "
        << "a.part_id, "
        << "a.det_id, "
        << "a.list_no, "
        << "b.part_no, "
        << "c.zakaz, "
        << "sum(IFNULL(`a`.`kol_det`, 0)) kol, "
        << "f.name det_name, "
        << "f.obd det_code "
        << "from manufacture.marsh_lists a "
        << "join manufacture.parts b on a.part_id = b.part_id "
        << "join manufacture.zakaz_list c on b.zak_id = c.zak_id "
        << "join manufacture.det_names f on f.det_id = a.det_id ";
    //сюда добавить:
    //количество деталей
    //обозначение, название детали
    if (type == "1")
    {//запуск
        sql << "where b.zap_id = '"<< object <<"'";
    }
    else if (type == "2")
    {//заказ
        sql << "where b.zap_id = '"<< object <<"' and b.zak_id = '"<< element <<"'";
    }
    else if (type == "4")
    {//партия
        sql << "where a.part_id = '"<< object <<"'";
    }
    else if (type == "8")
    {//продукт
        sql << "where a.det_id = '"<< object <<"'";
    }
    else
        throw std::runtime_error("Не известный тип объекта");

    sql << "group by a.det_id ";
    sql << "order by f.obd, a.list_no ";

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
            size_t start_row = 1, end_row = 85, row_size = 14, template_row = 1;
            size_t template_page = 6;

			bool add_row = true;

			size_t file_no = 0;
            size_t page_no(0);
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
							TrimFile(xl,path,"",cur_lists,lists_by_file,teml_file,file_no);
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
