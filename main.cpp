#include <vcl.h>
#pragma hdrstop

#include "main.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TmForm *mForm;

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
		// ��������� �����������
		String sql="call administration.Get_Rights('"+String(UserID)+"')";
		TADOQuery *rez=DB->SendSQL(sql);
		bool SpView=false, TehRead=false, TehEdit=false, NormEdit=false, plan_pr_va_det=false,
		otbor_po_ceu=false, mat_ved=false, texnologic=false,Orders=false,Run_at_manufacture=false;
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
				if (val=="Run_at_manufacture")
				{
                	Run_at_manufacture=true;
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
		N28->Visible=Run_at_manufacture;
		N28->Enabled=Run_at_manufacture;
		N33->Visible=Run_at_manufacture;
		N33->Enabled=Run_at_manufacture;
		N34->Visible=Run_at_manufacture;
		N34->Enabled=Run_at_manufacture;
		N35->Visible=Run_at_manufacture;
		N35->Enabled=Run_at_manufacture;
		ManufactureBTN->Visible = Run_at_manufacture;
		N36->Visible=Run_at_manufacture;
		N37->Visible=Run_at_manufacture;
		if(SpView)
		{
			AddTree(LeftPC, 0, Info);
		}
		/* if (TehEdit+NormEdit)
		 {
		 AddTexTab(RightPC,0);
		 } */
		AddSearch(RightPC);

		String name=""; //�������� ������ �� ��������� ����� ��� ������
		sql="call administration.Get_Name('"+String(UserID)+"')";
		rez=DB->SendSQL(sql);
		if (rez&&rez->RecordCount)
		{
			name=rez->FieldByName("name")->Value;
		}
		delete rez;
		HINSTANCE Reports=LoadLibrary(String("lib\\Reports.dll").c_str());
		// ��������� ���
		if(Reports)
		{
			RepInit=(init_func)GetProcAddress(Reports, "_Init");
			if(RepInit)
			{
				RepInit(name, DB);
				RepStart=(RepStart_func)GetProcAddress(Reports, "_Report");
				// �������� ��������� �� �������
			}
		}
	}
	else
	{
		Application->Terminate();
	}
	/* ������������ �����
	 typedef bool (*InetIsOffline_func)(int);
	 InetIsOffline_func InetIsOffline;
	 HINSTANCE LibHeader=LoadLibrary(String("URL.DLL").c_str());//��������� ���
	 if(!LibHeader){
	 throw Exception("�� ������� ��������� ���������� URL.DLL");
	 };
	 InetIsOffline=(InetIsOffline_func)GetProcAddress(LibHeader,"InetIsOffline");//�������� ��������� �� �������
	 if(!InetIsOffline){
	 throw Exception("� ���������� URL.DLL �� ������� ������� InetIsOffline");
	 };
	 //����� �������
	 int Flag;
	 bool result=InetIsOffline(Flag);
	 //������������ ����������
	 FreeLibrary(LibHeader);
	 */
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
	// �������� ���������� ��� ����������
	TMemoryStream *str=new TMemoryStream();
	Graphics::TBitmap *bmp=new Graphics::TBitmap();
	// ���������� ���������
	TADOQuery *rez=
		DB->SendSQL
		("Select `idsost`,`imgt`,`imgf` from administration.conditions");
	if(rez)
	{
		rez->First();
		while(!rez->Eof)
		{
			// ������� � ����� ���� ����
			str=(TMemoryStream *)rez->CreateBlobStream(rez->FieldByName("imgt"),
				bmRead);
			str->Position=0;
			bmp->LoadFromStream(str);
			if(!st->Count)
			{
				st->Add(bmp, 0);
				// ������� ������� ������� � ����� ������ ����� �.� ��������� ���������� � 1 � �� � 0
			}
			IcoData->LoadCollation(rez->FieldByName("idsost")->Value,
				st->Add(bmp, 0), true, 0);
			// �������� ������ � ������ �������������
			IcoData->LoadCollation(rez->FieldByName("idsost")->Value,
				il->Add(bmp, 0), true, 3);
			// �������� ������ � ������ �������������
			str=(TMemoryStream *)rez->CreateBlobStream(rez->FieldByName("imgf"),
				bmRead);
			str->Position=0;
			bmp->LoadFromStream(str);
			// il->Add(bmp,0);   //���������� �������?                                           //��� 0 ���������
			IcoData->LoadCollation(rez->FieldByName("idsost")->Value,
				st->Add(bmp, 0), false, 0);
			// �������� ������ � ������ �������������
			IcoData->LoadCollation(rez->FieldByName("idsost")->Value,
				il->Add(bmp, 0), false, 3);
			// �������� ������ � ������ �������������
			rez->Next();
		}
	}
	delete rez;
	// ���������� ������ ������
	rez=DB->SendSQL("Select `id`,`Ico` from administration.files_and_types");
	if(rez)
	{
		rez->First();
		while(!rez->Eof)
		{
			// ������� � ����� ���� ����
			str=(TMemoryStream *)rez->CreateBlobStream(rez->FieldByName("Ico"),
				bmRead);
			str->Position=0;
			bmp->LoadFromStream(str);
			// il->Add(bmp,0);   ���������� �������?                                            //��� 2 ������ ������
			IcoData->LoadCollation(rez->FieldByName("id")->Value,
				il->Add(bmp, 0), true, 2);
			// �������� ������ � ������ �������������
			rez->Next();
		}
	}
	delete rez;
	// ���������� �������� �������� ������������
	rez=DB->SendSQL("Select `RazdID`,`Icon` from administration.sprazd");
	if(rez)
	{
		rez->First();
		while(!rez->Eof)
		{
			// ������� � ����� ���� ����
			str=(TMemoryStream *)rez->CreateBlobStream(rez->FieldByName("Icon"),
				bmRead);
			str->Position=0;
			bmp->LoadFromStream(str);
			// il->Add(bmp,0);   ���������� �������?                                            //��� 1 ������
			IcoData->LoadCollation(rez->FieldByName("RazdID")->Value,
				il->Add(bmp, 0), true, 1);
			// �������� ������ � ������ �������������
			rez->Next();
		}
	}
	delete str;
	delete bmp;
	delete rez;
}

