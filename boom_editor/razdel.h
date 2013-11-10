//---------------------------------------------------------------------------

#ifndef razdelH
#define razdelH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ADODB.hpp>
//---------------------------------------------------------------------------
class Trzd : public TForm
{
__published:	// IDE-managed Components
	TBitBtn *BitBtn1;
	TBitBtn *BitBtn2;
	TComboBox *CB1;
	void __fastcall BitBtn1Click(TObject *Sender);
private:	// User declarations
String RazdName;
int    RazdID;
TADOQuery *SpRazd;
public:		// User declarations
String Get_RazdName(void) const {return RazdName;};
int 	Get_RazdID(void) const {return RazdID;};
	__fastcall Trzd(TComponent* Owner,TADOQuery *SpRazd);
};
#endif
