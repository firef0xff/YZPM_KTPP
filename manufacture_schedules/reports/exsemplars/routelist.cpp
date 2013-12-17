#include "routelist.h"
#include "sstream.h"
#include "Excel.h"

namespace rep
{

RouteList::RouteList (int set): rep::Report("Маршрутные листы",set),
    DB(0),path(""),use_listing(false),lists_by_file(0),object(""),element(""),type(""),template_path(""),
    cur_lists(0)
{
    params[REPORT_PATH];
    params[REPORT_LIST_COUNT] = "10";
    params[REPORT_USE_LISTING] = REP_TRUE;
}
RouteList::~RouteList()
{}

RouteList::RouteList(const RouteList &r):rep::Report(r),
    DB(0),path(""),use_listing(false),lists_by_file(0),object(""),element(""),type(""),template_path(""),
    cur_lists(0)
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
    sql << "select a.part_id, a.det_id, a.list_no from manufacture.marsh_lists a ";

    if (type == "1")
    {//запуск
        sql << "join manufacture.parts b on a.part_id = b.part_id ";
        sql << "where a.zap_id = '"<< object <<"'";
    }
    else if (type == "2")
    {//заказ
        sql << "join manufacture.parts b on a.part_id = b.part_id ";
        sql << "where b.zap_id = '"<< object <<"' and b.zak_id = '"<< element <<"'";
    }
    else if (type == "4")
    {//партия
        sql << "where a.part_id = '"<< object <<"'";
    }
    else if (type == "8")
    {//продукт
        sql << "where a.part_id = '"<< object <<"' and a.det_id = '"<< element <<"'";
    }
    else
        throw std::runtime_error("Не известный тип объекта");

    TADOQuery *rez = DB->SendSQL(sql.str().c_str());
    if (rez)
    {
        //включаем ексель
        cExcel ex;
        ex.Connect();
        ex.Visible(false);
        ex.DisplayAlerts(false);


        for (rez->First(); !rez->Eof(); rez->Next())
        {
            BuildData();//для каждой строчки данных подгружаем детализацию

            //проверяем количество страниц, если выставлена опция
        }
        //закрываем Excel в зависимости от опции сохранения в файл

        ex.Visible(true);
        ex.Disconnect();
        delete rez;
    }
    else
    {
        throw std::runtime_error("Ошибка соединения с базой данных");
    }
}
void RouteList::BuildData(size_t det_id)
{
    //для каждой строчки данных подгружаем детализацию
}

/*

void cReports::OpenTemplate (AnsiString templ)
{
    XL->SetActiveBooks(XL->Books_Open(templ));
    // Инициализация переменных указателей на итемы екселя
    XL->SetActiveBook(XL->GetFirstBook());
    XL->SetActiveSheets(XL->GetSheets());
    XL->SetActiveSheet(XL->GetFirstSheet());
}
void cReports::SaveFile        (String file_name,String file_ext, int Lcount)
{
    while(Lcount&&Lcount<XL->GetSheetsCount())
    {
        XL->Sheet_Del(XL->GetSheet(XL->GetSheetsCount()));
    }
    XL->Sheet_activate(XL->GetFirstSheet());
    XL->Books_Save(file_name+file_ext);
}
void cReports::TrimFile        (String file_name,String file_ext,String templ, int &Lcount, int max_list_no)
{
    static String prev_file_name="";
    static int file_no=0;

    if (Lcount&&Lcount>=max_list_no)
    {
        if (prev_file_name!=file_name)
        {
            file_no=0;
            prev_file_name=file_name;
        }
        else
        {
            ++file_no;
        }

        String addin;
        if (file_no)
        {
            addin="_"+String(file_no);
        }
        SaveFile(file_name+addin,file_ext,Lcount);
        XL->Book_Close(XL->GetBook(1));
        OpenTemplate(templ);
        Lcount=0;
    }
}



*/

