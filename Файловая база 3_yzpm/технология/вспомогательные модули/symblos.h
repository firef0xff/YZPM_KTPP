//---------------------------------------------------------------------------

#ifndef symblosH
#define symblosH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------
class TSymbol : public TForm
{
__published:	// IDE-managed Components
	TStringGrid *SG1;
	TBitBtn *BitBtn1;
	TBitBtn *BitBtn2;
	TEdit *E1;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall SG1DblClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TSymbol(TComponent* Owner);
};
//---------------------------------------------------------------------------
#endif
