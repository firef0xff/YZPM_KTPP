//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "params.h"
#pragma package(smart_init)
#pragma resource "*.dfm"
__fastcall Tparametr::Tparametr(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall Tparametr::FormShow(TObject *Sender)
{
cex->Text="";
zak->Text="";
part->Text="";
kol->Text="1";
switch (type)
	{
	case 3:{kol->Enabled=true;part->Enabled=true;zak->Enabled=true;cex->Enabled=true;cex->MaxLength=2;break;}
	case 4:{kol->Enabled=false;part->Enabled=false;zak->Enabled=false;cex->Enabled=true;cex->MaxLength=4;break;}
	case 5:{kol->Enabled=true;part->Enabled=false;zak->Enabled=true;cex->Enabled=false;cex->MaxLength=4;break;}
	default:
		{kol->Enabled=true;part->Enabled=true;zak->Enabled=true;cex->Enabled=true;cex->MaxLength=4;break;}
	}
}
//---------------------------------------------------------------------------

