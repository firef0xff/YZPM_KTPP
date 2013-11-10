//---------------------------------------------------------------------------

#ifndef loginwinH
#define loginwinH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <Mask.hpp>
#include "SQL.h"


//---------------------------------------------------------------------------
class TLogIn : public TForm
{
__published:    // IDE-managed Components
    TLabel *Label1;
    TLabel *Label2;
    TBitBtn *BitBtn1;
    TBitBtn *BitBtn2;
    TMaskEdit *pas;
    TComboBox *log;
    void __fastcall BitBtn1Click(TObject *Sender);
private:    // User declarations
cSQL *const DB;
int logcount;
int UserID;
public:        // User declarations
int    Get_UserID(void)const{return UserID;}
    __fastcall TLogIn(TComponent* Owner,cSQL *db);
};
#endif
