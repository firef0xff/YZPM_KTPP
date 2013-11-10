
#include <vcl.h>
#pragma hdrstop

#include "BomTree.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

__fastcall 		TSpTree::TSpTree(TComponent* Owner,TWinControl *_p,cSQL *db,const int &_LUser,TMemo *m,IconsData *_IcoData,int **_selected,void* _AddTexTab,
	void* _LoadTexToCurrTab,void* _AddTexViewTab,void* _LoadexViewToCurrTab)
	: TFrame(Owner),LUser(_LUser),selected(_selected)
{
// получить список доступных компонентов и сделать не активными не доступные

if (count==0)
	{
	DB=db;
	IcoData=_IcoData;
	}
Selector=new TObdSelector(this,(ClassConnector*)this,Panel3,db);
//функции указатели
AddTexTab=Tech(_AddTexTab);
AddTexViewTab=Tech(_AddTexViewTab);
LoadTexToCurrTab=Tech(_LoadTexToCurrTab);
LoadexViewToCurrTab=Tech(_LoadexViewToCurrTab);
// расположение
Align=alClient;
Parent=_p;
Name=Name+String(count);
memo=m;
Init();
Tree->Images=IcoData->GetImgList();
Tree->StateImages=IcoData->GetStateList();
count++;
MassAction=false;
N10->Checked=!MassAction;
N9->Checked=MassAction;
if (Parent->ClassNameIs("TTabSheet"))
	{
	((TTabSheet*)Parent)->Caption="Спецификация     ";
	}
}
__fastcall 		TSpTree::~TSpTree(void)
{
count--;
if (count==0)
	{
	DB=0;
	IcoData=0;
	}
TreeClear();
}
void  			TSpTree::Init 	 (void)
{
	bool 	FileInsert=false,
			FileDel=false,
			FileEdit=false,
			FileView=false,
			SpInsert=false,
			SpDel=false,
			SpEdit=false,
			SpView=false,
			TehAdd=false,
			TehRead=false,
			TehEdit=false,
			TehDel=false,
			FileGet=false;

	String sql="call administration.Get_Rights('"+String(LUser)+"')";
	TADOQuery *rez=DB->SendSQL(sql);
	if(rez&&rez->RecordCount)
	{
		for (rez->First(); !rez->Eof; rez->Next())
		{
			const String val=rez->FieldByName("progname")->Value;
			if (val=="FileInsert")
			{
				FileInsert=true;
			}
			if (val=="FileDel")
			{
				FileDel=true;
			}
			if (val=="FileEdit")
			{
				FileEdit=true;
			}
			if (val=="FileView")
			{
				FileView=true;
			}
			if (val=="FileGet")
			{
				FileGet=true;
			}
			if (val=="SpInsert")
			{
				SpInsert=true;
			}
			if (val=="SpDel")
			{
				SpDel=true;
			}
			if (val=="SpEdit")
			{
				SpEdit=true;
			}
			if (val=="SpView")
			{
				SpView=true;
			}
			if (val=="TehSave")
			{
				TehAdd=true;
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
		}
	}
	delete rez;
	//файл
	N11->Enabled=FileInsert+FileEdit;
	N4->Enabled=FileGet;
	N5->Enabled=FileDel;
	N11->Visible=FileInsert+FileEdit;
	N4->Visible=FileGet;
	N5->Visible=FileDel;
	N3->Visible=FileInsert+FileGet+FileDel;
	// технология

	N24->Enabled=(TehAdd+TehEdit+TehRead)*bool(AddTexTab);
	N24->Visible=(TehAdd+TehEdit+TehRead)*bool(AddTexTab);
	N1->Visible=TehRead*bool(AddTexViewTab);
	N1->Enabled=TehRead*bool(AddTexViewTab);
	N31->Visible=(TehAdd+TehEdit+TehRead)*bool(LoadTexToCurrTab);
	N31->Enabled=(TehAdd+TehEdit+TehRead)*bool(LoadTexToCurrTab);
	N25->Enabled=TehRead*bool(LoadexViewToCurrTab);
	N25->Visible=TehRead*bool(LoadexViewToCurrTab);
	N12->Enabled=TehDel;
	N12->Visible=TehDel;
	N17->Visible=TehAdd+TehEdit+TehRead+TehDel;
	// спецификация
	N15->Enabled=SpInsert;
	N16->Enabled=SpEdit;
	N29->Enabled=SpView;
	N18->Enabled=FileView;
	N19->Enabled=SpDel;

	N15->Visible=SpInsert;
	N16->Visible=SpEdit;
	N29->Visible=SpView;
	N18->Visible=FileView;
	N19->Visible=SpDel;

	N13->Visible=SpInsert+SpEdit+SpView+SpDel;
}

void  			TSpTree::TreeClear(void)
{
TTreeNode *node=Tree->Items->GetFirstNode();
while (node!=0)
	{
	if ((int)node->Data)
		{
		delete (Obd *)node->Data;
		}
	node=node->GetNext();
	}
Tree->Items->Clear();
}
void  			TSpTree::BranchClear(TTreeNode *Node)
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
		delete (Obd *)node->Data;
		node->Data=0;
		}
	node=node->getNextSibling();
	}
