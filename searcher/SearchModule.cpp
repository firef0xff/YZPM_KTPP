

#include <vcl.h>
#pragma hdrstop

#include "SearchModule.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

__fastcall TSearch::TSearch(TComponent* Owner,TWinControl *_p, int &_LUser,cSQL *db,IconsData *_IcoData,int **_selected,void *_OpenTree,void* _AddTexTab,
	void* _LoadTexToCurrTab,void* _AddTexViewTab,void* _LoadexViewToCurrTab)
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
//инициализация
Combo->Items->Clear();
String sql="select idsost,name from administration.conditions order by idsost";
TADOQuery *rez=DB->SendSQL(sql);
if (rez&&rez->RecordCount)
	{
	Combo->Items->AddObject("Все",(TObject *)-1);
	for (rez->First(); !rez->Eof; rez->Next())
		{
		Combo->Items->AddObject(rez->FieldByName("name")->Value,(TObject *)rez->FieldByName("idsost")->Value.operator int());
		}
	}
Combo->ItemIndex=0;
//деревья
MainTree->Images=IcoData->GetImgList();
MainTree->StateImages=IcoData->GetStateList();
SupportTree->Images=IcoData->GetImgList();
SupportTree->StateImages=IcoData->GetStateList();
//функция возврата
OpenTree=(void (*)(Obd *det))_OpenTree;
//функции указатели
AddTexTab=Tech(_AddTexTab);
AddTexViewTab=Tech(_AddTexViewTab);
LoadTexToCurrTab=Tech(_LoadTexToCurrTab);
LoadexViewToCurrTab=Tech(_LoadexViewToCurrTab);
if (Parent->ClassNameIs("TTabSheet"))
	{
	((TTabSheet*)Parent)->Caption="Поиск     ";
	}
//инициализация в меню
delete rez;

	SpView=false;
	TehRead=false;
	TehEdit=false;
	NormEdit=false;

	sql="call administration.Get_Rights('"+String(LUser)+"')";
	rez=DB->SendSQL(sql);
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
		}
	}
	delete rez;
	//
	N2->Enabled=SpView;
	//
	N25->Enabled=TehRead*bool(AddTexViewTab);
	N1->Enabled=TehRead*bool(LoadexViewToCurrTab);
	N24->Enabled=(TehEdit+NormEdit+TehRead)*bool(LoadTexToCurrTab);
	N31->Enabled=(TehEdit+NormEdit+TehRead)*bool(AddTexTab);
}
__fastcall 		TSearch::~TSearch(void)
{
count--;
if (count==0)
	{
	DB=0;
	IcoData=0;
	}
}
void __fastcall TSearch::RepaintPannels(TObject *Sender)
{
TPanel * pn=(TPanel *)Sender;
pn->Repaint();
Label2->Repaint();
Label1->Repaint();
Splitter1->Width=5;
Panel3->Constraints->MaxWidth=this->Width-Panel2->Constraints->MinWidth-Splitter1->Width;
Panel2->Constraints->MaxWidth=this->Width-Panel3->Constraints->MinWidth-Splitter1->Width;
Panel2->Width=this->Width-Panel3->Width-Splitter1->Width;
}
void  			TSearch::TreeClear(TTreeView *tv)
{
TTreeNode *node=tv->Items->GetFirstNode();
while (node!=0)
	{
	if ((int)node->Data)
		{
		delete ((Obd *)node->Data);
		}
	node=node->GetNext();
	}
tv->Items->Clear();
}
void  			TSearch::BranchClear(TTreeNode *Node)
{
TTreeNode *node=Node->getFirstChild();
while (node)  //перебор детей
	{
	if (node->Count) //есть дети которых надо порезать
		{
		BranchClear(node);
		}
	if ((int)node->Data)
		{
		delete ((Obd *)node->Data);
		node->Data=0;
		}
	node=node->getNextSibling();
	}
Node->DeleteChildren();
}

