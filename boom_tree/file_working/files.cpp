

#include <vcl.h>
#pragma hdrstop

#include "files.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

__fastcall TFileDisigner::TFileDisigner(TComponent* Owner,cSQL *const _DB,const int &_LUser,
                                        const Obd *const det,bool MassAction,const char &_type):
                                        TForm(Owner),LUser(_LUser),type(_type),DB(_DB)
{
//получение ссылки на хранилище файлов
TADOQuery *rez=DB->SendSQL("Select trim(value)as value from administration.settings where property='base'");
base=rez->FieldByName("value")->Value;
// инициализация сетки
SGClear(SG,0);
SG->Cells[1][0]="Файл";
SG->Cells[2][0]="Деталь";
SG->Cells[3][0]="Наличие в базе";
SG->Cells[4][0]="Действие";
SG->Cells[5][0]="Добавлено";
SG->Cells[6][0]="Добавил";
SG->Cells[7][0]="Изменено";
SG->Cells[8][0]="Изменил";
AutoWidthSG(SG);
//инициализация интерфейса
switch (type)
    {
    case 0:    {
            Caption="Добавление файлов к базе";
            N2->Enabled=true;
            save->Enabled=N2->Enabled;
            N1->Caption="Открыть";
            N1->ImageIndex=2;
            open->ImageIndex=N1->ImageIndex;
            break;
            }//загрузка файлов в базу
    case 1:    {
            N2->Enabled=false;
            save->Enabled=N2->Enabled;
            N1->Caption="Сохранить";
            N1->ImageIndex=3;
            open->ImageIndex=N1->ImageIndex;
            this->Caption="Получение файлов из базы";
            break;
            }//получение файлов из базы
    case 2:    {
            N2->Enabled=false;
            save->Enabled=N2->Enabled;
            N1->Caption="Удалить";
            N1->ImageIndex=9;
            open->ImageIndex=N1->ImageIndex;
            this->Caption="Удаление файлов из базы";
            break;
            }//удаление файлов из базы
    default:break;
    }
if ((type==1||type==2)&&det)
    {
    LoadFiles(det,MassAction);
    ShowData();
    }
}
__fastcall TFileDisigner::~TFileDisigner(void)
{
ClearData();
}

void __fastcall TFileDisigner::ClearAllClick(TObject *Sender)
{
//очистка вектора
ClearData();
}
void __fastcall TFileDisigner::OpenClick(TObject *Sender)
{
switch (type)
    {
    case 0:    {
            OpenFiles();
            break;
            }
    case 1:    {
            SaveToPc();
            if (!grid.size())
                {
                ShowMessage("Файлы получены успешно.");
                this->Close();
                }
            break;
            }
    case 2:    {
            //удаление
            Delete();
            if (!grid.size())
                {
                ShowMessage("Файлы удалены успешно.");
                this->Close();
                }
            break;
            }
    default:break;
    }
}
void __fastcall TFileDisigner::SaveClick(TObject *Sender)
{
SaveToBase();
}
void __fastcall TFileDisigner::ClearClick(TObject *Sender)
{
if (grid.size())
    {
    vector <FRowData>::iterator i,j;
    i=grid.begin()+SG->Selection.Top-1;
    j=grid.begin()+SG->Selection.Bottom;
    grid.erase(i,j);
    ShowData();
    }
}

bool            TFileDisigner::ChangeFiles(void)
{
String act,msg;
switch (type)
    {
    case 0:{act="Обновить";msg="Подтвердить замену файлов";break;}
    case 1:{act="";msg="";break;}
    case 2:{act="Удалить";msg="Подтвердить удаление файлов";break;}
    default:break;
    }
for (vector <FRowData>::iterator i=grid.begin(); i!=grid.end(); i++)
    {
    if (i->Get_Action()==act)
        {
        if (MessageDlg(msg,mtWarning,TMsgDlgButtons()<<mbYes<<mbNo,0)==mrYes)
        {return true;}else
        {return false;}
        }
    }
return false;
}
bool            TFileDisigner::CheckData(FRowData *row)
{
for (unsigned int i=0; i!=grid.size(); i++)
    {
    if (grid[i]==*row)
        {
        return true;
        }
    }
return false;
}

