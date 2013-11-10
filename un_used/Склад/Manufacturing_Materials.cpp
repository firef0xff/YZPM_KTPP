//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Manufacturing_Materials.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMaterials_Need *Materials_Need;
//инициализация/разрушение
__fastcall TMaterials_Need::TMaterials_Need(TComponent* Owner): TForm(Owner),LUser(25)
{
	ADC->ConnectionString="FILE NAME="+ExtractFileDir(Application->ExeName)+"\\lib\\connect.udl";
	DB=new cSQL(ADC);
	IcoData=nullptr;
    init();
}
__fastcall TMaterials_Need::TMaterials_Need(TComponent* Owner, TWinControl *_p, String _name,
							const int &_LUser,cSQL *db,IconsData *_IcoData)
	: TForm(Owner),LUser(_LUser)
{
	Align=alClient;
	Parent=_p;
	Name=_name;
	BorderStyle=bsNone;
	//иконки из базовой проги
	IcoData=_IcoData;
	//инициализация внутренностей формы
	init();
	//управление вкладкой
	if(Parent->ClassNameIs("TTabSheet"))
	{
		((TTabSheet *)Parent)->Caption="Потребность материала для производства     ";
	}
	Show();//нарисоваться уже...
}
__fastcall TMaterials_Need::~TMaterials_Need(void)
{}
//автосворачивание панели
void __fastcall TMaterials_Need::PanelEnter			(TObject *Sender)
{
	if (Sender){expand_pannel_h((TPanel *)Sender,true);}
}
void __fastcall TMaterials_Need::PanelExit			(TObject *Sender)
{
	if (Sender){expand_pannel_h((TPanel *)Sender,false);}
}
void __fastcall TMaterials_Need::PanelMouseEnter	(TObject *Sender)
{
	if (Sender){((TPanel *)Sender)->SetFocus();}
}

//поиск
void __fastcall TMaterials_Need::CngListClick(TObject *Sender)
{
	TSpeedButton *bt=(TSpeedButton *)Sender;
	switch (bt->Tag)
	{
	case  1:{
				E2->Text=String(E2->Text.ToInt()+1);
				break;
			}
	case -1:{
				if (E2->Text.ToInt()>1)
				{
					E2->Text=String(E2->Text.ToInt()-1);
				}
				break;
			}
	default:return;
	}
}
void __fastcall TMaterials_Need::E2Change(TObject *Sender)
{
	if (E2->Text==""||E2->Text=="0")
	{
		E2->Text="1";
	}
	Find();
}
void __fastcall TMaterials_Need::E3Change(TObject *Sender)
{
	if (E3->Text==""||E3->Text=="0")
	{
		E3->Text="1";
	}
	if (E2->Text!="1") {E2->Text="1";} else {Find();}
}
void __fastcall TMaterials_Need::E1KeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key==13)
	{
		Find();
	}
}
void __fastcall TMaterials_Need::StartSearchClick(TObject *Sender)
{
	Find();
}

