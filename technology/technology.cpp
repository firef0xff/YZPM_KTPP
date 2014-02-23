// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "technology.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
// ---------------------------------------------------------------------------

__fastcall TTechWnd::TTechWnd(TComponent *Owner, TWinControl *_p, String _name,
    int &_LUser, cSQL *db):TFrame(Owner), DB(db), LUser(_LUser), Ldet(0),
    Info(0), Selector(0)
{
    log.push_back(Time().TimeString()+"--"+String((int)this)+"--"+"TTechWnd("+
        String((int)Owner)+","+String((int)_p)+","+_name+","+String(_LUser)+","+
        String((int)db)+")");
    Selector=new TObdSelector(this, (ClassConnector *)this, Panel5, db);
    count++ ;
    // расположение
    Align=alClient;
    Parent=_p;
    Name=_name;
    Init();
    // загрузка данных по контролю, еденицам измерения
    Load_support_info();
    // инициализация заголовков таблиц
    operations->Cells[1][0]="Цех";
    operations->Cells[2][0]="Уч.";
    operations->Cells[3][0]="Опер.";
    operations->Cells[4][0]="Код, наименование операций";
    operations->Cells[5][0]="Обозначение документа";
    operations->Cells[6][0]="Код";
    operations->Cells[7][0]="Наименование";
    operations->Cells[8][0]="СМ";
    operations->Cells[9][0]="К.шт.";
    operations->Cells[10][0]="Проф";
    operations->Cells[11][0]="КР";
    operations->Cells[12][0]="Р";
    operations->Cells[13][0]="КОИД";
    operations->Cells[14][0]="ЕН";
    operations->Cells[15][0]="УТ";
    operations->Cells[16][0]="Т п.з.";
    operations->Cells[17][0]="Т шт.";
    operations->Cells[18][0]="ОП";
    AutoWidthSG(operations);
    instrum->Cells[1][0]="Наименвание инструмента";
    instrum->Cells[2][0]="Номер";
    AutoWidthSG(instrum);
    // капча на вкладку
    if(Parent->ClassNameIs("TTabSheet"))
    {
        ((TTabSheet *)Parent)->Caption="Технология     ";
    }
}

__fastcall TTechWnd::~TTechWnd()
{
    log.push_back(Time().TimeString()+"--"+String((int)this)+"--"+
        "~TTechWnd()");
    if(Ldet)
    {
        DB->SendCommand("Call constructions.unblock('"+(String)Ldet->Get_ID()+
            "','"+LUser+"')");
    }
    count-- ;
    delete Info;
    Info=0;
}

void TTechWnd::Init(void)
{
    log.push_back(Time().TimeString()+"--"+String((int)this)+"--"+"Init()");

    TehSave=false;
    TehRead=false;
    TehEdit=false;
    TehDel=false;
    NormEdit=false;
    String sql="call administration.Get_Rights('"+String(LUser)+"')";
    TADOQuery *rez=DB->SendSQL(sql);
    if(rez&&rez->RecordCount)
    {
        for (rez->First(); !rez->Eof; rez->Next())
        {
            const String val=rez->FieldByName("progname")->Value;
            if (val=="TehSave")
            {
                TehSave=true;
            }
            if (val=="TehRead")
            {
                TehRead=true;
            }
            if (val=="TehEdit")
            {
                TehEdit=true;
            }
            if (val=="TehDel")
            {
                TehDel=true;
            }
            if (val=="NormEdit")
            {
                NormEdit=true;
            }
        }
    }
    delete rez;
    if(!TehRead)
    {
        TehSave=false;
        TehEdit=false;
        TehDel=false;
        NormEdit=false;
    }
}

void TTechWnd::Load_support_info(void)
{
    log.push_back(Time().TimeString()+"--"+String((int)this)+"--"+
        "Load_support_info()");
    ei->Items->Clear();
    TADOQuery *rez=DB->SendSQL("Call catalogs.Get_ei_list('"+
        (String)ei_opt->ItemIndex+"')");
    if(rez&&rez->RecordCount)
    {
        for(rez->First(); !rez->Eof; rez->Next())
        {
            ei->Items->AddObject(rez->FieldByName("text")->Value,
                (TObject *)rez->FieldByName("id")->Value.operator int());
        }
    }
    delete rez;
    Check_ei_box();
    rez=DB->SendSQL("Call catalogs.Get_control()");
    control->Items->Clear();
    if(rez&&rez->RecordCount)
    {
        for(rez->First(); !rez->Eof; rez->Next())
        {
            control->Items->AddObject(rez->FieldByName("text")->Value,
                (TObject *)rez->FieldByName("id")->Value.operator int());
        }
    }
}

void TTechWnd::Check_ei_box(void)
{
    log.push_back(Time().TimeString()+"--"+String((int)this)+"--"+
        "Check_ei_box()");
    if(Info)
    {
        if(ei->Items->IndexOfObject((TObject *)Info->Get_ei())== -1)
        {
            ei->Items->AddObject(Info->Get_eiName(), (TObject *)Info->Get_ei());
        }
    }
}

void __fastcall TTechWnd::ei_optClick(TObject *Sender)
{
    log.push_back(Time().TimeString()+"--"+String((int)this)+"--"+
        "ei_optClick()");
    Load_support_info(); // выбор другого режима наполнения
    if(Info)
    {
        ShowDetInfo();
    }
}

// загрузка и очистка
void TTechWnd::Load(const Obd * const det)
{
    log.push_back(Time().TimeString()+"--"+String((int)this)+"--"+"Load("+
        String((int)det)+")");
    if(TehRead&&(!Ldet||det->Get_ID()!=Ldet->Get_ID()))
    { // процесс загрузки
        bool accept=false;
        if(Ldet)
        {
            accept=Close_teh(); // попытка закрыть открытую технологию
        }
        else
        {
            accept=true;
        }
        if(accept)
        {
            delete Ldet;
            Ldet=new Obd(*det);
            delete Info;
            Info=0;
            Info=new DtInfo(DB, Ldet->Get_ID(), LUser);
            Check_ei_box();
            ReadOnly= !(Info->Get_Access()*TehSave*(TehEdit+NormEdit));
            if(!ReadOnly)
            {
                DB->SendCommand("Call constructions.block('"+
                    (String)Ldet->Get_ID()+"','"+LUser+"')");
            }
            InfoColors();
            ShowDetInfo();
            ShowOperations();
        }
        else
        {
            Load_sel(new Obd(*Ldet));
        }
    }
};

bool TTechWnd::Close_teh(void)
{
    log.push_back(Time().TimeString()+"--"+String((int)this)+"--"+
        "Close_teh()");
    TimerTimer(0);
    // проверка на необходимость сохранения
    bool closed=true;
    if(Ldet&&Info&& !ReadOnly)
    {
        operations->SetFocus();
        perexod->Lines->Clear();
        SGClear(instrum, 2);
        if(Info->Need_Save())
        { // вопрос на сохранение
            String msg;
            int result;
            result=MessageDlg("Технология "+Ldet->Get_Text()+
                " нуждается в сохранении. Сохранить?", mtWarning,
                TMsgDlgButtons()<<mbYes<<mbNo<<mbCancel, 0);
            if(result==mrYes)
            {
                if(Info->Can_Save(msg))
                {
                    operSave(operations->Row);
                    closed=Info->SaveData();
                    if(!closed)
                    {
                        ShowMessage("Невозможно сохранить технологию "+
                            Ldet->Get_Text());
                    }
                    else
                    {
                        DB->SendCommand("Call constructions.unblock('"+
                            (String)Ldet->Get_ID()+"','"+LUser+"')");
                        delete Info;
                        Info=0;
                    }
                }
                else
                {
                    MessageDlg(msg, mtError, TMsgDlgButtons()<<mbOK, 0);
                    closed=false;
                }
            }
            else
            {
                if(result==mrNo)
                {
                    closed=true;
                    DB->SendCommand("Call constructions.unblock('"+
                        (String)Ldet->Get_ID()+"','"+LUser+"')");
                    delete Info;
                    Info=0;
                }
                else
                {
                    closed=false;
                }
            }

        }
        else
        {
            DB->SendCommand("Call constructions.unblock('"+(String)Ldet->Get_ID
                ()+"','"+LUser+"')");
            delete Info;
            Info=0;
        }
    }
    return closed;
}

void TTechWnd::Save_tex(void)
{
    log.push_back(Time().TimeString()+"--"+String((int)this)+"--"+"Save_tex()");
    TimerTimer(0);
    if(Ldet&&Info&& !ReadOnly)
    {
        operations->SetFocus();
        perexod->Lines->Clear();
        SGClear(instrum, 2);
        if(Info->Need_Save())
        { // вопрос на сохранение
            String msg;
            if(Info->Can_Save(msg))
            {
                operSave(operations->Row);
                if(Info->SaveData())
                {
                    delete Info;
                    Info=0;
                    Info=new DtInfo(DB, Ldet->Get_ID(), LUser);
                    Check_ei_box();
                    InfoColors();
                    ShowDetInfo();
                    ShowOperations();
                }
                else
                {
                    ShowMessage("Невозможно сохранить технологию "+
                        Ldet->Get_Text());
                }
            }
            else
            {
                MessageDlg(msg, mtError, TMsgDlgButtons()<<mbOK, 0);
            }
        }
    }
}

void __fastcall TTechWnd::SavebtnClick(TObject *Sender)
{
    log.push_back(Time().TimeString()+"--"+String((int)this)+"--"+
        "SavebtnClick("+String((int)Sender)+")");
    Save_tex();
}

