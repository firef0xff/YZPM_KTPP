#include <vcl.h>
#pragma hdrstop

#include "test.h"
#include "otchetnost.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
#include "Add_zak.h"
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	ADC->ConnectionString="FILE NAME="+ExtractFileDir(Application->ExeName)+
			"\\lib\\connect.udl";
	DB=new cSQL(ADC);
	DB->Connect();
}
void __fastcall TForm1::RepStartClick(TObject *Sender)
{
	cReports *rep=new cReports(DB);
	rep->CreateReport(RepNo->Text.ToIntDef(0),Obd->Text);
}

void __fastcall TForm1::GetLogClick(TObject *Sender)
{
	vector <String> log=DB->Get_log();
	Log->Lines->Clear();
	for (vector <String>::iterator i=log.begin(); i<log.end(); i++)
	{
		Log->Lines->Add(*i);
	}
}

void __fastcall TForm1::ClearLogClick(TObject *Sender)
{
	DB->Get_log().clear();
	GetLog->Click();
}
//---------------------------------------------------------------------------

