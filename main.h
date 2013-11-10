#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
#include <ActnPopup.hpp>
#include <ADODB.hpp>
#include <Classes.hpp>
#include <ComCtrls.hpp>
#include <Controls.hpp>
#include <DB.hpp>
#include <ExtCtrls.hpp>
#include <ImgList.hpp>
#include <Menus.hpp>
#include <PlatformDefaultStyleActnCtrls.hpp>
#include <StdCtrls.hpp>
#include <ToolWin.hpp>
#include <XPMan.hpp>

#include "Tabs.h"
#include "loginwin.h"
#include "material.h"
#include "zagotovk.h"
#include "professions.h"
#include "log.h"
#include "otchethost.h"
#include "Settings_wnd.h"
#include <Graphics.hpp>
#include <Buttons.hpp>

class TmForm : public TForm
{
__published:    
    TSplitter *Splitter1;
    TXPManifest *XPManifest1;
    TMainMenu *MainMenu1;
    TMenuItem *N1;
    TMenuItem *N7;
    TMenuItem *N8;
    TMenuItem *N9;
    TMenuItem *N10;
    TMenuItem *N15;
    TMenuItem *N16;
    TMenuItem *N17;
    TMenuItem *N18;
    TMenuItem *N19;
    TMenuItem *N20;
    TMenuItem *N21;
    TMenuItem *N22;
    TPageControl *RightPC;
    TTabSheet *InfoTab;
    TMemo *Info;
    TMenuItem *N2;
    TMenuItem *N3;
    TMenuItem *N4;
    TMenuItem *N5;
    TMenuItem *N6;
    TMenuItem *N23;
    TMenuItem *N24;
    TMenuItem *N29;
    TMenuItem *N30;
    TMenuItem *N31;
    TMenuItem *N32;
    TPageControl *LeftPC;
    TImageList *Img;
    TImageList *btns;
    TMenuItem *N26;
    TMenuItem *N27;
    TToolBar *ToolBar1;
    TToolButton *TreeBTN;
    TToolButton *TechnologicBTN;
    TToolButton *TechnologicVievBTN;
    TToolButton *SearchBTN;
    TToolButton *ShowInfo;
    TPanel *Indikators;
    TPanel *MailPannel;
    TMenuItem *N14;
    TADOConnection *ADC;
    TTimer *gonaway;
    TToolButton *ToolButton1;
    TToolButton *ProcessingBTN;
    TMenuItem *N11;
    TMenuItem *N12;
    TToolButton *OrdersBTN;
    TMenuItem *N13;
    TMenuItem *N25;
    TMenuItem *N28;
    TMenuItem *N33;
    TMenuItem *N34;
    TMenuItem *N35;
    TToolButton *ManufactureBTN;
    TToolButton *ToolButton2;
    TMenuItem *N36;
    TMenuItem *N37;
    
    void __fastcall PCDrawTab(TCustomTabControl *Control, int TabIndex, const TRect &Rect,
          bool Active);
    void __fastcall PCMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
    void __fastcall PCMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
    void __fastcall PCMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
    void __fastcall PCMouseLeave(TObject *Sender);
    void __fastcall PCDragOver(TObject *Sender, TObject *Source, int X, int Y, TDragState State,
          bool &Accept);
    void __fastcall PCDragDrop(TObject *Sender, TObject *Source, int X, int Y);
    void __fastcall FormDragOver(TObject *Sender, TObject *Source, int X, int Y, TDragState State,
          bool &Accept);
    void __fastcall FormDragDrop(TObject *Sender, TObject *Source, int X, int Y);
    
    void __fastcall PCChange(TObject *Sender);
    void __fastcall InfoClick(TObject *Sender);
    void __fastcall SpTreeClick(TObject *Sender);
    void __fastcall TechClick(TObject *Sender);
    void __fastcall TechViewClick(TObject *Sender);
    void __fastcall SearchClick(TObject *Sender);
    void __fastcall TreeBTNClick(TObject *Sender);
    void __fastcall TechnologicBTNClick(TObject *Sender);
    void __fastcall TechnologicVievBTNClick(TObject *Sender);
    void __fastcall SearchBTNClick(TObject *Sender);
    void __fastcall ShowInfoClick(TObject *Sender);
    void __fastcall PCEnter(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall N8Click(TObject *Sender);
    void __fastcall N9Click(TObject *Sender);
    void __fastcall N10Click(TObject *Sender);
    void __fastcall MailPannelClick(TObject *Sender);
    void __fastcall otchet(TObject *Sender);
    void __fastcall gonawayTimer(TObject *Sender);
    void __fastcall ProcessingBTNClick(TObject *Sender);
    void __fastcall ProcessingClick(TObject *Sender);
    void __fastcall N14Click(TObject *Sender);
    void __fastcall OrdersBTNClick(TObject *Sender);
    void __fastcall OrdersClick(TObject *Sender);
    void __fastcall ManufactureBTNClick(TObject *Sender);
    void __fastcall ManufactureClick(TObject *Sender);

    

private:    
int UserID;
IconsData *IcoData;
vector <Tab*> Tabs;
int *selected;

void  LoadIL       (void);
TRect DrawCloseTabBtn(TPageControl *PC,const TRect *Rect,int X,int Y,int TabNo,char type);

void         SetLastTab    (TTabSheet *tab);
void         CloseTab     (TTabSheet *tab);

typedef bool (*RepStart_func)(AnsiString type,AnsiString param);
typedef void (*init_func)(AnsiString user,cSQL *DbWork);
RepStart_func RepStart;
init_func      RepInit;
public:
    __fastcall TmForm(TComponent* Owner);
    __fastcall ~TmForm(void);

cSQL *DB;

TTabSheet * GetLastTab    (char type);
Tab*        GetTab         (TTabSheet *tab);

void     AddTree                 (TPageControl *Page,Obd *Det,TMemo *memo);

void     AddTexTab            (TPageControl *Page,Obd *Det);
void     LoadTexToCurrTab    (Obd *Det);

void     AddTexViewTab        (TPageControl *Page,Obd *Det);
void     LoadexViewToCurrTab    (Obd *Det);

void    AddSearch            (TPageControl *Page);

void     AddProcessing        (TPageControl *Page);

void    AddOrders            (TPageControl *Page);

void    AddManufacture        (TPageControl *Page);

};

void     _AddTexTab                (const Obd *Det);
void     _AddTexViewTab            (const Obd *Det);
void     _LoadTexToCurrTab        (const Obd *Det);
void     _LoadexViewToCurrTab    (const Obd *Det);
void     _ShowTree                (const Obd *Det);
#endif
