//---------------------------------------------------------------------------

#ifndef add_data_wndH
#define add_data_wndH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include "def_types.h"
//---------------------------------------------------------------------------
class TCalckAddParams : public TForm
{
__published:	// IDE-managed Components
	TLabeledEdit *Cex;
	TLabeledEdit *Utch;
	TLabeledEdit *Percent;
	TLabeledEdit *Kol;
	TBitBtn *BitBtn1;
	void __fastcall BitBtn1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TCalckAddParams(TComponent* Owner);
};

#endif
