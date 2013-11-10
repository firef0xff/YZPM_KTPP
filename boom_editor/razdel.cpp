#include <vcl.h>
#pragma hdrstop
#include "razdel.h"
#include "SPEdit.h"
#pragma package(smart_init)
#pragma resource "*.dfm"
__fastcall Trzd::Trzd(TComponent* Owner,TADOQuery *_SpRazd)
	: TForm(Owner),SpRazd(_SpRazd)
{
RazdName="";
RazdID=0;
CB1->Items->Clear();
CB1->Text="";
if (SpRazd&&SpRazd->RecordCount)
	{
	for (SpRazd->First(); !SpRazd->Eof; SpRazd->Next())
		{
		CB1->Items->AddObject(SpRazd->FieldByName("RazdName")->Value,(TObject*)SpRazd->FieldByName("RazdID")->Value.operator int());
		}
	}
}
void __fastcall Trzd::BitBtn1Click(TObject *Sender)
{
if (CB1->ItemIndex>=0)
	{
	RazdName=Trim(CB1->Text);
	RazdID=(int)CB1->Items->Objects[CB1->ItemIndex];
	}
}


