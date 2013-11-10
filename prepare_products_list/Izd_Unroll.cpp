//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Izd_Unroll.h"
#include "List_add.h"
#include "Excel.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

//инициализация и уничтожение
__fastcall TList_Editor::TList_Editor(TComponent* Owner, TWinControl *_p, String _name,
										const int &_LUser,cSQL *db,IconsData *_IcoData,int **_select,
										void *_OpenTree,void* _AddTexTab,void* _LoadTexToCurrTab,
										void* _AddTexViewTab,void* _LoadexViewToCurrTab)
	: TForm(Owner),LUser(_LUser),DB(db),IcoData(_IcoData)
{
	Align=alClient;
	Parent=_p;
	Name=_name;
	BorderStyle=bsNone;
	init();
	Selected=_select;//массив с минимальной длинной 2 позиции. 1 позиция это номер последней позиции массива
	//функция возврата
	OpenTree=outFunc(_OpenTree);
	//функции указатели
	AddTexTab=outFunc(_AddTexTab);
	AddTexViewTab=outFunc(_AddTexViewTab);
	LoadTexToCurrTab=outFunc(_LoadTexToCurrTab);
	LoadexViewToCurrTab=outFunc(_LoadexViewToCurrTab);
	if(Parent->ClassNameIs("TTabSheet"))
	{
		((TTabSheet *)Parent)->Caption="Обработка данных     ";
	}
	Show();
}
__fastcall TList_Editor::~TList_Editor()
{
	Set_list_Block(N13,Grid->Row,true);
}

void  			TList_Editor::init 		(void)
{
	Grid->Cells[0][0]=L"Список №";
	Grid->Cells[1][0]=L"Тип";
	Grid->Cells[2][0]=L"Редактировал";
	Grid->Cells[3][0]=L"Дата модификации";
	Grid->Cells[4][0]=L"Создал";
	Grid->Cells[5][0]=L"Дата создания";
	order_by="order by list_no asc";
	sortparams="";
	states="";
	types="";
	Active_list=nullptr;
	Tree->Images=IcoData->GetImgList();
	Errs->Images=IcoData->GetImgList();
	//инициализация ограничений доступа
	//ограничение по типам
	TADOQuery *rez=DB->SendSQL("call processed_list.Get_aval_types("+String(LUser)+")");
	if(rez&&rez->RecordCount)
		{
		for(rez->First(); !rez->Eof; rez->Next())
			{
			types=types+rez->FieldByName("Type_ID")->Value+",";
			}
		}
	delete rez;
	if (types!="")
	{
    	types=types.Delete(types.Length(),1);
	}
    //ограничение по состояниям
	rez=DB->SendSQL("call processed_list.Get_aval_States("+String(LUser)+")");
	if(rez&&rez->RecordCount)
		{
		for(rez->First(); !rez->Eof; rez->Next())
			{
			states=states+rez->FieldByName("State_ID")->Value+",";
			}
		}
	delete rez;
	if (states!="")
	{
    	states=types.Delete(states.Length(),1);
	}
	inWork=false;
	N13->Caption="Редактировать";

	// получение минимально доступного состояния
	rez=DB->SendSQL("Call administration.Get_MinState('"+String(LUser)+"')");
	if (rez&&rez->RecordCount)
	{
		StateID=rez->FieldByName("IdCond")->Value;
		StateName=rez->FieldByName("CondName")->Value;
	}else
	{
		StateID=0;
		StateName="";
	}
	delete rez;

	GetLists();
}
//интерфейсные манипуляторы
void __fastcall TList_Editor::Find_paramsClick(TObject *Sender)
{
	TList_sel_params *wnd=new TList_sel_params(this,LUser,DB);
	if (wnd->ShowModal()==mrOk)
	{
        sortparams=wnd->Get_Where();
	}
	delete wnd;
	GetLists();
}
void __fastcall TList_Editor::E3Change(TObject *Sender)
{
if (E3->Text==""||E3->Text=="0")
	{
	E3->Text="1";
	}
if (E2->Text!="1") {E2->Text="1";} else {GetLists();}
}
void __fastcall TList_Editor::E2Change(TObject *Sender)
{
if (E2->Text==""||E2->Text=="0")
	{
	E2->Text="1";
	}
GetLists();
}
void __fastcall TList_Editor::ChgListClick(TObject *Sender)
{
	TSpeedButton *bt=(TSpeedButton *)Sender;
	switch (bt->Tag)
	{
		case  1:{E2->Text=String(E2->Text.ToInt()+1);break;}
		case -1:{if (E2->Text.ToInt()>1) {E2->Text=String(E2->Text.ToInt()-1);}break;}
		default:return;
	}
}
void __fastcall TList_Editor::GridFixedCellClick(TObject *Sender, int ACol, int ARow)

