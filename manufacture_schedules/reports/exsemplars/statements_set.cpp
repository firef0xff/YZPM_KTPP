#include "statements_set.h"
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
    params["Ведомость кооперации"] = REP_TRUE;
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
    build_cooperation = params["Ведомость кооперации"] == REP_TRUE;

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
            for (rez->First(); !rez->Eof; rez->Next())
            {
                cur_lists = 0;

                ObectData obj;
                obj.det_id =    (rez->FieldByName("det_id")->Value.operator AnsiString()).c_str();
                obj.part_id =   (rez->FieldByName("part_id")->Value.operator AnsiString()).c_str();
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

void StatementsSet::BuildDataAll           (const ObectData &obj)
{}
void StatementsSet::BuildDataCooperation   (const ObectData &obj)
{

    DB->SendCommand(std::string("Call `manufacture`.GetContent(0,0,0,"+obj.det_id+",0)").c_str());

    DB->SendCommand("Drop TEMPORARY TABLE if EXISTS `manufacture`.`itog`");
    DB->SendCommand("Drop TEMPORARY TABLE if EXISTS `manufacture`.`opr_l_filter`");

    DB->SendCommand("CREATE TEMPORARY table `manufacture`.`itog` "
                    "( "
                        "det_id bigint(20) unsigned not NULL, "
                        "kol double not NULL DEFAULT 0, "
                        "key det_id(`det_id`) "
                    ") engine = MEMORY; ");

    DB->SendCommand(std::string("insert into `manufacture`.`itog` (det_id, kol) "
                    "select "
                    "`a`.`det_idc`, "
                    "sum(`a`.`kol_using`) "
                    "from `manufacture`.`det_tree` a "
                    "join `manufacture`.`output` b on `a`.`det_idc` = `b`.`det_id` and a.`inst_idc` = b.`inst_id` "
                    "group by `a`.`det_idc` ").c_str() );


    DB->SendCommand("CREATE TEMPORARY table `manufacture`.`opr_l_filter` "
                    "( "
                        "det_id bigint(20) unsigned not NULL, "
                        "key det_id(`det_id`) "
                    ") engine = MEMORY; ");

    DB->SendCommand("insert into `manufacture`.`opr_l_filter` "
                    "SELECT distinct a.det_id "
                    "from `manufacture`.`itog` a "
                    "JOIN `manufacture`.`operation_list` b on `a`.`det_id` = `b`.`det_id` and "
                                                             "`b`.`cex`='16' and "
                                                             "`b`.`utch`!='25' and "
                                                             "`b`.`utch`!='26' and "
                                                             "`b`.`utch`!='27' and "
                                                             "`b`.`utch`!='28' and "
                                                             "`b`.`utch`!='63';");

    std::string sql = "select b.det_id, "
                        "b.obd as `Обозначение`, "
                        "if (b.name is not null,b.name,'') as `Наименование`, "
                        "if (a.kol is not null,a.kol,0) as `Кол-во`, "
                        "if (c.ei is not null,c.ei,'') as `Ед. изм.`, "
                        "if (c.masd is not null,c.masd,0) as `Масса детали`, "
                        "if (e.obd is not null,e.obd,'') as obm, "
                        "if (g.snameei is not null,snameei,'') as snameei, "
                        "if (concat(d.nama,' ',d.prma) is not null,concat(trim(d.nama),' ',trim(d.prma)),if(e.name is not null,e.name,'')) as `Материал`, "
                        "if (c.vz is not null,c.vz,0) as `Код заготовки`, "
                        "if (c.kdz is not null,c.kdz,0) as `Кол-во дет. в заг.`, "
                        "if (c.masz is not null,c.masz,0) as `Масса заг.`, "
                        "if (c.razz is not null,c.razz,'') as `Размеры заг.`, "
                        "if (c.nrm is not null,c.nrm,0) as `Норма расхода`, "
                        "if (c.pm is not null,c.pm,'') as `Рассцеховка` "
                        "from `manufacture`.`itog` a "
                        "join `manufacture`.`det_names` b on `a`.`det_id` = `b`.`det_id` "
                        "left join `manufacture`.`det_info` c on `a`.`det_id` = `c`.`det_id` "
                        "left JOIN `manufacture`.`materials` d on d.obmid=c.obmid "
                        "left join `manufacture`.`det_names` e on e.id=c.obmid "
                        "left join `catalogs`.`dimensionality` g on g.kodei=c.ei "
                        "left join `manufacture`.`opr_l_filter` f on `a`.`det_id` = `f`.`det_id` "
                        "where `f`.`det_id` is not null or c.vz in ('144','146','141','142','126','121','122','589','716','742','744','241','242') "
                        "order BY b.obd; ";
    TADOQuery *rez = DB->SendSQL(sql.c_str());

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
            std::string file_name = path + "(" + obj.zakaz + " - " + obj.part_no + ")";
            std::string title = "Ведомость материалов на заготовки, по кооперации";

            OpenTemplate(xl, teml_file);

            bool new_page = true;
            size_t cur_row = 0;
            size_t row_size = 3, start_row = 6, end_row = 48,
                    template_row = 6;
            size_t template_page = 17;
            size_t max_page_no=0;

            size_t file_no = 0;

            //подсчет строк
            size_t need_rows(0);

            DataList data;
            for (rez->First(); !rez->Eof; rez->Next())
            {
                ReportData item;
                item.det_id = (rez->FieldByName("det_id")->Value.operator AnsiString()).c_str();
                item.obd = VinToGost(rez->FieldByName("Обозначение")->Value.operator AnsiString()).c_str();
                item.name = (rez->FieldByName("Наименование")->Value.operator AnsiString()).c_str();
                item.kol = (rez->FieldByName("Кол-во")->Value.operator AnsiString()).c_str();
                item.ei = (rez->FieldByName("Ед. изм.")->Value.operator AnsiString()).c_str();
                item.mass = (rez->FieldByName("Масса детали")->Value.operator AnsiString()).c_str();
                item.obm = VinToGost(rez->FieldByName("obm")->Value.operator AnsiString()).c_str();
                item.name_ei = (rez->FieldByName("snameei")->Value.operator AnsiString()).c_str();
                item.mater = (rez->FieldByName("Материал")->Value.operator AnsiString()).c_str();
                item.vz = (rez->FieldByName("Код заготовки")->Value.operator AnsiString()).c_str();
                item.kdz = (rez->FieldByName("Кол-во дет. в заг.")->Value.operator AnsiString()).c_str();
                item.masz = (rez->FieldByName("Масса заг.")->Value.operator AnsiString()).c_str();
                item.razz = (rez->FieldByName("Размеры заг.")->Value.operator AnsiString()).c_str();
                item.nrm = (rez->FieldByName("Норма расхода")->Value.operator AnsiString()).c_str();

                Get_Rascex(item);

                data.push_back(item);

                //считать все данные в структуры спрогнозировать разметку

                //правила построения
                //при смене признака вставляется доп строчка
                //группировать по вхождениям детали пока не буду, но возможно потребуется в будущем
                need_rows += row_size;
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
                const ReportData &lnk = *it;

                CheckList(new_page, row_size, start_row, end_row, template_page, max_page_no, file_name, teml_file,
                          title, obj, cur_row, file_no, list_no, xl);

                //вставить строку в отчет
                // копирование
                xl.Range_Copy(xl.GetRows(xl.GetSheet(cur_lists+template_page), template_row, template_row + row_size - 1));
                // вставка
                xl.Sheet_activate();
                xl.Range_Paste(xl.GetRows(cur_row, cur_row + row_size-1));
                //вывод инфо

                xl.toCells(cur_row,     1,  lnk.obd.c_str());
                xl.toCells(cur_row+1,   1,  lnk.name.c_str());
                xl.toCells(cur_row,     4,  lnk.kol.c_str());
                xl.toCells(cur_row,     5,  lnk.ei.c_str());
                xl.toCells(cur_row+1,   5,  lnk.name_ei.c_str());
                xl.toCells(cur_row,     6,  lnk.mass.c_str());
                xl.toCells(cur_row,     7,  lnk.obd.c_str());
                xl.toCells(cur_row+1,   7,  lnk.mater.c_str());
                xl.toCells(cur_row,     8,  lnk.vz.c_str());
                xl.toCells(cur_row+1,   8,  lnk.razz.c_str());
                xl.toCells(cur_row,     9,  lnk.kdz.c_str());
                xl.toCells(cur_row,     10, lnk.masz.c_str());
                xl.toCells(cur_row,     11, lnk.nrm.c_str());
                xl.toCells(cur_row,     12, lnk.pm.c_str());

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
        delete rez;
    }

    DB->SendCommand("Drop TEMPORARY TABLE if EXISTS `manufacture`.`itog`");
    DB->SendCommand("Drop TEMPORARY TABLE if EXISTS `manufacture`.`opr_l_filter`");
}
void StatementsSet::BuildDataForging       (const ObectData &obj)
{}
void StatementsSet::BuildDataLitho         (const ObectData &obj)
{}
void StatementsSet::BuildDataStamping      (const ObectData &obj)
{}

void StatementsSet::Get_Rascex(ReportData &obj)
{
    String OBD=GostToVin(obj.obd.c_str());

    int id=0;
    TADOQuery *rez = 0;

    std::string sql = "Select concat(cex,utch)as ceu,opr from `manufacture`.`operation_list` where det_id='"+obj.det_id+"' order by opr",
                sql1 =" Select napr,pm from `manufacture`.`det_info` where det_id='"+obj.det_id+"'limit 0,1",
                sql2 = "Select sklad from `manufacture`.`materials` where obmid = '"+obj.det_id+"'";
    AnsiString  result = "",
                last = "";

    if(OBD.SubString(1, 9)=="000000000"&&OBD.Length()==15)
    { // если расцеховка по стандартному изделию
        rez = DB->SendSQL(sql.c_str());
        if(rez)
        { // построение расцеховки
            size_t count = rez->RecordCount;
            if (count)
            {
                for(rez->First(); !rez->Eof; rez->Next())
                {
                    if(Trim(rez->FieldByName("ceu")->Value)!=""
                       &&Trim(rez->FieldByName("ceu")->Value)!=last)
                    {
                        last=Trim(rez->FieldByName("ceu")->Value);
                        result+=last+" ";
                    }
                }
            }
            delete rez;
            rez = 0;
            if (!count)
            {
                obj.pm = result.c_str();
                return;
            }
        }
        else
        {
            obj.pm = result.c_str();
            return;
        }

        rez=DB->SendSQL(sql1.c_str());
        if(rez)
        { // поиск направления
            size_t count = rez->RecordCount;
            if (count)
            {
                if(result=="")
                {
                    result=Trim(rez->FieldByName("pm")->Value)+" ";
                }
                if(Trim(rez->FieldByName("napr")->Value)!=last)
                {
                    last=Trim(rez->FieldByName("napr")->Value);
                    result+=last.Trim();
                }
            }
            delete rez;
            rez = 0;
            if (!count)
            {
                obj.pm = result.c_str();
                return;
            }
        }
        else
        {
            obj.pm = result.c_str();;
            return;
        }

        rez=DB->SendSQL(sql2.c_str());
        if(rez&&rez->RecordCount)
        { // дописывание склада
            size_t count = rez->RecordCount;
            if (count)
            {
                if(result=="")
                {
                    result="1600?? "+Trim(rez->FieldByName("sklad")->Value);
                }
                else
                {
                    if(Trim(rez->FieldByName("sklad")->Value)!=last)
                    {
                        last=Trim(rez->FieldByName("sklad")->Value);
                        result+=last;
                    }
                }
            }
            delete rez;
            rez = 0;
            if (!count)
            {
                obj.pm = result.c_str();
                return;
            }
        }
        else
        {
            result=result+"напр???";
        }
    }
    else
    {
        rez=DB->SendSQL(sql.c_str());
        if(rez)
        { // расцеховка
            size_t count = rez->RecordCount;
            if (count)
            {
                for(rez->First(); !rez->Eof; rez->Next())
                {
                    if(Trim(rez->FieldByName("ceu")->Value)!=""&&Trim
                        (rez->FieldByName("ceu")->Value)!=last)
                    {
                        last=Trim(rez->FieldByName("ceu")->Value);
                        result+=last+" ";
                    }
                }
            }
            delete rez;
            rez = 0;
            if (!count)
            {
                obj.pm = result.c_str();
                return;
            }
        }
        else
        {
            obj.pm = result.c_str();
            return;
        }

        rez=DB->SendSQL(sql1.c_str());
        if(rez)
        {
            size_t count = rez->RecordCount;
            if (count)
            {
                for(rez->First(); !rez->Eof; rez->Next())
                {
                    if(result=="")
                    {
                        result=Trim(rez->FieldByName("pm")->Value)+" ";
                    }
                    if(Trim(rez->FieldByName("napr")->Value)!=last)
                    {
                        last=Trim(rez->FieldByName("napr")->Value);
                        result+=last.Trim();
                    }
                }
            }
            delete rez;
            rez = 0;
            if (!count)
            {
                result+="напр???";
            }
        }
        else
        {
            result+="напр???";
        }
    }
    obj.pm = AnsiString(result.Trim()).c_str();
}


void StatementsSet::CheckList   (bool &new_page,
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
        xl.toCells(1,   2,  Now().FormatString("dd.mm.yyyy"));
        xl.toCells(1,   3,  title.c_str());
        xl.toCells(1,   9,  VinToGost(obj.obd.c_str()));
        xl.toCells(1,   12, ("Заказ "+obj.zakaz).c_str());
        xl.toCells(1,   13, ("Партия "+obj.part_no).c_str());

        std::stringstream list;
        list << "Лист "<<list_no<<"/"<<max_page_no;
        xl.toCells(1, 15, list.str().c_str());

        cur_row = start_row;
    }
}

}