// инормация о детали
void TTechWnd::ShowDetInfo(void)
{
    log.push_back(Time().TimeString()+"--"+String((int)this)+"--"+
        "ShowDetInfo()");
    creator->Caption="Разработал "+Info->Get_CreateUser()+" "+
        Info->Get_CreateDate();
    updater->Caption="Редактировал "+Info->Get_ChangeUser()+" "+
        Info->Get_ChangeDate();
    access->Caption= !ReadOnly?"Полный доступ":"Только чтение";
    // общие параметры
    DT_Name->Caption=Ldet->Get_Name();
    napr->Text=Info->Get_napr();
    rasceh->Text=Info->Get_pm();

    // параметры детали
    masd->Text=Trim(String(Info->Get_masd())+" "+Info->Get_eiName());
    ei->ItemIndex=ei->Items->IndexOf(Info->Get_eiName());
    ei->Hint=Info->Get_ei();
    ShowMatInfo();
    // параметры заготовки
    kz->Text=Info->Get_vz();
    kz->Hint=Info->Get_vzName();
    razmzagot->Text=Info->Get_razz();
    kdz->Text=Info->Get_kdz();
    masz->Text=Trim(String(Info->Get_masz())+" "+Info->Get_eiName());
    norma->Text=Trim(String(Info->Get_nrm())+" "+Info->Get_eiName());
}

void TTechWnd::ShowMatInfo(void)
{
    log.push_back(Time().TimeString()+"--"+String((int)this)+"--"+
        "ShowMatInfo()");
    L1->Caption="";
    L2->Caption="";
    L3->Caption="";
    L4->Caption="";
    obm->Text="";
    TADOQuery *rez=
        DB->SendSQL("Call sklad.Get_Material('"+
        GostToVin(Info->Get_obm())+"')");
    if(rez&&rez->RecordCount)
    {
        L1->Caption=rez->FieldByName("l1")->Value;
        L3->Caption=rez->FieldByName("l3")->Value;
        L4->Caption=rez->FieldByName("l4")->Value;
        L3->Left=L1->Left+L1->Width+5;
        L4->Left=L1->Left+L1->Width+5;
        L2->Left=L1->Left+L1->Width+5;
        while(L2->Caption.Length()<L3->Caption.Length()||L2->Caption.Length()<
            L4->Caption.Length())
        {
            L2->Caption=L2->Caption+"-";
        }
        obm->Text=Info->Get_obm();
    }
}

void TTechWnd::ShowOperations(void)
{
    log.push_back(Time().TimeString()+"--"+String((int)this)+"--"+
        "ShowOperations()");
    SGClear(operations, 3);
    int rows=operations->RowCount-1;
    if(Info&&Info->Get_Operations())
    {//проверка наличия списка операций и вообще на загруженость технологии
        for(OperRow*i=Info->Get_Operations()->Get_First(); i; i=i->Get_Next())
        {
            if(i->isUsed())//показывает только не удаляемые операции
            {
                /*
                При наличии списка только удаленных операций указатель на массив не будет указан         Warning !!!!!!!!!!!!1
                */
                int str=0;
                operations->Cells[0][rows]="";
                operations->Cells[1][rows]=i->Get_ceh();
                operations->Cells[2][rows]=i->Get_uch();
                operations->Cells[3][rows]=i->Get_opr();
                operations->Cells[4][rows]=i->Get_OprKod()+" "+i->Get_OprName();
                operations->Cells[5][rows]=i->Get_Instruct();
                operations->Cells[6][rows]=i->Get_oboID();
                operations->Cells[7][rows]=i->Get_OboName();
                operations->Cells[19][rows]=(String)(unsigned __int64)i;// указатель на операцию

                operations->Cells[21][rows+str]=(String)str;// номер строки операции

                // operations->Cells[22][rows]=i->Get_action();
                // найти см=ttp ут=kvn оп=kts
                if(i->Get_nrm())
                {//проверка на наличие норм в операции
                    for(NrmRow*j=i->Get_nrm()->Get_First(); j; j=j->Get_Next())
                    {
                        if(j->isUsed())
                        {//показывает только не удаляемые нормы
                            /*
                            При наличии списка удаленных норм указатель на массив не будет указан            Warning !!!!!!!!!!!!1
                            */
                            operations->Cells[0][rows+str]="";
                            operations->Cells[8][rows+str]=j->Get_Ttp();
                            operations->Cells[9][rows+str]=
                                (String)j->Get_Ksht();
                            operations->Cells[10][rows+str]=j->Get_Prof();
                            operations->Cells[11][rows+str]=j->Get_Krop();
                            operations->Cells[12][rows+str]=j->Get_Rr();
                            operations->Cells[13][rows+str]=
                                (String)j->Get_Kolod();
                            operations->Cells[14][rows+str]=j->Get_En();
                            operations->Cells[15][rows+str]=
                                j->Get_Kts()+"/"+j->Get_Kvn();
                            operations->Cells[16][rows+str]=
                                (String)j->Get_Tpz();
                            operations->Cells[17][rows+str]=
                                (String)j->Get_Tsht();
                            operations->Cells[19][rows+str]=
                                (String)(unsigned __int64)i;
                            // указатель на операцию
                            operations->Cells[20][rows+str]=
                                (String)(unsigned __int64)j;
                            // указатель на норму
                            operations->Cells[21][rows+str]=(String)str;
                            // номер строки операции
                            // operations->Cells[23][rows+str]=i->Get_action();
                            // operations->Cells[18][rows+str]="ОП";
                            str++ ;
                        }
                    }
                    if(str>0)
                    {
                        str-- ;
                    }
                }
                else
                {
                    str=0;
                }
                rows+=str+1;
            }
        }
        ShowData(Info->Get_Operations()->Get_First());
    }
    else
    {
        SetDefaultData();
    }
    operations->RowCount=rows+1;
    operations->Cells[0][rows]="*";
    AutoWidthSG(operations);
}

void TTechWnd::ShowData(OperRow *opr)
{
    log.push_back(Time().TimeString()+"--"+String((int)this)+"--"+"ShowData("+
        String((int)opr)+")");
    perexod->Lines->Clear();
    SGClear(instrum,1);
    strpLabel->Caption="Строповка";
    tara->Text="";
    tara->Tag=0;
    SetDefaultData();
    if(opr->isUsed())
    {
        // переходы
        perexod->Paragraph->Numbering=nsBullet;
        if(opr->Get_perex())
        {
            for(PerexRow*i=opr->Get_perex()->Get_First(); i; i=i->Get_Next())
            {
                if(i->isUsed())
                {
                    perexod->Lines->Add(i->Get_Text());
                }
            }
        }
        // инструмент
        if(opr->Get_instrum())
        {
            int rows=1;
            for(InstrumRow*i=opr->Get_instrum()->Get_First(); i;
            i=i->Get_Next())
            {
                if(i->isUsed())
                {
                    instrum->Cells[3][rows]=(String)((int)i);
                    instrum->Cells[2][rows]=i->Get_kod();
                    instrum->Cells[1][rows]=i->Get_Text();
                    instrum->Cells[0][rows]="";
                    rows++ ;
                }
            }
            instrum->RowCount=rows+1;
            instrum->Cells[0][rows]="*";
            AutoWidthSG(instrum);
        }
        else
        {
            instrum->Cells[0][1]="*";
        }
        // строповка и прочее
        if(opr->Get_Strop()!="")
        {
            strpLabel->Caption="Строповка по РТМ 2103-11-75 чертеж:";
        }
        else
        {
            strpLabel->Caption="Строповка";
        }
        strop->Text=opr->Get_Strop();
        tara->Text=opr->Get_Tara();
        tara->Tag=opr->Get_idtar();
        control->ItemIndex=control->Items->IndexOfObject
            ((TObject *)opr->Get_id_cntrl());
    }
}

// --редактирование Info
// ei
void __fastcall TTechWnd::eiClick(TObject *Sender)
{
    log.push_back(Time().TimeString()+"--"+String((int)this)+"--"+"eiClick("+
        String((int)Sender)+")");
    if(Info)
    {
        Info->Set_ei((int)ei->Items->Objects[ei->ItemIndex]);
        ShowDetInfo();
        InfoColors();
    }
}

// масса детали
void __fastcall TTechWnd::masdEnter(TObject *Sender)
{
    log.push_back(Time().TimeString()+"--"+String((int)this)+"--"+"masdEnter("+
        String((int)Sender)+")");
    if(Info)
    {
        masd->Text=String(Info->Get_masd());
    }
}

void __fastcall TTechWnd::masdExit(TObject *Sender)
{
    log.push_back(Time().TimeString()+"--"+String((int)this)+"--"+"masdExit("+
        String((int)Sender)+")");
    if(Info)
    {
        if(masd->Tag)
        {
            Info->Set_masd(masd->Text.ToDouble());
        }
        InfoColors();
        ShowDetInfo();
    }
}

void __fastcall TTechWnd::DoubleFildChange(TObject *Sender)
{
    log.push_back(Time().TimeString()+"--"+String((int)this)+"--"+
        "DoubleFildChange("+String((int)Sender)+")");
    TLabeledEdit *t=(TLabeledEdit *)Sender;
    if(Info&&t->Focused())
    {
        try
        {
            String d_s=Decimal_Separator==","?".":",";
            t->Text=Replace(t->Text, d_s, Decimal_Separator);
            t->SelStart=t->Text.Length();
            t->Text.ToDouble();
            t->Tag=1;
        }
        catch(...)
        {
            t->Tag=0;
            t->Text="";
        }
    }
}

// -масса заготовки
void __fastcall TTechWnd::maszEnter(TObject *Sender)
{
    log.push_back(Time().TimeString()+"--"+String((int)this)+"--"+"maszEnter("+
        String((int)Sender)+")");
    if(Info)
    {
        masz->Text=String(Info->Get_masz());
    }
}

