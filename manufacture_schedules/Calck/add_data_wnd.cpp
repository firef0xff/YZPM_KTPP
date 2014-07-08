//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "add_data_wnd.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

__fastcall TCalckAddParams::TCalckAddParams(TComponent* Owner)
	: TForm(Owner)
{
}

void __fastcall TCalckAddParams::BitBtn1Click(TObject *Sender)
{
    try
    {
		Percent->Text.ToDouble();

		ModalResult = mrOk;
		CloseModal();
    }
    catch (...)
	{
        ShowMessage("В поле 'Процент' должно находиться число (целое/дробное)");
    }
}