{
	UpdateSort(ACol);
}

//алгоритмы работы

void  			TList_Editor::GetLists 			(void)
{
	String sql="";
	sql+="SELECT a.List_No,b.Type_id,b.Type_Name, ";
	sql+="a.CreateDate,a.CreateUser,a.UpdateDate,a.UpdateUser, ";
	sql+="if (a.User='' or a.User=c.LogIN,0,1) as blocked ";
	sql+="FROM processed_list.lists a ";
	sql+="join processed_list.types b on a.Type=b.Type_id ";
	sql+="left join administration.logins c on c.LogID='"+String(LUser)+"' ";
	sql+=" Where State_ID in ('"+states+"') and Type in ('"+types+"') "+sortparams+" ";
	sql=sql+order_by+" limit "+String(E2->Text.ToInt()*E3->Text.ToInt()-E3->Text.ToInt())+","+E3->Text;
	TADOQuery *rez=DB->SendSQL(sql);
	list.clear();
	if (rez&&rez->RecordCount)
	{
		list.resize(rez->RecordCount);
		for (rez->First(); !rez->Eof; rez->Next())
		{
			list[rez->RecNo-1]=List_data(
										 rez->FieldByName("List_No")->Value.operator __int64(),
										 rez->FieldByName("Type_id")->Value.operator int(),
										 rez->FieldByName("CreateUser")->Value,
										 rez->FieldByName("UpdateUser")->Value,
										 rez->FieldByName("Type_Name")->Value,
										 rez->FieldByName("CreateDate")->Value.operator TDateTime(),
										 rez->FieldByName("UpdateDate")->Value.operator TDateTime(),
										 rez->FieldByName("blocked")->Value.operator bool()
										);
		}
	}

	ShowList();
}
void			TList_Editor::ShowList			(void)
{
	SGClear(Grid,0);
	for (V_List::iterator i=list.begin(); i!=list.end(); i++)
	{
		int row=Grid->RowCount-1;
		Grid->Cells[0][row]=i->Get_List_No();
		Grid->Cells[1][row]=i->Get_Type_Name();
		Grid->Cells[2][row]=i->Get_UpdateUser();
		Grid->Cells[3][row]=i->Get_UpdateDate().FormatString("hh:mm:ss dd.mm.yyyy");
		Grid->Cells[4][row]=i->Get_CreateUser();
		Grid->Cells[5][row]=i->Get_CreateDate().FormatString("hh:mm:ss dd.mm.yyyy");
		Grid->RowCount++;
	}
	if (Grid->RowCount>2)
	{
    	Grid->RowCount--;
	}
	AutoWidthSG(Grid);
	ShowData(Grid->Row);
}
void			TList_Editor::ShowData			(size_t row)
{
	Tree->Items->Clear();
	Errs->Items->Clear();
	if (!list.empty())
	{
		//список деталей
		String sql="call processed_list.Get_list_data ('"+String(list[row-1].Get_List_No())+"')";
		TADOQuery *rez=DB->SendSQL(sql);
		TTreeNode *node=nullptr;
		if (rez&&rez->RecordCount)
		{
			for (rez->First(); !rez->Eof; rez->Next())
			{
				unsigned __int64 t=rez->FieldByName("eid")->Value.operator __int64();
				Tree_data *data=new Tree_data(DB,t);
				node=Tree->Items->AddObject(node,data->Get_Text(),(void *)data);
				Set_img(node);//нарисовать иконки
				//добавить плюсик
				Tree->Items->AddChild(node,"");
			}
		}
		delete rez;
		//список ошибок
		sql="call processed_list.Get_err_data ('"+String(list[row-1].Get_List_No())+"')";
		rez=DB->SendSQL(sql);
		node=nullptr;
		if (rez&&rez->RecordCount)
		{
			for (rez->First(); !rez->Eof; rez->Next())
			{
				unsigned int t=rez->FieldByName("id")->Value.operator int();
				Obd *data=new Obd(DB,t);
				node=Errs->Items->AddObject(node,data->Get_Text(),(void *)data);
				Set_img(node);//нарисовать иконки
			}
		}
		delete rez;
	}
}
void			TList_Editor::UpdateSort		(int ACol)
{
//сортировка
	String field="";
	switch(ACol)
	{
	case 0:
		{
			field="list_no";
			break;
		}
	case 1:
		{
			field="type";
			break;
		}
	case 2:
		{
			field="UpdateDate";
			break;
		}
	default:
		return;
	}
	// определение порядка сортировки
	String order="desc", kor="";
	int pos=order_by.Pos(field);
	if(pos==10)
	{
		kor=" ";
		String o_order=order_by.SubString(pos+field.Length()+1, 4);
		if(o_order=="desc")
		{
			order="asc ";
		}
		else
		{
			order="desc";
		}
	}
	// удаление старого вхождения строки
	order_by.Delete(pos, field.Length()+order.Length()+2);
	// вставка нового вхождения
	order_by.Insert(kor+field+" "+order+",", 10);
	order_by=order_by.Trim();
	if(order_by[order_by.Length()]==',')
	{
		order_by.Delete(order_by.Length(), 1);
	}
	GetLists();
}
void    		TList_Editor::Set_list_Block 	(TMenuItem *it,int row,bool free)
{
	//проверка состояния блокировки
	if (list.size()&&row-1<list.size()&&!list[row-1].Get_blocked())
	{//если не заблокировано то можно работать блокировкой для текущего
		//этап1 определение назначаемого состояния
		bool setBlock=false;//устанавливаемое значение блокировки листа
		if (!free)//проверим триггер освобождения
		{
			setBlock=!inWork;//для переключателя кнопки и режима работы
		}else
		{
            setBlock=false;//сброс блокировки
		}
        //попытка назначить состояние, проверка состояния блокировки
		bool blocked=false;//состояние блокировки листа для текущего пользователя
		TADOQuery *rez=DB->SendSQL("call processed_list.Set_list_block('"+String(list[row-1].Get_List_No())+"','"+String((int)setBlock)+"','"+String(LUser)+"')");
		//читаем ответ
		if (rez&&rez->RecordCount)
		{
			blocked=rez->FieldByName("result")->Value.operator bool();
		}else
		{//ошибка связи с серваком вероятно потому блочим
			blocked=true;
		}
		list[row-1].Set_blocked(blocked);

		//что касается inWork
		//повторяем проверку на состояние блокировки если не заблокированно то меняем состояние
		if (!blocked)
		{
			inWork=setBlock;
			if (inWork)
			{
				it->Caption="Отменить редактирование";
				Tree->Color=0x00e0FFe0;
			}else
			{
				it->Caption="Редактировать";
				Tree->Color=clWindow;
			}
		}
	}
}
bool			TList_Editor::inTree			(int id,bool root)
{
	bool result=false;
	TTreeNode *node=Tree->Items->GetFirstNode();
	while (node&&!result)
	{
		if (node->Data)
		{
			if (((Obd *)node->Data)->Get_ID()==id)
			{
				result=true;
			}
		}
		if (root)
		{
			node=node->getNextSibling();
		}else
		{
			node=node->GetNext();
		}
	}
	return result;
}
void			TList_Editor::Upd_Branch		(TTreeNode *node)
{
	//обновляется количество (абс и олл) и статус ветки
	if (node->Data&&((Obd *)node->Data)->TrueClassName()=="Tree_data")
	{
		((Tree_data *)node->Data)->Update();
		Set_img(node);
	}
	if (node->Count)
	{
		if (node->Expanded)
		{
			node->Collapse(true);
			node->Expand(false);
		}
	}
}
void			TList_Editor::Set_img			(TTreeNode *node)
{
	if (node&&node->Data)
	{
		Obd *data=(Obd *)node->Data;
		node->ImageIndex=IcoData->GetInList(data->Get_SpRazd(),true,1);
		node->SelectedIndex=node->ImageIndex;
		node->ExpandedImageIndex=node->ImageIndex;
		if (((Obd*)node->Data)->TrueClassName()=="Tree_data")
		{
			if (((Tree_data*)data)->Get_active()) //интересный фак бул переменная может хранить числовые значения и принимать не только -1 и 0
			{
				node->StateIndex=1;
			}else
			{
				node->StateIndex=2;
			}
		}
	}
}
void 			TList_Editor::Show_Kol			(TTreeNode *node)
{
	Kol->Caption="Количество";
	if (node)
	{
		ABS_Kol->Text="";
		SP_Kol->Text="";
		ALL_Kol->Text="";
		Obd *data=(Obd*)node->Data;
		if (data&&data->TrueClassName()=="Tree_data")
		{
			Tree_data *row=(Tree_data *)data;
			ABS_Kol->Text=row->Get_abs_kol();
			SP_Kol->Text=row->Get_sp_kol();
			ALL_Kol->Text=row->Get_all_kol();
			Kol->Caption=Kol->Caption+"("+row->Get_EI()+")";
		}
	}
}
size_t 			TList_Editor::CheckErrors		(unsigned __int64 list_no)
{
	TADOQuery *rez=DB->SendSQL("call processed_list.Check_errs('"+String(list_no)+"')");
	size_t error=1;
	if (rez&&rez->RecordCount)
	{
		error=rez->FieldByName("result")->Value.operator unsigned int();
	}
	delete rez;
	return error;
}

