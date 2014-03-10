//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "workers.h"
#include "functions.h"
#include "EditWorkerData.h"
#include "EditWorkerGroup.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

__fastcall TWorkersSettings::TWorkersSettings(TComponent* Owner,cSQL *db,const int&_LUser)
	: TFrame(Owner),DB(db),LUser(_LUser)
{
	sgGroups->Cells[0][0] = "Группа";
	sgGroups->Cells[1][0] = "Кол-во";
	sgGroups->Cells[2][0] = "Расч.";
    AutoWidthSG(sgGroups);

	sgWorkers->Cells[0][0] = "Таб №";
	sgWorkers->Cells[1][0] = "Фамилия";
	sgWorkers->Cells[2][0] = "Имя";
	sgWorkers->Cells[3][0] = "Отчество";
	sgWorkers->Cells[4][0] = "Профессия";
	sgWorkers->Cells[5][0] = "Разряд";
	AutoWidthSG(sgWorkers);

    OnShow();
}
void TWorkersSettings::OnShow(void)
{
	LoadGroups();//загрузить список групп
    LoadWorkers();//загрузить список рабочих
}

void TWorkersSettings::LoadGroups(void)
{
    SGClear(sgGroups,1);
    ++sgGroups->RowCount;
    sgGroups->Cells[0][1] = "Все";
    sgGroups->Cells[1][1] = "...";
    sgGroups->Cells[2][1] = "...";
    TADOQuery *rez = DB->SendSQL("select "
                                 "convert(`a`.`group_id`, char) group_id, "
                                 "`a`.`name` name, "
                                 "convert(`a`.`p_kol`, char) p_kol, "
                                 "convert(count(`b`.`tab_no`), char) kol "
                                 "from `manufacture`.`worker_groups` `a` "
                                 "left join `manufacture`.`workers` `b` on `a`.`group_id` = `b`.`group_id` and `b`.`date_to` = '0000-00-00'"
                                 "group by `a`.`group_id`");
    if (rez)
    {
        for (rez->First(); !rez->Eof; rez->Next())
        {
			size_t row = sgGroups->RowCount-1;
            sgGroups->Cells[0][row] = rez->FieldByName("name")->Value;
            sgGroups->Cells[1][row] = rez->FieldByName("kol")->Value;
            sgGroups->Cells[2][row] = rez->FieldByName("p_kol")->Value;
			sgGroups->Cells[3][row] = rez->FieldByName("group_id")->Value;//id
            ++sgGroups->RowCount;
        }
		if (sgGroups->RowCount > 2)
            --sgGroups->RowCount;
        delete rez;
    }

    AutoWidthSG(sgGroups);
}
void TWorkersSettings::LoadWorkers(std::string group_id)
{
    SGClear(sgWorkers,1);
    std::stringstream sql;
    sql << "select "
           "convert(`a`.`tab_no`, char) tab_no,"
           "convert(`a`.`family`, char) family,"
           "convert(`a`.`name`, char) name,"
           "convert(`a`.`otch`, char) otch,"
           "convert(`a`.`razr`, char) razr,"
           "convert(`a`.`proff`, char) proff "
           "from `manufacture`.`workers` `a` "
		   "where `a`.`date_to` = '0000-00-00' ";
	if (!group_id.empty())
		sql << "and group_id = '"<<group_id<<"' ";
	sql << "order by tab_no";


    TADOQuery *rez = DB->SendSQL(sql.str().c_str());
    if (rez)
    {
        for (rez->First(); !rez->Eof; rez->Next())
        {
            size_t row = sgWorkers->RowCount-1;
            sgWorkers->Cells[0][row] = rez->FieldByName("tab_no")->Value;
            sgWorkers->Cells[1][row] = rez->FieldByName("family")->Value;
            sgWorkers->Cells[2][row] = rez->FieldByName("name")->Value;
            sgWorkers->Cells[3][row] = rez->FieldByName("otch")->Value;
            sgWorkers->Cells[4][row] = rez->FieldByName("proff")->Value;
            sgWorkers->Cells[5][row] = rez->FieldByName("razr")->Value;
            ++sgWorkers->RowCount;
        }
        if (sgWorkers->RowCount > 2)
            --sgWorkers->RowCount;
        delete rez;
    }

    AutoWidthSG(sgWorkers);
}
//---------------------------------------------------------------------------