void __fastcall TTechWnd::maszExit(TObject *Sender)
{
    log.push_back(Time().TimeString()+"--"+String((int)this)+"--"+"maszExit("+
        String((int)Sender)+")");
    if(Info)
    {
        if(masz->Tag)
        {
            Info->Set_masz(masz->Text.ToDouble());
        }
        InfoColors();
        ShowDetInfo();
    }
}

// -Норма расхода
void __fastcall TTechWnd::normaEnter(TObject *Sender)
{
    log.push_back(Time().TimeString()+"--"+String((int)this)+"--"+"normaEnter("+
        String((int)Sender)+")");
    if(Info)
    {
        norma->Text=String(Info->Get_nrm());
    }
}

void __fastcall TTechWnd::normaExit(TObject *Sender)
{
    log.push_back(Time().TimeString()+"--"+String((int)this)+"--"+"normaExit("+
        String((int)Sender)+")");
    if(Info)
    {
        if(norma->Tag)
        {
            Info->Set_nrm(norma->Text.ToDouble());
        }
        InfoColors();
        ShowDetInfo();
    }
}

// -Направление
void __fastcall TTechWnd::naprChange(TObject *Sender)
{
    log.push_back(Time().TimeString()+"--"+String((int)this)+"--"+"naprChange("+
        String((int)Sender)+")");
    if(Info)
    {
        if(napr->Text.Length()==napr->MaxLength)
        {
            Info->Set_napr(napr->Text);
            InfoColors();
        }
    }
}

void __fastcall TTechWnd::naprExit(TObject *Sender)
{
    log.push_back(Time().TimeString()+"--"+String((int)this)+"--"+"naprExit("+
        String((int)Sender)+")");
    if(Info)
    {
        InfoColors();
        napr->Text=Info->Get_napr();
    }
}

// -Материал заготовки
void __fastcall TTechWnd::obmChange(TObject *Sender)
{
    log.push_back(Time().TimeString()+"--"+String((int)this)+"--"+"obmChange("+
        String((int)Sender)+")");
    if(Info)
    {
        InfoColors();
    }
}

void __fastcall TTechWnd::obmExit(TObject *Sender)
{
    log.push_back(Time().TimeString()+"--"+String((int)this)+"--"+"obmExit("+
        String((int)Sender)+")");
    if(Info)
    {
        InfoColors();
        TADOQuery *rez=
            DB->SendSQL("Call sklad.Get_Material('"+GostToVin(obm->Text)+"')");
        if(rez&&rez->RecordCount)
        {
            if(Info->Get_obm()!=obm->Text.Trim())
            {
                Info->Set_obm(obm->Text);
                Info->Set_ei(0);
            }
            // Info->Set_ei(rez->FieldByName("ei")->Value);
        }
        ShowDetInfo();
        delete rez;
    }
}

// -код заготовки
void __fastcall TTechWnd::kzChange(TObject *Sender)
{
    log.push_back(Time().TimeString()+"--"+String((int)this)+"--"+"kzChange("+
        String((int)Sender)+")");
    if(Info)
    {
        if(kz->Text.Length()==kz->MaxLength)
        {
            Info->Set_vz(kz->Text.ToInt());
            kz->Text=(String)Info->Get_vz();
            kz->Hint=Info->Get_vzName();
            InfoColors();
        }
    }
}

void __fastcall TTechWnd::kzExit(TObject *Sender)
{
    log.push_back(Time().TimeString()+"--"+String((int)this)+"--"+"kzExit("+
        String((int)Sender)+")");
    if(Info)
    {
        InfoColors();
        kz->Text=(String)Info->Get_vz();
        kz->Hint=Info->Get_vzName();
    }
}

// -количество деталей
void __fastcall TTechWnd::kdzChange(TObject *Sender)
{
    log.push_back(Time().TimeString()+"--"+String((int)this)+"--"+"kdzChange("+
        String((int)Sender)+")");
    if(Info)
    {
        Info->Set_kdz(kdz->Text.ToIntDef(1));
        InfoColors();
    }
}

// -профиль и размеры
void __fastcall TTechWnd::razmzagotChange(TObject *Sender)
{
    log.push_back(Time().TimeString()+"--"+String((int)this)+"--"+
        "razmzagotChange("+String((int)Sender)+")");
    if(Info)
    {
        Info->Set_razz(razmzagot->Text);
        InfoColors();
    }
}

// -цветоиндикация
// --зеленый готово для сохранения
// --красный конфликт значений
void TTechWnd::InfoColors(void)
{
    log.push_back(Time().TimeString()+"--"+String((int)this)+"--"+
        "InfoColors()");
    // общие параметры
    int good_color=0x00DDFFDD, bad_color=0x00DDDDFF;
    if(Info->Get_napr()=="")
    {
        napr->Color=bad_color;
    }
    else
    {
        napr->Color=good_color;
    }
    double m1=Info->Get_masd(), m3=Info->Get_nrm(), m2=Info->Get_masz();
    if(m1==0||m2==0||m3==0||m1>m2||m1>m3||m2>m3)
    {
        masd->Color=bad_color;
        masz->Color=bad_color;
        norma->Color=bad_color;
    }
    else
    {
        masd->Color=good_color;
        masz->Color=good_color;
        norma->Color=good_color;
        kim->Text=String(m1/m3).SubString(1, 6);
    }
    if(!Info->Get_ei())
    {
        ei->Color=bad_color;
    }
    else
    {
        ei->Color=good_color;
    }
    if(Info->Get_obm().Trim()=="")
    {
        obm->Color=bad_color;
    }
    else
    {
        obm->Color=good_color;
    }
    if(!Info->Get_vz())
    {
        kz->Color=bad_color;
    }
    else
    {
        kz->Color=good_color;
    }
    if(!Info->Get_razz().Length())
    {
        razmzagot->Color=bad_color;
    }
    else
    {
        razmzagot->Color=good_color;
    }
    if(!Info->Get_kdz())
    {
        kdz->Color=bad_color;
    }
    else
    {
        kdz->Color=good_color;
    }
}

// -работа с сеткой
void __fastcall TTechWnd::operationsSelectCell(TObject *Sender, int ACol,
    int ARow, bool &CanSelect)
{
    log.push_back(Time().TimeString()+"--"+String((int)this)+"--"+
        "razmzagotChange("+String((int)Sender)+","+(String)ACol+","+
        (String)ARow+")");
    int pRow=operations->Row;
    // доступ на изменение ячеек
    /* Блокировка гриды */
    if((ACol&&ACol<8))
    {
        if(!TehEdit||ReadOnly)
        {
            operations->Options=operations->Options>>goEditing;
        }
        else
        {
            operations->Options=operations->Options<<goEditing;
        }
    }
    else
    {
        if(!NormEdit||ReadOnly)
        {
            operations->Options=operations->Options>>goEditing;
        }
        else
        {
            operations->Options=operations->Options<<goEditing;
        }
    }
    GreedClickControl(ACol);
    if(pRow==ARow)
    {   //не произошол переход на другую сторку
        return;
    }
    // АВТОСЕЙФ
    if(Info)
    {
        if(operSave(pRow))
        {
            UpdGreedData(pRow);
        }
        rasceh->Text=Info->Get_pm();


        // получение новых свойств
        if(operations->Cells[19][ARow]!="") // указатель на операцию
        {
            ShowData((OperRow *)operations->Cells[19][ARow].ToInt());
        }
        else
        {
            SetDefaultData();
        }
    }
}

void TTechWnd::SetDefaultData(void)
{
    log.push_back(Time().TimeString()+"--"+String((int)this)+"--"+
        "SetDefaultData()");
    control->ItemIndex=1;
}

