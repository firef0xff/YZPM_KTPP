//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "User_Data.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

//---------------------------------------------------------------------------
__fastcall TUserData::TUserData(TComponent* Owner,cSQL *DB)
    : TForm(Owner)
{
    cbGroup->Clear();
    TADOQuery *rez=DB->SendSQL("Select GroupName,GroupID from administration.privileges order by GroupName");
    if (rez&&rez->RecordCount)
    {
        for (rez->First(); !rez->Eof; rez->Next())
        {
            String name=rez->FieldByName("GroupName")->Value;
            int id=rez->FieldByName("GroupID")->Value;
            cbGroup->Items->AddObject(name,(TObject *)id);
        }
    }
    cbGroup->ItemIndex=-1;
    delete rez;
}
void __fastcall TUserData::BitBtn1Click(TObject *Sender)
{
    if (leLogin->Text.Trim()!=""&&cbGroup->ItemIndex!=-1)
    {
        ModalResult=mrOk;
        CloseModal();
    }else
    {
        MessageBox(Handle,_T("Укажите логин и группу пользователя"),_T("Внимание!"),MB_ICONWARNING|MB_OK);
    }
}
