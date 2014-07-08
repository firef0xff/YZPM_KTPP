//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Usage.h"
#include "add_data_wnd.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
__fastcall TResourceUsage::TResourceUsage(TComponent* Owner,TWinControl *_p, int &_LUser,cSQL *db,IconsData *_IcoData)
    : TFrame(Owner),LUser(_LUser),IcoData(_IcoData),DB(db),new_orders(db),started_orders(db),calck_equipmen_load(0)
{
	static size_t count = 0;
	count++;
    // расположение
    Align=alClient;
    Parent=_p;
    Name=Name+String(count);

    if (Parent->ClassNameIs("TTabSheet"))
    {
		((TTabSheet*)Parent)->Caption="Расчет загрузки     ";
    }
	ManufactureTree->Images=IcoData->GetImgList();
    DevelopTree->Images=IcoData->GetImgList();

    // настройка содержимого
    std::stringstream sql; sql<<"call administration.Get_Rights('"<<LUser<<"')";
    TADOQuery *rez=DB->SendSQL(sql.str().c_str());
    if(rez)
    {
        for (rez->First(); !rez->Eof; rez->Next())
		{
            const String val=rez->FieldByName("progname")->Value;
		}
		delete rez;
	}


	zap_sg->Cells[1][0] = "Заказ";
	zap_sg->Cells[2][0] = "Партия";
	zap_sg->Cells[3][0] = "Обозначение";
	zap_sg->Cells[4][0] = "Кол-во.";
	zap_sg->Cells[5][0] = "Цех";
	zap_sg->Cells[6][0] = "Уч-к.";
	zap_sg->Cells[7][0] = "Процент";
    AutoWidthSG(zap_sg);


	plan_sg->Cells[1][0] = "Заказ";
	plan_sg->Cells[2][0] = "Партия";
	plan_sg->Cells[3][0] = "Обозначение";
	plan_sg->Cells[4][0] = "Кол-во.";
	plan_sg->Cells[5][0] = "Цех";
	plan_sg->Cells[6][0] = "Уч-к.";
	plan_sg->Cells[7][0] = "Процент";
    AutoWidthSG(plan_sg);


    Previe->Cells[1][0] = "Цех/Группа";
    Previe->Cells[2][0] = "Кол-во обор";
    Previe->Cells[3][0] = "Ксм";
    Previe->Cells[4][0] = "План";
    Previe->Cells[5][0] = "Дифицит";
    Previe->Cells[6][0] = "Действ.";
    Previe->Cells[7][0] = "Отклонение";
    Previe->Cells[8][0] = "Примечание";
    AutoWidthSG(Previe);
}

void __fastcall TResourceUsage::FindStartedClick(TObject *Sender)
{
/*Получаем список всех запущенных/закрытых партий
 *
*/
    std::stringstream sql;
    sql << " select "
           " a.zakaz, a.zak_id, b.part_id, b.part_no "
           " from `manufacture`.`zakaz_list` a "
           " join `manufacture`.`parts` b on a.zak_id = b.zak_id "
           " where a.zakaz like '%"<<AnsiString(StartedParams->Text).c_str()<<"%' ";
    if (Show_Closed->Checked)
    {
        sql << " and b.close_date is not null";
    }
    else
    {
        sql << " and b.close_date is null";
    }
    sql << " order by a.zakaz,b.part_no ";

    ManufactureTree->Items->Clear();

    TADOQuery *rez = DB->SendSQL(sql.str().c_str());
    if (rez && rez->RecordCount)
    {
        String prev_zakaz;
        TTreeNode *node = 0;
        for (rez->First(); !rez->Eof; rez->Next())
        {
            TTreeNode *ch_node = 0;

            AnsiString zak = rez->FieldByName("zakaz")->Value;
            unsigned int part_no = rez->FieldByName("part_no")->Value;
            __uint64 zak_id = (__uint64)rez->FieldByName("zak_id")->Value.operator __int64();
            __uint64 part_id = (__uint64)rez->FieldByName("part_id")->Value.operator __int64();


            if (zak != prev_zakaz)
            {
                if (node)
                {
                    node->SelectedIndex = node->ImageIndex;
                    node->ExpandedImageIndex = node->ImageIndex;
                }

                data::ZakazData *ptr = new data::ZakazData(zak_id, zak);
                node = ManufactureTree->Items->AddObject(node, ptr->zakaz, (void *)ptr);
                node->ImageIndex = -1;
                prev_zakaz = zak;
            }
            data::PartData *ptr = new data::PartData(zak_id, zak, part_id, part_no);
            ch_node = ManufactureTree->Items->AddChildObject(node, ptr->part_no, (void*)ptr);
            ch_node->ImageIndex = -1;
            ch_node->SelectedIndex = ch_node->ImageIndex;
            ch_node->ExpandedImageIndex = ch_node->ImageIndex;
        }
        if (node)
        {
            node->SelectedIndex=node->ImageIndex;
            node->ExpandedImageIndex=node->ImageIndex;
        }
        delete rez;
    }

}

