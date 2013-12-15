//---------------------------------------------------------------------------

#ifndef report_paramsH
#define report_paramsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include <Dialogs.hpp>
#include <Grids.hpp>

#include <report.h>
//---------------------------------------------------------------------------
class TRepParams : public TForm
{
__published:	// IDE-managed Components
	TPanel *TopPanel;
	TPanel *MidPanel;
	TPanel *BottomPanel;
	TSaveDialog *SD;
	TCheckBox *ActiveDelimiter;
	TEdit *Count;
	TLabel *Label1;
	TLabeledEdit *FileName;
	TButton *SetFile;
	TBitBtn *ok;
	TBitBtn *cancel;
	TStringGrid *OptionsSG;
	void __fastcall okClick(TObject *Sender);
	void __fastcall SetFileClick(TObject *Sender);
	void __fastcall FileNameChange(TObject *Sender);
private:	// User declarations
    rep::Report::ParamList &params;
	bool use_path;
    bool use_lists;
	bool use_params;

	void SetListingEnabled(void);
public:		// User declarations
	bool NoParams()
	{
		return  !(use_path + use_params);
	}
    __fastcall TRepParams(TComponent* Owner, rep::Report::ParamList &params_ );
};

#endif
