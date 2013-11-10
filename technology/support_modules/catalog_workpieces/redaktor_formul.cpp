//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "redaktor_formul.h"
#pragma package(smart_init)
#pragma resource "*.dfm"

__fastcall TFomul_Editor::TFomul_Editor(TComponent* Owner,cSQL *db,String _vz)
    : TForm(Owner),DB(db)
{
vz=_vz;
init();
}
void         TFomul_Editor::init (void)
{
start_sql=false;
SGClear(SG1,0);
SG1->Cells[1][0]="Параметр";
SG1->Cells[2][0]="Описание";
AutoWidthSG(SG1);
SGClear(SG0,0);
SG0->Cells[1][0]="Параметр";
SG0->Cells[2][0]="Описание";

String sql="Select distinct parametr,parametr_name from  billets.parametr_list order by parametr";
TADOQuery *rez=DB->SendSQL(sql);
if (rez&&rez->RecordCount)
    {
    for (rez->First(); !rez->Eof; rez->Next())
        {
        SG0->Cells[1][SG0->RowCount-1]=rez->FieldByName("parametr")->Value;
        SG0->Cells[2][SG0->RowCount-1]=rez->FieldByName("parametr_name")->Value;
        SG0->RowCount+=1;
        }
    delete rez; rez=0;
    if (SG0->RowCount>2)
        {
        SG0->RowCount-=1;
        }
    }
AutoWidthSG(SG0);
LE1->Text=vz;
LE5->Text=vz;
CB1->Items->Clear();
CB1->Text="";
LE2->Text="";
LE3->Text="";
LE4->Text="";
LE1Change(0);
}
void __fastcall TFomul_Editor::LE1Change(TObject *Sender)
{
if (LE1->Text.Trim()=="") {return;}
String sql="Select distinct title from billets.raschet_zagot where kod='"+LE1->Text.Trim()+"' order by title";
CB1->Items->Clear();
SGClear(SG1,0);
AutoWidthSG(SG1);
CB1->Text="";
TADOQuery *rez=DB->SendSQL(sql);
if (rez&&rez->RecordCount)
    {
    for (rez->First(); !rez->Eof; rez->Next())
        {
        CB1->Items->Add(rez->FieldByName("title")->Value);
        }
    }
delete rez; rez=0;
CB1->ItemIndex=0;
CB1Click(0);
}
void __fastcall TFomul_Editor::CB1Click(TObject *Sender)
{
start_sql=false;
String sql="Select formula,type from billets.raschet_zagot  where kod='"+LE1->Text+"' and title='"+CB1->Text+"' order by title";
TADOQuery *rez=DB->SendSQL(sql);
if (rez&&rez->RecordCount)
    {
    for (rez->First(); !rez->Eof; rez->Next())
        {
        if (rez->FieldByName("type")->Value=="nrm")
            {
            LE3->Text=rez->FieldByName("Formula")->Value;
            }
        if (rez->FieldByName("type")->Value=="mass")
            {
            LE2->Text=rez->FieldByName("Formula")->Value;
            }
        }
    }
delete rez; rez=0;
/*размер заготовки*/
sql="Select razz from billets.razzm_zag where kod='"+LE1->Text+"' and title='"+CB1->Text+"'";
rez=DB->SendSQL(sql);
if (rez&&rez->RecordCount)
    {
    LE4->Text=rez->FieldByName("razz")->Value;
    }
delete rez; rez=0;
start_sql=Active;
LE2Change(0);
}
void __fastcall TFomul_Editor::LE2Change(TObject *Sender)
{
if (!start_sql)
{return;}
int i;
String formuls=LE2->Text+LE3->Text,params;
formuls=Replace(formuls,"pow","");
formuls=Replace(formuls,"sqrt","");
formuls=Replace(formuls,"pi","");
formuls=Replace(formuls,"acos","");
formuls=Replace(formuls,"asin","");
formuls=Replace(formuls,"atan","");
formuls=Replace(formuls,"log10","");
formuls=Replace(formuls,"log","");
formuls=Replace(formuls,"sin","");
formuls=Replace(formuls,"cos","");
formuls=Replace(formuls,"tan","");
formuls=Replace(formuls,"degrees","");
formuls=Replace(formuls,"exp","");
formuls=Replace(formuls,"abs","");
for (i = 1; i <=formuls.Length(); i++)
    {
    if (
    formuls.operator [](i)!='('&&
    formuls.operator [](i)!=')'&&
    formuls.operator [](i)!='+'&&
    formuls.operator [](i)!='-'&&
    formuls.operator [](i)!='*'&&
    formuls.operator [](i)!='/'&&
    formuls.operator [](i)!='='&&
    !isdigit(formuls.operator [](i)) &&
    !params.Pos(formuls.operator [](i))
    )
        {
        params=params+"'"+formuls.operator [](i)+"'," ;
        }
    }
params.Delete(params.Length(),1);
SGClear(SG1,0);
if (params.Trim()=="") {return;}   //загрузка глобальных параметров
String sql="Select distinct c.parametr,c.parametr_name from  billets.parametr_list c  where BINARY parametr in ("+params+") order by c.parametr";
TADOQuery *rez=DB->SendSQL(sql);
if (rez&&rez->RecordCount)
    {
    for (rez->First(); !rez->Eof; rez->Next())
        {
        SG1->Cells[1][SG1->RowCount-1]=rez->FieldByName("parametr")->Value;
        SG1->Cells[2][SG1->RowCount-1]=rez->FieldByName("parametr_name")->Value;
        SG1->RowCount+=1;
        }
    }
delete rez; rez=0;
SG1->Cells[0][SG1->RowCount-1]="*";
AutoWidthSG(SG1);
}
void __fastcall TFomul_Editor::FormActivate(TObject *Sender)
{
start_sql=Active;
LE2Change(0);
}
void __fastcall TFomul_Editor::SG1SetEditText(TObject *Sender, int ACol, int ARow,
          const UnicodeString Value)
{
int i;
if (ARow==SG1->RowCount-1&&Value.Trim()!="")
    {
    SG1->Cells[0][SG1->RowCount-1]="";
    SG1->RowCount++;
    SG1->Cells[0][SG1->RowCount-1]="*";
    }
if (SG1->Cells[1][ARow].Trim()==""&&SG1->Cells[2][ARow].Trim()==""&&SG1->Cells[0][ARow].Trim()!="*"&&SG1->RowCount>2)
    {
    for (i = ARow; i < SG1->RowCount; i++)
        {
        SG1->Cells[0][i]=SG1->Cells[0][i+1];
        SG1->Cells[1][i]=SG1->Cells[1][i+1];
        SG1->Cells[2][i]=SG1->Cells[2][i+1];
        }
    SG1->RowCount--;
    }
if (ACol==1)
    {
    for (i = 1; i < SG1->RowCount; i++)
        {
        if (SG1->Cells[1][i].Trim()==Value&&SG1->Cells[1][i].Trim()!=""&&i!=ARow||Value.Length()>1)
            {
            SG1->Cells[ACol][ARow]=""; return;
            }
        }
    SG1->Cells[ACol][ARow]=Value.Trim();
    }
}
void __fastcall TFomul_Editor::BitBtn1Click(TObject *Sender)
{
if (LE5->Text.Trim()!=""&&CB1->Text!="")
    {
    String params,existing,sql="Delete from billets.raschet_zagot where kod='"+LE5->Text+"' and title='"+CB1->Text+"'";
    if (!DB->SendCommand(sql)){return;}
    sql="Delete from billets.razzm_zag where kod='"+LE5->Text+"' and title='"+CB1->Text+"'";
    if (!DB->SendCommand(sql)){return;}
    int i,id;
    for (i=1; i<SG1->RowCount-1; i++)
        {
        params=params+"'"+SG1->Cells[1][i]+"',";
        }
    params.Delete(params.Length(),1);
    sql="select paramid,parametr from billets.parametr_list where BINARY parametr in ("+params+")";
    TADOQuery *rez=DB->SendSQL(sql);
    if (!rez){return;}
    rez->First();
    while (!rez->Eof)
        {
        existing=existing+"'"+rez->FieldByName("parametr")->Value+"',";
        rez->Next();
        }
    delete rez; rez=0;
    existing.Delete(existing.Length(),1);
    for (i = 1; i<SG1->RowCount-1; i++)
        {
        if (!existing.Pos(SG1->Cells[1][i].Trim()))
            {
            sql="INSERT INTO billets.parametr_list (parametr,parametr_name) values ('"+SG1->Cells[1][i]+"','"+SG1->Cells[2][i].Trim()+"')";
            if (!DB->SendCommand(sql)){return;}
            } else
            {
            sql="update billets.parametr_list set parametr_name='"+SG1->Cells[2][i].Trim()+"' where BINARY parametr='"+SG1->Cells[1][i]+"'";
            if (!DB->SendCommand(sql)){return;}
            }
        }
    existing="";
    sql="select paramid,parametr from billets.parametr_list where BINARY parametr in ("+params+")";
    rez=DB->SendSQL(sql);
    if (!rez){return;}
    rez->First();
    while (!rez->Eof)
        {
        existing=existing+"'"+rez->FieldByName("paramid")->Value+"',";
        rez->Next();
        }
    existing.Delete(existing.Length(),1);
    sql="select id,paramid from billets.zagot_parametrs where id in(select id from billets.zagot_parametrs where paramid in ("+existing+")GROUP BY id HAVING count(id)="+rez->RecordCount+")group by id HAVING count(id)="+rez->RecordCount;
    delete rez; rez=0;
    rez=DB->SendSQL(sql);
    if (!rez){return;}
    rez->First();
    if (rez->RecordCount)
        {
        id=rez->FieldByName("id")->Value;
        }else
        {
        delete rez; rez=0;
        sql="select distinct id from billets.zagot_parametrs order by id DESC limit 0,1";
        TADOQuery *rez=DB->SendSQL(sql);
        if (!rez){return;}
        rez->First();
        id=rez->FieldByName("id")->Value+1;
        for (i=1; i<SG1->RowCount-1; i++)
            {
            sql="insert into billets.zagot_parametrs (id,paramid) select "+IntToStr(id)+",paramid from billets.parametr_list where BINARY parametr='"+SG1->Cells[1][i]+"'";
            if (!DB->SendCommand(sql)){return;}
            }
        }
    delete rez; rez=0;
    sql="insert into billets.raschet_zagot (id,kod,title,formula,type) values('"+IntToStr(id)+"','"+LE5->Text+"','"+CB1->Text+"','"+LE2->Text.Trim()+"','mass')";
    if (!DB->SendCommand(sql)){return;}
    sql="insert into billets.raschet_zagot (id,kod,title,formula,type) values('"+IntToStr(id)+"','"+LE5->Text+"','"+CB1->Text+"','"+LE3->Text.Trim()+"','nrm')";
    if (!DB->SendCommand(sql)){return;}
    sql="insert into billets.razzm_zag (kod,title,Razz) values('"+LE5->Text+"','"+CB1->Text+"','"+LE4->Text.Trim()+"')";
    if (!DB->SendCommand(sql)){return;}
    init();
    }else
    {
    ShowMessage("Необходимо указать название метода расчета и код заготовки для сохранения");
    }
}
void __fastcall TFomul_Editor::BitBtn2Click(TObject *Sender)
{
String sql="Delete from billets.raschet_zagot where kod='"+LE1->Text+"' and title='"+CB1->Text+"'";
DB->SendCommand(sql);
sql="Delete from billets.razzm_zag where kod='"+LE1->Text+"' and title='"+CB1->Text+"'";
DB->SendCommand(sql);
sql="Delete from billets.zagot_parametrs where id not in (select id from billets.raschet_zagot) or paramid not in(select paramid from billets.parametr_list)";
DB->SendCommand(sql);
init();
}
