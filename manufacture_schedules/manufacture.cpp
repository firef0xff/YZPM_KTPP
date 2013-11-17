//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "manufacture.h"
#include "ZapCreator.h"
#include "ZakazCreator.h"
#include "IzdAppender.h"
#include "functions.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

#define ZAP_ID_COL 4
__fastcall TManufactureControl::TManufactureControl(TComponent* Owner,TWinControl *_p, int &_LUser,cSQL *db,IconsData *_IcoData,int **_selected)
    : TFrame(Owner),LUser(_LUser),selected(_selected)
{
    if (count==0)
    {
        DB=db;
        IcoData=_IcoData;
    }
    count++;
    // расположение
    Align=alClient;
    Parent=_p;
    Name=Name+String(count);

    if (Parent->ClassNameIs("TTabSheet"))
    {
        ((TTabSheet*)Parent)->Caption="Запуски     ";
    }
    contentTV->Images=IcoData->GetImgList();

    zapSG->Cells[1][0] = "Название";
    zapSG->Cells[2][0] = "Дата начала";
    zapSG->Cells[3][0] = "Дата окончания";
    AutoWidthSG(zapSG);

    detSG->Cells[1][0] = "Обозначение";
    detSG->Cells[2][0] = "Наименование";
    detSG->Cells[3][0] = "Кол - во";
    detSG->Cells[4][0] = "Труд. Ед.";
    detSG->Cells[5][0] = "Труд.";
    detSG->Cells[6][0] = "Изготовлено";
    detSG->Cells[7][0] = "Брак";
    AutoWidthSG(detSG);

    operSG->Cells[1][0] = "Подр.";
    operSG->Cells[2][0] = "№ ОП";
    operSG->Cells[3][0] = "Код";
    operSG->Cells[4][0] = "Операция";
    operSG->Cells[5][0] = "Труд.";
    operSG->Cells[6][0] = "Код Обор.";
    operSG->Cells[7][0] = "Оборудование";
    AutoWidthSG(operSG);

    makeSG->Cells[1][0] = "№ ОП";
    makeSG->Cells[2][0] = "Код";
    makeSG->Cells[3][0] = "Операция";
    makeSG->Cells[4][0] = "Кол - во";
    makeSG->Cells[5][0] = "Изг - но";
    makeSG->Cells[6][0] = "Брак";
    AutoWidthSG(makeSG);

    det_matSG->Cells[1][0] = "Обозначение";
    det_matSG->Cells[2][0] = "Наименование";
    det_matSG->Cells[3][0] = "Ед. Изм.";
    det_matSG->Cells[4][0] = "Необходимо";
    det_matSG->Cells[5][0] = "Использованно";
    AutoWidthSG(det_matSG);

    det_oborudSG->Cells[1][0] = "Труд.";
    det_oborudSG->Cells[2][0] = "Подр.";
    det_oborudSG->Cells[3][0] = "Код Обор.";
    det_oborudSG->Cells[4][0] = "Оборудование";
    det_oborudSG->Cells[5][0] = "Заданий";
    det_oborudSG->Cells[6][0] = "Выполнено";
    AutoWidthSG(det_oborudSG);

}
__fastcall    TManufactureControl::~TManufactureControl(void)
{
    count--;
    if (count==0)
    {
        DB=0;
        IcoData=0;
    }
}

