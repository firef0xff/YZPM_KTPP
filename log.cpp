//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "log.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

__fastcall TLogForm::TLogForm(TComponent* Owner,vector <String> log)
    : TForm(Owner)
{
Memo1->Lines->Clear();
for (vector <String>::iterator i =log.begin(); i <log.end(); i++)
    {
    Memo1->Lines->Add(*i);
    }
}

