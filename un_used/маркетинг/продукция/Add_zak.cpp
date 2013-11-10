//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Add_zak.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

#define MAX_HEIGHT_MOD1	240
#define MAX_HEIGHT_MOD2 1024
#define MIN_HEIGHT_MOD1 240
#define MIN_HEIGHT_MOD2 404
__fastcall  TZak_prop::TZak_prop(TComponent* Owner)
	: TForm(Owner),Using_add_composition(false)
{
	Use_add_composition(Using_add_composition);
}
//---------------------------------------------------------------------------
 void 		TZak_prop::Use_add_composition(bool trig)
 {//включение/отключение сетки ввода дополнительного состава
	if (trig)
	{
	Ad_composition->Show();
	Constraints->MinHeight=MIN_HEIGHT_MOD2;
	Constraints->MaxHeight=MAX_HEIGHT_MOD2;
	}else
	{
	Ad_composition->Hide();
	Constraints->MinHeight=MIN_HEIGHT_MOD1;
	Constraints->MaxHeight=MAX_HEIGHT_MOD1;
	}
	Using_add_composition=trig;
	Height=Constraints->MinHeight;
 }
