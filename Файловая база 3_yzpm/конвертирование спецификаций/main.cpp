//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "main.h"
#include "Excel.h"
#include "functions.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm3 *Form3;
//---------------------------------------------------------------------------
__fastcall TForm3::TForm3(TComponent* Owner)
	: TForm(Owner)
{
SG->Cells[0][0]="Заменить";
SG->Cells[1][0]="На";
SGClear(SG,0);
}
//---------------------------------------------------------------------------
void __fastcall TForm3::Button1Click(TObject *Sender)
{
OD->FileName="";
OD->Execute();
sp=OD->FileName;
if (sp!="")
	{
	Button2->Enabled=true;
	}else
	{
	Button2->Enabled=false;
	}
}
void __fastcall TForm3::Button3Click(TObject *Sender)
{
OD->FileName="";
OD->Execute();
templ=OD->FileName;
}
void __fastcall TForm3::Button2Click(TObject *Sender)
{
AnsiString file="\\\\skb35\\fbase\\templates\\sptemplate.xlt";
if (templ!="")
	{
	file=templ;
	}
cExcel *fr=new cExcel();
cExcel *to=new cExcel();
fr->Connect();
fr->DisplayAlerts(false);
to->Connect();
to->DisplayAlerts(false);
fr->SetActiveBooks(fr->Books_Open(OD->FileName));
to->SetActiveBooks(to->Books_Open(file));
// Инициализация переменных указателей на итемы екселя
fr->SetActiveBook(fr->GetFirstBook());
fr->SetActiveSheets(fr->GetSheets());
fr->SetActiveSheet(fr->GetFirstSheet());
// Инициализация переменных указателей на итемы екселя
to->SetActiveBook(to->GetFirstBook());
to->SetActiveSheets(to->GetSheets());
to->SetActiveSheet(to->GetFirstSheet());
int fl=31,fp=3,nl=32;
int liscount=(LE2->Text.ToInt()-LE1->Text.ToInt())/fl+1;
int list=2;
while (liscount>list)
		{
		to->Sheet_Copy(to->GetSheet(list),to->GetSheet(list+1));
		list++;
		}
to->SetActiveSheet(to->GetFirstSheet());
list=1;
for (int i=LE1->Text.ToInt(),j=fp;i<=LE2->Text.ToInt()&&list<=liscount; i++,j++)
	{
	if (j>fl)
		{
		list++;
		to->SetActiveSheet(to->GetSheet(list));
		j=fp;
		}
	 to->toCells(j,4,fr->fromCells(i,1));//1=4
	 to->toCells(j,5,fr->fromCells(i,2));
	 to->toCells(j,7,fr->fromCells(i,3));
	 to->toCells(j,8,Format(fr->fromCells(i,4))); //обозначение
	 to->toCells(j,12,fr->fromCells(i,5));
	 to->toCells(j,17,fr->fromCells(i,6));
	 to->toCells(j,19,fr->fromCells(i,7));
	}
to->Visible(true);
bool ss=fr->Disconnect();
}
void __fastcall TForm3::SGSetEditText(TObject *Sender, int ACol, int ARow, const UnicodeString Value)

{
int col=0;
switch (ACol)
	{
	case 0:{col=1;break;}
	case 1:{col=0;break;}
	default:return;
	}
if (Value!=""||SG->Cells[col][ARow]!="")
	{
	if (ARow==SG->RowCount-1)
		{
		SG->RowCount++;
		}
	}else
	{
	// смещение строк вверх
	int i,j;
	for (i = ARow; i < SG->RowCount; i++)
		{
		for (j=0; j < SG->ColCount; j++)
			{
			SG->Cells[j][i]=SG->Cells[j][i+1];
			SG->Cells[j][i+1]="";
			}
		}
	if (SG->RowCount>2)
		{
		SG->RowCount--;
		}
	}

}
String TForm3::Format(String s)
{
if (s.Trim()=="") {return s;}
int length=LE->Text.Length();
//1 произвести замены
bool replace=false;
for (int i=1; i<SG->RowCount-1&&!replace; i++)
	{
	String r=Replace(s,SG->Cells[0][i],SG->Cells[1][i]);
	if (s!=r)
		{
		replace=true;
		s=r;
		}
	}
if (replace)
	{
	s=Replace(s,".","");
	s=Replace(s,"-","");
	s=Replace(s,",","");
	s=Replace(s,":","");

		//2 форматировать как на образце
		int k=0;
		for (int i=1; i<=length; i++)
			{
			if (LE->Text.SubString(i,1)!="_")
				{
				s.Insert(LE->Text.SubString(i,1),i+k);
				//k++;
				}
			}
	}
return s.SubString(1,length);
}