void __fastcall TmForm::PCMouseDown(TObject *Sender, TMouseButton Button,
	TShiftState Shift, int X, int Y)
{ // ������� ������
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
	// ������������� ������
	TPageControl *PC=(TPageControl *)Sender;
	TRect btn=DrawCloseTabBtn(PC, 0, X, Y, -1, 0);
	if(X>=btn.Left&&X<=btn.Right&&Y>=btn.Top&&Y<=btn.Bottom)
		// ��������� �������� ������
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
	// ������� � ������� ����
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
	// ������
	PC->Canvas->FillRect(Rect);
	// ������� �����
	if(!PC->Pages[TabIndex]->Tag)
	{
		PC->Canvas->TextOutW(txt.X, txt.Y,
		(PC->Pages[TabIndex]->Caption).Trim());
		PC->Pages[TabIndex]->Tag=0;
	}
	// ��������
	DrawCloseTabBtn(PC, &Rect, 0, 0, TabIndex, 0);
	// ���������� ������
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
	// ������������� ������
	TPageControl *PC=(TPageControl *)Sender;
	TRect btn=DrawCloseTabBtn(PC, 0, X, Y, -1, 2);
	/* static TRect btnOld;     // ��������� ����������� �������� �� ���������� ����
	 if (btn!=btnOld&&(btnOld.top||btnOld.Bottom||btnOld.Left||btnOld.Right))
	 {
	 TPoint s;
	 s.X=btnOld.Left+5;
	 s.Y=btnOld.Top+5;
	 s=PC->ParentToClient(s,PC->Parent);
	 DrawCloseTabBtn(PC,0,s.x,s.y,-1,0);     //�������� ���������� � ������� ����
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
	// ���� ->������ �� ��������������� �������
	// ������ ���� �����
	// �������� ���������� � � � � ����������� ���������� ��������� ���� � ���� �� ���������� �� ��� ����
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
				// ��������� �������� ������
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
		{ // ����� ����� ������������
			ClassType="TreeTab";
			break;
		}
	case 1:
		{ // ����� ����� ����������
			ClassType="TechTab";
			break;
		}
	case 2:
		{ // ����� ����� ���������� ����������
			ClassType="TechViewTab";
			break;
		}
	case 3:
		{ // ����� ����� �������
			ClassType="SearchTab";
			break;
		}
	case 4:
		{ // ����� ����� �������
			ClassType="ProcessingTab";
			break;
		}
	case 5:
		{ // ����� ����� �������
			ClassType="OrdersTab";
			break;
		}
	case 6:
		{ // ����� ����� �������
			ClassType="ManufactureTab";
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
	tab=new TTabSheet(this); // �������� ����
	tab->ImageIndex=0;
	tab->PageControl=Page; // ������������ ����
	// �������� ������ //������������ ������
	SpTree=new TSpTree(this, tab, DB, UserID, memo, IcoData, &selected,
		&_AddTexTab, &_LoadTexToCurrTab, 0,0/*&_AddTexViewTab,
		&_LoadexViewToCurrTab*/);

	// ����������� ���� � ������
	t->tab=tab;
	t->module=SpTree;
	t->last_tab=false;
	Tabs.push_back((Tab *)t);
	SetLastTab(tab);
	tab->Show();
	// ��������� ��������� ������ � ������
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
	tab=new TTabSheet(this); // �������� ����
	tab->ImageIndex=1;
	tab->PageControl=Page; // ������������ ����
	// �������� ���������
	TechWnd=new TTechWnd(this, tab, "TechEdit"+String(++i), UserID, DB);
	// ����������� ���� � ������
	t->tab=tab;
	t->module=TechWnd;
	t->last_tab=false;
	Tabs.push_back((Tab *)t);
	SetLastTab(tab);
	tab->Show();
	// ��������� ��������� ������ � ����������
	if(Det)
	{
		((ClassConnector *)TechWnd)->Load_sel(Det);
	}
}

