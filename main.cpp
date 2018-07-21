#include <vcl.h>
#pragma hdrstop

#include "main.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TmForm *mForm;

//Возвращает полный путь к временной папке
const AnsiString GetFullTempPath() {
    char chBuffer[MAX_PATH];
    GetTempPathA(MAX_PATH,chBuffer);
    AnsiString sTempPath = chBuffer;
    // если получилось сокращённое имя, получаем полное
    GetLongPathNameA(sTempPath.c_str(),chBuffer,MAX_PATH);
    sTempPath =chBuffer;
    return sTempPath;
}

__fastcall TmForm::TmForm(TComponent *Owner):TForm(Owner), UserID(0)
{
#ifndef NODB
    ADC->ConnectionString="FILE NAME="+ExtractFileDir(Application->ExeName)+
        "\\lib\\connect.udl";

    ADC->Connected=true;
#endif
    DB=new cSQL(ADC);
    TLogIn *wnd=new TLogIn(this, DB);
    wnd->ShowModal();
    selected=0;
    if(wnd->ModalResult==mrOk)
    {
        Tabs.clear();
		IcoData=new IconsData(this);
        LoadIL();
        UserID=wnd->Get_UserID();
        // настройка содержимого
        String sql="call administration.Get_Rights('"+String(UserID)+"')";
        TADOQuery *rez=DB->SendSQL(sql);
        bool SpView=false, TehRead=false, TehEdit=false, NormEdit=false, plan_pr_va_det=false,
        otbor_po_ceu=false, mat_ved=false, texnologic=false,Orders=false,manufacture_view=false;
        if(rez&&rez->RecordCount)
        {
            for (rez->First(); !rez->Eof; rez->Next())
            {
                const String val=rez->FieldByName("progname")->Value;
                if (val=="SpView")
                {
                    SpView=true;
                }
                if (val=="TehRead")
                {
                    TehRead=true;
                }
                if (val=="TehEdit")
                {
                    TehEdit=true;
                }
                if (val=="NormEdit")
                {
                    NormEdit=true;
                }
                if (val=="plan_pr_va_det")
                {
                    plan_pr_va_det=true;
                }
                if (val=="otbor_po_ceu")
                {
                    otbor_po_ceu=true;
                }
                if (val=="mat_ved")
                {
                    mat_ved=true;
                }
                if (val=="texnologic")
                {
                    texnologic=true;
                }
                if (val=="OrderView")
                {
                    Orders=true;
                }
                if (val=="manufacture_view")
                {
                    manufacture_view=true;
                }
            }
        }
        delete rez;
        //
        N24->Visible=SpView;
        N29->Visible=SpView;
        TreeBTN->Visible=SpView;
        //
        N26->Visible=false; // TehRead;
        N27->Visible=false; // TehRead;
        TechnologicVievBTN->Visible=false; // TehRead;
        //
        N6->Visible=TehEdit+NormEdit+TehRead;
        N30->Visible=TehEdit+NormEdit+TehRead;
        TechnologicBTN->Visible=TehEdit+NormEdit+TehRead;
        //
        N18->Enabled=plan_pr_va_det;
        N19->Enabled=otbor_po_ceu;
        N20->Enabled=mat_ved;
        N21->Enabled=mat_ved;
        N22->Enabled=texnologic;
        //
        OrdersBTN->Visible=Orders;
        N13->Visible=Orders;
        N25->Visible=Orders;
        //
        N28->Visible=manufacture_view;
        N28->Enabled=manufacture_view;
        N33->Visible=manufacture_view;
        N33->Enabled=manufacture_view;
        N34->Visible=manufacture_view;
        N34->Enabled=manufacture_view;
        N35->Visible=manufacture_view;
        N35->Enabled=manufacture_view;
        ManufactureBTN->Visible = manufacture_view;
        N36->Visible=manufacture_view;
        N37->Visible=manufacture_view;
        if(SpView)
        {
            AddTree(LeftPC, 0, Info);
        }
        /* if (TehEdit+NormEdit)
         {
         AddTexTab(RightPC,0);
         } */
        AddSearch(RightPC);

        String name=""; //добавить запрос на получение имени для отчета
        sql="call administration.Get_Name('"+String(UserID)+"')";
        rez=DB->SendSQL(sql);
        if (rez&&rez->RecordCount)
        {
            name=rez->FieldByName("name")->Value;
        }
        delete rez;
        HINSTANCE Reports=LoadLibrary(String("lib\\Reports.dll").c_str());
        // загружаем длл
        if(Reports)
        {
            RepInit=(init_func)GetProcAddress(Reports, "_Init");
            if(RepInit)
            {
                RepInit(name, DB);
                RepStart=(RepStart_func)GetProcAddress(Reports, "_Report");
                // получаем указатель на функцию
            }
        }
    }
    else
    {
        Application->Terminate();
    }
    /* динамический вызов
     typedef bool (*InetIsOffline_func)(int);
     InetIsOffline_func InetIsOffline;
     HINSTANCE LibHeader=LoadLibrary(String("URL.DLL").c_str());//загружаем длл
     if(!LibHeader){
     throw Exception("Не удалось загрузить библиотеку URL.DLL");
     };
     InetIsOffline=(InetIsOffline_func)GetProcAddress(LibHeader,"InetIsOffline");//получаем указатель на функцию
     if(!InetIsOffline){
     throw Exception("В библиотеке URL.DLL не найдена функция InetIsOffline");
     };
     //вызов функции
     int Flag;
     bool result=InetIsOffline(Flag);
     //освобождение библиотеки
     FreeLibrary(LibHeader);
	 */

	 //Создание каталога для временных файлов, если его нет
	 String pathToTemp = GetFullTempPath() + "yzpmktpp\\";
	 CreateDirectory(pathToTemp.c_str(), NULL);
}

