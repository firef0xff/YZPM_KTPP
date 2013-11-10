//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "trb_params.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

__fastcall TTrbOptions::TTrbOptions(TComponent* Owner)
	: TForm(Owner)
{
}

void __fastcall TTrbOptions::SetFileClick(TObject *Sender)
{
	if (SD->Execute())
	{
		FileName->Text=SD->FileName;
	}
	else
	{
		FileName->Text="";
	}
	ActiveDelimiter->Enabled=FileName->Text.Trim().Length();
}
//---------------------------------------------------------------------------

void __fastcall TTrbOptions::okClick(TObject *Sender)
{
	save_to_file=ExtractFilePath(FileName->Text)+ExtractFileName(FileName->Text);
	file_ext=ExtractFileExt(FileName->Text);
	if (save_to_file.Pos(file_ext))
	{
		save_to_file.Delete(save_to_file.Pos(file_ext),file_ext.Length());
	}
	if (file_ext!=".xls"||file_ext!=".xlsx")
	{
		file_ext=".xls";
	}
	trim_file=ActiveDelimiter->Enabled*ActiveDelimiter->Checked;
	if (trim_file)
	{
		lists_in_file=Count->Text.ToInt();
	}

	Organization=Organization_->Text;
	MatReceiver=Receiver->Text;
}
//---------------------------------------------------------------------------

void __fastcall TTrbOptions::FormShow(TObject *Sender)
{
	FileName->Text="";
	save_to_file="";
	file_ext="";
	trim_file=false;
	lists_in_file=0;
	Receiver->Text="";
	Organization_->Text="";
	ActiveDelimiter->Enabled=false;
	ActiveDelimiter->Checked=false;
}
//---------------------------------------------------------------------------

