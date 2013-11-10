//---------------------------------------------------------------------------

#ifndef paramsH
#define paramsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class Tparametr : public TForm
{
__published:	// IDE-managed Components
	TLabeledEdit *cex;
	TLabeledEdit *zak;
	TLabeledEdit *part;
	TLabeledEdit *kol;
	TBitBtn *BitBtn1;
	void __fastcall FormShow(TObject *Sender);
private:	// User declarations
public:		// User declarations
int type;
	__fastcall Tparametr(TComponent* Owner);
};
#endif
