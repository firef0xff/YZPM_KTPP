//---------------------------------------------------------------------------


#pragma hdrstop

#include "Excel.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
		cExcel::cExcel			()
{
}
		cExcel::~cExcel			()
{
}

bool 	cExcel::Connect			(void)
{
try
	{
	App=Variant::CreateObject("Excel.Application");
	return true;
	}
catch (...)
	{
	return false;
	}
}
bool  	cExcel::Disconnect      (void)
{
if (!App.intVal){return false;}
try
	{
	App.OleProcedure("Quit");
	return true;
	}
catch (...)
	{
	return false;
	}
}

Variant cExcel::Books_New 		(void)
{
if (!App.intVal){return 0;}
try
	{
	App.OlePropertyGet("WorkBooks").OleProcedure("Add");
	return App.OlePropertyGet("Workbooks");
	}
catch (...)
	{
	return 0;
	}
}
Variant cExcel::Books_Open		(AnsiString url)
{
if (!App.intVal){return 0;}
try
	{
	App.OlePropertyGet("WorkBooks").OleProcedure("Open",url.c_str());    //уточнить  с c_str
	return App.OlePropertyGet("Workbooks");
	}
catch (...)
	{
	return 0;
	}
}
void 	cExcel::Books_Save		(AnsiString url)
{
	GetBook(1).OleProcedure("SaveAs",url.c_str());
}

Variant cExcel::GetBook			(int number)
{
if (!Books.intVal){return 0;}
try
	{
	return Books.OlePropertyGet("Item",number);
	} catch (...)
	{
	return 0;
	}
}
bool 	cExcel::Book_Close      (Variant Book)
{
if (!Book.intVal){return false;}
try
	{
	Book.OleProcedure("Close");
	return true;
	} catch (...)
	{
	return false;
	}
}

Variant cExcel::GetSheets		(void)
{
if (!Book.intVal) {return 0;}
try
	{
	return Book.OlePropertyGet("Worksheets");
	} catch (...)
	{
	return 0;
	}
}
int 	cExcel::GetSheetsCount	(void)
{
if (!Sheets.intVal) {return 0;}
try
	{
	return Sheets.OlePropertyGet("Count");
	} catch (...)
	{
	return 0;
	}
}

Variant cExcel::GetSheet		(int number)
{
if (!Sheets.intVal) {return 0;}
try
	{
	return Sheets.OlePropertyGet("Item",number);
	} catch (...)
	{
	return 0;
	}
}
void 	cExcel::Sheet_activate	(Variant sheet)
{
if (!Sheets.intVal||!sheet.intVal) {return;}
try
	{
	sheet.OleProcedure("Activate");
	}
catch (...)
	{
	return;
	}
}
void 	cExcel::Sheet_activate	(void)
{
Sheet_activate	(Sheet);
}
void 	cExcel::Sheet_Copy		(Variant sheet,Variant before,Variant after)
{
if (!Sheets.intVal||(!before.intVal&&!after.intVal&&!sheet.intVal)) {return;}
try
	{
	Sheet_activate(sheet);
	sheet.OleProcedure("Copy",before,after);
	}
catch (...)
	{
	return;
	}
}
void 	cExcel::Sheet_Add		(Variant sheets,Variant before,Variant after)
{
if (!Sheets.intVal||(!before.intVal&&!after.intVal&&!sheets.intVal)) {return;}
try
	{
	sheets.OleProcedure("Add",before,after);
	}
catch (...)
	{
	return;
	}
}
void 	cExcel::Set_Sheet_Name	(Variant sheet,String name)
{
if (!Sheets.intVal||!sheet.intVal) {return;}
try
	{
	Sheet_activate(sheet);
	sheet.OlePropertySet("Name",WideString(name));
	}
catch (...)
	{
	return;
	}
}
void 	cExcel::Sheet_Del		(Variant sheet)
{
if (!sheet.intVal) {return;}
try
	{
	sheet.OleProcedure("Delete");
	}
catch (...)
	{
	return;
	}
}

void 	cExcel::DisplayAlerts	(bool r)
{
if (!App.intVal){return;}
App.OlePropertySet("DisplayAlerts",r);
}
void 	cExcel::Visible			(bool r)
{
if (!App.intVal){return;}
App.OlePropertySet("Visible",r);
}

