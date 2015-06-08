//---------------------------------------------------------------------------

#ifndef orders_historyH
#define orders_historyH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Grids.hpp>
#include "SQL.h"
#include <Menus.hpp>
#include "sstream.h"

//---------------------------------------------------------------------------
class TwinEditOrdersHistory : public TForm
{
__published:	// IDE-managed Components
	TStringGrid *SGOrdersHistory;
	TPopupMenu *CMOrdHistory;
	TMenuItem *N1;
	void __fastcall N1Click(TObject *Sender);
	void __fastcall SGOrdersHistoryMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y);


private:	// User declarations
	int orderNum;
	int narListRow;
	cSQL *DB;
	// Хранит последние координаты правого клика мышки на списке
	TPoint SGOrdersHistoryLastRightMouse;
	void LoadOrdersHistory();
public:		// User declarations
	__fastcall TwinEditOrdersHistory(TComponent* Owner, cSQL *db, int orderNum, int narListRow);
};

#endif