// сохранение операции и норм
bool TTechWnd::operSave(int nRow)
{
    log.push_back(Time().TimeString()+"--"+String((int)this)+"--"+"operSave("+
        String(nRow)+")");
    bool new_opr=false, new_nrm=false, can_opr_save=false, can_nrm_save=false,
        save=false;
    if(operations->Cells[19][nRow]=="")
    {
        new_opr=true;
    }
    if((operations->Cells[1][nRow]!=""||operations->Cells[2][nRow]!=""||
        operations->Cells[3][nRow]!=""||operations->Cells[4][nRow]!=""||
        operations->Cells[5][nRow]!=""||operations->Cells[6][nRow]!="")&&
        (operations->Cells[21][nRow]==""||operations->Cells[21][nRow]=="0"))
    {//проверка на наличие информации у операции для сохранения
        can_opr_save=true;
    }
    if(operations->Cells[20][nRow]=="")
    { //проверка на наличие нормы по наличию указателя
        //(вспомним что там Warning т.к. указатель не показывается если массив норм весь на удаление)    Warning!!!!
        //на этапе присоединения нормы вспомним об этом
        new_nrm=true;
        if((operations->Cells[8][nRow]!=""||operations->Cells[9][nRow]!=""||
            operations->Cells[10][nRow]!=""||operations->Cells[11][nRow]!=""||
            operations->Cells[12][nRow]!=""||operations->Cells[13][nRow]!=""||
            operations->Cells[14][nRow]!=""||operations->Cells[15][nRow]!=""||
            operations->Cells[16][nRow]!=""||
            operations->Cells[17][nRow]!="") /* &&
             (can_opr_save||
             operations->Cells[19][nRow]!="") */)
        {
            can_nrm_save=true;
        }
    }
    // подготовка данных  для сохранения оперции
    int idtar=tara->Tag, id_cntrl=
        (int)control->Items->Objects[control->ItemIndex];
    String     ceh=operations->Cells[1][nRow].Trim(),
            uch=operations->Cells[2][nRow].Trim(),
            Opr=operations->Cells[3][nRow].Trim(),
            oboID=operations->Cells[6][nRow].Trim(),
            OboName=operations->Cells[7][nRow].Trim(),
            tmp=operations->Cells[4][nRow],
            OprName, OprKod,
            Strop=strop->Text.Trim(),
            Tara=tara->Text.Trim(),
            Control=control->Items->operator[](control->ItemIndex),
            Instruct=operations->Cells[5][nRow].Trim();
    OprKod=tmp.SubString(1, tmp.Pos(" ")-1);
    OprName=tmp.SubString(tmp.Pos(" ")+1, tmp.Length()-tmp.Pos(" "));
    // сохранение
    if(!new_opr)
    {
        if(operations->Cells[21][nRow]=="0")
        {
            OperRow *opr=(OperRow *)operations->Cells[19][nRow].ToInt();
            save=opr->SetValues(idtar, id_cntrl, ceh, uch, Opr, oboID, OboName,
                OprName, OprKod, Strop, Tara, Control, Instruct);
        }
    }
    else
    {
        if(can_opr_save)
        {//ВНИМАНИЕ впоминием про warning связанный с тображением указателей на
        //операции для удаления если технология состоит только из них
            // поиск операции к которой можно прицепиться  среди отображающихся
            OperRow *opr=0;
            for(int i=nRow; i>=1&& !opr; i--)
            {
                if(operations->Cells[19][i]!="")
                {
                    opr=(OperRow *)operations->Cells[19][i].ToInt();
                }
            }
            OperRow *insopr=new OperRow(DB, Info->Get_LUser(), 0, "ins",
                Ldet->Get_ID(), idtar, id_cntrl, ceh, uch, Opr, oboID, OboName,
                OprName, OprKod, Strop, Tara, Control, Instruct,
                Info->Get_LUser(), Info->Get_LUser(), Date(), Date(), opr);
            if(!opr)//проверка результата поиска
            {
                if (Info->Get_Operations())
                {//если среди отображающихся прицепиться не удалось пробуем цепляться к удаленным
                    Info->Get_Operations()->Insert_line(0,insopr);
                }else
                {//технология пуста нет даже удаленных вставляем операцию
                    Info->Set_Operations(insopr);
                }
            }
            operations->Cells[19][nRow]=(String)(unsigned __int64)insopr;
            operations->Cells[21][nRow]=(String)(0);
            save=true;
        }
    }
    // подготовка данных  для сохранения норм
    String     prof=operations->Cells[10][nRow].Trim(),
            krop=operations->Cells[11][nRow].Trim(),
            rr=operations->Cells[12][nRow].Trim(),
            en=operations->Cells[14][nRow].Trim(),
            kts, kvn,
            ttp=operations->Cells[8][nRow].Trim();

    tmp=operations->Cells[15][nRow].Trim();
    if(tmp.Pos("/"))
    {
        kts=tmp.SubString(1, tmp.Pos("/")-1);
        kvn=tmp.SubString(tmp.Pos("/")+1, tmp.Length()-tmp.Pos("/"));
    }
    else
    {
        kts="0";
        kvn="0";
    }
    int kolod=operations->Cells[13][nRow].ToIntDef(1);
    double ksht, tpz, tsht;
    String d_s=Decimal_Separator==","?".":",";
    if(operations->Cells[16][nRow]!="")
    {
        operations->Cells[16][nRow]=Replace(operations->Cells[16][nRow], d_s,
            Decimal_Separator);
        tpz=operations->Cells[16][nRow].ToDouble();
    }
    else
    {
        tpz=0;
    }
    if(operations->Cells[17][nRow]!="")
    {
        operations->Cells[17][nRow]=Replace(operations->Cells[17][nRow], d_s,
            Decimal_Separator);
        tsht=operations->Cells[17][nRow].ToDouble();
    }
    else
    {
        tsht=0;
    }
    if(operations->Cells[9][nRow]!="")
    {
        operations->Cells[9][nRow]=Replace(operations->Cells[9][nRow], d_s,
            Decimal_Separator);
        ksht=operations->Cells[9][nRow].ToDouble();
    }
    else
    {
        ksht=0;
    }
    // сохранение  норм
    if(!new_nrm)
    { // обновление
        NrmRow *nrm=(NrmRow *)operations->Cells[20][nRow].ToInt();
        save=save+nrm->SetValues(kolod, prof, krop, rr, en, kts, kvn, ttp, ksht,
            tpz, tsht);
    }
    else
    { // создоние новой
        if(can_nrm_save)
        {
            // поиск ближайшей операции
            String mark="";
            for(int i=nRow; i>0&&mark==""; i--)
            {
                if(operations->Cells[19][i]!="")
                {
                    mark=operations->Cells[19][i];
                }
            }
            OperRow *opr=(OperRow *)mark.ToIntDef(0);
            if(opr)
            {
                NrmRow *nrm=0;
                // получить ссылку на норму стоящую до вводимой
                int pos= -1;
                for(int i=nRow-1;
                i>=1&&operations->Cells[19][i].ToIntDef(0)==(int)opr&&pos<0; i--)
                {
                    if(operations->Cells[21][i]!="")
                    {
                        pos=operations->Cells[21][i].ToInt();
                    }
                }
                if(pos>=0)
                {
                    if(opr->Get_nrm())
                    {
                        nrm=opr->Get_nrm()->operator[](pos);
                    }
                }
                NrmRow *insnrm=new NrmRow(DB, Info->Get_LUser(),
                    opr->Get_OpID(), "ins", kolod, prof, krop, rr, en, kts, kvn,
                    ttp, ksht, tpz, tsht, Info->Get_LUser(), Info->Get_LUser(),
                    Date(), Date(), nrm);
                if(!nrm)
                { // подключение цепочки
                    //вспоминаем про warning  с неуказанием указателей на удаленные объекты к которым нужно цепляться
                    if (opr->Get_nrm())
                    {//значит есть список удаленных норм впереди которого нужно вкорячить созданное
                        opr->Get_nrm()->Insert_line(0,insnrm);
                    }else
                    {//значит норм ваще нет и нада с этим чота делать
                        opr->Set_nrm(insnrm);
                    }
                }
                operations->Cells[19][nRow]=(String)(unsigned __int64)opr;
                operations->Cells[20][nRow]=(String)(unsigned __int64)insnrm;
                operations->Cells[21][nRow]=(String)(pos+1);
                save=save +true;
            }
        }
    }
    return save;
}
// обновление операции и норм
void TTechWnd::UpdGreedData(int nRow)
{
    log.push_back(Time().TimeString()+"--"+String((int)this)+"--"+
        "UpdGreedData("+String(nRow)+")");
    int start=0, //позиция начала обновления сетки
        end=0,   //позиция конца обновления
        count=0, //количество занимаемых строк которые надо обновить
        ncount=0;//новое количество строк которое будет после позиции  start
    // -найти начало строк операций
    for(start=nRow; start>0&&operations->Cells[19][nRow]==operations->Cells[19]
        [start]; start--){}
    start++ ;
    // -найти конец строк операций
    end=operations->RowCount-1;
    // -расчитать количество занимаемых строк
    count=end-start+1;
    // -расчитать новое количество строк
    if(operations->Cells[19][nRow]!="")
    {
        for(OperRow*opr=(OperRow *)operations->Cells[19][nRow].ToInt(); opr;
        opr=opr->Get_Next())//предполагается что колонка 19 заполнена без пробелов что в нормальной ситуации и есть    Warning
        {
            if(opr->isUsed())
            {
                ncount++ ;
                if(opr->Get_nrm())
                {
                    int norm_count=0;//количество строчек норм
                    for(NrmRow*nrm=opr->Get_nrm()->Get_First(); nrm;
                    nrm=nrm->Get_Next())
                    {
                        if(nrm->isUsed())
                        {
                            norm_count++ ;
                        }
                    }
                    if(norm_count>1)//если одна строчка то ncount не меняется т.к. первая норма на тойже строке что и операция
                    {
                        ncount+=norm_count-1;
                    }
                }
            }
        }
    }
    else
    {//в 19й пусто (расчитывается на то что это последняя строка)
        if(nRow==operations->RowCount-1)
        {//действительно последняя ставим 1чку чтобы обновить
            ncount=1;
        }
        else
        {//не последняя ставим 0 а вот зачем щас узнаю
            ncount=0; //поидее эта ситуация недолжна никогда возникнуть
            //в этом случае не будет пустой строки для дальнейшего ввода
        }
    }
    // -сдвинуть строки сетки
    for(int i=operations->RowCount-1; i>start; i--)
    { //это такая перманентная чистка (офсет указан как magic однако помним что это офсет для чистки невидимиых столбцов)
        for(int j=0; j<operations->ColCount+3; j++)
        {
            operations->Cells[j][i]="";
        }
    }
    //вот наконецто применяется новое количество строк
    operations->RowCount=operations->RowCount-count+ncount+1;
    // -вставить данные    тут warningи такие же как и при простой отрисовке данных
    if(operations->Cells[19][start]!="")
    {
        int rows=start;
        for(OperRow*i=(OperRow *)operations->Cells[19][start].ToIntDef(0); i;       //стоят умолчания при конвертации дабы не слететь в exeption
        i=i->Get_Next())
        {
            if(i->isUsed())
            {
                int str=0;
                operations->Cells[0][rows]="";
                operations->Cells[1][rows]=i->Get_ceh();
                operations->Cells[2][rows]=i->Get_uch();
                operations->Cells[3][rows]=i->Get_opr();
                operations->Cells[4][rows]=i->Get_OprKod()+" "+i->Get_OprName();
                operations->Cells[5][rows]=i->Get_Instruct();
                operations->Cells[6][rows]=i->Get_oboID();
                operations->Cells[7][rows]=i->Get_OboName();
                operations->Cells[8][rows]="";
                operations->Cells[9][rows]="";
                operations->Cells[10][rows]="";
                operations->Cells[11][rows]="";
                operations->Cells[12][rows]="";
                operations->Cells[13][rows]="";
                operations->Cells[14][rows]="";
                operations->Cells[15][rows]="";
                operations->Cells[16][rows]="";
                operations->Cells[17][rows]="";
                operations->Cells[19][rows]=(String)(unsigned __int64)i;
                // указатель на операцию
                operations->Cells[20][rows]=""; // указатель на норму
                operations->Cells[21][rows]=(String)str;
                // номер строки операции
                // operations->Cells[22][rows]=i->Get_action();
                // найти см=ttp ут=kvn оп=kts

                if(i->Get_nrm())
                {
                    for(NrmRow*j=i->Get_nrm()->Get_First(); j; j=j->Get_Next())
                    {
                        if(j->isUsed())
                        {
                            operations->Cells[0][rows+str]="";
                            operations->Cells[8][rows+str]=j->Get_Ttp();
                            operations->Cells[9][rows+str]=
                                (String)j->Get_Ksht();
                            operations->Cells[10][rows+str]=j->Get_Prof();
                            operations->Cells[11][rows+str]=j->Get_Krop();
                            operations->Cells[12][rows+str]=j->Get_Rr();
                            operations->Cells[13][rows+str]=
                                (String)j->Get_Kolod();
                            operations->Cells[14][rows+str]=j->Get_En();
                            operations->Cells[15][rows+str]=
                                j->Get_Kts()+"/"+j->Get_Kvn();
                            operations->Cells[16][rows+str]=
                                (String)j->Get_Tpz();
                            operations->Cells[17][rows+str]=
                                (String)j->Get_Tsht();
                            operations->Cells[19][rows+str]=
                                (String)(unsigned __int64)i;
                            // указатель на операцию
                            operations->Cells[20][rows+str]=
                                (String)(unsigned __int64)j;
                            // указатель на норму
                            operations->Cells[21][rows+str]=(String)str;
                            // номер строки операции
                            // operations->Cells[23][rows+str]=i->Get_action();
                            // operations->Cells[18][rows+str]="ОП";
                            str++ ;
                        }
                    }
                    if(str>0)
                    {
                        str-- ;
                    }
                }
                else
                {
                    str=0;
                }
                rows+=str+1;
            }
        }
    }
    operations->Cells[0][operations->RowCount-1]="*";
    // AutoWidthSG(operations);
}