void __fastcall TSearch::ChgListClick(TObject *Sender)
{
TSpeedButton *bt=(TSpeedButton *)Sender;
switch (bt->Tag)
	{
	case  1:{E2->Text=String(E2->Text.ToInt()+1);break;}
	case -1:{if (E2->Text.ToInt()>1) {E2->Text=String(E2->Text.ToInt()-1);}break;}
	default:return;
	}
}
void __fastcall TSearch::ChgSListClick(TObject *Sender)
{
TSpeedButton *bt=(TSpeedButton *)Sender;
switch (bt->Tag)
	{
	case  1:{SE2->Text=String(SE2->Text.ToInt()+1);break;}
	case -1:{if (SE2->Text.ToInt()>1) {SE2->Text=String(SE2->Text.ToInt()-1);}break;}
	default:return;
	}
}
void __fastcall TSearch::E3Change(TObject *Sender)
{
if (E3->Text==""||E3->Text=="0")
	{
	E3->Text="1";
	}
if (E2->Text!="1") {E2->Text="1";} else {Find();}
}
void __fastcall TSearch::E2Change(TObject *Sender)
{
if (E2->Text==""||E2->Text=="0")
	{
	E2->Text="1";
	}
Find();
}
void __fastcall TSearch::SE3Change(TObject *Sender)
{
if (SE3->Text==""||SE3->Text=="0")
	{
	SE3->Text="1";
	}
if (SE2->Text!="1") {SE2->Text="1";} else {TreeClear(SupportTree);GetParents(LastChild,0);}
}
void __fastcall TSearch::SE2Change(TObject *Sender)
{
if (SE2->Text==""||SE2->Text=="0")
	{
	SE2->Text="1";
	}
TreeClear(SupportTree);
if (LastChild)
	{
	GetParents(LastChild,0);
	}
}

void __fastcall TSearch::AddCondClick(TObject *Sender)
{
if (M2->Lines->Count!=0 && Trim(M2->Lines->Strings[M2->Lines->Count-1])!="" && Trim(M2->Lines->Strings[M2->Lines->Count-1])!="и" && Trim(M2->Lines->Strings[M2->Lines->Count-1])!="или")
	{
	M2->Lines->Add(RG2->Items->Strings[RG2->ItemIndex]);
	}
String COLUMN;
switch (SearchParams->ItemIndex)
	{
	case 0: {COLUMN="Обозначение содержит";break;}
	case 1: {COLUMN="Наименование содержит";break;}
	case 2: {COLUMN="Заказ содержит";break;}
	case 3: {COLUMN="Изготавливается из";break;}
	default: break;
	}
if (Trim(E1->Text)!="") {M2->Lines->Add(COLUMN+" "+Trim(E1->Text));}
}

