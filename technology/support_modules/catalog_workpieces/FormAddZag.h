//---------------------------------------------------------------------------

#ifndef FormAddZagH
#define FormAddZagH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>

#include <ADODB.hpp>
#include <DB.hpp>
#include "SQL.h"
#include <Grids.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TFormAddZagCode : public TForm
{
__published:	// IDE-managed Components
	TLabeledEdit *eCode;
	TBitBtn *bOk;
	TBitBtn *bCancel;
	TComboBox *cbUse;
	TLabel *Label2;
	TLabeledEdit *eName;
	void __fastcall bOkClick(TObject *Sender);
private:	// User declarations
	cSQL * const DB;
	String pID;
	bool editZag;
	String lastpID;
public:		// User declarations
	__fastcall TFormAddZagCode(TComponent* Owner,cSQL *db, String parentID, bool edit);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormAddZagCode *FormAddZagCode;
//---------------------------------------------------------------------------
#endif
