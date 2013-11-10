

#include <vcl.h>
#pragma hdrstop

#include "DetSelector.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

__fastcall TObdSelector::TObdSelector(TComponent* Owner,ClassConnector *const Own,TWinControl *_p,cSQL *const db,char _ListSize):
TFrame(Owner),DB(db),ListSize(_ListSize),owner(Own)
{
static int count=0;
count++;
Name=Name+String(count);
Align=alClient;
Parent=_p;
}
__fastcall TObdSelector::~TObdSelector()
{
ComboClear();
}
void __fastcall TObdSelector::FastNavigatorClick(TObject *Sender)
{
TComboBox *cb=(TComboBox *)Sender;
if (!cb->Tag)
    {
    Obd *tmp=new Obd(*((Obd *)cb->Items->Objects[cb->ItemIndex]));
    LoadDet(tmp);
    }
}
void __fastcall TObdSelector::FastNavigatorDropDown(TObject *Sender)
{
TComboBox *cb=(TComboBox *)Sender;
cb->Tag=0;
}
void __fastcall TObdSelector::FastNavigatorKeyPress(TObject *Sender, wchar_t &Key)

{
TComboBox *cb=(TComboBox *)Sender;
if (Key==13)
    {
    SetText(cb->Text);
    }else
    {
    cb->Tag=1;
    }
}
void __fastcall TObdSelector::SpChange(TObject *Sender)
{
TSpeedButton *sb=(TSpeedButton *)Sender;
TComboBox *cb=FastNavigator;
if (!cb->Items->Count) {return;}
int current=cb->ItemIndex;
int count=cb->Items->Count;
if (sb->Tag)
    {
    if (current==0)
        {
        current=count-1;
        }else
        {
        current--;
        }
    }else
    {
    if (current==count-1)
        {
        current=0;
        }else
        {
        current++;
        }
    }
Obd *f=(Obd *)cb->Items->Objects[current];  //вызов класса
if (f->UpdateVal())
    {
    cb->ItemIndex=current; //показать вставленное
    owner->Load(f);
    }else
    {
    delete f;
    cb->Items->Delete(current);
    cb->ItemIndex=0;
    SpChange(Sender);
    }
}
void              TObdSelector::SetText(const String &Text)
{
Obd *tmp=new Obd(DB,Text);
if (!tmp->CanUse()){delete tmp;return;}
LoadDet(tmp);
}
void               TObdSelector::LoadDet  (Obd *det)
{
TComboBox *cb=FastNavigator;
//если есть деталь то вставить в очередь массива
for (int i = 0; i<cb->Items->Count; i++)
    {
    if (cb->Items->operator [](i)==det->Get_Obd(true))
        {
        delete (Obd *)cb->Items->Objects[i];
        cb->Items->Delete(i);//удалить повторение
        i--;
        }
    }
int count=cb->Items->Count;
if (count>ListSize)
    {
    delete (Obd *)cb->Items->Objects[count-1];
    cb->Items->Delete(count-1);//удалить повторение
    }
if (det->UpdateVal())
    {
    cb->Items->InsertObject(0,det->Get_Obd(true),(TObject*)det);//вставить текст в первый итем
    cb->ItemIndex=0;                    //показать вставленное
    cb->SelStart=cb->Text.Length();       // установить курсор в последнюю позицию
    owner->Load(det);
    }else{delete det;}
}
void              TObdSelector::ComboClear()
{
TComboBox *cb=FastNavigator;
for (int i = 0; i<cb->Items->Count; i++)
    {
    delete (Obd *)cb->Items->Objects[i];
    cb->Items->Delete(i);//очистить бокс
    i--;
    }
}
