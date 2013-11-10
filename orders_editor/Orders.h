//---------------------------------------------------------------------------

#ifndef OrdersH
#define OrdersH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <Menus.hpp>

#include "Obd.h"
#include "IconsData.h"
#include "Order_set.h"
#include "OrderContent_set.h"
#include <ImgList.hpp>
//---------------------------------------------------------------------------
class TOrders_editor : public TFrame
{
__published:	// IDE-managed Components
	TPopupMenu *Pab1;
	TMenuItem *N1;
	TMenuItem *N2;
	TPopupMenu *Pab2;
	TMenuItem *N3;
	TMenuItem *N4;
	TPanel *Panel1;
	TPanel *Panel6;
	TLabel *Label1;
	TPanel *Panel7;
	TPanel *Panel8;
	TGroupBox *GroupBox2;
	TSpeedButton *next;
	TSpeedButton *prev;
	TLabeledEdit *E2;
	TLabeledEdit *E3;
	TPanel *Panel3;
	TRadioGroup *FindType;
	TLabeledEdit *SeartchStr;
	TButton *Find;
	TStringGrid *ZakazList;
	TPanel *Panel2;
	TLabel *Label2;
	TStringGrid *Detalise;
	TSplitter *Splitter1;
	TImageList *ImageList1;
	TMenuItem *N5;
	TMenuItem *N6;
	void __fastcall FindClick(TObject *Sender);
	void __fastcall ZakazListSelectCell(TObject *Sender, int ACol, int ARow, bool &CanSelect);
	void __fastcall pageClick(TObject *Sender);
	void __fastcall E2Change(TObject *Sender);
	void __fastcall EnterPress(TObject *Sender, wchar_t &Key);
	void __fastcall N1Click(TObject *Sender);
	void __fastcall N5Click(TObject *Sender);
	void __fastcall N2Click(TObject *Sender);
	void __fastcall N3Click(TObject *Sender);
	void __fastcall N4Click(TObject *Sender);
	void __fastcall N6Click(TObject *Sender);

private:	// User declarations
	int **selected;

	const int &LUser;
	static IconsData *IcoData;
	static int count;
	static cSQL *DB;

	bool OrderEdit;
	bool OrderView;

public:		// User declarations
	__fastcall TOrders_editor(TComponent* Owner,TWinControl *_p, int &_LUser,cSQL *db,IconsData *_IcoData,int **_selected);
	__fastcall ~TOrders_editor(void);
};
int TOrders_editor::count=0;
IconsData *TOrders_editor::IcoData=0;
cSQL *TOrders_editor::DB=0;


#endif
