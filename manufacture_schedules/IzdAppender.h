//---------------------------------------------------------------------------

#ifndef IzdAppenderH
#define IzdAppenderH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>

#include "SQL.h"
#include "Obd.h"
#include "def_types.h"
//---------------------------------------------------------------------------

class ZakazData : public TObject
{
public:
    __fastcall ZakazData(__uint64 zak_id_, String zakaz_):
    zak_id(zak_id_), zakaz(zakaz_)
    {}
    __fastcall ~ZakazData(){}
    __uint64 getZakID(void)
    {
        return zak_id;
    }
    String getZakaz(void)
    {
        return zakaz;
    }
private:
    __uint64 zak_id;
    String zakaz;
};

class PartData : public TObject
{
public:
    __fastcall PartData(__uint64 part_id_,  int part_no_):
                part_id(part_id_), part_no(part_no_)
    {}
    __fastcall ~PartData()
    {}
    __uint64 getPartID(void)
    {
        return part_id;
    }
    unsigned int getPartNo(void)
    {
        return part_no;
    }
private:
    __uint64 part_id;
    unsigned int part_no;
};

class TIzdAppenderWnd : public TForm
{
__published:    // IDE-managed Components
    TComboBox *ZakazList;
    TComboBox *PartList;
    TEdit *Izd;
    TLabel *Label1;
    TLabel *Label2;
    TLabel *Label3;
    TBitBtn *BitBtn2;
    TBitBtn *BitBtn1;
    TEdit *Kol;
    TLabel *Label4;
    void __fastcall ZakazListChange(TObject *Sender);
    void __fastcall BitBtn1Click(TObject *Sender);
private:    // User declarations
cSQL *DB;
const Obd &obd;
String zap_id;
public:        // User declarations
    __fastcall TIzdAppenderWnd(TComponent* Owner, cSQL *db, String zap_id_, const Obd &obd_);
};

#endif
