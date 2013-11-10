//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "kol_det.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
__fastcall Tkoldet::Tkoldet(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall Tkoldet::CB1Click(TObject *Sender)
{
// 
GetKol();
if (CB1->Text==""){return;}
String sql="Call temporary_tables.Get_zakaz_list('"+GostToVin(CB1->Text)+"')";
TADOQuery *rez=DB->SendSQL(sql);
rez->First();
CB2->Items->Clear();
CB2->Items->Add("");
while (!rez->Eof)
    {
    CB2->Items->Add(rez->FieldByName("zakaz")->Value);
    rez->Next();
    }
delete rez;
}
//---------------------------------------------------------------------------
void __fastcall Tkoldet::CB2Click(TObject *Sender)
{
//получение списка узлов по заазу   
GetKol();
if (CB2->Text.Length()<6) {return;}
String sql="Call temporary_tables.Get_obd_from_zaka('"+CB2->Text+"')";
TADOQuery *rez=DB->SendSQL(sql);
rez->First();
CB1->Items->Clear();
CB1->Items->Add("");
while (!rez->Eof)
    {
    CB1->Items->Add(VinToGost(rez->FieldByName("obd")->Value));
    rez->Next();
    }    
delete rez;
}
void __fastcall Tkoldet::GetKol(void)
{
// вывод количества деталей  
String sql;
if (CB1->Text.Trim()!="") 
    {
    sql="call temporary_tables.kol_det_obu('"+GostToVin(CB1->Text)+"','"+obd+"')";
    }else
    {
    if (CB2->Text!="")
        {
        sql="call temporary_tables.kol_det('"+CB2->Text+"','"+obd+"')";
        }else {E1->Text=""; return;}
    }
TADOQuery *rez=DB->SendSQL(sql);
rez->First();
if (rez->RecordCount)
    {
    E1->Text=rez->FieldByName("kol")->Value;
    }else
    {
    E1->Text="";
    }
delete rez;

}
void __fastcall Tkoldet::FormShow(TObject *Sender)
{
//получение списка узлов по детали
String sql="call temporary_tables.obu_list ('"+obd+"')";
TADOQuery *rez=DB->SendSQL(sql);
rez->First();
CB1->Items->Clear();
while (!rez->Eof)
    {
    CB1->Items->Add(VinToGost(rez->FieldByName("obu")->Value));
    rez->Next();
    }
CB2->Text="";
CB1->ItemIndex=0;
CB1Click(0);
delete rez;
}