void TManufactureControl::LoadZapusk(String zapusk, String zakaz, String det)
{
    SGClear(zapSG,1);
    zakTV->Items->Clear();
    contentTV->Items->Clear();

    String zap_sql = "select a.name, a.begin, a.end, a.zap_id from manufacture.manufacture_orders a ";
    if (zakaz.Length() || det.Length())
    {
        zap_sql +=     " join manufacture.parts b on a.zap_id = b.zap_id "
                    " join manufacture.zakaz_list e on b.zak_id = e.zak_id ";

        if (det.Length())
        {
            zap_sql +=     " join manufacture.part_content c on b.part_id = c.part_id "
                        " join manufacture.det_names d on d.det_id = c.det_id ";
        }
    }

    String where = "where 1 ";
    if (zapusk.Length())
    {
        where += " and a.name like '%"+zapusk+"%' ";
    }
    if (zakaz.Length())
    {
        where += " and e.zakaz like '%"+zakaz+"%' ";
    }
    if (det.Length())
    {
        where += " and d.obd like '%"+GostToVin(det)+"%' ";
    }
    String order = "order by a.name";
    TADOQuery *rez = DB->SendSQL(zap_sql+where+order);
    if (rez && rez->RecordCount)
    {
        for (rez->First(); !rez->Eof; rez->Next())
        {
            int row = zapSG->RowCount - 1;
            zapSG->Cells[1][row] = rez->FieldByName("name")->Value;
            zapSG->Cells[2][row] = rez->FieldByName("begin")->Value;
            zapSG->Cells[3][row] = rez->FieldByName("end")->Value;
            zapSG->Cells[ZAP_ID_COL][row] = rez->FieldByName("zap_id")->Value;
            zapSG->RowCount ++;
        }
        if (zapSG->RowCount > 2)
        {
            zapSG->RowCount--;
        }
    }
    delete rez;
    AutoWidthSG(zapSG);
    bool t;
    zapSGSelectCell(this, zapSG->Col, zapSG->Row, t); 
}
void TManufactureControl::LoadZakaz (String zap_id, String zakaz, String det)
{
    zakTV->Items->Clear();

    String zap_sql = "select a.zap_id, a.zak_id, a.part_no, a.part_id, b.zakaz from manufacture.parts a "
                     " join manufacture.zakaz_list b on a.zak_id = b.zak_id ";
    if (zap_id.Length())
    {
        zap_sql +=     " join manufacture.manufacture_orders c on a.zap_id = c.zap_id ";
    }
    if (det.Length())
    {
        zap_sql +=     " join manufacture.part_content d on a.part_id = d.part_id "
                    " join manufacture.det_names e on e.det_id = d.det_id ";
    }

    String where = "where 1 ";
    if (zap_id.Length())
    {
        where += " and c.zap_id = '"+zap_id+"' ";
    }
    if (zakaz.Length())
    {
        where += " and b.zakaz like '%"+zakaz+"%' ";
    }
    if (det.Length())
    {
        where += " and e.obd like '%"+GostToVin(det)+"%' ";
    }
    String order = "order by b.zakaz ";

    TADOQuery *rez = DB->SendSQL(zap_sql+where+order);
    if (rez && rez->RecordCount)
    {
        String prev_zakaz;
        TTreeNode *node = 0;
        for (rez->First(); !rez->Eof; rez->Next())
        {
            TTreeNode *ch_node = 0;
            String zak = rez->FieldByName("zakaz")->Value;
            unsigned int part_no = rez->FieldByName("part_no")->Value;
            unsigned __int64 zak_id = (unsigned __int64)rez->FieldByName("zak_id")->Value.operator __int64();
            unsigned __int64 zap_id = (unsigned __int64)rez->FieldByName("zap_id")->Value.operator __int64();
            unsigned __int64 part_id = (unsigned __int64)rez->FieldByName("part_id")->Value.operator __int64();

            if (zak != prev_zakaz)
            {
                ZakazNode *ptr = new ZakazNode(zak_id, zap_id, zak);
                node = zakTV->Items->AddObject(node, ptr->getZakaz(), (void *)ptr);
                prev_zakaz = zak;
            }
            PartNode *ptr = new PartNode(part_id, part_no);
            ch_node = zakTV->Items->AddChildObject(node, ptr->getPartNo(), (void*)ptr);
        }
    }
    delete rez;
}
void TManufactureControl::LoadIzd   (String zap_id, unsigned __int64 zak_id, unsigned __int64 part_id, String det)
{
    contentTV->Items->Clear();

    String zap_sql = "select b.obd, b.name, a.det_id, a.kol, count(b1.det_idp) have_childs, b.sp_id, "
                     " b.sp_name from manufacture.part_content a "
                     " join manufacture.det_names b on a.det_id = b.det_id "
                     " left join manufacture.det_tree b1 on a.det_id = b1.det_idp ";
    if (zap_id.Length()||zak_id)
    {
        zap_sql +=     " join manufacture.parts c on a.part_id = c.part_id ";
    }

    String where = "where 1 ";
    if (zap_id.Length())
    {
        where += " and c.zap_id = '"+zap_id+"' ";
    }
    if (zak_id)
    {
        where += " and c.zak_id = '"+String(zak_id)+"' ";
    }
    if (part_id)
    {
        where += " and a.part_id = '"+String(part_id)+"' ";
    }
    if (det.Length())
    {
        where += " and b.obd like '%"+GostToVin(det)+"%' ";
    }
    String order = "group by a.det_id order by b.obd ";
    TADOQuery *rez = DB->SendSQL(zap_sql+where+order);
    if (rez && rez->RecordCount)
    {
        TTreeNode *node = 0;
        for (rez->First(); !rez->Eof; rez->Next())
        {
            String obd = rez->FieldByName("obd")->Value;
            String name = rez->FieldByName("name")->Value;
            unsigned __int64 det_id = (unsigned __int64)rez->FieldByName("det_id")->Value.operator __int64();
            unsigned int kol = (unsigned int)rez->FieldByName("kol")->Value.operator int();
            bool have_childs = int(rez->FieldByName("have_childs")->Value);
            unsigned int sp_id = (unsigned int)rez->FieldByName("sp_id")->Value.operator int();
            String sp_name = rez->FieldByName("sp_name")->Value;
            IzdNode *ptr = new IzdNode(name, obd, det_id, kol, sp_id, sp_name);
            node = contentTV->Items->AddObject(node, VinToGost(ptr->getDetObd())+" "+ptr->getDetName()+" - "+String(ptr->getCount())+" шт.", (void*)ptr);
            Set_img(node);
            if (have_childs)
            {
                contentTV->Items->AddChildObject(node, "", 0);
            }
        }
    }
    delete rez;
}