void __fastcall TSearch::E1KeyPress(TObject *Sender, wchar_t &Key)
{
if (Key==13)
	{
	StartSearchClick(StartSearch);
	}
}
void __fastcall TSearch::StartSearchClick(TObject *Sender)
{
conditions="";
String COLUMN="COLUMN",cond;
if (M2->Lines->Count)
	{
	if (conditions=="") {conditions="Where ";}
	int i=0;
	M2->WordWrap=false;
	for (i = 0; i <M2->Lines->Count; i++)
		{
		if (Trim(M2->Lines->Strings[i])!="")
			{
			if (Trim(M2->Lines->Strings[i])=="и")
				{
				conditions=conditions+" and ";
				}else
			if (Trim(M2->Lines->Strings[i])=="или")
				{
				conditions=conditions+" or ";
				} else
				{
				cond=Trim(M2->Lines->Strings[i]);
				if (cond.Pos("Обозначение содержит"))
					{
					COLUMN="obd";
					cond.Delete(cond.Pos("Обозначение содержит"),21);
					conditions=conditions+" "+COLUMN+" LIKE '%"+GostToInt(cond)+"%'";
					}
				if (cond.Pos("Наименование содержит"))
					{
					COLUMN="namd";
					cond.Delete(cond.Pos("Наименование содержит"),22);
					conditions=conditions+" "+COLUMN+" LIKE '%"+cond.Trim()+"%'";
					}
				if (cond.Pos("Заказ содержит"))
					{
					COLUMN="zakaz";
					cond.Delete(cond.Pos("Заказ содержит"),15);
					conditions=conditions+" "+COLUMN+" LIKE '%"+cond.Trim()+"%'";
					}
				if (cond.Pos("Изготавливается из"))
					{
					COLUMN="obmid";
					cond.Delete(cond.Pos("Изготавливается из"),22);
					conditions=conditions+" "+COLUMN+" in (select id from constructions.det_names where obd like '%"+cond.Trim()+"%')";
					}
				}
			}
		}
	M2->WordWrap=true;
	} else
	{
	String val="";
	if (E1->Text.Trim()!="")
		{
		switch (SearchParams->ItemIndex)
			{
			case 0: {
					COLUMN="obd";val=GostToInt(E1->Text.Trim());
					conditions="Where "+COLUMN+" LIKE '%"+val+"%'";
					break;}
			case 1: {
					COLUMN="namd";val=E1->Text.Trim();
					conditions="Where "+COLUMN+" LIKE '%"+val+"%'";
					break;}
			case 2: {
					COLUMN="zakaz";val=E1->Text.Trim();
					conditions="Where "+COLUMN+" LIKE '%"+val+"%'";
					break;}
			case 3: {
					COLUMN="obmid";val=E1->Text.Trim();
					conditions="Where "+COLUMN+" in (select id from constructions.det_names where obd like '%"+val+"%')";
					break;}
			default: return;
			}
		}
	}
M2->Clear();
if (E2->Text=="1")
	{
	Find();
	}else
	{
	E2->Text="1";  //срабатывет onChange а ссылка который и вызывает Find
	}
//E1->Text="";
M2->Lines->Clear();
}
String  		TSearch::GetConditions(int User_ID)
{
String result="'0',";
String sql="select a.idCond from administration.gtucond a inner join administration.conditions b on b.idsost=a.idCond inner join administration.logins c on c.Levelacss=a.IdGroup where c.LogID='"+String(User_ID)+"' and b.arhive=0";
TADOQuery *rez=DB->SendSQL(sql);
if (rez&&rez->RecordCount)
	{
	rez->First();
	while (!rez->Eof)
		{
		result=result+"'"+rez->FieldByName("idcond")->Value+"',";
		rez->Next();
		}
	}
delete rez; rez=0;
result.Delete(result.Length(),1);
return result;
}
void 			TSearch::Find	(void)
{
TreeClear(MainTree);
String condition=conditions;
String sql="select a.id,a.obd,a.namd,a.razdSPID,b.Razdname from constructions.det_names a  join administration.sprazd b on b.RazdID=a.razdSPID ";
if (condition.Pos(" zakaz "))
	{
	//добавить вхождение в заказы
	sql+="right join market.zakaz c on c.id=a.id ";
	sql+="right join market.Orders c1 on c.zakaz_id=c1.zakaz_id ";
	}
if (condition.Pos(" obmid "))
	{
    //добавить вхождение в технологии
	sql+="join technologic.det_info d on d.id=a.id " ;
	}
//разделы поиска
String razd=" razdSPID in(";
if (products->Checked)
	{
	razd+="'0',";
	}
if (assemblies->Checked)
	{
	razd+="'2','3','8',";
	}
if (details->Checked)
	{
	razd+="'4',";
	}
if (stdelements->Checked)
	{
    razd+="'5','6','7',";
	}
razd.Delete(razd.Length(),1);
razd+=")";
if (razd.Length()==13)
	{
	razd=" razdSPID in('999')";
	}
if (condition.Length())
	{
	condition="Where ("+condition.Delete(condition.Pos("Where"),5)+" ) and"+razd;
	}else
	{
	condition="Where "+razd;
	}
if (Combo->ItemIndex)
	{
	condition=condition+" and a.state="+(String)((int)Combo->Items->Objects[Combo->ItemIndex]);
	}
if (CB1->Checked)
	{
	if (!condition.Length())
		{
		condition="Where UserID='"+String(LUser)+"'";
		}else
		{
		condition="Where ("+condition.Delete(condition.Pos("Where"),5)+" ) and UserID='"+String(LUser)+"'";
		}
	}
if (CB3->Checked)
	{
	if (!condition.Length())
		{
		condition="Where state in ("+GetConditions(LUser)+")";
		} else
		{
		condition="Where ("+condition.Delete(condition.Pos("Where"),5)+" ) and state in ("+GetConditions(LUser)+")";
		}
	}
if (conditions.Length())
	{
	sql=sql+condition+" order by a.razdSPID,a.obd,a.namd  limit "+String(E2->Text.ToInt()*E3->Text.ToInt()-E3->Text.ToInt())+","+E3->Text;
	}else
	{
	sql=sql+condition+"  limit "+String(E2->Text.ToInt()*E3->Text.ToInt()-E3->Text.ToInt())+","+E3->Text;
	}
TreeClear(SupportTree);
FillTV(MainTree,0,sql);
}
void 			TSearch::FillTV(TTreeView *tv,TTreeNode *StartNode,String sql,bool AsChild,bool CanChild)
{
TADOQuery *rez=DB->SendSQL(sql);
if (rez&&rez->RecordCount)
	{
	//наполнение сетки
	String name,obd,razd_name;
	int id,razd;
	rez->First();
	Obd *data;
	TTreeNode *node=StartNode;
	while (!rez->Eof)
		{
		data=new Obd(DB);
		name=rez->FieldByName("namd")->Value;
		obd=rez->FieldByName("obd")->Value;
		id=rez->FieldByName("id")->Value;
		razd=rez->FieldByName("razdSPID")->Value;
		razd_name=rez->FieldByName("Razdname")->Value;
		if (data->SetData(id,razd,obd,name,razd_name))
			{
			if (node==StartNode&&AsChild)
				{
				node=tv->Items->AddChildObject(node,data->Get_Text(),(void *)data);
				}else
				{
				node=tv->Items->AddObject(node,data->Get_Text(),(void *)data);
				}
			if (CanChild)
				{
				tv->Items->AddChildObject(node,"",0);
				}
			node->ImageIndex=IcoData->GetInList(razd,true,1);
			node->SelectedIndex=node->ImageIndex;
			node->ExpandedImageIndex=node->ImageIndex;
			node->StateIndex=0;
			}else
			{
			delete data;
			}
		rez->Next();
		}
	}
delete rez;
}
void __fastcall TSearch::refindClick(TObject *Sender)
{
if (Sender->ClassNameIs("TComboBox"))
	{
	TComboBox *cb=(TComboBox *)Sender;
	int id=(int)cb->Items->Objects[cb->ItemIndex];
	IMG->Picture->Bitmap=0;
	TImageList *ico=IcoData->GetStateList();
	ico->GetBitmap(IcoData->GetInList(id,true,0),IMG->Picture->Bitmap);
	}
if (E2->Text=="1")
	{
	Find();
	}else
	{
	E2->Text="1";
	}
}