void 	cExcel::toCells			(int Row,int Col,AnsiString data)         //уточнить  с c_str
{
if (!Sheet.intVal){return;}
Variant cur=Sheet.OlePropertyGet("Cells",Row,Col);
cur.OlePropertySet("Value",data.c_str());
}
Variant cExcel::fromCells		(int Row,int Col)
{
if (!Sheet.intVal){return 0;}
Variant cur=Sheet.OlePropertyGet("Cells",Row,Col);
return cur.OlePropertyGet("Value");
}
Variant cExcel::GetRange		(int StartRow,int StartCol,int EndRow,int EndCol)
{
if (!Sheet.intVal){return 0;}
return Sheet.OlePropertyGet("Range",Sheet.OlePropertyGet("Cells",StartRow,StartCol),Sheet.OlePropertyGet("Cells",EndRow,EndCol));
}
Variant cExcel::GetColumn		(int Col)
{
if (!Sheet.intVal){return 0;}
return Sheet.OlePropertyGet("Columns",Col);
}
Variant cExcel::GetRows			(int StartRow,int EndRow)
{
return GetRows(Sheet,StartRow,EndRow);
}
Variant cExcel::GetRows			(Variant sheet,int StartRow,int EndRow)
{
if (!sheet.intVal){return 0;}
Sheet_activate(sheet);
Variant rez=sheet.OlePropertyGet("Rows",WideString(IntToStr(StartRow)+":"+IntToStr(EndRow)));
Sheet_activate();
return  rez;
}
void 	cExcel::Range_Merge		(Variant Range)
{
if (!Range.intVal){return;}
Range.OleProcedure("Merge");
}
void 	cExcel::Range_Select    (Variant Range)
{
if (!Range.intVal){return;}
Range.OleProcedure("Select");
}
void 	cExcel::Range_Copy      (Variant Range)
{
if (!Range.intVal){return;}
Range.OleProcedure("Copy");
}
void 	cExcel::Range_Paste     (Variant Range)
{
if (!Range.intVal){return;}
Range_Select(Range);
Sheet.OleProcedure("Paste");
}
void 	cExcel::Range_Border	(Variant Range,int type,int LineStyle,int Weight,int ColorIndex)
{
/*Константы, определяющие где проводить линию:   type
xlInsideHorizontal 12
xlInsideVertical 11
xlDiagonalDown 5
xlDiagonalUp 6
xlEdgeBottom 9
xlEdgeLeft 7
xlEdgeRight 10
xlEdgeTop 8
все внутренние линии 1
все правые линии 2  */

/*Константы стиля линии      LineStyle
xlContinuous 1
xlDash -4115
xlDashDot 4
xlDashDotDot 5
xlDot -4118
xlDouble -4119
xlSlantDashDot 13
xlLineStyleNone -4142  */
/*Толщина линии  int Weight
xlHairline 1
xlMedium -4138
xlThick 4
xlThin 2  */


if (!Range.intVal) {return;}
Range.OlePropertyGet("Borders",type).OlePropertySet("LineStyle",LineStyle);
Range.OlePropertyGet("Borders",type).OlePropertySet("Weight",Weight);
Range.OlePropertyGet("Borders",type).OlePropertySet("ColorIndex",ColorIndex);
}
void 	cExcel::Range_ColWidth	(Variant Range,int width)
{
if (!Range.intVal) {return;}
Range.OlePropertySet("ColumnWidth",width);
}
void	cExcel::Range_RowHeight	(Variant Range,int height)
{
if (!Range.intVal) {return;}
Range.OlePropertySet("RowHeight", height);
}
void 	cExcel::Set_format		(Variant Range,String format)
{
if (!Range.intVal) {return;}
Range.OlePropertySet("NumberFormat",WideString(format));
}
void 	cExcel::HorizontalAlignment (Variant Range,int type)
{
if (!Range.intVal) {return;}
Range.OlePropertySet("HorizontalAlignment",type);
/*Выравнивание текста - горизонтальное - Константы
xlVAlignBottom = -4107
xlVAlignCenter = -4108
xlVAlignDistributed = -4117
xlVAlignJustify = -4130
xlVAlignTop = -4160 */
}
void 	cExcel::VerticalAlignment 	(Variant Range,int type)
{
if (!Range.intVal) {return;}
Range.OlePropertySet("VerticalAlignment",type);
/*
Выравнивание текста - вертикальное - Константы
xlHAlignCenter -4108
xlHAlignCenterAcrossSelection 7
xlHAlignDistributed -4117
xlHAlignFill 5
xlHAlignGeneral 1
xlHAlignJustify -4130
xlHAlignLeft -4131
xlHAlignRight -4152   */
}