void __fastcall TResourceUsage::FindNewClick(TObject *Sender)
{
/*
 * Получаем список всех заказов с составом по номеру заказа или обозначению детали
 * разворачивать дерево дальше второго уровня смысла пока не вижу
*/
    std::stringstream sql;
    sql << " select "
           " a.kol, b.zakaz_id, b.zakaz, c.id, c.obd "
           " from `market`.`zakaz` a "
           " join `market`.`orders` b on a.zakaz_id = b.zakaz_id"
           " join `constructions`.`det_names` c on a.id = c.id "
           " where b.zakaz like '%"<<AnsiString(NewParams->Text).c_str()<<"%' or c.obd like '%"<<GostToInt(NewParams->Text).c_str()<<"%'";

	DevelopTree->Items->Clear();

    TADOQuery *rez = DB->SendSQL(sql.str().c_str());
    if (rez && rez->RecordCount)
    {
        String prev_zakaz;
        TTreeNode *node = 0;
        for (rez->First(); !rez->Eof; rez->Next())
        {
            TTreeNode *ch_node = 0;

            AnsiString zak = rez->FieldByName("zakaz")->Value;
            __uint64 zak_id = (__uint64)rez->FieldByName("zakaz_id")->Value.operator __int64();

            AnsiString obd = rez->FieldByName("obd")->Value;
            unsigned int det_id = rez->FieldByName("id")->Value;
            __uint64 kol = (__uint64)rez->FieldByName("kol")->Value.operator __int64();

            if (zak != prev_zakaz)
            {
                if (node)
                {
                    node->SelectedIndex = node->ImageIndex;
                    node->ExpandedImageIndex = node->ImageIndex;
                }

				data::ZakazData *ptr = new data::ZakazData(zak_id, zak);
                node = DevelopTree->Items->AddObject(node, ptr->zakaz, (void *)ptr);
                prev_zakaz = zak;
            }
            data::IzdData *ptr = new data::IzdData(zak_id, zak, det_id, kol, obd);
            ch_node = DevelopTree->Items->AddChildObject(node, VinToGost(ptr->obd) + " - " + ptr->kol + " шт.", (void*)ptr);

            ch_node->SelectedIndex = ch_node->ImageIndex;
            ch_node->ExpandedImageIndex = ch_node->ImageIndex;
        }
        if (node)
        {
            node->SelectedIndex=node->ImageIndex;
            node->ExpandedImageIndex=node->ImageIndex;
        }
        delete rez;
    }
}

void __fastcall TResourceUsage::TVDeletion(TObject *Sender, TTreeNode *Node)
{
    if (Node->Data)
    {
        delete (data::ZakazData *)Node->Data;
	}
   return;
}


void __fastcall TResourceUsage::AddStartedClick(TObject *Sender)
{
	TCalckAddParams *wnd = new TCalckAddParams(this);
	wnd->Kol->Visible = false;

	if (wnd->ShowModal() == mrOk)
	{
		for (size_t i = 0; i < ManufactureTree->SelectionCount; ++i)
		{
			TTreeNode *node = ManufactureTree->Selections[i];
			if (node->Level == 0)
			{//Добавить заказ
				for (TTreeNode *ch_node = node->getFirstChild(); ch_node; ch_node = node->GetNextChild(ch_node))
				{
					data::PartData *ptr = (data::PartData *)ch_node->Data;
					started_orders.AddPart(ptr->part_id, wnd->Percent->Text.ToDouble(),
										   AnsiString(wnd->Cex->Text).c_str(), AnsiString(wnd->Utch->Text).c_str());
				}
			}
			else
			{//Добавить партию
				data::PartData *ptr = (data::PartData *)node->Data;
				started_orders.AddPart(ptr->part_id, wnd->Percent->Text.ToDouble(),
									   AnsiString(wnd->Cex->Text).c_str(), AnsiString(wnd->Utch->Text).c_str());
			}
		}

	}


    delete wnd;
    UpdateStarted();
}
void __fastcall TResourceUsage::StartedClearClick(TObject *Sender)
{
    if ( MessageBoxA(this->Handle, "Очистить задание расчета?", "Очистить задание расчета?",MB_YESNO|MB_ICONQUESTION) == mrYes )
    {
        started_orders.Clear();
        UpdateStarted();
    }
}
void __fastcall TResourceUsage::StartedRemoveClick(TObject *Sender)
{
    if ( MessageBoxA(this->Handle, "Очистить задание расчета?", "Очистить задание расчета?",MB_YESNO|MB_ICONQUESTION) == mrYes )
    {
        for(int i=zap_sg->Selection.Top; i<=zap_sg->Selection.Bottom; i++)
        {
            if(zap_sg->Cells[8][i]!="")
            {
                started_orders.Remove(zap_sg->Cells[8][i].ToIntDef(0));
            }
        }
        UpdateStarted();
    }
}

