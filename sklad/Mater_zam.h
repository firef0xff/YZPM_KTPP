//---------------------------------------------------------------------------

#ifndef Mater_zamH
#define Mater_zamH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include "SQL.h"
//---------------------------------------------------------------------------
class TMat_zam : public TForm
{
__published:    // IDE-managed Components
    TLabeledEdit *old_mat;
    TLabeledEdit *new_mat;
    TLabel *Label1;
    TBitBtn *BitBtn1;
    TBitBtn *BitBtn2;
    TCheckBox *CB1;
    void __fastcall BitBtn2Click(TObject *Sender);
private:    // User declarations
cSQL *Db;
public:        // User declarations
    __fastcall TMat_zam(TComponent* Owner);
};
#endif