__fastcall TmForm::~TmForm(void)
{
    DB->SendCommand
        ("update administration.logins set status='offline' where logid='"+
        (String)UserID+"'");
    if (selected)
    {
        delete []selected;
	}

	//Удаление временных файлов
	String pathToTemp = GetFullTempPath() + "yzpmktpp\\";
	TSearchRec sr;
	if (FindFirst(pathToTemp + "*.*", faAnyFile, sr) == 0)
	{
		do
		{
			DeleteFile(pathToTemp + sr.Name);
		}while (FindNext(sr) == 0);
		FindClose(sr);
	}
}

void __fastcall TmForm::FormClose(TObject *Sender, TCloseAction &Action)
{
    if(Tabs.size())
    {
        vector < Tab * > ::iterator i=Tabs.begin();
        while(i<Tabs.end()&&Action==caHide)
        {
            if((*i)->CanClose())
            {
                delete(*i);
                i=Tabs.erase(i);
            }
            else
            {
                Action=caNone;
            }
        }
    }
}

void TmForm::LoadIL(void)
{
    TImageList *il=IcoData->GetImgList();
    TImageList *st=IcoData->GetStateList();
    // обьявить переменные для считывания
    TMemoryStream *str=new TMemoryStream();
    Graphics::TBitmap *bmp=new Graphics::TBitmap();
    // считывание состояний
    TADOQuery *rez=
        DB->SendSQL
        ("Select `idsost`,`imgt`,`imgf` from administration.conditions");
    if(rez)
    {
        rez->First();
        while(!rez->Eof)
        {
            // считать в поток блоб поле
            str=(TMemoryStream *)rez->CreateBlobStream(rez->FieldByName("imgt"),
                bmRead);
            str->Position=0;
            bmp->LoadFromStream(str);
            if(!st->Count)
            {
                st->Add(bmp, 0);
                // забивка нулевой позиции в целом юзлесс нужно т.к нумерация начинается с 1 а не с 0
            }
            IcoData->LoadCollation(rez->FieldByName("idsost")->Value,
                st->Add(bmp, 0), true, 0);
            // добавить запись в массив сопоставления
            IcoData->LoadCollation(rez->FieldByName("idsost")->Value,
                il->Add(bmp, 0), true, 3);
            // добавить запись в массив сопоставления
            str=(TMemoryStream *)rez->CreateBlobStream(rez->FieldByName("imgf"),
                bmRead);
            str->Position=0;
            bmp->LoadFromStream(str);
            // il->Add(bmp,0);   //возвращает позицию?                                           //тип 0 состояния
            IcoData->LoadCollation(rez->FieldByName("idsost")->Value,
                st->Add(bmp, 0), false, 0);
            // добавить запись в массив сопоставления
            IcoData->LoadCollation(rez->FieldByName("idsost")->Value,
                il->Add(bmp, 0), false, 3);
            // добавить запись в массив сопоставления
            rez->Next();
        }
    }
    delete rez;
    // считывание иконок файлов
    rez=DB->SendSQL("Select `id`,`Ico` from administration.files_and_types");
    if(rez)
    {
        rez->First();
        while(!rez->Eof)
        {
            // считать в поток блоб поле
            str=(TMemoryStream *)rez->CreateBlobStream(rez->FieldByName("Ico"),
                bmRead);
            str->Position=0;
            bmp->LoadFromStream(str);
            // il->Add(bmp,0);   возвращает позицию?                                            //тип 2 иконки файлов
            IcoData->LoadCollation(rez->FieldByName("id")->Value,
                il->Add(bmp, 0), true, 2);
            // добавить запись в массив сопоставления
            rez->Next();
        }
    }
    delete rez;
    // считывание разделов разделов спецификации
    rez=DB->SendSQL("Select `RazdID`,`Icon` from administration.sprazd");
    if(rez)
    {
        rez->First();
        while(!rez->Eof)
        {
            // считать в поток блоб поле
            str=(TMemoryStream *)rez->CreateBlobStream(rez->FieldByName("Icon"),
                bmRead);
            str->Position=0;
            bmp->LoadFromStream(str);
            // il->Add(bmp,0);   возвращает позицию?                                            //тип 1 иконки
            IcoData->LoadCollation(rez->FieldByName("RazdID")->Value,
                il->Add(bmp, 0), true, 1);
            // добавить запись в массив сопоставления
            rez->Next();
        }
    }
    delete str;
    delete bmp;
    delete rez;
}

