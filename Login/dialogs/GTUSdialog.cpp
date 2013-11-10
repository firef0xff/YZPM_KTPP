//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "GTUSdialog.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

__fastcall TGTUSGroupSelector::TGTUSGroupSelector(TComponent* Owner,cSQL *db,String Table,String param)
	: TForm(Owner),DB(db)
{
	cbGroups->Items->Clear();
	String sql=	"select GroupName,GroupID from administration.privileges a "
				"left join administration."+Table+" b on a.GroupID=b.IdGroup and b.IdCond="+param+" "
				"where b.IdGroup is null "
				"ORDER BY GroupName ";
	TADOQuery *rez=DB->SendSQL(sql);
	if (rez&&rez->RecordCount)
	{
		for (rez->First(); !rez->Eof; rez->Next())
		{
			cbGroups->Items->AddObject(rez->FieldByName("GroupName")->Value.operator UnicodeString(),
										(TObject*)rez->FieldByName("GroupID")->Value.operator int());
		}
	}
	delete rez;
	Name="";
	ID=0;
}

void __fastcall TGTUSGroupSelector::BitBtn1Click(TObject *Sender)
{
	if (cbGroups->ItemIndex>=0)
	{
		Name=cbGroups->Items->operator [](cbGroups->ItemIndex);
		ID=(int)cbGroups->Items->Objects[cbGroups->ItemIndex];
		ModalResult=mrOk;
	}else
	{
		ModalResult=mrCancel;
	}
	CloseModal();
}
//---------------------------------------------------------------------------

