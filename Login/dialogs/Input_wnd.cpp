//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Input_wnd.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
__fastcall TnewItem::TnewItem(TComponent* Owner)
	: TForm(Owner)
{
}

void __fastcall TnewItem::BitBtn1Click(TObject *Sender)
{
	if (leItem->Text!="")
	{
		ModalResult=mrOk;
		CloseModal();
	}else
	{
    	MessageBoxW(Handle,L"�������� �� ����� ���� ������",L"��������",MB_ICONWARNING|MB_OK);
	}
}
//---------------------------------------------------------------------------