void __fastcall TmForm::PCMouseDown(TObject *Sender, TMouseButton Button,
    TShiftState Shift, int X, int Y)
{ // нажатие кнопки
    TPageControl *PC=(TPageControl *)Sender;
    DrawCloseTabBtn(PC, 0, X, Y, -1, 1);
    TRect r;
    r=PC->TabRect(PC->IndexOfTabAt(X, Y));
    if(Button==mbLeft&&X<r.Right-btns->Width-4)
    {
        if(PC->Tag!=1)
        {
            PC->BeginDrag(false);
            PC->Tag=1;
        }
    }
}

void __fastcall TmForm::PCMouseUp(TObject *Sender, TMouseButton Button,
    TShiftState Shift, int X, int Y)
{
    // страбатывание кнопки
    TPageControl *PC=(TPageControl *)Sender;
    TRect btn=DrawCloseTabBtn(PC, 0, X, Y, -1, 0);
    if(X>=btn.Left&&X<=btn.Right&&Y>=btn.Top&&Y<=btn.Bottom)
        // проверить диапазон кнопки
    {
        TTabSheet *t=PC->Pages[PC->IndexOfTabAt(X, Y)];
        CloseTab(t);
    }
    if(PC->Tag==1)
    {
        PC->EndDrag(false);
        PC->Tag=0;
    }
}

void __fastcall TmForm::PCDrawTab(TCustomTabControl *Control, int TabIndex,
    const TRect &Rect, bool Active)
{
    TPageControl *PC=(TPageControl *)Control;
    // размеры и рисовка табы
    /* PC->TabWidth=
     PC->TabHeight= */
    TPoint txt;
    if(PC->Pages[TabIndex]->ImageIndex>=0)
    {
        txt.X=Rect.Left+Img->Width+4;
        txt.Y=Rect.Top+2;
    }
    else
    {
        if(PC->Pages[TabIndex]->Showing)
        {
            txt.X=Rect.Left+6;
            txt.Y=Rect.Top+3;
        }
        else
        {
            txt.X=Rect.Left+3;
            txt.Y=Rect.Top+3;
        }

    }
    // чистка
    PC->Canvas->FillRect(Rect);
    // вывести текст
    if(!PC->Pages[TabIndex]->Tag)
    {
        PC->Canvas->TextOutW(txt.X, txt.Y,
        (PC->Pages[TabIndex]->Caption).Trim());
        PC->Pages[TabIndex]->Tag=0;
    }
    // кнупочка
    DrawCloseTabBtn(PC, &Rect, 0, 0, TabIndex, 0);
    // нарисовать иконку
    TPoint ico;
    ico.X=Rect.Left+2;
    ico.Y=Rect.Top+2;
    Graphics::TBitmap *b=new Graphics::TBitmap();
    if(Img->GetBitmap(PC->Pages[TabIndex]->ImageIndex, b))
    {
        PC->Canvas->Draw(ico.X, ico.Y, b);
    }
    delete b;
}

void __fastcall TmForm::PCMouseLeave(TObject *Sender)
{
    ((TPageControl *)Sender)->Repaint();
}

void __fastcall TmForm::PCMouseMove(TObject *Sender, TShiftState Shift,
    int X, int Y)
{
    // страбатывание кнопки
    TPageControl *PC=(TPageControl *)Sender;
    TRect btn=DrawCloseTabBtn(PC, 0, X, Y, -1, 2);
    /* static TRect btnOld;     // отключена перерисовка крестина на предыдущей табе
     if (btn!=btnOld&&(btnOld.top||btnOld.Bottom||btnOld.Left||btnOld.Right))
     {
     TPoint s;
     s.X=btnOld.Left+5;
     s.Y=btnOld.Top+5;
     s=PC->ParentToClient(s,PC->Parent);
     DrawCloseTabBtn(PC,0,s.x,s.y,-1,0);     //привести координаты к нужному виду
     }
     btnOld=btn; */
}

void __fastcall TmForm::PCDragOver(TObject *Sender, TObject *Source, int X,
    int Y, TDragState State, bool &Accept)
{
    Accept=Source->ClassNameIs("TPageControl");
}

void __fastcall TmForm::PCDragDrop(TObject *Sender, TObject *Source,
    int X, int Y)
{

    if(Source->ClassNameIs("TPageControl"))
    {
        TPageControl *from=(TPageControl *)Source;
        TPageControl *to=(TPageControl *)Sender;
        TTabSheet *tab=from->ActivePage;
        if(from!=to)
        {
            tab->PageControl=to;
        }
        tab->PageIndex=to->IndexOfTabAt(X, Y);
        from->Tag=0;
        to->Tag=0;
    }
}

void __fastcall TmForm::FormDragOver(TObject *Sender, TObject *Source, int X,
    int Y, TDragState State, bool &Accept)
{
    // сорс ->ссылка на паратаскиваемый контрол
    // сендер сама форма
    // сравнить координаты х и у с параметрами размещения контролов если в зоне их нахождения то все норм
    if(Source->ClassNameIs("TPageControl"))
    {
        if(X>=LeftPC->Left&&X<=LeftPC->Left+LeftPC->Width&&Y>=LeftPC->Top&&Y<=
            LeftPC->Top+LeftPC->Height)
        {
            Accept=true;
            return;
        }
        if(X>=RightPC->Left&&X<=RightPC->Left+RightPC->Width&&Y>=
            RightPC->Top&&Y<=RightPC->Top+RightPC->Height)
        {
            Accept=true;
            return;
        }
    }
    Accept=false;
    return;
}

