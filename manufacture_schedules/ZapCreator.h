//---------------------------------------------------------------------------

#ifndef ZapCreatorH
#define ZapCreatorH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TZapuskWnd : public TForm
{
__published:	// IDE-managed Components
	TDateTimePicker *dtStart;
	TDateTimePicker *dtEnd;
	TLabeledEdit *name;
	TLabel *lb_dt_start;
	TLabel *Label1;
	TBitBtn *BitBtn2;
	TBitBtn *BitBtn1;
private:	// User declarations
public:		// User declarations
	__fastcall TZapuskWnd(TComponent* Owner);
};

#endif