Node->DeleteChildren();
}
void  			TSpTree::LoadTree (int _id)
{
TreeClear();
TTreeNode *node;
TreeRow *row;
TADOQuery *rez;
String sql;
sql="Call constructions.LoadDet('"+String(_id)+"','"+String(LUser)+"')";  //загрузка информации о детали формировавние раздела документация
rez=DB->SendSQL(sql);
if (rez&&rez->RecordCount)
	{
	int id,idparent,sprazd,pp,ppp,ei,state,userid;
	String obd,obu,name,sprazdname,format,pos,prim,zona,ppname,einame,user,condname,detcreator,
	detupdater,rowcreator,rowupdater;
	double kol;
	bool arhive,canchild,accept;
	TDateTime  detcreated,detupdated,rowcreated,rowupdated;

	rez->First();
	row=new TreeRow(DB,LUser);

	id=rez->FieldByName("idchild")->Value;
	idparent=rez->FieldByName("idparent")->Value;
	sprazd=rez->FieldByName("razdSPID")->Value;
	pp=rez->FieldByName("pp")->Value.operator UnicodeString().ToInt();
	ppp=rez->FieldByName("ppp")->Value.operator UnicodeString().ToInt();
	ei=rez->FieldByName("ei")->Value.operator UnicodeString().ToInt();
	state=rez->FieldByName("state")->Value;
	userid=rez->FieldByName("UserID")->Value;
	obd=rez->FieldByName("obd")->Value;
	obu=rez->FieldByName("obu")->Value;
	name=rez->FieldByName("name")->Value;
	sprazdname=rez->FieldByName("Razdname")->Value;
	format=rez->FieldByName("format")->Value;
	pos=rez->FieldByName("pos")->Value;
	prim=rez->FieldByName("prim")->Value;
	zona=rez->FieldByName("zona")->Value;
	ppname=rez->FieldByName("ppName")->Value;
	einame=rez->FieldByName("eiName")->Value;
	user=rez->FieldByName("User")->Value;
	condname=rez->FieldByName("CondName")->Value;
	detcreator=rez->FieldByName("DetCreator")->Value;
	detupdater=rez->FieldByName("DetUpdater")->Value;
	rowcreator=rez->FieldByName("RowCreator")->Value;
	rowupdater=rez->FieldByName("RowUpdater")->Value;
	kol=rez->FieldByName("kol")->Value;
	arhive=rez->FieldByName("arhive")->Value;
	canchild=rez->FieldByName("CanChild")->Value;
	accept=rez->FieldByName("Accept")->Value;
	if (!rez->FieldByName("DetCreated")->Value.IsNull()){detcreated=rez->FieldByName("DetCreated")->Value.operator TDateTime();}else{detcreated=0;}
	if (!rez->FieldByName("DetUpdated")->Value.IsNull()){detupdated=rez->FieldByName("DetUpdated")->Value.operator TDateTime();}else{detupdated=0;}
	if (!rez->FieldByName("RowCreated")->Value.IsNull()){rowcreated=rez->FieldByName("RowCreated")->Value.operator TDateTime();}else{rowcreated=0;}
	if (!rez->FieldByName("RowUpdated")->Value.IsNull()){rowupdated=rez->FieldByName("RowUpdated")->Value.operator TDateTime();}else{rowupdated=0;}
	row->SetData(id,idparent,sprazd,pp,ppp,ei,state,userid,obd,obu,name,
				sprazdname,format,pos,prim,zona,ppname,einame,user,
				condname,detcreator,detupdater,rowcreator,rowupdater,
				kol,arhive,canchild,accept,detcreated,detupdated,rowcreated,
				rowupdated);
	//создание узла
	node=Tree->Items->AddObject(0,row->Get_Text(),(void*)row);
	node->ImageIndex=IcoData->GetInList(row->Get_SpRazd(),true,1);
	node->SelectedIndex=node->ImageIndex;
	node->ExpandedImageIndex=node->ImageIndex;
	node->StateIndex=IcoData->GetInList(row->Get_state(),row->Get_Accept(),0);
	if (row->Get_CanChild())
		{
		Obd *r=new Obd(*((Obd*)row));
		r->SetData(r->Get_ID(),1,r->Get_Obd(false),r->Get_Name(),"Документация"); //создание раздела документация, прикрепление к нему фыйлов
		node=Tree->Items->AddChildObject(node,r->Get_SpRazdName(),(void*)r);
		node->ImageIndex=IcoData->GetInList(r->Get_SpRazd(),true,1);
		node->SelectedIndex=node->ImageIndex;
		node->ExpandedImageIndex=node->ImageIndex;
		node->StateIndex=-1;
		}
	LoadFiles(node);
	if (row->Get_CanChild())
		{
		LoadBranch(Tree->Items->GetFirstNode());// если кен чилд то LoadBranch
		}
	}
if (Tree->Items->GetFirstNode())
	{
	Tree->Items->GetFirstNode()->Expand(false);
	}
delete rez;
}
void  			TSpTree::LoadTree (TTreeNode *Node)
{
Obd* bag=(Obd*)Node->Data;
if (!bag) {return;}
if (bag->TrueClassName()=="TreeRow")
	{
	TreeRow *row=(TreeRow*)bag;
	TTreeNode *node=Node;
	bool force=row->Get_Force();
	row->UpdateVal();
	node->ImageIndex=IcoData->GetInList(row->Get_SpRazd(),true,1);
	node->SelectedIndex=node->ImageIndex;
	node->ExpandedImageIndex=node->ImageIndex;
	node->StateIndex=IcoData->GetInList(row->Get_state(),row->Get_Accept(),0);
	if (row->Get_CanChild()||force) //создание раздела документация, прикрепление к нему фaйлов
		{   //добавить в контейнер обд и тут оперировать им
		Obd *r=new Obd(*((Obd*)row));
		r->SetData(r->Get_ID(),1,r->Get_Obd(false),r->Get_Name(),"Документация"); //создание раздела документация, прикрепление к нему фыйлов
		node=Tree->Items->AddChildObject(node,r->Get_SpRazdName(),(void*)r);
		node->ImageIndex=IcoData->GetInList(r->Get_SpRazd(),true,1);
		node->SelectedIndex=node->ImageIndex;
		node->ExpandedImageIndex=node->ImageIndex;
		node->StateIndex=-1;
		}
	LoadFiles(node);  // если кен чилд то LoadBranch
	if (row->Get_CanChild()||force)
		{
		LoadBranch(Node);
		}
	}
}
void  			TSpTree::LoadBranch(TTreeNode *Node)
{  // продолжение отдельной функцией получения состава
Obd* t=(Obd*)Node->Data;
if (!t) {return;}
if (t->TrueClassName()=="TreeRow")
	{ //загрузка информации о составе детали формирования остальных разделов
	TreeRow *row=(TreeRow*)t;
	int id=row->Get_ID();
	String sql="Call constructions.LoadTree('"+String(id)+"','"+String(LUser)+"')";
	TADOQuery *rez=DB->SendSQL(sql);
	if (rez&&rez->RecordCount)
		{
		rez->First();
		String CurRazd="";
		TTreeNode *node,*pnode;
		int id,idparent,sprazd,pp,ppp,ei,state,userid;
		String obd,obu,name,sprazdname,format,pos,prim,zona,ppname,einame,user,condname,detcreator,
		detupdater,rowcreator,rowupdater;
		double kol;
		bool arhive,canchild,accept;
		TDateTime  detcreated,detupdated,rowcreated,rowupdated;
		while (!rez->Eof)
			{
			row=new TreeRow(DB,LUser);
			id=rez->FieldByName("idchild")->Value;
			idparent=rez->FieldByName("idparent")->Value;
			sprazd=rez->FieldByName("razdSPID")->Value;
			pp=rez->FieldByName("pp")->Value.operator UnicodeString().ToInt();
			ppp=rez->FieldByName("ppp")->Value.operator UnicodeString().ToInt();
			ei=rez->FieldByName("ei")->Value.operator UnicodeString().ToInt();
			state=rez->FieldByName("state")->Value;
			userid=rez->FieldByName("UserID")->Value;
			obd=rez->FieldByName("obd")->Value;
			obu=rez->FieldByName("obu")->Value;
			name=rez->FieldByName("name")->Value;
			sprazdname=rez->FieldByName("Razdname")->Value;
			format=rez->FieldByName("format")->Value;
			pos=rez->FieldByName("pos")->Value;
			prim=rez->FieldByName("prim")->Value;
			zona=rez->FieldByName("zona")->Value;
			ppname=rez->FieldByName("ppName")->Value;
			einame=rez->FieldByName("eiName")->Value;
			user=rez->FieldByName("User")->Value;
			condname=rez->FieldByName("CondName")->Value;
			detcreator=rez->FieldByName("DetCreator")->Value;
			detupdater=rez->FieldByName("DetUpdater")->Value;
			rowcreator=rez->FieldByName("RowCreator")->Value;
			rowupdater=rez->FieldByName("RowUpdater")->Value;
			kol=rez->FieldByName("kol")->Value;
			arhive=rez->FieldByName("arhive")->Value;
			canchild=rez->FieldByName("CanChild")->Value;
			accept=rez->FieldByName("Accept")->Value;
			if (!rez->FieldByName("DetCreated")->Value.IsNull()){detcreated=rez->FieldByName("DetCreated")->Value.operator TDateTime();}else{detcreated=0;}
			if (!rez->FieldByName("DetUpdated")->Value.IsNull()){detupdated=rez->FieldByName("DetUpdated")->Value.operator TDateTime();}else{detupdated=0;}
			if (!rez->FieldByName("RowCreated")->Value.IsNull()){rowcreated=rez->FieldByName("RowCreated")->Value.operator TDateTime();}else{rowcreated=0;}
			if (!rez->FieldByName("RowUpdated")->Value.IsNull()){rowupdated=rez->FieldByName("RowUpdated")->Value.operator TDateTime();}else{rowupdated=0;}
			row->SetData(id,idparent,sprazd,pp,ppp,ei,state,userid,obd,obu,name,
						sprazdname,format,pos,prim,zona,ppname,einame,user,
						condname,detcreator,detupdater,rowcreator,rowupdater,
						kol,arhive,canchild,accept,detcreated,detupdated,rowcreated,
						rowupdated);
			if (CurRazd!=row->Get_SpRazdName())
				{
				pnode=Node->Owner->AddChildObject(Node,row->Get_SpRazdName(),0);
				pnode->ImageIndex=IcoData->GetInList(row->Get_SpRazd(),true,1);
				pnode->SelectedIndex=pnode->ImageIndex;
				pnode->ExpandedImageIndex=pnode->ImageIndex;
				pnode->StateIndex=-1;
				CurRazd=row->Get_SpRazdName();
				}
			node=Node->Owner->AddChildObject(pnode,row->Get_Text(),(void*)row);
			node->ImageIndex=IcoData->GetInList(row->Get_SpRazd(),true,1);
			node->SelectedIndex=node->ImageIndex;
			node->ExpandedImageIndex=node->ImageIndex;
			node->StateIndex=IcoData->GetInList(row->Get_state(),row->Get_Accept(),0);
			if (row->Get_CanChild()) //создание раздела документация, прикрепление к нему фaйлов
				{   //добавить в контейнер обд и тут оперировать им
				Obd *r=new Obd(*((Obd*)row));
				r->SetData(r->Get_ID(),1,r->Get_Obd(false),r->Get_Name(),"Документация"); //создание раздела документация, прикрепление к нему фыйлов
				node=Tree->Items->AddChildObject(node,r->Get_SpRazdName(),(void*)r);
				node->ImageIndex=IcoData->GetInList(r->Get_SpRazd(),true,1);
				node->SelectedIndex=node->ImageIndex;
				node->ExpandedImageIndex=node->ImageIndex;
				node->StateIndex=-1;
				}
			LoadFiles(node);
			rez->Next();
			}
		}
	delete rez;
	}
}
void  			TSpTree::UpdateBranch(TTreeNode *Node,bool force=false)
{
Obd *bag=(Obd *)Node->Data;
if (bag&&bag->TrueClassName()=="TreeRow")
	{
	TreeRow *Row=(TreeRow*)bag;
	Row->Set_Force(force);
	Node->Owner->AddChildObject(Node,"",0);
	//Node->Expand(false);
	BranchClear(Node);
	LoadTree(Node);
	}
}
void  			TSpTree::LoadFiles(TTreeNode *Node)
{
FileRow *file;
TTreeNode *node;
int _id=((Obd*)Node->Data)->Get_ID();
String sql="Call constructions.LoadFiles('"+String(_id)+"','"+String(LUser)+"')";
TADOQuery *rez=DB->SendSQL(sql);
if (rez&&rez->RecordCount)
	{
	rez->First();
	int id,sprazd,icoid;
	String obd,name,sprazdname,filename,filepath,creator,updater;
	bool accept;
	TDateTime dateofcreate,dateofupdate;
	while (!rez->Eof)
		{
		file=new FileRow(DB,LUser); //создание ксаса свойств
		//заполнение свойств файла
		id=rez->FieldByName("id")->Value;
		sprazd=rez->FieldByName("razdSPID")->Value;
		icoid=rez->FieldByName("icoID")->Value;
		obd=rez->FieldByName("obd")->Value;
		name=rez->FieldByName("namd")->Value;
		sprazdname=rez->FieldByName("Razdname")->Value;
		filename=rez->FieldByName("FileName")->Value;
		filepath=rez->FieldByName("FilePath")->Value;
		creator=rez->FieldByName("Creator")->Value;
		updater=rez->FieldByName("Updater")->Value;
		accept=rez->FieldByName("Accept")->Value;
		if (!rez->FieldByName("DateOfCreate")->Value.IsNull()){dateofcreate=rez->FieldByName("DateOfCreate")->Value.operator TDateTime();}else{dateofcreate=0;}
		if (!rez->FieldByName("DateOfUpdate")->Value.IsNull()){dateofupdate=rez->FieldByName("DateOfUpdate")->Value.operator TDateTime();}else{dateofupdate=0;}
		file->SetData	(id,sprazd,obd,name,sprazdname,icoid,
						filename,filepath,creator,updater,accept,
						dateofcreate,dateofupdate);
		node=Node->Owner->AddChildObject(Node,file->Get_Text(),(void*)file);
		node->ImageIndex=IcoData->GetInList(file->Get_icoID(),true,2);
		node->SelectedIndex=node->ImageIndex;
		node->ExpandedImageIndex=node->ImageIndex;
		node->StateIndex=-1;
		rez->Next();
		}
	}
delete rez;
}
void __fastcall TSpTree::TreeExpanding(TObject *Sender, TTreeNode *Node, bool &AllowExpansion)
{
Obd *bag=(Obd *)Node->Data;
if (Node->Level&&bag&&bag->TrueClassName()=="TreeRow"&&!((TreeRow*)bag)->Get_Force())
	{
	BranchClear(Node);
	LoadTree(Node);
	}
}
void __fastcall TSpTree::TreeMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y)
{
TTreeView* TV=(TTreeView*)Sender;
Selection(TV,Shift,X,Y);
TTreeNode *node=TV->GetNodeAt(X,Y);
if (!node) {return;}
if (node==TV->Selected&&memo)
	{
	memo->Lines->Clear();
	if (node->Data)
		{
		Obd *bag=(Obd *)node->Data;
		if (bag->TrueClassName()=="TreeRow")
			{
			TreeRow* row=(TreeRow*)bag;
			if (row->Get_CanChild())
				{
				node=node->getFirstChild();
				}
			}
		if (bag->TrueClassName()=="FileRow")
			{
			node=node->Parent;
			}
		GetInfo(node);
		}
	}
}
void  			TSpTree::GetInfo(TTreeNode *Node)
{
Obd *bag=(Obd *)Node->Data;
TreeRow *tr(0);
FileRow *fl(0);
if (bag->ItTrueClassName())
	{
	tr=(TreeRow *)Node->Parent->Data;
	}else
	{
	tr=(TreeRow *)Node->Data;
	}

// расписать информацию об узле/детали
memo->Lines->Add("Информация по спецификации");
memo->Lines->Add("Деталь: "+tr->Get_Text());
memo->Lines->Add("Формат: "+tr->Get_format());
memo->Lines->Add("Зона: "+tr->Get_zona());
memo->Lines->Add("Позиция: "+tr->Get_pos());
memo->Lines->Add("Кол-во: "+String(tr->Get_kol())+" "+tr->Get_eiName());
memo->Lines->Add("Признак производства: "+IntToStr(tr->Get_pp())+" - "+tr->Get_ppName());
memo->Lines->Add("Примечание: "+tr->Get_prim());
memo->Lines->Add("");
// расписать информацию о блокираторах и создателях
memo->Lines->Add("Работы c деталью/спецификацией");
memo->Lines->Add("Текущее состояние: "+tr->Get_CondName());
String dat="";
if (tr->Get_DetCreated().Val){dat=tr->Get_DetCreated();}else{dat="";}
memo->Lines->Add("Дата создания: "+dat);
memo->Lines->Add("Создал: "+tr->Get_DetCreator());
if (tr->Get_DetUpdated().Val){dat=tr->Get_DetUpdated();}else{dat="";}
memo->Lines->Add("Дата редактирования: "+dat);
memo->Lines->Add("Редактировал: "+tr->Get_DetUpdater());
if (tr->Get_RowCreated().Val){dat=tr->Get_RowCreated();}else{dat="";}
memo->Lines->Add("Внесена в спец-ю: "+dat);
memo->Lines->Add("Внес: "+tr->Get_RowCreator());
if (tr->Get_RowUpdated().Val){dat=tr->Get_RowUpdated();}else{dat="";}
memo->Lines->Add("Редактирование спец-и:"+dat);
memo->Lines->Add("Редактировал: "+tr->Get_RowUpdater());
memo->Lines->Add("");
memo->Lines->Add("Занято пользователем: ");
memo->Lines->Add(tr->Get_User());
memo->Lines->Add("");
// расписать информацию о входящих файлах
if (Node->Count)
	{
	memo->Lines->Add("Количество прикрепленных файлов: "+IntToStr(Node->Count));
	TTreeNode *node=Node->getFirstChild();
	while (node)
		{
		bag=(Obd *)node->Data;
		if (bag&&bag->TrueClassName()=="FileRow")
			{
			FileRow *fl=(FileRow*)bag;
			if (fl)
				{
				memo->Lines->Add("Файл: "+fl->Get_FileName());//данные о файле
				//memo->Lines->Add("Текущее состояние: "+fl->CondName);
				if (fl->Get_DateOfCreate().Val){dat=fl->Get_DateOfCreate();}else{dat="";}
				memo->Lines->Add("Дата добавления: "+dat);
				memo->Lines->Add("Добавил: "+fl->Get_Creator());
				if (fl->Get_DateOfUpdate().Val){dat=fl->Get_DateOfUpdate();}else{dat="";}
				memo->Lines->Add("Обновлен: "+dat);
				memo->Lines->Add("Обновил: "+fl->Get_Updater());
			   //	memo->Lines->Add("Занято пользователем: "+fl->User);
				memo->Lines->Add("");
				}
			}
		node=node->getNextSibling();
		}
	}
// расписать  инфо о дате последнего запуска в производство;
}

