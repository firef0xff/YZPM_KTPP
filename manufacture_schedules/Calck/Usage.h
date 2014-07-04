//---------------------------------------------------------------------------

#ifndef UsageH
#define UsageH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <ActnPopup.hpp>
#include <Menus.hpp>
#include <PlatformDefaultStyleActnCtrls.hpp>

#include "SQL.h"
#include "IconsData.h"
#include "string.h"
#include "def_types.h"

class ZakazData
{
public:
    ZakazData(__uint64 zakaz_id, const AnsiString &zakaz)
        :zakaz_id(zakaz_id),zakaz(zakaz)
    {
    }
    virtual ~ZakazData()
    {}

    const __uint64 zakaz_id;
    const AnsiString zakaz;
};
class PartData : public ZakazData
{
public:
    PartData(long zakaz_id, const AnsiString &zakaz, __uint64 part_id, __uint64 part_no)
        :ZakazData(zakaz_id, zakaz),part_id(part_id),part_no(part_no)
    {}
    ~PartData()
    {}
    const __uint64 part_no;
    const __uint64 part_id;
};
class IzdData : public ZakazData
{
public:
    IzdData(long zakaz_id, const AnsiString &zakaz, __uint64 det_id, __uint64 kol, const AnsiString &obd)
        :ZakazData(zakaz_id, zakaz),det_id(det_id),kol(kol),obd(obd)
    {}
    ~IzdData()
    {}
    const __uint64 det_id;
    const __uint64 kol;
    const AnsiString obd;
};
//---------------------------------------------------------------------------
class TResourceUsage : public TFrame
{
__published:	// IDE-managed Components
	TPageControl *PageControl1;
	TTabSheet *TabSheet1;
	TTabSheet *TabSheet2;
	TTreeView *ManufactureTree;
	TTreeView *DevelopTree;
	TPageControl *PageControl2;
	TTabSheet *TabSheet3;
	TPanel *Panel1;
	TPanel *Panel2;
	TSplitter *Splitter1;
	TSplitter *Splitter2;
	TLabel *Label1;
	TLabel *Label2;
	TStringGrid *zap_sg;
	TTabSheet *TabSheet4;
	TPanel *Panel3;
	TLabeledEdit *StartedParams;
	TPanel *Panel4;
	TLabeledEdit *NewParams;
	TCheckBox *Show_Closed;
	TPopupActionBar *PAB1;
	TMenuItem *N1;
	TMenuItem *N2;
	TMenuItem *N3;
	TPopupActionBar *PAB2;
	TMenuItem *MenuItem3;
	TPopupActionBar *PAB3;
	TMenuItem *MenuItem4;
	TMenuItem *MenuItem5;
	TPopupActionBar *PAB4;
	TMenuItem *MenuItem6;
	TMenuItem *MenuItem7;
	TStringGrid *plan_sg;
	TButton *FindStarted;
	TButton *FindNew;
    void __fastcall FindStartedClick(TObject *Sender);
    void __fastcall FindNewClick(TObject *Sender);
    void __fastcall TVDeletion(TObject *Sender, TTreeNode *Node);
private:	// User declarations
    const int &LUser;
	IconsData *IcoData;
    cSQL *DB;
public:		// User declarations
	__fastcall TResourceUsage(TComponent* Owner,TWinControl *_p, int &_LUser,cSQL *db,IconsData *_IcoData);
};
#endif