void            TFileDisigner::OpenFiles(void)
{
OD->Files->Clear();
OD->FileName="";
OD->Execute();
if (OD->Files->Count)
    {
    for (int i=0; i<OD->Files->Count; i++)
        {
        FRowData *row=new FRowData(DB,LUser,OD->Files->operator [](i),0,base,type);
        if (!CheckData(row))     // проверка на наличие пары деталь файл в массиве
            {
            grid.push_back(*row);
            }
        delete row;
        }
    ShowData();
    }
}
void             TFileDisigner::LoadFiles(const Obd *const det,bool MassAction)
{
if (det)
    {
    if (det->TrueClassName()!="FileRow")
        {
        String sql="";
        if (MassAction) // проанализировать мас акчион
            {// если масс акшен то получить все пары файл-обозначение из узла
            sql="Call constructions.GetFilesForTree('"+String(det->Get_ID())+"')";
            }else
            {// иначе получить только пары файл-обозначение из текущего узла
            sql="Call constructions.GetFiles('"+String(det->Get_ID())+"')";
            }
            // наполниить массив
        TADOQuery *rez=DB->SendSQL(sql);
        if (rez&&rez->RecordCount)
            {
            rez->First();
            while (!rez->Eof)
                {
                FRowData *row=new FRowData(DB,LUser,rez->FieldByName("Name")->Value,rez->FieldByName("idDet")->Value,base,type);
                grid.push_back(*row);
                delete row;
                rez->Next();
                }
            }
        delete rez;
        }else
        {
        FRowData *row=new FRowData(DB,LUser,((FileRow*)det)->Get_FileName(),det->Get_ID(),base,type);
        grid.push_back(*row);
        delete row;
        }
    }
}
void            TFileDisigner::SaveToBase(void)
{
bool allow_change=ChangeFiles();
for (vector <FRowData>::iterator i=grid.begin(); i!=grid.end(); i++)
    {
    if (i->Get_Accept()&&((i->Get_Action()=="Обновить"&&allow_change)||i->Get_Action()=="Добавить"))
        {
        if (i->SaveToBase())
            {
            i=grid.erase(i);
            i--;
            }
        }
    }
ShowData();
}
void            TFileDisigner::SaveToPc(void)
{
SD->FileName="_";
bool result=SD->Execute();
//диалог сохранения

// само сохраненние
if (SD->FileName.Length()&&result)
    {
    String path=ExtractFilePath(SD->FileName);
    for (vector <FRowData>::iterator i=grid.begin(); i!=grid.end(); i++)
        {
        if (i->Get_Action()=="Получить")
            {
            if (i->SaveToPC(path))
                {
                i=grid.erase(i);
                i--;
                }
            }
        }
    }
ShowData();
}
void            TFileDisigner::Delete(void)
{
bool allow_change=ChangeFiles();
for (vector <FRowData>::iterator i=grid.begin(); i!=grid.end(); i++)
    {
    if (i->Get_Action()=="Удалить"&&allow_change)
        {
        if (i->Delete())
            {
            i=grid.erase(i);
            i--;
            }
        }
    }
ShowData();
}