void __fastcall TmForm::FormDragDrop(TObject *Sender, TObject *Source,
    int X, int Y)
{
    if(Source->ClassNameIs("TPageControl"))
    {
        TPageControl *from=(TPageControl *)Source;
        TPageControl *to=0;
        if(X>=LeftPC->Left&&X<=LeftPC->Left+LeftPC->Width&&Y>=LeftPC->Top&&Y<=
            LeftPC->Top+LeftPC->Height)
        {
            to=LeftPC;
        }
        if(X>=RightPC->Left&&X<=RightPC->Left+RightPC->Width&&Y>=
            RightPC->Top&&Y<=RightPC->Top+RightPC->Height)
        {
            to=RightPC;
        }
        TTabSheet *tab=from->ActivePage;
        if(from!=to)
        {
            tab->PageControl=to;
        }
        tab->PageIndex=to->PageCount-1;
        from->Tag=0;
        to->Tag=0;
    }
}

TRect TmForm::DrawCloseTabBtn(TPageControl *PC, const TRect *Rect, int X, int Y,
    int TabNo, char type)
{
    TRect r;
    static int oldi;
    int i;
    if(TabNo>=0)
    {
        i=TabNo;
    }
    else
    {
        i=PC->IndexOfTabAt(X, Y);
    }
    if(i<0)
    {
        return r;
    }
    if(Rect)
    {
        r= *Rect;
    }
    else
    {
        r=PC->TabRect(i);
    }

    TRect btn;
    int vofset, gofset;
    if(!Rect)
    {
        if(PC->Pages[i]->Showing)
        {
            vofset=2;
            gofset=2;
        }
        else
        {
            vofset=4;
            gofset=6;
        }
    }
    else
    {
        if(Rect&&X&&Y)
        {
            if(i==oldi)
            {
                return btn;
            }
            vofset=0;
            gofset=0;
        }
        else
        {
            vofset=4;
            gofset=4;
        }
    }
    oldi=i;
    btn.Right=r.Right-gofset;
    btn.Top=r.Top+vofset;
    btn.Left=btn.Right-btns->Width;
    btn.Bottom=btn.Top+btns->Height;
    Graphics::TBitmap *b=new Graphics::TBitmap();
    char img;
    bool CanDraw=false;
    switch(type)
    {
    case 0:
        {
            img=0;
            CanDraw=true;
            break;
        }
    case 1:
        {
            img=1;
            if(X>=btn.Left&&X<=btn.Right&&Y>=btn.Top&&Y<=btn.Bottom)
            {
                CanDraw=true;
            }
            else
            {
                CanDraw=false;
            }
            break;
        }
    case 2:
        {
            int k=GetKeyState(VK_LBUTTON);
            if(X>=btn.Left&&X<=btn.Right&&Y>=btn.Top&&Y<=btn.Bottom&&k<0)
                // проверить диапазон кнопки
            {
                img=1;
            }
            else
            {
                img=0;
            }
            CanDraw=true;
            break;
        }
    default:
        break;
    }
    if(btns->GetBitmap(img, b)&&CanDraw)
    {
        PC->Canvas->Draw(btn.Left, btn.top, b);
    }
    delete b;
    return btn;
}

void __fastcall TmForm::PCChange(TObject *Sender)
{
    TPageControl *pc=(TPageControl *)Sender;
    SetLastTab(pc->ActivePage);
}

void TmForm::SetLastTab(TTabSheet *tab)
{
    Tab *t=GetTab(tab);
    if(t&&Tabs.size())
    {
        for(vector < Tab * > ::iterator i=Tabs.begin(); i<Tabs.end(); i++)
        {
            if((*i)->TrueClassName()==t->TrueClassName())
            {
                if((*i)!=t)
                {
                    (*i)->last_tab=false;
                }
            }

        }
        t->last_tab=true;
    }
}

Tab *TmForm::GetTab(TTabSheet *tab)
{
    if(Tabs.size())
    {
        for(vector < Tab * > ::iterator i=Tabs.begin(); i<Tabs.end(); i++)
        {
            if((*i)->tab==tab)
            {
                return *i;
            }
        }
    }
    return 0;
}

TTabSheet *TmForm::GetLastTab(char type)
{
    String ClassType="";
    switch(type)
    {
    case 0:
        { // поиск среди спецификаций
            ClassType="TreeTab";
            break;
        }
    case 1:
        { // поиск среди технологий
            ClassType="TechTab";
            break;
        }
    case 2:
        { // поиск среди просмотров технологий
            ClassType="TechViewTab";
            break;
        }
    case 3:
        { // поиск среди поисков
            ClassType="SearchTab";
            break;
        }
    case 4:
        { // поиск среди поисков
            ClassType="ProcessingTab";
            break;
        }
    case 5:
        { // поиск среди поисков
            ClassType="OrdersTab";
            break;
        }
    case 6:
        { // поиск среди поисков
            ClassType="ManufactureTab";
            break;
        }
    case 7:
        { // поиск среди поисков
            ClassType="ResourceUsageTab";
            break;
        }
    default:
        ClassType="";
        break;
    }
    if(Tabs.size())
    {
        for(vector < Tab * > ::iterator i=Tabs.begin(); i<Tabs.end(); i++)
        {
            if((*i)->TrueClassName()==ClassType&&(*i)->last_tab)
            {
                return (*i)->tab;
            }
        }
    }
    return 0;
}

