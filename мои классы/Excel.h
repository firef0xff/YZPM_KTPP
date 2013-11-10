//---------------------------------------------------------------------------

#ifndef ExcelH
#define ExcelH
#include <StdCtrls.hpp>

class cExcel
	{
	public:
		cExcel();
		~cExcel();
		
	bool 	Connect				(void);
	bool  	Disconnect          (void);
	Variant GetConnection		(void){return App;};
	void 	SetActiveConnection	(Variant excel){App=excel;};
		
	Variant Books_New 			(void);
	Variant Books_Open			(AnsiString url);
	void 	SetActiveBooks		(Variant r){Books=r;};
	void 	Books_Save			(AnsiString url);
		
	void 	SetActiveBook		(Variant r){Book=r;};
	Variant GetBook				(int number);
	Variant GetFirstBook		(void)			{return GetBook(1);}
	bool 	Book_Close          (Variant Book);
		//доступ в массиву листов
	void 	SetActiveSheets		(Variant r)		{Sheets=r;};
	Variant GetSheets			(void);
	int 	GetSheetsCount		(void);
		//доступ к листу
	void 	SetActiveSheet		(Variant r)		{Sheet=r;};
	Variant GetSheet			(int number);
	Variant GetFirstSheet		(void)			{return GetSheet(1);};
	Variant GetActiveSheet		(void)			{return Sheet;};
	void 	Sheet_Copy			(Variant sheet,Variant before=Variant().NoParam(),Variant after=Variant().NoParam());
	void 	Sheet_Add			(Variant sheets,Variant before=Variant().NoParam(),Variant after=Variant().NoParam());
	void 	Set_Sheet_Name		(Variant sheet,String name);
	void 	Sheet_activate		(Variant sheet);
	void 	Sheet_activate		(void);
	void 	Sheet_Del			(Variant sheet);
		
	void 	toCells				(int Row,int Col,AnsiString data);
	Variant fromCells			(int Row,int Col);
		
	void 	DisplayAlerts		(bool);
	void 	Visible				(bool);
	void 	Range_Merge			(Variant Range);
	void 	Range_Select        (Variant Range);
	void 	Range_Copy        	(Variant Range);
	void 	Range_Paste         (Variant Range);
	void 	Range_Border		(Variant Range,int type,int LineStyle,int Weight,int ColorIndex);
	void 	Range_ColWidth		(Variant Range,int width);
	void	Range_RowHeight		(Variant Range,int height);
	void 	Set_format			(Variant Range,String format);
	void	Set_Font			(Variant Range,TFont font);
	void 	HorizontalAlignment (Variant Range,int type);
    void 	VerticalAlignment 	(Variant Range,int type);
	Variant GetRange			(int StartRow,int StartCol,int EndRow,int EndCol);
	Variant GetColumn			(int Col);
	Variant GetRows				(int StartRow,int EndRow);
	Variant GetRows				(Variant sheet,int StartRow,int EndRow);
	protected:
	private:
		Variant App,Books,Book,Sheets,Sheet;
	};
#endif
