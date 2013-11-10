//---------------------------------------------------------------------------

#ifndef Add_matH
#define Add_matH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <ADODB.hpp>
#include <DB.hpp>

#include "SQL.h"
#include "functions.h"
//---------------------------------------------------------------------------
class TMater_add : public TForm
{
__published:	// IDE-managed Components
	TLabeledEdit *LE1;
	TLabeledEdit *LE2;
	TLabeledEdit *LE3;
	TLabeledEdit *LE4;
	TLabel *L1;
	TBitBtn *BitBtn1;
	TBitBtn *BitBtn2;
	TLabel *Label1;
	TLabel *Label2;
	TComboBox *ei_opt;
	TComboBox *ei;
	void __fastcall BitBtn1Click(TObject *Sender);
	void __fastcall ei_optClick(TObject *Sender);
private:	// User declarations
cSQL *  const DB;
const int &LUser;
void Load_support_info(void);
public:		// User declarations
	__fastcall TMater_add(TComponent* Owner,cSQL *db,const int &_LUser);
};
#endif
