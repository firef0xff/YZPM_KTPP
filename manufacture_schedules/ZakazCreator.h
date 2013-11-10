//---------------------------------------------------------------------------

#ifndef ZakazCreatorH
#define ZakazCreatorH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>

#include "SQL.h"
//---------------------------------------------------------------------------
class TZakazWnd : public TForm
{
__published:	// IDE-managed Components
	TLabeledEdit *zakaz;
	TBitBtn *BitBtn2;
	TBitBtn *BitBtn1;
	TLabeledEdit *part;
	void __fastcall BitBtn1Click(TObject *Sender);
	void __fastcall zakazChange(TObject *Sender);
private:	// User declarations
	cSQL *DB;
public:		// User declarations
	__fastcall TZakazWnd(TComponent* Owner, cSQL *db);
};

#endif
