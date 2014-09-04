#include "complects.h"


namespace rep
{

Complect05::Complect05 (int set): rep::Report("Ведомость комплектации",set),
    DB(0),path(""),use_listing(false),lists_by_file(0),object(""),element(""),type(""),template_path(""),
    cur_lists(0),templ("manufacture_forms.xlt")
{
    params[REPORT_PATH];
    params[REPORT_LIST_COUNT] = "10";
    params[REPORT_USE_LISTING] = REP_TRUE;
}
Complect05::~Complect05()
{}

Complect05::Complect05(const Complect05 &r):rep::Report(r),
    DB(0),path(""),use_listing(false),lists_by_file(0),object(""),element(""),type(""),template_path(""),
    cur_lists(0),templ("manufacture_forms.xlt")
{

}

void Complect05::Build(void)
{
    cur_lists = 0;
    ParseParams();
    LoadSettings();
    BuildReport();
}
boost::shared_ptr<rep::Report> Complect05::SelfCopy (void) const
{
    return boost::shared_ptr<rep::Report>(new Complect05(*this));
}

void Complect05::ParseParams(void)
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
void Complect05::LoadSettings()
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
void Complect05::BuildReport()
{
    //получить список маршрутных листов по заданию
    std::stringstream sql;
	sql <<  "select `a`.`det_id`, `c`.`obd`, `c`.`name`,`d`.`zakaz`,`b`.`part_no` "
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
                std::string det_id =    (rez->FieldByName("det_id")->Value.operator AnsiString()).c_str();
                std::string obd =       (rez->FieldByName("obd")->Value.operator AnsiString()).c_str();
                std::string name =      (rez->FieldByName("name")->Value.operator AnsiString()).c_str();

                std::string zakaz =     (rez->FieldByName("zakaz")->Value.operator AnsiString()).c_str();
                std::string part_no =   (rez->FieldByName("part_no")->Value.operator AnsiString()).c_str();
                BuildData(det_id, obd, name, zakaz, part_no);
            }
        }
        delete rez;
    }
    else
    {
        throw std::runtime_error("Ошибка соединения с базой данных");
    }
}
void Complect05::BuildData      (std::string det_id, std::string obd, std::string name,
                                 std::string zakaz, std::string part_no)
{
    cur_lists = 0;

    DB->SendCommand(std::string("Call `manufacture`.GetContent(0,0,0,"+det_id+",0)").c_str());
    TADOQuery *rez = DB->SendSQL("select "
                                 "`c1`.`obd` as obu, "
                                 "`c2`.`obd` as obd, "
                                 "`c2`.`name`, "
                                 "sum(`b`.`kol_using`) as kol, "
                                 "concat(`c3`.`prma`,' ', `c3`.`gopr`) as sort "
                                 "from `manufacture`.output a "
                                 "join `manufacture`.`det_tree` b on `b`.`inst_idc` = `a`.`inst_id` "
                                 "join `manufacture`.`det_names` c1 on `c1`.`det_id` = `b`.`det_idp` "
                                 "join `manufacture`.`det_names` c2 on `c2`.`det_id` = `a`.`det_id` "
                                 "join `manufacture`.`materials` c3 on `c3`.`obmid` = `a`.`det_id` "
                                 "where `c2`.`pp` = '05' and `b`.`using` = '1' "
                                 "GROUP BY `c2`.`obd`,`c1`.`obd`");

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
            size_t row_size = 1, start_row = 9, end_row = 39,
                    template_row = 9;
            size_t template_page = 16;
            size_t max_page_no=0;

            size_t file_no = 0;

            //подсчет строк
            std::string last_obd;
            size_t need_rows(0);

            DataList data;
            for (rez->First(); !rez->Eof; rez->Next())
            {
                std::string obu = VinToGost(rez->FieldByName("obu")->Value.operator AnsiString()).c_str();
                std::string obd = VinToGost(rez->FieldByName("obd")->Value.operator AnsiString()).c_str();

                ReportData &lnk = data[obd];

                lnk.obd     = obd;
                lnk.name    = (rez->FieldByName("name")->Value.operator AnsiString()).c_str();
                lnk.sort    = (rez->FieldByName("sort")->Value.operator AnsiString()).c_str();

                ReportData::ObuData &obu_tmp = lnk.obu_list[obu];
                obu_tmp.obu = obu;
                obu_tmp.kol = rez->FieldByName("kol")->Value.operator double();



                //считать все данные в структуры спрогнозировать разметку

                //правила построения
                //при смене признака вставляется доп строчка
                //группировать по вхождениям детали пока не буду, но возможно потребуется в будущем
                need_rows += row_size;
                if (last_obd != obd && last_obd != "")
                {
                    need_rows += 1;
                    last_obd = lnk.obd;
                }
            }
            //пробежаться по списку структур, заполнить шаблон
            max_page_no = need_rows/(end_row-start_row);
            if (need_rows%(end_row-start_row))
            {
                ++max_page_no;
            }

            size_t list_no(0);
            for (DataList::const_iterator it = data.begin(), end = data.end() ; it!=end; ++it)
            {
                const ReportData &lnk = it->second;

                double summary(0.0);

                CheckList(new_page, row_size, start_row, end_row, template_page, max_page_no, file_name, teml_file,
                          zakaz, obd, name, part_no, cur_row, file_no, list_no, xl);

                //вставить строку в отчет
                // копирование
                xl.Range_Copy(xl.GetRows(xl.GetSheet(cur_lists+template_page), template_row, template_row + row_size - 1));
				// вставка
                xl.Sheet_activate();
				xl.Range_Paste(xl.GetRows(cur_row, cur_row + row_size-1));
                //вывод общей инфо
                xl.toCells(cur_row, 1, lnk.obd.c_str());
                xl.toCells(cur_row, 2, lnk.sort.c_str());
				xl.toCells(cur_row, 3, lnk.name.c_str());
                for (ReportData::ObuDataList::const_iterator it1 = lnk.obu_list.begin(), end1 = lnk.obu_list.end();
                     it1 != end1; ++it1)
                {
                    const ReportData::ObuData obu_lnk = it1->second;
                    CheckList(new_page, row_size, start_row, end_row, template_page, max_page_no, file_name, teml_file,
                              zakaz, obd, name, part_no, cur_row, file_no, list_no, xl);
                    //вывод детализации
                    xl.toCells(cur_row, 6, obu_lnk.obu.c_str());
                    xl.toCells(cur_row, 4, obu_lnk.kol);
					summary += obu_lnk.kol;
					++cur_row;
                    //вставить строку в отчет
                    // копирование
                    xl.Range_Copy(xl.GetRows(xl.GetSheet(cur_lists+template_page), template_row, template_row + row_size - 1));
                    // вставка
                    xl.Sheet_activate();
                    xl.Range_Paste(xl.GetRows(cur_row, cur_row + row_size-1));
                }
                //суммарная информация
                CheckList(new_page, row_size, start_row, end_row, template_page, max_page_no, file_name, teml_file,
                          zakaz, obd, name, part_no, cur_row, file_no, list_no, xl);
                xl.toCells(cur_row,3, "Итого");
				xl.toCells(cur_row,4, summary);
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
void Complect05::CheckList      (bool &new_page,
                                 const size_t row_size,
                                 const size_t start_row,
                                 const size_t end_row,
                                 const size_t template_page,
                                 const size_t max_page_no,

                                 const std::string &file_name,
                                 const std::string &teml_file,

                                 const std::string &zakaz,
                                 const std::string &obd,
                                 const std::string &name,
                                 const std::string &part_no,

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
        xl.toCells(3,   7,  zakaz.c_str()  );
        xl.toCells(4,   1,  VinToGost(obd.c_str()));
        xl.toCells(4,   3,  name.c_str()   );
        xl.toCells(6,   7,  part_no.c_str());

        xl.toCells(1,   7,  list_no        );
        xl.toCells(1,   9,  max_page_no    );
        cur_row = start_row;
    }

}

}

