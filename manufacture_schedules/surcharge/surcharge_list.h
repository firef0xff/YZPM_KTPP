//---------------------------------------------------------------------------

#ifndef surcharge_listH
#define surcharge_listH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>

#include "SQL.h"
//---------------------------------------------------------------------------
class TSurchargeList : public TForm
{
__published:	// IDE-managed Components
    TLabeledEdit *zak_no;
    TLabeledEdit *part_no;
    TEdit *opr_kod;
    TEdit *opr_name;//ro
	TLabeledEdit *kts;
	TLabeledEdit *rr;
	TLabeledEdit *vn;
	TLabeledEdit *kol;
	TLabeledEdit *tpz;
	TLabeledEdit *tsht;
    TLabeledEdit *tfact;
    TMemo *descr;

	TComboBox *reason;

	TLabeledEdit *nar_no;
	TLabeledEdit *cex;
	TLabeledEdit *utch;
	TLabeledEdit *tab_no;
    TLabeledEdit *fio;//ro

    TLabel *Label1;
    TLabel *Label2;
    TLabel *Label3;
    TLabel *Label4;

	TBitBtn *save;
	TBitBtn *cancel;
	TBitBtn *BitBtn1;
	TBitBtn *ok;
	TLabeledEdit *obd;

	void __fastcall saveClick(TObject *Sender);
	void __fastcall opr_kodChange(TObject *Sender);
	void __fastcall zak_noChange(TObject *Sender);
	void __fastcall part_noChange(TObject *Sender);
	void __fastcall tab_noChange(TObject *Sender);
private:	// User declarations
    cSQL *DB;
public:		// User declarations
	__fastcall TSurchargeList(TComponent* Owner, cSQL *db);

    String surcharge_id;
    String zak_id;
    String part_id;
};

#endif
