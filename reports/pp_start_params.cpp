//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "pp_start_params.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

__fastcall TPP_params::TPP_params(TComponent* Owner)
	: TForm(Owner)
{
	P_prClick(0);
}
//---------------------------------------------------------------------------
void __fastcall TPP_params::P_prClick(TObject *Sender)
{
	ML->Enabled=P_pr->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TPP_params::SetFileClick(TObject *Sender)
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

void __fastcall TPP_params::okClick(TObject *Sender)
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
}
//---------------------------------------------------------------------------

void __fastcall TPP_params::FormShow(TObject *Sender)
{
	FileName->Text="";
	save_to_file="";
	file_ext="";
	trim_file=false;
	lists_in_file=0;
	ActiveDelimiter->Enabled=false;
	ActiveDelimiter->Checked=false;
}
//---------------------------------------------------------------------------
