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

class ZakazData
{
public:
    ZakazData(long zakaz_id, const std::string &zakaz)
        :zakaz_id(zakaz_id),zakaz(zakaz)
    {
    }
    virtual ~ZakazData()
    {}

    const long zakaz_id;
    const std::string zakaz;
};
class PartData : public ZakazData
{
public:
    PartData(long zakaz_id, const std::string &zakaz, long part_id, long part_no)
        :ZakazData(zakaz_id, zakaz),part_id(part_id),part_no(part_no)
    {}
    ~PartData()
    {}
    const long part_no;
    const long part_id;
};
class IzdData : public ZakazData
{
public:
    IzdData(long zakaz_id, const std::string &zakaz, long det_id, long kol, const std::string &obd)
        :ZakazData(zakaz_id, zakaz),det_id(det_id),kol(kol),obd(obd)
    {}
    ~IzdData()
    {}
    const long det_id;
    const long kol;
    const std::string obd;
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
private:	// User declarations
    const int &LUser;
	IconsData *IcoData;
    cSQL *DB;
public:		// User declarations
	__fastcall TResourceUsage(TComponent* Owner,TWinControl *_p, int &_LUser,cSQL *db,IconsData *_IcoData);
};
#endif
