//---------------------------------------------------------------------------

#ifndef manufactureH
#define manufactureH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <DockTabSet.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <Tabs.hpp>
#include <ActnPopup.hpp>
#include <Menus.hpp>
#include <PlatformDefaultStyleActnCtrls.hpp>

#include "SQL.h"
#include "IconsData.h"
#include <ImgList.hpp>
//---------------------------------------------------------------------------
#ifndef __int64
#define __int64 long long
#endif

class NodeData
{
    public:
    NodeData():locked(false){}
    virtual ~NodeData(){}

    bool Locked(void)
    {
        return locked;
    }
    void SetLock(bool r = true)
    {
        locked = r;
    }

    private:
        bool locked;
};

class ZakazNode : public NodeData
{
public:
    ZakazNode(unsigned __int64 zak_id_, unsigned __int64 zap_id_, String zakaz_):
    zak_id(zak_id_), zap_id(zap_id_), zakaz(zakaz_)
    {}
    ~ZakazNode(){}
    unsigned __int64 getZakID(void)
    {
        return zak_id;
    }
    unsigned __int64 getZapID(void)
    {
        return zap_id;
    }
    String getZakaz(void)
    {
        return zakaz;
    }
private:
    unsigned __int64 zak_id;
    unsigned __int64 zap_id;
    String zakaz;
};
class PartNode : public NodeData
{
public:
    PartNode(unsigned __int64 part_id_,  int part_no_):
    part_id(part_id_), part_no(part_no_)
    {}
    ~PartNode()
    {}
    unsigned __int64 getPartID(void)
    {
        return part_id;
    }
    unsigned int getPartNo(void)
    {
        return part_no;
    }
private:
    unsigned __int64 part_id;
    unsigned int part_no;
};

class IzdNode : public NodeData
{
public:
    IzdNode(String name_, String obd_, unsigned __int64 det_id_, double kol_used_, unsigned int sp_id_, String sp_name_):
    name(name_),obd(obd_),det_id(det_id_),kol_used(kol_used_), sp_id(sp_id_), sp_name(sp_name_)
    {}
    ~IzdNode()
    {}
    unsigned __int64 getDetID(void)
    {
        return det_id;
    }
    String getDetObd(void)
    {
        return obd;
    }
    String getDetName(void)
    {
        return name;
    }
    unsigned int getSpRazd(void)
    {
        return sp_id;
    }
    virtual bool IsUsed(void)
    {
        return true;
    }
    double getCount(void)
    {
        return kol_used;
    }
protected:
    String name;
    String sp_name;
    unsigned int sp_id;
    unsigned __int64 det_id;
    String obd;
    double kol_used;
};

class IzdPartNode : public IzdNode
{
public:
    IzdPartNode(String name_, String obd_, unsigned __int64 det_id_, double kol_used_,
        unsigned __int64 det_idp_ ,unsigned __int64 inst_idc_,unsigned __int64 inst_idp_,double kol_sp_, unsigned int sp_id_, String sp_name_, bool used_):
    IzdNode(name_, obd_, det_id_, kol_used_, sp_id_, sp_name_), det_idp(det_idp_), kol_sp(kol_sp_), used(used_),inst_idc(inst_idc_),inst_idp(inst_idp_)
    {}
    ~IzdPartNode()
    {}
    bool IsUsed(void)
    {
        return used;
    }
    unsigned __int64 getDetIDp(void)
    {
        return det_idp;
    }
    unsigned __int64 getInstIDc(void)
    {
        return inst_idc;
    }
    unsigned __int64 getInstIDp(void)
    {
        return inst_idp;
    }
    void Update (cSQL *DB)
    {
        TADOQuery *rez = DB->SendSQL("select `using` from manufacture.det_tree where inst_idc = '"+String(inst_idc)+"'");
        if (rez)
        {
            used = int(rez->FieldByName("using")->Value);
            delete rez;
        }
    }
private:
    unsigned __int64 det_idp;
    unsigned __int64 inst_idc;
    unsigned __int64 inst_idp;
    double kol_sp;
    bool used;
};