void __fastcall TmForm::PCEnter(TObject *Sender)
{
    TPageControl *PC=(TPageControl *)Sender;
    if(PC)
    {
        SetLastTab(PC->ActivePage);
    }
}

void TmForm::CloseTab(TTabSheet *tab)
{
    if(tab==InfoTab)
    {
        tab->Hide();
        tab->PageControl=0;
    }
    else
    {
        Tab *t=GetTab(tab);
        if(t&&Tabs.size()&&t->CanClose())
        {
            for(vector < Tab * > ::iterator i=Tabs.begin(); i<Tabs.end(); i++)
            {
                if((*i)==t)
                {
                    Tabs.erase(i);
                }
            }
            delete t;
        }
    }
}

void TmForm::AddTree(TPageControl *Page, Obd *Det, TMemo *memo)
{
    TSpTree *SpTree=0;
    TTabSheet *tab;
    TreeTab *t=new TreeTab();
    tab=new TTabSheet(this); // создание щита
    tab->ImageIndex=0;
    tab->PageControl=Page; // прикрепление щита
    // создание дерева //прикрепление дерева
    SpTree=new TSpTree(this, tab, DB, UserID, memo, IcoData, &selected,
        &_AddTexTab, &_LoadTexToCurrTab, 0,0/*&_AddTexViewTab,
        &_LoadexViewToCurrTab*/);

    // регистрация щита и дерева
    t->tab=tab;
    t->module=SpTree;
    t->last_tab=false;
    Tabs.push_back((Tab *)t);
    SetLastTab(tab);
    tab->Show();
    // занесение первичных данных в дерево
    if(Det)
    {
        ((ClassConnector *)SpTree)->Load_sel(Det);
    }
}

void TmForm::AddTexTab(TPageControl *Page, Obd *Det)
{
    static i=0;
    TTechWnd *TechWnd;
    TTabSheet *tab;
    TechTab *t=new TechTab();
    tab=new TTabSheet(this); // создание щита
    tab->ImageIndex=1;
    tab->PageControl=Page; // прикрепление щита
    // создание эелемента
    TechWnd=new TTechWnd(this, tab, "TechEdit"+String(++i), UserID, DB);
    // регистрация щита и дерева
    t->tab=tab;
    t->module=TechWnd;
    t->last_tab=false;
    Tabs.push_back((Tab *)t);
    SetLastTab(tab);
    tab->Show();
    // занесение первичных данных в технологию
    if(Det)
    {
        ((ClassConnector *)TechWnd)->Load_sel(Det);
    }
}

void TmForm::LoadTexToCurrTab(Obd *Det)
{
    Tab *t=GetTab(GetLastTab(1));
    if(t)
    { // найдена последняя таба
        ((ClassConnector *)(((TechTab *)t)->module))->Load_sel(Det);
        t->tab->Show();
    }
    else
    {
        AddTexTab(RightPC, Det);
    }
    // поиск последней табы с технологией и обращение к ней если нет табы то создать новую
}

void TmForm::AddTexViewTab(TPageControl *Page, Obd *Det)
{
    static i=0;
    TTechView *TechView=0;
    TTabSheet *tab;
    TechViewTab *t=new TechViewTab();
    tab=new TTabSheet(this); // создание щита
    tab->ImageIndex=2;
    tab->PageControl=Page; // прикрепление щита
    // создание эелемента
    // TechView=new TTechView(this);
    // регистрация щита и дерева

    t->tab=tab;
    t->module=TechView;
    t->last_tab=false;
    Tabs.push_back((Tab *)t);
    SetLastTab(tab);
    tab->Show();
    // занесение первичных данных в дерево
    // TechView->LoadDet(DetID);
    tab->Caption="просмотр новая вкладка"; // !!!!!!!!!!
}

void TmForm::LoadexViewToCurrTab(Obd *Det)
{
    Tab *t=GetTab(GetLastTab(2));
    if(t)
    { // найдена последняя таба
        // ((ClassConnector*)(((TechViewTab*)t)->module))->Load(det);
        t->tab->Show();
        t->tab->Caption="просмотр текущая вкладка";
    }
    else
    {
        AddTexViewTab(RightPC, Det);
    }
}

void TmForm::AddSearch(TPageControl *Page)
{
    TSearch *Search=0;
    TTabSheet *tab;
    SearchTab *t=new SearchTab();
    tab=new TTabSheet(this); // создание щита
    tab->PageControl=Page; // прикрепление щита
    // создание эелемента //прикрепление дерева
    Search=new TSearch(this, tab, UserID, DB, IcoData, &selected, &_ShowTree,
        &_AddTexTab, &_LoadTexToCurrTab, 0,0/*&_AddTexViewTab,
        &_LoadexViewToCurrTab*/);
    tab->ImageIndex=3;
    // регистрация щита и дерева
    t->tab=tab;
    t->module=Search;
    t->last_tab=false;
    Tabs.push_back((Tab *)t);
    SetLastTab(tab);
    tab->Show();
}

