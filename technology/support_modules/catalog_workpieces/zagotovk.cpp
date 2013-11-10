//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "zagotovk.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
__fastcall Tzagotovka::Tzagotovka(TComponent* Owner,cSQL *db,bool ReadOnly,const int &_LUser,String kz,String masz,String norma,String razmzagot)
	: TForm(Owner),DB(db),LUser(_LUser)
{
if (srtby==-1)
	{
	srtby=RG1->ItemIndex;
	}else
	{
	RG1->ItemIndex=srtby;
	}
SGClear(SG1,0);
SG1->Cells[0][0]="Параметр";
SG1->Cells[1][0]="Значение";
SG1->Cells[2][0]="Описание";
AutoWidthSG(SG1);
E1->Text="";
mass->Text="";
nrm->Text="";
LE1->Text="";
CB1->Items->Clear();
CB1->Text="";
// считывание норм с технологии
try
	{
	E1->Text=kz;
	mass->Text=masz;
	nrm->Text=norma;
	LE1->Text=razmzagot;
	}
catch (...){}
FillTree();
if (ReadOnly)
	{
	BB1->Hide();
	}
	String sql="call administration.Get_Rights('"+String(LUser)+"')";
	TADOQuery *rez=DB->SendSQL(sql);
	bool ZFormEdit=false;
	if(rez&&rez->RecordCount)
	{
		for (rez->First(); !rez->Eof; rez->Next())
		{
			const String val=rez->FieldByName("progname")->Value;
			if (val=="ZFormEdit")
			{
				ZFormEdit=true;
				break;
			}
		}
	}
	delete rez;
	Button1->Visible=ZFormEdit;
}
void 			Tzagotovka::FillTree(void)
{
TV->Items->Clear();
String sql;
switch (RG1->ItemIndex)
	{
	case 0: {sql="select kod,name from billets.vz_tree where parent=0 order by name"; break;}
	case 1: {sql="select vz_grp_id as kod,name from billets.vz_groups order by name"; break;}
	default: sql="select kod,name from billets.vz_tree where parent=0 order by name";
	}
TADOQuery *rez=DB->SendSQL(sql);
if (rez&&rez->RecordCount)
	{
	for (rez->First(); !rez->Eof; rez->Next())
		{
		TV->Items->AddChildObject(TV->Items->AddObject(0,Trim(rez->FieldByName("name")->Value),(void*)(int)rez->FieldByName("kod")->Value),"",0);
		}
	}
delete rez; rez=0;
}
void __fastcall Tzagotovka::TVExpanding(TObject *Sender, TTreeNode *Node, bool &AllowExpansion)

