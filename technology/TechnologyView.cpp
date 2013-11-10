//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TechnologyView.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
__fastcall TTechView::TTechView(TComponent* Owner,TWinControl *_p,String _name, int user,cSQL *db)
	: TFrame(Owner)
{
}
//---------------------------------------------------------------------------
