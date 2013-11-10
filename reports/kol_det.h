//---------------------------------------------------------------------------

#ifndef kol_detH
#define kol_detH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include "SQL.h"
#include "functions.h"
//---------------------------------------------------------------------------
class Tkoldet : public TForm
{
__published:	// IDE-managed Components
	TComboBox *CB1;
	TComboBox *CB2;
	TLabel *L1;
	TLabel *L2;
	TEdit *E1;
	TLabel *Label1;
	TBitBtn *BitBtn1;
	TBitBtn *BitBtn2;
	TBitBtn *BitBtn3;
	void __fastcall CB1Click(TObject *Sender);
	void __fastcall CB2Click(TObject *Sender);
	void __fastcall GetKol(void);
	void __fastcall FormShow(TObject *Sender);
private:	// User declarations
public:		// User declarations
cSQL *DB;
String obd;
	__fastcall Tkoldet(TComponent* Owner);
};
#endif