{
Node->DeleteChildren();
String sql;
switch (RG1->ItemIndex)
	{
	case 0: {sql="select kod,name from billets.vz_tree where parent="+String((int)Node->Data)+" order by name"; break;}
	case 1: {sql="select kod,name from billets.vz_tree where vz_grp_id="+String((int)Node->Data)+" order by name"; break;}
	default: sql="select kod,name from billets.vz_tree where parent="+String((int)Node->Data)+" order by name";
	}
TADOQuery *rez=DB->SendSQL(sql);
if (rez&&rez->RecordCount)
	{
	for (rez->First(); !rez->Eof; rez->Next())
		{
		TV->Items->AddChildObject(TV->Items->AddChildObject(Node,Trim(rez->FieldByName("kod")->Value)+"-"+Trim(rez->FieldByName("name")->Value),(void*)(int)rez->FieldByName("kod")->Value),"",0);
		}
	}
delete rez; rez=0;
}
void __fastcall Tzagotovka::RG1Click(TObject *Sender)
{
FillTree();
srtby=RG1->ItemIndex;
}
void __fastcall Tzagotovka::TVDblClick(TObject *Sender)
{
if (TV->Selected->Level)
	{
	E1->Text=(int)TV->Selected->Data;
	}
CB1->Items->Clear();
CB1->Text="";
String sql="Select distinct title from billets.raschet_zagot where kod='"+String((int)TV->Selected->Data)+"' order by title";
TADOQuery *rez=DB->SendSQL(sql);
if (rez&&rez->RecordCount)
	{
	for (rez->First(); !rez->Eof; rez->Next())
		{
		CB1->Items->Add(rez->FieldByName("title")->Value);
		}
	 CB1->ItemIndex=0;
	 CB1Click(0);
	}
delete rez; rez=0;
}
void __fastcall Tzagotovka::BB1Click(TObject *Sender)
{
kz=E1->Text;
masz=mass->Text;
norma=nrm->Text;
razmzagot=LE1->Text;
for (int i = 1; i < SG1->RowCount; i++)
	{
	if (SG1->Cells[0][i].Trim()=="n") {kdz=SG1->Cells[1][i].Trim();break;}
	}
}
void __fastcall Tzagotovka::BitBtn1Click(TObject *Sender)
{
String sql,sql1,formula;
int i;
for (i = 1; i < SG1->RowCount; i++)
	{
	if (SG1->Cells[1][i].Trim()=="") {ShowMessage("Заполните все исходные данные"); return;}
	}
sql="Select formula,type from billets.raschet_zagot  where kod='"+E1->Text+"' and title='"+CB1->Text+"' order by title";
TADOQuery *rez=DB->SendSQL(sql);
if (rez&&rez->RecordCount)
	{
	for (rez->First(); !rez->Eof; rez->Next())
		{
		formula=rez->FieldByName("Formula")->Value;
		for (i = 1; i < SG1->RowCount; i++)
			{
			formula=Replace(formula,SG1->Cells[0][i],Replace(SG1->Cells[1][i],",","."));
			}
		sql1="select Round(("+formula+"),4) as result";
		TADOQuery *rez1=DB->SendSQL(sql1);
		if (rez1&&rez->RecordCount)
			{
			rez1->First();
			if (rez->FieldByName("type")->Value=="nrm")
				{
				nrm->Text=rez1->FieldByName("result")->Value;
				}
			if (rez->FieldByName("type")->Value=="mass")
				{
				mass->Text=rez1->FieldByName("result")->Value;
				}
			}
		delete rez1; rez1=0;
		}
	}
delete rez; rez=0;
sql="Select Razz from billets.razzm_zag  where kod='"+E1->Text+"' and title='"+CB1->Text+"' order by title";
rez=DB->SendSQL(sql);
if (rez&&rez->RecordCount)
	{
	rez->First();
	formula=rez->FieldByName("Razz")->Value;
		for (i = 1; i < SG1->RowCount; i++)
			{
			formula=Replace(formula,SG1->Cells[0][i],SG1->Cells[1][i]);
			}
	}
delete rez; rez=0;
LE1->Text=formula;
}
void __fastcall Tzagotovka::CB1Click(TObject *Sender)
{
SGClear(SG1,0);
String sql="Select distinct c.parametr,c.parametr_name from billets.raschet_zagot a join billets.zagot_parametrs b on b.id=a.id join billets.parametr_list c on b.paramid=c.paramid where a.kod='"+E1->Text+"' and a.title='"+CB1->Text+"' order by c.parametr";
TADOQuery *rez=DB->SendSQL(sql);
if (rez&&rez->RecordCount)
	{
	for (rez->First(); !rez->Eof; rez->Next())
		{
		SG1->Cells[0][SG1->RowCount-1]=rez->FieldByName("parametr")->Value;
		SG1->Cells[2][SG1->RowCount-1]=rez->FieldByName("parametr_name")->Value;
		SG1->RowCount+=1;
		}
	}
delete rez; rez=0;
if (SG1->RowCount>2)
	{
	SG1->RowCount-=1;
	}
AutoWidthSG(SG1);
}
void __fastcall Tzagotovka::Button1Click(TObject *Sender)
{
TFomul_Editor *wnd=new TFomul_Editor(this,DB,E1->Text.Trim());
wnd->ShowModal();
delete wnd;
}
