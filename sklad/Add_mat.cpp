//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Add_mat.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
__fastcall     TMater_add::TMater_add(TComponent* Owner,cSQL *db,const int &_LUser)
    : TForm(Owner),DB(db),LUser(_LUser)
{
L1->Caption="";
TADOQuery *rez=DB->SendSQL("Select max(right(obd,4)) as id from constructions.det_names where obd like 'NA____'");
int rec=0;
if (rez&&rez->RecordCount)
    {
    rec=Trim(rez->FieldByName("id")->Value).ToInt();
    rec++;
    }
L1->Caption=String(rec);
while (L1->Caption.Length()<4)
    {
    L1->Caption="0"+L1->Caption;
    }
L1->Caption="NA"+L1->Caption;
delete rez;
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
    DB->SendCommand("Call save_tmp_material('"+String(LUser)+"','"+L1->Caption+"','"+LE1->Text.Trim()+"','"+LE2->Text.Trim()+"','"+LE3->Text.Trim()+"','"+LE4->Text.Trim()+"','"+String((int)ei->Items->Objects[ei->ItemIndex])+"')");
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

