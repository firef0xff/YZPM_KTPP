#include <vcl.h>
#pragma hdrstop

#include "tara_and_strop.h"
#pragma package(smart_init)
#pragma resource "*.dfm"

//---------------------------------------------------------------------------
__fastcall Ttarandsrop::Ttarandsrop(TComponent* Owner,cSQL *db,String _type,String _id,String _text)
    : TForm(Owner),DB(db),type(_type),id(_id),text(_text)
{
img->Picture=0;
TV->Items->Clear();
TTreeNode *node;
String sql="";
if (type=="strop")
    {
    sql="select distinct `p1` from catalogs.stropovka order by `p1`";
    }
if (type=="tara")
    {
    sql="select distinct tara from catalogs.tara order by tara";
    }
LE1->Text=text;
if (sql==""){return;}
TADOQuery *rez=DB->SendSQL(sql);
if (rez&&rez->RecordCount)
    {
    for (rez->First(); !rez->Eof; rez->Next())
        {
        if (!rez->FieldByName(rez->Fields->operator [](0)->FieldName)->Value.IsNull())
            {
            node=TV->Items->AddObject(0,Trim(rez->FieldByName(rez->Fields->operator [](0)->FieldName)->Value),0);
            if (!node->Level)
                {
                TV->Items->AddChildObject(node,"",0);
                }
            }
        }
    }
delete rez;
rez=DB->SendSQL("select value from administration.settings where property='imgs'");
if (rez&&rez->RecordCount)
    {
    base=Trim(rez->FieldByName("value")->Value);
    }
}
void __fastcall Ttarandsrop::TVExpanding(TObject *Sender, TTreeNode *Node, bool &AllowExpansion)
{
Node->DeleteChildren();
String sql="", text="",f1,f2,f3;
if (type=="strop")
    {
    sql="select predm,chert from catalogs.stropovka where p1='"+Trim(Node->Text)+"' order by `p1`";
    f1="predm";f2="chert";f3="chert";
    }
if (type=="tara")
    {
    sql="select kota,obta,razm  from catalogs.tara where tara='"+Trim(Node->Text)+"' order by razm";
    f1="obta";f2="razm";f3="kota";
    }
if (sql==""){return;}
TADOQuery *rez=DB->SendSQL(sql);
if (rez&&rez->RecordCount)
    {
    for (rez->First(); !rez->Eof; rez->Next())
        {
        text="(";
        if (!rez->FieldByName(f2)->Value.IsNull())
            {
            text=text+Trim(rez->FieldByName(f2)->Value);
            }
        text=text+") ";
        if (!rez->FieldByName(f1)->Value.IsNull())
            {
            text=text+Trim(rez->FieldByName(f1)->Value);
            }
        if (Trim(text)!="")
            {
            String *str=new String(rez->FieldByName(f3)->Value.operator UnicodeString());
            TV->Items->AddChildObject(Node,text,(void *)str);
            }
        }
    }
delete rez;
}
void __fastcall Ttarandsrop::TVDblClick(TObject *Sender)
{
if (TV->Selected)
    {
    if (TV->Selected->Level)
        {
        if (type=="strop")
            {
            id=(*((String *)TV->Selected->Data));
            text="Строповка по РТМ 2103-11-75 чертеж:";
            LE1->Text="Строповка по РТМ 2103-11-75 чертеж "+id;
            }
        if (type=="tara")
            {
            id=(*((String *)TV->Selected->Data));
            text="Тара "+Trim(Trim(TV->Selected->Text).SubString(Trim(TV->Selected->Text).Pos(")")+1,Trim(TV->Selected->Text).Length()-Trim(TV->Selected->Text).Pos(")")));
            LE1->Text="Тара "+Trim(Trim(TV->Selected->Text).SubString(Trim(TV->Selected->Text).Pos(")")+1,Trim(TV->Selected->Text).Length()-Trim(TV->Selected->Text).Pos(")")));
            }
        }
    }
}

void __fastcall Ttarandsrop::BitBtn1Click(TObject *Sender)
{
if (type=="strop")
    {

    }
if (type=="tara")
    {

    }
}
void __fastcall Ttarandsrop::BitBtn3Click(TObject *Sender)
{
LE1->Text="";
id="";
text="";
}
//---------------------------------------------------------------------------

void __fastcall Ttarandsrop::TVClick(TObject *Sender)
{
String numb;
if (type=="strop"&&TV->Selected->Level)
    {
    if (FileExists(base+Trim(Trim(TV->Selected->Text).SubString(Trim(TV->Selected->Text).Pos("(")+1,Trim(TV->Selected->Text).Pos(")")-1-Trim(TV->Selected->Text).Pos("(")))+".bmp"))
        {
        img->Picture->Bitmap->LoadFromFile(base+Trim(Trim(TV->Selected->Text).SubString(Trim(TV->Selected->Text).Pos("(")+1,Trim(TV->Selected->Text).Pos(")")-1-Trim(TV->Selected->Text).Pos("(")))+".bmp");
        }else
        {
        img->Picture=0;
        }
    }
if (type=="tara"&&TV->Selected->Level)
    {
    if (((*(String*)(TV->Selected->Data)).Trim().ToInt())<10)
        {
        numb="3";
        }else
        if (((*(String*)(TV->Selected->Data)).Trim().ToInt())<13)
            {
            numb="10";
            }else
            {
            numb=((*(String*)(TV->Selected->Data)).Trim());
            }
    if (FileExists(base+"tara"+numb+".bmp"))
        {
        img->Picture->Bitmap->LoadFromFile(base+"tara"+numb+".bmp");
        }else
        {
        img->Picture=0;
        }
    }
}
void __fastcall Ttarandsrop::TVDeletion(TObject *Sender, TTreeNode *Node)
{
if (Node->Data)
    {
    delete (String *)Node->Data;
    }
}
