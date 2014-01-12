#include "routelist.h"
#include "xl_operations.h"
#include "functions.h"

namespace rep
{

RouteList::RouteList (int set): rep::Report("Маршрутные листы",set),
    DB(0),path(""),use_listing(false),lists_by_file(0),object(""),element(""),type(""),template_path(""),
    cur_lists(0),templ("manufacture_forms.xlt")
{
    params[REPORT_PATH];
    params[REPORT_LIST_COUNT] = "10";
    params[REPORT_USE_LISTING] = REP_TRUE;
}
RouteList::~RouteList()
{}

RouteList::RouteList(const RouteList &r):rep::Report(r),
    DB(0),path(""),use_listing(false),lists_by_file(0),object(""),element(""),type(""),template_path(""),
    cur_lists(0),templ("manufacture_forms.xlt")
{

}

void RouteList::Build(void)
{
    cur_lists = 0;
    ParseParams();
    LoadSettings();
    BuildReport();
}
boost::shared_ptr<rep::Report> RouteList::SelfCopy (void) const
{
    return boost::shared_ptr<rep::Report>(new RouteList(*this));
}

void RouteList::ParseParams(void)
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
void RouteList::LoadSettings()
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
void RouteList::BuildReport()
{
    //получить список маршрутных листов по заданию
    std::stringstream sql;
    sql << "select a.part_id, a.det_id, a.list_no, b.part_no, c.zakaz from manufacture.marsh_lists a "
        << "join manufacture.parts b on a.part_id = b.part_id "
        << "join manufacture.zakaz_list c on b.zak_id = c.zak_id "
        << "join manufacture.det_names d on d.det_id = a.det_id ";
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
    sql << "order by d.obd, a.list_no ";
    TADOQuery *rez = DB->SendSQL(sql.str().c_str());
	if (rez)
	{
		if (rez->RecordCount)
		{
			//включаем ексель
			cExcel ex;
			ex.Connect();
			ex.Visible(false);
			ex.DisplayAlerts(false);

			std::string teml_file = template_path + templ;

			OpenTemplate(ex, teml_file);

			size_t file_no = 0;

			for (rez->First(); !rez->Eof; rez->Next())
			{
				size_t det_id  = rez->FieldByName("det_id")->Value.operator int();
                std::string part_id = (rez->FieldByName("part_id")->Value.operator AnsiString()).c_str();
				std::string part_no = (rez->FieldByName("part_no")->Value.operator AnsiString()).c_str();
				std::string list_no = (rez->FieldByName("list_no")->Value.operator AnsiString()).c_str();
				std::string zakaz = (rez->FieldByName("zakaz")->Value.operator AnsiString()).c_str();

                BuildData(ex, det_id,part_id, part_no, list_no, zakaz);//для каждой строчки данных подгружаем детализацию

				if (use_listing && !path.empty())
				{//проверяем количество страниц, если выставлена опция
					TrimFile(ex,path,"",cur_lists,lists_by_file,teml_file,file_no);
				}

			}
			if (!path.empty())//закрываем Excel в зависимости от опции сохранения в файл
			{
				SaveFile(ex,path,"",cur_lists,file_no);
				ex.Book_Close(ex.GetBook(1));
				ex.Disconnect();
			}
			else
			{
				RemoveTemplates(ex,cur_lists);
				ex.Visible(true);
			}
		}
		delete rez;
    }
    else
    {
        throw std::runtime_error("Ошибка соединения с базой данных");
    }
}
void RouteList::BuildData(cExcel &xl, size_t det_id, std::string part_id, std::string part_no, std::string list_no, std::string zakaz)
{
    //для каждой строчки данных подгружаем детализацию
    std::stringstream sql;
    sql << "select "
           //для шапки
        << "date_format(now(),'%d.%m.%Y') date, "
        << "ceil(IFNULL(`b`.`kol_det`, 0)/`g`.`kdz`) kol_zag, "
        << "`g`.`nrm` norm, "
        << "`g`.`nrm` * IFNULL(`b`.`kol_det`, 0) norm_summ, "
        << "`g`.`masz` mass, "
        << "`g`.`masz` * IFNULL(`b`.`kol_det`, 0) mass_summ, "
        << "`g`.`razz` razz, "
        << "`g`.`vz`   zag_code, "
        << "trim(concat(`g`.`pm`,' ',`g`.`napr`)) marshrut, "
        << "IFNULL(`h`.`nama`,IFNULL(`h1`.`name`,'')) mat_name, "
        << "IFNULL(`h`.`prma`,'') mat_proff, "

           //отрывные
        << "`a`.`obd`   det_code, "
        << "`a`.`name`  det_name, "
        << "IFNULL(`b`.`kol_det`, 0) kol, "
        << "`c`.`cex`   cex, "
        << "`c`.`utch`  utch, "
        << "`c`.`opr`   oper_no, "
        << "IFNULL(`c`.`oboID`, '')     obo, "
        << "IFNULL(`d`.`OprID`, '')     opr_code, "
        << "IFNULL(`d`.`name`, '')      opr_name, "
        << "IFNULL(`e`.`order_id`, '')  order_no, "

        << "IFNULL(`f`.`rr`,  '') rr, "
        << "IFNULL(`f`.`kvn`, '') vn, "
        << "IFNULL(`f`.`tpz`, '') tpz, "
        << "IFNULL(round(`f`.`tsht`*`f`.`ksht`*`f`.`krop`/`f`.`kolod`, 5), '') tsht "

        << "from        `manufacture`.`det_names` a "
        << "join        `manufacture`.`marsh_lists` b on `b`.`det_id` = `a`.`det_id` and `b`.`part_id` = '"<<part_id<<"'"
        << "join        `manufacture`.`operation_list` c  on `c`.`det_id`         = `a`.`det_id` "
        << "left join   `equipment`.`opr_names` d         on `d`.`oprid`          = `c`.`oprid`  "
        << "left join   `manufacture`.`orders` e          on `e`.`operation_id`   = `c`.`OpUUID` "
        << "left join   `manufacture`.`operation_norms` f on `f`.`OpUUID`         = `c`.`OpUUID` "
        << "join        `manufacture`.`det_info` g        on `g`.`det_id`         = `a`.`det_id` "
        << "left join   `manufacture`.`materials` h       on `h`.`obmid`          = `g`.`obmid`  "
        << "left join   `manufacture`.`det_names` h1      on `h1`.`det_id`        = `g`.`obmid`  "

        << "where `a`.`det_id` = '" << det_id <<"' "

		<< "group by `a`.`obd`,`c`.`opr`,`c`.`oboid` "
		<< "order by `c`.`opr` desc, `c`.`oboID` asc ";

    TADOQuery *rez = DB->SendSQL(sql.str().c_str());
    if (rez)
    {
        if (rez->RecordCount)
        {
            bool new_page = true;
            bool first_page = true;
            size_t cur_row = 0;
            size_t start_row = 0, end_row = 69, row_size = 0, template_row = 0;
            size_t first_page_start = 17;
            size_t second_page_start = 4;
            size_t summary_row_size = 2;
            size_t data_row_size = 7;

            int page = 0;
            bool summary_info = true;

            //расчитать количество листов
            size_t rows_count = rez->RecordCount * (summary_row_size + data_row_size)+1;
            size_t page_count = 1;
            if (rows_count > end_row - first_page_start)
            {
                page_count += (rows_count - (end_row - first_page_start))/(end_row - second_page_start);
                if ((rows_count - (end_row - first_page_start))%(end_row - second_page_start))
                {
                    ++page_count;
                }
            }

            std::stringstream buf;
            for (size_t i = 0; i < 2; ++i)
            {
                if (summary_info)
                {
                    row_size = summary_row_size;
                    template_row = 17;
                }
                else
                {
                    row_size = data_row_size;
                    template_row = 20;
                }

				std::string last_podr ="";
				for (rez->First(); !rez->Eof; rez->Next())
				{
                    //считать данные запроса
                    list_no;
                    zakaz;
                    part_no;

					std::string kol_zag     =(rez->FieldByName("kol_zag")->Value.operator AnsiString()).c_str();
					std::string norm        =(rez->FieldByName("norm")->Value.operator AnsiString()).c_str();
					std::string norm_summ   =(rez->FieldByName("norm_summ")->Value.operator AnsiString()).c_str();
					std::string mass        =(rez->FieldByName("mass")->Value.operator AnsiString()).c_str();
					std::string mass_summ   =(rez->FieldByName("mass_summ")->Value.operator AnsiString()).c_str();
					std::string razz        =(rez->FieldByName("razz")->Value.operator AnsiString()).c_str();
					std::string zag_code    =(rez->FieldByName("zag_code")->Value.operator AnsiString()).c_str();
					std::string marshrut    =(rez->FieldByName("marshrut")->Value.operator AnsiString()).c_str();
					std::string mat_name    =(rez->FieldByName("mat_name")->Value.operator AnsiString()).c_str();
					std::string mat_proff   =(rez->FieldByName("mat_proff")->Value.operator AnsiString()).c_str();


					std::string date        =(rez->FieldByName("date")->Value.operator AnsiString()).c_str();

					std::string det_code    =VinToGost(rez->FieldByName("det_code")->Value.operator AnsiString()).c_str();
					std::string det_name    =(rez->FieldByName("det_name")->Value.operator AnsiString()).c_str();
					std::string kol         =(rez->FieldByName("kol")->Value.operator AnsiString()).c_str();

					std::string cex         =(rez->FieldByName("cex")->Value.operator AnsiString()).c_str();
					std::string utch        =(rez->FieldByName("utch")->Value.operator AnsiString()).c_str();
					std::string oper_no     =(rez->FieldByName("oper_no")->Value.operator AnsiString()).c_str();
					std::string obo         =(rez->FieldByName("obo")->Value.operator AnsiString()).c_str();
					std::string opr_code    =(rez->FieldByName("opr_code")->Value.operator AnsiString()).c_str();
					std::string opr_name    =(rez->FieldByName("opr_name")->Value.operator AnsiString()).c_str();
					std::string order_no    =(rez->FieldByName("order_no")->Value.operator AnsiString()).c_str();

					std::string rr      =(rez->FieldByName("rr")->Value.operator AnsiString()).c_str();
					std::string vn      =(rez->FieldByName("vn")->Value.operator AnsiString()).c_str();
					std::string tpz     =(rez->FieldByName("tpz")->Value.operator AnsiString()).c_str();
					std::string tsht    =(rez->FieldByName("tsht")->Value.operator AnsiString()).c_str();

                    new_page = new_page + (cur_row + row_size > end_row);//проанализировать количестко оставшихся строк
                    if (new_page)
					{
						new_page = false;
                        //создать страницу
                        xl.Sheet_Copy(xl.GetSheet(cur_lists+7), xl.GetSheet(cur_lists+1), Variant().NoParam());
                        cur_lists++ ;
                        page++;
                        xl.SetActiveSheet(xl.GetSheet(cur_lists));
                        xl.Set_Sheet_Name(xl.GetSheet(cur_lists),"МЛ-"+String(list_no.c_str())+"-"+IntToStr(page));

                        //первая строка
                        buf.str("");
                        buf<<page;
                        xl.toCells(1,     30,  buf.str().c_str() );
                        buf.str("");
                        buf<<page_count;
                        xl.toCells(1,     32,  buf.str().c_str() );


                        xl.toCells(1,     6,  list_no.c_str()   );
                        xl.toCells(1,     9,  zakaz.c_str()     );
                        xl.toCells(1,     12, part_no.c_str()   );
                        xl.toCells(1,     16, det_code.c_str()  );

                        if (first_page)
                        {
                            first_page = false;
                            start_row = first_page_start;

                            //убрать лишние строки шаблона
                            // копирование
							xl.Range_Copy(xl.GetRows(xl.GetSheet(cur_lists+7), 30, 70));
							// вставка
                            xl.Sheet_activate();
                            xl.Range_Paste(xl.GetRows(17, 30));

                            //шапка
                            //часть 1
                            xl.toCells(3,     4,  list_no.c_str()   );
                            xl.toCells(3,     6,  date.c_str()      );
                            xl.toCells(3,     9,  det_code.c_str()  );
                            xl.toCells(3,     14,  zakaz.c_str()    );
                            xl.toCells(3,     15,  part_no.c_str()  );

                            xl.toCells(4,     2,  det_name.c_str()  );

                            xl.toCells(5,     4,  kol_zag.c_str()   );
                            xl.toCells(5,     5,  mat_name.c_str()  );

                            xl.toCells(6,     4,  kol.c_str()       );
                            xl.toCells(6,     5,  mat_proff.c_str() );

                            xl.toCells(8,     5,  mass.c_str()      );
                            xl.toCells(8,     9,  mass_summ.c_str() );
                            xl.toCells(8,     12, zag_code.c_str()  );

                            xl.toCells(9,     5,  norm.c_str()      );
                            xl.toCells(9,     9,  norm_summ.c_str() );

                            //часть 2
                            xl.toCells(3,     20,  list_no.c_str()  );
                            xl.toCells(3,     23,  date.c_str()     );
                            xl.toCells(3,     27,  det_code.c_str() );
                            xl.toCells(3,     31,  zakaz.c_str()    );
                            xl.toCells(3,     33,  part_no.c_str()  );

                            xl.toCells(4,     17,  det_name.c_str() );

                            xl.toCells(5,     20,  kol_zag.c_str()  );
                            xl.toCells(5,     21,  mat_name.c_str() );

                            xl.toCells(6,     20,  kol.c_str()      );
                            xl.toCells(6,     21,  mat_proff.c_str());

                            xl.toCells(8,     22,  mass.c_str()     );
                            xl.toCells(8,     27,  mass_summ.c_str());
                            xl.toCells(8,     30,  zag_code.c_str() );

                            xl.toCells(9,     22,  norm.c_str()     );
                            xl.toCells(9,     27,  norm_summ.c_str());

                            //шапка для инофрмации о детали
                            xl.toCells(11,    6,  list_no.c_str()   );
                            xl.toCells(11,    9,  date.c_str()      );
                            xl.toCells(11,    12, zakaz.c_str()     );
                            xl.toCells(11,    15, part_no.c_str()   );
                            xl.toCells(11,    16, det_code.c_str()  );
                            xl.toCells(11,    29, mat_name.c_str()  );

                            xl.toCells(12,    1,  det_name.c_str()  );
                            xl.toCells(12,    14, kol_zag.c_str()   );
                            xl.toCells(12,    27, mat_proff.c_str() );

                            xl.toCells(13,    14, kol.c_str()       );
                            xl.toCells(13,    15, razz.c_str()      );

                            size_t delim_pos = std::string::npos;
                            if (marshrut.size() > 25 )
                                delim_pos = marshrut.find_last_of(" ",25);
							if (delim_pos != std::string::npos)
							{
								xl.toCells(13,    4, marshrut.substr(0, delim_pos).c_str());//26 знаков
								xl.toCells(14,    1, marshrut.substr(delim_pos+1, marshrut.size()).c_str());
							}
							else
							{
								xl.toCells(13,    4, marshrut.c_str());//26 знаков
								xl.toCells(14,    1, "");
							}
                        }
                        else
                        {
                            start_row = second_page_start;

                            //убрать лишние строки шаблона
                            // копирование
                            xl.Range_Copy(xl.GetRows(xl.GetSheet(cur_lists+7), 30, 70));
                            // вставка
                            xl.Sheet_activate();
                            xl.Range_Paste(xl.GetRows(2, 30));
                            if(summary_info)
                            {
                                //вставить шапку для инофрмации о детали
                                // копирование
                                xl.Range_Copy(xl.GetRows(xl.GetSheet(cur_lists+7), 15, 16));
                                // вставка
                                xl.Sheet_activate();
                                xl.Range_Paste(xl.GetRows(2, 3));
                            }
                        }

                        cur_row = start_row;
                    }


                    //вставить строку в отчет
                    // копирование
                    xl.Range_Copy(xl.GetRows(xl.GetSheet(cur_lists+7), template_row, template_row + row_size - 1));
                    // вставка
                    xl.Sheet_activate();
                    xl.Range_Paste(xl.GetRows(cur_row, cur_row + row_size));

                    if (summary_info)
                    {
                        xl.toCells(cur_row,     1,  (cex + utch).c_str());
                        xl.toCells(cur_row+1,   1,  oper_no.c_str()     );

                        xl.toCells(cur_row,     2,  opr_code.c_str()    );
                        xl.toCells(cur_row,     3,  opr_name.c_str()    );

                        xl.toCells(cur_row,     7,  rr.c_str()          );
                        xl.toCells(cur_row+1,   7,  vn.c_str()          );

                        xl.toCells(cur_row,     8,  order_no.c_str()    );

                        xl.toCells(cur_row,     11,  tpz.c_str()        );
                        xl.toCells(cur_row,     13,  tsht.c_str()       );
                    }
					else
					{
						std::string curr_podr = cex + utch;
						if (last_podr == curr_podr)
						{
							xl.toCells(cur_row,     2,  "");
						}
						last_podr = curr_podr;

						xl.toCells(cur_row,     5,  list_no.c_str()     );
                        xl.toCells(cur_row,     14,  zakaz.c_str()      );
                        xl.toCells(cur_row,     15,  part_no.c_str()    );
                        xl.toCells(cur_row,     7,  det_code.c_str()    );
                        xl.toCells(cur_row,     18,  kol.c_str()        );

                        xl.toCells(cur_row+1,   3,  det_name.c_str()    );

						xl.toCells(cur_row+3,   3,  (cex + utch).c_str());
                        xl.toCells(cur_row+3,   5,  obo.c_str()         );
                        xl.toCells(cur_row+3,   7,  oper_no.c_str()     );
                        xl.toCells(cur_row+3,   8,  opr_code.c_str()    );
                        xl.toCells(cur_row+3,   9,  rr.c_str()          );
                        xl.toCells(cur_row+3,   10, vn.c_str()          );
                        xl.toCells(cur_row+3,   14,  tsht.c_str()       );

                        xl.toCells(cur_row+4,   3,  opr_name.c_str()    );
                        xl.toCells(cur_row+4,   14,  tpz.c_str()        );

                        for (size_t i = 1; i < row_size-1; ++i)
                        {
                            xl.toCells(cur_row+i,   26, order_no.c_str());
						}
					}
					cur_row += row_size;
                }
				summary_info = false;
				++cur_row;
			}
        }
        delete rez;
    }
}

}
