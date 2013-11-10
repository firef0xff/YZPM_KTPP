#include <vcl.h>
#pragma hdrstop
#include "otchethost.h"
#pragma package(smart_init)
#pragma resource "*.dfm"

__fastcall TOtchet::TOtchet(TComponent* Owner,String obd)
	: TForm(Owner)
{
LE1->Text=obd;
}
void __fastcall TOtchet::BitBtn1Click(TObject *Sender)
{
if (LE1->Text.Trim()!="")
	{
	ModalResult=mrOk;
	CloseModal();
	}else {ShowMessage("¬ведите обозначение узла.");}
}
//---------------------------------------------------------------------------