// функции контроллеры
void TTechWnd::GreedClickControl(int ACol)
{
    log.push_back(Time().TimeString()+"--"+String((int)this)+"--"+
        "GreedClickControl("+String(ACol)+")");
    if(ACol==1||ACol==2||ACol==4||ACol==5||ACol==6||ACol==7)
    {
        operations->Options=operations->Options>>goEditing;
    }
}

bool TTechWnd::GreedDataControl(int ACol, int ARow)
{
    // log.push_back(Time().TimeString()+"--"+String((int)this)+"--"+"GreedDataControl("+String(ACol)+","+String(ARow)+")");
    int Length=0;
    bool it_double=false, it_int=false;
    switch(ACol)
    {
    case 1:
        {
            Length=2;
            it_double=false;
            it_int=true;
            break;
        }
    case 2:
        {
            Length=2;
            it_double=false;
            it_int=true;
            break;
        }
    case 3:
        {
            Length=3;
            it_double=false;
            it_int=true;
            break;
        }
    case 4:
        {
            Length=0;
            it_double=false;
            it_int=false;
            break;
        }
    case 5:
        {
            Length=0;
            it_double=false;
            it_int=false;
            break;
        }
    case 6:
        {
            Length=5;
            it_double=false;
            it_int=true;
            break;
        }
    case 7:
        {
            Length=0;
            it_double=false;
            it_int=false;
            break;
        }
    case 8:
        {
            Length=0;
            it_double=false;
            it_int=false;
            break;
        }
    case 9:
        {
            Length=0;
            it_double=true;
            it_int=false;
            break;
        }
    case 10:
        {
            Length=4;
            it_double=false;
            it_int=true;
            break;
        }
    case 11:
        {
            Length=1;
            it_double=false;
            it_int=true;
            break;
        }
    case 12:
        {
            Length=1;
            it_double=false;
            it_int=true;
            break;
        }
    case 13:
        {
            Length=0;
            it_double=false;
            it_int=true;
            break;
        }
    case 14:
        {
            Length=2;
            it_double=false;
            it_int=true;
            break;
        }
    case 15:
        {
            Length=4;
            it_double=false;
            it_int=false;
            break;
        }
    case 16:
        {
            Length=0;
            it_double=true;
            it_int=false;
            break;
        }
    case 17:
        {
            Length=0;
            it_double=true;
            it_int=false;
            break;
        }
    default:
        break;
    }
    bool result=true;
    if(Length)
    {
        if(operations->Cells[ACol][ARow].Length()==Length)
        {
            result=result *true;
        }
        else
        {
            result=result *false;
        }
    }
    else
    {
        if(operations->Cells[ACol][ARow]!="")
        {
            result=result *true;
        }
        else
        {
            result=result *false;
        }
    }
    if(it_double)
    {
        try
        {
            String d_s=Decimal_Separator==","?".":",";
            if(operations->Cells[ACol][ARow].Pos(d_s))
            {
                operations->Cells[ACol][ARow]=
                    Replace(operations->Cells[ACol][ARow], d_s,
                    Decimal_Separator);
            }
            operations->Cells[ACol][ARow].ToDouble();
            result=result *true;
        }
        catch(...)
        {
            result=result *false;
        }
    }
    if(it_int)
    {
        try
        {
            operations->Cells[ACol][ARow].ToInt();
            result=result *true;
        }
        catch(...)
        {
            result=result *false;
        }
    }
    if(ACol<8&&operations->Cells[21][ARow].ToIntDef(0))
    {
        result=true;
    }
    if(ACol==8||ACol==18)
    {
        result=true;
    }
    return result;
}

// рисовка сетки
void __fastcall TTechWnd::operationsDrawCell(TObject *Sender, int ACol,
    int ARow, TRect &Rect, TGridDrawState State)
{
    // - раскраска сетки
    static int color=0X00E0FFFF;
    int bad_color=0x00DDDDFF;
    if(ARow==1)
    {
        color=0X00E0FFFF;
    }
    if(ACol&&ARow) // разлинейка
    {
        int k=0;
        for(int i=1; operations->Cells[19][i]!=operations->Cells[19][ARow]; i++)
        {//всего лиш индикатор четности позиции операции
            if(operations->Cells[19][i-1]!=operations->Cells[19][i])
            {
                k++ ;
            }
        }
        if((k%2))
        {
            color=0X00E0FFFF;
        }
        else
        {
            color=0x00e0FFe0;
        }
        if(GreedDataControl(ACol, ARow))
        {
            operations->Canvas->Brush->Color=color;
        }
        else
        {
            operations->Canvas->Brush->Color=bad_color;
        }
        operations->Font->Color=clBlack;
        operations->Canvas->FillRect(Rect);
        operations->Canvas->TextOutW(Rect.left+2, Rect.top+1,
            operations->Cells[ACol][ARow]);
    }

    // выделенные поля
    if(ACol>=operations->Selection.Left&&ACol<=
        operations->Selection.Right&&ARow>=operations->Selection.Top&&ARow<=
        operations->Selection.Bottom) // выделение
    {
        operations->Canvas->Brush->Color=0x00FFE0E0; // clMenu;
        operations->Canvas->FillRect(Rect);
        operations->Font->Color=clBlack;
        operations->Canvas->TextOutW(Rect.left+2, Rect.top+1,
            operations->Cells[ACol][ARow]);
    }
}

