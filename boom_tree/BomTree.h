
#ifndef BomTreeH
#define BomTreeH

#include <ActnPopup.hpp>
#include <Buttons.hpp>
#include <Classes.hpp>
#include <ComCtrls.hpp>
#include <Controls.hpp>
#include <ExtCtrls.hpp>
#include <ImgList.hpp>
#include <Menus.hpp>
#include <PlatformDefaultStyleActnCtrls.hpp>
#include <StdCtrls.hpp>

#include "DetSelector.h"
#include "Conditions.h"
#include "files.h"
#include "SPEdit.h"
typedef void (*Tech)(Obd *Det);
class TSpTree : public TFrame,public ClassConnector
{
__published:    
    TPanel *Panel3;
    TTreeView *Tree;
    TPopupActionBar *PAB;
    TMenuItem *N17;
    TMenuItem *N31;
    TMenuItem *N20;
    TMenuItem *N21;
    TMenuItem *N22;
    TMenuItem *N40;
    TMenuItem *N41;
    TMenuItem *N42;
    TMenuItem *N26;
    TMenuItem *N14;
    TMenuItem *N23;
    TMenuItem *N1;
    TMenuItem *N3;
    TMenuItem *N4;
    TMenuItem *N5;
    TMenuItem *N6;
    TMenuItem *N7;
    TMenuItem *N8;
    TMenuItem *N9;
    TMenuItem *N10;
    TMenuItem *N11;
    TMenuItem *N12;
    TMenuItem *N13;
    TMenuItem *N15;
    TMenuItem *N16;
    TMenuItem *N18;
    TMenuItem *N19;
    TMenuItem *N24;
    TMenuItem *N25;
    TImageList *ImageList1;
    TMenuItem *N2;
    TMenuItem *N27;
    TMenuItem *N28;
    TMenuItem *N29;
    void __fastcall TreeExpanding(TObject *Sender, TTreeNode *Node, bool &AllowExpansion);
    void __fastcall TreeMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
    
    void __fastcall N14Click(TObject *Sender);
    void __fastcall N21Click(TObject *Sender);
    void __fastcall N22Click(TObject *Sender);
    void __fastcall N23Click(TObject *Sender);
    
    void __fastcall SpMaster(TObject *Sender);
    void __fastcall SpDel(TObject *Sender);
    
    void __fastcall N4Click(TObject *Sender);
    void __fastcall N5Click(TObject *Sender);
    void __fastcall N11Click(TObject *Sender);
    
    void __fastcall TechAction(TObject *Sender);
    void __fastcall TechDel(TObject *Sender);
    void __fastcall N41Click(TObject *Sender);
    
    void __fastcall N26Click(TObject *Sender);
    
    void __fastcall N10Click(TObject *Sender);
    void __fastcall N9Click(TObject *Sender);
    
    void __fastcall TreeAdvancedCustomDrawItem(TCustomTreeView *Sender, TTreeNode *Node,
          TCustomDrawState State, TCustomDrawStage Stage, bool &PaintImages,
          bool &DefaultDraw);
    void __fastcall TreeClick(TObject *Sender);
private:    
    void  Init        (void);
    
       void  TreeClear(void);
    void  BranchClear(TTreeNode *Node);
    void  Selection(TTreeView *TView,TShiftState Shift,int X, int Y);
    
    void  Load (const Obd *const det){LoadTree(det->Get_ID());};
    void  Load_sel(Obd *det){Selector->LoadDet(det);};
    void  LoadTree (int _id);
    void  LoadTree (TTreeNode *Node);
    void  LoadBranch(TTreeNode *Node);
    void  LoadFiles(TTreeNode *Node);
       void  UpdateBranch(TTreeNode *Node,bool force);
       
    void  GetInfo(TTreeNode *Node);
       void  UpdateInfo(TTreeNode *Node);

    void  Block(String &ids);
    void  UnBlock(String &ids);

    Tech AddTexTab;
    Tech AddTexViewTab;
    Tech LoadTexToCurrTab;
    Tech LoadexViewToCurrTab;
    
    bool  MassAction;
    TMemo *memo;
    TObdSelector *Selector;
    const int &LUser;
    
    static IconsData *IcoData;
    static int count;

    static cSQL *DB;
    int ** selected;
public:        
    __fastcall TSpTree(TComponent* Owner,TWinControl *_p,cSQL *db,const int &_LUser,TMemo *m,IconsData *_IcoData,int **_selected,void* _AddTexTab,
    void* _LoadTexToCurrTab,void* _AddTexViewTab,void* _LoadexViewToCurrTab);
    __fastcall TSpTree::~TSpTree(void);
    void LoadDet (Obd *det){Selector->LoadDet(det);};
};

int TSpTree::count=0;
IconsData *TSpTree::IcoData=0;

cSQL *TSpTree::DB=0;
#endif
