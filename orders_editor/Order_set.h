//---------------------------------------------------------------------------

#ifndef Order_setH
#define Order_setH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TZakaz_set : public TForm
{
__published:    // IDE-managed Components
    TLabeledEdit *Zakaz;
    TLabeledEdit *Description;
    TBitBtn *BitBtn2;
    TBitBtn *BitBtn1;
private:    // User declarations
public:        // User declarations
    __fastcall TZakaz_set(TComponent* Owner);
};
#endif