void __fastcall TWorkersSettings::sgGroupsSelectCell(TObject *Sender, int ACol, int ARow,
          bool &CanSelect)
{
//
	LoadWorkers(AnsiString(sgGroups->Cells[3][ARow]).c_str());
}

//группы рабочих
void __fastcall TWorkersSettings::N1Click(TObject *Sender)
{
//добавить
    TWorkerGroup *wnd = new TWorkerGroup(this);
    if (wnd->ShowModal() == mrOk)
    {
        std::string group_name = AnsiString(wnd->group_name->Text).c_str();
        long r_kol = wnd->r_kol->Text.ToIntDef(0);

        TADOQuery *rez = DB->SendSQL(std::string("select count(*) as cnt from `manufacture`.`worker_groups` where name = '"+ group_name +"'").c_str());
        if (rez)
        {
            int cnt = (int)rez->FieldByName("cnt")->Value;
            if (!cnt)
            {
                std::stringstream sql;
                sql << "insert into `manufacture`.`worker_groups` (name,p_kol) values ('"<<group_name<<"','"<<r_kol<<"')";
                DB->SendCommand(sql.str().c_str());
            }
            delete rez;
        }
        LoadGroups();
    }
    delete wnd;
}
void __fastcall TWorkersSettings::N6Click(TObject *Sender)
{
//редактировать
    std::string group_id = AnsiString(sgGroups->Cells[3][sgGroups->Row]).c_str();
    if (group_id == "")
        return;

    TWorkerGroup *wnd = new TWorkerGroup(this);
    wnd->group_name->Text = sgGroups->Cells[0][sgGroups->Row];
    wnd->group_name->Enabled = false;
    wnd->r_kol->Text = sgGroups->Cells[2][sgGroups->Row];

    if (wnd->ShowModal() == mrOk)
    {
        long r_kol = wnd->r_kol->Text.ToIntDef(0);

        std::stringstream sql;
        sql << "update `manufacture`.`worker_groups` set p_kol = '"<<r_kol<<"' where group_id = '"<<group_id<<"'";
        DB->SendCommand(sql.str().c_str());

        LoadGroups();
    }
    delete wnd;
}
void __fastcall TWorkersSettings::N2Click(TObject *Sender)
{
//удалить
    std::string group_id = AnsiString(sgGroups->Cells[3][sgGroups->Row]).c_str();
    if (group_id == "")
        return;

    if ( MessageBoxA(this->Handle, "Удалить группу рабочих?", "Удалить группу рабочих?",MB_YESNO|MB_ICONQUESTION) == mrYes )
    {
        std::stringstream sql;
        sql << "delete from `manufacture`.`worker_groups` where group_id = '"<<group_id<<"'";
        DB->SendCommand(sql.str().c_str());

        LoadGroups();
    }
}

