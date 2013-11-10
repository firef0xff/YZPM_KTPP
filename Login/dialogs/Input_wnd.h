//---------------------------------------------------------------------------

#ifndef Input_wndH
#define Input_wndH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TnewItem : public TForm
{
__published:	// IDE-managed Components
	TLabeledEdit *leItem;
	TBitBtn *BitBtn2;
	TBitBtn *BitBtn1;
	void __fastcall BitBtn1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TnewItem(TComponent* Owner);
};

#endif
