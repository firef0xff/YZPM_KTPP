//---------------------------------------------------------------------------

#ifndef User_DataH
#define User_DataH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include "SQL.h"
//---------------------------------------------------------------------------
class TUserData : public TForm
{
__published:	// IDE-managed Components
	TLabeledEdit *leLogin;
	TBitBtn *BitBtn2;
	TBitBtn *BitBtn1;
	TLabeledEdit *lePass;
	TLabeledEdit *leName;
	TLabeledEdit *leFam;
	TLabeledEdit *leOtch;
	TComboBox *cbGroup;
	TLabel *Label1;
	void __fastcall BitBtn1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TUserData(TComponent* Owner,cSQL *DB);
};
#endif
