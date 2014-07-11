//---------------------------------------------------------------------------

#ifndef testH
#define testH
//---------------------------------------------------------------------------

#include <ADODB.hpp>
#include <Classes.hpp>
#include <ComCtrls.hpp>
#include <Controls.hpp>
#include <DB.hpp>
#include <StdCtrls.hpp>
#include <Dialogs.hpp>


#include "products.h"
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TPageControl *PageControl1;
	TADOConnection *ADC;
	TOpenDialog *OD;
	TTabSheet *TabSheet2;
	TEdit *Obd;
	TButton *RepStart;
	TButton *ClearLog;
	TButton *GetLog;
	TMemo *Log;
	TEdit *RepNo;
	void __fastcall GetLogClick(TObject *Sender);
	void __fastcall RepStartClick(TObject *Sender);
	void __fastcall ClearLogClick(TObject *Sender);



private:
cSQL * DB;
int LUser;
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
#endif
