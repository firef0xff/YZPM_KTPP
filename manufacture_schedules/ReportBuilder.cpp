﻿//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ReportBuilder.h"
#include "report_params.h"
#include <functions.h>
#include <reports/exsemplars/routelist.h>o
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

rep::RouteList per1(STARTUP|ORDER|PART|PRODUCT);
//fake::FakeReport test_report0(STARTUP|ORDER|PART|PRODUCT);

__fastcall TReports::TReports(TComponent* Owner,cSQL *DB, Reports_set set, __uint64  id, __uint64  sub_id )
    : TForm(Owner),selected_set(set),object_id(id),element_id(sub_id)
{
    rep::ReportList::ConstReportsSet reps = rep::ReportList::Instance().GetReports(set);
    rep::ReportList::Instance().DbConnection(DB);

	ReportsList->Items->Clear();

    for (rep::ReportList::ConstReportsSet::const_iterator it = reps.begin(); it != reps.end(); ++it)
	{
		ReportsList->Items->AddObject((*it)->Name().c_str(),(TObject *)*it);
	}
	if (ReportsList->Items->Count)
	{
		ReportsList->ItemIndex = 0;
	}

    SGClear(ScheduleSG);
	ScheduleSG->Cells[1][0] = "Отчет";
    ScheduleSG->Cells[2][0] = "Параметры";
    AutoWidthSG(ScheduleSG);
}
//---------------------------------------------------------------------------
void __fastcall TReports::AddClick(TObject *Sender)
{
	if (ReportsList->ItemIndex >= 0)
	{
        rep::Report *ptr = (rep::Report *)ReportsList->Items->Objects[ReportsList->ItemIndex];

        boost::shared_ptr<rep::Report> t(ptr->SelfCopy());

        TRepParams *wnd = new TRepParams(this,t->Params());
        if (wnd->NoParams() || wnd->ShowModal() == mrOk)
        {
            schedules.push_back(t);
        }
        delete wnd;
	}
    UpdateRepListSG();
}

void __fastcall TReports::ScheduleSGDblClick(TObject *Sender)
{
    int ofset = ScheduleSG->Row - 1;

    if (ofset >= 0 && ofset < schedules.size())
    {
        ScheduleList::iterator it = schedules.begin() + ofset;

        if (it != schedules.end())
        {
            boost::shared_ptr<rep::Report> t = *it;
            rep::Report::ParamList tmp = t->Params();
            TRepParams *wnd = new TRepParams(this,tmp);
            if (wnd->NoParams() || wnd->ShowModal() == mrOk)
            {
                t->Params() = tmp;
            }
            delete wnd;
        }
    }
    UpdateRepListSG();
}

void __fastcall TReports::DelClick(TObject *Sender)
{
    int ofset = ScheduleSG->Row - 1;
	if (ofset >= 0 && ofset < schedules.size())
    {
        ScheduleList::iterator it = schedules.begin() + ofset;

        if (it != schedules.end())
        {
            schedules.erase(it);
        }
    }
    UpdateRepListSG();
}

void TReports::UpdateRepListSG (void)
{
	int old_row = ScheduleSG->Row;
    SGClear(ScheduleSG);

    for (ScheduleList::const_iterator it = schedules.begin(); it != schedules.end(); ++it)
    {
        boost::shared_ptr<rep::Report> ptr= *it;
        int row = ScheduleSG->RowCount-1;
        ScheduleSG->Cells[1][row] = ptr->Name().c_str();
        ScheduleSG->Cells[2][row] = ptr->ParamsValues().c_str();

        ++ScheduleSG->RowCount;
    }

    if (ScheduleSG->RowCount > 2)
    {
		--ScheduleSG->RowCount;
    }

	AutoWidthSG(ScheduleSG);

	if (old_row > ScheduleSG->RowCount -1) 
	{
		old_row = ScheduleSG->RowCount -1;		
	}
	ScheduleSG->Row = old_row;
}

void __fastcall TReports::ScheduleSGDrawCell(TObject *Sender, int ACol, int ARow,
          TRect &Rect, TGridDrawState State)
{
//
}

void __fastcall TReports::BuildClick(TObject *Sender)
{
    for (ScheduleList::const_iterator it = schedules.begin(),end = schedules.end(); it!=end; ++it)
    {
        const boost::shared_ptr<rep::Report> ptr = *it;
        ptr->Params()[REPORT_OBJECT_ID] = AnsiString(object_id).c_str();
        ptr->Params()[REPORT_ELEMENT_ID] = AnsiString(element_id).c_str();
        ptr->Params()[REPORT_OBJECT_TYPE] = AnsiString(selected_set).c_str();

        try
        {
            ptr->Build();
        }
        catch (std::runtime_error &e)
        {
            ShowMessage(e.what());
        }
    }
}
//---------------------------------------------------------------------------

