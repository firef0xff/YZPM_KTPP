//---------------------------------------------------------------------------

#ifndef komplectH
#define komplectH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class Tkomplekt : public TForm
{
__published:    // IDE-managed Components
    TGroupBox *GroupBox1;
    TBitBtn *BitBtn1;
    TBitBtn *BitBtn2;
    TCheckBox *materials;
    TCheckBox *litho;
    TCheckBox *forging;
    TCheckBox *cooperation;
    TCheckBox *shtamping;
private:    // User declarations
public:        // User declarations
    __fastcall Tkomplekt(TComponent* Owner);
};
#endif
