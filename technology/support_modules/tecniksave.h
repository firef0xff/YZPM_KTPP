//---------------------------------------------------------------------------

#ifndef tecniksaveH
#define tecniksaveH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include "SQL.h"
#include "functions.h"
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TTB : public TForm
{
__published:	// IDE-managed Components
	TStringGrid *SG1;
	TPanel *Panel1;
	TComboBox *Params;
	TLabel *Label1;
	TBitBtn *ok;
	TBitBtn *cancel;
	TBitBtn *savelist;
	void __fastcall SG1DrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect, TGridDrawState State);
	void __fastcall SG1DblClick(TObject *Sender);
	void __fastcall SaveClick(TObject *Sender);
	void __fastcall ParamsClick(TObject *Sender);
private:	// User declarations
cSQL *const DB;
String oprid;
String ioht;
public:		// User declarations
	__fastcall TTB(TComponent* Owner,String _oprid,String _ioht,cSQL *db);
String Get_ioht(void)const{return ioht;}
};
//---------------------------------------------------------------------------
#endif
