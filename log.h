//---------------------------------------------------------------------------

#ifndef logH
#define logH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "SQL.h"
#include <ComCtrls.hpp>
#include <ToolWin.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TLogForm : public TForm
{
__published:    // IDE-managed Components
    TMemo *Memo1;
	TPanel *Panel1;
	TBitBtn *BitBtn1;
	void __fastcall ClearClick(TObject *Sender);
private:    // User declarations
	void repaintText();
	cSQL *DB;
public:        // User declarations
	__fastcall TLogForm(TComponent* Owner,cSQL *DB);
};
#endif
