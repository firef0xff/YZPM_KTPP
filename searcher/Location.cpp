//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Location.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TLocationForm *LocationForm;
//---------------------------------------------------------------------------
int _id;
__fastcall TLocationForm::TLocationForm(TComponent* Owner, int id,cSQL *db)
	: TForm(Owner),DB(db)
{
	_id=id;
	DB=db;
	SQL="Select `id`,`cab`,`stack`,`rack` from constructions.location where `id`="+(String)_id;
	TADOQuery *rez=DB->SendSQL(SQL);
	if (!rez->FieldByName("id")->Value.IsNull()) {
		_eLocationCab->Text = rez->FieldByName("cab")->Value;
		_eLocationStack->Text = rez->FieldByName("stack")->Value;
		_eLocationRack->Text = rez->FieldByName("rack")->Value;
		_bChangeLocation->Caption = "Редактировать";
	}
	else
	{
		_bChangeLocation->Caption = "Редактировать (Нет в базе)";
	}
}
//---------------------------------------------------------------------------


void __fastcall TLocationForm::_bChangeLocationClick(TObject *Sender)
{
	if (_eLocationCab->Text == "") {
		_eLocationCab->Color = clRed;
	}
	else
	{
		_eLocationCab->Color = clWindow;
		if (_eLocationStack->Text == "") {
			_eLocationStack->Color = clRed;
		}
		else
		{
			_eLocationStack->Color = clWindow;
			if (_eLocationRack->Text == "") {
			_eLocationRack->Color = clRed;
			}
			else
			{
				_eLocationRack->Color = clWindow;
				SQL="Select `id` from constructions.location where `id`="+(String)_id;
				TADOQuery *rez=DB->SendSQL(SQL);
				if (!rez->FieldByName("id")->Value.IsNull())
				{//если в базе уже есть такой
					SQL="delete from constructions.location where `id`="+(String)_id;
					rez=DB->SendSQL(SQL);
				}
				SQL="insert into constructions.location (id,cab,stack,rack) select "+(String)_id+","+(String)_eLocationCab->Text+","+(String)_eLocationStack->Text+","+(String)_eLocationRack->Text;
				rez=DB->SendSQL(SQL);
				_bChangeLocation->Caption = "Редактировать (Успешно)";
			}
		}
    }
}
//---------------------------------------------------------------------------
