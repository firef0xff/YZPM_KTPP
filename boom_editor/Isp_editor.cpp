//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Isp_editor.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
__fastcall TIspList::TIspList(TComponent* Owner,cSQL *const db,vector <IspData> &_list,bool _edit)
    : TForm(Owner),list(_list),DB(db)
{
//сортировка вектора по обозначению
std::sort (list.begin(),list.end(),Less());
TV->Items->Clear();
edit=_edit;
if (edit)
    {
    TV->PopupMenu=PAB;
    }else
    {
    TV->PopupMenu=0;
    }
for (int i= 0; i <list.size(); i++)
    {
    list[i].selected=!edit;
    }
Show();
}
void   TIspList::Show(void)
{
TV->Items->Clear();
TTreeNode *node=0;
for (int i=0; i<list.size(); i++)
    {
     node=TV->Items->AddChildObject(0,list[i].Get_Obd(true),(void*)i);
     node->StateIndex=edit?-1:1;
     node->ExpandedImageIndex=node->StateIndex;
     node->ImageIndex=node->ExpandedImageIndex;
     node->SelectedIndex=node->ImageIndex;
    }
}
void __fastcall TIspList::N1Click(TObject *Sender)
{
//добавить
TObd_edit *wnd=new TObd_edit(this);
wnd->ShowModal();
if (wnd->ModalResult==mrOk)
    {
    int i=0;
    bool find=false;
    String obd=GostToVin(wnd->Edit1->Text),obdm="";
    while (i<list.size()&&!find)
        {
        if (list[i].Get_Obd(false)==obd)
            {
            find=true;
            }else
            {
            i++;
            }
        }
    if (!find)
        {
        i=0;
        while (i<list.size()&&!find)
            {
            if (list[i].main_isp)
                {
                find=true;
                }else
                {
                i++;
                }
            }
        if (find)
            {
            obdm=list[i].Get_Obd(false);
            }
        if (obd.SubString(1,obd.Length()-2)==obdm.SubString(1,obdm.Length()-2))
            {
            IspData tmp;
            tmp.id=0;
            tmp.main_isp=false;
            tmp.Set_Obd(wnd->Edit1->Text);
            list.push_back(tmp);
            std::sort (list.begin(),list.end(),Less());
            Show();
            }
        }
    }
}
void __fastcall TIspList::N2Click(TObject *Sender)
{
//исключить
if (TV->Selected)
    {
    int ofset=(int)TV->Selected->Data;
    if (!list[ofset].main_isp)
        {
        list.erase(list.begin()+ofset);
        }
    Show();
    }

}
void __fastcall TIspList::N3Click(TObject *Sender)
{
//сменить обозначение
if (TV->Selected)
    {
    int ofset=(int)TV->Selected->Data;
    TObd_edit *wnd=new TObd_edit(this);
    wnd->ShowModal();
    if (wnd->ModalResult==mrOk)
        {//проверить наличие детали в базе
        TADOQuery *rez=DB->SendSQL("Call constructions.Get_id('"+GostToVin(wnd->Edit1->Text)+"')");
        if (rez&&!rez->RecordCount)
            {
            list[ofset].Set_Obd(wnd->Edit1->Text);
            Show();
            }
        delete rez;
        }
    }
}

void __fastcall TIspList::TVDblClick(TObject *Sender)
{
if (!edit)
    {
    TTreeNode *node=TV->Selected;
    node->StateIndex=1-node->StateIndex;
    node->ExpandedImageIndex=node->StateIndex;
    node->ImageIndex=node->ExpandedImageIndex;
    node->SelectedIndex=node->ImageIndex;
    list[(int)node->Data].selected=node->StateIndex;
    }
}