void __fastcall TSpTree::N14Click(TObject *Sender)
{ 
UpdateBranch(Tree->Selected,true);
Tree->Selected->Expand(false);
}
void __fastcall TSpTree::N23Click(TObject *Sender)
{
int id=((Obd*)Tree->Items->GetFirstNode()->Data)->Get_ID();
LoadTree(id);
}
void __fastcall TSpTree::N21Click(TObject *Sender)
{
TTreeNode *node=Tree->Selected;
if (node)
	{
	node->Expand(true);
	}
}
void __fastcall TSpTree::N22Click(TObject *Sender)
{
TTreeNode *node=Tree->Selected;
if (node)
	{
	node->Collapse(true);
	}
}

void __fastcall TSpTree::N41Click(TObject *Sender)
{
TTreeView *TV=Tree;
String ids="";
Obd *det=0;
for (unsigned int i=0; i < TV->SelectionCount; i++)
	{
	det=(Obd*)TV->Selections[i]->Data;
	if (det&&det->TrueClassName()=="TreeRow")
		{
		TreeRow *Row=(TreeRow *)det;
		Row->UpdateVal();
		if (Row->Get_Accept())
			{
			ids=ids+String(Row->Get_ID())+",";
			}
		}
	}
if (ids!="")
	{
	ids.Delete(ids.Length(),1);
	if (((TMenuItem*)Sender)->Tag)
		{
		UnBlock(ids); //разблокировка
		}else
		{
		Block(ids);  //блокировка
		}
	for (unsigned int i=0; i < TV->SelectionCount; i++)
		{
		UpdateInfo(TV->Selections[i]);
		}
	TV->Repaint();
	}
}
void  			TSpTree::Block(String &ids)
{
String sql;
if (!MassAction)
	{
	sql="Call constructions.block('"+ids+"','"+String(LUser)+"')";
	} else
	{
	sql="Call constructions.blockALL('"+ids+"','"+String(LUser)+"')";
	}
DB->SendCommand(sql);
return;
}
void  			TSpTree::UnBlock(String &ids)
{
String sql;
if (!MassAction)
	{
	sql="Call constructions.unblock('"+ids+"','"+String(LUser)+"')";
	} else
	{
	sql="Call constructions.unblockALL('"+ids+"','"+String(LUser)+"')";
	}
!DB->SendCommand(sql);
return;
}

