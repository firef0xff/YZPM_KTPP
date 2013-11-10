//---------------------------------------------------------------------------

#ifndef NextStateSelectorH
#define NextStateSelectorH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>

#include "SQL.h"

#ifndef nullptr
    #define nullptr 0
#endif
class TNext_State_Selector : public TForm
{
__published:    // IDE-managed Components
    TComboBox *cbConditions;
    TComboBox *cbType;
    TBitBtn *BitBtn2;
    TBitBtn *BitBtn1;
    TLabel *Label3;
    TLabel *Label1;
    void __fastcall BitBtn1Click(TObject *Sender);
private:    // User declarations
    cSQL *DB;
    bool Edit;
public:        // User declarations
    __fastcall TNext_State_Selector(TComponent* Owner,cSQL *db,String param,bool edit=false);
    String Name;
    String type;
    int ID;
};

#endif
