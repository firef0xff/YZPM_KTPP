//---------------------------------------------------------------------------

#ifndef contractorsH
#define contractorsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ADODB.hpp>
#include <Buttons.hpp>
#include <DB.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>

#include "functions.h"
#include "SQL.h"
//---------------------------------------------------------------------------
class TContragents : public TForm
{
__published:	// IDE-managed Components
	TADOConnection *ADC1C;
	TBitBtn *OK;
	TPanel *Panel1;
	TLabel *Label1;
	TPanel *Panel8;
	TGroupBox *GroupBox2;
	TSpeedButton *next;
	TSpeedButton *prev;
	TLabeledEdit *E2;
	TLabeledEdit *E3;
	TEdit *Name_params;
	TBitBtn *FIND;
	TBitBtn *ADD;
	TBitBtn *DEL;
	TPanel *Panel2;
	TStringGrid *SG;
	TPanel *Panel3;
	TButton *split;
	TLabeledEdit *Inn;
	TLabeledEdit *Kpp;
	TLabeledEdit *sName;
	TLabeledEdit *fName;
	TLabeledEdit *Addr_yur;
	TLabeledEdit *Addr_fiz;
	TLabeledEdit *Phones;
	TBitBtn *Save;
	TBitBtn *Edit;
	TBitBtn *Cancel;
	TBitBtn *Upd1C;
	void __fastcall splitClick(TObject *Sender);
	void __fastcall ADDClick(TObject *Sender);
	void __fastcall EditClick(TObject *Sender);
	void __fastcall SaveClick(TObject *Sender);
	void __fastcall Upd1CClick(TObject *Sender);
	void __fastcall SGSelectCell(TObject *Sender, int ACol, int ARow, bool &CanSelect);
	void __fastcall CancelClick(TObject *Sender);
	void __fastcall FINDClick(TObject *Sender);
	void __fastcall Name_paramsKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall E2Change(TObject *Sender);
	void __fastcall E3Change(TObject *Sender);
	void __fastcall nextClick(TObject *Sender);
	void __fastcall OKClick(TObject *Sender);
	void __fastcall SGDrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect, TGridDrawState State);
	void __fastcall DELClick(TObject *Sender);



private:	// User declarations
	static int count;
	static cSQL *DB;
	static cSQL *DB1C;
	const int &LUser;

	String mode;
	unsigned __int64 id;
	unsigned __int64 Select_id;
	String Select_name;
	TADOQuery *data;

	void 	init(void);
	void 	Update_contractors(void);
	void	Find(void);
	void	ShowData(void);
	void	ShowRowData(int row);

public:		// User declarations
	__fastcall TContragents(TComponent* Owner,const int &_LUser,cSQL *db);
	__fastcall ~TContragents(void);
	 void Get_id(unsigned __int64 &_id,String &_name){_id=Select_id; _name=Select_name;}
};
int TContragents::count=0;
cSQL *TContragents::DB1C=0;
cSQL *TContragents::DB=0;
#endif
