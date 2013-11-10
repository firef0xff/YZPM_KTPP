//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "RightSelect.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

__fastcall TfselRight::TfselRight(TComponent* Owner,cSQL *db,String GroupID)
	: TForm(Owner),DB(db)
{
//заполнение комбы с группами
	cbRight->Items->Clear();
	String  sql=L"call administration.Get_new_Group_right('"+GroupID+"')";
	TADOQuery *rez=DB->SendSQL(sql);
	if (rez&&rez->RecordCount)
	{
		for (rez->First(); !rez->Eof; rez->Next())
		{
			cbRight->Items->AddObject(rez->FieldByName("Name")->Value,nullptr);
		}
		cbRight->ItemIndex=0;
	}
	delete rez;
}
//---------------------------------------------------------------------------