void TmForm::AddProcessing(TPageControl *Page)
{
/*
TTabSheet * GetLastTab    (char type);
Tab*        GetTab         (TTabSheet *tab);
*/
TTabSheet *tab=0;

    static i=0;
    TList_Editor *Process=0;
    ProcessingTab *t=new ProcessingTab();
    tab=new TTabSheet(this); // создание щита
    tab->ImageIndex=9;
    tab->PageControl=Page; // прикрепление щита
    // создание дерева //прикрепление дерева
    Process=new TList_Editor(this, tab, "Processing"+String(++i), UserID, DB,IcoData,&selected,&_ShowTree,
        &_AddTexTab, &_LoadTexToCurrTab, &_AddTexViewTab,
        &_LoadexViewToCurrTab);

    // регистрация щита и дерева
    t->tab=tab;
    t->module=Process;
    t->last_tab=false;
    Tabs.push_back((Tab *)t);
    SetLastTab(tab);
    //показать
    tab->Show();

}

void TmForm::AddOrders    (TPageControl *Page)
{
    TTabSheet *tab=0;

    TOrders_editor *Orders_editor=0;
    OrdersTab *t=new OrdersTab();
    tab=new TTabSheet(this); // создание щита
    tab->ImageIndex=10;
    tab->PageControl=Page; // прикрепление щита
    // создание дерева //прикрепление дерева
    Orders_editor=new TOrders_editor(this, tab, UserID, DB,IcoData,&selected);

    // регистрация щита и дерева
    t->tab=tab;
    t->module=Orders_editor;
    t->last_tab=false;
    Tabs.push_back((Tab *)t);
    SetLastTab(tab);
    //показать
    tab->Show();
}

void TmForm::AddManufacture(TPageControl *Page)
{
    TTabSheet *tab=0;

    TManufactureControl *ManufactureControl=0;
    ManufactureTab *t=new ManufactureTab();
    tab=new TTabSheet(this); // создание щита
    tab->ImageIndex=10;
    tab->PageControl=Page; // прикрепление щита
    // создание дерева //прикрепление дерева
    ManufactureControl=new TManufactureControl(this, tab, UserID, DB,IcoData,&selected);

    // регистрация щита и дерева
    t->tab=tab;
    t->module=ManufactureControl;
    t->last_tab=false;
    Tabs.push_back((Tab *)t);
    SetLastTab(tab);
    //показать
    tab->Show();
}

void TmForm::AddResourceUsage(TPageControl *Page)
{
    TTabSheet *tab=0;

    TResourceUsage *ResourceUsage=0;
    ResourceUsageTab *t=new ResourceUsageTab();
    tab=new TTabSheet(this); // создание щита
    tab->ImageIndex=11;
    tab->PageControl=Page; // прикрепление щита
    // создание дерева //прикрепление дерева
	ResourceUsage=new TResourceUsage(this, tab, UserID, DB,IcoData);

    // регистрация щита и дерева
    t->tab=tab;
    t->module=ResourceUsage;
    t->last_tab=false;
    Tabs.push_back((Tab *)t);
    SetLastTab(tab);
    //показать
    tab->Show();
}

void __fastcall TmForm::InfoClick(TObject *Sender)
{
    TPageControl *pc;
    TMenuItem *curr=(TMenuItem *)Sender;
    if(curr!=N5&&curr!=N32)
    {
        return;
    }
    switch(curr->Tag)
    {
    case 1:
        {
            pc=RightPC;
            break;
        }
    case -1:
        {
            pc=LeftPC;
            break;
        }
    default:
        return;
    }
    InfoTab->PageControl=pc; // переключение-включение
}

void __fastcall TmForm::SpTreeClick(TObject *Sender)
{
    // если нет ни одного дерева то создать
    TPageControl *pc;
    TMenuItem *curr=(TMenuItem *)Sender;
    if(curr!=N24&&curr!=N29)
    {
        return;
    }
    switch(curr->Tag)
    {
    case 1:
        {
            pc=RightPC;
            break;
        }
    case -1:
        {
            pc=LeftPC;
            break;
        }
    default:
        return;
    }
    if(Tabs.size())
    {
        TTabSheet *t=GetLastTab(0);
        if(t)
        {
            t->PageControl=pc;
            // если есть хоть одно показать последнее выбранное
        }
        else
        {
            AddTree(pc, 0, Info);
        }
    }
    else
    {
        AddTree(pc, 0, Info);
    }
}

void __fastcall TmForm::TechClick(TObject *Sender)
{
    TPageControl *pc;
    TMenuItem *curr=(TMenuItem *)Sender;
    if(curr!=N6&&curr!=N30)
    {
        return;
    }
    switch(curr->Tag)
    {
    case 1:
        {
            pc=RightPC;
            break;
        }
    case -1:
        {
            pc=LeftPC;
            break;
        }
    default:
        return;
    }
    if(Tabs.size())
    {
        TTabSheet *t=GetLastTab(1);
        if(t)
        {
            t->PageControl=pc;
            // если есть хоть одно показать последнее выбранное
        }
        else
        {
            AddTexTab(pc, 0);
        }
    }
    else
    {
        AddTexTab(pc, 0);
    }
}