void TManufactureControl::LoadDetailData(String zap_id, unsigned __int64 zak_id, unsigned __int64 part_id, unsigned __int64 det_id)
{
    if (Content_detail->ActivePage == Parts)
    {
        LoadDetailParts(zap_id, zak_id, part_id, det_id);
    }
    else if (Content_detail->ActivePage == StandartParts)
    {
        LoadDetailStandartParts(zap_id, zak_id, part_id, det_id);
    }
    else if (Content_detail->ActivePage == Materials)
    {
        LoadDetailMaterials(zap_id, zak_id, part_id, det_id);
    }
    else if (Content_detail->ActivePage == Oborud)
    {
        LoadDetailOborud(zap_id, zak_id, part_id, det_id);
    }
}
void TManufactureControl::LoadDetailParts          (String zap_id, unsigned __int64 zak_id, unsigned __int64 part_id, unsigned __int64 det_id)
{
    SGClear(detSG, 1);
    SGClear(operSG);
    SGClear(det_oborudSG);
    SGClear(det_matSG);
    SGClear(makeSG);


    //получить список деталей для развертки
    String tmp_drop = "drop temporary table if exists manufacture.idc";
    String tmp_create = "create temporary table if not exists manufacture.idc as ";
    String sql = "select a.det_id, a.sp_id from manufacture.det_names a ";
    String where = " where true ";
    String joins;
    if (det_id > 0)
    {
        where+= " and a.det_id = '"+String(det_id)+"' ";
    }
    if (part_id > 0 || zak_id > 0 || zap_id!="")
    {
        joins += " join manufacture.part_content b on b.det_id = a.det_id "
                 " join manufacture.parts c on c.part_id = b.part_id ";
        if (part_id > 0)
        {
            where += " and c.part_id = '"+String(part_id)+"' ";
        }
        if (zak_id > 0)
        {
            where += " and c.zak_id = '"+String(zak_id)+"' ";
        }
        if (zap_id > 0)
        {
            where += " and c.zap_id = '"+zap_id+"' ";
        }
    }
    DB->SendCommand(tmp_drop);
    DB->SendCommand(tmp_create + sql + joins + where);

    //развернуть детали до составов учитывая разделы спецификации 0,2,3,4,8
    String tmp2_drop = "drop temporary table if exists manufacture.dets";
    String tmp2_create = "create temporary table if not exists manufacture.dets "
                        "( "
                        " det_idc bigint(20) unsigned not null, "
                        " det_idp bigint(20) unsigned default null, "
                        " lvl int(10) unsigned not null, "
                        " key det_idc(`det_idc`), "
                        " key det_idp(`det_idp`) "
                        " )";
    String tmp3_drop = "drop temporary table if exists manufacture.dets_tmp";
    String tmp3_create = "create temporary table if not exists manufacture.dets_tmp "
                        "( "
                        " det_idc bigint(20) unsigned not null, "
                        " det_idp bigint(20) unsigned default null, "
                        " lvl int(10) unsigned not null, "
                        " key det_idc(`det_idc`), "
                        " key det_idp(`det_idp`) "
                        " )";

    //инициализация
    DB->SendCommand(tmp2_drop);
    DB->SendCommand(tmp2_create);
    int lvl = 0;
    DB->SendCommand("insert into manufacture.dets select a.det_id, null, '"+String(lvl)+"' "
                    "from manufacture.idc a "
                    "where a.sp_id in (0,2,3,4,8)");

    while (lvl < 100)
    {
        TADOQuery *rez = DB->SendSQL("select count(1) cnt from manufacture.dets where lvl = '"+String(lvl)+"'");
        if (rez&&rez->RecordCount)
        {
            if (!(int)rez->FieldByName("cnt")->Value)
            {
                break;
            }
            delete rez;
        }
        DB->SendCommand(tmp3_drop);
        DB->SendCommand(tmp3_create);
        DB->SendCommand("insert into manufacture.dets_tmp select * from manufacture.dets where lvl = '"+String(lvl)+"'");

        DB->SendCommand("insert into manufacture.dets select a.det_idc, a.det_idp ,'"+String(lvl+1)+"' "
                        "from manufacture.det_tree a "
                        "join manufacture.dets_tmp b on a.det_idp = b.det_idc "
                        "join manufacture.det_names c on a.det_idc = c.det_id "
                        "where c.sp_id in (0,2,3,4,8)");
        ++lvl;
    }
    DB->SendCommand(tmp_drop);
    DB->SendCommand(tmp3_drop);

    //посчитать трудоемкости по списку
    String tmp4_drop = "drop temporary table if exists manufacture.dets_trud";
    String tmp4_create = "create temporary table if not exists manufacture.dets_trud as "
                         " select a.det_idc as det_id, sum(c.tsht*c.ksht*c.krop/c.kolod ) as trud_ed, "
                         " sum(c.tsht*c.ksht*c.krop/c.kolod )*d.kol_using as trud, d.kol_using "
                         " from manufacture.dets a "
                         " join manufacture.operation_list b on a.det_idc = b.det_id "
                         " join manufacture.operation_norms c on b.OpUUID = c.OpUUID "
                         " join manufacture.det_tree d on d.det_idc = a.det_idc "
                         " group by a.det_idc";
    DB->SendCommand(tmp4_drop);
    DB->SendCommand(tmp4_create);

    DB->SendCommand("insert into manufacture.dets_trud "
                    " select a.det_idc as det_id, sum(c.tsht*c.ksht*c.krop/c.kolod ) as trud_ed, "
                    " sum(c.tsht*c.ksht*c.krop/c.kolod )*d.kol as trud, d.kol "
                    " from manufacture.dets a "
                    " join manufacture.operation_list b on a.det_idc = b.det_id "
                    " join manufacture.operation_norms c on b.OpUUID = c.OpUUID "
                    " join manufacture.part_content d on d.det_id = a.det_idc and a.det_idp is null "
                    " group by a.det_idc");
    //посчитать количества по списку

    //соеденить данные
    TADOQuery *rez = DB->SendSQL("select a.det_idc det_id, round(sum(b.trud_ed),3) trud_ed, "
                                 " round(sum(b.trud),3) trud, sum(b.kol_using) kol, c.obd, c.name, c.id id, "
                                 " 0 maked, 0 broken "
                                 " from manufacture.dets a "
                                 " join manufacture.dets_trud b on a.det_idc = b.det_id "
                                 " join manufacture.det_names c on a.det_idc = c.det_id "
                                 " group by c.id order by c.sp_id, c.obd");
                                 //TODO место для постранички
    DB->SendCommand(tmp4_drop);
    DB->SendCommand(tmp2_drop);
    //вывести результат
    if (rez)
    {
        for (rez->First(); !rez->Eof; rez->Next())
        {
            int row = detSG->RowCount-1;
            detSG->Cells[1][row] = VinToGost(rez->FieldByName("obd")->Value);
            detSG->Cells[2][row] = rez->FieldByName("name")->Value;
            detSG->Cells[3][row] = rez->FieldByName("kol")->Value;
            detSG->Cells[4][row] = rez->FieldByName("trud_ed")->Value;
            detSG->Cells[5][row] = rez->FieldByName("trud")->Value;
            detSG->Cells[6][row] = rez->FieldByName("maked")->Value;
            detSG->Cells[7][row] = rez->FieldByName("broken")->Value;
            detSG->Cells[8][row] = rez->FieldByName("det_id")->Value;  //ID FIELD
            detSG->Cells[9][row] = rez->FieldByName("id")->Value;          //ID FIELD
            ++detSG->RowCount;
        }
        delete rez;
        if (detSG->RowCount>2)
        {
            --detSG->RowCount;
        }
        AutoWidthSG(detSG);
    }
    return;
}

