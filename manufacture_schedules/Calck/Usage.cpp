//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Usage.h"
#include "functions.h"
#include "sstream.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
__fastcall TResourceUsage::TResourceUsage(TComponent* Owner,TWinControl *_p, int &_LUser,cSQL *db,IconsData *_IcoData)
	: TFrame(Owner),LUser(_LUser),IcoData(_IcoData),DB(db)
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
}
//---------------------------------------------------------------------------
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
        sql << "' and b.close_date is not null'";
    }
    else
    {
        sql << "' and b.close_date is null'";
    }
}
//---------------------------------------------------------------------------

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
           " where b.zakaz like '%"<<AnsiString(NewParams->Text).c_str()<<"%' or c.obd like '%"<<GostToVin(NewParams->Text).c_str()<<"%'";
}
//---------------------------------------------------------------------------