void             TFileDisigner::ShowData (void)
{
SGClear(SG,0);
for (vector <FRowData>::iterator i=grid.begin(); i!=grid.end(); i++)
    {
    SG->Cells[1][SG->RowCount-1]=i->Get_FileName();
    SG->Cells[2][SG->RowCount-1]=i->Get_Text();
    if (i->Get_inbase())
        {
        SG->Cells[3][SG->RowCount-1]="Есть в базе";
        }else
        {
        SG->Cells[3][SG->RowCount-1]="Нет в базе";
        }
    SG->Cells[4][SG->RowCount-1]=i->Get_Action();
    if (i->Get_DateOfCreate().Val!=0)
        {
        SG->Cells[5][SG->RowCount-1]=i->Get_DateOfCreate().DateString();
        }else
        {
        SG->Cells[5][SG->RowCount-1]="";
        }
    SG->Cells[6][SG->RowCount-1]=i->Get_Creator();
    if (i->Get_DateOfUpdate().Val!=0)
        {
        SG->Cells[7][SG->RowCount-1]=i->Get_DateOfUpdate().DateString();
        }else
        {
        SG->Cells[7][SG->RowCount-1]="";
        }
    SG->Cells[8][SG->RowCount-1]=i->Get_Updater();
      //    i->Get_Accept();
    SG->RowCount++;
    }
if (SG->RowCount>2)
    {
    SG->RowCount--;
    }
AutoWidthSG(SG);
}
void             TFileDisigner::ClearData(void)
{
grid.clear();
SGClear(SG,0);
}
void __fastcall TFileDisigner::SGDrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect,
          TGridDrawState State)
{
TStringGrid *sg=(TStringGrid *)Sender;
if (ARow&&ACol&&grid.size())
    {
    if (grid[ARow-1].Get_Accept())
        {
        if (grid[ARow-1].Get_inbase())
            {
            sg->Canvas->Brush->Color=0x00DDFFFF; //clYellow разрешонный узел
            }else
            {
            sg->Canvas->Brush->Color=0x00DDFFDD;//clGreen; // разрешонный узел
            }
        }else
        {
        sg->Canvas->Brush->Color=0x00DDDDFF;// clRed нет доступа
        }
    sg->Canvas->Font->Color=clBlack;
if (ACol>=sg->Selection.Left&&ACol<=sg->Selection.Right&&ARow>=sg->Selection.Top&&ARow<=sg->Selection.Bottom)                                     //выделение
    {
    sg->Canvas->Brush->Color=0x00FFDDDD;//clBlue;
    sg->Canvas->Font->Color=clBlack;
    }
    sg->Canvas->FillRect(Rect);
    sg->Canvas->TextOutW(Rect.left+2,Rect.top+1,sg->Cells[ACol][ARow]);
    }
}