void TmForm::LoadTexToCurrTab(Obd *Det)
{
	Tab *t=GetTab(GetLastTab(1));
	if(t)
	{ // ������� ��������� ����
		((ClassConnector *)(((TechTab *)t)->module))->Load_sel(Det);
		t->tab->Show();
	}
	else
	{
		AddTexTab(RightPC, Det);
	}
	// ����� ��������� ���� � ����������� � ��������� � ��� ���� ��� ���� �� ������� �����
}

void TmForm::AddTexViewTab(TPageControl *Page, Obd *Det)
{
	static i=0;
	TTechView *TechView=0;
	TTabSheet *tab;
	TechViewTab *t=new TechViewTab();
	tab=new TTabSheet(this); // �������� ����
	tab->ImageIndex=2;
	tab->PageControl=Page; // ������������ ����
	// �������� ���������
	// TechView=new TTechView(this);
	// ����������� ���� � ������

	t->tab=tab;
	t->module=TechView;
	t->last_tab=false;
	Tabs.push_back((Tab *)t);
	SetLastTab(tab);
	tab->Show();
	// ��������� ��������� ������ � ������
	// TechView->LoadDet(DetID);
	tab->Caption="�������� ����� �������"; // !!!!!!!!!!
}

void TmForm::LoadexViewToCurrTab(Obd *Det)
{
	Tab *t=GetTab(GetLastTab(2));
	if(t)
	{ // ������� ��������� ����
		// ((ClassConnector*)(((TechViewTab*)t)->module))->Load(det);
		t->tab->Show();
		t->tab->Caption="�������� ������� �������";
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
	tab=new TTabSheet(this); // �������� ����
	tab->PageControl=Page; // ������������ ����
	// �������� ��������� //������������ ������
	Search=new TSearch(this, tab, UserID, DB, IcoData, &selected, &_ShowTree,
		&_AddTexTab, &_LoadTexToCurrTab, 0,0/*&_AddTexViewTab,
		&_LoadexViewToCurrTab*/);
	tab->ImageIndex=3;
	// ����������� ���� � ������
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
TTabSheet * GetLastTab	(char type);
Tab*		GetTab 		(TTabSheet *tab);
*/
TTabSheet *tab=0;

	static i=0;
	TList_Editor *Process=0;
	ProcessingTab *t=new ProcessingTab();
	tab=new TTabSheet(this); // �������� ����
	tab->ImageIndex=9;
	tab->PageControl=Page; // ������������ ����
	// �������� ������ //������������ ������
	Process=new TList_Editor(this, tab, "Processing"+String(++i), UserID, DB,IcoData,&selected,&_ShowTree,
		&_AddTexTab, &_LoadTexToCurrTab, &_AddTexViewTab,
		&_LoadexViewToCurrTab);

	// ����������� ���� � ������
	t->tab=tab;
	t->module=Process;
	t->last_tab=false;
	Tabs.push_back((Tab *)t);
	SetLastTab(tab);
	//��������
	tab->Show();

}

void TmForm::AddOrders	(TPageControl *Page)
{
	TTabSheet *tab=0;

	TOrders_editor *Orders_editor=0;
	OrdersTab *t=new OrdersTab();
	tab=new TTabSheet(this); // �������� ����
	tab->ImageIndex=10;
	tab->PageControl=Page; // ������������ ����
	// �������� ������ //������������ ������
	Orders_editor=new TOrders_editor(this, tab, UserID, DB,IcoData,&selected);

	// ����������� ���� � ������
	t->tab=tab;
	t->module=Orders_editor;
	t->last_tab=false;
	Tabs.push_back((Tab *)t);
	SetLastTab(tab);
	//��������
	tab->Show();
}

void TmForm::AddManufacture(TPageControl *Page)
{
	TTabSheet *tab=0;

	TManufactureControl *ManufactureControl=0;
	ManufactureTab *t=new ManufactureTab();
	tab=new TTabSheet(this); // �������� ����
	tab->ImageIndex=10;
	tab->PageControl=Page; // ������������ ����
	// �������� ������ //������������ ������
	ManufactureControl=new TManufactureControl(this, tab, UserID, DB,IcoData,&selected);

	// ����������� ���� � ������
	t->tab=tab;
	t->module=ManufactureControl;
	t->last_tab=false;
	Tabs.push_back((Tab *)t);
	SetLastTab(tab);
	//��������
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
	InfoTab->PageControl=pc; // ������������-���������
}

void __fastcall TmForm::SpTreeClick(TObject *Sender)
{
	// ���� ��� �� ������ ������ �� �������
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
			// ���� ���� ���� ���� �������� ��������� ���������
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
			// ���� ���� ���� ���� �������� ��������� ���������
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
			// ���� ���� ���� ���� �������� ��������� ���������
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
			// ���� ���� ���� ���� �������� ��������� ���������
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
			// ���� ���� ���� ���� �������� ��������� ���������
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
			// ���� ���� ���� ���� �������� ��������� ���������
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
			// ���� ���� ���� ���� �������� ��������� ���������
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
		 case 1:{type=1;break;}//��������� ������
		 case 2:{type=2;break;}//������ ������������
		 case 3:{type=3;break;}//���� ������������
		 case 4:{type=4;break;}//����� �� ����
		 case 5:{type=5;break;}//���������� ��������
		 case 6:{type=6;break;}//����������
		 case 7:{type=7;break;}//����������
		 case 8:{type=8;break;}//���������� ���������
		 case 9:{type=9;break;}//��������� ��������� ������
		 case 10:{type=10;break;}//���� ������������ ��� �������
		 case 11:{type=11;break;}//���� ������������ ��� ������� (���)
		 default:return;
		 } */
		// �������� �����������
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
	// ��� ������ ������ ������� ������ �������� �� 5 �����
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
//���������
