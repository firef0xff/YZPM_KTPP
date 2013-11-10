//---------------------------------------------------------------------------

#ifndef pp_start_paramsH
#define pp_start_paramsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TPP_params : public TForm
{
__published:	// IDE-managed Components
	TCheckBox *P_pr;
	TCheckBox *T_cex;
	TCheckBox *T_obor;
	TBitBtn *cancel;
	TBitBtn *ok;
	TCheckBox *ML;
	TSaveDialog *SD;
	TLabeledEdit *FileName;
	TButton *SetFile;
	TCheckBox *ActiveDelimiter;
	TEdit *Count;
	TLabel *Label1;
	void __fastcall P_prClick(TObject *Sender);
	void __fastcall SetFileClick(TObject *Sender);
	void __fastcall okClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
private:	// User declarations
public:		// User declarations
	String save_to_file;
	String file_ext;
	bool trim_file;
	int  lists_in_file;
	__fastcall TPP_params(TComponent* Owner);
};

#endif