void __fastcall TFileDisigner::SGFixedCellClick(TObject *Sender, int ACol, int ARow)
{
switch (ACol)
    {
    case 1:{FileAsc=!FileAsc;        SortByFile(FileAsc);break;}
    case 2:{ObdAsc=!ObdAsc;          SortByObd(ObdAsc);break;}
    case 3:{InBaseAsc=!InBaseAsc;     SortByInBase(InBaseAsc);break;}
    case 4:{ActionAsc=!ActionAsc;     SortByAction(ActionAsc);break;}
    default:break;
    }
ShowData();
}
void            TFileDisigner::SortByObd    (bool asc)
{
long inc,i,j,seq[40],size=grid.size();
int s;
FRowData TmpRow(DB,LUser,"",0,base,type);
// вычисление последовательности приращений
s = increment(seq, size);
while (s >= 0)
    {
    // сортировка вставками с инкрементами inc[]
    inc = seq[s--];
    for (i = inc; i < size; i++)
        {
        if (asc)
            {
            for (j = i-inc; (j >= 0) && (grid.operator [](j).Get_Obd(true) > grid.operator [](j+inc).Get_Obd(true)); j -= inc)
                {
                TmpRow=grid.operator [](j);
                grid.operator [](j)=grid.operator [](j+inc);
                grid.operator [](j+inc)=TmpRow;
                }
            }else
            {
            for (j = i-inc; (j >= 0) && (grid.operator [](j).Get_Obd(true) < grid.operator [](j+inc).Get_Obd(true)); j -= inc)
                {
                TmpRow=grid.operator [](j);
                grid.operator [](j)=grid.operator [](j+inc);
                grid.operator [](j+inc)=TmpRow;
                }
            }
        
        }
    }
}
void            TFileDisigner::SortByFile    (bool asc)
{
long inc,i,j,seq[40],size=grid.size();
int s;
FRowData TmpRow(DB,LUser,"",0,base,type);
// вычисление последовательности приращений
s = increment(seq, size);
while (s >= 0)
    {
    // сортировка вставками с инкрементами inc[]
    inc = seq[s--];
    for (i = inc; i < size; i++)
        {
        if (asc)
            {
            for (j = i-inc; (j >= 0) && (grid.operator [](j).Get_FileName() > grid.operator [](j+inc).Get_FileName()); j -= inc)
                {
                TmpRow=grid.operator [](j);
                grid.operator [](j)=grid.operator [](j+inc);
                grid.operator [](j+inc)=TmpRow;
                }
            }else
            {
            for (j = i-inc; (j >= 0) && (grid.operator [](j).Get_FileName() < grid.operator [](j+inc).Get_FileName()); j -= inc)
                {
                TmpRow=grid.operator [](j);
                grid.operator [](j)=grid.operator [](j+inc);
                grid.operator [](j+inc)=TmpRow;
                }
            }
        
        }
    }
}
void            TFileDisigner::SortByInBase    (bool asc)
{
long inc,i,j,seq[40],size=grid.size();
int s;
FRowData TmpRow(DB,LUser,"",0,base,type);
// вычисление последовательности приращений
s = increment(seq, size);
while (s >= 0)
    {
    // сортировка вставками с инкрементами inc[]
    inc = seq[s--];
    for (i = inc; i < size; i++)
        {
        if (asc)
            {
            for (j = i-inc; (j >= 0) && (grid.operator [](j).Get_inbase() > grid.operator [](j+inc).Get_inbase()); j -= inc)
                {
                TmpRow=grid.operator [](j);
                grid.operator [](j)=grid.operator [](j+inc);
                grid.operator [](j+inc)=TmpRow;
                }
            }else
            {
            for (j = i-inc; (j >= 0) && (grid.operator [](j).Get_inbase() < grid.operator [](j+inc).Get_inbase()); j -= inc)
                {
                TmpRow=grid.operator [](j);
                grid.operator [](j)=grid.operator [](j+inc);
                grid.operator [](j+inc)=TmpRow;
                }
            }
        
        }
    }
}
void            TFileDisigner::SortByAction    (bool asc)
{
long inc,i,j,seq[40],size=grid.size();
int s;
FRowData TmpRow(DB,LUser,"",0,base,type);
// вычисление последовательности приращений
s = increment(seq, size);
while (s >= 0)
    {
    // сортировка вставками с инкрементами inc[]
    inc = seq[s--];
    for (i = inc; i < size; i++)
        {
        if (asc)
            {
            for (j = i-inc; (j >= 0) && (grid.operator [](j).Get_Action() > grid.operator [](j+inc).Get_Action()); j -= inc)
                {
                TmpRow=grid.operator [](j);
                grid.operator [](j)=grid.operator [](j+inc);
                grid.operator [](j+inc)=TmpRow;
                }
            }else
            {
            for (j = i-inc; (j >= 0) && (grid.operator [](j).Get_Action() < grid.operator [](j+inc).Get_Action()); j -= inc)
                {
                TmpRow=grid.operator [](j);
                grid.operator [](j)=grid.operator [](j+inc);
                grid.operator [](j+inc)=TmpRow;
                }
            }
        
        }
    }
}
int             TFileDisigner::increment    (long inc[], long size)
{
int p1, p2, p3, s;
p1 = p2 = p3 = 1;
s = -1;
do
    {
    if (++s % 2)
        {
        inc[s] = 8*p1 - 6*p2 + 1;
        } else
        {
        inc[s] = 9*p1 - 9*p3 + 1;
        p2 *= 2;
        p3 *= 2;
        }
    p1 *= 2;
    }
while(3*inc[s] < size);
return s > 0 ? --s : 0;
}

