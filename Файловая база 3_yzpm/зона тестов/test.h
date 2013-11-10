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
	TTabSheet *TabSheet1;
	TTabSheet *ts;
	TTabSheet *ts2;
	TEdit *Edit1;
	TButton *Button1;
	TADOConnection *ADC;
	TMemo *Memo1;
	TTabSheet *ts1;
	TComboBox *ComboBox1;
	TButton *Button2;
	TButton *Button3;
	TButton *Button4;
	TButton *Button5;
	TButton *Button6;
	TButton *Button7;
	TButton *Button8;
	TOpenDialog *OD;
	TTabSheet *ts3;
	TTabSheet *TabSheet4;
	TTabSheet *TabSheet2;
	TEdit *Edit2;
	TButton *Button9;
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button9Click(TObject *Sender);



private:
cSQL * DB;
int LUser;
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
#endif