void __fastcall TmForm::TechViewClick(TObject *Sender)
{
    TPageControl *pc;
    TMenuItem *curr=(TMenuItem *)Sender;
    if(curr!=N26&&curr!=N27)
    {
        return;
    }
    switch(curr->Tag)
    {
    case 1:
        {
            pc=RightPC;
            break;
        }
    case -1:
        {
            pc=LeftPC;
            break;
        }
    default:
        return;
    }
    if(Tabs.size())
    {
        TTabSheet *t=GetLastTab(2);
        if(t)
        {
            t->PageControl=pc;
            // если есть хоть одно показать последнее выбранное
        }
        else
        {
            AddTexViewTab(pc, 0);
        }
    }
    else
    {
        AddTexViewTab(pc, 0);
    }
}

void __fastcall TmForm::SearchClick(TObject *Sender)
{
    TPageControl *pc;
    TMenuItem *curr=(TMenuItem *)Sender;
    if(curr!=N23&&curr!=N31)
    {
        return;
    }
    switch(curr->Tag)
    {
    case 1:
        {
            pc=RightPC;
            break;
        }
    case -1:
        {
            pc=LeftPC;
            break;
        }
    default:
        return;
    }
    if(Tabs.size())
    {
        TTabSheet *t=GetLastTab(3);
        if(t)
        {
            t->PageControl=pc;
            // если есть хоть одно показать последнее выбранное
        }
        else
        {
            AddSearch(pc);
        }
    }
    else
    {
        AddSearch(pc);
    }
}

void __fastcall TmForm::ProcessingClick(TObject *Sender)
{
    TPageControl *pc;
    TMenuItem *curr=(TMenuItem *)Sender;
    if(curr!=N11&&curr!=N12)
    {
        return;
    }
    switch(curr->Tag)
    {
    case 1:
        {
            pc=RightPC;
            break;
        }
    case -1:
        {
            pc=LeftPC;
            break;
        }
    default:
        return;
    }
    if(Tabs.size())
    {
        TTabSheet *t=GetLastTab(4);
        if(t)
        {
            t->PageControl=pc;
            // если есть хоть одно показать последнее выбранное
        }
        else
        {
            AddProcessing(pc);
        }
    }
    else
    {
        AddProcessing(pc);
    }
}
void __fastcall TmForm::OrdersClick(TObject *Sender)
{
    TPageControl *pc;
    TMenuItem *curr=(TMenuItem *)Sender;
    if(curr!=N13&&curr!=N25)
    {
        return;
    }
    switch(curr->Tag)
    {
    case 1:
        {
            pc=RightPC;
            break;
        }
    case -1:
        {
            pc=LeftPC;
            break;
        }
    default:
        return;
    }
    if(Tabs.size())
    {
        TTabSheet *t=GetLastTab(5);
        if(t)
        {
            t->PageControl=pc;
            // если есть хоть одно показать последнее выбранное
        }
        else
        {
            AddOrders(pc);
        }
    }
    else
    {
        AddOrders(pc);
    }
}

void __fastcall TmForm::ManufactureClick(TObject *Sender)
{
    TPageControl *pc;
    TMenuItem *curr=(TMenuItem *)Sender;
    if(curr!=N36&&curr!=N37)
    {
        return;
    }
    switch(curr->Tag)
    {
    case 1:
        {
            pc=RightPC;
            break;
        }
    case -1:
        {
            pc=LeftPC;
            break;
        }
    default:
        return;
    }
    if(Tabs.size())
    {
        TTabSheet *t=GetLastTab(6);
        if(t)
        {
            t->PageControl=pc;
            // если есть хоть одно показать последнее выбранное
        }
        else
        {
            AddManufacture(pc);
        }
    }
    else
    {
        AddManufacture(pc);
    }
}

void __fastcall TmForm::ResourceUsageClick(TObject *Sender)
{
    TPageControl *pc;
    TMenuItem *curr=(TMenuItem *)Sender;
    if(curr!=N38&&curr!=N39)
    {
        return;
    }
    switch(curr->Tag)
    {
    case 1:
        {
            pc=RightPC;
            break;
        }
    case -1:
        {
            pc=LeftPC;
            break;
        }
    default:
        return;
    }
    if(Tabs.size())
    {
        TTabSheet *t=GetLastTab(7);
        if(t)
        {
            t->PageControl=pc;
            // если есть хоть одно показать последнее выбранное
        }
        else
        {
            AddResourceUsage(pc);
        }
    }
    else
    {
        AddResourceUsage(pc);
    }
}


void __fastcall TmForm::TreeBTNClick(TObject *Sender)
{
    AddTree(LeftPC, 0, Info);
}

void __fastcall TmForm::TechnologicBTNClick(TObject *Sender)
{
    AddTexTab(RightPC, 0);
}