void __fastcall TFileDisigner::SGDblClick(TObject *Sender)
{
if (!grid.size()) {return;} //проверка заполненности массива
TStringGrid *sg=(TStringGrid *)Sender;
int ACol,ARow;
TPoint s;                  //вычисление кликнутой ячейки
GetCursorPos(&s);
s=sg->ScreenToClient(s);
sg->MouseToCell(s.X,s.Y,ACol,ARow);
if (ARow<=0) {return;}    //проверка клика
switch (ACol)
    {
    case 2:{SetNewObd(ACol,ARow);break;}
    case 4:{SetNewAction(ACol,ARow);break;}
    default:return;
    }
}
void            TFileDisigner::SetNewObd(int ACol,int ARow)
{
if (type) {return;}//отключение обоих функций для режима восстановления/удаления файлов
//if (!grid[ARow-1].Get_Accept()&&grid[ARow-1].Get_inbase()) {return;}    //проверка на наличие доступа к детали и файла в базе
TRect R=SG->CellRect(ACol,ARow);
// проверка на наличие мыши в зоне
R.Left=R.Left+SG->Left;
R.Right=R.Right+SG->Left;
R.Top=R.Top+SG->Top;
R.Bottom=R.Bottom+SG->Top;
ED->Left=R.Left+1;
ED->Top=R.Top+1;
ED->Width=(R.Right+1)-R.Left;
ED->Height=(R.Bottom+1)-R.Top;
ED->Visible=true;
ED->SetFocus();
}
void            TFileDisigner::SetNewAction(int ACol,int ARow)
{
if (!grid[ARow-1].Get_Accept()) {return;}
TRect R=SG->CellRect(ACol,ARow);
R.Left=R.Left+SG->Left;
R.Right=R.Right+SG->Left;
R.Top=R.Top+SG->Top;
R.Bottom=R.Bottom+SG->Top;
CB->Left=R.Left+1;
CB->Top=R.Top+1;
CB->Width=(R.Right+1)-R.Left;
CB->Height=(R.Bottom+1)-R.Top;
FillCombo(ARow-1);
CB->Visible=true;
CB->SetFocus();
}

void            TFileDisigner::FillCombo(int pos)
{
CB->Clear();
CB->Items->Add("Нет");
switch (type)
    {
    case 0:    {
            if (grid[pos].Get_inbase())
                {
                CB->Items->Add("Обновить");
                }else
                {
                CB->Items->Add("Добавить");
                }
            break;
            }
    case 1:    {
            if (grid[pos].Get_inbase())
                {
                CB->Items->Add("Получить");
                }
            break;
            }
    case 2:    {
            if (grid[pos].Get_inbase())
                {
                CB->Items->Add("Удалить");
                }
            break;
            }
    default:break;
    }
}
void __fastcall TFileDisigner::CBExit(TObject *Sender)
{
TComboBox *cb=(TComboBox *)Sender;
cb->Clear();
cb->Text="";
cb->Hide();
}
void __fastcall TFileDisigner::CBChange(TObject *Sender)
{
TComboBox *cb=(TComboBox *)Sender;
int pos=SG->Selection.Top-1;
grid[pos].SetAction(CB->Text);
UpdRow(pos+1);
cb->Hide();
}

void __fastcall TFileDisigner::EDExit(TObject *Sender)
{
TEdit *ed=(TEdit *)Sender;
ed->Text="";
ed->Hide();
}
void __fastcall TFileDisigner::EDKeyPress(TObject *Sender, wchar_t &Key)
{
TEdit *ed=(TEdit *)Sender;
if (Key==13)
    {
    int pos=SG->Selection.Top-1;
    grid[pos].UpdateVal(ed->Text);
    UpdRow(pos+1);
    ed->Hide();
    }
}

void            TFileDisigner::UpdRow(int ARow)
{
SG->Cells[1][ARow]=grid[ARow-1].Get_FileName();
SG->Cells[2][ARow]=grid[ARow-1].Get_Text();
if (grid[ARow-1].Get_inbase())
    {
    SG->Cells[3][ARow]="Есть в базе";
    }else
    {
    SG->Cells[3][ARow]="Нет в базе";
    }
SG->Cells[4][ARow]=grid[ARow-1].Get_Action();
if (grid[ARow-1].Get_DateOfCreate().Val!=0)
    {
    SG->Cells[5][ARow]=grid[ARow-1].Get_DateOfCreate().DateString();
    }else
    {
    SG->Cells[5][ARow]="";
    }
SG->Cells[6][ARow]=grid[ARow-1].Get_Creator();
if (grid[ARow-1].Get_DateOfUpdate().Val!=0)
    {
    SG->Cells[7][ARow]=grid[ARow-1].Get_DateOfUpdate().DateString();
    }else
    {
    SG->Cells[7][ARow]="";
    }
SG->Cells[8][ARow]=grid[ARow-1].Get_Updater();
}

void __fastcall TFileDisigner::SGKeyPress(TObject *Sender, wchar_t &Key)
{
if (Key==13)
    {
    SGDblClick(Sender);
    }
}