/*
int cReports::AddML(String obd, String name, String name_mat, String prof_mat,
    int kol, int Lcount, int mlnumber)
{
    int page=0, kolzag=0, row_start, row_end=62;
    String Range;
    bool newpage=true;
    // запрос на данные

    TADOQuery *rez=DB->SendSQL("Call temporary_tables.Marsh_list ('"+obd+"')");
    if(rez==0)
    {
        ShowMessage("Ошибка формирования запроса");
        return Lcount;
    }
    while(!rez->Eof)
    {
        // если есть что выводить то
        if(newpage)
        {
            XL->Sheet_Copy(XL->GetSheet(Lcount+2), XL->GetSheet(Lcount+1),
                Variant().NoParam());
            Lcount++ ;
            page++ ;
            XL->SetActiveSheet(XL->GetSheet(Lcount));
            XL->Set_Sheet_Name(XL->GetSheet(Lcount),
                "МЛ-"+IntToStr(mlnumber)+"-"+IntToStr(page));
            if(page==1)
            {
                // удаление лишнего/
                XL->Range_Copy(XL->GetRows(22, 26));
                XL->Range_Paste(XL->GetRows(18, 21));
                // расчет данных для записи/
                if(rez->FieldByName("kdz")->Value.operator int())
                {
                    kolzag=ceil(double(kol)/rez->FieldByName("kdz")
                        ->Value.operator int());
                }
                // запись шапки/
                XL->toCells(3, 3, "К М/Л "+IntToStr(mlnumber)+" от "+Date()+" "+
                    VinToGost(obd)+" "+parametr->zak->Text+" "+
                    parametr->part->Text);
                XL->toCells(3, 14, "К М/Л "+IntToStr(mlnumber)+" от "+Date()+
                    " "+VinToGost(obd)+" "+parametr->zak->Text+" "+
                    parametr->part->Text);
                XL->toCells(4, 3, name);
                XL->toCells(4, 14, name);
                XL->toCells(5, 4, kolzag);
                XL->toCells(6, 4, IntToStr(kol));
                XL->toCells(5, 16, kolzag);
                XL->toCells(6, 16, IntToStr(kol));
                XL->toCells(8, 4, rez->FieldByName("masz")->Value);
                XL->toCells(8, 6,
                    FloatToStrF(rez->FieldByName("masz")->Value.operator double
                    () *kol, ffGeneral, 9, 2));
                XL->toCells(8, 7, rez->FieldByName("vz")->Value);
                XL->toCells(8, 16, rez->FieldByName("masz")->Value);
                XL->toCells(8, 18,
                    FloatToStrF(rez->FieldByName("masz")->Value.operator double
                    () *kol, ffGeneral, 9, 2));
                XL->toCells(8, 20, rez->FieldByName("vz")->Value);
                XL->toCells(9, 4, rez->FieldByName("nrm")->Value);
                XL->toCells(9, 6,
                    FloatToStrF(rez->FieldByName("nrm")->Value.operator double()
                    *kol, ffGeneral, 9, 2));
                XL->toCells(9, 16, rez->FieldByName("nrm")->Value);
                XL->toCells(9, 18,
                    FloatToStrF(rez->FieldByName("nrm")->Value.operator double()
                    *kol, ffGeneral, 9, 2));
                XL->toCells(11, 20, name_mat+" "+prof_mat);
                XL->toCells(11, 12, VinToGost(obd));
                XL->toCells(11, 10, parametr->part->Text);
                XL->toCells(11, 8, parametr->zak->Text);
                XL->toCells(11, 6, "от "+Date());
                XL->toCells(11, 5, IntToStr(mlnumber));

                XL->toCells(12, 1, name);
                XL->toCells(12, 17, rez->FieldByName("razz")->Value);
                XL->toCells(13, 4, Get_Rascex(obd));
                XL->toCells(13, 13, kolzag);
                XL->toCells(14, 13, IntToStr(kol));
                row_start=18;
            }
            else
            {
                // стирание шапки первого листа остается только шапка таблиицы/
                XL->Range_Copy(XL->GetRows(22, 35));
                XL->Range_Paste(XL->GetRows(2, 15));
                XL->Range_Copy(XL->GetRows(16, 17));
                XL->Range_Paste(XL->GetRows(2, 3));
                XL->Range_Copy(XL->GetRows(22, 27));
                XL->Range_Paste(XL->GetRows(16, 21));
                row_start=4;
            }
            XL->toCells(1, 8, VinToGost(obd));
            XL->toCells(1, 7, parametr->part->Text);
            XL->toCells(1, 6, parametr->zak->Text);
            XL->toCells(1, 5, IntToStr(mlnumber));
            XL->toCells(1, 23, IntToStr(page));
            newpage=false;
        }
        // копирование
        XL->Range_Copy(XL->GetRows(XL->GetSheet(Lcount+2), 18, 21));
        // вставка
        XL->Sheet_activate();
        XL->Range_Paste(XL->GetRows(row_start, row_start+4));
        // вывод данных/
        XL->toCells(row_start, 1, rez->FieldByName("ceu")->Value);
        XL->toCells(row_start+2, 1, rez->FieldByName("opr")->Value);
        XL->toCells(row_start, 2, Trim(rez->FieldByName("obo")->Value)+
            "                                     "+
            Trim(rez->FieldByName("kop")->Value)+" "+
            Trim(rez->FieldByName("nop")->Value));
        XL->toCells(row_start, 5, rez->FieldByName("rr")->Value);
        XL->toCells(row_start+2, 5, rez->FieldByName("kvn")->Value);
        XL->toCells(row_start, 7, rez->FieldByName("tpz")->Value);
        XL->toCells(row_start, 9, rez->FieldByName("tsht")->Value);
        if(row_start<row_end)
        {
            row_start+=4;
        }
        else
        {
            newpage=true;
        }
        rez->Next();
    }
    delete rez;
    return Lcount;
}

}*/

}
