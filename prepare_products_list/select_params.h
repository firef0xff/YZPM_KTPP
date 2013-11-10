//---------------------------------------------------------------------------

#ifndef select_paramsH
#define select_paramsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include "SQL.h"
//---------------------------------------------------------------------------
class TList_sel_params : public TForm
{
__published:    // IDE-managed Components
    TGroupBox *GroupBox1;
    TLabel *Label9;
    TLabel *Label5;
    TDateTimePicker *cd_max;
    TDateTimePicker *cd_min;
    TCheckBox *b_cd;
    TGroupBox *GroupBox2;
    TLabel *Label1;
    TLabel *Label2;
    TDateTimePicker *ud_max;
    TDateTimePicker *ud_min;
    TCheckBox *b_ud;
    TCheckBox *b_type;
    TComboBox *Type;
    TBitBtn *OK;
    TBitBtn *Cancel;
    TComboBox *State;
    TCheckBox *b_State;
    void __fastcall OKClick(TObject *Sender);
private:    // User declarations
    String sortparams;
    cSQL *DB;
    const int &LUser;
public:        // User declarations
String Get_Where(void)const{return sortparams;}
    __fastcall TList_sel_params(TComponent *Owner,const int &_LUser, cSQL *db);
    __fastcall ~TList_sel_params(void);
};
#endif
