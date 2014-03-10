//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "EditWorkerData.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"


__fastcall TWorkerData::TWorkerData(TComponent* Owner, cSQL *DB)
    : TForm(Owner),group_id(0)
{
	TADOQuery *rez = DB->SendSQL("select group_id, name from `manufacture`.`worker_groups`");
	ComboBox1->Items->Clear();
    if (rez)
    {
        for (rez->First(); !rez->Eof; rez->Next())
		{
			GroupData *ptr = new GroupData();
            ptr->group_name = (rez->FieldByName("name")->Value.operator AnsiString()).c_str();
			ptr->group_id = rez->FieldByName("group_id")->Value.operator int() ;
			ComboBox1->Items->AddObject(ptr->group_name.c_str(), ptr);
        }
        delete rez;
    }
}

__fastcall TWorkerData::~TWorkerData()
{
    for (size_t i = 0; i < ComboBox1->Items->Count; ++i)
    {
		delete ComboBox1->Items->Objects[i];
	}
    ComboBox1->Items->Clear();
}

void __fastcall TWorkerData::ComboBox1Click(TObject *Sender)
{
	if (ComboBox1->ItemIndex >= 0)
	{
		group_id = ((GroupData *)ComboBox1->Items->Objects[ComboBox1->ItemIndex])->group_id;
	}
}
//---------------------------------------------------------------------------