class TManufactureControl : public TFrame
{
__published:    // IDE-managed Components
    TPanel *Bottom_pannel;
    TPanel *Top_pannel;
    TPanel *Find_pannel;
    TSpeedButton *Find;
    TSpeedButton *Obozn_cl;
    TSpeedButton *Zakaz_cl;
    TSpeedButton *Zap_cl;
    TLabeledEdit *Obozn;
    TLabeledEdit *Zakaz;
    TLabeledEdit *Zap_name;
    TPanel *zap_list_hd;
    TPanel *zakaz_list_hd;
    TStringGrid *zapSG;
    TPanel *contain_list_hd;
    TTreeView *contentTV;
    TTreeView *zakTV;
    TSplitter *Splitter1;
    TPageControl *Content_detail;
    TTabSheet *StandartParts;
    TTabSheet *Materials;
    TStringGrid *stSG;
    TStringGrid *matSG;
    TPopupActionBar *PAB1;
    TMenuItem *N1;
    TMenuItem *N2;
    TMenuItem *N3;
    TPopupActionBar *PAB3;
    TMenuItem *MenuItem4;
    TMenuItem *MenuItem5;
    TMenuItem *N4;
    TMenuItem *N5;
    TPopupActionBar *PAB2;
    TMenuItem *MenuItem1;
    TMenuItem *MenuItem2;
    TMenuItem *MenuItem3;
    TMenuItem *MenuItem7;
    TMenuItem *MenuItem8;
    TMenuItem *N7;
    TPopupActionBar *PAB3_1;
    TMenuItem *MenuItem11;
    TMenuItem *MenuItem12;
    TMenuItem *MenuItem13;
    TImageList *States;
    TTabSheet *Parts;
    TSplitter *Splitter2;
    TPanel *Panel1;
    TStringGrid *detSG;
	TPageControl *DetDetailControl;
	TTabSheet *OperationsSheet;
    TRadioGroup *RadioGroup1;
    TTabSheet *TabSheet2;
    TStringGrid *operSG;
    TStringGrid *det_matSG;
    TTabSheet *TabSheet3;
    TStringGrid *makeSG;
	TTabSheet *ObourSheet;
    TStringGrid *det_oborudSG;
    TTabSheet *Oborud;
    TTabSheet *TabSheet6;
	TLabeledEdit *leZak;
	TLabeledEdit *lePart;
	TLabeledEdit *leIzd;
	TLabeledEdit *leDet;
	TBitBtn *btSearch;
	TStringGrid *OborudSG;
	TImageList *marks;
	TStringGrid *detDetails;
	TSplitter *Splitter3;
	TLabeledEdit *leNar;
	TStringGrid *SGNarList;
	TRadioGroup *RG2;
	TBitBtn *btSave;
	TSpeedButton *prev;
	TLabeledEdit *E2;
	TSpeedButton *next;
	TLabeledEdit *E3;
	TTabSheet *Surcharge;
	TStringGrid *surch_sg;
	TPopupActionBar *PAB4;
	TMenuItem *N6;
	TMenuItem *N8;
	TMenuItem *N9;
	TPanel *Panel2;
	TSplitter *Splitter4;
	TMemo *surch_descr;
	TEdit *surch_reason;
	TCheckBox *Show_Closed;
	TMenuItem *N10;
    void __fastcall CreateZapusk(TObject *Sender);
    void __fastcall RemoveZapusk(TObject *Sender);
    void __fastcall InWorkZapusk(TObject *Sender);
    void __fastcall ToEditZapusk(TObject *Sender);
    void __fastcall AddZakaz(TObject *Sender);
    void __fastcall RemoveZakaz(TObject *Sender);
    void __fastcall InWorkZakaz(TObject *Sender);
    void __fastcall ToEditZakaz(TObject *Sender);
    void __fastcall AddIzdelie(TObject *Sender);
    void __fastcall RemoveIzdelie(TObject *Sender);
    void __fastcall IncludePath(TObject *Sender);
    void __fastcall UnIncludePath(TObject *Sender);
    void __fastcall ClearZpusk(TObject *Sender);
    void __fastcall ClearZakaz(TObject *Sender);
    void __fastcall ClearIzdelie(TObject *Sender);
    void __fastcall FindClick(TObject *Sender);
    void __fastcall zakTVDeletion(TObject *Sender, TTreeNode *Node);
    void __fastcall zapSGSelectCell(TObject *Sender, int ACol, int ARow, bool &CanSelect);
    void __fastcall contentTVDeletion(TObject *Sender, TTreeNode *Node);
    void __fastcall contentTVExpanding(TObject *Sender, TTreeNode *Node, bool &AllowExpansion);
    void __fastcall contentTVMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
    void __fastcall detSGSelectCell(TObject *Sender, int ACol, int ARow, bool &CanSelect);
	void __fastcall DetDetailControlChange(TObject *Sender);
	void __fastcall zakTVMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall zapSGDrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect,
          TGridDrawState State);
	void __fastcall N5Click(TObject *Sender);
	void __fastcall MenuItem8Click(TObject *Sender);
	void __fastcall N7Click(TObject *Sender);
	void __fastcall detDetailsSelectCell(TObject *Sender, int ACol, int ARow, bool &CanSelect);
	void __fastcall btSearchClick(TObject *Sender);
	void __fastcall SGNarListMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall SGNarListSelectCell(TObject *Sender, int ACol, int ARow, bool &CanSelect);
	void __fastcall btSaveClick(TObject *Sender);
	void __fastcall SGNarListDrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect,
          TGridDrawState State);
	void __fastcall pagerClick(TObject *Sender);
	void __fastcall E2Change(TObject *Sender);
	void __fastcall E3Change(TObject *Sender);
	void __fastcall RG2Click(TObject *Sender);
    void __fastcall SGNarListSetEditText(TObject *Sender, int ACol, int ARow, const UnicodeString Value);
	void __fastcall surch_sgSelectCell(TObject *Sender, int ACol, int ARow, bool &CanSelect);
	void __fastcall N6Click(TObject *Sender);
	void __fastcall N9Click(TObject *Sender);
	void __fastcall N8Click(TObject *Sender);
	void __fastcall N10Click(TObject *Sender);






