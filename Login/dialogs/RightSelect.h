//---------------------------------------------------------------------------

#ifndef RightSelectH
#define RightSelectH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>

#include "SQL.h"
#include <Buttons.hpp>

#ifndef nullptr
    #define nullptr 0
#endif
//---------------------------------------------------------------------------
class TfselRight : public TForm
{
__published:    // IDE-managed Components
    TComboBox *cbRight;
    TLabel *Label3;
    TBitBtn *BitBtn2;
    TBitBtn *BitBtn1;
private:    // User declarations
    cSQL *DB;
public:        // User declarations
    __fastcall TfselRight(TComponent* Owner,cSQL *db,String GroupID);
};

#endif
