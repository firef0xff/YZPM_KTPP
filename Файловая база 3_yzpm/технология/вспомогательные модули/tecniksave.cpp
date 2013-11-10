#include <vcl.h>
#pragma hdrstop
#include "tecniksave.h"
#pragma package(smart_init)
#pragma resource "*.dfm"

__fastcall TTB::TTB(TComponent* Owner,String _oprid,String _ioht,cSQL *db)
	: TForm(Owner),DB(db),oprid(_oprid),ioht(_ioht)
{
SG1->Cells[1][0]=" од опер.";
SG1->Cells[2][0]="ќбозначение документа";
SG1->Cells[3][0]="ќписание";
Params->ItemIndex=2;
ParamsClick(Params);
}
void __fastcall TTB::SG1DrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect,
          TGridDrawState State)
{
SG1->ColWidths[0]=18;
if((!ACol)&&(ARow))
	{
	SG1->Canvas->Brush->Color=clBtnFace;
	SG1->Canvas->FillRect(Rect);
	TRect r = Rect;
	r.left+=2;
	r.top += Rect.Height()/2 - 6;
	r.right = r.left + 12;
	r.bottom = r.top + 12;
	if (SG1->Cells[0][ARow]=="1")
		{
		DrawFrameControl(SG1->Canvas->Handle, &r, DFC_BUTTON, DFCS_BUTTONCHECK|DFCS_CHECKED);
		} else
		{
		DrawFrameControl(SG1->Canvas->Handle, &r, DFC_BUTTON, DFCS_BUTTONCHECK);
		}
	}
}
void __fastcall TTB::SG1DblClick(TObject *Sender)
{
if (!SG1->Col&&Trim(SG1->Cells[2][SG1->Row]).Length())
	{
	if (SG1->Cells[0][SG1->Row]!="1")
		{
		SG1->Cells[0][SG1->Row]="1";
		if (ioht.Trim()!="")
			{
			if (ioht.Trim().SubString(ioht.Length(),1)==";")
				{
				ioht=ioht+" "+SG1->Cells[2][SG1->Row]+";";
				}else
				{
				ioht=ioht+"; "+SG1->Cells[2][SG1->Row]+";";
				}
			}else
			{
            ioht=SG1->Cells[2][SG1->Row]+";";
			}
		}
		else
		{
		ioht=ioht.Delete(ioht.Pos(SG1->Cells[2][SG1->Row]),SG1->Cells[2][SG1->Row].Length()+2);
		SG1->Cells[0][SG1->Row]="0";
		}
	}
}
void __fastcall TTB::SaveClick(TObject *Sender)
{
String substr="",sql;
substr=oprid;
if (Trim(substr)!="")
	{
	sql="update catalogs.instruc_tb set kop=replace(kop,'"+substr+";','')";//удалениестарых маркеров
	DB->SendCommand(sql);
	for (int i=1; i<SG1->RowCount; i++)
		{
		if (SG1->Cells[0][i]==1)
			{
			sql="update catalogs.instruc_tb set kop=concat(kop,'"+substr+";') where ioht='"+SG1->Cells[2][i]+"'";//добавление новых маркеров
			DB->SendCommand(sql);
			}
		}
	}
}
void __fastcall TTB::ParamsClick(TObject *Sender)
{
//перенаполнение сетки
String sql="";
if (Params->ItemIndex<2)
	{
	sql="Call Catalogs.Get_ioht('"+(String)Params->ItemIndex+"','"+oprid+"')";
	}else
	{
	String qioht=Replace(ioht,"; ","','");
	qioht=Replace(qioht,";","");
	sql="Call Catalogs.Get_ioht('"+(String)Params->ItemIndex+"',\""+qioht+"\")";
	}
TADOQuery *rez=DB->SendSQL(sql);
SGClear(SG1,0);
if (rez&&rez->RecordCount)
	{
	for (rez->First(); !rez->Eof; rez->Next())
		{
		SG1->Cells[1][SG1->RowCount-1]=rez->FieldByName("kop")->Value;
		SG1->Cells[2][SG1->RowCount-1]=rez->FieldByName("ioht")->Value;
		SG1->Cells[3][SG1->RowCount-1]=rez->FieldByName("nioht")->Value;
		SG1->RowCount++;
		}
	if (SG1->RowCount>2) {SG1->RowCount--;}
	}
delete rez;
for (int i=1; i<SG1->RowCount; i++)
	{
	if (ioht.Pos(SG1->Cells[2][i]))
		{
		SG1->Cells[0][i]="1";
		}
	}
AutoWidthSG(SG1);
}

