//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "FormAddZag.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormAddZagCode *FormAddZagCode;
//---------------------------------------------------------------------------
__fastcall TFormAddZagCode::TFormAddZagCode(TComponent* Owner,cSQL *db, int parentID)
	: TForm(Owner),DB(db), pID(parentID)
{
	cbUse->Items->Clear();
	int firstItemID = 0;

	TADOQuery *rez=DB->SendSQL("select * from `billets`.`vz_groups`");
	if (rez&&rez->RecordCount)
	{
		for (rez->First(); !rez->Eof; rez->Next())
		{
			cbUse->Items->AddObject(rez->FieldByName("name")->Value,(TObject *)rez->FieldByName("vz_grp_id")->Value.operator int());
		}
	}

	delete rez;

	if(cbUse->Items->Count > 0) cbUse->ItemIndex = 0;
}
//---------------------------------------------------------------------------

void __fastcall TFormAddZagCode::bOkClick(TObject *Sender)
{
	if((eCode->Text != "") && (eName->Text != ""))
	{
		DB->SendCommand("insert into `billets`.`vz_tree` (`kod`, `name`, `parent`, `vz_grp_id`) values('" + eCode->Text + "', '" + eName->Text + "', '" + IntToStr(pID) + "', '" + IntToStr((int)cbUse->Items->Objects[cbUse->ItemIndex]) + "')");
        ModalResult=mrOk;
	}
}
//---------------------------------------------------------------------------

