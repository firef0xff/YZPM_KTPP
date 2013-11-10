//---------------------------------------------------------------------------

#ifndef OrderContent_setH
#define OrderContent_setH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TZakazContent_set : public TForm
{
__published:    // IDE-managed Components
    TLabeledEdit *Kol;
    TLabeledEdit *Obd;
    TBitBtn *BitBtn1;
    TBitBtn *BitBtn2;
private:    // User declarations
public:        // User declarations
    __fastcall TZakazContent_set(TComponent* Owner);
};
#endif
