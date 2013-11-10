//---------------------------------------------------------------------------

#ifndef Isp_editorH
#define Isp_editorH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ActnPopup.hpp>
#include <ImgList.hpp>
#include <Menus.hpp>
#include <PlatformDefaultStyleActnCtrls.hpp>

#include "IspData.h"
#include "SQL.h"
#include <Vector.h>
#include "Obd_edt.h"
#include <Buttons.hpp>
#include <ExtCtrls.hpp>

class Less
{
public:
inline bool operator()(IspData a1, IspData a2)
    {
    return a1.Get_Obd(false)<a2.Get_Obd(false);
    }
};
class TIspList : public TForm
{
__published:    // IDE-managed Components
    TTreeView *TV;
    TPopupActionBar *PAB;
    TMenuItem *N1;
    TMenuItem *N2;
    TMenuItem *N3;
    TImageList *ImageList1;
    TBitBtn *BitBtn1;
    TPanel *Panel1;
    TBitBtn *BitBtn2;
    void __fastcall N1Click(TObject *Sender);
    void __fastcall N2Click(TObject *Sender);
    void __fastcall N3Click(TObject *Sender);
    void __fastcall TVDblClick(TObject *Sender);
private:    // User declarations
vector <IspData> &list;
cSQL *const DB;
bool edit;
void     Show(void);
public:        // User declarations
    __fastcall TIspList(TComponent* Owner, cSQL *const db,vector <IspData> &_list,bool _edit=true);
};
#endif
