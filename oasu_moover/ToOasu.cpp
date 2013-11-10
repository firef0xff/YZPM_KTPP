//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ToOasu.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

const int luser=25;
__fastcall TOASUtrasfer::TOASUtrasfer(TComponent* Owner): TForm(Owner),LUser(luser)
{
    ADC->ConnectionString="FILE NAME="+ExtractFileDir(Application->ExeName)+"\\lib\\connect.udl";
    DB=new cSQL(ADC);
    init_interface();
}
__fastcall TOASUtrasfer::TOASUtrasfer(TComponent* Owner,int &_LUser,cSQL *db)
    : TForm(Owner),DB(db),LUser(_LUser)
{
    count++;
    init_interface();
}
__fastcall TOASUtrasfer::TOASUtrasfer(TComponent* Owner,TWinControl *_p,String _name, int &_LUser,cSQL *db)
    : TForm(Owner),DB(db),LUser(_LUser)
{
    count++;
    init_interface();
    // расположение
    BorderStyle=bsNone;
    Align=alClient;
    Parent=_p;
    Name=_name;
    // капча на вкладку
    if(Parent->ClassNameIs("TTabSheet"))
    {
        ((TTabSheet *)Parent)->Caption="Передача данных на АСУ     ";
    }
    Show();
}
__fastcall TOASUtrasfer::~TOASUtrasfer(void)
{
    if (count)
    {
        count--;
    }
}
void TOASUtrasfer::init_interface(void)
{ }


void __fastcall TOASUtrasfer::_tableClick(TObject *Sender)
{
String view="";
switch (_table->ItemIndex)
    {
    case 0:{view="nsi001v";break;}
    case 1:{view="nsi002v";break;}
    case 2:{view="nsi003v";break;}
    case 3:{view="nsi004v";break;}
    case 4:{view="nsi005v";break;}
    case 5:{view="nsi006v";break;}
    case 6:{view="nsi009v";break;}
    case 7:{view="nsi010v";break;}
    default:return;
    }
TADOQuery *rez=DB->SendSQL("select * from oasu."+view);
int i,j;
for (i =0; i < table->RowCount; i++)
    {
    for (j=0; j < table->ColCount; j++)
        {
        table->Cells[j][i]="";
        }
    }
table->RowCount=2;
AutoWidthSG(table);
if (rez)
    {
    table->ColCount=rez->FieldCount+1;
    for (int i=0; i <rez->FieldCount; i++)
        {
        table->Cells[i+1][0]=rez->FieldDefList->operator [](i)->DisplayName;
        }
    if (rez->RecordCount)
        {
        table->RowCount=rez->RecordCount+1;
        for (rez->First(); !rez->Eof; rez->Next())
            {
            for (int i=0; i <rez->FieldCount; i++)
                {
                table->Cells[i+1][rez->RecNo]=rez->FieldByName(rez->FieldDefList->operator [](i)->DisplayName)->Value;
                }
            }
        }
    AutoWidthSG(table);
    }
delete rez;
}
//---------------------------------------------------------------------------

void __fastcall TOASUtrasfer::TS3Show(TObject *Sender)
{
_table->ItemIndex=0;
_tableClick(0);
}
//---------------------------------------------------------------------------

void __fastcall TOASUtrasfer::Button1Click(TObject *Sender)
{
String view="";
switch (_table->ItemIndex)
    {
    case 0:{view="nsi001v";break;}
    case 1:{view="nsi002v";break;}
    case 2:{view="nsi003v";break;}
    case 3:{view="nsi004v";break;}
    case 4:{view="nsi005v";break;}
    case 5:{view="nsi006v";break;}
    case 6:{view="nsi009v";break;}
    case 7:{view="nsi010v";break;}
    default:return;
    }
DB->SendCommand("delete from oasu."+view);
_tableClick(0);
}
//---------------------------------------------------------------------------
void __fastcall TOASUtrasfer::SpeedButton1Click(TObject *Sender)
{
cExcel *rep=new cExcel();
rep->Connect();
rep->SetActiveBooks(rep->Books_New());
rep->SetActiveBook(rep->GetFirstBook());
rep->SetActiveSheets(rep->GetSheets());
rep->SetActiveSheet(rep->GetFirstSheet());

rep->Visible(false);
rep->DisplayAlerts(false);

rep->toCells(1,1,"Обозначение");
rep->toCells(1,2,"Ошибка");
TADOQuery *rez=DB->SendSQL("select * from oasu.report order by obd");
if (rez&&rez->RecordCount)
    {
    for (rez->First(); !rez->Eof; rez->Next())
        {
        int i=rez->RecNo+1;
        rep->toCells(i,1,VinToGost(rez->FieldByName("obd")->Value));
        rep->toCells(i,2,rez->FieldByName("err")->Value.operator UnicodeString());
        }
    }
delete rez;
rep->DisplayAlerts(true);
rep->Visible(true);
delete rep;
}
//---------------------------------------------------------------------------



