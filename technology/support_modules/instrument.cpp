//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "instrument.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tinstr *instr;
//---------------------------------------------------------------------------
__fastcall Tinstr::Tinstr(TComponent* Owner,cSQL *db,String _kod,String _name)
    : TForm(Owner),DB(db),kod(_kod),name(_name)
{
LE1->Text=kod;
LE2->Text=name;
TTreeNode *node;
TV->Items->Clear();
 String sql="Select distinct `nagr` from instrum.`instrum_types` where `nagr` is not null order by nagr";
 TADOQuery *rez=DB->SendSQL(sql);
 if (rez&&rez->RecordCount)
     {
     for (rez->First(); !rez->Eof; rez->Next())
         {
         node=TV->Items->AddObject(0,Trim(rez->FieldByName("nagr")->Value),0);
         TV->Items->AddChildObject(node,"",0);
         }
     }
delete rez;
}
void __fastcall Tinstr::TVExpanding(TObject *Sender, TTreeNode *Node, bool &AllowExpansion)

{
TTreeNode *node;
Node->DeleteChildren();
String sql="";
if (Node->Level==0)
    {
    sql="Select distinct `pc` from instrum.`instrum_types` where `nagr`='"+Trim(Node->Text)+"' order by pc";
    }
if (Node->Level==1)
    {
    sql="Select distinct `pd` from instrum.`instrum_types` where `nagr`='"+Trim(Node->Parent->Text)+"' and `pc`='"+Trim(Node->Text)+"' order by pd";
    }
if (Node->Level==2)
    {
    sql="Select distinct `pe` from instrum.`instrum_types` where `nagr`='"+Trim(Node->Parent->Parent->Text)+"' and `pc`='"+Trim(Node->Parent->Text)+"' and `pd`='"+Trim(Node->Text)+"' order by pe";
    }
if (Node->Level==3)
    {
    sql="Select distinct `pf` from instrum.`instrum_types` where `nagr`='"+Trim(Node->Parent->Parent->Parent->Text)+"' and `pc`='"+Trim(Node->Parent->Parent->Text)+"' and `pd`='"+Trim(Node->Parent->Text)+"' and `pe`='"+Trim(Node->Text)+"' order by pf";
    }
if (sql!="")
    {
    TADOQuery *rez=DB->SendSQL(sql);
    if (rez&&rez->RecordCount)
        {
        for (rez->First(); !rez->Eof; rez->Next())
            {
            if (!rez->FieldByName(rez->Fields->operator [](0)->FieldName)->Value.IsNull())
                {
                node=TV->Items->AddChildObject(Node,Trim(rez->FieldByName(rez->Fields->operator [](0)->FieldName)->Value),0);
                if (Node->Level<3)
                    {
                    TV->Items->AddChildObject(node,"",0);
                    }
                }
            }
        }
    delete rez;
    }
}
void __fastcall Tinstr::TVDblClick(TObject *Sender)
{
TTreeNode *node=TV->Selected;
LE2->Text="";
while (node->Level)
    {
    LE2->Text=node->Text+" "+LE2->Text;
    node=node->Parent;
    }
}
//---------------------------------------------------------------------------
void __fastcall Tinstr::BitBtn1Click(TObject *Sender)
{
name=Trim(LE2->Text);
kod=Trim(LE1->Text);
}
