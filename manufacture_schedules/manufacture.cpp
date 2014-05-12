//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "manufacture.h"
#include "ZapCreator.h"
#include "ZakazCreator.h"
#include "IzdAppender.h"
#include "functions.h"
#include "ReportBuilder.h"
#include "sstream.h"

#include <surcharge/surcharge_list.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

#define ZAP_ID_COL 4
#define ZAP_IN_WORK_COL 5
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

    // настройка содержимого
    std::stringstream sql; sql<<"call administration.Get_Rights('"<<LUser<<"')";
    TADOQuery *rez=DB->SendSQL(sql.str().c_str());
    bool manufacture_orders=false,Run_at_manufacture=false,manufacture_view=false;
    if(rez)
    {
        for (rez->First(); !rez->Eof; rez->Next())
        {
            const String val=rez->FieldByName("progname")->Value;
            if (val=="manufacture_orders")
            {
                manufacture_orders=true;
            }
            if (val=="Run_at_manufacture")
            {
                Run_at_manufacture=true;
            }
            if (val=="manufacture_view")
            {
                manufacture_view=true;
            }
        }
        delete rez;
    }
    N1->Enabled = Run_at_manufacture;
    N2->Enabled = Run_at_manufacture;
    N3->Enabled = Run_at_manufacture;
    N4->Enabled = Run_at_manufacture;
    MenuItem1->Enabled = Run_at_manufacture;
    MenuItem2->Enabled = Run_at_manufacture;
    MenuItem3->Enabled = Run_at_manufacture;
    MenuItem4->Enabled = Run_at_manufacture;
    MenuItem5->Enabled = Run_at_manufacture;
    MenuItem7->Enabled = Run_at_manufacture;
    MenuItem11->Enabled = Run_at_manufacture;
    MenuItem12->Enabled = Run_at_manufacture;

    TabSheet6->Enabled = manufacture_orders;
    this->Enabled = manufacture_view;

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

    OborudSG->Cells[1][0] = "Труд.";
    OborudSG->Cells[2][0] = "Подр.";
    OborudSG->Cells[3][0] = "Код Обор.";
    OborudSG->Cells[4][0] = "Оборудование";
    OborudSG->Cells[5][0] = "Заданий";
    OborudSG->Cells[6][0] = "Выполнено";
    AutoWidthSG(OborudSG);

    detDetails->Cells[1][0] = "Входит в";
    detDetails->Cells[2][0] = "Обозначение";
    detDetails->Cells[3][0] = "Наименование";
    detDetails->Cells[4][0] = "Кол - во";
    detDetails->Cells[5][0] = "Труд. Ед.";
    detDetails->Cells[6][0] = "Труд.";
    detDetails->Cells[7][0] = "Изготовлено";
    detDetails->Cells[8][0] = "Брак";
    AutoWidthSG(detDetails);

    SGNarList->Cells[1][0] = "Наряд";
    SGNarList->Cells[2][0] = "Изгот.";
    SGNarList->Cells[3][0] = "Брак";
    SGNarList->Cells[4][0] = "Таб №";
    SGNarList->Cells[5][0] = "Рабочий";
    SGNarList->Cells[6][0] = "Задание";
    SGNarList->Cells[7][0] = "Остаток";
    SGNarList->Cells[8][0] = "Деталь";
    SGNarList->Cells[9][0] = "Операция";
    SGNarList->Cells[10][0] = "Оборудование";
	AutoWidthSG(SGNarList);


	surch_sg->Cells[1][0] = "Наряд №";

	surch_sg->Cells[2][0] = "Заказ";
	surch_sg->Cells[3][0] = "Партия";
	surch_sg->Cells[4][0] = "Деталь";

	surch_sg->Cells[5][0] = "Цех";
	surch_sg->Cells[6][0] = "Уч-ок";
	surch_sg->Cells[7][0] = "Операция";

	surch_sg->Cells[8][0] = "Таб №";
	surch_sg->Cells[9][0] = "РР";
	surch_sg->Cells[10][0] = "ВН";
	surch_sg->Cells[11][0] = "КТС";

	surch_sg->Cells[12][0] = "кол";
	surch_sg->Cells[13][0] = "Тпз.";
	surch_sg->Cells[14][0] = "Тшт.";
	surch_sg->Cells[15][0] = "Тфакт.";
	AutoWidthSG(surch_sg);
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
    SGClear(zapSG,2);
    zakTV->Items->Clear();
    contentTV->Items->Clear();

    String zap_sql = "select a.name, a.begin, a.end, a.zap_id, (a.in_work is not null) started from manufacture.manufacture_orders a "
                     " join manufacture.parts b on a.zap_id = b.zap_id ";
    if (zakaz.Length() || det.Length())
    {
        if (zakaz.Length())
        {
            zap_sql +=  " join manufacture.zakaz_list e on b.zak_id = e.zak_id ";
        }

        if (det.Length())
        {
            zap_sql +=  " join manufacture.part_content c on b.part_id = c.part_id "
                        " join manufacture.det_names d on d.det_id = c.det_id ";
        }
	}

    String where = "where 1 ";
    if (!Show_Closed->Checked)
		where += " and b.close_date is null ";
    else
        where += " and b.close_date is not null ";

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
            zapSG->Cells[ZAP_IN_WORK_COL][row] = rez->FieldByName("started")->Value;
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

    String zap_sql = "select a.zap_id, a.zak_id, a.part_no, a.part_id, b.zakaz, (a.in_work is not null) started  from manufacture.parts a "
                     " join manufacture.zakaz_list b on a.zak_id = b.zak_id ";
    if (zap_id.Length())
    {
        zap_sql +=     " join manufacture.manufacture_orders c on a.zap_id = c.zap_id ";
    }
    if (det.Length())
    {
        zap_sql +=  " join manufacture.part_content d on a.part_id = d.part_id "
                    " join manufacture.det_names e on e.det_id = d.det_id ";
    }

    String where = "where 1 ";
    if (!Show_Closed->Checked)
        where += " and a.close_date is null ";
    else
        where += " and a.close_date is not null ";
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
        int started_count(0);
        int summary_count(0);
        for (rez->First(); !rez->Eof; rez->Next())
        {
            TTreeNode *ch_node = 0;
            ++summary_count;

            String zak = rez->FieldByName("zakaz")->Value;
            unsigned int part_no = rez->FieldByName("part_no")->Value;
            unsigned __int64 zak_id = (unsigned __int64)rez->FieldByName("zak_id")->Value.operator __int64();
            unsigned __int64 zap_id = (unsigned __int64)rez->FieldByName("zap_id")->Value.operator __int64();
            unsigned __int64 part_id = (unsigned __int64)rez->FieldByName("part_id")->Value.operator __int64();
            bool started = (int)rez->FieldByName("started")->Value;

            if (zak != prev_zakaz)
            {

                if (node)
                {
                    if (started_count > 0)
                    {
                        ((NodeData *)node->Data)->SetLock();
                        if (started_count == summary_count -1)
                        {
                            node->ImageIndex = 1;
                        }
                        else
                        {
                            node->ImageIndex = 2;
                        }
                    }
                    else
                    {
                        ((NodeData *)node->Data)->SetLock(false);
                        node->ImageIndex = 0;
                    }

                    node->SelectedIndex=node->ImageIndex;
                    node->ExpandedImageIndex=node->ImageIndex;
                    summary_count = 1;
                    started_count = 0;
                }

                ZakazNode *ptr = new ZakazNode(zak_id, zap_id, zak);
                node = zakTV->Items->AddObject(node, ptr->getZakaz(), (void *)ptr);
                prev_zakaz = zak;
            }
            PartNode *ptr = new PartNode(part_id, part_no);
            ptr->SetLock(started);
            ch_node = zakTV->Items->AddChildObject(node, ptr->getPartNo(), (void*)ptr);

            if (started)
            {
                ++started_count;
                ch_node->ImageIndex = 1;
            }
            else
            {
                ch_node->ImageIndex = 0;
            }

            ch_node->SelectedIndex = ch_node->ImageIndex;
            ch_node->ExpandedImageIndex = ch_node->ImageIndex;
        }
        if (node)
        {
            if (started_count > 0)
            {
                ((NodeData *)node->Data)->SetLock();
                if (started_count == summary_count)
                {
                    node->ImageIndex = 1;
                }
                else
                {
                    node->ImageIndex = 2;
                }
            }
            else
            {
                ((NodeData *)node->Data)->SetLock(false);
                node->ImageIndex = 0;
            }

            node->SelectedIndex=node->ImageIndex;
            node->ExpandedImageIndex=node->ImageIndex;
        }
    }
    delete rez;
}
void TManufactureControl::LoadIzd   (String zap_id, unsigned __int64 zak_id, unsigned __int64 part_id, String det)
{
    contentTV->Items->Clear();

    String zap_sql = "select b.obd, b.name, a.det_id, a.kol, count(b1.det_idp) have_childs, b.sp_id, "
                     " b.sp_name, (a.in_work is not null) started  "
                     " from manufacture.part_content a "
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
            bool started = (int)rez->FieldByName("started")->Value;
            IzdNode *ptr = new IzdNode(name, obd, det_id, kol, sp_id, sp_name);
            ptr->SetLock(started);
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

void TManufactureControl::LoadDetailData    (String zap_id, unsigned __int64 zak_id, unsigned __int64 part_id, unsigned __int64 det_id, unsigned __int64 inst_id)
{
    if (Content_detail->ActivePage == Parts)
    {
        LoadDetailParts(zap_id, zak_id, part_id, det_id, inst_id);
    }
    else if (Content_detail->ActivePage == StandartParts)
    {
        LoadDetailStandartParts(zap_id, zak_id, part_id, det_id, inst_id);
    }
    else if (Content_detail->ActivePage == Materials)
	{
        LoadDetailMaterials(zap_id, zak_id, part_id, det_id, inst_id);
    }
    else if (Content_detail->ActivePage == Oborud)
    {
        LoadDetailOborud(zap_id, zak_id, part_id, det_id, inst_id);
    }
    else if (Content_detail->ActivePage == Surcharge)
    {
        LoadDetailSurCharge(zap_id, zak_id, part_id, det_id, inst_id);
    }
}
void TManufactureControl::LoadDetailParts   (String zap_id, unsigned __int64 zak_id, unsigned __int64 part_id, unsigned __int64 det_id, unsigned __int64 inst_id)
{
    SGClear(detSG, 6);
    SGClear(detDetails, 1);
    SGClear(operSG);
    SGClear(det_oborudSG);
    SGClear(det_matSG);
    SGClear(makeSG);

    //получить список инстов
    std::stringstream get_ids;
    get_ids << "Call manufacture.GetContent("<<zap_id.ToIntDef(0)<<","<<zak_id<<","<<part_id<<","<<det_id<<","<<inst_id<<")";
    //отрезать от инстов не используемые
    //отрезать все детали не из разделов 0,2,3,4,8
    std::string step_1_drop =   "drop temporary table if exists manufacture.step_1";
    std::string step_1_init =   "create temporary table if not exists manufacture.step_1 as "
                                "select a.det_id as det_id, sum(b.kol_using) as det_kol from manufacture.output a "
                                "left join manufacture.det_tree b on a.inst_id = b.inst_idc "
                                "join manufacture.det_names c on c.det_id = a.det_id "
                                "where b.inst_idc is null or b.using != 0 and c.sp_id in (0,2,3,4,8) "
                                "group by a.det_id ";
    //получить количества деталей
    std::string step_2 = "update manufacture.step_1 a join manufacture.part_content b on a.det_id = b.det_id set a.det_kol = IFNULL(a.det_kol,0)+IFNULL(b.kol,0)";

    //посчитать трудоемкости по списку
    std::string step_3 = " select "
                         " a.det_id as det_id, "
                         " round(sum(c.tsht*c.ksht*c.krop/c.kolod),3) as trud_ed, "
                         " round(sum(c.tsht*c.ksht*c.krop/c.kolod)*a.det_kol,3) as trud, "
                         " a.det_kol as kol, d.obd, d.name, d.id id,0 maked, 0 broken "
                         " from manufacture.step_1 a "
                         " join manufacture.operation_list b on b.det_id = a.det_id "
                         " join manufacture.operation_norms c on c.OpUUID = b.OpUUID "
                         " join manufacture.det_names d on d.det_id = a.det_id "
                         " group by d.id order by d.sp_id, d.obd";
    DB->SendCommand(get_ids.str().c_str());
    DB->SendCommand(step_1_drop.c_str());
    DB->SendCommand(step_1_init.c_str());
    DB->SendCommand(step_2.c_str());
    TADOQuery *rez = DB->SendSQL(step_3.c_str());
    DB->SendCommand(step_1_drop.c_str());

    String out_zap_id   (zap_id);
    String out_zak_id   (zak_id);
    String out_part_id  (part_id);
    String out_det_id   (det_id);
    String out_inst_id  (inst_id);
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

            //ID FIELDS
            detSG->Cells[8][row] = rez->FieldByName("id")->Value;
            detSG->Cells[9][row] = out_zap_id;
            detSG->Cells[10][row] = out_zak_id;
            detSG->Cells[11][row] = out_part_id;
            detSG->Cells[12][row] = out_det_id;
            detSG->Cells[13][row] = out_inst_id;
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

void TManufactureControl::LoadPartDetails   (String id, String zap_id, String zak_id, String part_id, String det_id, String inst_id)
{
    SGClear(detDetails, 1);

    //получить список инстов
    std::stringstream get_ids;
    get_ids << "Call manufacture.GetContent("<<zap_id.ToIntDef(0)<<","<<zak_id.ToIntDef(0)<<","<<part_id.ToIntDef(0)<<","<<det_id.ToIntDef(0)<<","<<inst_id.ToIntDef(0)<<")";
    //отрезать от инстов не используемые
    //отрезать все детали не из разделов 0,2,3,4,8
    std::string step_1_drop =   "drop temporary table if exists manufacture.step_1";
    std::string step_1_init =   "create temporary table if not exists manufacture.step_1 as "
                                "select a.det_id as det_id, sum(b.kol_using) as det_kol, b.det_idp,b.inst_idc from manufacture.output a "
                                "left join manufacture.det_tree b on a.inst_id = b.inst_idc "
                                "join manufacture.det_names c on c.det_id = a.det_id "
                                "where b.inst_idc is null or b.using != 0 and c.sp_id in (0,2,3,4,8) "
                                "group by a.det_id,b.inst_idc ";
    //получить количества деталей
    std::string step_2 = "update manufacture.step_1 a join manufacture.part_content b on a.det_id = b.det_id set a.det_kol = IFNULL(a.det_kol,0)+IFNULL(b.kol,0)";

    //посчитать трудоемкости по списку
    std::stringstream step_3;
    step_3 <<   " select "
                " a.det_id as det_id, "
                " round(sum(c.tsht*c.ksht*c.krop/c.kolod),3) as trud_ed, "
                " round(sum(c.tsht*c.ksht*c.krop/c.kolod)*a.det_kol,3) as trud, "
                " a.det_kol as kol, d.obd,convert(IFNULL(e.obd,''),CHAR) as parent_obd, d.name, d.id id,0 maked, 0 broken "
                " from manufacture.step_1 a "
                " join manufacture.operation_list b on b.det_id = a.det_id "
                " join manufacture.operation_norms c on c.OpUUID = b.OpUUID "
                " join manufacture.det_names d on d.det_id = a.det_id "
                " left join manufacture.det_names e on e.det_id = a.det_idp"
                " where d.id = '"<<id.ToIntDef(0)<<"' "
                " group by a.det_id,a.inst_idc order by d.sp_id, d.obd";
    DB->SendCommand(get_ids.str().c_str());
    DB->SendCommand(step_1_drop.c_str());
    DB->SendCommand(step_1_init.c_str());
    DB->SendCommand(step_2.c_str());
    TADOQuery *rez = DB->SendSQL(step_3.str().c_str());
    DB->SendCommand(step_1_drop.c_str());
    //вывести результат
    if (rez)
    {
        for (rez->First(); !rez->Eof; rez->Next())
        {
            int row = detDetails->RowCount-1;
            detDetails->Cells[1][row] = VinToGost(rez->FieldByName("parent_obd")->Value);
            detDetails->Cells[2][row] = VinToGost(rez->FieldByName("obd")->Value);
            detDetails->Cells[3][row] = rez->FieldByName("name")->Value;
            detDetails->Cells[4][row] = rez->FieldByName("kol")->Value;
            detDetails->Cells[5][row] = rez->FieldByName("trud_ed")->Value;
            detDetails->Cells[6][row] = rez->FieldByName("trud")->Value;
            detDetails->Cells[7][row] = rez->FieldByName("maked")->Value;
            detDetails->Cells[8][row] = rez->FieldByName("broken")->Value;

            //ID FIELDS
            detDetails->Cells[9][row] = rez->FieldByName("det_id")->Value;

            ++detDetails->RowCount;
        }
        delete rez;
        if (detDetails->RowCount>2)
        {
            --detDetails->RowCount;
        }
        AutoWidthSG(detDetails);
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
    LoadPartDetails(detSG->Cells[8][ARow],detSG->Cells[9][ARow],detSG->Cells[10][ARow],detSG->Cells[11][ARow],detSG->Cells[12][ARow],detSG->Cells[13][ARow]);

}
void __fastcall TManufactureControl::detDetailsSelectCell(TObject *Sender, int ACol,
          int ARow, bool &CanSelect)
{
    if (detDetails->Cells[9][ARow] == "")
    {
        return;
    }
    if (DetDetailControl->ActivePage == OperationsSheet)
        LoadTechDetails(detDetails->Cells[9][ARow]);
    if (DetDetailControl->ActivePage == ObourSheet)
        LoadOborudDetails(detDetails->Cells[9][ARow]);
}
void __fastcall TManufactureControl::DetDetailControlChange(TObject *Sender)
{
    bool t;
    detDetailsSelectCell(0, detDetails->Col, detDetails->Row, t);
}


void TManufactureControl::LoadDetailStandartParts(String zap_id, unsigned __int64 zak_id, unsigned __int64 part_id, unsigned __int64 det_id, unsigned __int64 inst_id)
{
    return;
}
void TManufactureControl::LoadDetailMaterials    (String zap_id, unsigned __int64 zak_id, unsigned __int64 part_id, unsigned __int64 det_id, unsigned __int64 inst_id)
{
    return;
}
void TManufactureControl::LoadDetailOborud       (String zap_id, unsigned __int64 zak_id, unsigned __int64 part_id, unsigned __int64 det_id, unsigned __int64 inst_id)
{
    SGClear(OborudSG);

    //получить список инстов
    std::stringstream get_ids;
    get_ids << "Call manufacture.GetContent("<<zap_id.ToIntDef(0)<<","<<zak_id<<","<<part_id<<","<<det_id<<","<<inst_id<<")";
    //отрезать от инстов не используемые
    //отрезать все детали не из разделов 0,2,3,4,8
    std::string step_1_drop =   "drop temporary table if exists manufacture.step_1";
    std::string step_1_init =   "create temporary table if not exists manufacture.step_1 as "
                                "select a.det_id as det_id, sum(b.kol_using) as det_kol from manufacture.output a "
                                "left join manufacture.det_tree b on a.inst_id = b.inst_idc "
                                "join manufacture.det_names c on c.det_id = a.det_id "
                                "where b.inst_idc is null or b.using != 0 and c.sp_id in (0,2,3,4,8) "
                                "group by a.det_id ";
    //получить количества деталей
    std::string step_2 = "update manufacture.step_1 a join manufacture.part_content b on a.det_id = b.det_id set a.det_kol = IFNULL(a.det_kol,0)+IFNULL(b.kol,0)";

    //посчитать трудоемкости по списку
    std::string step_3 = " select "
                         " b.cex, b.utch, b.oboID, d.name obo_name,"
                         " round(sum(c.tsht*c.ksht*c.krop/c.kolod)*a.det_kol,3) as trud, "
                         " sum(IFNULL(kol_request-kol_unmaked,0)) maked, sum(IFNULL(kol_request,0)) schedule "
                         " from manufacture.step_1 a "
                         " join manufacture.operation_list b on b.det_id = a.det_id "
                         " join manufacture.operation_norms c on c.OpUUID = b.OpUUID "
                         " left join equipment.obor_list d on d.oboID = b.oboID "
                         " left join manufacture.orders e on e.operation_id = b.OpUUID "
                         " group by b.cex, b.utch, b.oboID";
    DB->SendCommand(get_ids.str().c_str());
    DB->SendCommand(step_1_drop.c_str());
    DB->SendCommand(step_1_init.c_str());
    DB->SendCommand(step_2.c_str());
    TADOQuery *rez = DB->SendSQL(step_3.c_str());
    DB->SendCommand(step_1_drop.c_str());

    //вывести результат
    if (rez)
    {
        for (rez->First(); !rez->Eof; rez->Next())
        {
            int row = OborudSG->RowCount - 1;
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
            OborudSG->Cells[1][row] = rez->FieldByName("trud")->Value;
            OborudSG->Cells[2][row] = podr;
            OborudSG->Cells[3][row] = rez->FieldByName("OboID")->Value;
            OborudSG->Cells[4][row] = rez->FieldByName("obo_name")->Value;
            OborudSG->Cells[5][row] = rez->FieldByName("schedule")->Value;
            OborudSG->Cells[6][row] = rez->FieldByName("maked")->Value;

            ++OborudSG->RowCount;
        }
        if (OborudSG->RowCount > 2)
        {
            --OborudSG->RowCount;
        }
        delete rez;
    }
    AutoWidthSG(OborudSG);
    return;
}
void TManufactureControl::LoadDetailSurCharge    (String zap_id, unsigned __int64 zak_id, unsigned __int64 part_id, unsigned __int64 det_id, unsigned __int64 inst_id)
{
    SGClear(surch_sg, 8);

    //входные параметры нужно свести к набору part_id + obd

    std::string step_1_drop = "Drop temporary table if exists step_1";
    std::string step_1 = "Create temporary table if not exists step_1 "
                         "("
                         "part_id bigint(20) unsigned not null,"
                         "key part_id(`part_id`)"
                         ")engine = MEMORY";
    DB->SendCommand(step_1_drop.c_str());
    DB->SendCommand(step_1.c_str());

    std::stringstream where;
    std::stringstream joins;
    std::string obd("");
    if (zap_id != "")
    {
        where << " and a.zap_id = '"<<zap_id.ToIntDef(0)<<"' ";
    }
    if (zak_id > 0)
    {
        where << " and a.zak_id = '"<<zak_id<<"' ";
    }
    if (part_id > 0)
    {
        where << " and a.part_id = '"<<part_id<<"' ";
    }
    if (det_id > 0)
    {
        joins << " join `manufacture`.`part_content` b on `a`.`part_id` = `b`.`part_id` ";
        where << " and b.det_id = '"<<det_id<<"' ";

        std::stringstream sql;
        sql << "select a.obd from manufacture.det_names a where a.det_id = '"<<det_id<<"'";
        TADOQuery *rez = DB->SendSQL(sql.str().c_str());
        if (rez)
        {
            if (rez->RecordCount)
            {
                obd = rez->FieldByName("obd")->Value.operator AnsiString().Trim().c_str();
            }
            delete rez;
        }
    }

    if (!where.str().empty())
    {
        std::stringstream step_1_fill;
        step_1_fill << "insert into step_1 (part_id) "
                       "select `a`.`part_id` "
                       "from `manufacture`.`parts` a "
                       <<joins.str()<<
                       "where true "<< where.str();
        DB->SendCommand(step_1_fill.str().c_str());
    }
    where.str("");

    /*
    добавить обработку inst_id для этого нужно получить обозначение детали и проследить до партии по древу спецификации
    */

    std::stringstream sql;
    sql << "select "
           "CONVERT(`a`.`record_id`, CHAR) record_id,"
           "CONVERT(`c1`.`order_id`, CHAR) order_id,"//cells

           "CONVERT(`a`.`zak_id`, CHAR) zak_id,     "
           "CONVERT(`b`.`zakaz`, CHAR) zakaz,       "//cells

           "CONVERT(`a`.`part_id`, CHAR) part_id,   "
           "CONVERT(`c`.`part_no`, CHAR) part_no,   "//cells

           "CONVERT(`a`.`opr_id`, CHAR) opr_id, "//cells
           "CONVERT(`d`.`name`, CHAR) opr_name,     "//cells

           "CONVERT(`a`.`cex`, CHAR) cex,       "//cells
           "CONVERT(`a`.`utch`, CHAR) utch,     "//cells

           "CONVERT(`a`.`tab_no`, CHAR) tab_no, "//cells
           "CONVERT(IFNULL(concat(e.family, ' ',Upper(left(e.name,1)),'.', Upper(left(e.otch,1)),'.'),''), CHAR) as fio, "

           "CONVERT(`a`.`obd`, CHAR) obd,       "//cells
           "CONVERT(`a`.`kts`, CHAR) kts,       "//cells
           "CONVERT(`a`.`rr`, CHAR) rr,         "//cells
           "CONVERT(`c1`.`kol_request`, CHAR) kol,       "//cells
           "CONVERT(`a`.`tpz`, CHAR) tpz,       "//cells
           "CONVERT(`a`.`tsht`, CHAR) tsht,     "//cells
           "CONVERT(`a`.`kvn`, CHAR) kvn,       "//cells
           "CONVERT(`a`.`reason`, CHAR) reason, "
           "CONVERT(`a`.`tfact`, CHAR) tfact,   "//cells
           "CONVERT(`a`.`descr`, CHAR)  descr   "
           "from manufacture.surcharge a "
           "join step_1 a1 on a.part_id = a1.part_id "
           "join manufacture.zakaz_list b on a.zak_id = b.zak_id "
           "join manufacture.parts c on a.part_id = c.part_id "
           "join manufacture.orders c1 on c1.surcharge_id = a.record_id "
           "left join equipment.opr_names d on a.opr_id = d.OprID "
           "left join manufacture.workers e on a.tab_no = e.tab_no and e.date_from < c1.creation_date and (c1.creation_date < e.date_to or e.date_to = '0000-00-00') ";
    if (!obd.empty())
    {
        sql << " where a.obd = '"<<obd<<"'";
    }


    TADOQuery *rez = DB->SendSQL(sql.str().c_str());
    DB->SendCommand(step_1_drop.c_str());

    /*
    часть данных спрятать в сетке и при клике на ячейку отображать
    */
    //вывести результат
    if (rez)
    {
        for (rez->First(); !rez->Eof; rez->Next())
        {
            int row = surch_sg->RowCount - 1;

            surch_sg->Cells[1][row] = rez->FieldByName("order_id")->Value;

            surch_sg->Cells[2][row] = rez->FieldByName("zakaz")->Value;
            surch_sg->Cells[3][row] = rez->FieldByName("part_no")->Value;
            surch_sg->Cells[4][row] = VinToGost(rez->FieldByName("obd")->Value);

            surch_sg->Cells[5][row] = rez->FieldByName("cex")->Value;
            surch_sg->Cells[6][row] = rez->FieldByName("utch")->Value;
            surch_sg->Cells[7][row] = rez->FieldByName("opr_id")->Value.operator UnicodeString() + rez->FieldByName("opr_name")->Value.operator UnicodeString();

            surch_sg->Cells[8][row] = rez->FieldByName("tab_no")->Value;
            surch_sg->Cells[9][row] = rez->FieldByName("rr")->Value;
            surch_sg->Cells[10][row] = rez->FieldByName("kvn")->Value;
            surch_sg->Cells[11][row] = rez->FieldByName("kts")->Value;

            surch_sg->Cells[12][row] = rez->FieldByName("kol")->Value;
            surch_sg->Cells[13][row] = rez->FieldByName("tpz")->Value;
            surch_sg->Cells[14][row] = rez->FieldByName("tsht")->Value;
            surch_sg->Cells[15][row] = rez->FieldByName("tfact")->Value;

            //доп поля
            surch_sg->Cells[16][row] = rez->FieldByName("record_id")->Value;
            surch_sg->Cells[17][row] = rez->FieldByName("zak_id")->Value;
            surch_sg->Cells[18][row] = rez->FieldByName("part_id")->Value;
            surch_sg->Cells[19][row] = rez->FieldByName("reason")->Value;
            surch_sg->Cells[20][row] = rez->FieldByName("descr")->Value;
            surch_sg->Cells[21][row] = rez->FieldByName("fio")->Value;

            surch_sg->Cells[22][row] = rez->FieldByName("opr_id")->Value;
            surch_sg->Cells[23][row] = rez->FieldByName("opr_name")->Value;


            ++surch_sg->RowCount;
        }
        if (surch_sg->RowCount > 2)
        {
            --surch_sg->RowCount;
        }
        delete rez;
    }
    AutoWidthSG(surch_sg);

    bool s;
    surch_sgSelectCell(0, surch_sg->Col, surch_sg->Row, s);
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
		//получить список партий для запуска
        std::vector<unsigned __int64> parts;
        TADOQuery *rez = DB->SendSQL("Select part_id from manufacture.manufacture_orders a "
                                     " join manufacture.parts b on a.zap_id = b.zap_id "
                                     " where a.zap_id ='"+zapSG->Cells[ZAP_ID_COL][zapSG->Row]+"'");
        if (rez)
		{
            for (rez->First(); !rez->Eof; rez->Next())
			{
				parts.push_back((unsigned __int64)((__int64)rez->FieldByName("part_id")->Value));
            }
            delete rez;
        }

        StartOrder(parts);
        UpdateOrderStatus();
    }
    return;
}
void __fastcall TManufactureControl::ToEditZapusk(TObject *Sender)
{
    if ( MessageBoxA(this->Handle, "Вернуть в разработку?", "Вернуть в разработку?",MB_YESNO|MB_ICONQUESTION) == mrYes )
    {
        //получить список партий для запуска
        std::vector<unsigned __int64> parts;
        TADOQuery *rez = DB->SendSQL("Select part_id from manufacture.manufacture_orders a "
                                     " join manufacture.parts b on a.zap_id = b.zap_id "
                                     " where a.zap_id ='"+zapSG->Cells[ZAP_ID_COL][zapSG->Row]+"'");
        if (rez)
        {
            for (rez->First(); !rez->Eof; rez->Next())
            {
                parts.push_back((unsigned __int64)((__int64)rez->FieldByName("part_id")->Value));
            }
            delete rez;
        }

        StopOrder(parts);
        UpdateOrderStatus();
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
    LoadDetailData(zapSG->Cells[ZAP_ID_COL][ARow], 0, 0, 0,0);

    N2->Enabled = !zapSG->Cells[ZAP_IN_WORK_COL][ARow].ToIntDef(0);
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
            LoadZakaz(zapSG->Cells[ZAP_ID_COL][zapSG->Row], "", "");
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
        DB->SendCommand("START TRANSACTION");
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
        if (zapSG->Cells[ZAP_ID_COL][zapSG->Row] != "")
        {
            LoadZakaz(zapSG->Cells[ZAP_ID_COL][zapSG->Row], "", "");
        }
    }
    return;
}
void __fastcall TManufactureControl::InWorkZakaz(TObject *Sender)
{
    if ( MessageBoxA(this->Handle, "Запустить в работу?", "Запустить в работу?",MB_YESNO|MB_ICONQUESTION) == mrYes )
    {
        std::vector<unsigned __int64> parts;
        for (size_t i = 0; i < zakTV->SelectionCount; ++i)
        {
            TTreeNode *node = zakTV->Selections[i];
            if (node->Level == 0)
            {//запустить заказ
                for (TTreeNode *ch_node = node->getFirstChild(); ch_node; ch_node = node->GetNextChild(ch_node))
                {
                    PartNode *ptr = (PartNode *)ch_node->Data;
                    parts.push_back(ptr->getPartID());
                }
            }
            else
            {//запустить партию
                PartNode *ptr = (PartNode *)node->Data;
                parts.push_back(ptr->getPartID());
            }
        }
        StartOrder(parts);
        UpdateOrderStatus();
    }
    return;
}
void __fastcall TManufactureControl::ToEditZakaz(TObject *Sender)
{
    if ( MessageBoxA(this->Handle, "Вернуть в разработку?", "Вернуть в разработку?",MB_YESNO|MB_ICONQUESTION) == mrYes )
    {
        std::vector<unsigned __int64> parts;
        for (size_t i = 0; i < zakTV->SelectionCount; ++i)
        {
            TTreeNode *node = zakTV->Selections[i];
            if (node->Level == 0)
            {//запустить заказ
                for (TTreeNode *ch_node = node->getFirstChild(); ch_node; ch_node = node->GetNextChild(ch_node))
                {
                    PartNode *ptr = (PartNode *)ch_node->Data;
                    parts.push_back(ptr->getPartID());
                }
            }
            else
            {//запустить партию
                PartNode *ptr = (PartNode *)node->Data;
                parts.push_back(ptr->getPartID());
            }
        }
        StopOrder(parts);
        UpdateOrderStatus();
    }
    return;
}
void __fastcall TManufactureControl::N10Click(TObject *Sender)
{
    //закрыть заказ
    if ( MessageBoxA(this->Handle, "Закрыть заказ?", "Закрыть заказ?",MB_YESNO|MB_ICONQUESTION) == mrYes )
    {
        std::vector<unsigned __int64> parts;
        for (size_t i = 0; i < zakTV->SelectionCount; ++i)
        {
            TTreeNode *node = zakTV->Selections[i];
            if (node->Level == 0)
            {//запустить заказ
                for (TTreeNode *ch_node = node->getFirstChild(); ch_node; ch_node = node->GetNextChild(ch_node))
                {
                    PartNode *ptr = (PartNode *)ch_node->Data;
                    parts.push_back(ptr->getPartID());
                }
            }
            else
            {//запустить партию
                PartNode *ptr = (PartNode *)node->Data;
                parts.push_back(ptr->getPartID());
            }
        }
        CloseOrder(parts);
        Find->Click();
    }
}
void __fastcall TManufactureControl::zakTVMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
    TTreeNode *node = zakTV->GetNodeAt(X, Y);;
    if (node )
    {
        if (Button == TMouseButton::mbLeft)
        {
            if (!node->Level)
            {
                ZakazNode *ptr = (ZakazNode *)node->Data;
                LoadIzd(String(ptr->getZapID()), ptr->getZakID(), 0, "");
                LoadDetailData(String(ptr->getZapID()), ptr->getZakID(), 0, 0,0);
            }
            else
            {
                PartNode *ptr = (PartNode *)node->Data;
                LoadIzd("", 0, ptr->getPartID(), "");
                LoadDetailData("", 0, ptr->getPartID(), 0,0);
            }
        }
        else if (Button == TMouseButton::mbRight)
        {
            NodeData *ptr = (NodeData *)node->Data;
            if (ptr)
            {
                 MenuItem2->Enabled = !ptr->Locked();
                 MenuItem3->Enabled = !ptr->Locked();
            }
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
    if (ptr && node->Level && ((IzdPartNode *)node->Parent->Parent->Data)->IsUsed())
    {
        DB->SendCommand("call manufacture.SetUsage ('"+String(ptr->getInstIDc())+"', '1')");
        Update(node);
    }

    return;
}
void __fastcall TManufactureControl::UnIncludePath(TObject *Sender)
{
    TTreeNode *node = contentTV->Selected;
    IzdPartNode *ptr = (IzdPartNode *)node->Data;
    DB->SendCommand("call manufacture.SetUsage ('"+String(ptr->getInstIDc())+"', '0')");
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

    Node->DeleteChildren();
    String sql = " select "
                 " a.det_idp, "
                 " a.inst_idc, "
                 " IFNULL(a.inst_idp,0) inst_idp, "
                 " a.using, "
                 " b.det_id, "
                 " b.obd, "
                 " b.name, "
                 " a.kol_sp, "
                 " a.kol_using,"
                 " count(b1.inst_idp) have_childs, "
                 " b.sp_id, b.sp_name "
                 " from manufacture.det_tree a "
                 " left join manufacture.det_tree b1 on a.inst_idc = b1.inst_idp "
                 " join manufacture.det_names b on a.det_idc = b.det_id ";
    if (Node->Level)
    {
        IzdPartNode *ptr = (IzdPartNode *)Node->Data;
        sql += " where a.inst_idp = '"+String(ptr->getInstIDc())+"' ";
    }
    else
    {
        IzdNode *ptr = (IzdNode *)Node->Data;
        sql += " where a.det_idp = '"+String(ptr->getDetID())+"' ";
    }
    sql += " group by a.inst_idc "
           " order by b.sp_id, b.obd";

	TADOQuery *rez = DB->SendSQL(sql);
    if (rez && rez->RecordCount)
	{
		NodeData *ptr = (NodeData *)Node->Data;
        TTreeNode *node = 0;
        TTreeNode *sp_node = 0;
        unsigned int prev_sp_id = -1;
        for (rez->First(); !rez->Eof; rez->Next())
        {
            String obd = rez->FieldByName("obd")->Value;
            String name = rez->FieldByName("name")->Value;
            unsigned __int64 det_id = (unsigned __int64)rez->FieldByName("det_id")->Value.operator __int64();
            unsigned __int64 det_idp = (unsigned __int64)rez->FieldByName("det_idp")->Value.operator __int64();
            unsigned __int64 inst_idc = (unsigned __int64)rez->FieldByName("inst_idc")->Value.operator __int64();
            unsigned __int64 inst_idp = (unsigned __int64)rez->FieldByName("inst_idp")->Value.operator __int64();
            unsigned int kol_using = (unsigned int)rez->FieldByName("kol_using")->Value.operator int();
            unsigned int kol_sp = (unsigned int)rez->FieldByName("kol_sp")->Value.operator int();
            bool have_childs = int(rez->FieldByName("have_childs")->Value);
            unsigned int sp_id = (unsigned int)rez->FieldByName("sp_id")->Value.operator int();
            String sp_name = rez->FieldByName("sp_name")->Value;
            bool using_ = rez->FieldByName("using")->Value;
            IzdPartNode *ch_ptr = new IzdPartNode(name, obd, det_id, kol_using, det_idp, inst_idc, inst_idp, kol_sp, sp_id, sp_name, using_);
            ch_ptr->SetLock(ptr->Locked());
            if (prev_sp_id != sp_id)
            {
                sp_node = contentTV->Items->AddChildObject(Node, sp_name, 0);
                sp_node->ImageIndex = IcoData->GetInList(sp_id,true,1);
                sp_node->SelectedIndex = sp_node->ImageIndex;
                sp_node->ExpandedImageIndex = sp_node->ImageIndex;
                prev_sp_id = sp_id;
                Set_img(sp_node);
            }
            node= contentTV->Items->AddChildObject(sp_node, VinToGost(ch_ptr->getDetObd())+" "+ch_ptr->getDetName(), (void*)ch_ptr);
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
            if (Button == TMouseButton::mbLeft)
            {
                if (node->Data)
                {
                    if (node->Level)
                    {
                        IzdPartNode *ptr = (IzdPartNode *)node->Data;
                        LoadDetailData("",0,0,0,ptr->getInstIDc());
                    }
                    else
                    {
                        LoadDetailData("",0,0,ptr->getDetID(),0);
                    }
                }
            }

            MenuItem5->Enabled = !ptr->Locked();
            MenuItem11->Enabled = !ptr->Locked();
            MenuItem12->Enabled = !ptr->Locked();
        }
    }
    return;
}
void TManufactureControl::Update       (TTreeNode *node)
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
void TManufactureControl::UpdateOrderStatus (void)
{
	if (zapSG->Cells[ZAP_ID_COL][zapSG->Row] == "")
        return;
    TADOQuery *rez = DB->SendSQL("select (a.in_work is not null) started "
                                 " from manufacture.manufacture_orders a "
                                 " where a.zap_id = '"+zapSG->Cells[ZAP_ID_COL][zapSG->Row]+"'");
    if (rez)
    {
		zapSG->Cells[ZAP_IN_WORK_COL][zapSG->Row] = rez->FieldByName("started")->Value;
		delete rez;
    }
    zapSG->Repaint();
    UpdatePartsStatus();
}
void TManufactureControl::UpdatePartsStatus (void)
{
    if (zapSG->Cells[ZAP_ID_COL][zapSG->Row] == "")
        return;

    LoadZakaz(zapSG->Cells[ZAP_ID_COL][zapSG->Row], "", "");
    LoadIzd(zapSG->Cells[ZAP_ID_COL][zapSG->Row], 0, 0, "");
}

void TManufactureControl::StartOrder(const std::vector<unsigned __int64> &parts)
{
    Transaction tr(DB);
	for (std::vector<unsigned __int64>::const_iterator it = parts.begin(); it!=parts.end(); ++it)
    {
		DB->SendCommand("call manufacture.zapusk_starter('"+String(*it)+"')");
	}
	tr.Commit();
}
void TManufactureControl::StopOrder(const std::vector<unsigned __int64> &parts)
{
	Transaction tr(DB);
	for (std::vector<unsigned __int64>::const_iterator it = parts.begin(); it!=parts.end(); ++it)
	{
        DB->SendCommand("call manufacture.zapusk_stopper('"+String(*it)+"')");
    }
    tr.Commit();
}
void TManufactureControl::CloseOrder(const std::vector<unsigned __int64> &parts)
{
    Transaction tr(DB);
    for (std::vector<unsigned __int64>::const_iterator it = parts.begin(); it!=parts.end(); ++it)
    {
        DB->SendCommand("call manufacture.Close_part('"+String(*it)+"')");
    }
    tr.Commit();
}

void __fastcall TManufactureControl::zapSGDrawCell(TObject *Sender, int ACol, int ARow,
		  TRect &Rect, TGridDrawState State)
{
	TStringGrid *sg = dynamic_cast<TStringGrid *>(Sender);
	if (!sg)
	{
    	return;
	}
	TColor cur_color = sg->Canvas->Brush->Color;

	if (ACol == 0 && ARow !=0)
	{
		int caser = zapSG->Cells[ZAP_IN_WORK_COL][ARow].ToIntDef(0);
		TColor color = clRed;
		switch (caser)
		{
			case 0: {color = clRed; break;}
			case 1: {color = clGreen; break;}
		default: color = clRed;
		}

		sg->Canvas->Brush->Color = color;
		sg->Canvas->FillRect(Rect);
	}


    sg->Canvas->Brush->Color = cur_color;
}
//---------------------------------------------------------------------------

void __fastcall TManufactureControl::N5Click(TObject *Sender)
{
	int zap_id = zapSG->Cells[ZAP_ID_COL][zapSG->Row].ToIntDef(0);
	if (zap_id)
	{
		TReports *wnd = new TReports(this,DB,STARTUP,zap_id);
		wnd->ShowModal();
		delete wnd;
	}
}
void __fastcall TManufactureControl::MenuItem8Click(TObject *Sender)
{
	TTreeNode *node = zakTV->Selected;
	if (node && node->Data)
	{
		if (node->Level == 0)
		{//запустить заказ
			ZakazNode *ptr = (ZakazNode *)node->Data;

			TReports *wnd = new TReports(this,DB,ORDER,ptr->getZapID(),ptr->getZakID());
			wnd->ShowModal();
			delete wnd;
		}
		else
		{//запустить партию
			PartNode *ptr = (PartNode *)node->Data;

			TReports *wnd = new TReports(this,DB,PART,ptr->getPartID());
			wnd->ShowModal();
			delete wnd;
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TManufactureControl::N7Click(TObject *Sender)
{
	TTreeNode *node = contentTV->Selected;
	if (node&& node->Data)
	{
		IzdNode *ptr = (IzdNode *)node->Data;

		TReports *wnd = new TReports(this,DB,PRODUCT,ptr->getDetID());
		wnd->ShowModal();
		delete wnd;
	}
}


//____________________________________________Закрытие нарядов_____________________________________________________
void __fastcall TManufactureControl::btSearchClick(TObject *Sender)
{
    bool need_save = false;
    for (size_t i = 0; i < SGNarList->RowCount && !need_save; ++i)
    {
        need_save = SGNarList->Cells[1][i] != "" && (SGNarList->Cells[2][i].ToIntDef(0) + SGNarList->Cells[3][i].ToIntDef(0))!=0;
    }
    if (need_save)
    {
        if ( MessageBoxA(this->Handle, "Сохранить изменения?", "Сохранить изменения?",MB_YESNO|MB_ICONQUESTION) == mrYes )
            btSave->Click();
    }
    SGClear(SGNarList);

    bool use_step1 = false;
    bool use_step2 = false;
    bool use_step3 = false;
    bool use_step4 = false;

    std::string step1_cleaner = "Drop temporary table if exists `manufacture`.`step1`";
    std::string step3_cleaner = "Drop temporary table if exists `manufacture`.`step3`";
    std::string step4_cleaner = "Drop temporary table if exists `manufacture`.`step4`";
    if (leZak->Text.Length() || lePart->Text.Length())
    {
        use_step1 = true;
        std::string sql = "Create temporary table if not exists `manufacture`.`step1` (det_id bigint(20) unsigned, key det_id(`det_id`)) as"
                          " Select `a`.`det_id` from `manufacture`.`marsh_lists` a "
                          " join `manufacture`.`parts` b on `b`.`part_id` = `a`.`part_id` "
                          " join `manufacture`.`zakaz_list` c on `c`.`zak_id` = `b`.`zak_id` "
                          " where true ";
        if (leZak->Text.Length())
        {
            sql = sql + " and `c`.`zakaz` = '" + AnsiString(leZak->Text.Trim()).c_str() + "' ";
        }
        if (lePart->Text.Length())
        {
            sql = sql + " and `b`.`part_no` = '" + AnsiString(lePart->Text.Trim()).c_str() + "' ";
        }

        DB->SendCommand(step1_cleaner.c_str());
        DB->SendCommand(sql.c_str());
    }

    if (leIzd->Text.Length())
    {
        use_step2 = true;
        std::string sql = " Select convert(`a`.`det_id`,CHAR) det_id from `manufacture`.`part_content` a "
                          " join `manufacture`.`det_names` b on `b`.`det_id` = `a`.`det_id` "
                          " where b.obd = '"+std::string(GostToVin(leIzd->Text.Trim()).c_str())+"' ";
        TADOQuery *rez = DB->SendSQL(sql.c_str());
        if (rez)
        {
            if (rez->RecordCount)
            {
                std::string sql = "Call `manufacture`.`GetContentFull`('"+std::string((rez->FieldByName("det_id")->Value.operator AnsiString()).c_str())+"')";
                DB->SendCommand(sql.c_str());
            }
            else
            {
                delete rez;
                return;
            }
            delete rez;
        }
    }

    if (leDet->Text.Length())
    {
        use_step3 = true;
        std::string sql =   "Create temporary table if not exists `manufacture`.`step3` (det_id bigint(20) unsigned, key det_id(`det_id`)) as"
                            " Select `a`.`det_id` from `manufacture`.`marsh_lists` a "
                            " join `manufacture`.`det_names` b on `b`.`det_id` = `a`.`det_id` "
                            " where b.obd = '"+std::string(GostToVin(leDet->Text.Trim()).c_str())+"' ";
        DB->SendCommand(step3_cleaner.c_str());
        DB->SendCommand(sql.c_str());
    }

    if (leNar->Text.Length())
    {
        use_step4 = true;
        std::string sql =   "Create temporary table if not exists `manufacture`.`step4` (det_id bigint(20) unsigned, key det_id(`det_id`)) as"
                            " Select `a`.`det_id` from `manufacture`.`marsh_lists` a "
                            " join `manufacture`.`operation_list` b on `b`.`det_id` = `a`.`det_id` "
                            " join `manufacture`.`orders` c on `c`.`operation_id` = `b`.`OpUUID` "
                            " where c.order_id = '"+std::string(AnsiString(leNar->Text.Trim()).c_str())+"' ";
        DB->SendCommand(step4_cleaner.c_str());
        DB->SendCommand(sql.c_str());
    }

    if (use_step1 || use_step2 || use_step3 || use_step4)
    {
        std::string sql =   "select "
                            " convert( `a`.`order_id` ,CHAR) as order_id, "
                            " convert( `a`.`kol_request` ,CHAR) as kol_request, "
                            " convert( `a`.`kol_unmaked` ,CHAR) as kol_unmaked, "
                            " convert( `d`.`obd` ,CHAR) as obd, "
                            " convert( trim(concat(`b`.`opr`,' ',IFNULL(`b`.`oprid`,''),' ',IFNULL(`e`.`name`,''))) ,CHAR) as oper, "
                            " convert( trim(concat(IFNULL(`b`.`oboid`,''),' ',IFNULL(`f`.`name`,''))) ,CHAR) as obor  "
                            " from `manufacture`.`orders` a "
                            " join `manufacture`.`operation_list` b on `b`.`OpUUID` = `a`.`operation_id` "
                            " join `manufacture`.`marsh_lists` c on `c`.`det_id` = `b`.`det_id` "
                            " join `manufacture`.`det_names` d on `d`.`det_id` = `c`.`det_id` "
                            " left join `equipment`.`opr_names` e on `e`.`OprID` = `b`.`oprid` "
                            " left join `equipment`.`obor_list` f on `f`.`oboID` = `b`.`oboID` ";
        if (use_step1)
        {
            sql += " join `manufacture`.`step1` s1 on `s1`.`det_id` = `c`.`det_id` ";
        }
        if (use_step2)
        {
            sql += " join `manufacture`.`output` s2 on `s2`.`det_id` = `c`.`det_id` ";
        }
        if (use_step3)
        {
            sql += " join `manufacture`.`step3` s3 on `s3`.`det_id` = `c`.`det_id` ";
        }
        if (use_step4)
        {
            sql += " join `manufacture`.`step4` s4 on `s4`.`det_id` = `c`.`det_id` ";
        }

        sql += " where true ";
        switch (RG2->ItemIndex)
        {
            case 1:
            {
                sql += " and `a`.`kol_unmaked` = '0' ";
                break;
            }
            case 2:
            {
                sql += " and `a`.`kol_unmaked` != '0' ";
                break;
            }
            default: break;
        }
        sql += "order by `d`.`det_id`, `b`.`opr`, `b`.`oboid` ";

        sql = sql + "LIMIT "+AnsiString(E2->Text.ToIntDef(0)*E3->Text.ToIntDef(0)-E3->Text.ToIntDef(0)).c_str()+","+AnsiString(E3->Text).c_str()+" ";


        TADOQuery *rez = DB->SendSQL(sql.c_str());

        DB->SendCommand(step1_cleaner.c_str());
        DB->SendCommand(step3_cleaner.c_str());
        DB->SendCommand(step4_cleaner.c_str());
        if (rez)
        {
            for (rez->First(); !rez->Eof; rez->Next())
            {
                int row = SGNarList->RowCount-1;
              SGNarList->Cells[1][row] = rez->FieldByName("order_id")->Value;
//                SGNarList->Cells[2][row] = "Изгот.";
//                SGNarList->Cells[3][row] = "Брак";
//                SGNarList->Cells[4][row] = "Таб №";
//                SGNarList->Cells[5][row] = "Рабочий";
                SGNarList->Cells[6][row] = rez->FieldByName("kol_request")->Value;
                SGNarList->Cells[7][row] = rez->FieldByName("kol_unmaked")->Value;
                SGNarList->Cells[8][row] = VinToGost(rez->FieldByName("obd")->Value);
                SGNarList->Cells[9][row] = rez->FieldByName("oper")->Value;
                SGNarList->Cells[10][row]= rez->FieldByName("obor")->Value;

                ++SGNarList->RowCount;
            }
            if (SGNarList->RowCount > 2)
                --SGNarList->RowCount;
            delete rez;
        }
    }
    AutoWidthSG(SGNarList);
}
void __fastcall TManufactureControl::SGNarListMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
//
}
void __fastcall TManufactureControl::SGNarListSelectCell(TObject *Sender, int ACol,
		  int ARow, bool &CanSelect)
{
	TStringGrid *sg = (TStringGrid *)Sender;
	if (ARow&& ACol>=2 && ACol<=4 && sg->Cells[1][ARow]!="")
	{
		sg->Options<<goEditing;
	}
	else
	{
		sg->Options>>goEditing;
	}

}
void __fastcall TManufactureControl::btSaveClick(TObject *Sender)
{
    for (size_t i = 0; i < SGNarList->RowCount; ++i)
    {
        if (SGNarList->Cells[1][i] != "" && (SGNarList->Cells[2][i].ToIntDef(0) + SGNarList->Cells[3][i].ToIntDef(0))!=0)
        {
            if (SGNarList->Cells[4][i].Trim() != "")
            {

                std::string sql = std::string("Insert into `manufacture`.`orders_history` (order_id,date,tab_no,maked,broken) values ('")
                        +AnsiString(SGNarList->Cells[1][i]).c_str()+"',now(),'"+AnsiString(SGNarList->Cells[4][i]).Trim().c_str()
                        +"','"+AnsiString(SGNarList->Cells[2][i].ToIntDef(0)).c_str()+"','"+AnsiString(SGNarList->Cells[3][i].ToIntDef(0)).c_str()+"')";

                std::string upd = std::string("Update `manufacture`.`orders` set"
                        " kol_maked = kol_maked + '")+AnsiString(SGNarList->Cells[2][i].ToIntDef(0)).c_str()+"', "
                        " kol_broken = kol_broken +'"+AnsiString(SGNarList->Cells[3][i].ToIntDef(0)).c_str()+"', "
                        " kol_unmaked = kol_unmaked - ('"+AnsiString(SGNarList->Cells[2][i].ToIntDef(0)).c_str()+"' + '"+AnsiString(SGNarList->Cells[3][i].ToIntDef(0)).c_str()+"') "
                        " where order_id = '"+AnsiString(SGNarList->Cells[1][i]).c_str()+"'";

                std::string upd2 = std::string("Update `manufacture`.`orders` set"
                        " closed_date = now(), closed_type = 'end of actions' "
                        " where kol_unmaked = 0 and order_id = '")+AnsiString(SGNarList->Cells[1][i]).c_str()+"'";

                Transaction tr(DB);
                bool res = DB->SendCommand(sql.c_str());
                res *= DB->SendCommand(upd.c_str());
                res *= DB->SendCommand(upd2.c_str());
                if (res)
                {
                    tr.Commit();
                }
                NarUpdate(i);
            }
            else
            {
                ShowMessage("Не указан табельный номер для наряда "+ SGNarList->Cells[1][i]);
            }
        }
    }
}
void TManufactureControl::NarUpdate(int Row)
{
    std::stringstream sql;
    sql << "select "
           " convert( `a`.`order_id` ,CHAR) as order_id, "
           " convert( `a`.`kol_request` ,CHAR) as kol_request, "
           " convert( `a`.`kol_unmaked` ,CHAR) as kol_unmaked, "
           " convert( `d`.`obd` ,CHAR) as obd, "
           " convert( trim(concat(`b`.`opr`,' ',IFNULL(`b`.`oprid`,''),' ',IFNULL(`e`.`name`,''))) ,CHAR) as oper, "
           " convert( trim(concat(IFNULL(`b`.`oboid`,''),' ',IFNULL(`f`.`name`,''))) ,CHAR) as obor  "
           " from `manufacture`.`orders` a "
           " join `manufacture`.`operation_list` b on `b`.`OpUUID` = `a`.`operation_id` "
           " join `manufacture`.`marsh_lists` c on `c`.`det_id` = `b`.`det_id` "
           " join `manufacture`.`det_names` d on `d`.`det_id` = `c`.`det_id` "
           " left join `equipment`.`opr_names` e on `e`.`OprID` = `b`.`oprid` "
           " left join `equipment`.`obor_list` f on `f`.`oboID` = `b`.`oboID` "
           " where `a`.`order_id` = '"<< AnsiString(SGNarList->Cells[1][Row]).c_str() <<"'";
    TADOQuery *rez = DB->SendSQL(sql.str().c_str());
    if (rez)
    {
        if (rez->RecordCount)
        {
			SGNarList->Cells[1][Row] = rez->FieldByName("order_id")->Value;
			SGNarList->Cells[2][Row] = "";
			SGNarList->Cells[3][Row] = "";
			SGNarList->Cells[4][Row] = "";
			SGNarList->Cells[5][Row] = "";
            SGNarList->Cells[6][Row] = rez->FieldByName("kol_request")->Value;
            SGNarList->Cells[7][Row] = rez->FieldByName("kol_unmaked")->Value;
            SGNarList->Cells[8][Row] = VinToGost(rez->FieldByName("obd")->Value);
            SGNarList->Cells[9][Row] = rez->FieldByName("oper")->Value;
            SGNarList->Cells[10][Row]= rez->FieldByName("obor")->Value;
        }
        delete rez;
    }


}
void __fastcall TManufactureControl::SGNarListDrawCell(TObject *Sender, int ACol,
          int ARow, TRect &Rect, TGridDrawState State)
{
	TStringGrid *sg = (TStringGrid *)Sender;
	// - раскраска сетки
    static int color=0X00E0FFFF;
    if(ACol&&ARow) // разлинейка
    {
		if((ARow%2))
        {
            color=0X00E0FFFF;
        }
        else
        {
            color=0x00e0FFe0;
		}
		sg->Canvas->Brush->Color=color;

		sg->Font->Color=clBlack;
		sg->Canvas->FillRect(Rect);
		sg->Canvas->TextOutW(Rect.left+2, Rect.top+1,
		sg->Cells[ACol][ARow]);
    }

	// выделенные поля
    if(ACol>=sg->Selection.Left&&ACol<=
		sg->Selection.Right&&ARow>=sg->Selection.Top&&ARow<=
		sg->Selection.Bottom) // выделение
    {
		sg->Canvas->Brush->Color=0x00FFE0E0; // clMenu;
		sg->Canvas->FillRect(Rect);
		sg->Font->Color=clBlack;
		sg->Canvas->TextOutW(Rect.left+2, Rect.top+1,
        sg->Cells[ACol][ARow]);
    }
}
//---------------------------------------------------------------------------

void __fastcall TManufactureControl::pagerClick(TObject *Sender)
{
TSpeedButton *bt=(TSpeedButton *)Sender;
switch (bt->Tag)
    {
    case  1:{E2->Text=String(E2->Text.ToInt()+1);break;}
    case -1:{if (E2->Text.ToInt()>1) {E2->Text=String(E2->Text.ToInt()-1);}break;}
    default:return;
    }
}
void __fastcall TManufactureControl::E2Change(TObject *Sender)
{
	if (E2->Text==""||E2->Text=="0")
	{
		E2->Text="1";
	}
	btSearch->Click();
}
void __fastcall TManufactureControl::E3Change(TObject *Sender)
{

if (E3->Text==""||E3->Text=="0")
{
	E3->Text="1";
}
if (E2->Text!="1")
{
	E2->Text="1";
}

}
void __fastcall TManufactureControl::RG2Click(TObject *Sender)
{
    btSearch->Click();
}
//---------------------------------------------------------------------------


void __fastcall TManufactureControl::SGNarListSetEditText(TObject *Sender, int ACol,
          int ARow, const UnicodeString Value)
{
    TStringGrid *sg = (TStringGrid *)Sender;
	switch (ACol)
    {
		case 2:
		{
            int kol = sg->Cells[7][ARow].ToIntDef(0) - sg->Cells[3][ARow].ToIntDef(0);

            if (Value.ToIntDef(0) > kol)
			{
				sg->Cells[2][ARow] = kol;
            }
            break;
		}
		case 3:
        {
            int kol = sg->Cells[7][ARow].ToIntDef(0) - sg->Cells[2][ARow].ToIntDef(0);

            if (Value.ToIntDef(0) > kol)
            {
                sg->Cells[3][ARow] = kol;
            }
            break;
        }
		case 4:
        {
            std::string sql = std::string("select IFNULL(concat(family, ' ',Upper(left(name,1)),'.', Upper(left(otch,1)),'.'),'') fio from `manufacture`.`workers` where tab_no ='")+
                    AnsiString(Value).c_str()
                    +"' and date_from < now() and (date_to >=now() or date_to is null) ";

            TADOQuery *rez = DB->SendSQL(sql.c_str());
            sg->Cells[5][ARow] = "";
            if (rez)
            {
                if (rez->RecordCount)
                {
                    sg->Cells[5][ARow] = rez->FieldByName("fio")->Value;
                    AutoWidthSG(SGNarList);
                }
                delete rez;
            }
        }
	default:  break;
	}
}
//---------------------------------------------------------------------------

void __fastcall TManufactureControl::surch_sgSelectCell(TObject *Sender, int ACol,
          int ARow, bool &CanSelect)
{
	surch_descr->Lines->Text = surch_sg->Cells[20][ARow];
	surch_reason->Text = surch_sg->Cells[19][ARow];
}
//---------------------------------------------------------------------------

void __fastcall TManufactureControl::N6Click(TObject *Sender)
{
	//create
    TSurchargeList *wnd = new TSurchargeList(this, DB);
    wnd->ShowModal();
    delete wnd;
}
void __fastcall TManufactureControl::N9Click(TObject *Sender)
{
	//edit
    TSurchargeList *wnd = new TSurchargeList(this, DB);
    //загрузить данные из гриды

    wnd->zak_no->Text = surch_sg->Cells[2][surch_sg->Row];
    wnd->part_no->Text = surch_sg->Cells[3][surch_sg->Row];
    wnd->obd->Text = surch_sg->Cells[4][surch_sg->Row];
    wnd->opr_kod->Text = surch_sg->Cells[22][surch_sg->Row];
    wnd->opr_name->Text = surch_sg->Cells[23][surch_sg->Row];//ro
    wnd->kts->Text = surch_sg->Cells[11][surch_sg->Row];
    wnd->rr->Text = surch_sg->Cells[9][surch_sg->Row];
    wnd->vn->Text = surch_sg->Cells[10][surch_sg->Row];
    wnd->kol->Text = surch_sg->Cells[12][surch_sg->Row];
    wnd->tpz->Text = surch_sg->Cells[13][surch_sg->Row];
    wnd->tsht->Text = surch_sg->Cells[14][surch_sg->Row];
    wnd->tfact->Text = surch_sg->Cells[15][surch_sg->Row];

    wnd->reason->Text = surch_sg->Cells[19][surch_sg->Row];
    wnd->descr->Lines->Text = surch_sg->Cells[20][surch_sg->Row];

    wnd->nar_no->Text = surch_sg->Cells[1][surch_sg->Row];//ro
    wnd->cex->Text = surch_sg->Cells[5][surch_sg->Row];
    wnd->utch->Text = surch_sg->Cells[6][surch_sg->Row];
    wnd->tab_no->Text = surch_sg->Cells[8][surch_sg->Row];
    wnd->fio->Text = surch_sg->Cells[21][surch_sg->Row];//ro

    wnd->surcharge_id = surch_sg->Cells[16][surch_sg->Row];
    wnd->zak_id = surch_sg->Cells[17][surch_sg->Row];
    wnd->part_id = surch_sg->Cells[18][surch_sg->Row];

    wnd->ShowModal();

    delete wnd;
}
void __fastcall TManufactureControl::N8Click(TObject *Sender)
{
	//remove
    std::string surch_id(AnsiString(surch_sg->Cells[16][surch_sg->Row]).c_str());
    if (surch_id.empty())
        return;

    if ( MessageBoxA(this->Handle, "Удалить доплатной лист?", "Удалить доплатной лист?",MB_YESNO|MB_ICONQUESTION) == mrYes )
    {
        Transaction tr(DB);
        std::stringstream sql;
        sql << "delete from `manufacture`.`orders` where surcharge_id = '"<<surch_id<<"'";
        DB->SendCommand(sql.str().c_str());

        sql.str("");

        sql << "delete from `manufacture`.`surcharge` where record_id = '"<<surch_id<<"'";
        DB->SendCommand(sql.str().c_str());
        tr.Commit();
    }
}
//---------------------------------------------------------------------------