//рабочие
void __fastcall TWorkersSettings::N3Click(TObject *Sender)
{
//добавить
    TWorkerData *wnd = new TWorkerData(this, DB);
    if (wnd->ShowModal() == mrOk)
    {
        std::string tab_no          = AnsiString(wnd->tab_no->Text).c_str();
        std::string worker_family   = AnsiString(wnd->worker_family->Text).c_str();
        std::string worker_name     = AnsiString(wnd->worker_name->Text).c_str();
        std::string worker_otch     = AnsiString(wnd->worker_otch->Text).c_str();
        std::string razr            = AnsiString(wnd->razr->Text).c_str();
        std::string proff           = AnsiString(wnd->proff->Text).c_str();
        long group_id               = wnd->group_id;

        //если не задан табельный - послать
        DB->SendCommand(std::string("update `manufacture`.`workers` set date_to = now() "
                                "where tab_no = '"+tab_no+"' and date_to = '0000-00-00'").c_str());
        //если табельный задан, считать последнего активного рабочего с ним,
        //если такового нет то просто добавить новоро работягу
        //если таковой есть то закрыть его историю работы на этом номере

        std::stringstream sql;
        sql << "insert into `manufacture`.`workers` "
               "set date_from = now(), "
               "tab_no = '"<<tab_no<<"',"
               "razr = '"<<razr<<"',"
               "family = '"<<worker_family<<"',"
               "name = '"<<worker_name<<"',"
               "otch = '"<<worker_otch<<"',"
               "proff = '"<<proff<<"' ";
        if (group_id)
            sql << ", group_id = '"<<group_id<<"'";

        DB->SendCommand(sql.str().c_str());

        LoadGroups();
        LoadWorkers(AnsiString(sgGroups->Cells[3][sgGroups->Row]).c_str());
    }
    delete wnd;
}
void __fastcall TWorkersSettings::N4Click(TObject *Sender)
{
//редактировать
    TWorkerData *wnd = new TWorkerData(this, DB);

    wnd->tab_no->Text           = sgWorkers->Cells[0][sgWorkers->Row];
    wnd->tab_no->Enabled = false;
    wnd->worker_family->Text    = sgWorkers->Cells[1][sgWorkers->Row];
    wnd->worker_name->Text      = sgWorkers->Cells[2][sgWorkers->Row];
    wnd->worker_otch->Text      = sgWorkers->Cells[3][sgWorkers->Row];
    wnd->razr->Text             = sgWorkers->Cells[5][sgWorkers->Row];
    wnd->proff->Text            = sgWorkers->Cells[4][sgWorkers->Row];
    wnd->group_id               = sgGroups->Cells[3][sgGroups->Row].ToIntDef(0);
    for (size_t i = 0; i < wnd->ComboBox1->Items->Count; ++i)
    {
        if (wnd->group_id == ((GroupData *)wnd->ComboBox1->Items->Objects[i])->group_id)
        {
            wnd->ComboBox1->ItemIndex = i;
            break;
        }
    }
    if (wnd->ShowModal() == mrOk)
    {
        std::string tab_no          = AnsiString(wnd->tab_no->Text).c_str();
        std::string worker_family   = AnsiString(wnd->worker_family->Text).c_str();
        std::string worker_name     = AnsiString(wnd->worker_name->Text).c_str();
        std::string worker_otch     = AnsiString(wnd->worker_otch->Text).c_str();
        std::string razr            = AnsiString(wnd->razr->Text).c_str();
        std::string proff           = AnsiString(wnd->proff->Text).c_str();
        long group_id               = wnd->group_id;

        std::stringstream sql;
        sql << "update `manufacture`.`workers` "
               "set date_from = now(), "
               "razr = '"<<razr<<"',"
               "family = '"<<worker_family<<"',"
               "name = '"<<worker_name<<"',"
               "otch = '"<<worker_otch<<"',"
               "proff = '"<<proff<<"' ";
        if (group_id)
            sql << ", group_id = '"<<group_id<<"'";
        sql << "where tab_no = '"<<tab_no<<"' and date_to = '0000-00-00'";

        DB->SendCommand(sql.str().c_str());

        LoadGroups();
        LoadWorkers(AnsiString(sgGroups->Cells[3][sgGroups->Row]).c_str());
    }
    delete wnd;
}
void __fastcall TWorkersSettings::N5Click(TObject *Sender)
{
//удалить
    if ( MessageBoxA(this->Handle, "Удалить рабочего?", "Удалить рабочего?",MB_YESNO|MB_ICONQUESTION) == mrYes )
    {
        DB->SendCommand(AnsiString("update `manufacture`.`workers` set date_to = now() "
                                "where tab_no = '"+sgWorkers->Cells[0][sgWorkers->Row]+"' and date_to = '0000-00-00'"));

        LoadGroups();
        LoadWorkers(AnsiString(sgGroups->Cells[3][sgGroups->Row]).c_str());
    }
}