void TManufactureControl::LoadTechDetails   (String det_id)
{
   SGClear(operSG);
   String sql = "select a.cex, a.utch, a.opr, a.oprid, a.OboID,"
                " ifnull(c.name, '') oper_name, "
                " ifnull(d.name, '') obo_name, "
                " ifnull(round(sum(b.tsht*b.ksht*b.krop/b.kolod),3), 0) as trud_ed "
                " from manufacture.operation_list a "
                " left join manufacture.operation_norms b on a.OpUUID = b.OpUUID "
                " left join equipment.opr_names c on c.OprID = a.oprid "
                " left join equipment.obor_list d on d.oboID = a.oboID "
                " where a.det_id = '"+det_id+"'"
                " group by a.det_id,a.OpUUID order by a.det_id, a.opr, a.oboid ";

    TADOQuery *rez = DB->SendSQL(sql);
    if (rez)
    {
        for (rez->First(); !rez->Eof; rez->Next())
        {
            int row = operSG->RowCount - 1;
            String podr;
            if (rez->FieldByName("cex")->Value.IsNull())
            {
                podr += "XX";
            }
            else
            {
                podr += rez->FieldByName("cex")->Value.operator UnicodeString();
            }

            if (rez->FieldByName("utch")->Value.IsNull())
            {
                podr += "XX";
            }
            else
            {
                podr += rez->FieldByName("utch")->Value.operator UnicodeString();
            }
            operSG->Cells[1][row] = podr;
            operSG->Cells[2][row] = rez->FieldByName("opr")->Value;
            operSG->Cells[3][row] = rez->FieldByName("oprid")->Value;
            operSG->Cells[4][row] = rez->FieldByName("oper_name")->Value;
            operSG->Cells[5][row] = rez->FieldByName("trud_ed")->Value;
            operSG->Cells[6][row] = rez->FieldByName("OboID")->Value;
            operSG->Cells[7][row] = rez->FieldByName("obo_name")->Value;"Оборудование";  //

            ++operSG->RowCount;
        }
        if (operSG->RowCount > 2)
        {
            --operSG->RowCount;
        }
        delete rez;
    }
    AutoWidthSG(operSG);
}
void TManufactureControl::LoadOborudDetails (String det_id)
{
    SGClear(det_oborudSG);
    String sql = "select a.cex, a.utch, a.OboID,"
                 " ifnull(d.name, '') obo_name, "
                 " ifnull(round(sum(b.tsht*b.ksht*b.krop/b.kolod),3), 0) as trud_ed, "
                 " 0 as schedule, "
                 " 0 as maked "
                 " from manufacture.operation_list a "
                 " left join manufacture.operation_norms b on a.OpUUID = b.OpUUID "
                 " left join equipment.obor_list d on d.oboID = a.oboID "
                 " where a.det_id = '"+det_id+"'"
                 " group by a.cex, a.utch, a.oboid  order by a.cex, a.utch, a.oboid ";
    TADOQuery *rez = DB->SendSQL(sql);
    if (rez)
    {
        for (rez->First(); !rez->Eof; rez->Next())
        {
            int row = det_oborudSG->RowCount - 1;
            String podr;
            if (rez->FieldByName("cex")->Value.IsNull())
            {
                podr += "XX";
            }
            else
            {
                podr += rez->FieldByName("cex")->Value.operator UnicodeString();
            }

            if (rez->FieldByName("utch")->Value.IsNull())
            {
                podr += "XX";
            }
            else
            {
                podr += rez->FieldByName("utch")->Value.operator UnicodeString();
            }
            det_oborudSG->Cells[1][row] = rez->FieldByName("trud_ed")->Value;
            det_oborudSG->Cells[2][row] = podr;
            det_oborudSG->Cells[3][row] = rez->FieldByName("OboID")->Value;
            det_oborudSG->Cells[4][row] = rez->FieldByName("obo_name")->Value;
            det_oborudSG->Cells[5][row] = rez->FieldByName("schedule")->Value;
            det_oborudSG->Cells[6][row] = rez->FieldByName("maked")->Value;

            ++det_oborudSG->RowCount;
        }
        if (det_oborudSG->RowCount > 2)
        {
            --det_oborudSG->RowCount;
        }
        delete rez;
    }
    AutoWidthSG(det_oborudSG);
}