void __fastcall TSpTree::N11Click(TObject *Sender)
{
TFileDisigner *wnd=new TFileDisigner(this->Owner,DB,LUser,0,false,0);
wnd->ShowModal();
delete wnd;
// добавить
if (Tree->Items->Count)
	{
	N23Click(N23);
	}
}
void __fastcall TSpTree::N4Click(TObject *Sender)
{
if (Tree->Selected&&Tree->Selected->Data)
	{
	TFileDisigner *wnd=new TFileDisigner(this->Owner,DB,LUser,(Obd *)Tree->Selected->Data,MassAction,1);
	wnd->ShowModal();
	delete wnd;
	}
// получить файлы
}
void __fastcall TSpTree::N5Click(TObject *Sender)
{
if (Tree->Selected&&Tree->Selected->Data)
	{
	TFileDisigner *wnd=new TFileDisigner(this->Owner,DB,LUser,(Obd *)Tree->Selected->Data,MassAction,2);
	wnd->ShowModal();
	delete wnd;
	}
if (Tree->Items->Count)
	{
	N23Click(N23);
	}
}

void __fastcall TSpTree::TechAction(TObject *Sender)
{
TTreeNode *node=Tree->Selected;
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
void __fastcall TSpTree::TechDel(TObject *Sender)
{
if (!MessageDlg("Удаление безвозвратно уничтожит всю информацию. Продолжить?",mtWarning,TMsgDlgButtons()<<mbYes<<mbNo,0)==mrYes){return;}
TTreeView *TV=Tree;
String ids="";
Obd *det=0;
for (unsigned int i=0; i < TV->SelectionCount; i++)
    {
    det=(Obd*)TV->Selections[i]->Data;
    if (det&&det->TrueClassName()=="TreeRow")
        {
        TreeRow *Row=(TreeRow *)det;
        Row->UpdateVal();
        if (Row->Get_Accept())
            {
            ids=ids+String(Row->Get_ID())+",";
            }
        }
    }
if (ids!="")
    {
    ids.Delete(ids.Length(),1);
	DB->SendCommand("Call technologic.TechDel('"+ids+"')");
    }
}

void __fastcall TSpTree::SpMaster(TObject *Sender)
{
/*	switch (m->Tag)
{
case 0:{break;} 	//добавить
case 1:{break;}     //редактировать
case 2:{break;}		//просмотр
default:break;
} */
bool start=false;
TMenuItem *m=(TMenuItem *)Sender;
String obd="";
if (Tree->Selected)
	{
	Obd *row=(Obd*)Tree->Selected->Data;
	if (row)
		{
		obd=row->Get_Obd(false);
		start=true;
		}
	}
if (!m->Tag)
	{
	start=true;
	}
if (start)
	{
	TSPEditor *wnd=new TSPEditor(this,DB,LUser,m->Tag,obd);
	wnd->ShowModal();
	delete wnd;
	}
}
void __fastcall TSpTree::SpDel(TObject *Sender)
{
if (!MessageDlg("Удаление безвозвратно уничтожит всю информацию. Продолжить?",mtWarning,TMsgDlgButtons()<<mbYes<<mbNo,0)==mrYes){return;}
TTreeView *TV=Tree;
String ids="",param;
Obd *det=0;
vector <TTreeNode *>nodes;
for (unsigned int i=0; i < TV->SelectionCount; i++)
    {
	det=(Obd*)TV->Selections[i]->Data;
	if (det&&det->TrueClassName()=="TreeRow")
        {
        TreeRow *Row=(TreeRow *)det;
        Row->UpdateVal();
        if (Row->Get_Accept())
            {
			ids=ids+String(Row->Get_ID())+",";
			nodes.push_back(TV->Selections[i]);
			}
        }
    }
switch (((TMenuItem*)Sender)->Tag)
	{
	case 0:{param="sp_only";break;}
	case 1:{param="det";break;}
	case 2:{param="sp_and_all_det";break;}
	default:return;
	}
if (ids!="")
    {
	ids.Delete(ids.Length(),1);
	DB->SendCommand("Call constructions.SpDel('"+ids+"','"+param+"')");
	if (TV->Selected->Parent)
		{
		for (vector<TTreeNode *>::iterator i=nodes.begin(); i!=nodes.end(); i++)
			{
			UpdateInfo(*i);
			}
		}else
		{
		LoadTree(((Obd*)(TV->Selected->Data))->Get_ID());
		}
	}else
	{
	ShowMessage("Нет доступа ни к одному из элементов");
	}
}

void __fastcall TSpTree::N26Click(TObject *Sender)
{
vector <TTreeNode *>nodes;
for (unsigned int i=0; i < Tree->SelectionCount; i++)
    {
	nodes.push_back(Tree->Selections[i]);
	}
//смена состояния
TCond *wnd;
wnd=new TCond(this->Owner,*Tree,MassAction,DB,IcoData,LUser);
wnd->ShowModal();
delete wnd;
Obd *bag=0;
TreeRow *Row=0;
//обновить инфорацию о каждой детали в узле
for (vector<TTreeNode *>::iterator i=nodes.begin(); i!=nodes.end(); i++)
	{
	UpdateInfo(*i);
	bag=(Obd *)(*i)->Data;
	if (bag&&bag->TrueClassName()=="TreeRow")
		{
		Row=(TreeRow *)bag;
		(*i)->StateIndex=IcoData->GetInList(Row->Get_state(),Row->Get_Accept(),0);
		}
	}
//Tree->Repaint();
}

void __fastcall TSpTree::N10Click(TObject *Sender)
{
MassAction=false;
N10->Checked=!MassAction;
N9->Checked=MassAction;
}
void __fastcall TSpTree::N9Click(TObject *Sender)
{
MassAction=true;
N10->Checked=!MassAction;
N9->Checked=MassAction;
}

void  			TSpTree::UpdateInfo(TTreeNode *Node)
{     //если массовые действи явыключены то происходит обновление указанного узла и входящих в него деталей
// при вуключенных масс действиях происходит полное перестроение ветви
Obd *bag=(Obd *)Node->Data;
if (bag&&bag->TrueClassName()=="TreeRow")
	{
	TreeRow *Row=(TreeRow *)bag;
	if (!Row->UpdateVal())//обновлние информации в ноде
		{
		BranchClear(Node);
		delete Row;                                    //если нод неюзабелен то удаляем и на выход
		Node->Delete();
		}else
		{
		if (MassAction)                         //проверка на массовость действий
			{
			bool expand=Node->Expanded;         //если массовое действие то выполнить полное перестроение
			UpdateBranch(Node);
			if (expand)
				{
				Node->Expand(false);
				}
			}else
			{
			if (Row->Get_CanChild()||Row->Get_Force())// обновление информации в ноде разделе "документация"
				{
				Node=Node->getFirstChild();
				if (Node)
					{
					Obd *r=(Obd *)Node->Data;
					if (r&&r->TrueClassName()=="Obd")
						{
						r->UpdateVal();
						r->SetData(r->Get_ID(),1,r->Get_Obd(false),r->Get_Name(),"Документация");
						}
					}
				}
			if (Node&&Node->Count) // обновление информации в файлах
				{
				Node=Node->getFirstChild();
				while (Node)
					{
					bag=(Obd *)Node->Data;
					if (bag)
						{
						if (!bag->UpdateVal())    //если нод неюзабелен то он будет удален
							{
							delete bag;
							if (Node->getPrevSibling())
								{
								Node=Node->getPrevSibling();
								Node->getNextSibling()->Delete();
								Node=Node->getNextSibling();
								}else
								{
								if (Node->getNextSibling())
									{
									Node=Node->getNextSibling();
									Node->getPrevSibling()->Delete();
									}else
									{
									Node->Delete();
									Node=0;
									}
								}
							}else
							{
							Node=Node->getNextSibling();
							}
						}else
						{
						Node=Node->getNextSibling();
						}
					}
				}
			}
		}
	}
}

void __fastcall TSpTree::TreeAdvancedCustomDrawItem(TCustomTreeView *Sender, TTreeNode *Node,
          TCustomDrawState State, TCustomDrawStage Stage, bool &PaintImages,
          bool &DefaultDraw)
{
TTreeView *TV=(TTreeView *)Sender;
DefaultDraw=true;
Obd *bag=(Obd *)Node->Data;
if (bag&&bag->TrueClassName()=="TreeRow")
	{
	TreeRow *Row=(TreeRow *)bag;
	if (Node->Selected&&TV->Focused())   // В зависимости от того, выделен узел или нет
		{
		if (Row->Get_Accept())
			{
			if (LUser==Row->Get_UserID())
				{
				Sender->Canvas->Font->Color=clYellow; // разрешонный узел
				}
			}else
			{
			if (Row->Get_UserID()!=-1)
				{
				Sender->Canvas->Font->Color=clRed;  //заблокированный узел
				}else
				{
				Sender->Canvas->Font->Color=clWhite; // а это остальные
				}
			}                        // Используются разные цветовые схемы
		}else
		{
		if (Row->Get_Accept())
			{
			if (LUser==Row->Get_UserID())
				{
				Sender->Canvas->Font->Color=clGreen; // разрешонный узел
				}
			}else
			{
			if (Row->Get_UserID()!=-1)
				{
				Sender->Canvas->Font->Color=clRed; //заблокированный узел
				}else
				{
				Sender->Canvas->Font->Color=clBlack; // а это остальные
				}
			}
		}
	}
}

void  			TSpTree::Selection(TTreeView *TView,TShiftState Shift,int X, int Y)
{
if (!TView->Items->Count||!TView->GetNodeAt(X,Y)) {return;}
if (Shift.ToInt()!=17&&Shift.ToInt()!=12&&Shift.ToInt()!=20&&Shift.ToInt()!=9)
	{
	TView->ClearSelection();
	}
if (Shift.ToInt()!=12&&Shift.ToInt()!=9)
	{
	TView->Select(TView->GetNodeAt(X,Y),Shift);
	TView->GetNodeAt(X,Y)->Focused=true;
	}
TView->Repaint();
}


void __fastcall TSpTree::TreeClick(TObject *Sender)
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

