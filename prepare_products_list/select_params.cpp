//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "select_params.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

__fastcall TList_sel_params::TList_sel_params(TComponent *Owner,
	const int &_LUser, cSQL *db):TForm(Owner), LUser(_LUser), DB(db)
{
	cd_max->Date=Date();
	cd_min->Date=Date();
	ud_max->Date=Date();
	ud_min->Date=Date();
	sortparams="";
		// предмет договора
	Type->Items->Clear();
	TADOQuery *rez=DB->SendSQL("call processed_list.Get_aval_types("+String(LUser)+")");
	if(rez&&rez->RecordCount)
		{
		for(rez->First(); !rez->Eof; rez->Next())
			{
			Type->Items->AddObject(rez->FieldByName("Type_Name")->Value,(TObject *)rez->FieldByName("Type_ID")->Value.operator int());
			}
		}
	delete rez;
	rez=DB->SendSQL("call processed_list.Get_aval_States("+String(LUser)+")");
	if(rez&&rez->RecordCount)
		{
		for(rez->First(); !rez->Eof; rez->Next())
			{
			State->Items->AddObject(rez->FieldByName("State_Name")->Value,(TObject *)rez->FieldByName("State_ID")->Value.operator int());
			}
		}
	delete rez;
}
__fastcall TList_sel_params::~TList_sel_params(void)
{
}
void __fastcall TList_sel_params::OKClick(TObject *Sender)
{
	String add=" and ";
	if(b_type->Checked&&Type->ItemIndex>=0)
	{
		/* if (sortparams=="")
		 {
			 sortparams="Where ";
			 add=" ";
		 }else
		 {
			add=" and ";
		 } */
		sortparams=sortparams+add+"(a.type='"+
			String((int)Type->Items->Objects[Type->ItemIndex])+"')";
	}
	if(b_State->Checked&&State->ItemIndex>=0)
	{
		/* if (sortparams=="")
		 {
			 sortparams="Where ";
			 add=" ";
		 }else
		 {
			add=" and ";
		 } */
		sortparams=sortparams+add+"(a.type='"+
			String((int)State->Items->Objects[State->ItemIndex])+"')";
	}
	if(b_cd->Checked)
	{
		/*if (sortparams=="")
		{
			sortparams="Where ";
			add=" ";
		}else
		{
			add=" and ";
		}  */
		sortparams=sortparams+add+"(a.CreateDate BETWEEN '"
							+cd_min->Date.FormatString("yyyy-mm-dd")+"' and '"
							+cd_max->Date.FormatString("yyyy-mm-dd")+"')";
	}
	if(b_ud->Checked)
	{
		/*if (sortparams=="")
		{
			sortparams="Where ";
			add=" ";
		}else
		{
			add=" and ";
		}     */
		sortparams=sortparams+add+"(a.UpdateDate BETWEEN '"
							+ud_min->Date.FormatString("yyyy-mm-dd")+"' and '"
							+ud_max->Date.FormatString("yyyy-mm-dd")+"')";
	}
}
