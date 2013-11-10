//---------------------------------------------------------------------------

#ifndef redaktor_formulH
#define redaktor_formulH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include <Grids.hpp>

#include "functions.h"
#include <ctype.h >
#include "SQL.h"
//---------------------------------------------------------------------------
class TFomul_Editor : public TForm
{
__published:	// IDE-managed Components
	TLabeledEdit *LE1;
	TLabeledEdit *LE2;
	TLabeledEdit *LE3;
	TComboBox *CB1;
	TLabel *Label1;
	TBitBtn *BitBtn1;
	TLabel *Label2;
	TStringGrid *SG1;
	TLabeledEdit *LE4;
	TStringGrid *SG0;
	TLabel *Label3;
	TBitBtn *BitBtn2;
	TLabeledEdit *LE5;
	void __fastcall LE1Change(TObject *Sender);
	void __fastcall CB1Click(TObject *Sender);
	void __fastcall LE2Change(TObject *Sender);
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall SG1SetEditText(TObject *Sender, int ACol, int ARow, const UnicodeString Value);
	void __fastcall BitBtn1Click(TObject *Sender);
	void __fastcall BitBtn2Click(TObject *Sender);

private:	// User declarations
cSQL *const DB;
bool start_sql;
String vz;
void init (void);
public:		// User declarations
	__fastcall TFomul_Editor(TComponent* Owner,cSQL *db,String _vz);

};
#endif
