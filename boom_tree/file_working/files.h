

#ifndef filesH
#define filesH


#include "FRowData.h"

#include <ActnPopup.hpp>
#include <Classes.hpp>
#include <ComCtrls.hpp>
#include <Controls.hpp>
#include <Dialogs.hpp>
#include <Grids.hpp>
#include <ImgList.hpp>
#include <Menus.hpp>
#include <PlatformDefaultStyleActnCtrls.hpp>
#include <StdCtrls.hpp>
#include <ToolWin.hpp>


class TFileDisigner : public TForm
{
__published:    
    TStringGrid *SG;
    TComboBox *CB;
    TOpenDialog *OD;
    TEdit *ED;
    TToolBar *ToolBar1;
    TToolButton *open;
    TToolButton *clear;
    TToolButton *save;
    TImageList *ImageList1;
    TToolButton *ClearAll;
    TPopupActionBar *PAB;
    TMenuItem *N1;
    TMenuItem *N2;
    TMenuItem *N3;
    TMenuItem *N4;
    TSaveDialog *SD;
	TMenuItem *N5;
	TToolButton *ViewDoc;
    void __fastcall ClearAllClick(TObject *Sender);
    void __fastcall OpenClick(TObject *Sender);
    void __fastcall SGDrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect, TGridDrawState State);
    void __fastcall SaveClick(TObject *Sender);
    void __fastcall SGFixedCellClick(TObject *Sender, int ACol, int ARow);
    void __fastcall SGDblClick(TObject *Sender);
    void __fastcall CBExit(TObject *Sender);
    void __fastcall CBChange(TObject *Sender);
    void __fastcall EDExit(TObject *Sender);
    void __fastcall EDKeyPress(TObject *Sender, wchar_t &Key);
    void __fastcall ClearClick(TObject *Sender);
    void __fastcall SGKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall N5Click(TObject *Sender);


private:    
vector <FRowData> grid;
cSQL  *const     DB;
const int    &LUser;
const char type;

bool FileAsc;
bool ObdAsc;
bool InBaseAsc;
bool ActionAsc;
String base;

bool    ChangeFiles(void);
bool    CheckData(FRowData *row);
void    ClearData(void);
void     ShowData (void);
void    SetNewObd(int ACol,int ARow);
void    SetNewAction(int ACol,int ARow);
void    FillCombo(int pos);
void    UpdRow(int ARow);

void     LoadFiles(const Obd *const det,bool MassAction);
void    SaveToBase(void);
void    SaveToPc(void);
void    Delete(void);
void    OpenFiles(void);

void    SortByObd(bool asc);
void    SortByFile(bool asc);
void    SortByInBase(bool asc);
void    SortByAction(bool asc);
int     increment(long inc[], long size);


public:        
    __fastcall TFileDisigner(TComponent* Owner,cSQL *const _DB,const int &_LUser,const Obd *const det,bool MassAction,const char &_type);
    __fastcall ~TFileDisigner(void);
};
//---------------------------------------------------------------------------
#endif
