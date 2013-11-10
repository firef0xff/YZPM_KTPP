//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "List_add.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

__fastcall TListAdd::TListAdd(TComponent *Owner,const int &_LUser, cSQL *db):TForm(Owner), LUser(_LUser), DB(db)
{
        // предмет договора
    Type->Items->Clear();
    TADOQuery *rez=
        DB->SendSQL
        ("call processed_list.Get_aval_types("+String(LUser)+")");
    if(rez&&rez->RecordCount)
        {
        for(rez->First(); !rez->Eof; rez->Next())
            {
            Type->Items->AddObject(rez->FieldByName("Type_Name")->Value,(TObject *)rez->FieldByName("Type_ID")->Value.operator int());
            }
        }
    delete rez;
}
__fastcall TListAdd::~TListAdd(void)
{

}
void __fastcall TListAdd::OKClick(TObject *Sender)
{
    if (Type->ItemIndex>=0)
    {
        DB->SendCommand("call processed_list.Add_list('"+String((int)Type->Items->Objects[Type->ItemIndex])+"','"+String(LUser)+"')");
    }
}
//---------------------------------------------------------------------------

