//---------------------------------------------------------------------------

#ifndef sp_paramsH
#define sp_paramsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class Tspparams : public TForm
{
__published:	// IDE-managed Components
	TBitBtn *cancel;
	TBitBtn *ok;
	TLabeledEdit *LE1;
	TLabeledEdit *LE2;
private:	// User declarations
public:		// User declarations
	__fastcall Tspparams(TComponent* Owner);
String Get_Obd(void)const {return LE1->Text.Trim();};
String Get_Name(void)const{return LE2->Text.Trim();};
};
#endif
