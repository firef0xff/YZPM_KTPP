#include <reports/exsemplars/rep16.h>
#include "functions.h"
#include "boost/lexical_cast.hpp"
#include "functions.h"

namespace rep
{

Rep16::Rep16 (int set): rep::Report("Ресурсы заказа",set),
    DB(0),path(""),use_listing(false),lists_by_file(0),object(""),element(""),type(""),template_path(""),
	cur_lists(0),templ("rep16.xlt"),template_page(1),page_no(0)
{
    params[REPORT_PATH];
    params[REPORT_LIST_COUNT] = "10";
	params[REPORT_USE_LISTING] = REP_TRUE;
}
Rep16::~Rep16()
{}

Rep16::Rep16(const Rep16 &r):rep::Report(r),
    DB(0),path(""),use_listing(false),lists_by_file(0),object(""),element(""),type(""),template_path(""),
    cur_lists(0),templ("rep16.xlt"),template_page(1),page_no(0)
{

}

void Rep16::Build(void)
{
    cur_lists = 0;
	file_no = 0;
	page_no = 0;
    ParseParams();
    LoadSettings();
	BuildReport();
}
boost::shared_ptr<rep::Report> Rep16::SelfCopy (void) const
{
    return boost::shared_ptr<rep::Report>(new Rep16(*this));
}

void Rep16::ParseParams(void)
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
void Rep16::LoadSettings()
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
void Rep16::BuildReport()
{
    //получить список маршрутных листов по заданию
    //этап 1 получить список деталей
    std::string drop_step_1 = "drop temporary table if exists `manufacture`.`step_1`";
    std::stringstream create_step_1;
    //step1
	{
		create_step_1   <<  "create temporary table if not exists `manufacture`.`step_1` as "
							"select "
							"a1.zakaz, "
							"a.part_no, "
							"a.part_id, "
							"`b`.`det_id` as det_id "
							"from `manufacture`.`parts` a "
							"join `manufacture`.`zakaz_list` a1      on `a1`.`zak_id` = `a`.`zak_id` "
							"join `manufacture`.`marsh_lists` b      on `b`.`part_id` = `a`.`part_id` ";

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
	}
    //этап 2 получить нормы для деталей с оборудованием
	std::stringstream sql;
	sql <<"select "
		  "a1.zakaz, "
		  "a1.part_no, "
		  "`a`.`obd`   det_code, "
		  "`a`.`name`  det_name, "
		  "IF( `d1`.`name` is null or `c`.`cex` = 16, `d`.`name`, `d1`.`name` )  op_name, "
		  "`d`.`oprid`, "
		  "`g`.`razz` razz, "
		  "`g`.`vz`   zag_code, "
		  "CONVERT(trim(concat(IFNULL(concat(`h`.`nama`,' ',`h`.`goma`),IFNULL(`h1`.`name`,'')),' ', IFNULL(concat(`h`.`prma`,' ',`h`.`gopr`),''))), CHAR) mat_name, "
		  "IFNULL(`b`.`kol_det`, 0) kol, "
		  "`c`.`cex`   cex, "
		  "`c`.`utch`  utch, "
		  "if( `c`.`cex` = 16, 1, 0) as koop, "
		  "IFNULL(round(sum(`f`.`tpz`), 3), '') tpz, "
		  "replace(IFNULL(round(sum(`f`.`tsht`*`f`.`ksht`*`f`.`krop`/`f`.`kolod`)*IFNULL(`b`.`kol_det`, 0), 3), ''),'.',',') tsht "
		  "from        `manufacture`.`det_names` a "
		  "join 	   `manufacture`.`step_1` a1 		 on a.det_id=a1.det_id "
		  "join        `manufacture`.`marsh_lists` b 	 on `b`.`det_id` = `a`.`det_id` and `b`.`part_id` = a1.part_id "
		  "join        `manufacture`.`operation_list` c  on `c`.`det_id`         = `a`.`det_id` "
		  "left join   `equipment`.`opr_names` d         on `d`.`oprid`          = `c`.`oprid` "
		  "left join   `equipment`.`obor_list` d1         on `d1`.`oboid`        = `c`.`oboid` "
		  "left join   `manufacture`.`operation_norms` f on `f`.`OpUUID`         = `c`.`OpUUID` "
		  "join        `manufacture`.`det_info` g        on `g`.`det_id`         = `a`.`det_id` "
		  "left join   `manufacture`.`materials` h       on `h`.`obmid`          = `g`.`obmid` "
		  "left join   `manufacture`.`det_names` h1      on `h1`.`det_id`        = `g`.`obmid` "
		  "group by  a1.zakaz, a1.part_no,`a`.`obd`, op_name, koop ";

	DB->SendCommand(drop_step_1.c_str());
	DB->SendCommand(create_step_1.str().c_str());
	TADOQuery *rez = DB->SendSQL(sql.str().c_str());
	DB->SendCommand(drop_step_1.c_str());

	if (rez)
	{
		if (rez->RecordCount)
		{
			StartXL();
			for (rez->First(); !rez->Eof; rez->Next())
			{
				std::string curr_zakaz = (rez->FieldByName("zakaz")->Value.operator AnsiString()).c_str();
				std::string part_no = (rez->FieldByName("zakaz")->Value.operator AnsiString()).c_str();
				std::string zakaz = curr_zakaz;

				DataSet zak_data;
				DataOpersSet op_data;
				DataOpersSet coop_data;

				do //добваление деталей
				{
					Data d;
					d.obd = ( VinToGost( rez->FieldByName("det_code")->Value.operator AnsiString() ) ).c_str();
					d.name = (rez->FieldByName("det_name")->Value.operator AnsiString()).c_str();
					d.mater = (rez->FieldByName("mat_name")->Value.operator AnsiString()).c_str();
					d.raz_zag = (rez->FieldByName("razz")->Value.operator AnsiString()).c_str();
					d.kod_mat = (rez->FieldByName("zag_code")->Value.operator AnsiString()).c_str();
					d.count = (rez->FieldByName("kol")->Value.operator AnsiString()).c_str();
					std::string next_obd = d.obd;
					do //добавление операций
					{
					   OpData op;
					   op.tsht = (rez->FieldByName("tsht")->Value.operator AnsiString()).c_str();
					   std::string oper = (rez->FieldByName("op_name")->Value.operator AnsiString()).c_str();
					   bool koop = rez->FieldByName("koop")->Value.operator bool();

					   if (!koop)
					   {
						  op_data[oper][d.obd]=op;
					   }
					   else
					   {
						  coop_data[oper][d.obd]=op;
					   }

					   	rez->Next();
						if (!rez->Eof)
						{
							next_obd = (rez->FieldByName("det_code")->Value.operator AnsiString()).c_str();
							if( d.obd != next_obd )
								rez->Prior();
						}
					}while( d.obd == next_obd && !rez->Eof );

                    zak_data.push_back( d );

					rez->Next();
					if (!rez->Eof)
					{
						zakaz = (rez->FieldByName("zakaz")->Value.operator AnsiString()).c_str();
						if( zakaz != curr_zakaz )
							rez->Prior();
					}
				}while( zakaz == curr_zakaz && !rez->Eof );
				AddPage(curr_zakaz);
				CreateHead( curr_zakaz, op_data.size(), coop_data.size(), zak_data.size() );
				PrintBody( zak_data, op_data, coop_data );
			}
			StopXL();
		}
        delete rez;
	}
    else
    {
        throw std::runtime_error("Ошибка соединения с базой данных");
    }
}

void Rep16::StartXL()
{
	//включаем ексель
	mXL.reset( new cExcel );
	mXL->Connect();
	mXL->Visible(false);
	mXL->DisplayAlerts(false);

	OpenTemplate(*mXL, template_path + templ);
}
void Rep16::StopXL()
{
	if (!path.empty())//закрываем Excel в зависимости от опции сохранения в файл
	{
		SaveFile( *mXL, path , "", cur_lists, file_no );
		mXL->Book_Close( mXL->GetBook(1) );
		mXL->Disconnect();
	}
	else
	{
		RemoveTemplates( *mXL, cur_lists );
		mXL->Visible(true);
	}
	mXL.reset();
}

void Rep16::AddPage( std::string const& zak )
{
	//создать страницу
	mXL->Sheet_Add(mXL->GetSheets(), mXL->GetSheet(cur_lists+1), Variant().NoParam());
	cur_lists++ ;
	page_no++;
	mXL->SetActiveSheet(mXL->GetSheet(cur_lists));
	mXL->Set_Sheet_Name(mXL->GetSheet(cur_lists),zak.c_str());
}
void Rep16::CreateHead     ( std::string const& zak, int op, int coop, int rows )
{
    int start_row = 1;
	//добавитьоснову
	// копирование
	mXL->SetActiveSheet(mXL->GetSheet(cur_lists+template_page));
	mXL->Sheet_activate();
	Variant range = mXL->GetRange( 1, 1, 10, 3 );
	mXL->Range_Copy( range );
	// вставка
	mXL->SetActiveSheet(mXL->GetSheet(cur_lists));
	mXL->Sheet_activate();
	mXL->Range_PasteSpecial( mXL->GetRange( start_row, 1, start_row+9, 3 ));

	//заполнить шапку
	mXL->toCells(1,   2,   zak.c_str() );

	//добавить операции
	mXL->SetActiveSheet(mXL->GetSheet(cur_lists+template_page));
	mXL->Sheet_activate();
	range = mXL->GetRange( 2, 4, 10, 5 );
	mXL->Range_Copy( range );
	// вставка
	mXL->SetActiveSheet(mXL->GetSheet(cur_lists));
	mXL->Sheet_activate();

	int op_cols = 1;
	int ofset = 4;
	for ( op_cols = 1; op_cols <= op; ++op_cols)
	{
		int size = 2;
		mXL->Range_PasteSpecial( mXL->GetRange( start_row+1, ofset, start_row+9, ofset + size - 1 ));
		ofset += size ;
	}
   //добавить коооперации
	mXL->SetActiveSheet(mXL->GetSheet(cur_lists+template_page));
	mXL->Sheet_activate();
	range = mXL->GetRange( 2, 6, 10, 7 );
	mXL->Range_Copy( range );
	// вставка
	mXL->SetActiveSheet(mXL->GetSheet(cur_lists));
	mXL->Sheet_activate();

	int koop_cols = 1;
	for ( koop_cols = 1; koop_cols <= coop; ++koop_cols)
	{
		int size = 2;
		mXL->Range_PasteSpecial( mXL->GetRange( start_row+1, ofset, start_row+9, ofset + size - 1 ));
		ofset += size ;
	}

    // копирование
	mXL->SetActiveSheet(mXL->GetSheet(cur_lists+template_page));
	mXL->Sheet_activate();
	range = mXL->GetRange( 2, 8, 10, 8 );
	mXL->Range_Copy( range );
	// вставка
	mXL->SetActiveSheet(mXL->GetSheet(cur_lists));
	mXL->Sheet_activate();
	mXL->Range_PasteSpecial( mXL->GetRange( start_row+1, ofset, start_row+9, ofset ));

	// копирование
	int row_offset = start_row + 8;
	int row_size = 2;
	range = mXL->GetRange( row_offset, 1, row_offset+row_size-1, ofset );
	mXL->Range_Copy( range );
	// вставка
	row_offset +=  row_size;

	for ( int i = 0; i < rows-1; ++i)
	{
		mXL->Range_Paste( mXL->GetRange( row_offset, 1, row_offset+row_size-1, ofset ));
		row_offset +=  row_size;
	}
}
void Rep16::PrintBody( DataSet const& det_data , DataOpersSet const& op_data, DataOpersSet const& coop_data )
{
	std::map<std::string, int> obd_row;
	int op_head_row = 2;
	int coop_head_row = 3;
	int first_row = 9;
	int row_size = 2;
	int current_row = first_row;
	int first_col = 4;
	int current_col = first_col;

	for ( DataSet::const_iterator it = det_data.begin(), end = det_data.end(); it != end; ++it )
	{
		Data const& dt = *it;
		obd_row[ dt.obd ] = current_row;

		mXL->toCells(current_row,   1,   dt.obd.c_str() );
		mXL->toCells(current_row+1, 1,   dt.name.c_str() );
		mXL->toCells(current_row,   2,   dt.mater.c_str() );
		mXL->toCells(current_row+1, 2,   dt.raz_zag.c_str() );
		mXL->toCells(current_row,   3,   dt.kod_mat.c_str() );
		mXL->toCells(current_row+1, 3,   dt.count.c_str() );

		current_row +=  row_size;
	}

	for ( DataOpersSet::const_iterator it = op_data.begin(), end = op_data.end(); it != end; ++it )
	{
		DataOpers const& opers = it->second;
		std::string const& op_name = it->first;
		mXL->toCells(op_head_row,   current_col,   op_name.c_str() );

		for ( DataOpers::const_iterator it1 = opers.begin(), end = opers.end(); it1 != end; ++it1 )
		{
			OpData const& op_data = it1->second;
			std::string const& obd = it1->first;
			int row = obd_row[obd];
			if (!row)
				continue;
			mXL->toCells(row,   current_col,   op_data.count.c_str() );
			mXL->toCells(row+1, current_col,   op_data.tsht.c_str() );
			mXL->toCells(row,   current_col+1, op_data.date.c_str() );
			Variant range = mXL->GetRange( row, current_col, row+1, current_col+1 );
			mXL->Range_Color( range, 19 );
		}
		current_col +=  2;
	}

	for ( DataOpersSet::const_iterator it = coop_data.begin(), end = coop_data.end(); it != end; ++it )
	{
		DataOpers const& opers = it->second;
		std::string const& op_name = it->first;
		mXL->toCells(coop_head_row,   current_col,   op_name.c_str() );

		for ( DataOpers::const_iterator it1 = opers.begin(), end = opers.end(); it1 != end; ++it1 )
		{
			OpData const& op_data = it1->second;
			std::string const& obd = it1->first;
			int row = obd_row[obd];
			if (!row)
				continue;
			mXL->toCells(row,   current_col,   op_data.count.c_str() );
			mXL->toCells(row+1, current_col,   op_data.tsht.c_str() );
			mXL->toCells(row,   current_col+1, op_data.date.c_str() );
			Variant range = mXL->GetRange( row, current_col, row+1, current_col+1 );
			mXL->Range_Color( range, 20 );
		}
		current_col +=  2;
	}
}

/*void Rep16::CheckList (cExcel &xl, size_t &row, size_t row_size)
{

    const size_t start_row = 4, end_row = 58;

    bool new_page = !row + (row + row_size > end_row);//проанализировать количестко оставшихся строк

    if (new_page)
    {
        if (cur_lists)
        {
            if (use_listing && !path.empty())
            {//проверяем количество страниц, если выставлена опция
                TrimFile(xl,path,"",cur_lists,lists_by_file,template_path + templ,file_no);
            }
        }

        //создать страницу
        xl.Sheet_Copy(xl.GetSheet(cur_lists+template_page), xl.GetSheet(cur_lists+1), Variant().NoParam());
        cur_lists++ ;
		page_no++;
        xl.SetActiveSheet(xl.GetSheet(cur_lists));
        std::stringstream buf;
        buf<<page_no;
        xl.Set_Sheet_Name(xl.GetSheet(cur_lists),("ФY09102-"+buf.str()).c_str());

        // почистить лист
        // копирование
        xl.Range_Copy(xl.GetRows(xl.GetSheet(cur_lists+template_page), 7, 9));
        // вставка
        xl.Sheet_activate();
        xl.Range_Paste(xl.GetRows(4, 6));

        //заполнить шапку

        xl.toCells(2,   1,   Now().FormatString("dd.mm.yyyy")           );

        row = start_row;
    }
}*/

}
