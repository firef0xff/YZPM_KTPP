//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Add_mat.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
__fastcall     TMater_add::TMater_add(TComponent* Owner,cSQL *db,const int &_LUser, long number)
    : TForm(Owner),DB(db),LUser(_LUser)
{
L1->Caption="";
L1->Caption=String(number);
while (L1->Caption.Length()<15)
{
    L1->Caption="0"+L1->Caption;
}
}
void          TMater_add::Load_support_info(void)
{
ei->Items->Clear();
TADOQuery *rez=DB->SendSQL("Call catalogs.Get_ei_list('"+(String)ei_opt->ItemIndex+"')");
if (rez&&rez->RecordCount)
    {
    for (rez->First(); !rez->Eof; rez->Next())
        {
        ei->Items->AddObject(rez->FieldByName("text")->Value,(TObject *)rez->FieldByName("id")->Value.operator int());
        }
    }
delete rez;
}
void __fastcall TMater_add::BitBtn1Click(TObject *Sender)
{
if (ei->ItemIndex&&(LE1->Text.Trim()!=""||LE2->Text.Trim()!=""||LE3->Text.Trim()!=""||LE4->Text.Trim()!=""))
    {
    DB->SendCommand("Call sklad.save_tmp_material('"+String(LUser)+"','"+L1->Caption+"','"+LE1->Text.Trim()+"','"+LE2->Text.Trim()+"','"+LE3->Text.Trim()+"','"+LE4->Text.Trim()+"','"+String((int)ei->Items->Objects[ei->ItemIndex])+"')");
    }else
    {
    ShowMessage("Не введены все необходимые данные.");
    }
}
void __fastcall TMater_add::ei_optClick(TObject *Sender)
{
Load_support_info();
}
//---------------------------------------------------------------------------


void __fastcall TMater_add::bAddSymbolClick(TObject *Sender)
{
	TSymbol *wnd=new TSymbol(this);
	wnd->ShowModal();
	if(wnd->ModalResult==mrOk)
	{
		LE1->Text = LE1->Text + wnd->E1->Text.Trim();
	}
	delete wnd;
}
//---------------------------------------------------------------------------

