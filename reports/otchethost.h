//---------------------------------------------------------------------------

#ifndef otchethostH
#define otchethostH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <OleServer.hpp>
class TOtchet : public TForm
{
__published:    // IDE-managed Components
    TLabeledEdit *LE1;
    TBitBtn *BitBtn1;
    TBitBtn *BitBtn2;
    void __fastcall BitBtn1Click(TObject *Sender);
private:    // User declarations
public:        // User declarations
    __fastcall TOtchet(TComponent* Owner,String obd);
};
#endif