void __fastcall TManufactureControl::detSGSelectCell(TObject *Sender, int ACol, int ARow,
          bool &CanSelect)
{
    if (detSG->Cells[8][ARow] == "")
    {
        return;
    }
    if (DetDetailControl->ActivePage == OperationsSheet)
        LoadTechDetails(detSG->Cells[8][ARow]);
    if (DetDetailControl->ActivePage == ObourSheet)
        LoadOborudDetails(detSG->Cells[8][ARow]);
}
void __fastcall TManufactureControl::DetDetailControlChange(TObject *Sender)
{
    bool t;
    detSGSelectCell(0, detSG->Col, detSG->Row, t);
}


void TManufactureControl::LoadDetailStandartParts(String zap_id, unsigned __int64 zak_id, unsigned __int64 part_id, unsigned __int64 det_id)
{
    return;
}
void TManufactureControl::LoadDetailMaterials     (String zap_id, unsigned __int64 zak_id, unsigned __int64 part_id, unsigned __int64 det_id)
{
    return;
}
void TManufactureControl::LoadDetailOborud         (String zap_id, unsigned __int64 zak_id, unsigned __int64 part_id, unsigned __int64 det_id)
{
    return;
}

void __fastcall TManufactureControl::zakTVDeletion(TObject *Sender, TTreeNode *Node)
{
    if (Node->Data)
    {
        delete (NodeData *)Node->Data;
    }
    return;
}
void __fastcall TManufactureControl::contentTVDeletion(TObject *Sender, TTreeNode *Node)
{
    if (Node->Data)
    {
        delete (NodeData *)Node->Data;
    }
    return;
}

