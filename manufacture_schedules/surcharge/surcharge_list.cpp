//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "surcharge_list.h"
#include "functions.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

//---------------------------------------------------------------------------
__fastcall TSurchargeList::TSurchargeList(TComponent* Owner, cSQL *db)
	: TForm(Owner),DB(db)
{
// load
    reason->Items->Clear();

    TADOQuery *rez = DB->SendSQL("select reason from manufacture.surcharge_reasons order by reason");
    if (rez)
    {
        for (rez->First(); !rez->Eof; rez->Next())
        {
            reason->Items->Add(rez->FieldByName("reason")->Value);
        }
        delete rez;
    }
}
void __fastcall TSurchargeList::saveClick(TObject *Sender)
{
// save
    if (!zak_id.ToIntDef(0) || !part_id.ToIntDef(0))
    {
        ShowMessage("Укажите заказ и номер партии");
        return;
    }

    Transaction tr(DB);
    if (surcharge_id != "")
    {
        //update
        DB->SendCommand("update `manufacture`.`orders` "
                        "set kol_request = '"+kol->Text+"', kol_maked = '"+kol->Text+"' "
                        "where surcharge_id = '"+surcharge_id+"'");


        DB->SendCommand("update `manufacture`.`surcharge` set "
                        "`zak_id`   ='"+zak_id+"', "
                        "`part_id`  ='"+part_id+"', "
                        "`opr_id`   ='"+opr_kod->Text+"', "
                        "`cex`      ='"+cex->Text+"', "
                        "`utch`     ='"+utch->Text+"', "
                        "`tab_no`   ='"+tab_no->Text+"', "
                        "`obd`      ='"+obd->Text+"', "
                        "`kts`      ='"+kts->Text+"', "
                        "`rr`       ='"+rr->Text+"', "
                        "`tpz`      ='"+tpz->Text+"', "
                        "`tsht`     ='"+tsht->Text+"', "
                        "`kvn`      ='"+vn->Text+"', "
                        "`reason`   ='"+reason->Text+"', "
                        "`tfact`    ='"+tfact->Text+"', "
                        "`descr`    ='"+ekran(descr->Text)+"' "
                        "where record_id = '"+surcharge_id+"'"
                        );
    }
    else
    {
        //insert
        DB->SendCommand("insert into `manufacture`.`surcharge` set "
                        "`zak_id`   ='"+zak_id+"', "
                        "`part_id`  ='"+part_id+"', "
                        "`opr_id`   ='"+opr_kod->Text+"', "
                        "`cex`      ='"+cex->Text+"', "
                        "`utch`     ='"+utch->Text+"', "
                        "`tab_no`   ='"+tab_no->Text+"', "
                        "`obd`      ='"+obd->Text+"', "
                        "`kts`      ='"+kts->Text+"', "
                        "`rr`       ='"+rr->Text+"', "
                        "`tpz`      ='"+tpz->Text+"', "
                        "`tsht`     ='"+tsht->Text+"', "
                        "`kvn`      ='"+vn->Text+"', "
                        "`reason`   ='"+reason->Text+"', "
                        "`tfact`    ='"+tfact->Text+"', "
                        "`descr`    ='"+ekran(descr->Text)+"' ");

        TADOQuery * rez = DB->SendSQL("select last_insert_id() id");
        if (rez)
        {
            surcharge_id = rez->FieldByName("id")->Value;
            delete rez;
        }
        DB->SendCommand("insert into `manufacture`.`orders` "
                        "set kol_request = '"+kol->Text+"', kol_maked = '"+kol->Text+"', "
                        "surcharge_id = '"+surcharge_id+"', creation_date = now() ");

        rez = DB->SendSQL("select last_insert_id() id");
        if (rez)
        {
            nar_no->Text = rez->FieldByName("id")->Value;
            delete rez;
        }
    }
    tr.Commit();
}
void __fastcall TSurchargeList::opr_kodChange(TObject *Sender)
{
//opr_id
    TADOQuery *rez = DB->SendSQL("select a.name from `equipment`.`opr_names` a where a.OprID = '"+opr_kod->Text+"'" );
    if (rez)
    {
        if (!rez->RecordCount)
        {
            opr_kod->Color = clRed;
        }
        else
        {
            opr_kod->Color = clWindow;
			opr_name->Text = rez->FieldByName("name")->Value;
        }
        delete rez;
    }
}
void __fastcall TSurchargeList::zak_noChange(TObject *Sender)
{
//zak_no
    TADOQuery *rez = DB->SendSQL("select zak_id from `manufacture`.`zakaz_list` a where a.zakaz = '"+zak_no->Text+"'" );
    if (rez)
    {
        if (!rez->RecordCount)
        {
            zak_no->Color = clRed;
        }
        else
        {
            zak_no->Color = clWindow;
            zak_id = rez->FieldByName("zak_id")->Value;
        }
        delete rez;
    }
}
void __fastcall TSurchargeList::part_noChange(TObject *Sender)
{
//part_no
    TADOQuery *rez = DB->SendSQL("select part_id from `manufacture`.`parts` a where a.zak_id = '"+zak_id+"' and a.part_no = '"+part_no->Text+"'" );
    if (rez)
    {
        if (!rez->RecordCount)
        {
            part_no->Color = clRed;
        }
        else
        {
            part_no->Color = clWindow;
            part_id = rez->FieldByName("part_id")->Value;
        }
        delete rez;
    }
}
void __fastcall TSurchargeList::tab_noChange(TObject *Sender)
{
//tab_no
    std::string sql = std::string("select IFNULL(concat(family, ' ',Upper(left(name,1)),'.', Upper(left(otch,1)),'.'),'') fio from `manufacture`.`workers` where tab_no ='")+
            AnsiString(tab_no->Text).c_str()
            +"' and date_from < now() and (date_to >=now() or date_to is null) ";

    TADOQuery *rez = DB->SendSQL(sql.c_str());
    fio -> Text= "";
    if (rez)
    {
        if (rez->RecordCount)
        {
            fio->Color = clWindow;
			fio->Text = rez->FieldByName("fio")->Value;
        }
        else
        {
            fio->Color = clRed;
        }
        delete rez;
    }
}
