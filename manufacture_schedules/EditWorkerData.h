//---------------------------------------------------------------------------

#ifndef EditWorkerDataH
#define EditWorkerDataH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>

#include "SQL.h"
//---------------------------------------------------------------------------
struct GroupData : TObject
{
    long group_id;
    std::string group_name;
};
class TWorkerData : public TForm
{
__published:	// IDE-managed Components
	TBitBtn *ok;
	TBitBtn *cancel;
	TLabeledEdit *tab_no;
	TLabeledEdit *worker_family;
	TLabeledEdit *worker_name;
	TLabeledEdit *worker_otch;
	TLabeledEdit *razr;
	TLabeledEdit *proff;
	TComboBox *ComboBox1;
	TLabel *Label1;
	void __fastcall ComboBox1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
    long group_id;
    __fastcall TWorkerData(TComponent* Owner, cSQL *DB);
    __fastcall ~TWorkerData();
};
#endif
