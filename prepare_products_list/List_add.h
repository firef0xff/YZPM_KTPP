//---------------------------------------------------------------------------

#ifndef List_addH
#define List_addH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include "SQL.h"
//---------------------------------------------------------------------------
class TListAdd : public TForm
{
__published:    // IDE-managed Components
    TComboBox *Type;
    TBitBtn *OK;
    TBitBtn *Cancel;
    TGroupBox *GroupBox1;
    void __fastcall OKClick(TObject *Sender);
private:    // User declarations
    cSQL *DB;
    const int &LUser;
public:        // User declarations
    __fastcall TListAdd(TComponent *Owner,const int &_LUser, cSQL *db);
    __fastcall ~TListAdd(void);
};
#endif