void __fastcall TResourceUsage::AddNewClick(TObject *Sender)
{
	TCalckAddParams *wnd = new TCalckAddParams(this);

	if (wnd->ShowModal() == mrOk)
	{
        for (size_t i = 0; i < DevelopTree->SelectionCount; ++i)
        {
            TTreeNode *node = DevelopTree->Selections[i];
            if (node->Level == 0)
            {//Добавить заказ
                for (TTreeNode *ch_node = node->getFirstChild(); ch_node; ch_node = node->GetNextChild(ch_node))
                {
                    data::IzdData *ptr = (data::IzdData *)ch_node->Data;
                    new_orders.AddDet(ptr->zakaz_id,ptr->det_id, wnd->Kol->Text.ToIntDef(1), wnd->Percent->Text.ToDouble(),
									  AnsiString(wnd->Cex->Text).c_str(), AnsiString(wnd->Utch->Text).c_str());
                }
            }
            else
            {//Добавить партию
                data::IzdData *ptr = (data::IzdData *)node->Data;
                new_orders.AddDet(ptr->zakaz_id,ptr->det_id, wnd->Kol->Text.ToIntDef(1), wnd->Percent->Text.ToDouble(),
								  AnsiString(wnd->Cex->Text).c_str(), AnsiString(wnd->Utch->Text).c_str());
            }
        }
	}
    delete wnd;
    UpdateNew();
}
void __fastcall TResourceUsage::NewClearClick(TObject *Sender)
{
    if ( MessageBoxA(this->Handle, "Очистить задание расчета?", "Очистить задание расчета?",MB_YESNO|MB_ICONQUESTION) == mrYes )
    {
        new_orders.Clear();
        UpdateNew();
    }
}
void __fastcall TResourceUsage::NewRemoveClick(TObject *Sender)
{
    if ( MessageBoxA(this->Handle, "Очистить задание расчета?", "Очистить задание расчета?",MB_YESNO|MB_ICONQUESTION) == mrYes )
    {
        for(int i=plan_sg->Selection.Top; i<=plan_sg->Selection.Bottom; i++)
        {
            if(plan_sg->Cells[8][i]!="")
            {
                new_orders.Remove(plan_sg->Cells[8][i].ToIntDef(0));
            }
        }
        UpdateNew();
    }
}