//события
void __fastcall TList_Editor::TreeDeletion(TObject *Sender, TTreeNode *Node)
{//реакция на удаление нода
	delete (Obd*)Node->Data;
}
void __fastcall TList_Editor::GridDrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect,
          TGridDrawState State)
{//рисовка сетки
	TStringGrid *sg=(TStringGrid *)Sender;
//отрисовка индикации листа
	// - раскраска сетки
	static int color=0X00E0FFFF;
	int bad_color=0x00DDDDFF;
	if(ARow==1)
	{
		color=0X00E0FFFF;
	}
	if(ARow) // разлинейка
	{
		if((ARow%2))
		{
			color=0X00E0FFFF;
		}
		else
		{
			color=0x00e0FFe0;
		}
		if(list.size()>=ARow&&!list[ARow-1].Get_blocked())
		{
			sg->Canvas->Brush->Color=color;
		}
		else
		{
			sg->Canvas->Brush->Color=bad_color;
		}
		sg->Font->Color=clBlack;
		sg->Canvas->FillRect(Rect);
		sg->Canvas->TextOutW(Rect.left+2, Rect.top+1,sg->Cells[ACol][ARow]);
	}

	// выделенные поля
	if(ACol>=sg->Selection.Left&&ACol<=sg->Selection.Right&&ARow>=sg->Selection.Top&&ARow<=sg->Selection.Bottom) // выделение
	{
		sg->Canvas->Brush->Color=0x00FFE0E0; // clMenu;
		sg->Canvas->FillRect(Rect);
		sg->Font->Color=clBlack;
		sg->Canvas->TextOutW(Rect.left+2, Rect.top+1,sg->Cells[ACol][ARow]);
	}
}
void __fastcall TList_Editor::TreeExpanding(TObject *Sender, TTreeNode *Node, bool &AllowExpansion)
{
//разворот дерева

	Tree_data * data=(Tree_data *)Node->Data;
	if (data)
	{
		Node->DeleteChildren();//чтобы плюсики пропали если нечего открыть
		TADOQuery *rez=DB->SendSQL("call processed_list.Get_Entrance_lvl('"+String(data->Get_eid())+"')");
		if (rez&&rez->RecordCount)
		{
			TTreeNode *node=nullptr,*pnode=nullptr;
			Tree_data *row=nullptr;
			String CurRazd="";//текущий раздел спецификации
			for (rez->First(); !rez->Eof; rez->Next())
			{
				int 				id=rez->FieldByName("id")->Value.operator int(),
									idp=rez->FieldByName("idp")->Value.operator int(),
									SpRazd=rez->FieldByName("SpRazd")->Value.operator int();
				unsigned __int64 	eid=rez->FieldByName("eid")->Value.operator __int64(),
									eidp=rez->FieldByName("eidp")->Value.operator __int64();
				double 				sp_kol=rez->FieldByName("sp_kol")->Value.operator double(),
									abs_kol=rez->FieldByName("abs_kol")->Value.operator double(),
									all_kol=rez->FieldByName("all_kol")->Value.operator double();
				bool 				active=rez->FieldByName("active")->Value.operator bool();
				String 				Name=rez->FieldByName("Name")->Value.operator UnicodeString(),
									V_Obd=rez->FieldByName("Obd")->Value.operator UnicodeString(),
									V_Obu=rez->FieldByName("Obu")->Value.operator UnicodeString(),
									SpRazdName=rez->FieldByName("SpRazdName")->Value.operator UnicodeString(),
									ei=rez->FieldByName("ei")->Value.operator UnicodeString();

				row=new Tree_data  (DB,id,idp,SpRazd,eid,eidp,sp_kol,abs_kol,all_kol,active,Name,V_Obd,V_Obu,SpRazdName,ei);

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
				Set_img(node);
                Node->Owner->AddChildObject(node,"",0);//плюсик
			}
		}
	}
}
void __fastcall TList_Editor::GridSelectCell(TObject *Sender, int ACol, int ARow,
		  bool &CanSelect)
{
	TStringGrid *sg=(TStringGrid *)Sender;
//евент клика на сетку
//чтение данных
	if (ARow!=sg->Row)
	{
		Set_list_Block(N13,sg->Row,true);
		ShowData(ARow);
	}
}
void __fastcall TList_Editor::PAB1Popup(TObject *Sender)
{
	N1->Enabled=inWork;
	N2->Enabled=inWork;
	N3->Enabled=inWork;
	N4->Enabled=inWork;
	N5->Enabled=inWork;
	N6->Enabled=inWork;
	N7->Enabled=inWork;
}
void __fastcall TList_Editor::TreeMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	Change_kol->Enabled=inWork;
	Reset_kol->Enabled=inWork;
	ABS_Kol->ReadOnly=!inWork;
	Show_Kol(Tree->GetNodeAt(X,Y));
}
void __fastcall TList_Editor::ABS_KolChange(TObject *Sender)
{
	TLabeledEdit *t=(TLabeledEdit *)Sender;
	try
	{
		String Decimal_Separator=DecimalSeparator;
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
void __fastcall TList_Editor::ErrsMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	TTreeNode *node=Errs->GetNodeAt(X,Y);
	if (node!=nullptr)
	{
		Errs_list->Lines->Clear();
		if(node->Data||((Obd*)node->Data)->ItTrueClassName()&&list.size()&&Grid->Row-1<list.size())
		{
			TADOQuery *rez=DB->SendSQL("Call processed_list.Get_err_list('"+String(list[Grid->Row-1].Get_List_No())+"','"+String(((Obd*)node->Data)->Get_ID())+"')");
			if (rez&&rez->RecordCount)
			{
				for (rez->First(); !rez->Eof; rez->Next())
				{
					Errs_list->Lines->Add(rez->FieldByName("Err_Name")->Value);
				}
				delete rez;
			}
		}
	}
}
//меню списка листов
void __fastcall TList_Editor::WorkClick(TObject *Sender)
{
	TMenuItem *it=(TMenuItem *)Sender;
	int row=Grid->Row;
	Set_list_Block(it,row);
}
void __fastcall TList_Editor::AddClick(TObject *Sender)
{
//добавить лист
	TListAdd *wnd=new TListAdd(this,LUser,DB);
	wnd->ShowModal();
    GetLists();
}
void __fastcall TList_Editor::DelClick(TObject *Sender)
{
//удалить лист
	if (list.size()&&Grid->Row-1<list.size()&&!list[Grid->Row-1].Get_blocked())
	{
		Set_list_Block(N13,Grid->Row,true);
		DB->SendCommand("call processed_list.Del_list('"+String(list[Grid->Row-1].Get_List_No())+"')");
		GetLists();
	}
}
void __fastcall TList_Editor::Upd_list_Click(TObject *Sender)
{
	GetLists();
}
void __fastcall TList_Editor::Next_Step_Click(TObject *Sender)
{
	if (list.size()&&Grid->Row-1<list.size()&&!list[Grid->Row-1].Get_blocked())
	{
		size_t errors=CheckErrors(list[Grid->Row-1].Get_List_No());
		bool _continue=true;
		if (errors)
		{
			if (MessageDlg(L"Обнаружено "+String(errors)+" ошибок.\n Продолжить", mtWarning, TMsgDlgButtons()<<mbYes<<mbNo, 0)==mrYes)
			{
				_continue=true;
			}else
			{
            	_continue=false;
			}
			ShowData(Grid->Row);
		}
		if (_continue)
		{
			Set_list_Block(N13,Grid->Row,true);
			DB->SendCommand("Call processed_list.TurnToNextStep('"+String(list[Grid->Row-1].Get_List_No())+"','"+String(LUser)+"')");
			MessageDlg(L"Операция успешно проведена", mtInformation, TMsgDlgButtons()<<mbOK, 0);
			GetLists();
		}
	}
}

//меню работы с деревом
void __fastcall TList_Editor::TreeItems_Add_Click(TObject *Sender)
{
//добавить
	if (list.size()&&Grid->Row-1<list.size()) //защита
	{
		TTreeNode *node=nullptr;
		for (size_t i =1; i <=**Selected; i++)
		{
			if (!inTree(*(*Selected+i),true))
			{   //провести операцию добавления к базе
				DB->SendCommand("Call processed_list.Add_Entrance ('"+String(*(*Selected+i))+"','"+"1"+"','"+String(list[Grid->Row-1].Get_List_No())+"','"+String(LUser)+"' )");
			}
		}
		//обновить дерево
		ShowData(Grid->Row);
	}
}
void __fastcall TList_Editor::TreeItems_del_Click(TObject *Sender)
{
	//удалить
	if (list.size()&&Grid->Row-1<list.size()) //защита
	{
		for (size_t i=0; i<Tree->SelectionCount; i++)
		{//поддержим массовое удаление
			Tree_data * data=(Tree_data *)Tree->Selections[i]->Data;
			if (data)
			{
				DB->SendCommand("Call processed_list.Del_Entrance('"+String(data->Get_eid())+"','"+String(list[Grid->Row-1].Get_List_No())+"','"+String(LUser)+"' )");
			}
		}
		//обновить дерево
		ShowData(Grid->Row);
	}
}
void __fastcall TList_Editor::TreeItems_Activation(TObject *Sender)
{
//использовать
	if (list.size()&&Grid->Row-1<list.size())
	{
		TTreeView *TV=Tree;
		TMenuItem *it=(TMenuItem *)Sender;
		bool active=false,mass=false;
		switch (it->Tag)
		{
			case 1:{mass=false;	active=true;	break;}
			case 2:{mass=true;	active=true;	break;}
			case 3:{mass=false;	active=false;	break;}
			case 4:{mass=true;	active=false;	break;}
			default:return;
		}
		Obd *det=0;
		for (unsigned int i=0; i < TV->SelectionCount; i++)
		{
			det=(Obd*)TV->Selections[i]->Data;
			if (det&&det->TrueClassName()=="Tree_data")
			{
				((Tree_data *)det)->Set_active(active,mass,list[Grid->Row-1].Get_List_No(),LUser);
				if (mass)
				{
					Upd_Branch(TV->Selections[i]);
				}else
				{
					Set_img(TV->Selections[i]);
				}
			}
		}
	}
}

void __fastcall TList_Editor::Change_kol_Click(TObject *Sender)
{
	TTreeNode *node=Tree->Selected;
	TComponent *com=(TComponent *)Sender;
	if (node&&node->Data&&((Obd*)node->Data)->TrueClassName()=="Tree_data"&&list.size()&&Grid->Row-1<list.size()&&ABS_Kol->Tag)
	{
		if (ABS_Kol->Text.Length())
		{
			Tree_data * row=(Tree_data *)node->Data;
			String nKol=Replace(ABS_Kol->Text, DecimalSeparator,".");
			if (nKol.ToDouble()>0||com->Tag)
			{
				DB->SendCommand("call processed_list.reCalk_kol('"+String(row->Get_eid())+"','"+nKol+"','"+String(com->Tag)+"','"+String(list[Grid->Row-1].Get_List_No())+"','"+String(LUser)+"')");
			}
		}
		Upd_Branch(node);
		Show_Kol(node);
	}
}
void __fastcall TList_Editor::Update_Tree(TObject *Sender)
{
	ShowData(Grid->Row);
}

void __fastcall TList_Editor::N9Click(TObject *Sender)
{
	//узел раскрыть
	TTreeNode *node=Tree->Selected;
	if (node)
	{
		node->Expand(true);
	}
}
void __fastcall TList_Editor::N10Click(TObject *Sender)
{
	//узел раскрыть
	TTreeNode *node=Tree->Selected;
	if (node)
	{
		node->Collapse(true);
	}

}

//меню работы с ошибками
void __fastcall TList_Editor::ExcelClick(TObject *Sender)
{
	if (list.size()&&Grid->Row-1<list.size())
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
		TADOQuery *rez=DB->SendSQL("Call processed_list.Get_Excel_err_list('"+String(list[Grid->Row-1].Get_List_No())+"')");
		String old_val="",val="";
		if (rez&&rez->RecordCount)
			{
			for (rez->First(); !rez->Eof; rez->Next())
				{
				int i=rez->RecNo+1;
				val=VinToGost(rez->FieldByName("obd")->Value);
				if (val!=old_val)
				{
					rep->toCells(i,1,val);
					old_val=val;
				}
				rep->toCells(i,2,rez->FieldByName("err")->Value.operator UnicodeString());
				}
			}
		delete rez;
		rep->DisplayAlerts(true);
		rep->Visible(true);
		delete rep;
	}
}
void __fastcall TList_Editor::N16Click(TObject *Sender)
{
//проверить ошибки
	if (list.size()&&Grid->Row-1<list.size())
	{
		CheckErrors(list[Grid->Row-1].Get_List_No());
		ShowData(Grid->Row);
	}
}
void __fastcall TList_Editor::OutFunctions(TObject *Sender)
{
	TMenuItem *m=(TMenuItem *)Sender;
	size_t count=Errs->SelectionCount;
	bool single=count>1?false:true;
	if (count&&StateID)
	{
		TTreeNode *node=nullptr;
		for (size_t i = 0; i < count; i++)
		{
			node=Errs->Selections[i];
			if (node->Data)
			{
				Obd *bag=(Obd*)node->Data;
				DB->SendCommand("Call constructions.ChangeState('"+String(bag->Get_ID())+"','"+String(StateID)+"')"); //сбросить в доступное состояние
				switch (m->Tag) //открыть в требуемой вкладке
				{
				case 0:{LoadTexToCurrTab	(new Obd(*bag));break;}	//редактировать текущая вкладка
				case 1:{AddTexTab			(new Obd(*bag));break;} //редактировать новая вкладка
				case 2:{LoadexViewToCurrTab	(new Obd(*bag));break;}	//просмотр текущая вкладка
				case 3:{AddTexViewTab		(new Obd(*bag));break;}	//просмотр новая вкладка
				case 4:{OpenTree			(new Obd(*bag));break;} //открыть в дереве спецификации
				default:break;
				}
			}
		}
	}
}
//---------------------------------------------------------------------------

