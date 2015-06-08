//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "orders_history.h"
#include "functions.h"
#include "manufacture.h"


//---------------------------------------------------------------------------
#pragma resource "*.dfm"


__fastcall TwinEditOrdersHistory::TwinEditOrdersHistory(TComponent* Owner, cSQL *db, int orderNum, int narListRow)
	: TForm(Owner), orderNum(orderNum), narListRow(narListRow)
{
	DB = db;
	LoadOrdersHistory();
}

void TwinEditOrdersHistory::LoadOrdersHistory()
{
	SGClear(SGOrdersHistory);

	SGOrdersHistory->Cells[0][0] = "Наряд";
	SGOrdersHistory->Cells[1][0] = "Табельный номер";
	SGOrdersHistory->Cells[2][0] = "Рабочий";
	SGOrdersHistory->Cells[3][0] = "Дата";
	SGOrdersHistory->Cells[4][0] = "Изготовлено";
	SGOrdersHistory->Cells[5][0] = "Брак";

	String sql = "select h.order_id, h.tab_no, h.date, h.maked, h.broken, CONVERT(IFNULL(concat(e.family, ' ',Upper(left(e.name,1)),'.', Upper(left(e.otch,1)),'.'),''), CHAR) as worker from manufacture.orders_history h left join manufacture.workers e on(e.tab_no = h.tab_no) where h.order_id =" + String(orderNum) + ";";
	TADOQuery *rez = DB->SendSQL(sql);
	if (rez && rez->RecordCount)
	{
		for (rez->First(); !rez->Eof; rez->Next())
		{
			int row = SGOrdersHistory->RowCount - 1;
			SGOrdersHistory->Cells[0][row] = rez->FieldByName("order_id")->Value;
			SGOrdersHistory->Cells[1][row] = rez->FieldByName("tab_no")->Text;
			SGOrdersHistory->Cells[2][row] = rez->FieldByName("worker")->Text;
			SGOrdersHistory->Cells[3][row] = rez->FieldByName("date")->Value;
			SGOrdersHistory->Cells[4][row] = rez->FieldByName("maked")->Value;
			SGOrdersHistory->Cells[5][row] = rez->FieldByName("broken")->Value;
			SGOrdersHistory->RowCount ++;
		}
	}
	if (SGOrdersHistory->RowCount > 2){
		--SGOrdersHistory->RowCount;
	}

	delete rez;
	AutoWidthSG(SGOrdersHistory);
}

void __fastcall TwinEditOrdersHistory::N1Click(TObject *Sender)
{
	
	int ACol,ARow;
	SGOrdersHistory->MouseToCell(SGOrdersHistoryLastRightMouse.X,SGOrdersHistoryLastRightMouse.Y,ACol,ARow);
	if(ARow < 1) {
		return;
	}

	int orderId = SGOrdersHistory->Cells[0][ARow].ToIntDef(0);
	if(orderId < 1) {
        return;
    }

	if ( mrYes  != MessageBoxA(this->Handle, "Вы действительно хотите удалить запись?", "Подтверждение операции", MB_YESNO|MB_ICONQUESTION)) {
        return;
    }

    int tabNum  = SGOrdersHistory->Cells[1][ARow].ToInt();
	int maked	= SGOrdersHistory->Cells[4][ARow].ToInt();
	int broken  = SGOrdersHistory->Cells[5][ARow].ToInt();

	std::stringstream deleteRecSql;
	deleteRecSql <<  "delete from manufacture.orders_history where";
	deleteRecSql <<  " order_id = "     << orderId;
	deleteRecSql <<  " and tab_no = "       << tabNum;
	deleteRecSql <<  " and date = STR_TO_DATE( " 		<< '"'	<< AnsiString(SGOrdersHistory->Cells[3][ARow]).c_str() <<  '"' << ",'\%d.\%m.\%Y')";
	deleteRecSql <<  " and maked = " 	<< maked;
	deleteRecSql <<  " and broken = "	<< broken;
	deleteRecSql <<  " limit 1;";

	std::stringstream updateCountsSql;
	updateCountsSql << "update manufacture.orders set";
	updateCountsSql << " kol_maked = kol_maked - " << maked;
	updateCountsSql << ", kol_broken = kol_broken - " << broken;
	updateCountsSql << ", kol_unmaked = kol_unmaked + " << maked + broken;
	updateCountsSql << ", closed_date = NULL";
	updateCountsSql << ", closed_type = NULL";
	updateCountsSql << " where order_id = " << orderId << ";"; 

	Transaction tr(DB);
	if ( DB->SendCommand(deleteRecSql.str().c_str()) && DB->SendCommand(updateCountsSql.str().c_str()) ) {
		tr.Commit();
	}
    LoadOrdersHistory();
    ((TManufactureControl*)this->Owner)->NarUpdate(narListRow);

}
//---------------------------------------------------------------------------



void __fastcall TwinEditOrdersHistory::SGOrdersHistoryMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	if(Button == TMouseButton::mbRight) {
		SGOrdersHistoryLastRightMouse.X = X;
		SGOrdersHistoryLastRightMouse.Y = Y;
	}
}

