//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ZakazCreator.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

__fastcall TZakazWnd::TZakazWnd(TComponent* Owner, cSQL *db)
	: TForm(Owner),DB(db)
{
}
void __fastcall TZakazWnd::BitBtn1Click(TObject *Sender)
{
	String sql = " select count(1) as cnt from manufacture.parts a "
				 " join manufacture.zakaz_list b on a.zak_id = b.zak_id "
				 " where a.part_no = '"+part->Text+"' and b.zakaz = '"+zakaz->Text+"'";
	TADOQuery *rez = DB->SendSQL(sql);
	if (rez)
	{
		if ( int(rez->FieldByName("cnt")->Value) > 0 )
		{
        	ShowMessage("Партия с таким номером уже существует");
		}
		else
		{
			ModalResult = mrOk;
			this->CloseModal();
		}
		delete rez;
		return;
	}
	ShowMessage("Ошибка соединеия с базой данных");
	return;
}
//---------------------------------------------------------------------------

void __fastcall TZakazWnd::zakazChange(TObject *Sender)
{
	String sql = " select max(a.part_no)+1 as part_no from manufacture.parts a "
				 " join manufacture.zakaz_list b on a.zak_id = b.zak_id "
				 " where b.zakaz = '"+zakaz->Text+"'";
	TADOQuery *rez = DB->SendSQL(sql);
	if (rez)
	{
		if (rez->FieldByName("part_no")->Value.IsNull())
		{
			part->Text = "1";
		}
		else
		{
			part->Text = String(int(rez->FieldByName("part_no")->Value));
        }
		delete rez;
		return;
	}
}
//---------------------------------------------------------------------------