// вызов редакторов для заполенения данных
void __fastcall TTechWnd::operationsDblClick(TObject *Sender)
{
    log.push_back(Time().TimeString()+"--"+String((int)this)+"--"+
        "operationsDblClick("+String((int)Sender)+")");
    if(!Info)
    {
        return;
    }
    int ACol=operations->Col, ARow=operations->Row;
    // заполнение СВ в зависимости от колонки
    String sql="";
    switch(ACol)
    {
    case 1:
        {
            fcb->Style=csDropDownList;
            if(Trim(operations->Cells[4][ARow])=="")
            {
                sql="Call equipment.Get_ceh_list(0,0,0)";
            }
            else
            {
                String param="0";
                if(operations->Cells[6][ARow].Length())
                {
                    param=operations->Cells[6][ARow];
                }
                sql="Call equipment.Get_ceh_list(1,'"+
                    Trim(operations->Cells[4][operations->Row]).SubString(1,
                    operations->Cells[4][operations->Row].Pos(" "))+"','"+
                    param+"')";
            }
            break;
        }
    case 2:
        {
            fcb->Style=csDropDownList;
            if(Trim(operations->Cells[4][ARow])=="")
            {
                sql="Call equipment.Get_utch_list(0,0,'"+
                    operations->Cells[1][ARow]+"','0')";
            }
            else
            {
                String param="0";
                if(operations->Cells[6][ARow].Length())
                {
                    param=operations->Cells[6][ARow];
                }
                sql="Call equipment.Get_utch_list(1,'"+
                    Trim(operations->Cells[4][operations->Row]).SubString(1,
                    operations->Cells[4][operations->Row].Pos(" "))+"','"+
                    operations->Cells[1][ARow]+"','"+param+"')";
            }
            break;
        }
    case 4:
        {
            fcb->Style=csDropDown;
            if(Trim(operations->Cells[1][ARow])!=""&&Trim
                (operations->Cells[2][ARow])!="")
            {
                sql="Call equipment.Get_Opreations_list(1,'"+
                    Trim(operations->Cells[1][ARow])+"','"+
                    Trim(operations->Cells[2][ARow])+"')";
            }
            else
            {
                sql="Call equipment.Get_Opreations_list(0,0,0)";
            }
            break;
        }
    case 5:
        {
            if(!ReadOnly&&TehEdit)
            {
                if(Trim(operations->Cells[4][ARow])!="")
                {
                    TTB *wnd=
                        new TTB(this,
                        Trim(operations->Cells[4][operations->Row]).SubString(1,
                        operations->Cells[4][operations->Row].Pos(" ")-1),
                        operations->Cells[5][operations->Row], DB);
                    wnd->ShowModal();
                    if(wnd->ModalResult==mrOk)
                    {
                        operations->Cells[5][ARow]=wnd->Get_ioht();
                    }
                    delete wnd;
                }
            }
            break;
        }
    case 7:
        {
            fcb->Style=csDropDownList;
            if(Trim(operations->Cells[1][operations->Row])!=""&&Trim
                (operations->Cells[2][operations->Row])!="")
            {
                sql="Call equipment.Get_Obor_list(1,'"+
                    Trim(operations->Cells[1][operations->Row])+"','"+
                    Trim(operations->Cells[2][operations->Row])+"','"+
                    Trim(operations->Cells[4][operations->Row]).SubString(1,
                    operations->Cells[4][operations->Row].Pos(" ")-1)+"')";
            }
            else
            {
                sql="Call equipment.Get_Obor_list(0,0,0,'"+
                    Trim(operations->Cells[4][operations->Row]).SubString(1,
                    operations->Cells[4][operations->Row].Pos(" ")-1)+"')";
            }
            break;
        }
    case 10:
        {
            if(!ReadOnly&&NormEdit)
            {
                TProfessinos *wnd=new TProfessinos(this, DB, false);
                wnd->ShowModal();
                if(wnd->ModalResult==mrOk)
                {
                    operations->Cells[10][operations->Row]=wnd->Get_prof();
                }
                delete wnd;
            }
            break;
        }
    default:
        sql="";
    }
    if(sql!="")
    {
        TADOQuery *rez=DB->SendSQL(sql);
        fcb->Items->Clear();
        if(rez&&rez->RecordCount)
        {
            for(rez->First(); !rez->Eof; rez->Next())
            {
                fcb->Items->Add
                    (rez->FieldByName(rez->Fields->operator[](0)->FieldName)
                    ->Value);
            }
        }
    }
    if((ACol==1||ACol==2||ACol==4||ACol==7)&&TehEdit&& !ReadOnly)
    {
        fcb->Height=operations->DefaultRowHeight;
        fcb->Width=operations->ColWidths[ACol];
        TRect R=operations->CellRect(ACol, ARow);
        R.Left=R.Left+operations->Left;
        R.Right=R.Right+operations->Left;
        R.Top=R.Top+operations->Top;
        R.Bottom=R.Bottom+operations->Top;
        fcb->Left=R.Left;
        fcb->Top=R.Top;
        fcb->Width=(R.Right+1)-R.Left;
        fcb->Height=(R.Bottom+1)-R.Top;
        fcb->Visible=true;
        fcb->SetFocus();
        fcb->Text=operations->Cells[ACol][ARow];
    }
}

void __fastcall TTechWnd::fcbChange(TObject *Sender)
{
    log.push_back(Time().TimeString()+"--"+String((int)this)+"--"+"fcbChange("+
        String((int)Sender)+")");
    switch(operations->Col)
    {
    case 1:
        {
            operations->Cells[2][operations->Row]="";
            operations->Cells[operations->Col][operations->Row]=fcb->Text;
            break;
        }
    case 4:
        {
            operations->Cells[operations->Col][operations->Row]=fcb->Text;
            operations->Cells[5][operations->Row]="";
            operations->Cells[6][operations->Row]="";
            operations->Cells[7][operations->Row]="";
            if(fcb->Text.Length())
            {
                String sql=
                    "Select ioht from catalogs.`instruc_tb` where kop like '%"+
                    operations->Cells[operations->Col][operations->Row]
                    .SubString(1,
                    operations->Cells[operations->Col][operations->Row].Pos(" ")
                    -1)+";%'";
                TADOQuery *rez=DB->SendSQL(sql);
                if(rez&&rez->RecordCount)
                {
                    for(rez->First(); !rez->Eof; rez->Next())
                    {
                        operations->Cells[5][operations->Row]=
                            operations->Cells[5][operations->Row]+
                            rez->FieldByName("ioht")->Value+"; ";
                    }
                }
                delete rez;
                rez=0;
            }
            break;
        }

    case 7:
        {
            String tmp=fcb->Text;
            int del_pos=tmp.Pos(" |");
            operations->Cells[1][operations->Row]=tmp.SubString(1, del_pos-1);
            tmp.Delete(1,del_pos+1);
            del_pos=tmp.Pos("|");
            operations->Cells[2][operations->Row]=tmp.SubString(1, del_pos-1);
            tmp.Delete(1,del_pos+1);
            del_pos=tmp.Pos("|");
            operations->Cells[6][operations->Row]=tmp.SubString(1, del_pos-1);
            tmp.Delete(1,del_pos+1);
            operations->Cells[7][operations->Row]=tmp;
        } break;
    default:
        operations->Cells[operations->Col][operations->Row]=fcb->Text;
    }
    if(operations->Row==operations->RowCount-1)
    {
        operations->RowCount++ ;
        operations->Cells[0][operations->RowCount-1]="*";
        operations->Cells[0][operations->Row]="";
    }
    fcb->Visible=false;
    operations->SetFocus();
    AutoWidthSG(operations);
}

void __fastcall TTechWnd::fcbExit(TObject *Sender)
{
    log.push_back(Time().TimeString()+"--"+String((int)this)+"--"+"fcbExit("+
        String((int)Sender)+")");
    fcb->Clear();
    fcb->Text="";
    fcb->Hide();
}

void __fastcall TTechWnd::operationsSetEditText(TObject *Sender, int ACol,
    int ARow, const UnicodeString Value)
{
    log.push_back(Time().TimeString()+"--"+String((int)this)+"--"+
        "operationsSetEditText("+String((int)Sender)+","+(String)ACol+","+
        (String)ARow+","+Value+")");
    if(ARow==operations->RowCount-1&&Value!="")
    {
        operations->RowCount++ ;
        operations->Cells[0][operations->RowCount-1]="*";
        operations->Cells[0][ARow]="";
    }
}

// КОНТЕКСТНОЕ МЕНЮ
void __fastcall TTechWnd::N1Click(TObject *Sender)
{
    log.push_back(Time().TimeString()+"--"+String((int)this)+"--"+"N1Click("+
        String((int)Sender)+")");
    // копировать
    if(O_buff)
    {
        delete O_buff;
        O_buff=0;
    }
    if(N_buff)
    {
        delete N_buff;
        N_buff=0;
    }
    bool opr_copy=false, nrm_copy=false;
    if(operations->Selection.Left<8)
    {
        opr_copy=true;
    }
    else
    {
        nrm_copy=true;
    }
    if(opr_copy)
    {
        // поиск начала и конца копирования
        int start=0, end=0, count=0;
        bool s_find=false,e_find=false;
        for(int i=operations->Selection.Top;
        i<=operations->Selection.Bottom&& !start; i++)
        {
            if(operations->Cells[19][i]!="")
            {
                start=i;
                s_find=true;
            }
        }
        for(int i=operations->Selection.Bottom;
        i>=operations->Selection.Top&& !end; i--)
        {
            if(operations->Cells[19][i]!="")
            {
                end=i;
                e_find=true;
            }
        }
        if (s_find&&e_find)
        {//защита от попытки скопировать не сохраненные данные
            // подсчитать количество идентификаторов
            String oldrow="";
            for(int i=start; i<=end; i++)
            {
                if(operations->Cells[19][i]!=""&&operations->Cells[19][i]!=oldrow)
                {
                    count++ ;
                    oldrow=operations->Cells[19][i];
                }
            }
            // копирование данных
            OperRow *opr=(OperRow *)operations->Cells[19][start].ToIntDef(0);
            if (opr)
            {//проверка наличия операции для копирования (не муляж ли)
                oldrow="";
                int pos=0;
                for(int i=1; i<=start; i++)
                {
                    if(operations->Cells[19][i]!=""&&operations->Cells[19][i]!=oldrow)
                    {
                        pos++ ;
                        oldrow=operations->Cells[19][i];
                    }
                }
                O_buff=opr->Copy_subline(pos-1, count);
            }
        }
    }
    if(nrm_copy)
    {
        // получить копируемый диапазон
        int start=operations->Selection.Top, end=0, count=0;
        String opr=operations->Cells[19][start];
        for(end=start;
        end<=operations->Selection.Bottom&&operations->Cells[19][end]
            ==opr; end++){}
        end-- ;
        count=end-start+1;
        // получить идентификатор копируемой нормы
        NrmRow *nrm=(NrmRow *)operations->Cells[20][start].ToIntDef(0);
        if(nrm)
        {//проверка наличия нормы для копирования (не муляж ли) + защита от копирования не сохраненной нормы
            N_buff=nrm->Copy_subline
                (operations->Cells[21][start].ToIntDef(0), count);
        }
    }
}