private:    // User declarations

    void StartOrder(const std::vector<unsigned __int64> &parts);
    void StopOrder(const std::vector<unsigned __int64> &parts);
    void CloseOrder(const std::vector<unsigned __int64> &parts);


    void LoadZapusk(String zapusk, String zakaz, String det);
    void LoadZakaz (String zap_id, String zakaz, String det);
    void LoadIzd   (String zap_id, unsigned __int64 zak_id, unsigned __int64 part_id, String det);

    void LoadDetailData         (String zap_id, unsigned __int64 zak_id, unsigned __int64 part_id, unsigned __int64 det_id, unsigned __int64 inst_id);
    void LoadDetailParts        (String zap_id, unsigned __int64 zak_id, unsigned __int64 part_id, unsigned __int64 det_id, unsigned __int64 inst_id);
    void LoadPartDetails        (String id, String zap_id, String zak_id, String part_id, String det_id, String inst_id);
    void LoadTechDetails        (String det_id);
    void LoadOborudDetails      (String det_id);

    void LoadDetailStandartParts(String zap_id, unsigned __int64 zak_id, unsigned __int64 part_id, unsigned __int64 det_id, unsigned __int64 inst_id);
    void LoadDetailMaterials    (String zap_id, unsigned __int64 zak_id, unsigned __int64 part_id, unsigned __int64 det_id, unsigned __int64 inst_id);
    void LoadDetailOborud       (String zap_id, unsigned __int64 zak_id, unsigned __int64 part_id, unsigned __int64 det_id, unsigned __int64 inst_id);
    void LoadDetailSurCharge    (String zap_id, unsigned __int64 zak_id, unsigned __int64 part_id, unsigned __int64 det_id, unsigned __int64 inst_id);

    void Set_img   (TTreeNode *node);
    void Update    (TTreeNode *node);
    void UpdateOrderStatus (void);
    void UpdatePartsStatus (void);

    void NarUpdate (int Row);

    int **selected;

    const int &LUser;
    static IconsData *IcoData;
    static int count;
    static cSQL *DB;

public:        // User declarations
    __fastcall TManufactureControl(TComponent* Owner,TWinControl *_p, int &_LUser,cSQL *db,IconsData *_IcoData,int **_selected);
    __fastcall ~TManufactureControl(void);
};
int TManufactureControl::count=0;
IconsData *TManufactureControl::IcoData=0;
cSQL *TManufactureControl::DB=0;
#endif

