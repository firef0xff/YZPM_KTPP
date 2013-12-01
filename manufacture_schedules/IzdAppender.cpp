//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "IzdAppender.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"


__fastcall TIzdAppenderWnd::TIzdAppenderWnd(TComponent* Owner, cSQL *db, String zap_id_, const Obd &obd_)
    : TForm(Owner),DB(db),zap_id(zap_id_),obd(obd_)
{
    String sql = " select a.zakaz, a.zak_id from manufacture.zakaz_list a "
                 " join manufacture.parts b on b.zak_id = a.zak_id "
                 " where b.zap_id = '"+zap_id+"' and b.in_work is null group by a.zak_id ";
    TADOQuery *rez = DB->SendSQL(sql);
    if (rez)
    {
        for (rez->First(); !rez->Eof; rez->Next())
        {
            String zakaz = rez->FieldByName("zakaz")->Value;
            unsigned __int64 zak_id = (unsigned __int64)__int64(rez->FieldByName("zak_id")->Value);
            ZakazData *ptr = new ZakazData(zak_id, zakaz);
            ZakazList->Items->AddObject(ptr->getZakaz(), (TObject *)ptr);
        }
        delete rez;
    }
    Izd->Text = obd.Get_Obd(true);
}
void __fastcall TIzdAppenderWnd::ZakazListChange(TObject *Sender)
{
    if (ZakazList->ItemIndex < 0 )
    {
        return;
    }
    ZakazData *ptr = (ZakazData *)ZakazList->Items->Objects[ZakazList->ItemIndex];
    String sql = " select a.part_no, a.part_id from manufacture.parts a "
                 " where a.in_work is null and a.zap_id = '"+zap_id+"' and a.zak_id = '"+String(ptr->getZakID())+"'";
    TADOQuery *rez = DB->SendSQL(sql);
    if (rez)
    {
        PartList->Items->Clear();
        for (rez->First(); !rez->Eof; rez->Next())
        {
            unsigned int part_no = rez->FieldByName("part_no")->Value;
            unsigned __int64 part_id = (unsigned __int64) __int64(rez->FieldByName("part_id")->Value);
            PartData *ptr = new PartData(part_id, part_no);
            PartList->Items->AddObject(ptr->getPartNo(), (TObject *)ptr);
        }
        delete rez;
    }
}
void __fastcall TIzdAppenderWnd::BitBtn1Click(TObject *Sender)
{
    if (PartList->ItemIndex < 0 )
    {
        return;
    }
    PartData *ptr = (PartData *)PartList->Items->Objects[PartList->ItemIndex];
    DB->SendCommand("call manufacture.AddIzd('"+String(obd.Get_ID())+"','"+Kol->Text+"','"+String(ptr->getPartID())+"')");

    ModalResult = mrOk;

    CloseModal();
}