void __fastcall TManufactureControl::CreateZapusk(TObject *Sender)
{
    TZapuskWnd *wnd = new TZapuskWnd(this);
    if (wnd->ShowModal() == mrOk)
    {
        DB->SendCommand("insert into manufacture.manufacture_orders (begin,end,user,name) "
                    "values ('"+wnd->dtStart->Date.FormatString("yyyy-mm-dd")+"','"
                    +wnd->dtEnd->Date.FormatString("yyyy-mm-dd")+"','"+"user"+"','"+wnd->name->Text+"')");
        LoadZapusk(wnd->name->Text,"","");
    }
    delete wnd;
    return;
}
void __fastcall TManufactureControl::RemoveZapusk(TObject *Sender)
{
    if ( MessageBoxA(this->Handle, "Удалить запуск?", "Удалить запуск?",MB_YESNO|MB_ICONQUESTION) == mrYes )
    {
        DB->SendCommand("delete from `manufacture`.`manufacture_orders` where `zap_id` = "+zapSG->Cells[ZAP_ID_COL][zapSG->Row]);
        Find->Click();
    }
    return;
}
void __fastcall TManufactureControl::InWorkZapusk(TObject *Sender)
{
    if ( MessageBoxA(this->Handle, "Запустить в работу?", "Запустить в работу?",MB_YESNO|MB_ICONQUESTION) == mrYes )
    {
        return;
    }
    return;
}
void __fastcall TManufactureControl::ToEditZapusk(TObject *Sender)
{
    if ( MessageBoxA(this->Handle, "Вернуть в разработку?", "Вернуть в разработку?",MB_YESNO|MB_ICONQUESTION) == mrYes )
    {
        return;
    }
    return;
}
void __fastcall TManufactureControl::zapSGSelectCell(TObject *Sender, int ACol, int ARow,
          bool &CanSelect)
{
    if (zapSG->Cells[ZAP_ID_COL][ARow] == "")
    {
        return;
    }
    LoadZakaz(zapSG->Cells[ZAP_ID_COL][ARow], "", "");
    LoadIzd(zapSG->Cells[ZAP_ID_COL][ARow], 0, 0, "");
    LoadDetailData(zapSG->Cells[ZAP_ID_COL][ARow], 0, 0, 0);
}

void __fastcall TManufactureControl::AddZakaz(TObject *Sender)
{
    if (zapSG->Cells[ZAP_ID_COL][zapSG->Row] == "")
    {
        return;
    }
    TZakazWnd *wnd = new TZakazWnd(this, DB);
    if (wnd->ShowModal() == mrOk)
    {
        TADOQuery *rez = DB->SendSQL("select zak_id from manufacture.zakaz_list a where a.zakaz =" + wnd->zakaz->Text);
        if (rez)
        {
            if (!rez->RecordCount)
            {
                delete rez;
                DB->SendCommand("insert into manufacture.zakaz_list set zakaz = '" + wnd->zakaz->Text+"'");
                rez = DB->SendSQL("select zak_id from manufacture.zakaz_list a where a.zakaz ='" + wnd->zakaz->Text+"'");
            }
            DB->SendCommand("insert into manufacture.parts (zap_id,zak_id,part_no) values "
                            "('"+zapSG->Cells[ZAP_ID_COL][zapSG->Row]+"','"+rez->FieldByName("zak_id")->Value+"','"+wnd->part->Text+"')" );
            LoadZakaz(zapSG->Cells[ZAP_ID_COL][zapSG->Row], wnd->zakaz->Text, "");
        }
        delete rez;
    }
    delete wnd;
    return;
}
void __fastcall TManufactureControl::RemoveZakaz(TObject *Sender)
{
    if ( MessageBoxA(this->Handle, "Удалить заказ/партию из запуска?", "Удалить заказ/партию из запуска?",MB_YESNO|MB_ICONQUESTION) == mrYes )
    {
        DB->SendCommand("BEGIN");
        try
        {
            for (size_t i = 0; i < zakTV->SelectionCount; ++i)
            {
                TTreeNode *node = zakTV->Selections[i];
                if (node->Level == 0)
                {//удалить заказ
                    for (TTreeNode *ch_node = node->getFirstChild(); ch_node; ch_node = node->GetNextChild(ch_node))
                    {
                        PartNode *ptr = (PartNode *)ch_node->Data;
                        String sql = "Delete from manufacture.parts where part_id = '"+String(ptr->getPartID())+"'";
                        DB->SendCommand(sql);
                    }
                }
                else
                {//удалить партию
                    PartNode *ptr = (PartNode *)node->Data;
                    String sql = "Delete from manufacture.parts where part_id = '"+String(ptr->getPartID())+"'";
                    DB->SendCommand(sql);
                }
            }
        }
        catch(...)
        {
            DB->SendCommand("ROLLBACK");
        }
        DB->SendCommand("COMMIT");
    }
    return;
}
void __fastcall TManufactureControl::InWorkZakaz(TObject *Sender)
{
    if ( MessageBoxA(this->Handle, "Запустить в работу?", "Запустить в работу?",MB_YESNO|MB_ICONQUESTION) == mrYes )
    {
        return;
    }
    return;
}
void __fastcall TManufactureControl::ToEditZakaz(TObject *Sender)
{
    if ( MessageBoxA(this->Handle, "Вернуть в разработку?", "Вернуть в разработку?",MB_YESNO|MB_ICONQUESTION) == mrYes )
    {
        return;
    }
    return;
}
void __fastcall TManufactureControl::zakTVClick(TObject *Sender)
{
    TTreeNode *node = zakTV->Selected;
    if (node)
    {
        if (!node->Level)
        {
            ZakazNode *ptr = (ZakazNode *)node->Data;
            LoadIzd(String(ptr->getZapID()), ptr->getZakID(), 0, "");
            LoadDetailData(String(ptr->getZapID()), ptr->getZakID(), 0, 0);
        }
        else
        {
            PartNode *ptr = (PartNode *)node->Data;
            LoadIzd("", 0, ptr->getPartID(), "");
            LoadDetailData("", 0, ptr->getPartID(), 0);
        }
    }

    return;
}