void __fastcall TTechWnd::N2Click(TObject *Sender)
{
    if(!Info)
    {
        return;
    }
    log.push_back(Time().TimeString()+"--"+String((int)this)+"--"+"N2Click("+
        String((int)Sender)+")");
    // вставить
    if(O_buff&&TehEdit&& !ReadOnly)
    {
        // поиск места вставки
        int row=0;
        for(int i=operations->Selection.Bottom; i>=1&& !row; i--)
        {
            if(operations->Cells[19][i]!="")
            {
                row=i;
            }
        }
        // определение наличия массива для вставки
        if(Info->Get_Operations())
        { // вставка в существующий массив
            // определение позиции строки в массиве
            // подсчитать количество видимых идентификаторов до позиции вставки
            String oldrow="";
            int count=0;
            for(int i=1; i<=row; i++)
            {
                if(operations->Cells[19][i]!=""&&operations->Cells[19][i]
                    !=oldrow)
                {
                    count++ ;
                    oldrow=operations->Cells[19][i];
                }
            }
            // вставка
            OperRow *opr=Info->Get_Operations();
            opr->Insert_line(count, O_buff);
            if(row)
            {
                UpdGreedData(row);
            }
            else
            {
                ShowOperations();
            }
        }
        else
        { // привязка буфера т.к. некуда вставлять
            O_buff->UpdID(Info->Get_id(), O_buff, true);
            Info->Set_Operations(O_buff);
            ShowOperations();
        }
        O_buff=0;
    }
    if(N_buff&&NormEdit&& !ReadOnly)
    {
        int row=operations->Row;
        if(operations->Cells[19][row]!="")
        {//нормы нельзя вставлять в пустоту
            OperRow *opr=(OperRow *)operations->Cells[19][row].ToInt();
            NrmRow *nrm=opr->Get_nrm();
            if(nrm)
            { // вставка
                NrmRow *nrm=opr->Get_nrm();
                nrm->Insert_line(operations->Cells[21][row].ToIntDef(0),
                    N_buff);
            }
            else
            { // присоединение
                N_buff->ChangeOpID(opr->Get_OpID(), N_buff, true);
                opr->Set_nrm(N_buff);
            }
            N_buff=0;
            UpdGreedData(row);
        }
        // определить позицию вставки
    }
}

void __fastcall TTechWnd::N3Click(TObject *Sender)
{
    log.push_back(Time().TimeString()+"--"+String((int)this)+"--"+"N3Click("+
        String((int)Sender)+")");
    // удалить
    bool opr_del=false, nrm_del=false;
    if(operations->Selection.Left<8)
    {
        if(TehEdit)
        {
            opr_del=true;
        }
    }
    else
    {
        if(NormEdit)
        {
            nrm_del=true;
        }
    }
    if(opr_del)
    {
        int start=0, end=0, count=0;
        bool s_find=false,e_find=false;
        for(int i=operations->Selection.Top;
        i<=operations->Selection.Bottom&& !start; i++)
        {
            if(operations->Cells[19][i]!="")
            {
                start=i;
                s_find=true;
            }
        }
        for(int i=operations->Selection.Bottom;
        i>=operations->Selection.Top&& !end; i--)
        {
            if(operations->Cells[19][i]!="")
            {
                end=i;
                e_find=true;
            }
        }
        if (s_find&&e_find)
        {//защита от попытки удалить не сохраненные данные
            // подсчитать количество идентификаторов
            String oldrow="";
            for(int i=start; i<=end; i++)
            {
                if(operations->Cells[19][i]!=""&&operations->Cells[19][i]!=oldrow)
                {
                    count++ ;
                    oldrow=operations->Cells[19][i];
                }
            }
            // удаление данных
            //позиции начала
            oldrow="";
            int pos=0;
            for(int i=1; i<=start; i++)
            {
                if(operations->Cells[19][i]!=""&&operations->Cells[19][i]!=oldrow)
                {
                    pos++ ;
                    oldrow=operations->Cells[19][i];
                }
            }
            OperRow *opr=Info->Get_Operations();
            if (opr)
            {// защита от пустого указателя
                opr->Del_subline(opr, pos-1, count);
                Info->Set_Operations(opr);
            }
        }
        ShowOperations();
    }
    if(nrm_del)
    {
        // получить удаляемый диапазон
        int start=operations->Selection.Top, end=0, count=0;
        String opr=operations->Cells[19][start];
        for(end=start;
        end<=operations->Selection.Bottom&&operations->Cells[19][end]
            ==opr; end++){}
        end-- ;
        count=end-start+1;
        // получить идентификатор удаляемой нормы
        if(operations->Cells[19][start]!="")
        {
            OperRow *opr=(OperRow *)operations->Cells[19][start].ToInt();
            NrmRow *nrm=opr->Get_nrm();
            if(nrm)
            {//защита от попытки удалить несохраненное
                nrm->Del_subline(nrm,
                    operations->Cells[21][start].ToIntDef(0), count);
                opr->Set_nrm(nrm);
            }
        }
        UpdGreedData(start);
    }
}

void __fastcall TTechWnd::N4Click(TObject *Sender)
{
    log.push_back(Time().TimeString()+"--"+String((int)this)+"--"+"N4Click("+
        String((int)Sender)+")");
    // вырезать
    N1Click(Sender);
    N3Click(Sender);
}

void __fastcall TTechWnd::N5Click(TObject *Sender)
{
    log.push_back(Time().TimeString()+"--"+String((int)this)+"--"+"N5Click("+
        String((int)Sender)+")");
    // обновить
    ShowDetInfo();
    ShowOperations();
}

void __fastcall TTechWnd::N12Click(TObject *Sender)
{
    log.push_back(Time().TimeString()+"--"+String((int)this)+"--"+"N12Click("+
        String((int)Sender)+")");
    operations->RowCount++ ;
    for(int i=operations->RowCount-1; i>operations->Row; i--)
    {
        for(int j=0; j<operations->ColCount+3; j++)
        {
            operations->Cells[j][i]=operations->Cells[j][i-1];
        }
    }
    for(int j=0; j<operations->ColCount+3; j++)
    {
        operations->Cells[j][operations->Row]="";
    }
}

void __fastcall TTechWnd::PABPopup(TObject *Sender)
{
    log.push_back(Time().TimeString()+"--"+String((int)this)+"--"+"PABPopup("+
        String((int)Sender)+")");
    // вставить
    if(!O_buff&& !N_buff)
    {
        N2->Enabled=false;
    }
    else
    {
        if((TehEdit&&O_buff)||(NormEdit&&N_buff))
        {
            N2->Enabled=true;
        }
        else
        {
            N2->Enabled=false;
        }
    }
    // вырезать
    // удалить
    if((TehEdit||NormEdit)&& !ReadOnly)
    {
        N3->Enabled=true;
        N4->Enabled=true;
        N12->Enabled=true;
    }
    else
    {
        N3->Enabled=false;
        N4->Enabled=false;
        N12->Enabled=false;
    }
}

// символы
void __fastcall TTechWnd::C1Click(TObject *Sender)
{
    log.push_back(Time().TimeString()+"--"+String((int)this)+"--"+"C1Click("+
        String((int)Sender)+")");
    if(!perexod->ReadOnly)
    {
        TSymbol *wnd=new TSymbol(this);
        wnd->ShowModal();
        if(wnd->ModalResult==mrOk)
        {
            int line=perexod->CaretPos.Y, pos=perexod->CaretPos.X+1;
            int cur=perexod->SelStart;
            UnicodeString msg=wnd->E1->Text.Trim(), tmp=
                perexod->Lines->operator[](line).Insert(msg, pos);
            perexod->Lines->Delete(line);
            perexod->Lines->Insert(line, tmp);
            perexod->SelStart=cur+msg.Length();
        }
        delete wnd;
    }
}

// редактирование переходов
void __fastcall TTechWnd::perexodChange(TObject *Sender)
{
    log.push_back(Time().TimeString()+"--"+String((int)this)+"--"+
        "perexodChange("+String((int)Sender)+")");
    if(perexod->Paragraph->Numbering!=nsBullet)
    {
        perexod->Paragraph->Numbering=nsBullet;
    }
}

void __fastcall TTechWnd::perexodEnter(TObject *Sender)
{
    log.push_back(Time().TimeString()+"--"+String((int)this)+"--"+
        "perexodEnter("+String((int)Sender)+")");
    if(TehEdit&& !ReadOnly&&operations->Row!=operations->RowCount-1)
    {
        operSave(operations->Row);
        perexod->ReadOnly=false;
    }
    else
    {
        perexod->ReadOnly=true;
    }
}

void __fastcall TTechWnd::perexodExit(TObject *Sender)
{
    log.push_back(Time().TimeString()+"--"+String((int)this)+"--"+
        "perexodExit("+String((int)Sender)+")");
    // сохранение переходов
    if(operations->Cells[19][operations->Row]!="")
    {//операция сохранена (есть к чему цеплять)
        OperRow *row=(OperRow *)operations->Cells[19][operations->Row].ToInt();
        PerexRow *per=row->Get_perex(); //список переходов исходный (он весь удаляется и к нему цепляются новые)
        PerexRow *pertmp=0;
        if(per)
        {//удаление старого списка
         //опасность получить нуль когда список самоуничтожится(нечего будет чистить в базе)
            per->Del_subline(per, 0, per->Count());
        }
        if(perexod->Lines->Count)
        {//проверка на наличие строк для сохранения
            perexod->WordWrap=false;
            for(int i=0; i<perexod->Lines->Count; i++)
            {//наполнение тмп массива перехдов
                if(perexod->Lines->operator[](i)!="")
                {
                    pertmp=new PerexRow(DB, row->Get_OpID(), 0,
                        perexod->Lines->operator[](i), pertmp);
                }
            }
            if(per)
            { // обработка сущестующих переходов
                per->Insert_line(0, pertmp);
                row->Set_perex(per->Get_First());
            }
            else
            { // создание новой цепочки переходов
                if(pertmp)
                {
                    row->Set_perex(pertmp->Get_First());
                }
                else
                {
                    row->Set_perex(0);
                }
            }
            perexod->WordWrap=true;
        }
        else
        {
            if(per)
            {
                row->Set_perex(per->Get_First());
            }
            else
            {
                row->Set_perex(0);
            }
        }
    }
}

