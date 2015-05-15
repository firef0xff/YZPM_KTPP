//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "log.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

__fastcall TLogForm::TLogForm(TComponent* Owner,cSQL *DB)
    : TForm(Owner)
{
	this->DB = DB;
	this->repaintText();
}

void TLogForm::repaintText()
{
	Memo1->Lines->Clear();

	vector <String> log = this->DB->Get_log();
	for (vector <String>::iterator i =log.begin(); i <log.end(); i++){
		Memo1->Lines->Add(*i);
	}
}

void __fastcall TLogForm::ClearClick(TObject *Sender)
{
	this->DB->clearLog();
	this->repaintText();
}
//---------------------------------------------------------------------------