//алгоритмы
void 		TMaterials_Need::init			(void)
{
	//заголовки сеток
	//детали/узлы
	Dets->Cells[1][0]="Обозначение";
	Dets->Cells[2][0]="Наименование";
	Dets->Cells[3][0]="Необходимо";
	Dets->Cells[4][0]="На складе";
	Dets->Cells[5][0]="Нехватка";
	Dets->Cells[6][0]="Ед. изм.";
	AutoWidthSG(Dets);
	//стандартные
	Std_izd->Cells[1][0]="Обозначение";
	Std_izd->Cells[2][0]="Наименование";
	Std_izd->Cells[3][0]="Необходимо";
	Std_izd->Cells[4][0]="На складе";
	Std_izd->Cells[5][0]="Нехватка";
	Std_izd->Cells[6][0]="Ед. изм.";
	AutoWidthSG(Std_izd);
	//материалы
	Materials->Cells[1][0]="Обозначение";
	Materials->Cells[2][0]="Наименование";
	Materials->Cells[3][0]="Необходимо";
	Materials->Cells[4][0]="На складе";
	Materials->Cells[5][0]="Нехватка";
	Materials->Cells[6][0]="Ед. изм.";
	AutoWidthSG(Materials);
	//материалы вспомогательные
	Vspom_mat->Cells[1][0]="Обозначение";
	Vspom_mat->Cells[2][0]="Наименование";
	Vspom_mat->Cells[3][0]="Необходимо";
	Vspom_mat->Cells[4][0]="На складе";
	Vspom_mat->Cells[5][0]="Нехватка";
	Vspom_mat->Cells[6][0]="Ед. изм.";
	AutoWidthSG(Vspom_mat);
	//инициализация панелей
	expand_pannel_h(Panel17,false);
	//инициализация окнок
	if (IcoData)
	{
    	Tree->Images=IcoData->GetImgList();
	}
	//определить права доступа
	//отобразить начальные данные
	Find();
}
void 		TMaterials_Need::Set_Tree_Ico	(TTreeNode *node)
{
	if (node&&node->Data&&Tree->Images&&IcoData)
	{
		Obd *data=(Obd *)node->Data;
		node->ImageIndex=IcoData->GetInList(data->Get_SpRazd(),true,1);
		node->SelectedIndex=node->ImageIndex;
		node->ExpandedImageIndex=node->ImageIndex;
		node->StateIndex=-1;
	}
}
void 		TMaterials_Need::Read_Data		(TTreeNode *node)
{
	made_rows.clear();
	standart_rows.clear();
	material_rows.clear();
	support_material_rows.clear();

	if (node&&node->Data)
	{
		Tree_data * data=(Tree_data *)node->Data;
		String val="";
		if (node->Level==1)
		{
			val=" zakaz='"+((Tree_data *)node->Parent->Data)->Get_val()+"' and part='"+data->Get_val()+"' ";
		}else
		{
			val=data->Get_val();
		}
		TADOQuery *rez=DB->SendSQL("call manufacture.Get_Material_Info('"+String(data->Get_eid())+"','"+String(data->Get_Type())+"',\""+val+"\")");
		if (rez&&rez->RecordCount)
		{
			for (rez->First(); !rez->Eof; rez->Next())
			{
				int 				id=rez->FieldByName("id")->Value.operator int();
				Grid_data_types     Type=rez->FieldByName("Type")->Value.operator int();
				double 				Need_kol=rez->FieldByName("Need_kol")->Value.operator double(),
									Sklad_kol=rez->FieldByName("Sklad_kol")->Value.operator double(),
									Lacking_kol=rez->FieldByName("Lacking_kol")->Value.operator double();
				String 				Name=rez->FieldByName("Name")->Value.operator UnicodeString(),
									Obd=rez->FieldByName("Obd")->Value.operator UnicodeString(),
									ei=rez->FieldByName("ei")->Value.operator UnicodeString();
				switch (Type)
				{
				case made:
					{
						made_rows.push_back(Grid_data(Obd,Name,ei,Need_kol,Sklad_kol,Lacking_kol,id,Type));
						break;
					}
				case standart:
					{
						standart_rows.push_back(Grid_data(Obd,Name,ei,Need_kol,Sklad_kol,Lacking_kol,id,Type));
						break;
					}
				case materials:
					{
						material_rows.push_back(Grid_data(Obd,Name,ei,Need_kol,Sklad_kol,Lacking_kol,id,Type));
						break;
					}
				case support_materials:
					{
						support_material_rows.push_back(Grid_data(Obd,Name,ei,Need_kol,Sklad_kol,Lacking_kol,id,Type));
						break;
					}
				default:break;
				}
			}
		}
		delete rez;
	}
	ShowGridTab(materials_lists->ActivePage);
}
void 		TMaterials_Need::Find 			(void)
{
	//поиск
	String _find="";
	if (!SearchParams->ItemIndex)
	{
		_find=GostToVin(E1->Text);
	}else
	{
		_find=E1->Text;
	}
	TADOQuery *rez=DB->SendSQL("Call manufacture.Find('"+_find+"','"+
								String(SearchParams->ItemIndex)+
								"','limit "+String((E2->Text.ToInt()-1)*E3->Text.ToInt())+","+E3->Text+"')");
	Tree->Items->Clear();
	//заполнение верхних уровней древа
	if (rez&&rez->RecordCount)
	{
		TTreeNode *node=nullptr;
		for (rez->First(); !rez->Eof; rez->Next())
		{
			Tree_data *tmp=new Tree_data(DB,zakaz,rez->FieldByName("zakaz")->Value);
			node=Tree->Items->AddObject(node,tmp->Get_Text(),(void*)tmp);
			Set_Tree_Ico(node);
			Tree->Items->AddChildObject(node,"",nullptr);
		}
	}
	delete rez;
}
void 		TMaterials_Need::expand_pannel_h(TPanel *Panel,bool exp)
{
if (exp)
	{
	Panel->Height=Panel->Tag;
	}else
	{
	Panel->Tag=Panel->Height;
	Panel->Height=Panel->Constraints->MinHeight;
	}
}
void 		TMaterials_Need::ShowGridTab     (TTabSheet *tab)
{
	if (tab)
	{
		Grid_rows *row_set;
		TStringGrid *sg=nullptr;
		switch (tab->Tag)
		{
		case made:
			{
				row_set=&made_rows;
				sg=Dets;
				break;
			}
		case standart:
			{
				row_set=&standart_rows;
				sg=Std_izd;
				break;
			}
		case materials:
			{
				row_set=&material_rows;
				sg=Materials;
				break;
			}
		case support_materials:
			{
				row_set=&support_material_rows;
				sg=Vspom_mat;
				break;
			}
		default: return;
		}
		SGClear(sg,0);
		for (Grid_rows::iterator i=row_set->begin(); i!=row_set->end(); i++)
		{
			sg->Cells[1][sg->RowCount-1]=i->Get_Obd();
			sg->Cells[2][sg->RowCount-1]=i->Get_Name();
			sg->Cells[3][sg->RowCount-1]=i->Get_need_kol();
			sg->Cells[4][sg->RowCount-1]=i->Get_sklad_kol();
			sg->Cells[5][sg->RowCount-1]=i->Get_lacking_kol();
			sg->Cells[6][sg->RowCount-1]=i->Get_EI();
			sg->RowCount++;
		}
		if (sg->RowCount>2) {sg->RowCount--;}
		AutoWidthSG(sg);
	}
}
//контекст дерева
void __fastcall TMaterials_Need::N9Click(TObject *Sender)
{
	//узел раскрыть
	TTreeNode *node=Tree->Selected;
	if (node)
	{
		node->Expand(true);
	}
}
void __fastcall TMaterials_Need::N10Click(TObject *Sender)
{
	//узел свернуть
	TTreeNode *node=Tree->Selected;
	if (node)
	{
		node->Collapse(true);
	}
}
void __fastcall TMaterials_Need::N18Click(TObject *Sender)
{
	Find();
}
//события
void __fastcall TMaterials_Need::TreeDeletion(TObject *Sender, TTreeNode *Node)
{
	if (Node->Data)
	{
    	delete (Obd*)Node->Data;
	}
}
void __fastcall TMaterials_Need::TreeExpanding(TObject *Sender, TTreeNode *Node, bool &AllowExpansion)
{
//разворот дерева
	Tree_data * data=(Tree_data *)Node->Data;
	if (data)
	{
		Node->DeleteChildren();//чтобы плюсики пропали если нечего открыть
		String val="";
		if (Node->Level==1)
		{
			val="zakaz='"+((Tree_data *)Node->Parent->Data)->Get_val()+"' and part='"+data->Get_val()+"'";
		}else
		{
			val=data->Get_val();
		}
		TADOQuery *rez=DB->SendSQL("call manufacture.Get_Entrance_lvl('"+String(data->Get_eid())+"','"+String(data->Get_Type())+"',\""+val+"\")");
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
				Tree_data_types     Type=rez->FieldByName("Type")->Value.operator int();
				unsigned __int64 	eid=rez->FieldByName("eid")->Value.operator __int64(),
									eidp=rez->FieldByName("eidp")->Value.operator __int64();
				double 				sp_kol=rez->FieldByName("sp_kol")->Value.operator double(),
									abs_kol=rez->FieldByName("abs_kol")->Value.operator double(),
									all_kol=rez->FieldByName("all_kol")->Value.operator double();
				String 				Name=rez->FieldByName("Name")->Value.operator UnicodeString(),
									V_Obd=rez->FieldByName("Obd")->Value.operator UnicodeString(),
									V_Obu=rez->FieldByName("Obu")->Value.operator UnicodeString(),
									SpRazdName=rez->FieldByName("SpRazdName")->Value.operator UnicodeString(),
									ei=rez->FieldByName("ei")->Value.operator UnicodeString(),
									val=rez->FieldByName("val")->Value.operator UnicodeString();
				TDateTime			date=rez->FieldByName("create_date")->Value.operator TDateTime();
				row=new Tree_data  (DB,id,idp,SpRazd,eid,eidp,sp_kol,abs_kol,all_kol,Name,V_Obd,V_Obu,SpRazdName,ei,val,Type,date);

				if (Node->Level>1)
				{
					if (CurRazd!=row->Get_SpRazdName())
					{
						pnode=Node->Owner->AddChildObject(Node,row->Get_SpRazdName(),nullptr);
						Set_Tree_Ico(pnode);
						CurRazd=row->Get_SpRazdName();
					}
				}else
				{
					pnode=Node;
				}
				node=Node->Owner->AddChildObject(pnode,row->Get_Text(),(void*)row);
				Set_Tree_Ico(node);
                Node->Owner->AddChildObject(node,"",0);//плюсик
			}
		}
		delete rez;
	}
}
void __fastcall TMaterials_Need::TreeMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	Read_Data(Tree->GetNodeAt(X,Y));
}
void __fastcall TMaterials_Need::materials_listsChange(TObject *Sender)
{
//  определить открываемую вкладку обновить на ней содержимое
//	функция обновления отдельно т.к. будет доступ из контекста
	ShowGridTab(materials_lists->ActivePage);
}
void __fastcall TMaterials_Need::ContentGridsDrawCell(TObject *Sender, int ACol, int ARow,
		  TRect &Rect, TGridDrawState State)
{
	Grid_rows *row_set=nullptr;
	TStringGrid *sg=(TStringGrid *)Sender;
	const int 	even_color=0X00E0FFFF,		//зеленоватый
				uneven_color=0x00e0FFe0,  	//желтоватый
				select_color=0x00FFE0E0,	//синий
				bad_color=0x009090FF,     	//красноватый
				warning_color=0X0090FFFF, 	//желтоватый
				good_color=0x0090FF90;    	//зеленоватый
	if (sg->Parent)
	{
		switch (sg->Parent->Tag)
		{
		case made:
			{
				row_set=&made_rows;
				break;
			}
		case standart:
			{
				row_set=&standart_rows;
				break;
			}
		case materials:
			{
				row_set=&material_rows;
				break;
			}
		case support_materials:
			{
				row_set=&support_material_rows;
				break;
			}
		default: return;
		}
		if (row_set->size())
		{//проверка на наличие записей в сетке
			if (ARow)
			{
				if (ACol)
				{
					if (ARow%2)
					{
						sg->Canvas->Brush->Color=even_color;
					}else
					{
						sg->Canvas->Brush->Color=uneven_color;
					}
				}
				if (!ACol||ACol==5)//цвет первой ячейки (сигналка о неполадках с количеством)
				{
					Grid_rows::iterator i=row_set->begin()+(ARow-1);
					if (i->Get_need_kol()>i->Get_sklad_kol())
					{
						if (i->Get_sklad_kol()==0)
						{
							sg->Canvas->Brush->Color=bad_color;
						}else
						{
							sg->Canvas->Brush->Color=warning_color;
						}
					}else
					{
						if (!ACol)
						{
							sg->Canvas->Brush->Color=good_color;
						}
					}
				}
				// выделенные поля
				if(	ACol>=sg->Selection.Left&&
					ACol<=sg->Selection.Right&&
					ARow>=sg->Selection.Top&&
					ARow<=sg->Selection.Bottom) // выделение
				{
					sg->Canvas->Brush->Color=select_color;
				}
			sg->Canvas->Font->Color=clBlack;
			sg->Canvas->FillRect(Rect);
			sg->Canvas->TextOut(Rect.left+2, Rect.top+1,
			sg->Cells[ACol][ARow]);
			}
		}
	}
}
//---------------------------------------------------------------------------