// редактирование инструмента
void __fastcall TTechWnd::instrumDblClick(TObject *Sender)
{
    log.push_back(Time().TimeString()+"--"+String((int)this)+"--"+
        "instrumDblClick("+String((int)Sender)+")");
    if(TehEdit&& !ReadOnly&&operations->Row!=operations->RowCount-1)
    {
        Tinstr *wnd=new Tinstr(this, DB, instrum->Cells[2][instrum->Row],
            instrum->Cells[1][instrum->Row]);
        wnd->ShowModal();
        if(wnd->ModalResult==mrOk)
        {
            String name=wnd->Get_Name(), kod=wnd->Get_kod();
            if(name==""&&kod=="")
            {
                if(instrum->Row!=instrum->RowCount-1)
                {
                    for(int i=instrum->Row; i<instrum->RowCount; i++)
                    {
                        instrum->Cells[0][i]=instrum->Cells[0][i+1];
                        instrum->Cells[1][i]=instrum->Cells[1][i+1];
                        instrum->Cells[2][i]=instrum->Cells[2][i+1];
                    }
                    if(instrum->RowCount>2)
                    {
                        instrum->RowCount-- ;
                    }
                }
            }
            else
            {
                instrum->Cells[0][instrum->Row]="";
                instrum->Cells[1][instrum->Row]=name;
                instrum->Cells[2][instrum->Row]=kod;
                if(instrum->Row+1==instrum->RowCount)
                {
                    instrum->Cells[0][instrum->Row]="";
                    instrum->RowCount++ ;
                }
            }
            instrum->Cells[0][instrum->RowCount-1]="*";
        }
        delete wnd;
    }
}

void __fastcall TTechWnd::instrumExit(TObject *Sender)
{
    log.push_back(Time().TimeString()+"--"+String((int)this)+"--"+
        "instrumExit("+String((int)Sender)+")");
    if(operations->Cells[19][operations->Row]!=""&&instrum->RowCount>=2)
    {//операция сохранена (есть к чему цеплять)ну и список инструмента не пуст))
        OperRow *row=(OperRow *)operations->Cells[19][operations->Row].ToIntDef(0);
        InstrumRow *ins=row->Get_instrum();
        InstrumRow *instmp=0;
        for(int i=1; i<instrum->RowCount-1; i++)
        {//наполнение временного массива
            instmp=new InstrumRow(DB, row->Get_OpID(), 0, instrum->Cells[2][i],
                instrum->Cells[1][i], instmp);
        }
        if(ins)
        {//опасность паолучить нуль после удаления
            ins->Del_subline(ins, 0, ins->Count());
        }
        if(instmp)
        {
            if(ins)
            { // обработка сущестующих переходов
                ins->Insert_line(0, instmp);
                row->Set_instrum(ins->Get_First());
            }
            else
            { // создание новой цепочки переходов
                row->Set_instrum(instmp->Get_First());
            }
        }
        else
        {
            if(ins)
            { // обработка сущестующих переходов
                row->Set_instrum(ins->Get_First());
            }
            else
            { // создание новой цепочки переходов
                row->Set_instrum(0);
            }
        }

    }
}

// тара и строповка
void __fastcall TTechWnd::taraDblClick(TObject *Sender)
{
    log.push_back(Time().TimeString()+"--"+String((int)this)+"--"+
        "taraDblClick("+String((int)Sender)+")");
    if(TehEdit&&Info&& !ReadOnly)
    {
        String id, text;
        if(tara->Text.Trim()!="")
        {
            id=(String)tara->Tag;
            text=tara->Text.Trim();
        }
        else
        {
            id="";
            text="";
        }
        Ttarandsrop *wnd=new Ttarandsrop(this, DB, "tara", id, text);
        wnd->ShowModal();
        if(wnd->ModalResult==mrOk)
        {
            tara->Tag=wnd->Get_id().ToIntDef(0);
            tara->Text=wnd->Get_text();
        }
        delete wnd;
    }
}

void __fastcall TTechWnd::stropDblClick(TObject *Sender)
{
    log.push_back(Time().TimeString()+"--"+String((int)this)+"--"+
        "stropDblClick("+String((int)Sender)+")");
    if(TehEdit&&Info&& !ReadOnly)
    {
        String id, text;
        if(strop->Text.Trim()!="")
        {
            id=strop->Text.Trim();
            text=strpLabel->Caption+id;
        }
        else
        {
            id="";
            text="";
        }
        Ttarandsrop *wnd=new Ttarandsrop(this, DB, "strop", id, text);
        wnd->ShowModal();
        if(wnd->ModalResult==mrOk)
        {
            strop->Text=wnd->Get_id();
            strpLabel->Caption=Replace(wnd->Get_text(), " "+wnd->Get_id(),
                "").Trim();
        }
        delete wnd;
    }
}

// заготовки
void __fastcall TTechWnd::kzDblClick(TObject *Sender)
{
    log.push_back(Time().TimeString()+"--"+String((int)this)+"--"+"kzDblClick("+
        String((int)Sender)+")");
    if(Info&& !ReadOnly&&TehEdit)
    {
        Tzagotovka *wnd=new Tzagotovka(this, DB, false, LUser,
            (String)Info->Get_vz(), (String)Info->Get_masz(),
            (String)Info->Get_nrm(), Info->Get_razz());
        wnd->ShowModal();
        if(wnd->ModalResult==mrOk)
        {
            String d_s=Decimal_Separator==","?".":",";
            Info->Set_vz(wnd->Get_kz().ToIntDef(0));
            Info->Set_masz(Replace(wnd->Get_masz(), d_s, Decimal_Separator)
                .ToDouble());
            Info->Set_nrm(Replace(wnd->Get_norma(), d_s, Decimal_Separator)
                .ToDouble());
            Info->Set_razz(wnd->Get_razmzagot());
            Info->Set_kdz(wnd->Get_kdz().ToIntDef(1));
            ShowDetInfo();
        }
        delete wnd;
    }
}

// материал
void __fastcall TTechWnd::obmDblClick(TObject *Sender)
{
    log.push_back(Time().TimeString()+"--"+String((int)this)+"--"+
        "obmDblClick("+String((int)Sender)+")");
    if(Info&& !ReadOnly&&TehEdit)
    {
        Tmaterials *wnd=new Tmaterials(this, DB, false, LUser);
        wnd->ShowModal();
        if(wnd->ModalResult==mrOk)
        {
            Info->Set_obm(wnd->Get_obm());
            ShowDetInfo();
        }
        delete wnd;
    }
}

// перетаскивание строк
void __fastcall TTechWnd::operationsRowMoved(TObject *Sender, int FromIndex,
    int ToIndex)
{
    log.push_back(Time().TimeString()+"--"+String((int)this)+"--"+
        "operationsRowMoved("+String((int)Sender)+","+String(FromIndex)+","+
        String(ToIndex)+")");
    if(Info&&TehEdit&& !ReadOnly)
    {
        if(operations->Cells[19][FromIndex]!="")
        {
            // вычисление текущей позиции в массиве
            int from=0, to=0;
            String oldrow="";
            bool f_find=false,t_find=false;
            for(int i=1; i<=FromIndex; i++)
            {
                if(operations->Cells[19][i]!=""&&operations->Cells[19][i]
                    !=oldrow&&operations->Cells[21][i]=="0")
                {
                    from++ ;
                    oldrow=operations->Cells[19][i];
                    f_find=true;
                }
            }
            if(from)
            {
                from-- ;
            }
            // вычисление новой позиции в масиве
            oldrow="";
            for(int i=1; i<=ToIndex; i++)
            {
                if(operations->Cells[19][i]!=""&&operations->Cells[19][i]
                    !=oldrow&&operations->Cells[21][i]=="0")
                {
                    to++ ;
                    oldrow=operations->Cells[19][i];
                    t_find=true;
                }
            }
            if(to&&(FromIndex>ToIndex))
            {
                to-- ;
            }
            // замена строк
            if (f_find&&t_find)
            {
                Info->Get_Operations()->Move_items(from, 1, to);
            }
        }
        ShowOperations(); // обновление сетки
    }
}

// шифт и контрл
void __fastcall TTechWnd::operationsKeyDown(TObject *Sender, WORD &Key,
    TShiftState Shift)
{
    if(Shift.ToInt()==1||Shift.ToInt()==4)
    {
        operations->Options=operations->Options>>goEditing;
    }
}

void __fastcall TTechWnd::printbtnClick(TObject *Sender)
{
    TLogForm *wnd=new TLogForm(this, log);
    wnd->ShowModal();
    delete wnd;
}
// ---------------------------------------------------------------------------

void __fastcall TTechWnd::TimerTimer(TObject *Sender)
{
    if(Info)
    {
        Info->CheckAccept();
        ReadOnly= !(Info->Get_Access()*TehSave*(TehEdit+NormEdit));
        access->Caption= !ReadOnly?"Полный доступ":"Только чтение";
    }
}
// ---------------------------------------------------------------------------
