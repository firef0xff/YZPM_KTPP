//---------------------------------------------------------------------------

#ifndef materialH
#define materialH
//---------------------------------------------------------------------------
#include "Add_mat.h"
#include "Mater_zam.h"

#include <ActnPopup.hpp>
#include <ADODB.hpp>
#include <Buttons.hpp>
#include <Classes.hpp>
#include <ComCtrls.hpp>
#include <Controls.hpp>
#include <DB.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <Menus.hpp>
#include <PlatformDefaultStyleActnCtrls.hpp>
#include <StdCtrls.hpp>
//---------------------------------------------------------------------------
class Tmaterials : public TForm
{
__published:    // IDE-managed Components
    TPanel *Panel1;
    TStringGrid *SG;
    TTreeView *TV;
    TSplitter *Splitter1;
    TPopupActionBar *PAB;
    TMenuItem *N1;
    TMenuItem *N2;
    TRadioGroup *RG;
    TLabeledEdit *LE1;
    TLabeledEdit *LE2;
    TLabeledEdit *LE3;
    TButton *Button1;
    TSpeedButton *next;
    TEdit *E2;
    TSpeedButton *prev;
    TLabeledEdit *E3;
    TBitBtn *BB1;
    TButton *Add;
    TButton *Del;
    TButton *Button2;
    void __fastcall TVExpanding(TObject *Sender, TTreeNode *Node, bool &AllowExpansion);
    void __fastcall N1Click(TObject *Sender);
    void __fastcall N2Click(TObject *Sender);
    void __fastcall TVClick(TObject *Sender);
    void __fastcall Find(void);
    void __fastcall RGClick(TObject *Sender);
    void __fastcall Button1Click(TObject *Sender);
    void __fastcall nextClick(TObject *Sender);
    void __fastcall prevClick(TObject *Sender);
    void __fastcall E2Change(TObject *Sender);
    void __fastcall E3Change(TObject *Sender);
    void __fastcall BB1Click(TObject *Sender);
    void __fastcall AddClick(TObject *Sender);
    void __fastcall DelClick(TObject *Sender);
    void __fastcall Button2Click(TObject *Sender);

private:    // User declarations
cSQL *const DB;
String obm;
String SQL;
const int &LUser;
static String rowcount;
static String list;
static String _obm;
static String _name;
static String _prof;
public:        // User declarations
    __fastcall Tmaterials(TComponent* Owner,cSQL *db,bool ReadOnly,const int &_LUser);
String Get_obm(void)const {return obm;}
};
String Tmaterials::rowcount="20";
String Tmaterials::list="1";
String Tmaterials::_obm="";
String Tmaterials::_name="";
String Tmaterials::_prof="";
#endif
