//---------------------------------------------------------------------------

#ifndef technologyH
#define technologyH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "SQL.h"
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <ImgList.hpp>
#include <ActnPopup.hpp>
#include <Menus.hpp>
#include <PlatformDefaultStyleActnCtrls.hpp>

#include "zagotovk.h"
#include "professions.h"
#include "material.h"
#include "DetSelector.h"
#include "instrument.h"
#include "symblos.h"
#include "DtInfo.h"
#include "tecniksave.h"
#include "tara_and_strop.h"
#include <ActnList.hpp>
#include <StdActns.hpp>
#include <ToolWin.hpp>
#include "log.h"


class TTechWnd : public TFrame,public ClassConnector
{
__published:	// IDE-managed Components
	TPanel *Panel3;
	TSplitter *Splitter1;
	TStringGrid *operations;
	TStringGrid *instrum;
	TSplitter *Splitter3;
	TPanel *Panel2;
	TPanel *Panel4;
	TPanel *Panel1;
	TPageControl *PageControl3;
	TTabSheet *Detailparam;
	TLabeledEdit *napr;
	TLabeledEdit *rasceh;
	TTabSheet *TabSheet9;
	TLabel *L1;
	TLabel *L2;
	TLabel *L3;
	TLabel *L4;
	TLabeledEdit *masd;
	TLabeledEdit *obm;
	TTabSheet *TabSheet10;
	TLabeledEdit *kz;
	TLabeledEdit *razmzagot;
	TLabeledEdit *kdz;
	TLabeledEdit *masz;
	TLabeledEdit *norma;
	TLabeledEdit *LabeledEdit9;
	TLabeledEdit *kim;
	TTabSheet *transport;
	TLabel *strpLabel;
	TLabel *Label5;
	TLabel *Label2;
	TEdit *strop;
	TEdit *tara;
	TComboBox *control;
	TImageList *ImageList1;
	TPanel *Panel5;
	TLabel *DT_Name;
	TLabel *creator;
	TLabel *updater;
	TComboBox *ei;
	TLabel *Label1;
	TLabel *access;
	TComboBox *ei_opt;
	TLabel *Label3;
	TComboBox *fcb;
	TPopupActionBar *PAB;
	TMenuItem *N1;
	TMenuItem *N2;
	TMenuItem *N3;
	TMenuItem *N4;
	TMenuItem *N5;
	TPopupActionBar *PAB2;
	TMenuItem *C1;
	TMenuItem *N6;
	TMenuItem *N7;
	TMenuItem *N8;
	TActionList *ActionList1;
	TEditCut *EditCut1;
	TEditCopy *EditCopy1;
	TEditPaste *EditPaste1;
	TEditSelectAll *EditSelectAll1;
	TEditUndo *EditUndo1;
	TEditDelete *EditDelete1;
	TMenuItem *N9;
	TMenuItem *N10;
	TMenuItem *N11;
	TRichEdit *perexod;
	TMenuItem *N12;
	TToolBar *ToolBar1;
	TToolButton *Savebtn;
	TToolButton *printbtn;
	TTimer *Timer;
	void __fastcall operationsSelectCell(TObject *Sender, int ACol, int ARow, bool &CanSelect);
	//-рабрта с инфо
	void __fastcall ei_optClick(TObject *Sender);
	void __fastcall eiClick(TObject *Sender);
	void __fastcall masdEnter(TObject *Sender);
	void __fastcall masdExit(TObject *Sender);
	void __fastcall DoubleFildChange(TObject *Sender);
	void __fastcall maszEnter(TObject *Sender);
	void __fastcall maszExit(TObject *Sender);
	void __fastcall normaEnter(TObject *Sender);
	void __fastcall normaExit(TObject *Sender);
	void __fastcall naprChange(TObject *Sender);
	void __fastcall obmChange(TObject *Sender);
	void __fastcall kzChange(TObject *Sender);
	void __fastcall kdzChange(TObject *Sender);
	void __fastcall razmzagotChange(TObject *Sender);
	void __fastcall obmExit(TObject *Sender);
	void __fastcall naprExit(TObject *Sender);
	void __fastcall kzExit(TObject *Sender);
	void __fastcall operationsDrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect,
          TGridDrawState State);
	void __fastcall operationsDblClick(TObject *Sender);
	void __fastcall fcbChange(TObject *Sender);
	void __fastcall fcbExit(TObject *Sender);
	void __fastcall operationsSetEditText(TObject *Sender, int ACol, int ARow, const UnicodeString Value);
	void __fastcall N1Click(TObject *Sender);
	void __fastcall N2Click(TObject *Sender);
	void __fastcall N3Click(TObject *Sender);
	void __fastcall N4Click(TObject *Sender);
	void __fastcall N5Click(TObject *Sender);
	void __fastcall PABPopup(TObject *Sender);
	void __fastcall perexodChange(TObject *Sender);
	void __fastcall perexodEnter(TObject *Sender);
	void __fastcall perexodExit(TObject *Sender);
	void __fastcall instrumDblClick(TObject *Sender);
	void __fastcall instrumExit(TObject *Sender);
	void __fastcall taraDblClick(TObject *Sender);
	void __fastcall stropDblClick(TObject *Sender);
	void __fastcall C1Click(TObject *Sender);
	void __fastcall kzDblClick(TObject *Sender);
	void __fastcall obmDblClick(TObject *Sender);
	void __fastcall operationsRowMoved(TObject *Sender, int FromIndex, int ToIndex);
	void __fastcall N12Click(TObject *Sender);
	void __fastcall operationsKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall SavebtnClick(TObject *Sender);
	void __fastcall printbtnClick(TObject *Sender);
	void __fastcall TimerTimer(TObject *Sender);




    //---
private:	// User declarations
//статики
static int count;
static OperRow * O_buff;
static NrmRow * N_buff;
static PerexRow * P_buff;
static InstrumRow * I_buff;
static String Decimal_Separator;
cSQL *const DB;
const int &LUser;

// данные о строках внутренние классы
Obd *Ldet;
DtInfo *Info;
TObdSelector *Selector;
//блокировки элементов
bool TehSave,TehRead,TehEdit,TehDel,NormEdit;
bool ReadOnly;
//инициализация
void  	Init	(void);
void 	Load_support_info(void);
void 	Check_ei_box(void);
//функции заполнения интерфейса
void	ShowDetInfo(void);
void	ShowOperations(void);
void 	ShowData(OperRow *opr);
void    SetDefaultData(void);
void 	ShowMatInfo(void);
//цветоиндикация и указание на ошибки
void	InfoColors(void);
//работа с сеткой
bool	operSave(int nRow);
void 	UpdGreedData(int pRow);
void 	GreedClickControl(int ACol);
bool 	GreedDataControl(int ACol,int ARow);
//загрузка и удаление данных
void  Load (const Obd *const det);
void  Load_sel(Obd *det){Selector->LoadDet(det);log.push_back(Time().TimeString()+"---"+"Load_sel("+String((int)det)+")");};

void  Save_tex(void);

public:		// User declarations
	__fastcall TTechWnd(TComponent* Owner,TWinControl *_p,String _name, int &_LUser,cSQL *db);
	__fastcall ~TTechWnd();
	//закрытие вкладки;
	bool  Close_teh(void);
	static vector <String> log;
};
int TTechWnd::count=0;
OperRow * TTechWnd::O_buff=0;
NrmRow * TTechWnd::N_buff=0;
PerexRow * TTechWnd::P_buff=0;
InstrumRow * TTechWnd::I_buff=0;
String       TTechWnd::Decimal_Separator=DecimalSeparator;
vector <String> TTechWnd::log;
#endif