void __fastcall TManufactureControl::AddIzdelie(TObject *Sender)
{
    if (zapSG->Cells[ZAP_ID_COL][zapSG->Row] == "")
    {
        return;
    }
    if (!selected || !*selected)
    {
        return;
    }
    for (size_t i =1; i <=**selected; i++)
    {
        Obd det(DB,*(*selected+i));
        TIzdAppenderWnd *wnd = new TIzdAppenderWnd(this, DB, zapSG->Cells[ZAP_ID_COL][zapSG->Row], det);
        if (wnd->ShowModal() == mrOk)
        {
            LoadIzd(zapSG->Cells[ZAP_ID_COL][zapSG->Row], 0, 0, "");
        }
        delete wnd;
    }

}
void __fastcall TManufactureControl::RemoveIzdelie(TObject *Sender)
{
    if (contentTV->SelectionCount && MessageBoxA(this->Handle, "Удалить изделие?", "Удалить изделие?",MB_YESNO|MB_ICONQUESTION) == mrYes )
    {
        Transaction tr(DB);
        for (size_t i = 0; i < contentTV->SelectionCount; ++i)
        {
            TTreeNode *node = contentTV->Selections[i];
            if (node->Level == 0)
            {//удалить заказ
                IzdNode *ptr = (IzdNode *)node->Data;
                DB->SendCommand("call manufacture.DeleteIzd('"+String(ptr->getDetID())+"')");
            }
        }
        tr.Commit();
        LoadIzd(zapSG->Cells[ZAP_ID_COL][zapSG->Row], 0, 0, "");
    }
    return;
}
void __fastcall TManufactureControl::IncludePath(TObject *Sender)
{
    TTreeNode *node = contentTV->Selected;
    IzdPartNode *ptr = (IzdPartNode *)node->Data;
    DB->SendCommand("call manufacture.SetUsage ('"+String(ptr->getDetID())+"', '1')");
    Update(node);
    return;
}
void __fastcall TManufactureControl::UnIncludePath(TObject *Sender)
{
    TTreeNode *node = contentTV->Selected;
    IzdPartNode *ptr = (IzdPartNode *)node->Data;
    DB->SendCommand("call manufacture.SetUsage ('"+String(ptr->getDetID())+"', '0')");
    Update(node);
    return;
}
void __fastcall TManufactureControl::contentTVExpanding(TObject *Sender, TTreeNode *Node,
          bool &AllowExpansion)
{
    if (!Node->Data)
    {
        return;
    }
    IzdNode *ptr = (IzdNode *)Node->Data;
    Node->DeleteChildren();
    String sql = " select a.det_idp, a.using, b.det_id, b.obd, b.name, a.kol_sp, a.kol_using, count(b1.det_idp) have_childs, b.sp_id, b.sp_name from manufacture.det_tree a "
                 " left join manufacture.det_tree b1 on a.det_idc = b1.det_idp "
                 " join manufacture.det_names b on a.det_idc = b.det_id where a.det_idp = '"+String(ptr->getDetID())+"'group by a.det_idc order by b.sp_id, b.obd";
    TADOQuery *rez = DB->SendSQL(sql);
    if (rez && rez->RecordCount)
    {
        TTreeNode *node = 0;
        TTreeNode *sp_node = 0;
        unsigned int prev_sp_id = -1;
        for (rez->First(); !rez->Eof; rez->Next())
        {
            String obd = rez->FieldByName("obd")->Value;
            String name = rez->FieldByName("name")->Value;
            unsigned __int64 det_id = (unsigned __int64)rez->FieldByName("det_id")->Value.operator __int64();
            unsigned __int64 det_idp = (unsigned __int64)rez->FieldByName("det_idp")->Value.operator __int64();
            unsigned int kol_using = (unsigned int)rez->FieldByName("kol_using")->Value.operator int();
            unsigned int kol_sp = (unsigned int)rez->FieldByName("kol_sp")->Value.operator int();
            bool have_childs = int(rez->FieldByName("have_childs")->Value);
            unsigned int sp_id = (unsigned int)rez->FieldByName("sp_id")->Value.operator int();
            String sp_name = rez->FieldByName("sp_name")->Value;
            bool using_ = rez->FieldByName("using")->Value;
            IzdPartNode *ptr = new IzdPartNode(name, obd, det_id, kol_using, det_idp, kol_sp, sp_id, sp_name, using_);

            if (prev_sp_id != sp_id)
            {
                sp_node = contentTV->Items->AddChildObject(Node, sp_name, 0);
                sp_node->ImageIndex = IcoData->GetInList(sp_id,true,1);
                sp_node->SelectedIndex = sp_node->ImageIndex;
                sp_node->ExpandedImageIndex = sp_node->ImageIndex;
                prev_sp_id = sp_id;
                Set_img(sp_node);
            }
            node= contentTV->Items->AddChildObject(sp_node, VinToGost(ptr->getDetObd())+" "+ptr->getDetName(), (void*)ptr);
            Set_img(node);
            if (have_childs)
            {
                contentTV->Items->AddChildObject(node, "", 0);
            }
        }
    }
    delete rez;
}


