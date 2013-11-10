//---------------------------------------------------------------------------

#ifndef SPEditH
#define SPEditH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "SQL.h"
#include "Excel.h"
#include <ADODB.hpp>
#include <DB.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include "functions.h"
#include <ComCtrls.hpp>
#include <ImgList.hpp>
#include <ToolWin.hpp>


#include "SPROW.h"
#include "razdel.h"
#include "sp_params.h"
#include "Isp_editor.h"
#include "functions.h"
#include "math.h"
#include <ActnPopup.hpp>
#include <Menus.hpp>
#include <PlatformDefaultStyleActnCtrls.hpp>
//---------------------------------------------------------------------------
enum Type{Add,Edit,View};
class TSPEditor : public TForm
{
__published:    // IDE-managed Components
    TOpenDialog     *OD1;
    TPanel             *Panel1;
    TStringGrid     *SG1;
    TLabeledEdit     *LE1;
    TLabeledEdit     *LE2;
    TComboBox         *CB2;
    TLabel             *Label1;
    TToolBar         *ToolBar1;
    TToolButton     *OpenEX;
    TImageList         *ImageList1;
    TToolButton *Export;
    TToolButton     *New;
    TToolButton     *ToolButton1;
    TToolButton     *Remove;
    TToolButton *ChangeRZD;
    TCheckBox         *autosort;
    TEdit             *Editor;
    TToolButton     *FomBase;
    TToolButton     *SeveToBase;
    TComboBox         *Combo;
    TComboBox *ei_opt;
    TLabel *Label3;
    TToolButton *Recover;
    TPopupActionBar *PAB;
    TMenuItem *N1;
    TMenuItem *N2;
    TMenuItem *N3;
    TMenuItem *N4;
    TMenuItem *Export_xls;
    TMenuItem *N5;
    TMenuItem *N6;
    TMenuItem *N7;
    TMenuItem *N8;
    TMenuItem *N9;
    TMenuItem *N10;
    TMenuItem *N11;
    TMenuItem *N12;
    TMenuItem *N13;
    // кнопки
    void __fastcall NewClick(TObject *Sender);
    void __fastcall OpenEXClick(TObject *Sender);
    void __fastcall ExportClick(TObject *Sender);
    void __fastcall RemoveClick(TObject *Sender);
    void __fastcall ChangeRZDClick(TObject *Sender);
    void __fastcall FomBaseClick(TObject *Sender);
    // отработка сетки
    void __fastcall SG1DrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect, TGridDrawState State);
    void __fastcall SG1KeyPress(TObject *Sender, wchar_t &Key);
    void __fastcall SG1DblClick(TObject *Sender);
    void __fastcall EditorKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
    void __fastcall EditorExit(TObject *Sender);
    void __fastcall SeveToBaseClick(TObject *Sender);
    void __fastcall ComboClick(TObject *Sender);
    void __fastcall ComboExit(TObject *Sender);
    void __fastcall RecoverClick(TObject *Sender);
    void __fastcall autosortClick(TObject *Sender);
    void __fastcall LE1Exit(TObject *Sender);
    void __fastcall LE2Exit(TObject *Sender);
    void __fastcall CB2Change(TObject *Sender);
    void __fastcall N13Click(TObject *Sender);
    void __fastcall N12Click(TObject *Sender);
    void __fastcall N11Click(TObject *Sender);



private:    // User declarations
//рабочие переменные
        cSQL             *const DB;
        TADOQuery         *SPRazd;
        cExcel             *XL;
        vector <SpRow*> *SPList;
        vector <SpRow*> *File;
        vector <SpRow*> *Base;
        vector <IspData> ISP;
        Obd                *Object;
        const int         &LUser;
        String            UserName;
        int             StateID;
        String            StateName;

        String             Action_det;
        String            Obu_old;
        bool             ReadOnly;
// работа с сеткой
void     RemoveRow    (int TRow,int BRow);
void     RecoveryRow    (int TRow,int BRow);
// работа со спецификацией
void    LoadSP        (String name,bool from_base);
void      LoadFromBase(String obd);
String    LoadXL        (String FileName);
String    LoadDBF        (String Filename);
void    CompareSP    (void);
void    BuildISPList(void);
int     GetIDRazd    (String rname);
String     GetNameRazd    (int id);
void     ShowSP        (void);
void     SPInit        (void);
void    ClearMass    (void);
void    SaveToSPRow    (void);
int        LoadComboData(int type);
bool    SaveToBase    (void);
void    GetXL    (void);
// сортировка
vector <SpRow*> *SortMass    (vector <SpRow*> *mass);
void            SortByObd    (vector <SpRow*> *mass);
int             increment    (long inc[],long size);
// распознание полных наименований
void             UniteRows             (vector <SpRow*> *mass);
bool             isGroupType         (vector <SpRow*>::iterator i);
bool            isNormalRow         (vector <SpRow*>::iterator i);
bool            isEmptyRow             (vector <SpRow*>::iterator i);
bool            isFullDataRow        (String name);
bool            itVowel             (String letter);
String             CollectGroupRows    (vector <SpRow*> *mass,vector <SpRow*>::iterator &i);
void             CollectСarriedRows    (vector <SpRow*> *mass,vector <SpRow*>::iterator &i,String &name,int &pp,double &kol,String &prim);
String             GetWordEnding        (String word);
// прочие функции
bool     RepeatOBD    (int ARow);
String     GetUUID     (void);
public:        // User declarations
Type OpenType;
    __fastcall TSPEditor(TComponent* Owner,cSQL *const db,const int &_LUser,int mode, String obd);
    __fastcall ~TSPEditor(void);
};
#endif