void __fastcall TSearch::MainTreeClick(TObject *Sender)
{
// найти вхождения
TTreeView *tv=(TTreeView *)Sender;
TPoint s;                  //вычисление кликнутой ячейки
GetCursorPos(&s);
s=tv->ScreenToClient(s);
TTreeNode *node=tv->GetNodeAt(s.X,s.Y);
if (node&&node==tv->Selected)
	{
	LastChild=(Obd *)node->Data;
	TreeClear(SupportTree);
	GetParents(LastChild,0);
	}
TreeClick(Sender);
}
void __fastcall TSearch::SupportTreeExpanding(TObject *Sender, TTreeNode *Node, bool &AllowExpansion)
{
BranchClear(Node);
Obd *data=(Obd *)Node->Data;
GetParents(data,Node,true);
}
void 			TSearch::GetParents(Obd *data,TTreeNode *Node,bool AsChild)
{
if (data)
	{
	int id=data->Get_ID();
	String sql="call constructions.GetParents('"+String(id)+"','"+String(SE2->Text.ToInt()*SE3->Text.ToInt()-SE3->Text.ToInt())+"','"+SE3->Text+"')";
	FillTV(SupportTree,Node,sql,AsChild,true);
	sql="select b.zakaz from market.zakaz a join market.orders b on a.zakaz_id=b.zakaz_id where a.id="+String(id)+" limit "+String(SE2->Text.ToInt()*SE3->Text.ToInt()-SE3->Text.ToInt())+","+SE3->Text;
	TADOQuery *rez=DB->SendSQL(sql);
	if (rez&&rez->RecordCount)
		{
		rez->First();
		TTreeNode *node=0;
		while (!rez->Eof)
			{
			if (AsChild)
				{
				node=SupportTree->Items->AddChildObject(Node,rez->FieldByName("zakaz")->Value,0);
				}else
				{
				node=SupportTree->Items->AddObject(Node,rez->FieldByName("zakaz")->Value,0);
				}
			node->ImageIndex=-1;
			node->SelectedIndex=node->ImageIndex;
			node->ExpandedImageIndex=node->ImageIndex;
			node->StateIndex=-1;
			rez->Next();
			}
		}
	delete rez;
	}
}
void __fastcall TSearch::MainTreeDblClick(TObject *Sender)
{
// передать объект на спецификацию
TTreeView *tv=(TTreeView *)Sender;
TPoint s;                  //вычисление кликнутой ячейки
GetCursorPos(&s);
s=tv->ScreenToClient(s);
TTreeNode *node=tv->GetNodeAt(s.X,s.Y);
if (node&&node==tv->Selected)
	{
	Obd *data=(Obd *)node->Data;
	if (data)
		{
		OpenTree(data);
		}
	}
//вызов обратной функции
}