void __fastcall TManufactureControl::FindClick(TObject *Sender)
{
    LoadZapusk(Zap_name->Text,Zakaz->Text,Obozn->Text);
    return;
}
void __fastcall TManufactureControl::ClearZpusk(TObject *Sender)
{
    Zap_name->Text = "";
    Find->Click();
    return;
}
void __fastcall TManufactureControl::ClearZakaz(TObject *Sender)
{
    Zakaz->Text = "";
    Find->Click();
    return;
}
void __fastcall TManufactureControl::ClearIzdelie(TObject *Sender)
{
    Obozn->Text = "";
    Find->Click();
    return;
}


void            TManufactureControl::Set_img            (TTreeNode *node)
{
    if (node)
    {
        if (node->Data)
        {
            IzdNode *data=(IzdNode *)node->Data;
            node->ImageIndex=IcoData->GetInList(data->getSpRazd(),true,1);
            node->SelectedIndex=node->ImageIndex;
            node->ExpandedImageIndex=node->ImageIndex;
            if (data->IsUsed()) //интересный фак бул переменная может хранить числовые значения и принимать не только -1 и 0
            {
                node->StateIndex=1;
            }else
            {
                node->StateIndex=2;
            }
        }
    }
}
void __fastcall TManufactureControl::contentTVMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
    TTreeNode *node = contentTV->GetNodeAt(X, Y);
    contentTV->Selected = node;
    if (node)
    {
        if (!node->Level)
        {
            contentTV->PopupMenu = PAB3;
        }
        else
        {
            if (node->Data)
            {
                contentTV->PopupMenu = PAB3_1;
                IzdPartNode *ptr = (IzdPartNode *)node->Data;
                if (ptr->IsUsed())
                {
                    MenuItem11->Enabled = false;
                    MenuItem12->Enabled = true;
                }
                else
                {
                    MenuItem11->Enabled = true;
                    MenuItem12->Enabled = false;
                }
            }
            else
            {
                contentTV->PopupMenu = 0;
            }
        }
        if (node->Data)
        {
            IzdNode *ptr = (IzdNode *)node->Data;
            LoadDetailData("",0,0,ptr->getDetID());
        }
    }
    return;
}
void             TManufactureControl::Update       (TTreeNode *node)
{
    if (node->Data)
    {
        IzdPartNode *ptr = (IzdPartNode *)node->Data;
        ptr->Update(DB);
        Set_img(node);
    }
    for (TTreeNode * i = node->getFirstChild(); i; i=node->GetNextChild(i))
    {
        Update(i);
    }
}

//---------------------------------------------------------------------------

