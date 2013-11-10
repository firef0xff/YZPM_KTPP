#include <vcl.h>
#pragma hdrstop
#include "professions.h"
#pragma package(smart_init)
#pragma resource "*.dfm"
__fastcall TProfessinos::TProfessinos(TComponent* Owner,cSQL *db,bool ReadOnly)
	: TForm(Owner),DB(db)
{
CB->ItemIndex=filter;
prof="";
SG1->Cells[1][0]="Код";
SG1->Cells[2][0]="Профессия";
AutoWidthSG(SG1);
SG2->Cells[1][0]="Цех";
SG2->Cells[2][0]="Участок";
SG2->Cells[3][0]="Название";
AutoWidthSG(SG2);
init();
if (ReadOnly)
	{
	ok->Hide();
	}
}
void __fastcall TProfessinos::CBClick(TObject *Sender)
{
filter=CB->ItemIndex;
bool t;
SG2SelectCell(0,0,SG2->Row,t);
}
void 			TProfessinos::init (void)
{
SGClear(SG2,0);
TADOQuery *rez=DB->SendSQL("select distinct b.cex,b.utch,c.npodr from catalogs.podr_prof b  join catalogs.podr_list c on c.cex=b.cex and c.utch=b.utch");
if (rez&&rez->RecordCount)
	{
	SG2->RowCount=rez->RecordCount+1;
	int i=2;
	for (rez->First(); !rez->Eof; rez->Next(),i++)
		{
		SG2->Cells[1][i]=rez->FieldByName("cex")->Value;
		SG2->Cells[2][i]=rez->FieldByName("utch")->Value;
		SG2->Cells[3][i]=rez->FieldByName("npodr")->Value;
		}
	}
SG2->Cells[1][1]="все";
SG2->Cells[2][1]="";
SG2->Cells[3][1]="";
delete rez;
AutoWidthSG(SG2);
}
void __fastcall TProfessinos::okClick(TObject *Sender)
{
prof=SG1->Cells[1][SG1->Row];
}
void __fastcall TProfessinos::SG2SelectCell(TObject *Sender, int ACol, int ARow, bool &CanSelect)
{
SGClear(SG1,0);
String sql;
if (ARow==1)
	{
	sql="Call catalogs.Get_proff('"+(String)(CB->ItemIndex+2)+"','0','0')" ;
	}else
	{
	sql="Call catalogs.Get_proff('"+(String)(CB->ItemIndex)+"','"+SG2->Cells[1][ARow]+"','"+SG2->Cells[2][ARow]+"')" ;
	}
TADOQuery *rez=DB->SendSQL(sql);
if (rez&&rez->RecordCount)
	{
	SG1->RowCount=rez->RecordCount+1;
	int i=1;
	for (rez->First(); !rez->Eof; rez->Next(),i++)
		{
		SG1->Cells[1][i]=rez->FieldByName("kodp")->Value;
		SG1->Cells[2][i]=rez->FieldByName("prof")->Value;
		}
	}
delete rez;
AutoWidthSG(SG1);
}
//---------------------------------------------------------------------------

