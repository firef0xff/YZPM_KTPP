//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ReportBuilder.h"
#include "report_params.h"
#include <functions.h>
#include <reports/exsemplars/routelist.h>
#include <reports/exsemplars/label.h>
#include <reports/exsemplars/f_140005.h>
#include <reports/exsemplars/f_140003.h>
#include <reports/exsemplars/y09102.h>
#include <reports/exsemplars/single_application.h>
#include <reports/exsemplars/materaials_detail.h>
#include <reports/exsemplars/trud_report.h>
#include <reports/exsemplars/zakaz_trud_report.h>
#include <reports/exsemplars/making_details.h>
#include <reports/exsemplars/making_summary.h>
#include <reports/exsemplars/complects.h>
#include <reports/exsemplars/statements_set.h>
#include <reports/exsemplars/manufacturing_details.h>
#include <reports/exsemplars/rep16.h>
#include <reports/exsemplars/rep17.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

rep::RouteList rep1(STARTUP|ORDER|PART|PRODUCT);
rep::Lable rep2(STARTUP|ORDER|PART|PRODUCT);
rep::F140005 rep3(STARTUP|ORDER|PART);
rep::F140003 rep4(STARTUP|ORDER|PART);
rep::Y09102 rep5(STARTUP|ORDER|PART);
rep::SingleApplication rep_6(STARTUP|ORDER|PART);
rep::MaterialsDetail rep_7 (STARTUP|ORDER|PART);
rep::TrudReport rep_81 (STARTUP|ORDER|PART);
rep::ZakazTrudReport rep_91 (STARTUP|ORDER|PART);
rep::TrudReport2 rep_8 (STARTUP|ORDER|PART);
rep::ZakazTrudReport2 rep_9 (STARTUP|ORDER|PART);
rep::MakingDetails rep_10 (STARTUP|ORDER|PART);
rep::MakingSummary rep_11 (STARTUP|ORDER|PART);
rep::Complect05    rep12  (STARTUP|ORDER|PART);
rep::Complect06    rep13  (STARTUP|ORDER|PART);
rep::StatementsSet rep14  (STARTUP|ORDER|PART);
rep::ManufacturingDetails rep15  (STARTUP|ORDER|PART);
rep::Rep16 rep16  (STARTUP|ORDER|PART);
rep::Rep17 rep17  (STARTUP|ORDER|PART);
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

