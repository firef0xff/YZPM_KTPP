// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Agrements_select.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

__fastcall TAgreements_select::TAgreements_select(TComponent *Owner,
	const int &_LUser, cSQL *db):TForm(Owner)
	{
	frm=new TAgreements(this, Panel2, _LUser, db);
	}

void __fastcall TAgreements_select::OKClick(TObject *Sender)
	{
	frm->Update_selected_dog(id,d_num,d_date,d_type,ca_name);
	}
