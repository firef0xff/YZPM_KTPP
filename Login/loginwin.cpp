//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "loginwin.h"
#pragma package(smart_init)
#pragma resource "*.dfm"

//---------------------------------------------------------------------------
__fastcall TLogIn::TLogIn(TComponent* Owner,cSQL *db)
    : TForm(Owner),DB(db),logcount(0)
{
TADOQuery *rez=DB->SendSQL("Select login from administration.logins where pass!=''");
if (rez&&rez->RecordCount)
for (rez->First(); !rez->Eof; rez->Next())
    {
    log->Items->Add(rez->FieldByName("login")->Value);
    }
delete rez; rez=0;
}

void __fastcall TLogIn::BitBtn1Click(TObject *Sender)
{
#ifdef NODB
    ModalResult=mrOk;
    CloseModal();
    return;
#endif

String sql="";
sql="Select * from administration.logins Where login=\'"+Trim(log->Text)+"\' and pass=PASSWORD(\'"+pas->Text+"\')";
TADOQuery *rez=DB->SendSQL(sql);
if (rez&&rez->RecordCount)
    {
    log->Text=rez->FieldByName("LogIn")->Value;
    if (rez->FieldByName("status")->Value=="online")
        {
        ShowMessage("���� �� ������ ��� �������� �� \n 1 ���� ����� ��� ���������� ���� ����� \n 2 ���� ��������� ���� ��������� �� ���������.");
        }
    sql="update administration.logins set status='online',lastjoin=CURDATE() where login=\'"+Trim(log->Text)+"\' and pass=PASSWORD(\'"+pas->Text+"\')";
    DB->SendCommand(sql);
    UserID=rez->FieldByName("LogID")->Value;
    delete rez; rez=0;
    ModalResult=mrOk;
    CloseModal();
    }else
    {
    ShowMessage("�� ������ ��� ������������ �/��� ������");
    pas->Text="";
    logcount++;
    if (logcount>=5)
        {
        ModalResult=mrNo;
        Close();
        }
    }
}
