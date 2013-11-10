//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "NextStateSelector.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
__fastcall TNext_State_Selector::TNext_State_Selector(TComponent* Owner,cSQL *db,String param,bool edit)
	: TForm(Owner),DB(db)
{
	cbConditions->Enabled=edit;
	if (!edit)
	{
		//получить список состояний не занятых
		String sql=	"select a.name,a.idsost "
					"from administration.conditions a "
					"left join administration.treeconds b on b.IdNextCond=a.idsost and b.IdCond="+param+" "
					"where b.IdNextCond is null and a.idsost!="+param+" "
					"order by a.name ";
		TADOQuery *rez=DB->SendSQL(sql);
		if (rez&&rez->RecordCount)
		{
			for (rez->First(); !rez->Eof; rez->Next())
			{
				cbConditions->Items->AddObject(rez->FieldByName("name")->Value.operator UnicodeString(),
											(TObject*)rez->FieldByName("idsost")->Value.operator int());
			}
		}
		delete rez;
	}
	Edit=edit;
	Name="";
	type="basic";
	ID=0;
}
//---------------------------------------------------------------------------
void __fastcall TNext_State_Selector::BitBtn1Click(TObject *Sender)
{
	if (cbConditions->ItemIndex>=0||Edit)
	{
		if (cbConditions->ItemIndex>=0)
		{
			Name=cbConditions->Items->operator [](cbConditions->ItemIndex);
			ID=(int)cbConditions->Items->Objects[cbConditions->ItemIndex];
		}
		switch (cbType->ItemIndex)
		{
			case 0:{type="basic";break;}
			case 1:{type="optional";break;}
		default:;
		}
		ModalResult=mrOk;
	}else
	{
		ModalResult=mrCancel;
	}
	CloseModal();
}
//---------------------------------------------------------------------------