void TResourceUsage::UpdateStarted(void)
{
	CleanEquipLoad();
    dbtmp::StartedOrdersQueue::DataSet dt;
    started_orders.GetData(dt);
    SGClear(zap_sg ,2);

    for (dbtmp::StartedOrdersQueue::DataSet::const_iterator it = dt.begin(), end = dt.end(); it!=end; ++it)
    {
        const dbtmp::StartedOrdersQueue::Data &lnk = *it;

        zap_sg->Cells[1][zap_sg->RowCount - 1] = lnk.zakaz.c_str();
        zap_sg->Cells[2][zap_sg->RowCount - 1] = lnk.part_no;
        zap_sg->Cells[3][zap_sg->RowCount - 1] = lnk.obd.c_str();
        zap_sg->Cells[4][zap_sg->RowCount - 1] = lnk.kol;
        zap_sg->Cells[5][zap_sg->RowCount - 1] = lnk.ceh.c_str();
        zap_sg->Cells[6][zap_sg->RowCount - 1] = lnk.utch.c_str();
        zap_sg->Cells[7][zap_sg->RowCount - 1] = lnk.percent;
        zap_sg->Cells[8][zap_sg->RowCount - 1] = lnk.record_id;
        zap_sg->Cells[9][zap_sg->RowCount - 1] = lnk.det_id;

        ++zap_sg->RowCount;
    }

    if (zap_sg->RowCount > 2)
        --zap_sg->RowCount;

    AutoWidthSG(zap_sg);
}
void TResourceUsage::UpdateNew(void)
{
	CleanEquipLoad();
    dbtmp::NewOrdersQueue::DataSet dt;
    new_orders.GetData(dt);
    SGClear(plan_sg ,1);

    for (dbtmp::NewOrdersQueue::DataSet::const_iterator it = dt.begin(), end = dt.end(); it!=end; ++it)
    {
        const dbtmp::NewOrdersQueue::Data &lnk = *it;
        plan_sg->Cells[1][plan_sg->RowCount - 1] = lnk.zakaz.c_str();
        plan_sg->Cells[2][plan_sg->RowCount - 1] = lnk.part_no;
        plan_sg->Cells[3][plan_sg->RowCount - 1] = lnk.obd.c_str();
        plan_sg->Cells[4][plan_sg->RowCount - 1] = lnk.kol;
        plan_sg->Cells[5][plan_sg->RowCount - 1] = lnk.ceh.c_str();
        plan_sg->Cells[6][plan_sg->RowCount - 1] = lnk.utch.c_str();
        plan_sg->Cells[7][plan_sg->RowCount - 1] = lnk.percent;
        plan_sg->Cells[8][plan_sg->RowCount - 1] = lnk.record_id;
        plan_sg->Cells[9][plan_sg->RowCount - 1] = lnk.det_id;

        ++plan_sg->RowCount;
    }

    if (plan_sg->RowCount > 2)
        --plan_sg->RowCount;

    AutoWidthSG(plan_sg);
}
void TResourceUsage::UpdatePrevie(void)
{
    if (!calck_equipmen_load)
    {
        RecalckEquipLoad();
    }
    size_t days;
    switch (CalckPeroid->ItemIndex)
    {
        case 0:
        {
            days = MonthDays->Text.ToIntDef(22);
            break;
        }
        case 1:
        {
            days = MonthDays->Text.ToIntDef(22) * 3;
            break;
        }
        case 2:
        {
            days = MonthDays->Text.ToIntDef(22) * 12;
            break;
        }
        default:
        {
            days = PeriodDays->Text.ToIntDef(22);
        }
    }
    calck_equipmen_load->ToCells(Previe, days);
}
void TResourceUsage::RecalckEquipLoad(void)
{
    CleanEquipLoad();
    calck_equipmen_load = new calck::EquipmentLoad(DB, started_orders, new_orders);
}
void TResourceUsage::CleanEquipLoad(void)
{
    if (calck_equipmen_load)
    {
        delete calck_equipmen_load;
        calck_equipmen_load = 0;
    }
}


void __fastcall TResourceUsage::StartedParamsKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == 13)
	{
		FindStarted->Click();
	}
}
void __fastcall TResourceUsage::NewParamsKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == 13)
	{
		FindNew->Click();
	}
}


void __fastcall TResourceUsage::SetFileClick(TObject *Sender)
{
    if (SD->Execute())
    {
        FileName->Text=SD->FileName;
    }
    else
    {
        FileName->Text="";
    }
	ActiveDelimiter->Enabled=FileName->Text.Trim().Length();
}
void __fastcall TResourceUsage::ToExcelClick(TObject *Sender)
{
    if (!calck_equipmen_load)
    {
        RecalckEquipLoad();
    }
    calck_equipmen_load->path = AnsiString(FileName->Text).c_str();
    calck_equipmen_load->use_listing = ActiveDelimiter->Checked && ActiveDelimiter->Enabled;
    calck_equipmen_load->lists_by_file = Count->Text.ToIntDef(100);

    size_t days;
    switch (CalckPeroid->ItemIndex)
    {
        case 0:
        {
            days = MonthDays->Text.ToIntDef(22);
            break;
        }
        case 1:
        {
            days = MonthDays->Text.ToIntDef(22) * 3;
            break;
        }
        case 2:
        {
            days = MonthDays->Text.ToIntDef(22) * 12;
            break;
        }
        default:
        {
            days = PeriodDays->Text.ToIntDef(22);
        }
    }
    calck_equipmen_load->ToExcel(days);
}
void __fastcall TResourceUsage::FileNameChange(TObject *Sender)
{
	ActiveDelimiter->Enabled=FileName->Text.Trim().Length();
}
void __fastcall TResourceUsage::StartCalckClick(TObject *Sender)
{
    UpdatePrevie();
}
