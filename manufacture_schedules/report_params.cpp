//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "report_params.h"
#include "functions.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

__fastcall TRepParams::TRepParams(TComponent* Owner, rep::Report::ParamList &params_)
    : TForm(Owner),params(params_),use_path(false),use_lists(false),use_params(false)
{
    SGClear(OptionsSG);
    OptionsSG->Cells[0][0] = "Параметр";
    OptionsSG->Cells[1][0] = "Значение";

    for (rep::Report::ParamList::const_iterator it = params.begin(), end = params.end(); it!=end; ++it)
    {
        const rep::Report::Parametr &itm = *it;

		int row = OptionsSG->RowCount-1;

        if (itm.first == REPORT_PATH )
        {
            use_path = true;
            FileName->Text = itm.second.c_str();
        }
        else if (itm.first == REPORT_LIST_COUNT )
        {
            use_lists = true;
            if (itm.second != REP_NULL && itm.second != REP_FALSE)
			{
				Count->Text = itm.second.c_str();
			}
			else
			{
				Count->Text = "1";
            }
        }
        else if (itm.first == REPORT_USE_LISTING)
        {
			ActiveDelimiter->Checked = itm.second != REP_NULL && itm.second!=REP_FALSE;
        }
        else
        {
            use_params = true;
			OptionsSG->Cells[0][row] = itm.first.c_str();
            OptionsSG->Cells[1][row] = itm.second.c_str();
            ++OptionsSG->RowCount;
        }
    }
	if (OptionsSG->RowCount > 2)
    {
        --OptionsSG->RowCount;
	}
    AutoWidthSG(OptionsSG);

	SetListingEnabled();
	ActiveDelimiter->Enabled = FileName->Text.Trim().Length() * use_path * use_lists;
	Count->Enabled = use_path * use_lists;

	FileName->Enabled = use_path;
	SetFile->Enabled = use_path;

	TopPanel->Visible = use_path;
	MidPanel->Visible = use_params;

	if (!use_path)
	{
        Height -= (TopPanel->Height);
        TopPanel->Height = 0;
    }
	if (!use_params)
    {
        Height -= (MidPanel->Height);
        MidPanel->Height = 0;
    }
}

void __fastcall TRepParams::okClick(TObject *Sender)
{
	for (size_t i = 1; i<OptionsSG->RowCount; ++i)
	{
		AnsiString key = OptionsSG->Cells[0][i];
		AnsiString val = OptionsSG->Cells[1][i];
		params[key.c_str()] = val.c_str();
	}
    if (use_path)
    {
        AnsiString t = FileName->Text;
        params[REPORT_PATH] = t.c_str();
    }
    if (use_lists)
    {
        if (ActiveDelimiter->Checked && ActiveDelimiter->Enabled)
        {
            params[REPORT_USE_LISTING] = REP_TRUE;
        }
        else
        {
            params[REPORT_USE_LISTING] = REP_FALSE;
		}
		AnsiString t = Count->Text.c_str();
        params[REPORT_LIST_COUNT] = t.c_str();
    }
}
void __fastcall TRepParams::SetFileClick(TObject *Sender)
{
    if (SD->Execute())
    {
        FileName->Text=SD->FileName;
    }
    else
    {
        FileName->Text="";
    }
	SetListingEnabled();
}
void TRepParams::SetListingEnabled(void)
{
	ActiveDelimiter->Enabled=FileName->Text.Trim().Length()* use_path * use_lists;
}
void __fastcall TRepParams::FileNameChange(TObject *Sender)
{
	SetListingEnabled();
}
