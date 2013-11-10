//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "material.h"
#pragma package(smart_init)
#pragma resource "*.dfm"
 __fastcall Tmaterials::Tmaterials(TComponent* Owner,cSQL *db,bool ReadOnly,const int &_LUser)
	: TForm(Owner),DB(db),LUser(_LUser)
{
obm="";
SQL="";
LE1->Text=_obm;
LE2->Text=_name;
LE3->Text=_prof;
if (_obm!=""||_name!=""||_prof!="")
	{
	Button1Click(0);
	}
E3->Text=rowcount;
E2->Text=list;
TV->Items->Clear();
String sql="Select `ngrup`,`key`,`parent` from sklad.mat_tree where `parent`=0";
TADOQuery *rez=DB->SendSQL(sql);
if (rez&&rez->RecordCount)
	{
	for (rez->First(); !rez->Eof; rez->Next())
		{
		TV->Items->AddChildObject(TV->Items->AddObject(0,rez->FieldByName("ngrup")->Value,(void*)(int)rez->FieldByName("key")->Value),"",0);
		}
	}
delete rez;
SG->Cells[0][0]="Обозначение";
SG->Cells[1][0]="Наименование";
SG->Cells[2][0]="ГОСТ";
SG->Cells[3][0]="Профиль";
SG->Cells[4][0]="ГОСТ на профиль";
AutoWidthSG(SG);
if (ReadOnly)
	{
	Add->Hide();
	Button2->Hide();
	BB1->Hide();
	Del->Hide();
	}
}
void __fastcall Tmaterials::TVExpanding(TObject *Sender, TTreeNode *Node, bool &AllowExpansion)
{
Node->DeleteChildren();
String sql="Select `ngrup`,`key` from sklad.mat_tree where `parent`='"+(String)((int)Node->Data)+"'";
TADOQuery *rez=DB->SendSQL(sql);
if (rez&&rez->RecordCount)
	{
	for (rez->First(); !rez->Eof; rez->Next())
		{
		TV->Items->AddChildObject(TV->Items->AddChildObject(Node,rez->FieldByName("ngrup")->Value,(void*)(int)rez->FieldByName("key")->Value),"",0);
		}
	}
delete rez;
}
void __fastcall Tmaterials::N1Click(TObject *Sender)
{
TV->Selected->Expand(true);
}
void __fastcall Tmaterials::N2Click(TObject *Sender)
{
TV->Selected->Collapse(true);
}
void __fastcall Tmaterials::TVClick(TObject *Sender)
{
int kl=0,kb=0,ke=0;
if (!TV->Selected){TV->Selected=TV->Items->GetFirstNode();}
String sql="Select `kl`,`kb`,`ke` from sklad.mat_tree where `key`='"+(String)((int)TV->Selected->Data)+"'";
TADOQuery *rez=DB->SendSQL(sql);
if (rez&&rez->RecordCount)
	{
	kl=rez->FieldByName("kl")->Value;
	kb=rez->FieldByName("kb")->Value;
	ke=rez->FieldByName("ke")->Value;
	}
delete rez; rez=0;
SQL="Select a.obd,b.nama,b.goma,b.prma,b.gopr from constructions.det_names a join sklad.materials b on a.id=b.obmid where left(a.obd,9)='000000000' and left(a.obd,9+"+String(kl)+")*1 between '"+(String)kb+"' and '"+(String)ke+"'";
if (E2->Text!="1") {E2->Text="1";} else {Find();}
}
void __fastcall Tmaterials::Find(void)
{
if (SQL==""){return;}
if (SQL.Pos(" order")) {SQL.Delete(SQL.Pos(" order"),SQL.Length()+1-SQL.Pos(" order"));}
switch (RG->ItemIndex)
	{
	case 0 : SQL=SQL+" order by a.obd,b.prma"; break;
	case 1 : SQL=SQL+" order by b.prma,b.nama"; break;
	case 2 : SQL=SQL+" order by b.nama,b.prma"; break;
	case 3 : SQL=SQL+" order by b.gopr,b.prma"; break;
	default: break;
	}
if (SQL.Pos(" limit")){SQL.Delete(SQL.Pos(" limit"),SQL.Length()+1-SQL.Pos(" limit"));}
SQL=SQL+" limit "+IntToStr(E2->Text.ToInt()*E3->Text.ToInt()-E3->Text.ToInt())+","+E3->Text;
TADOQuery *rez=DB->SendSQL(SQL);
if (rez)
	{
	SGClear(SG,0);
	if (rez->RecordCount) {SG->RowCount=rez->RecordCount+1;} else {SG->RowCount=2;}
	while (!rez->Eof)
		{
		if (!rez->FieldByName("obd")->Value.IsNull()){SG->Cells[0][rez->RecNo]=VinToGost(rez->FieldByName("obd")->Value);}
		if (!rez->FieldByName("nama")->Value.IsNull()){SG->Cells[1][rez->RecNo]=Trim(rez->FieldByName("nama")->Value);}
		if (!rez->FieldByName("goma")->Value.IsNull()){SG->Cells[2][rez->RecNo]=Trim(rez->FieldByName("goma")->Value);}
		if (!rez->FieldByName("prma")->Value.IsNull()){SG->Cells[3][rez->RecNo]=Trim(rez->FieldByName("prma")->Value);}
		if (!rez->FieldByName("gopr")->Value.IsNull()){SG->Cells[4][rez->RecNo]=Trim(rez->FieldByName("gopr")->Value);}
		rez->Next();
		}
	delete rez;rez=0;
	AutoWidthSG(SG);
	}


}
//-------------------------сортировка-------------------------------------
void __fastcall Tmaterials::RGClick(TObject *Sender)
{
Find();
}
//-------------------------------поиск------------------------------
void __fastcall Tmaterials::Button1Click(TObject *Sender)
{
_obm=LE1->Text.Trim();
_name=LE2->Text.Trim();
_prof=LE3->Text.Trim();
if (LE1->Text.Trim()!=""||LE2->Text.Trim()!=""||LE3->Text.Trim()!="")
	{
	SQL="Select a.obd,b.nama,b.goma,b.prma,b.gopr from constructions.det_names a join sklad.materials b on a.id=b.obmid";
		if (LE1->Text.Trim()!="")
			{
			if (LE1->Text.SubString(1,2).UpperCase()=="NA")
				{
				SQL=SQL+" where a.obd like '"+LE1->Text.Trim()+"%'";
				}else
				{
				SQL=SQL+" where a.obd like '000000000%"+LE1->Text.Trim()+"%'";
				}
			}
		if (LE2->Text.Trim()!="")
			{
			if (SQL.Pos("where"))
				{
				SQL=SQL+" and b.nama like '%"+LE2->Text.Trim()+"%'";}else{SQL=SQL+" where b.nama like '%"+LE2->Text.Trim()+"%'";
				}
			}
		if (LE3->Text.Trim()!="")
			{
			if (SQL.Pos("where"))
				{
				SQL=SQL+" and b.prma like '%"+LE3->Text.Trim()+"%'";}else{SQL=SQL+" where b.prma like '%"+LE3->Text.Trim()+"%'";
				}
			}
	if (E2->Text!="1")
		{
		E2->Text="1";
		}else
		{
		Find();
		}
	}
}
void __fastcall Tmaterials::nextClick(TObject *Sender)
{
E2->Text=IntToStr(E2->Text.ToInt()+1);
list=E2->Text;
Find();
}
void __fastcall Tmaterials::prevClick(TObject *Sender)
{
if (E2->Text.ToInt()>1) {E2->Text=IntToStr(E2->Text.ToInt()-1);}
list=E2->Text;
Find();
}
void __fastcall Tmaterials::E2Change(TObject *Sender)
{
if (E2->Text==""||E2->Text=="0")
	{
	E2->Text="1";
	}
list=E2->Text;
Find();	
}
void __fastcall Tmaterials::E3Change(TObject *Sender)
{
if (E3->Text==""||E3->Text=="0")
	{
	E3->Text="1";
	}
rowcount=E3->Text;
if (E2->Text!="1") {E2->Text="1";} else {Find();}	
}
void __fastcall Tmaterials::BB1Click(TObject *Sender)
{
obm=SG->Cells[0][SG->Row];
}
void __fastcall Tmaterials::AddClick(TObject *Sender)
{
TMater_add *wnd=new TMater_add(this,DB,LUser);
wnd->ShowModal();
Find();
delete wnd;
}
void __fastcall Tmaterials::DelClick(TObject *Sender)
{
if (SG->Cells[0][SG->Row].Pos("NA"))
	{
	String sql="";
	sql="delete from constructions.det_names where obd='"+SG->Cells[0][SG->Row].Trim()+"'";
	DB->SendCommand(sql);
	Button1Click(Sender);
	}
}
void __fastcall Tmaterials::Button2Click(TObject *Sender)
{  /*
String _obm=SG->Cells[0][SG->Row];
TMat_zam *wnd=new TMat_zam(this,DB,_obm);
wnd->ShowModal();
Find();         */
}