void __fastcall TmForm::TechnologicVievBTNClick(TObject *Sender)
{
    AddTexViewTab(RightPC, 0);
}

void __fastcall TmForm::SearchBTNClick(TObject *Sender)
{
    AddSearch(RightPC);
}

void __fastcall TmForm::ShowInfoClick(TObject *Sender)
{
    if(!InfoTab->PageControl)
    {
        InfoTab->PageControl=RightPC;
    };
    InfoTab->Show();
}

void __fastcall TmForm::ProcessingBTNClick(TObject *Sender)
{
    AddProcessing(RightPC);
}

void __fastcall TmForm::OrdersBTNClick(TObject *Sender)
{
    AddOrders(RightPC);
}

void __fastcall TmForm::ManufactureBTNClick(TObject *Sender)
{
    AddManufacture(RightPC);
}

void __fastcall TmForm::ResourceUsageBTNClick(TObject *Sender)
{
    AddResourceUsage(RightPC);
}

void __fastcall TmForm::N8Click(TObject *Sender)
{
    Tmaterials *wnd=new Tmaterials(this, DB, true, UserID);
    wnd->ShowModal();
    delete wnd;
}

void __fastcall TmForm::N9Click(TObject *Sender)
{
    Tzagotovka *wnd=new Tzagotovka(this, DB, true, UserID, "", "", "", "");
    wnd->ShowModal();
    delete wnd;
}

void __fastcall TmForm::N10Click(TObject *Sender)
{
    TProfessinos *wnd=new TProfessinos(this, DB, true);
    wnd->ShowModal();
    delete wnd;
}

void __fastcall TmForm::otchet(TObject *Sender)
{
    TMenuItem *Item=(TMenuItem *)Sender;
    if(Item)
    {
        /* int type=0;
         switch (Item->Tag)
         {
         case 1:{type=1;break;}//развертка дерева
         case 2:{type=2;break;}//список состовляющих
         case 3:{type=3;break;}//план производстка
         case 4:{type=4;break;}//поиск по цеху
         case 5:{type=5;break;}//материалка основная
         case 6:{type=6;break;}//технология
         case 7:{type=7;break;}//материалки
         case 8:{type=8;break;}//требование материала
         case 9:{type=9;break;}//ведомость котельных сборок
         case 10:{type=10;break;}//план производства для участка
		 case 11:{type=11;break;}//план производства для участка (ЧПУ)
		 case 12:{type=12;break;}//перечень оригинальных документов
         default:return;
         } */
        // получить обозначение
        String obd="";
        if (selected)
        {
            TADOQuery *rez=
                DB->SendSQL("select obd from constructions.det_names where id='"+
                String(*(selected+1))+"'");
            if(rez&&rez->RecordCount)
            {
                obd=VinToGost(rez->FieldByName("obd")->Value);
            }
            delete rez;
        }
        TOtchet *wnd=new TOtchet(this, VinToGost(obd));
        wnd->ShowModal();
        if(wnd->ModalResult==mrOk)
        {
            if(Item->Tag)
            {
                if(RepStart)
                {
                    RepStart(Item->Tag, wnd->LE1->Text.Trim());
                }
            }
        }
        delete wnd;
    }
}
void __fastcall TmForm::gonawayTimer(TObject *Sender)
{
    // для обхода ошибки гонавеи таймер настроен на 5 минут
    TADOQuery *rez=DB->SendSQL("select 1");
    delete rez;
}
void __fastcall TmForm::MailPannelClick(TObject *Sender)
{
    TLogForm *wnd=new TLogForm(this, DB->Get_log());
    wnd->ShowModal();
    delete wnd;
}

void __fastcall TmForm::N14Click(TObject *Sender)
{//
	TSettings* wnd=new TSettings(this,DB,UserID);
	delete wnd;
}

void _AddTexTab(const Obd *Det)
{
    if(Det)
    {
        Obd *tmp=new Obd(*Det);
        mForm->AddTexTab(mForm->RightPC, tmp);
    }
}

void _AddTexViewTab(const Obd *Det)
{
    if(Det)
    {
        Obd *tmp=new Obd(*Det);
        mForm->AddTexTab(mForm->RightPC, tmp);
        // mForm->AddTexViewTab(mForm->RightPC,tmp);
    }
}

void _LoadTexToCurrTab(const Obd *Det)
{
    if(Det)
    {
        Obd *tmp=new Obd(*Det);
        mForm->LoadTexToCurrTab(tmp);
    }
}

void _LoadexViewToCurrTab(const Obd *Det)
{
    if(Det)
    {
        Obd *tmp=new Obd(*Det);
        mForm->LoadTexToCurrTab(tmp);
        // mForm->LoadexViewToCurrTab(tmp);
    }
}

void _ShowTree(const Obd *Det)
{
    if(Det)
    {
		Obd *tmp=new Obd(*Det);
		Tab *t=mForm->GetTab(mForm->GetLastTab(0));
		if(t)
		{
			((ClassConnector *)(((TreeTab *)t)->module))->Load_sel(tmp);
			return;
		}
		else
		{
			mForm->AddTree(mForm->LeftPC, tmp, mForm->Info);
			return;
		}
	}
}
//временные
//---------------------------------------------------------------------------

