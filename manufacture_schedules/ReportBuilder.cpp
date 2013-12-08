//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ReportBuilder.h"
#include <functions.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

ReportList::Report test_report0("rep_4056", "Маршрутные ведомости1",STARTUP|ORDER|PART|PRODUCT);
ReportList::Report test_report1("rep_4057", "Маршрутные ведомости2",STARTUP|ORDER|PART);
ReportList::Report test_report2("rep_4058", "Маршрутные ведомости3",STARTUP|ORDER|PART|PRODUCT);
ReportList::Report test_report3("rep_4059", "Маршрутные ведомости4",STARTUP|ORDER|PART);
ReportList::Report test_report4("rep_40510","Маршрутные ведомости5",STARTUP|ORDER|PART);
ReportList::Report test_report5("rep_40511","Маршрутные ведомости6",STARTUP|ORDER|PART|PRODUCT);
ReportList::Report test_report6("rep_40512","Маршрутные ведомости7",STARTUP|ORDER|PART);
ReportList::Report test_report7("rep_40513","Маршрутные ведомости8",STARTUP|ORDER|PART|PRODUCT);


__fastcall TReports::TReports(TComponent* Owner, Reports_set set, __uint64  id )
	: TForm(Owner)
{
    ReportList::ReportsSet reps = ReportList::Instance().GetReports(set);

	ReportsList->Items->Clear();
	for (ReportList::ReportsSet::const_iterator it = reps.begin(); it != reps.end(); ++it)
	{
		ReportsList->Items->AddObject((*it)->rep_name.c_str(),(TObject *)*it);
	}
	if (ReportsList->Items->Count)
	{
		ReportsList->ItemIndex = 0;
	}
}
//---------------------------------------------------------------------------
void __fastcall TReports::AddClick(TObject *Sender)
{
	if (ReportsList->ItemIndex >= 0)
	{
        ReportList::Report *ptr = (ReportList::Report *)ReportsList->Items->Objects[ReportsList->ItemIndex];

        boost::shared_ptr<TSchedule> t(new TSchedule(ptr->func_name,ptr->rep_name));
        t->AddVar("var1","val1");
        t->AddVar("var2","val2");
        t->AddVar("var3","val3");
        schedules.push_back(t);
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
        boost::shared_ptr<TSchedule> ptr= *it;
        int row = ScheduleSG->RowCount-1;
        ScheduleSG->Cells[1][row] = ptr->ReportName().c_str();
        ScheduleSG->Cells[2][row] = ptr->GetVariables().c_str();

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
//---------------------------------------------------------------------------

