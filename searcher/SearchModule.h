

#ifndef SearchModuleH
#define SearchModuleH

#include "Obd.h"
#include "IconsData.h"

#include <Buttons.hpp>
#include <Classes.hpp>
#include <ComCtrls.hpp>
#include <Controls.hpp>
#include <ExtCtrls.hpp>
#include <StdCtrls.hpp>
#include <ActnPopup.hpp>
#include <Menus.hpp>
#include <PlatformDefaultStyleActnCtrls.hpp>
#include <ImgList.hpp>

typedef void (*Tech)(Obd *Det);
class TSearch : public TFrame
{
__published:	
	TPanel *Panel1;
	TTreeView *SupportTree;
	TTreeView *MainTree;
	TSplitter *Splitter1;
	TGroupBox *RazdParams;
	TCheckBox *products;
	TCheckBox *assemblies;
	TCheckBox *details;
	TCheckBox *stdelements;
	TPanel *Panel2;
	TPanel *Panel3;
	TLabel *Label1;
	TLabel *Label2;
	TRadioGroup *SearchParams;
	TPanel *Panel4;
	TLabel *Label3;
	TEdit *E1;
	TRadioGroup *RG2;
	TMemo *M2;
	TButton *AddCond;
	TButton *StartSearch;
	TLabeledEdit *E3;
	TSpeedButton *next;
	TSpeedButton *prev;
	TCheckBox *CB3;
	TCheckBox *CB1;
	TGroupBox *GroupBox1;
	TLabeledEdit *E2;
	TGroupBox *GroupBox2;
	TPanel *Panel6;
	TPanel *Panel7;
	TGroupBox *GroupBox3;
	TSpeedButton *Snext;
	TSpeedButton *Sprev;
	TLabeledEdit *SE2;
	TLabeledEdit *SE3;
	TPanel *Panel5;
	TPanel *Panel8;
	TComboBox *Combo;
	TImage *IMG;
	TButton *HideBtn;
	TLabel *Label4;
	TPopupActionBar *PAB;
	TMenuItem *N17;
	TMenuItem *N31;
	TMenuItem *N24;
	TMenuItem *N25;
	TMenuItem *N1;
	TMenuItem *N2;
	TImageList *ImageList1;
	
	void __fastcall RepaintPannels(TObject *Sender);
	
	void __fastcall ChgListClick(TObject *Sender);
	void __fastcall ChgSListClick(TObject *Sender);
	void __fastcall E3Change(TObject *Sender);
	void __fastcall E2Change(TObject *Sender);
	void __fastcall SE3Change(TObject *Sender);
	void __fastcall SE2Change(TObject *Sender);
	
	void __fastcall AddCondClick(TObject *Sender);
	void __fastcall E1KeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall StartSearchClick(TObject *Sender);
	void __fastcall refindClick(TObject *Sender);
	
	void __fastcall MainTreeClick(TObject *Sender);
	void __fastcall MainTreeDblClick(TObject *Sender);
	void __fastcall SupportTreeExpanding(TObject *Sender, TTreeNode *Node, bool &AllowExpansion);
	void __fastcall HideBtnClick(TObject *Sender);
	void __fastcall N2Click(TObject *Sender);
	void __fastcall TechAction(TObject *Sender);
	void __fastcall TreeClick(TObject *Sender);
private:
	String conditions;
	Obd *LastChild;
    bool SpView,TehRead,TehEdit,NormEdit;

	void  			TreeClear(TTreeView *tv);
	void  			BranchClear(TTreeNode *Node);
	String  		GetConditions(int User_ID);
	void 			Find(void);
	void 			FillTV(TTreeView *tv,TTreeNode *StartNode,String sql,bool AsChild=false,bool CanChild=false);
	void 			GetParents(Obd *data,TTreeNode *Node,bool AsChild=false);

	const int &LUser;
	static IconsData *IcoData;
	static int count;
	static cSQL *DB;

	int **selected;

	Tech AddTexTab;
	Tech AddTexViewTab;
	Tech LoadTexToCurrTab;
	Tech LoadexViewToCurrTab;
	void (*OpenTree)(Obd *det);

public:
	__fastcall TSearch(TComponent* Owner,TWinControl *_p, int &_LUser,cSQL *db,IconsData *_IcoData,int **_selected,void *_OpenTree,void* _AddTexTab,
	void* _LoadTexToCurrTab,void* _AddTexViewTab,void* _LoadexViewToCurrTab);
	__fastcall ~TSearch(void);
};
int TSearch::count=0;
IconsData *TSearch::IcoData=0;
cSQL *TSearch::DB=0;
#endif
