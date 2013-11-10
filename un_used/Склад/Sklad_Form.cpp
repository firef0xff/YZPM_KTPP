//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Sklad_Form.h"
#include "math.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TSklad *Sklad;
//---------------------------------------------------------------------------
__fastcall TSklad::TSklad(TComponent* Owner)
	: TForm(Owner)
{
expand_pannel_h(Panel17,false);
expand_pannel_h(Panel19,false);
View_Kont->Hide();
View_Zagr->Hide();
}

void __fastcall TSklad::PanelEnter(TObject *Sender)
{
TPanel *panel=(TPanel *)Sender;
if (panel){expand_pannel_h(panel,true);}
}
void __fastcall TSklad::PanelExit(TObject *Sender)
{
TPanel *panel=(TPanel *)Sender;
if (panel){expand_pannel_h(panel,false);}
}
void __fastcall TSklad::PanelMouseEnter(TObject *Sender)
{
TPanel *panel=(TPanel *)Sender;
if (panel){panel->SetFocus();}
}
void TSklad::expand_pannel_h(TPanel *Panel,bool exp)
{
if (exp)
	{
	Panel->Height=Panel->Tag;
	}else
	{
	Panel->Tag=Panel->Height;
    Panel->Height=Panel->Constraints->MinHeight;
	}
}


void __fastcall TSklad::R_GraphClick(TObject *Sender)
{                                               // индикатор заполненности
int x_min=0,y_min=0,x_max=109,y_max=80;
static int percent=1;  //входной параметр
bool Xplus,Yplus;
double Y1=270,Y2=1;
Y2=Y1+double(360)/100*percent;
percent++;
if (percent==100) {percent=0;}
int
x1=(y_max+x_max)/4*(1+cos(M_PI*Y1/180)),
y1=(y_max+x_max)/4*(1+sin(M_PI*Y1/180)),
x2=(y_max+x_max)/4*(1+cos(M_PI*Y2/180)),
y2=(y_max+x_max)/4*(1+sin(M_PI*Y2/180));

R_Graph->Picture=0;
//рисуются свободное
R_Graph->Canvas->Brush->Color=clFuchsia;
R_Graph->Canvas->Pie(x_min,y_min,x_max,y_max,x1,y1,x2,y2);
//рисуется занятое
R_Graph->Canvas->Brush->Color=clBlue;
R_Graph->Canvas->Pie(x_min,y_min,x_max,y_max,x2,y2,x1,y1);
//заливка фона
R_Graph->Canvas->Brush->Color=((TPanel*)R_Graph->Parent)->Color;
R_Graph->Canvas->FloodFill(x_min+1,y_min+1,R_Graph->Canvas->Pixels[x_min+1][y_min+1],fsSurface);
R_Graph->Canvas->FloodFill(x_min+1,y_max-1,R_Graph->Canvas->Pixels[x_min+1][y_max-1],fsSurface);
R_Graph->Canvas->FloodFill(x_max-1,y_min+1,R_Graph->Canvas->Pixels[x_max-1][y_min+1],fsSurface);
R_Graph->Canvas->FloodFill(x_max-1,y_max-1,R_Graph->Canvas->Pixels[x_max-1][y_max-1],fsSurface);
}
//---------------------------------------------------------------------------

void __fastcall TSklad::Panel7Click(TObject *Sender)
{
View_Kont->Visible=!View_Kont->Visible;
View_Zagr->Visible=!View_Zagr->Visible;
}
//---------------------------------------------------------------------------

