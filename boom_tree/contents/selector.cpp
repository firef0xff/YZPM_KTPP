#include <vcl.h>
#pragma hdrstop

#include "selector.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------окно
__fastcall     TStSelect::TStSelect(TComponent* Owner,cSQL *db,IconsData *_IcoData,const int &State,const int &User)
    : TForm(Owner)
{
DB=db;
IcoData=_IcoData;
NextState=-1;
NextStateName="";
NextStateAccept=false;
String sql="Call constructions.GetNextStates('"+String(State)+"','"+String(User)+"')" ;
TADOQuery *rez=DB->SendSQL(sql);
if (rez&&rez->RecordCount)
    {
    rez->First();
    L1->Caption="\""+rez->FieldByName("CurrName")->Value+"\" изменить на";
    while (!rez->Eof)
        {
        ComboRow *row=new ComboRow(rez->FieldByName("NextState")->Value,rez->FieldByName("NextName")->Value,rez->FieldByName("NextAccept")->Value);
        CB1->Items->AddObject(row->GetStateName(),(TObject *)row);
        rez->Next();
        }
    }
delete rez;
}
__fastcall    TStSelect::~TStSelect(void)
{
ComboClear();
}
void         TStSelect::ComboClear(void)
{
TComboBox *cb=CB1;
for (int i = 0; i<cb->Items->Count; i++)
    {
    delete (ComboRow *)cb->Items->Objects[i];
    cb->Items->Delete(i);//очистить бокс
    i--;
    }
}

void __fastcall TStSelect::CB1Click(TObject *Sender)
{
TComboBox *cb=(TComboBox *)Sender;
ComboRow *row=(ComboRow *)cb->Items->Objects[cb->ItemIndex];  //вызов класса
if (row)
    {
    IMG->Picture->Bitmap=0;
    TImageList *ico=IcoData->GetStateList();
    ico->GetBitmap(IcoData->GetInList(row->GetStateID(),row->GetStateAccept(),0),IMG->Picture->Bitmap);
    }
}

void __fastcall TStSelect::BitBtn2Click(TObject *Sender)
{
TComboBox *cb=CB1;
int current=cb->Items->IndexOf(cb->Text);
if (current<0) {return;}
ComboRow *row=(ComboRow *)cb->Items->Objects[current];  //вызов класса
if (row)
    {
    NextState=row->GetStateID();
    NextStateName=row->GetStateName();
    NextStateAccept=row->GetStateAccept();
    }
}