void __fastcall TSearch::HideBtnClick(TObject *Sender)
{
TButton *btn=(TButton *)Sender;
if (btn)
	{
	if (btn->Tag)
		{
		Panel1->Height=148;
		btn->Tag=0;
		}else
		{
		Panel1->Height=36;
		btn->Tag=1;
		}
	}
}


void __fastcall TSearch::N2Click(TObject *Sender)
{
TTreeView *tv=0;
if (MainTree->Focused()) {tv=MainTree;}
if (SupportTree->Focused()) {tv=SupportTree;}
if (tv)
	{
	if (tv->Selected)
		{
		Obd *data=(Obd *)tv->Selected->Data;
		if (data)
			{
			OpenTree(data);
			}
		}
	}
}
void __fastcall TSearch::TechAction(TObject *Sender)
{
TTreeNode *node=0;
if (MainTree->Focused())
	{
	node=MainTree->Selected;
	}
if (SupportTree->Focused())
	{
	node=SupportTree->Selected;
	}
if (node)
	{
	//объект
	TMenuItem *m=(TMenuItem *)Sender;
	Obd *bag=(Obd*)node->Data;
	Obd *det=new Obd(*bag);
	switch (m->Tag)
		{
		case 1:{AddTexTab(det);break;} 	//редактировать новая вкладка
		case 0:{LoadTexToCurrTab(det);break;}       	//редактировать текущая вкладка
		case 3:{AddTexViewTab(det);break;}//просмотр новая вкладка
		case 2:{LoadexViewToCurrTab(det);break;}    	//просмотр текущая вкладка
		default:break;
		}
	bag->UpdateVal();
	}
}
void __fastcall  TSearch::TreeClick(TObject *Sender)
{
	TTreeView *tv=(TTreeView *)Sender;
	if (*selected)
	{
		delete []*selected;
		*selected=0;
	}
	if (tv->SelectionCount)
	{
		*selected =new int[tv->SelectionCount+1];
		**selected=tv->SelectionCount; //первое значение массива это номер последнего элемента
		for (size_t i=1; i <= tv->SelectionCount; i++)
		{
			Obd *det=(Obd*)tv->Selections[i-1]->Data;
			if (det&&det->CanUse())
			{
			*(*selected+i)=det->Get_ID();
			}else
			{
            *(*selected+i)=0;
			}
		}
	}
}
//---------------------------------------------------------------------------

