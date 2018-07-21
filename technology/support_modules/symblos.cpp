//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "symblos.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
__fastcall TSymbol::TSymbol(TComponent* Owner)
    : TForm(Owner)
{
//цифры верхний регистр
SG1->Cells[0][0]="›";
SG1->Cells[1][0]="њ";
SG1->Cells[2][0]="ќ";
SG1->Cells[3][0]="ћ";
SG1->Cells[4][0]="џ";
SG1->Cells[5][0]="…";
SG1->Cells[6][0]="Ў";
SG1->Cells[7][0]="ў";
SG1->Cells[8][0]="Ј";
SG1->Cells[9][0]="¤";
//цифры нижний регистр
SG1->Cells[0][1]="Ќ";
SG1->Cells[1][1]="Ћ";
SG1->Cells[2][1]="Џ";
SG1->Cells[3][1]="ђ";
SG1->Cells[4][1]="‘";
SG1->Cells[5][1]="’";
SG1->Cells[6][1]="“";
SG1->Cells[7][1]="”";
SG1->Cells[8][1]="–";     //8
SG1->Cells[9][1]="—";      //9
//знаки
SG1->Cells[0][2]="`";
SG1->Cells[1][2]="‹";
SG1->Cells[2][2]="‰";
SG1->Cells[3][2]="­"; //квадрат
SG1->Cells[4][2]="€";
SG1->Cells[5][2]="°";
SG1->Cells[6][2]="±";
SG1->Cells[7][2]="ґ";
SG1->Cells[8][2]="µ";
SG1->Cells[9][2]="Ѓ";
//знаки
SG1->Cells[0][3]="ѓ";
SG1->Cells[1][3]="†";
SG1->Cells[2][3]="•";
SG1->Cells[3][3]="‡";
SG1->Cells[4][3]="ј";
SG1->Cells[5][3]="Ґ";
SG1->Cells[6][3]="·";
SG1->Cells[7][3]="ѕ";
SG1->Cells[8][3]="Ђ";
SG1->Cells[9][3]="~";

//знаки
SG1->Cells[0][4]="¦";
SG1->Cells[1][4]="©";
SG1->Cells[2][4]="™";
SG1->Cells[3][4]="љ";
SG1->Cells[4][4]=L"Ø"; //диаметр(большая Ø, маленькая ø)
SG1->Cells[5][4]="";
SG1->Cells[6][4]="";
SG1->Cells[7][4]="";
SG1->Cells[8][4]="";
SG1->Cells[9][4]="";

}
//---------------------------------------------------------------------------
void __fastcall TSymbol::FormShow(TObject *Sender)
{
E1->Text="";
E1->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TSymbol::SG1DblClick(TObject *Sender)
{
TStringGrid *sg=(TStringGrid *)Sender;
if (sg->Cells[sg->Selection.Left][sg->Selection.Top]!="")
    {
    if (E1->Text!="")
        {
        int pos=E1->SelStart+1;
		int cur=E1->SelStart;
		UnicodeString msg=sg->Cells[sg->Selection.Left][sg->Selection.Top];
        E1->Text=E1->Text.Insert(msg,pos);
        } else
        {
        E1->Text=E1->Text+sg->Cells[sg->Selection.Left][sg->Selection.Top];
        }
    }
E1->SetFocus();
E1->SelStart=E1->Text.Length();
}

