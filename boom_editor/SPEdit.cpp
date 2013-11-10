#include <vcl.h>
#pragma hdrstop
#include "SPEdit.h"

#pragma package(smart_init)
#pragma resource "*.dfm"

//---------конструкторы
	 __fastcall TSPEditor::TSPEditor	(TComponent* Owner,cSQL *const db,const int &_LUser,int mode, String obd)
	: TForm(Owner),DB(db),LUser(_LUser)
{
//сетка
SG1->Cells[1][0]="Формат";
SG1->Cells[2][0]="Зона";
SG1->Cells[3][0]="Поз.";
SG1->Cells[4][0]="Обозначение";
SG1->Cells[5][0]="Наименование";
SG1->Cells[6][0]="Кол.";
SG1->Cells[7][0]="Код";
SG1->Cells[8][0]="Примечание";
SG1->Cells[9][0]="Ед. Изм.";
AutoWidthSG(SG1);
// разделы спецификации
SPRazd=DB->SendSQL("Call administration.Get_SpRazd()");
//классы
Object=0;
XL=new cExcel();
SPList=0;
File=0;
Base=0;
// получение минимально доступного состояния
TADOQuery *rez=DB->SendSQL("Call administration.Get_MinState('"+String(LUser)+"')");
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
//получение имяни пользователя
rez=DB->SendSQL("select LogIn from administration.logins where logid='"+String(LUser)+"'");
if (rez&&rez->RecordCount)
	{
	UserName=rez->FieldByName("LogIn")->Value;
	}
// заполнение списка разделов сп
if (SPRazd&&SPRazd->RecordCount)
	{
	for (SPRazd->First(); !SPRazd->Eof; SPRazd->Next())
		{
		CB2->Items->AddObject(SPRazd->FieldByName("RazdName")->Value,(TObject*)SPRazd->FieldByName("RazdID")->Value.operator int());
		}
	}
//инициализация
switch (mode)
	{
	case 0:{NewClick(0);ReadOnly=false;break;} //добавить
	case 1:{
			LoadSP(obd,true);
			New->Enabled=false;
			N1->Enabled=false;
			ReadOnly=false;
			break;
			}  //редактировать
	case 2:{
			LoadSP(obd,true);
			ReadOnly=true;
			//удалить все кнопки кроме экспорта
			New->Enabled=false;
			OpenEX->Enabled=false;
			FomBase->Enabled=false;
			SeveToBase->Enabled=false;
			ToolButton1->Enabled=false;
			ChangeRZD->Enabled=false;
			Remove->Enabled=false;
			Recover->Enabled=false;
			N1->Enabled=false;
			N2->Enabled=false;
			N3->Enabled=false;
			N8->Enabled=false;
			N4->Enabled=false;
			N9->Enabled=false;
			N5->Enabled=false;
			N6->Enabled=false;
			N7->Enabled=false;
			N10->Enabled=false;
			N11->Enabled=false;
			N12->Enabled=false;
			N13->Enabled=false;
			ei_opt->Enabled=false;
			CB2->Enabled=false;
			autosort->Enabled=false;
			break;}  //просмотр
	default:NewClick(0);
	}
//убрана кнопка загрузки из базы
}
	 __fastcall TSPEditor::~TSPEditor	(void)
{
delete XL;
ClearMass();
}
//--------------------------элементы управления
void __fastcall TSPEditor::NewClick		(TObject *Sender)
{
SPInit();
if (!SPList) {SPList=new vector <SpRow*>();};
if (!Object) {Object=new Obd(DB);}
Action_det="ins";
ShowSP();
}
void __fastcall TSPEditor::OpenEXClick	(TObject *Sender)
{
OD1->FileName="";
if (OD1->Execute()&&OD1->FileName!="")
	{
	SPInit();
	LoadSP(OD1->FileName,false);
	}
}
void __fastcall TSPEditor::FomBaseClick(TObject *Sender)
{
String obd=LE1->Text.Trim();
SPInit();
LoadSP(obd,true);
}//---функции
void __fastcall TSPEditor::ExportClick		(TObject *Sender)
{
 // запуск сохранялки
 GetXL();
}
void __fastcall TSPEditor::SeveToBaseClick(TObject *Sender)
{
if (SaveToBase())
	{ShowMessage("Спецификация сохранена в базе");FomBaseClick(0);}
	else
	{ShowMessage("Неполадки при сохранении спецификации");ShowSP();}

}
void __fastcall TSPEditor::RemoveClick		(TObject *Sender)
{
RemoveRow(SG1->Selection.Top,SG1->Selection.Bottom);
}
void __fastcall TSPEditor::RecoverClick(TObject *Sender)
{
RecoveryRow(SG1->Selection.Top,SG1->Selection.Bottom);
}
void __fastcall TSPEditor::ChangeRZDClick	(TObject *Sender)
{
Trzd *wnd=new Trzd(this,SPRazd);
wnd->ShowModal();
if (wnd->ModalResult==mrOk&&wnd->Get_RazdName()!="")
	{
	int TRow=SG1->Selection.Top,BRow=SG1->Selection.Bottom;
	//1 определить диапазон строк
	for (TRow=TRow; (SG1->Cells[11][TRow].ToIntDef(0)==1||SG1->Cells[10][TRow]=="")&&TRow<=BRow; TRow++);
	for (BRow=BRow; (SG1->Cells[11][BRow].ToIntDef(0)==1||SG1->Cells[10][BRow]=="")&&BRow>=TRow; BRow--);
	//1.5 определить итераторы начала и конца удаления
	vector <SpRow*>::iterator Sact=0,Eact=0;
	if (SG1->Cells[10][TRow]!="") {Sact=SPList->begin()+SG1->Cells[10][TRow].ToIntDef(0);}
	if (SG1->Cells[10][BRow]!="") {Eact=SPList->begin()+SG1->Cells[10][BRow].ToIntDef(0);}
	//2 задать раздел спецификации
	for (vector <SpRow*>::iterator i=Sact; i<=Eact; i++)
		{
		(*i)->Set_SpRazd(wnd->Get_RazdID(),wnd->Get_RazdName());
		}
	if (autosort->Checked)
		{
		SPList=SortMass(SPList);
		}
	ShowSP();
	}
}
// обработчики   сетки
void __fastcall TSPEditor::SG1DrawCell	(TObject *Sender, int ACol, int ARow, TRect &Rect,
		  TGridDrawState State)
{
/*сделать подсветку строк с разными текущм и начальным обозначением
рассмотреть вариант с отрисовкой цветов определенных строкой(проверку в этом случае делать в строке)       */
if (ACol&&ARow)
	{
	TStringGrid *sg=(TStringGrid *)Sender;
	// перенос текста
	//получить количество символов на каждой строке
	vector < pair<int,int> > rows; //вектор с данными по количество сиволов в каждой строке
	rows.clear();
	int count=1;//количество строк для текста
	for (int i=sg->FixedCols; i < sg->ColCount; i++)//максимальное количество строк
		{
		double wigth=sg->ColWidths[i];//ширина ячайки
		double length=sg->Canvas->TextWidth(sg->Cells[i][ARow]);         //длина строки в пикселях
		if ((length/wigth)>count)//получение максимального количества строк
			{
			count=ceil(length/wigth);
			if (count>sg->Cells[i][ARow].Length())
				{
				count=sg->Cells[i][ARow].Length();
				}
			}
		}
	//расчет переноса текста по строкам
	int _pos=1,_count=1;
	int wigth=sg->ColWidths[ACol];
	while (_pos<=sg->Cells[ACol][ARow].Length())
		{
		if (sg->Canvas->TextWidth(sg->Cells[ACol][ARow].SubString(_pos,_count))<wigth&&_pos+_count-1<=sg->Cells[ACol][ARow].Length())
			{//два условия 1 длинна выводимой строки должна быть в рамках и количество сиволов не должно превышать строку
			_count++;
			}else
			{
			pair<int,int> row;
			row.first=_pos;
			if (_count-1)
				{
				row.second=_count-1;
				_pos+=_count-1;
				}else
				{
				row.second=_count;
				_pos+=_count;
				}
			rows.push_back(row);
			_count=1;
			}
		}
	//установка высоты ячейки
	int _height=sg->DefaultRowHeight*count;
	if (sg->RowHeights[ARow]!=_height)
		{
		sg->RowHeights[ARow]=_height;
		return;//т.к. будет изменена высота ячейки и отрисовка запустится снова
		}

	// закраска ячеек
	if ((ACol>=SG1->Selection.Left&&ACol<=SG1->Selection.Right)&&(ARow>=SG1->Selection.Top&&ARow<=SG1->Selection.Bottom))
		{
		SG1->Canvas->Brush->Color=0x00FFE0E0;
		SG1->Canvas->FillRect(Rect);
		SG1->Canvas->Font->Color=clBlue;
		}
		else
		{
		if (SG1->Cells[11][ARow]!="1"&&SG1->Cells[10][ARow]!="")
			{
			//upd желтая
			if (SPList->operator [](SG1->Cells[10][ARow].ToIntDef(0))->Get_act_r()=="upd"||SPList->operator [](SG1->Cells[10][ARow].ToIntDef(0))->Get_act_d()=="upd")
				{
				SG1->Canvas->Brush->Color=0x00ccffff;
				}
			//если ins то зеленая
			if (SPList->operator [](SG1->Cells[10][ARow].ToIntDef(0))->Get_act_r()=="ins"||SPList->operator [](SG1->Cells[10][ARow].ToIntDef(0))->Get_act_d()=="ins")
				{
				SG1->Canvas->Brush->Color=0x00CCFFCC;
				}
			//del серая
			if (SPList->operator [](SG1->Cells[10][ARow].ToIntDef(0))->Get_act_r()=="del"||SPList->operator [](SG1->Cells[10][ARow].ToIntDef(0))->Get_act_d()=="del")
				{
				SG1->Canvas->Brush->Color=0x009f9f9f;
				}
			if (SPList->operator [](SG1->Cells[10][ARow].ToIntDef(0))->Get_act_r()=="no"&&SPList->operator [](SG1->Cells[10][ARow].ToIntDef(0))->Get_act_d()=="no")
				{//белая
				SG1->Canvas->Brush->Color=clWhite;
				}
			if (RepeatOBD(ARow))
				{
				SG1->Canvas->Brush->Color=0x000000FF;//повтор;   если обозначение повторяетя в группе то строка красная
				}
			}else
			{
			SG1->Canvas->Brush->Color=clWhite;//СУЩЕСТВУюТ
			}
		SG1->Canvas->FillRect(Rect);
		SG1->Canvas->Font->Color=clBlack;
		}
	//рисовка текста с переносом
	int _ofset=0;
	for (vector < pair<int,int> >::iterator i=rows.begin(); i<rows.end(); i++)
		{
		sg->Canvas->TextOutW(Rect.left+2,Rect.top+1+_ofset*sg->DefaultRowHeight,sg->Cells[ACol][ARow].SubString(i->first,i->second));
		_ofset++;
		}
	}
}// функции
	// работа с сеткой
void 			TSPEditor::RemoveRow	(int TRow,int BRow)
{
if (TRow==SG1->RowCount-1){return;}
//1 определить диапазон удаляемых строк
for (TRow=TRow; (SG1->Cells[11][TRow].ToIntDef(0)==1||SG1->Cells[10][TRow]=="")&&TRow<=BRow; TRow++);
for (BRow=BRow; (SG1->Cells[11][BRow].ToIntDef(0)==1||SG1->Cells[10][BRow]=="")&&BRow>=TRow; BRow--);
//1.5 определить итераторы начала и конца удаления
vector <SpRow*>::iterator Sact=0,Eact=0;
if (SG1->Cells[10][TRow]!="") {Sact=SPList->begin()+SG1->Cells[10][TRow].ToIntDef(0);}
if (SG1->Cells[10][BRow]!="") {Eact=SPList->begin()+SG1->Cells[10][BRow].ToIntDef(0);}
//2 задать действие / удалить объект класса / строки
vector <SpRow*>::iterator i=Sact;
while (i<=Eact)
	{
	if ((*i)->Get_act_r()!="ins")
		{
		(*i)->Delete();
		i++;
		}else
		{
		delete (*i);
		i=SPList->erase(i);
		Eact--;
		}
	}
//3 перестроить сетку ниже верхней границы выделения
ShowSP();
}
void 			TSPEditor::RecoveryRow	(int TRow,int BRow)
{
if (TRow==SG1->RowCount-1){return;}
//1 определить диапазон строк
for (TRow=TRow; (SG1->Cells[11][TRow].ToIntDef(0)==1||SG1->Cells[10][TRow]=="")&&TRow<=BRow; TRow++);
for (BRow=BRow; (SG1->Cells[11][BRow].ToIntDef(0)==1||SG1->Cells[10][BRow]=="")&&BRow>=TRow; BRow--);
//1.5 определить итераторы начала и конца удаления
vector <SpRow*>::iterator Sact=0,Eact=0;
if (SG1->Cells[10][TRow]!="") {Sact=SPList->begin()+SG1->Cells[10][TRow].ToIntDef(0);}
if (SG1->Cells[10][BRow]!="") {Eact=SPList->begin()+SG1->Cells[10][BRow].ToIntDef(0);}
//2 задать действие / удалить объект класса / строки
vector <SpRow*>::iterator i=Sact;
while (i<=Eact)
	{
	if ((*i)->Get_act_r()!="ins")
		{
		(*i)->Recover();
		}
	i++;
	}
//3 перестроить сетку ниже верхней границы выделения
ShowSP();
}
	// работа со спецификацией
void 			TSPEditor::SPInit		(void)
{
SGClear(SG1,2);
this->Caption="Редактор спецификаций";
LE1->Text="";
LE2->Text="";
CB2->ItemIndex=-1;
ClearMass();
}
void			TSPEditor::ClearMass	(void)
{
if (SPList)
	{
	for (int i=0; i<SPList->size(); i++)
		{
		delete SPList->operator [](i);
		}
	delete SPList;
	SPList=0;
	}
if (File)
	{
	for (int i=0; i<File->size(); i++)
		{
		delete File->operator [](i);
		}
    delete File;
	File=0;
	}
if (Base)
	{
	for (int i=0; i<Base->size(); i++)
		{
		delete Base->operator [](i);
		}
	delete Base;
	Base=0;
	}
if (Object)
	{
	delete Object;
	Object=0;
	}
ISP.clear();
}
void			TSPEditor::LoadSP		(String name,bool from_base)
{
//протокол загрузки
if (!SPList) {SPList=new vector <SpRow*>();};
if (!File) {File=new vector <SpRow*>();};
if (!Base) {Base=new vector <SpRow*>();};
Action_det="no";
Obu_old="";
if (!from_base)
	{
	String obd="",ext=ExtractFileExt(name);
	if (ext==".dbf")
		{
		obd=LoadDBF(name);
		}
	if (ext==".xls"||ext==".xlsx")
		{
		obd=LoadXL(name);
		}
	if (obd!="")
		{
        LoadFromBase(obd);
		}
	}else
	{
	LoadFromBase(name);
	}
CompareSP();
ShowSP();
}
String			TSPEditor::LoadXL		(String FileName)
{
XL->Connect();
XL->DisplayAlerts(false);
XL->SetActiveBooks(XL->Books_Open(FileName));
XL->SetActiveBook(XL->GetFirstBook());
XL->SetActiveSheets(XL->GetSheets());
XL->SetActiveSheet(XL->GetFirstSheet());
// счиитывание с екселя
int ppp=0;
Variant obd,obu,obu_name,name,sprazdname,format,pos,prim,pp,kol,zona,tmp;

bool mecahics=false,LastPage=false;
String TMPKod;
SpRow *Row=0;
int i,j,k,ListNumber=1,ListCount=XL->GetSheetsCount(),inc=1,SpRazd;
tmp=XL->fromCells(2,5);
if (Trim(tmp)=="Формат") {mecahics=true;}
int c1,c2,c3,c4,c5,c6,c7,c8;
if (mecahics==true)
	{
	j=6; k=56;
	inc=2;
	c1=5;c2=7;c3=9;c4=12;c5=33;c6=52;c7=55;c8=0;
	obu=XL->fromCells(58,26);   // обозначение в спецификации от механикса
	obu_name=XL->fromCells(61,26);
	}else
	{
	j=3;k=31; inc=1;
	c1=4;c2=5;c3=7;c4=8;c5=12;c6=17;c7=18;c8=19;
	obu=XL->fromCells(32,11);
	if (obu.operator UnicodeString()=="")
		{
        obu=XL->fromCells(33,12);
		}
	obu_name=XL->fromCells(35,11);
	}
if (obu.operator UnicodeString().Trim()=="")
	{
	ShowMessage("Нет обозначения спецификации.");
	return "";
	}
if (!Object)
	{
	Object=new Obd(DB,obu.operator UnicodeString());

	if (Object->Get_ID()<=0)
		{
		Action_det="ins";
		}else
		{
        Action_det="no";
		}
	if (!Object->CanUse()||Object->Get_Name()!=Trim(obu_name))
		{
		Object->SetData(Object->Get_ID(),Object->Get_SpRazd(),obu,obu_name,Object->Get_SpRazdName());
		if (Action_det!="ins")
			{
			Action_det="upd";
			}
		}
	Obu_old=Object->Get_Obd(false);
	CB2->ItemIndex=CB2->Items->IndexOf(Object->Get_SpRazdName());
	}
	Caption=Caption+" ("+obu+")";
for (ListNumber=1; ListNumber<=ListCount&&!LastPage; ListNumber++)
	{
	XL->SetActiveSheet(XL->GetSheet(ListNumber));//СЛЕДУЮЩИЙ ЛИСТ
	tmp=XL->fromCells(2,4);
	if (Trim(tmp)!="ЛИСТ  РЕГИСТРАЦИИ  ИЗМЕНЕНИЙ")
		{
		if (ListNumber>1)
			{
			if (mecahics==true){k=60;} else {k=34;}
			}
		for (i=j; i<=k; i+=inc)
			{
			//фильтр на сложную спецификацию ppp
			//obu взять с первой страницы из ячейки  далее корректировать обу по мере встречи исполнений
			format=XL->fromCells(i,c1);
			zona=XL->fromCells(i,c2);
			pos=XL->fromCells(i,c3);
			obd=XL->fromCells(i,c4);
			name=XL->fromCells(i,c5);
			kol=XL->fromCells(i,c6);
			pp=XL->fromCells(i,c7);
			if (!c8)
				{
				TMPKod=Trim(pp);
				TMPKod=Replace(TMPKod.UpperCase(),"O","0");
				TMPKod=Replace(TMPKod.UpperCase(),"О","0");
				if (TMPKod!=""&&isdigit(TMPKod[1])&&isdigit(TMPKod[2])) // разделение кода от примечания
					{
					pp=TMPKod.SubString(1,2);
					TMPKod.Delete(1,2);
					prim=TMPKod.Trim();
					}else{prim=pp; pp=""; }
				}else
				{
				prim=XL->fromCells(i,c8);
				}
			if (Trim(format)!=""|| Trim(zona)!=""|| Trim(pos)!="" || Trim(obd)!=""||Trim(name)!="" || Trim(kol)!=""|| Trim(pp)!=""|| Trim(prim)!="")
				{
				if (Pos(obd.operator UnicodeString(),"Переменные данные"))//поиск строки начала переменных данных
					{
					ppp=1;
					obu="";
					}else
					{
					int _spr=GetIDRazd(name);
					if (ppp&&Trim(format)==""&& Trim(zona)==""&& Trim(pos)==""&& Trim(obd)==""&& Trim(name)!="" && Trim(kol)==""&& Trim(pp)==""&& Trim(prim)==""&&_spr<0)
						{
						obu=name;
						}else
						{
						if (_spr>=0)
							{
							SpRazd=_spr;
							sprazdname=name;
							}else
							{
							Row=new SpRow(DB,LUser,pp,ppp,SpRazd,obd,obu,name,sprazdname,format,pos,prim,zona,kol);
							File->push_back(Row);
							}
						}
					}
				}
			}
		}else
		{
		LastPage=true;
		}
	}
XL->Book_Close(XL->GetFirstBook());
XL->Disconnect();
UniteRows(File);
return Object->Get_Obd(false);
}
String			TSPEditor::LoadDBF		(String Filename)
{
/*получить обозначение / наименование узла*/
Tspparams *wnd=new Tspparams(this);
wnd->ShowModal();
if (wnd->ModalResult==mrOk)
	{
	if (!Object)
		{
		Object=new Obd(DB,wnd->Get_Obd());
		if (Object->Get_ID()<=0)
			{
			Action_det="ins";
			}else
			{
			Action_det="no";
			}
		if (!Object->CanUse()||Object->Get_Name()!=wnd->Get_Name())
			{
			Object->SetData(Object->Get_ID(),Object->Get_SpRazd(),wnd->Get_Obd(),wnd->Get_Name(),Object->Get_SpRazdName());
			if (Action_det!="ins")
				{
				Action_det="upd";
				}
			}
		Obu_old=Object->Get_Obd(false);
		CB2->ItemIndex=CB2->Items->IndexOf(Object->Get_SpRazdName());
		}
	}
delete wnd;
TADOConnection *con=new TADOConnection(this);
con->ConnectionString="Provider=VFPOLEDB.1;Data Source="+ExtractFileDir(Filename)+";Password="";Collating Sequence=MACHINE";
cSQL *_db=new cSQL(con);
TADOQuery *rez=_db->SendSQL("select * from ["+ExtractFileName(Filename)+"]");
if (rez&&rez->RecordCount)
	{
	SpRow *Row=0;
	int pp,ppp=0,SpRazd;
	String obd,obu=Object->Get_Obd(false),name,sprazdname,format,pos,prim,zona;
	double kol;
	for (rez->First(); !rez->Eof; rez->Next())
		{
		format=rez->FieldByName("формат")->Value.operator UnicodeString().Trim();
		zona=rez->FieldByName("зона")->Value.operator UnicodeString().Trim();
		pos=rez->FieldByName("позиция")->Value.operator UnicodeString().Trim();
		if (pos=="0"){pos="";}
		obd=rez->FieldByName("обознач1")->Value.operator UnicodeString().Trim();
		name=rez->FieldByName("наименов")->Value.operator UnicodeString().Trim();
		kol=rez->FieldByName("количест")->Value;
		pp=rez->FieldByName("код")->Value.operator UnicodeString().ToIntDef(0);
		prim=rez->FieldByName("примечан")->Value.operator UnicodeString().Trim();
		if (format!=""|| zona!=""|| (pos!=""&&pos!="0") || obd!=""||name!="" || kol!=0|| prim!="")
			{
			if (obd.Pos("Переменные данные"))//поиск строки начала переменных данных
				{
				ppp=1;
				obu="";
				}else
				{
				int _spr=GetIDRazd(name);
				if (ppp&&format==""&&zona==""&&pos==""&&obd==""&&name!=""&&kol==0&&prim==""&&_spr<0)
					{
					String _t=GostToVin(name),__t=Object->Get_Obd(false);
					if (_t.SubString(1,_t.Length()-2)==__t.SubString(1,__t.Length()-2))
						{
						obu=name;
						}else
						{
						static int k=1;
						obu=Object->Get_Obd(false)+"("+(String)k+")";
						k++;
						}
					}else
					{

					if (_spr>=0)
						{
						SpRazd=_spr;
						sprazdname=name;
						}else
						{
						Row=new SpRow(DB,LUser,pp,ppp,SpRazd,obd,obu,name,sprazdname,format,pos,prim,zona,kol);
						File->push_back(Row);
						}
					}
				}
			}
		}
	UniteRows(File);
	return Object->Get_Obd(false);
	}
delete rez;
delete _db;
delete con;
return "";
}
void  			TSPEditor::LoadFromBase	(String obd)
{
int id=0;
TADOQuery *rez=DB->SendSQL("Call constructions.Get_id('"+GostToVin(obd)+"')");
if (rez&&rez->RecordCount)
	{
	id=rez->FieldByName("id")->Value;
	}
delete rez;
rez=0;
if (!Object)
	{
	Object=new Obd(DB,obd);
	Action_det="no";
	Obu_old=Object->Get_Obd(false);
	CB2->ItemIndex=CB2->Items->IndexOf(Object->Get_SpRazdName());
	}
if (id)
	{
	rez=DB->SendSQL("Call constructions.LoadFullSP('"+(String)id+"','"+(String)LUser+"')");
	if (rez&&rez->RecordCount)
		{
		SpRow *Row;
		int id,idparent,sprazd,pp,ppp,ei,state,userid;
		String obd,obu,name,sprazdname,format,pos,prim,zona,ppname,einame,user,condname,detcreator,
		detupdater,rowcreator,rowupdater;
		double kol;
		bool arhive,canchild,accept;
		TDateTime  detcreated,detupdated,rowcreated,rowupdated;
		for (rez->First(); !rez->Eof; rez->Next())
			{
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
			Row=new SpRow(DB,LUser,id,idparent,sprazd,pp,ppp,ei,state,userid,obd,obu,name,
							sprazdname,format,pos,prim,zona,ppname,einame,user,
							condname,detcreator,detupdater,rowcreator,rowupdater,
							kol,arhive,canchild,accept,detcreated,detupdated,rowcreated,
							rowupdated);
            Base->push_back(Row);
			}
		}
	delete rez;
	}
}
void			TSPEditor::CompareSP	(void)
{
if (Base->size())//есть спецификация загруженная из базы
	{//да работа со спецификацией из базы
	if (File->size()) //есть спецификация из файла
		{//да соединение данных
		//данные соединяются на основе base тоесть главный цикл идет по ней
		for (vector <SpRow*>::iterator i=Base->begin(); i<Base->end(); i++)
			{ //первое -- взять строку найти такуюже строку по ключам
			vector <SpRow*>::iterator j=0;
			bool find=false;
			j=File->begin();
			while (j<File->end()&&!find)
				{
				if ((*i)->Get_Obu(false)==(*j)->Get_Obu(false)&&(*i)->Get_Obd(false)==(*j)->Get_Obd(false))
					{
					find=true;
					}else
					{
					j++;
					}
				}
			//потом понять изменения строки если есть изменения то взять строку из спецификации
			if (find)
				{//строка найдена определить нужны ли изменения
				if 	(
				   //	(*i)->Get_Obu(false)	==(*i)->Get_Obu(false)	&&  ключ
				   //	(*i)->Get_Obd(false)	==(*i)->Get_Obd(false)	&&
					(*i)->Get_format()		!=(*j)->Get_format()	||
					(*i)->Get_zona()		!=(*j)->Get_zona()		||
					(*i)->Get_pos()			!=(*j)->Get_pos()		||
					(*i)->Get_Name()		!=(*j)->Get_Name()		||
					(*i)->Get_pp()			!=(*j)->Get_pp()		||
					(*i)->Get_ppp()			!=(*j)->Get_ppp()		||
					(*i)->Get_prim()		!=(*j)->Get_prim()		||
					(*i)->Get_kol()			!=(*j)->Get_kol()		||
					(*i)->Get_SpRazd()		!=(*j)->Get_SpRazd()
					)
					{//корректировка строки
					(*i)->Set_format((*j)->Get_format());
					(*i)->Set_zona((*j)->Get_zona());
					(*i)->Set_pos((*j)->Get_pos());
					(*i)->Set_Name((*j)->Get_Name());
				   	(*i)->Set_pp((*j)->Get_pp());
					(*i)->Set_ppp((*j)->Get_ppp());
					(*i)->Set_prim((*j)->Get_prim());
					(*i)->Set_kol((*j)->Get_kol());
					(*i)->Set_SpRazd((*j)->Get_SpRazd(),(*j)->Get_SpRazdName());
					}else
					{//строка без корректировки
					}
				}else
				{//корректировка строки для удаления
                (*i)->Delete();
				}
			//добавить строку в рабочую спецификацию
			SPList->push_back((*i));
			}
		//подгрузка новых
		//анализ загруженной спецификации на предмет строк которых нет в основной спецификации
		TADOQuery *rez=0;
		for (vector <SpRow*>::iterator i=File->begin(); i<File->end(); i++)
			{//первое -- взять строку найти такуюже строку по ключам
			vector <SpRow*>::iterator j=0;
			bool find=false;
			j=File->begin();
			while (j<File->end()&&!find)
				{
				if ((*i)->Get_Obu(false)==(*j)->Get_Obu(false)&&(*i)->Get_Obd(false)==(*j)->Get_Obd(false))
					{
					find=true;
					}else
					{
					j++;
					}
				}
			if (!find&&(*i)->Get_SpRazdName()!="Документация")
				{//добавление строки в базу
				//проверка данных детали
				String act_d="";
				rez=DB->SendSQL("Select * from constructions.det_names where obd='"+(*i)->Get_Obd(false)+"'");
				if (rez&&rez->RecordCount) //понять какое действие с деталью
					{
					if ((*i)->Get_Name()		!=rez->FieldByName("namd")->Value.operator UnicodeString()||
						(*i)->Get_pp()			!=rez->FieldByName("pp")->Value.operator int()||
						(*i)->Get_format()      !=rez->FieldByName("format")->Value.operator UnicodeString()||
						(*i)->Get_SpRazd()		!=rez->FieldByName("RazdSpID")->Value.operator int())
						{
						act_d="upd";
						}else
						{
						act_d="no";
						}
					}else
					{
					act_d="ins";      //детали в базе нет нужна вставка
					}
				delete rez;
				rez=0;
				//определить действие со строкой
				(*i)->Set_actions("ins",act_d);
				SPList->push_back((*i));
				}
			}
		delete File;
		File=0;
		delete Base;
		Base=0;
		}else
		{//нет перенос спецификации как рабочей
		delete SPList;
		SPList=0;
		delete File;
		File=0;
		SPList=Base;
		Base=0;
		}
	}else
	{//нет удаление рабочего экземпляра (если есть), записывание/обновление данных в строках
	delete SPList;
	SPList=0;
	delete Base;
	Base=0;
	SPList=File;
	File=0;
	TADOQuery *rez=0;
	for (vector <SpRow*>::iterator i=SPList->begin(); i<SPList->end(); i++)
		{//первое -- взять строку найти такуюже строку по ключам
		vector <SpRow*>::iterator j=0;
		if ((*i)->Get_SpRazdName()!="Документация")
			{//добавление строки в базу
			//проверка данных детали
			String act_d="";
			rez=DB->SendSQL("Select * from constructions.det_names where obd='"+(*i)->Get_Obd(false)+"'");
			if (rez&&rez->RecordCount) //понять какое действие с деталью
				{
				if ((*i)->Get_Name()		!=rez->FieldByName("namd")->Value.operator UnicodeString()||
					(*i)->Get_pp()			!=rez->FieldByName("pp")->Value.operator int()||
					(*i)->Get_format()      !=rez->FieldByName("format")->Value.operator UnicodeString()||
					(*i)->Get_SpRazd()		!=rez->FieldByName("RazdSpID")->Value.operator int())
					{
					act_d="upd";
					}else
					{
					act_d="no";
					}
				}else
				{
				act_d="ins";      //детали в базе нет нужна вставка
				}
			delete rez;
			rez=0;
			//определить действие со строкой
			(*i)->Set_actions("ins",act_d);
			}
		}
	}
BuildISPList();
 SPList=SortMass(SPList);
}
void			TSPEditor::BuildISPList(void)
{
if (Object)
	{
	TADOQuery *rez=DB->SendSQL("Call constructions.get_isp_list('"+(String)Object->Get_ID()+"')");
	if (rez&&rez->RecordCount)
		{
		for (rez->First(); !rez->Eof; rez->Next())
			{
			IspData tmp;
			tmp.id=rez->FieldByName("id")->Value.operator int();
			tmp.main_isp=rez->FieldByName("main")->Value;
			tmp.Set_Obd(rez->FieldByName("obd")->Value);
			ISP.push_back(tmp);
			}
		}
	//дозаполнить список исполнений
	for (vector <SpRow*>::iterator i=SPList->begin(); i<SPList->end(); i++)
		{
		String _Obu=(*i)->Get_Obu(true);
		bool inmass=false;
		for (int j=0; j<ISP.size()&&!inmass; j++)
			{
			if (ISP.operator [](j).Get_Obd(true)==_Obu)
				{
				inmass=true;
				}
			}
		if (!inmass)
			{
			IspData tmp;
			tmp.id=(*i)->Get_ParentID();
			tmp.main_isp=(*i)->Get_ppp()-1;
			tmp.Set_Obd((*i)->Get_Obu(false));
			ISP.push_back(tmp);
			}
		}
	}
}
void 			TSPEditor::ShowSP		(void)
{
//требования : сортировка по ppp,obu,sprazd,obd
for (int i = 0; i<SG1->ColCount+2; i++)
	{
	for (int j=1; j <SG1->RowCount; j++)
		{
		SG1->Cells[i][j]="";
		}
	}
if (SPList&&SPList->size())
	{
	String _obu=Object->Get_Obd(true);
	int ppp=0,Razd=-1,ofset=0,k=1;
	for (vector <SpRow*>::iterator i=SPList->begin(); i<SPList->end(); i++)
		{
		if (ppp!=(*i)->Get_ppp())
			{
			ppp=(*i)->Get_ppp();
			SG1->Cells[10][k]="";//номер строки в массиве
			SG1->Cells[11][k]="";  //индикатор служебной не редактируемой строки
			k++;
			SG1->Cells[10][k]=ofset;//номер строки в массиве
			SG1->Cells[11][k]="1";  //индикатор служебной не редактируемой строки
			k++;
			SG1->Cells[4][k]="Переменные данные";
			SG1->Cells[5][k]="для исполнений:";
			SG1->Cells[10][k]=ofset;//номер строки в массиве
			SG1->Cells[11][k]="1";  //индикатор служебной не редактируемой строки
			k++;
			_obu=(*i)->Get_Obu(true);
			SG1->Cells[5][k]=_obu;//сразу пишем обу чтобы не мудрить
			SG1->Cells[10][k]=ofset;//номер строки в массиве
			SG1->Cells[11][k]="1";  //индикатор служебной не редактируемой строки
			k++;
			Razd=0;//сброс чтобы разделы прописались с начала
			}
		if (/*ppp&&*/_obu!=(*i)->Get_Obu(true))//проверяет отличия обу (при включеном ppp )
			{
			_obu=(*i)->Get_Obu(true);
			SG1->Cells[10][k]="";//номер строки в массиве
			SG1->Cells[11][k]="";  //индикатор служебной не редактируемой строки
			k++;
			SG1->Cells[10][k]=ofset;//номер строки в массиве
			SG1->Cells[11][k]="1";  //индикатор служебной не редактируемой строки
			k++;
			SG1->Cells[5][k]=_obu;//сразу пишем обу чтобы не мудрить
			SG1->Cells[10][k]=ofset;//номер строки в массиве
			SG1->Cells[11][k]="1";  //индикатор служебной не редактируемой строки
			k++;
			}
		if ((*i)->Get_SpRazd()!=Razd)//сравнить раздел записи с текущим разделом
			{
			SG1->Cells[10][k]="";//номер строки в массиве
			SG1->Cells[11][k]="";  //индикатор служебной не редактируемой строки
			k++;
			Razd=(*i)->Get_SpRazd();
			SG1->Cells[5][k]=(*i)->Get_SpRazdName();
			SG1->Cells[10][k]=ofset;//номер строки в массиве
			SG1->Cells[11][k]="1";  //индикатор служебной не редактируемой строки
			k++;
			}
		SG1->Cells[1][k]=(*i)->Get_format();
		SG1->Cells[2][k]=(*i)->Get_zona();
		SG1->Cells[3][k]=(*i)->Get_pos();
		SG1->Cells[4][k]=(*i)->Get_Obd(true);
		SG1->Cells[5][k]=(*i)->Get_Name();
		SG1->Cells[6][k]=String((*i)->Get_kol());
		SG1->Cells[7][k]=String((*i)->Get_pp());
		SG1->Cells[8][k]=(*i)->Get_prim();
		SG1->Cells[9][k]=(*i)->Get_eiName();
		SG1->Cells[10][k]=ofset;//номер строки в массиве
		SG1->Cells[11][k]="0";  //индикатор служебной не редактируемой строки
		k++;
		ofset++;
		}
	SG1->RowCount=k+1;
	AutoWidthSG(SG1);
	}
if (Object)
	{
	LE1->Text=Object->Get_Obd(true);
	LE2->Text=Object->Get_Name();
	CB2->ItemIndex=CB2->Items->IndexOfObject((TObject*)Object->Get_SpRazd());
	}
}
int 		 	TSPEditor::GetIDRazd	(String rname)
{
for (SPRazd->First(); !SPRazd->Eof; SPRazd->Next())
	{
	if (Trim(rname)==Trim(SPRazd->FieldByName("razdname")->Value))
		{
		return SPRazd->FieldByName("razdid")->Value;
		}
	}
return -1;
}
String 		 	TSPEditor::GetNameRazd	(int id)
{
for (SPRazd->First(); !SPRazd->Eof; SPRazd->Next())
	{
	if ((String)id==Trim(SPRazd->FieldByName("RazdID")->Value))
		{
		return SPRazd->FieldByName("Razdname")->Value;
		}
	}
 return 0;
}
// сортировка вектора
vector <SpRow*> *	TSPEditor::SortMass				(vector <SpRow*> *mass)
{
vector <SpRow*> tmp;
vector <SpRow*> *Result=new vector <SpRow*>();
vector <String> ObuList;
Result->clear();
ObuList.clear();
tmp.clear();
//условие 1 подготовка -> получить список различных обу массива
for (vector <SpRow*>::iterator i=mass->begin(); i<mass->end(); i++)
	{
	String _Obu=(*i)->Get_Obu(true);
	bool inmass=false;
	for (int j=0; j<ObuList.size()&&!inmass; j++)
		{
		if (ObuList.operator [](j)==_Obu)
			{
			inmass=true;
			}
		}
	if (!inmass)
		{
		ObuList.push_back(_Obu);
		}
	}
std::sort (ObuList.begin(),ObuList.end()); //сортировка обу
int razd=0;
//1 собрать группы по постоянной и переменной части
for (int ppp=0; ppp<=1; ppp++)
	{
	//2 второй уровень вложеннойсти - отбор по обу
	for (vector <String>::iterator _obu=ObuList.begin(); _obu<ObuList.end(); _obu++)
		{
		//3й уровень вложенности -> отбор по разделу спецификации
		for (SPRazd->First(); !SPRazd->Eof; SPRazd->Next())
			{
			razd=SPRazd->FieldByName("RazdID")->Value.intVal;
			tmp.clear();
			for (vector <SpRow*>::iterator i=mass->begin(); i<mass->end(); i++)   // 1 разбить массив на несколько подмассивов
				{
				if ((*i)->Get_ppp()==ppp&&(*i)->Get_Obu(true)==(*_obu)&&(*i)->Get_SpRazd()==razd)
					{
					tmp.push_back((*i));
					}
				}
			if (tmp.size())
				{
				SortByObd(&tmp);  // 2 отсортировать подмасивы по обозначению
				for (vector <SpRow*>::iterator i=tmp.begin(); i<tmp.end(); i++)// 3 собрать массив
					{
					Result->push_back((*i));
					}
				}
			}
		}
	}
delete mass;
return Result;
}
void				TSPEditor::SortByObd			(vector <SpRow*> *mass)
{
long inc,i,j,seq[40],size=mass->size();
int s;
SpRow *TmpRow=0;
// вычисление последовательности приращений
s = increment(seq, size);
while (s >= 0)
	{
	// сортировка вставками с инкрементами inc[]
	inc = seq[s--];
	for (i = inc; i < size; i++)
		{
		for (j = i-inc; (j >= 0) && (mass->operator [](j)->Get_Obd(true) > mass->operator [](j+inc)->Get_Obd(true)); j -= inc)
			{
			TmpRow=mass->operator [](j);
			mass->operator [](j)=mass->operator [](j+inc);
			mass->operator [](j+inc)=TmpRow;
			}
		}
	}
}
int 				TSPEditor::increment			(long inc[], long size)
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
void 				TSPEditor::UniteRows 			(vector <SpRow*> *mass)
{
String tmp="",data="",pt1="",name, prim="";
int pp=0;
double kol=0;
bool NewName=false,/*DataRow=false,*/ AddInfo=false;
// удаление переносов строк
for (vector <SpRow*>::iterator i=mass->begin(); i<mass->end(); i++)//перебор строк вектора
	{
	SpRow &lnk=**i;
	(*i)->Correct_obd();//восстановление обозначения если оно было стерто
	//проверка на начало группы
	if (!isNormalRow(i)&&isGroupType(i))
		{
		// запуск сбора группы
		data=CollectGroupRows(mass,i);
		int pos=data.Pos(" ");
		if (!pos) {pos=data.Length()+1;}
		pt1=data.SubString(1,pos-1).Trim();       //набор разбит на 2 части
        pt1=GetWordEnding(pt1);
		if (pos<data.Length()){data=data.SubString(pos+1,data.Length());} else {data="";}
		AddInfo=true;// разрешение на добавление в наименованию даты
		}
	//проверка на наличие переноса строк
	if ((i+1)!=mass->end())
		{
		if (isNormalRow(i)&&!isNormalRow(i+1))
			{
			// запуск сбора переносов
			// получение количества, пп и примечаний
			CollectСarriedRows(mass,i,tmp,pp,kol,prim);
			NewName=true;
			}else
			{
			NewName=false;
			tmp=(*i)->Get_Name();
			}
		}else
		{
		NewName=false;
		tmp=(*i)->Get_Name();
		}

	if (isFullDataRow(tmp))
		{
        AddInfo=false;
		}
	//внесение  изменений  при необходимости
	if (AddInfo||NewName)
		{
		if (AddInfo)
			{
			name=pt1.Trim()+" "+tmp.Trim()+" "+data.Trim();
			}else
			{
			name=tmp.Trim();
			(*i)->Set_kol(kol);
		   	(*i)->Set_pp(pp);
			(*i)->Set_prim(prim);
			}
		(*i)->Set_Name(name);
		}
	}
}
String 				TSPEditor::CollectGroupRows		(vector <SpRow*> *mass,vector <SpRow*>::iterator &i)
{
String data="";
vector <SpRow*>::iterator k=i;
while (!isNormalRow(i)&&(*k)->Get_SpRazd()==(*i)->Get_SpRazd()&&i<mass->end())
	{
	data=data.Trim()+" "+(*i)->Get_Name();
	i++;
	}
if (k!=i)
	{
	for (vector <SpRow*>::iterator j=k; j<i; j++)
		{
		delete (*j);
		}
	i=mass->erase(k,i);
	}
return data.Trim();
}
void 				TSPEditor::CollectСarriedRows	(vector <SpRow*> *mass,vector <SpRow*>::iterator &i,String &name,int &pp,double &kol,String &prim)
{
String data="",_prim="";
vector <SpRow*>::iterator k=i;
data=(*k)->Get_Name();
_prim=(*k)->Get_prim();
pp=(*k)->Get_pp();
kol=(*k)->Get_kol();
i++;
while (i<mass->end()&&!isNormalRow(i)&&(*k)->Get_SpRazd()==(*i)->Get_SpRazd()&&!isGroupType(i))
	{
	data=data.Trim()+" "+(*i)->Get_Name();
	_prim=_prim.Trim()+" "+(*i)->Get_prim();
	if (!pp&&!kol)
		{
		pp=(*i)->Get_pp();
		kol=(*i)->Get_kol();
		}
	i++;
	}
if (k!=i)
	{
	for (vector <SpRow*>::iterator j=k+1; j<i; j++)
		{
		delete (*j);
		}
	mass->erase(k+1,i);
	}
i=k;
name=data.Trim();
prim=_prim.Trim();
return ;
}
bool				TSPEditor::isFullDataRow		(String name)
{
if (name.Pos("ГОСТ")||name.Pos("ОСТ")||name.Pos("СТП")||name.Pos("ТУ")||name.Pos("АТК")||name.Pos("ASME")||name.Pos("DIN"))
	{
	return true;
	}
return false;
}
bool 				TSPEditor::isGroupType  		(vector <SpRow*>::iterator i)
{
String name=(*i)->Get_Name();        //определить критерии множественного числа существительного по окончанию
int FWE=name.Pos(" ");
if (!FWE)
	{
	FWE=name.Length()+1;
	}
if ((name.SubString(FWE-1,1).LowerCase()=="ы"||name.SubString(FWE-1,1).LowerCase()=="и"||name.SubString(FWE-2,2).LowerCase()=="ца")&&name.SubString(1,1)==name.SubString(1,1).UpperCase())
	{
	return true;
	}
	else
	{
	return false;
	}
}
bool            	TSPEditor::isNormalRow  		(vector <SpRow*>::iterator i)
{
if (
	(*i)->Get_Obd(false)==""&&
	(*i)->Get_format()==""&&
	(*i)->Get_zona()==""&&
	(*i)->Get_pos()==""//&&
	//(*i)->Get_kol()==0&&
   //	(*i)->Get_pp()<0&&  //похоже  что если ячейка эксель пустая он вернется как нулевой а для считания его пустым нужна -1
	//(*i)->Get_prim()==""   //закрыл т.к. с этой строкой любая строка имеющая название и примечание считается нормальной и не объединяется
	)
	{
	return false;
	}else
	{
	return true;
	}
}
// вспомогательные функции
bool            	TSPEditor::isEmptyRow 			(vector <SpRow*>::iterator i)
{
if ((*i)->Get_Obd(false)==""&&
	(*i)->Get_format()==""&&
	(*i)->Get_zona()==""&&
	(*i)->Get_pos()==""&&
	(*i)->Get_kol()==0&&
	//(*i)->Get_pp()<0&&
	(*i)->Get_prim()==""&&
	(*i)->Get_Name()=="")
	{
	return true;
	}else
	{
	return false;
	}
}
String 				TSPEditor::GetWordEnding		(String word)
{
word.Delete(word.Length(),1);
if (word.SubString(word.Length(),1).LowerCase()=="ц")
	{
	word=word+"о";
	} else
	{
	if ((word.SubString(word.Length(),1).LowerCase()=="т"&&itVowel(word.SubString(word.Length()-1,1)))||(word.SubString(word.Length(),1).LowerCase()=="к"&&!itVowel(word.SubString(word.Length()-1,1))))
		{
		word=word+"а";
		}else
		{
		if (word.SubString(word.Length(),1).LowerCase()!="т"&&word.SubString(word.Length(),1).LowerCase()!="к")
			{
			word=word+"а";
			}
		}
	}
return word;
}
bool				TSPEditor::itVowel             	(String letter)
{
String Vowels="яиюэоаыуеё";
if (Vowels.LowerCase().Pos(letter)||Vowels.UpperCase().Pos(letter))
	{
	return true;
	}
return false;
}

bool 				TSPEditor::RepeatOBD			(int ARow)
{
//проверка на дублирование обозначения в сетке
return false;
}
String 				TSPEditor::GetUUID				(void)
{
	TADOQuery *rez=DB->SendSQL("select uuid() uuid");
	if (rez&&rez->RecordCount)
	{
        return  rez->FieldByName("uuid")->Value;
	}
}
// функции ввода текста в вектор
void __fastcall 	TSPEditor::SG1KeyPress	(TObject *Sender, wchar_t &Key)
{
if (ReadOnly) {return;}
if (SG1->Cells[11][SG1->Row].ToIntDef(0)==1) {return;}
//колонки 7 и 9 комбо боксы
int ACol=SG1->Col,ARow=SG1->Row;
bool show=false;
TRect R=SG1->CellRect(ACol,ARow);
R.Left=R.Left+SG1->Left;
R.Right=R.Right+SG1->Left;
R.Top=R.Top+SG1->Top;
R.Bottom=R.Bottom+SG1->Top;
if (ACol!=7&&ACol!=9)
	{
	Editor->Left=R.Left+1;
	Editor->Top=R.Top+1;
	Editor->Width=(R.Right+1)-R.Left;
	Editor->Height=(R.Bottom+1)-R.Top;
	Editor->Text="";
	if (Key>=32)
		{
		Editor->Text=SG1->Cells[ACol][ARow]+Key;
		show=true;
		} else
		{
		if (Key==13)
			{
			Editor->Text=SG1->Cells[ACol][ARow];
			show=true;
			}
		if (Key==8)
			{
			Editor->Text=SG1->Cells[ACol][ARow].SubString(1,SG1->Cells[ACol][ARow].Length()-1);
			show=true;
			}
		}
	Editor->Visible=show;
	if (show)
		{
		Editor->SetFocus();
		Editor->SelStart=Editor->Text.Length();
		}
	}else
	{
	int _width=0;
	if (ACol==7)
		{
		_width=LoadComboData(1);
		}
	if (ACol==9)
		{
		_width=LoadComboData(0);
		}
	if (_width<R.Width())
		{
		_width=R.Width();
		}
	Combo->Left=R.Right-_width;
	Combo->Top=R.Top+1;
	Combo->Width=(R.Right+1)-Combo->Left;
	Combo->Height=(R.Bottom+1)-Combo->Top;
	Combo->ItemIndex=Combo->Items->IndexOfName(SG1->Cells[ACol][ARow]);
	Combo->Visible=true;
	}
}
void __fastcall 	TSPEditor::SG1DblClick	(TObject *Sender)
{
if (ReadOnly) {return;}
if (SG1->Cells[11][SG1->Row].ToIntDef(0)==1) {return;}
int ACol=SG1->Col,ARow=SG1->Row;
TRect R=SG1->CellRect(ACol,ARow);
R.Left=R.Left+SG1->Left;
R.Right=R.Right+SG1->Left;
R.Top=R.Top+SG1->Top;
R.Bottom=R.Bottom+SG1->Top;
if (ACol!=7&&ACol!=9)
	{
	Editor->Left=R.Left+1;
	Editor->Top=R.Top+1;
	Editor->Width=(R.Right+1)-R.Left;
	Editor->Height=(R.Bottom+1)-R.Top;
	Editor->Visible=true;
	Editor->SetFocus();
	Editor->Text=SG1->Cells[ACol][ARow];
	Editor->SelStart=Editor->Text.Length();
	}else
	{
	int _width=0;
	if (ACol==7)
		{
		_width=LoadComboData(1);
		}
	if (ACol==9)
		{
		_width=LoadComboData(0);
		}
	if (_width<R.Width())
		{
		_width=R.Width();
		}
	Combo->Left=R.Right-_width;
	Combo->Top=R.Top+1;
	Combo->Width=(R.Right+1)-Combo->Left;
	Combo->Height=(R.Bottom+1)-Combo->Top;
	if (ACol==7)
		{
		Combo->ItemIndex=Combo->Items->IndexOfObject((TObject *)SG1->Cells[ACol][ARow].ToIntDef(0));
		}
	if (ACol==9)
		{
		Combo->ItemIndex=Combo->Items->IndexOf(SG1->Cells[ACol][ARow]);
		}
	Combo->Visible=true;
	}
}
void __fastcall 	TSPEditor::EditorKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
if (Key==13)
	{
	Editor->Visible=false;
	//перемещение выделения
	if (SG1->Col<SG1->ColCount-1)
		{
		SG1->Col++;
		}else
		{
		if (SG1->Row<SG1->RowCount-1)
			{
			SG1->Col=1;
			SG1->Row++;
			}else
			{
			SG1->Col=1;
			SG1->Row=1;
			}
		}
	}
}
void				TSPEditor::SaveToSPRow	(void)
{
if (SG1->Cells[10][SG1->Row]!="")//если строка из массива
	{//то обновить в ней данные
	vector <SpRow*>::iterator row=SPList->begin()+SG1->Cells[10][SG1->Row].ToInt();
	switch (SG1->Col)
		{
		case 1:{(*row)->Set_format(Editor->Text.Trim());break;}
		case 2:{(*row)->Set_zona(Editor->Text.Trim());	break;}
		case 3:{(*row)->Set_pos(Editor->Text.Trim());	break;}
		case 4:{(*row)->SetObd(Editor->Text.Trim());	break;}
		case 5:{(*row)->Set_Name(Editor->Text.Trim());	break;}
		case 6:	{
				String  txt=Editor->Text.Trim();
				if (txt!="")
					{
					try
						{
						(*row)->Set_kol(Replace(txt,".",",").ToDouble());
						} catch (...) {}
					};
				break;
				}
		case 7:{
				if (Combo->ItemIndex>=0)
					{
					(*row)->Set_pp((int)Combo->Items->Objects[Combo->ItemIndex]);
					}
				break;
				}
		case 8:{(*row)->Set_prim(Editor->Text.Trim());		SG1->Cells[8][SG1->Row]=(*row)->Get_prim(); 		break;}
		case 9:{
				if (Combo->ItemIndex>=0)
					{
					(*row)->Set_ei((int)Combo->Items->Objects[Combo->ItemIndex]);
					}
				break;
				}
		default:break;
		}
	}else
	{//иначе добавить новую cтроку в массив с записанными данными
	//проверить существование детали в базе
	SpRow *row;
	 //данные строки
		//деталь
		int id=0,
			SpRazd=0,pp=0;//получить из текущего расположеия строки
		String
			Obd="",//назначить из активной ячейки
			Name="",//назначить из активной ячейки
			SpRazdName="",//получить из текущего расположеия строки
			format="";//назначить из активной ячейки
		//строка
		int idparent=0,
			ppp=0,//получить из текущего расположеия строки
			ei=401;//назначить из активной ячейки  !!!!!!!!!!!!!!!!!!!!!!!!! warning жесткая не настраиваемая привязка
		double kol=1;//назначить из активной ячейки
		String
			Obu="",
			pos="",//назначить из активной ячейки
			prim="",//назначить из активной ячейки
			zona="",//назначить из активной ячейки
			eiName="шт.";//назначить из активной ячейки!!!!!!!!!!!!!!!!!!!!!!!!! warning жесткая не настраиваемая привязка
	//служебные
		//деталь
		int state=StateID,
			UserID=LUser;
		String
			ppName="",//получить из текущего расположеия строки
			User="",//имя пользователя LUser
			CondName=StateName,
			DetCreator="",
			DetUpdater="";
		TDateTime
			DetCreated=Date(),
			DetUpdated=Date();
		//строка
		String
			RowCreator="",
			RowUpdater="";
		TDateTime
			RowCreated=Date(),
			RowUpdated=Date();
		//прочая
		int
			_User=LUser;
		String
			action_row="ins",
			action_det="ins";//в зависимости от id ins/no
		bool
			arhive=false,
			CanChild=false,
			Accept=true,
			inBase=false;
	//назначение переменных
	switch (SG1->Col)
		{
		case 1:{format=Editor->Text.Trim();break;}
		case 2:{zona=Editor->Text.Trim();break;}
		case 3:{pos=Editor->Text.Trim();break;}
		case 4:{Obd=GostToVin(Editor->Text.Trim());break;}
		case 5:{Name=Editor->Text.Trim();break;}
		case 6:{
				String  txt=Editor->Text.Trim();
				if (txt!="")
					{
					try
						{
						kol=Replace(txt,".",",").ToDouble();
						} catch (...) {}
					}
				break;
				}
		case 7:{
				if (Combo->ItemIndex>=0)
					{
					pp=(int)Combo->Items->Objects[Combo->ItemIndex];
					ppName=Combo->Items->operator [](Combo->ItemIndex).SubString(4,Combo->Items->operator [](Combo->ItemIndex).Length()).Trim();
					}
				break;
				}
		case 8:{prim=Editor->Text.Trim();break;}
		case 9:{
				if (Combo->ItemIndex>=0)
					{
					ei=(int)Combo->Items->Objects[Combo->ItemIndex];
					eiName=Combo->Items->operator [](Combo->ItemIndex);
					}
				break;
				}
		default:break;
		}
	if (format!=""||zona!=""||pos!=""||Obd!=""||Name!="")//проверка на наличие текста
		{
		//заполнение данных строки
		int line=-1;bool before=false;
		if (SG1->Cells[10][SG1->Row-1]!="")
			{//проверить номер строки выше
			before=false;
			line=SG1->Cells[10][SG1->Row-1].ToInt();
			}else
			{
			if (SG1->Cells[10][SG1->Row+1]!="")
				{//если его нет то строки ниже
				before=true;
				line=SG1->Cells[10][SG1->Row+1].ToInt();
				}
			}
		 if (line>=0)
			 {//если есть номер то скопироватьотуда
			 vector <SpRow *>::iterator i=SPList->begin()+line;
			 SpRazd=(*i)->Get_SpRazd();
			 SpRazdName=(*i)->Get_SpRazdName();
			 ppp=(*i)->Get_ppp();
			 Obu=(*i)->Get_Obu(false);
			 idparent=(*i)->Get_ParentID();
			 }else
			 { //если его нет спросить с пользователя раздел спецификации  проверить obd в object
			 idparent=Object->Get_ID();
			 Obu=Object->Get_Obd(false);
			 Trzd *wnd=new Trzd(this,SPRazd);
			 wnd->ShowModal();
			 if (wnd->ModalResult==mrOk&&wnd->Get_RazdName()!="")
				 {
				 SpRazd=wnd->Get_RazdID();
				 SpRazdName=wnd->Get_RazdName();
				 }else
				 {
				 delete wnd;
                 return;
				 }
			 delete wnd;
			 }
		TADOQuery *rez=DB->SendSQL("Call constructions.Get_id('"+GostToVin(Obd)+"')");
		if (rez&&rez->RecordCount)
			{
			id=rez->FieldByName("id")->Value;
			}
		delete rez;
		row=new SpRow(DB,_User,id,idparent,SpRazd,pp,ppp,ei,state,UserID,Obd,Obu,Name,SpRazdName,format,pos,prim,
					zona,ppName,eiName,User,CondName,DetCreator,DetUpdater,RowCreator,RowUpdater,
					action_row,action_det,kol,arhive,CanChild,Accept,inBase,DetCreated,DetUpdated,
					RowCreated,RowUpdated);
		if (id)
			{//существует
				//взять данные по детали
			row->Load_det();
			row->Set_actions("ins","no");
			}
		//обновить данные в сетке
		if (line<0)
			{
			SPList->push_back(row);
			}else
			{
			if (before)
				{
				SPList->insert(SPList->begin()+line,row);
				}else
				{
				SPList->insert(SPList->begin()+line+1,row);
				}
			}
		if (autosort->Checked)
			{
			SPList=SortMass(SPList);
			}
		}
	}
ShowSP();
}
void __fastcall 	TSPEditor::ComboClick	(TObject *Sender)
{
Combo->Visible=false;
SaveToSPRow();
SG1->SetFocus();
}
void __fastcall 	TSPEditor::EditorExit	(TObject *Sender)
{
Editor->Visible=false;
SaveToSPRow();
Editor->Text="";
SG1->SetFocus();
}
void __fastcall 	TSPEditor::ComboExit	(TObject *Sender)
{
Combo->Visible=false;
SG1->SetFocus();
}
int					TSPEditor::LoadComboData(int type)
{
String sql="";
Combo->Items->Clear();
int _length=0;
switch (type)
	{
	case 0:{sql="Call catalogs.Get_ei_list('"+(String)ei_opt->ItemIndex+"')";break;}
	case 1:{sql="Call catalogs.Get_pp_list()";break;}
	default:sql="";
	}
if (sql!="")
	{
	TADOQuery *rez=DB->SendSQL(sql);
	if (rez&&rez->RecordCount)
		{
		for (rez->First(); !rez->Eof; rez->Next())
			{
			Combo->Items->AddObject(rez->Fields->operator [](1)->Value.operator UnicodeString(),(TObject *)rez->Fields->operator [](0)->Value.operator int());
			int _width=Canvas->TextWidth(rez->Fields->operator [](1)->Value);
			if (_length<_width)
				{
				_length=_width+20;
				}
			}
		//Combo->ItemIndex=0;
		}
	delete rez;
	}
return  _length;
}
//действия
void __fastcall 	TSPEditor::autosortClick(TObject *Sender)
{
if (autosort->Checked)
	{
	SPList=SortMass(SPList);
	}
ShowSP();
}

//смена данных главного узла
void __fastcall TSPEditor::LE1Exit(TObject *Sender)
{
if (ReadOnly) {return;}
//изменено поле обозначения
if (Object)
	{//спецификация загружена
	if (Object->Get_Obd(true)!=LE1->Text.Trim()||Object->Get_Obd(false)!=LE1->Text.Trim())
		{//обозначение отличается от загруженного
		int id=0;
		TADOQuery *rez=DB->SendSQL("Call constructions.Get_id('"+GostToVin(LE1->Text)+"')");
		if (rez&&rez->RecordCount)
			{
			id=rez->FieldByName("id")->Value;
			}
		delete rez;
		if (!id||GostToVin(LE1->Text.Trim())==Obu_old /*и не находится в списке исполнений*/)
			{//в этом режиме не допускается пересечение с деталями которые уже есть в базе
			if (Action_det!="ins")
				{
				Action_det="upd";
				}
			//заменить данные в массиве спецификации
			for (vector <SpRow *>::iterator i=SPList->begin(); i<SPList->end(); i++)
				{
				if ((*i)->Get_ParentID()==Object->Get_ID()&&(*i)->Get_Obu(false)==Object->Get_Obd(false))
					{
					(*i)->SetObu(LE1->Text);
					}
				}
			//заменить данные в массиве исполнений
			if (ISP.size())
				{ //найти исполнение и изменить обозначение
				for (int i=0; i<ISP.size(); i++)
					{
					if (ISP[i].id==Object->Get_ID()&&ISP[i].Get_Obd(false)==Object->Get_Obd(false))
						{
						ISP[i].Set_Obd(LE1->Text);
						}
					}
				}else
				{//если массив пуст то добавиться как базовое исполнение
				IspData tmp;
				tmp.id=Object->Get_ID();
				tmp.main_isp=true;
				tmp.selected=false;
				tmp.Set_Obd(LE1->Text);
				ISP.push_back(tmp);
				}
			//загруженное обозначение изменяетcя
			Object->SetData(Object->Get_ID(),Object->Get_SpRazd(),LE1->Text.Trim(),Object->Get_Name(),Object->Get_SpRazdName());
			}
		}
	//возврат обозначения к обозначению из структуры
	LE1->Text=Object->Get_Obd(true);
	}else
	{
	LE1->Text="";
	}
}
void __fastcall TSPEditor::LE2Exit(TObject *Sender)
{
if (Object)
	{
	if (!ReadOnly)
		{
		Object->SetData(Object->Get_ID(),Object->Get_SpRazd(),Object->Get_Obd(false),LE2->Text.Trim(),Object->Get_SpRazdName());
		}
	//возврат наименования из структуры
	LE2->Text=Object->Get_Name();
	}else
	{
	LE2->Text="";
	}
}
void __fastcall TSPEditor::CB2Change(TObject *Sender)
{
if (ReadOnly) {return;}
if (Object)
	{
	Object->SetData(Object->Get_ID(),(int)CB2->Items->Objects[CB2->ItemIndex],Object->Get_Obd(false),Object->Get_Name(),CB2->Items->operator [](CB2->ItemIndex));
	}
}


//сохранение в базу
bool			TSPEditor::SaveToBase	(void)
{
if (CB2->ItemIndex<0)
	{
	ShowMessage("Укажите раздел спецификации для узла");
	return false;
	}
DB->SendCommand("begin");
//сохранить узел
vector <SpRow *>::iterator i;
//проверить наличие исполнений в базе записать в базу те которых нет
for (vector <IspData>::iterator i =ISP.begin(); i <ISP.end(); i++)
	{
	TADOQuery *rez=DB->SendSQL("Call constructions.Get_id('"+i->Get_O_V_Obd()+"')");
	if (rez&&rez->RecordCount) 
		{
		i->id=rez->FieldByName("id")->Value.operator int();
		//обновить данные в тех что уже есть в базе
		if (!i->Get_Obd(false).Length())  //замена пустого обозначения на uid
		{
			i->Set_Obd(GetUUID());
		}

		DB->SendCommand("update constructions.det_names set obd='"+i->Get_Obd(false)+"', namd='"+Object->Get_Name()+"',razdSPID='"+(String)Object->Get_SpRazd()+"',base='mysql',UpdateDate=CURRENT_TIMESTAMP(),UpdateUser='"+UserName+"'where id='"+(String)i->id+"'");
		}else
		{
		if (DB->SendCommand("insert into constructions.det_names (obd,namd,razdSPID,state,CreateDate,CreateUser,UpdateDate,UpdateUser)values('"+i->Get_Obd(false)+"','"+Object->Get_Name()+"','"+(String)Object->Get_SpRazd()+"','"+(String)StateID+"',CURRENT_TIMESTAMP(),'"+UserName+"',CURRENT_TIMESTAMP(),'"+UserName+"')"))
			{ //вставка исполнения
			TADOQuery *rez1=DB->SendSQL("Call constructions.Get_id('"+i->Get_Obd(false)+"')");
			if (rez1&&rez1->RecordCount) 
				{  //получение идентификатора
				i->id=rez1->FieldByName("id")->Value.operator int();
				}
			delete rez1;
			}else
			{
			i->id=0;
			}
		}
	}
//сохранение нового списка исполнений
	//получение идентификаторов всех исполнений
	String _ids="",_idm="";
	for (vector <IspData>::iterator i =ISP.begin(); i <ISP.end(); i++)
		{
		if (i->main_isp)
			{
			_idm=(String)i->id;
			}
		_ids=_ids+(String)i->id+",";
		}
	if (_ids!="")
		{
		_ids.Delete(_ids.Length(),1);
		//удаление идетнификаторов из таблицы исполнения
		DB->SendCommand("Delete from constructions.basik_performance where id in("+_ids+")");
		DB->SendCommand("Delete from constructions.basik_performance where id00="+_idm);
		//Вставка новых пар данных
		for (vector <IspData>::iterator i =ISP.begin(); i <ISP.end(); i++)
			{
			if (!i->main_isp)
				{
				DB->SendCommand("Insert into constructions.basik_performance (id,id00)values('"+(String)i->id+"','"+_idm+"')");
				}
			}
		}
//расставить ид в массиве
String _obu="";
bool find=false;
vector <IspData >::iterator j;
for (vector <SpRow*>::iterator i=SPList->begin(); i<SPList->end(); i++)
	{
	if (_obu!=(*i)->Get_Obu(false))
		{ //проверка на смену обозначния
		_obu=(*i)->Get_Obu(false);
		find=false;
		j=ISP.begin();
		while (j <ISP.end()&&!find)
			{//поиск идентификатора для обозначения
			if (j->Get_Obd(false)==(*i)->Get_Obu(false))
				{
				find=true;
				}else
				{
				j++;
				}
			}
		}
	if (find) //указание идентификатора
		{
		(*i)->Set_IDp(j->id);
		}else
		{
        (*i)->Set_IDp(0);
		}
	}

//	обновление данных деталей
i=SPList->begin();
while (i<SPList->end())
	{
		if (!(*i)->Get_Obd(false).Length())  //замена пустого обозначения на uid
		{
			(*i)->SetObd(GetUUID());
		}
	if ((*i)->Get_act_d()=="upd")
		{
		String pp=(String)(*i)->Get_pp();
		while (pp.Length()<2)
			{
            pp="0"+pp;
			}
		if (DB->SendCommand("update constructions.det_names set obd='"+(*i)->Get_Obd(false)+"', namd='"+(*i)->Get_Name()+"',format='"+(*i)->Get_format()+"',razdSPID='"+(String)(*i)->Get_SpRazd()+"',pp='"+pp+"',base='mysql',UpdateDate=CURRENT_TIMESTAMP(),UpdateUser='"+UserName+"'where id='"+(String)(*i)->Get_ID()+"'"))
			{//правка метки
			(*i)->Set_actions((*i)->Get_act_r(),"no");
			}
		i++;
		}else
		{
        i++;
		}
	}
//вставка новых деталей
i=SPList->begin();
while (i<SPList->end())
	{
	if ((*i)->Get_act_d()=="ins")
		{
		String pp=(String)(*i)->Get_pp();
		while (pp.Length()<2)
			{
			pp="0"+pp;
			}
		if (!(*i)->Get_Obd(false).Length())  //замена пустого обозначения на uid
		{
			(*i)->SetObd(GetUUID());
		}
		if (DB->SendCommand("insert into constructions.det_names (obd,namd,pp,format,razdSPID,state,CreateDate,CreateUser,UpdateDate,UpdateUser)values('"+(*i)->Get_Obd(false)+"','"+(*i)->Get_Name()+"','"+pp+"','"+(*i)->Get_format()+"','"+(String)(*i)->Get_SpRazd()+"','"+(String)StateID+"',CURRENT_TIMESTAMP(),'"+UserName+"',CURRENT_TIMESTAMP(),'"+UserName+"')"))
			{ //правка метки
			(*i)->Set_ID();
			}
			i++;
		}else
		{
		i++;
		}
	}
//сохранить спецификацию
// удаление срок с меткой удалить
i=SPList->begin();
while (i<SPList->end())
	{
	if ((*i)->Get_act_r()=="del")
		{
		if (
		DB->SendCommand("delete from constructions.det_tree where idparent='"+(String)(*i)->Get_idp_t()+"' and idchild='"+(String)(*i)->Get_id_t()+"'")
		)
			{//удаление строк из вектора
			i=SPList->erase(i);
			}else
			{
			i++;
			}
		}else
		{
		if ((*i)->Get_act_r()=="no"&&(*i)->Get_act_d()=="no")
			{//убрать из вектора все строки которые не изменяются
			i=SPList->erase(i);
			}else
			{
			i++;
			}
		}
	}
//обновление данных строк
i=SPList->begin();
while (i<SPList->end())
	{
	if ((*i)->Get_act_r()=="upd")
		{
		String ei=(String)(*i)->Get_ei();
		while (ei.Length()<3)
			{
			ei="0"+ei;
			}
		if (
		DB->SendCommand("update constructions.det_tree set ppp='"+(String)(*i)->Get_ppp()+"',ei='"+ei+"',kol='"+Replace((String)(*i)->Get_kol(),",",".")+"',zona='"+(*i)->Get_zona()+"',pos='"+(*i)->Get_pos()+"',prim='"+(*i)->Get_prim()+"',base='mysql',UpdateDate=CURRENT_TIMESTAMP(),UpdateUser='"+UserName+"',idparent='"+(String)(*i)->Get_ParentID()+"',idchild='"+(String)(*i)->Get_ID()+"' where idparent='"+(String)(*i)->Get_idp_t()+"' and idchild='"+(String)(*i)->Get_id_t()+"'")
		)
			{//удаление строк из вектора
			i=SPList->erase(i);
			}else
			{
			i++;
			}
		}else
		{
        i++;
		}
	}
//вставка новых строк
i=SPList->begin();
while (i<SPList->end())
	{
	if ((*i)->Get_act_r()=="ins")
		{
		String ei=(String)(*i)->Get_ei();
		while (ei.Length()<3)
			{
			ei="0"+ei;
			}
		if (
		DB->SendCommand("insert into constructions.det_tree (idparent,idchild,ppp,ei,kol,zona,pos,prim,CreateDate,CreateUser,UpdateDate,UpdateUser) values ('"+(String)(*i)->Get_ParentID()+"','"+(String)(*i)->Get_ID()+"','"+(String)(*i)->Get_ppp()+"','"+ei+"','"+Replace((String)(*i)->Get_kol(),",",".")+"','"+(*i)->Get_zona()+"','"+(*i)->Get_pos()+"','"+(*i)->Get_prim()+"',CURRENT_TIMESTAMP(),'"+UserName+"',CURRENT_TIMESTAMP(),'"+UserName+"')")
		)
			{//удаление строк из вектора
			i=SPList->erase(i);
			}else
			{
			i++;
			}
		}else
		{
        i++;
		}
	}
if (SPList->size())
	{
	DB->SendCommand("rollback");
	return false;
	}else
	{
	DB->SendCommand("commit");
	return true;
	}
}
//получение распечатки хл
void			TSPEditor::GetXL	(void)
{
//вывод в эксель
if (!(SPList&&SPList->size()))
	{
	ShowMessage("Спецификация пуста");
	return;
	}
//получить расположение папки с шаблонами
AnsiString file="";
TADOQuery *rez=DB->SendSQL("Select value from administration.settings where property='template'");
if (rez&&rez->RecordCount)
	{
	file=rez->FieldByName("value")->Value.operator UnicodeString()+"sptemplate.xlt";
	}
if (file=="")
	{
	ShowMessage("потеряна директория с шаблонами");
	return;
	}
cExcel *to=new cExcel();
to->Connect();
to->DisplayAlerts(false);
to->SetActiveBooks(to->Books_Open(file));
// Инициализация переменных указателей на итемы екселя
to->SetActiveBook(to->GetFirstBook());
to->SetActiveSheets(to->GetSheets());
to->SetActiveSheet(to->GetFirstSheet());
//перебор строк по массиву
to->Visible(true);

SPList=SortMass(SPList);
//инициализация переменных для вывода
int end=27,//номер последней строки листа
	start=3, //номер первой строки листа
	nl=32;//строка вывода обозначения
int list=2; //номер текущего листа
to->SetActiveSheet(to->GetFirstSheet());
list=1;
String _obu=Object->Get_Obd(true);
int ppp=0,Razd=-1,ofset=0,k=1;

for (int i=0,j=start;i<SPList->size(); i++,j++)
	{
	if (list==1&&j==start) //ВНИМАНИЕ ЗАПЛАТКА !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		{                  //ВНИМАНИЕ ЗАПЛАТКА !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		j=10;//пустые строчки перед началом печати списка
		}                  //ВНИМАНИЕ ЗАПЛАТКА !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	if (ppp!=SPList->operator [](i)->Get_ppp())
		{
		ppp=SPList->operator [](i)->Get_ppp();
		j+=2;
		to->toCells(j,8,"Переменные данные");
		to->toCells(j,12,"для исполнений:");
		to->GetRange(j,8,j,8).OlePropertySet("HorizontalAlignment",-4152); //право
		to->GetRange(j,12,j,12).OlePropertySet("HorizontalAlignment",-4131);//лево
		to->GetRange(j,8,j,12).OlePropertyGet("Font").OlePropertySet("Bold",true);
		j++;
		_obu=SPList->operator [](i)->Get_Obu(true);
		to->toCells(j,12,_obu);//сразу пишем обу чтобы не мудрить
		to->GetRange(j,12,j,12).OlePropertyGet("Font").OlePropertySet("Bold",true);
		to->GetRange(j,12,j,12).OlePropertyGet("Font").OlePropertySet("Underline",3);
		to->GetRange(j,12,j,12).OlePropertySet("HorizontalAlignment",-4108); //центр
		j++;
		Razd=0;//сброс чтобы разделы прописались с начала
		}
	if (/*ppp&&*/_obu!=SPList->operator [](i)->Get_Obu(true))//проверяет отличия обу (при включеном ppp )
		{
		_obu=SPList->operator [](i)->Get_Obu(true);
		j+=2;
		to->toCells(j,12,_obu);//сразу пишем обу чтобы не мудрить
		to->GetRange(j,12,j,12).OlePropertyGet("Font").OlePropertySet("Bold",true);
		to->GetRange(j,12,j,12).OlePropertyGet("Font").OlePropertySet("Underline",3);
		to->GetRange(j,12,j,12).OlePropertySet("HorizontalAlignment",-4108); //центр
		j++;
		}
	if (SPList->operator [](i)->Get_SpRazd()!=Razd)//сравнить раздел записи с текущим разделом
		{
		j++;
		Razd=SPList->operator [](i)->Get_SpRazd();
		to->toCells(j,12,SPList->operator [](i)->Get_SpRazdName());
		to->GetRange(j,12,j,12).OlePropertyGet("Font").OlePropertySet("Bold",true);
		to->GetRange(j,12,j,12).OlePropertySet("HorizontalAlignment",-4108); //центр
		to->GetRange(j,12,j,12).OlePropertyGet("Font").OlePropertySet("Underline",3);
		j+=2;
		}

	if (j>end)
		{
		to->toCells(nl,11,Object->Get_Obd(true));
		if (list==1)
			{
			to->toCells(35,11,Object->Get_Name());
			to->toCells(36,17,list);
			nl=37;
			}else
			{
			to->toCells(38,19,list);
			}
		end=30;
		list++;
		to->SetActiveSheet(to->GetSheet(list));
		to->Sheet_Copy(to->GetSheet(list),to->GetSheet(list+1));
		to->Set_Sheet_Name(to->GetSheet(list+1),"Лист"+String(list+1));
		j=start;
		}
	 to->toCells(j,4,SPList->operator [](i)->Get_format());//1=4
	 to->toCells(j,5,SPList->operator [](i)->Get_zona());
	 to->toCells(j,7,SPList->operator [](i)->Get_pos());
	 to->toCells(j,8,SPList->operator [](i)->Get_Obd(true)); //обозначение
	 String name=SPList->operator [](i)->Get_Name();
	 int cnt=30;       //перенос
	 while (name.Length()>cnt)
		{
		int pos=cnt;
		while (name.operator [](pos)!=' '&&pos>1)
			{
			pos--;
			}
		if (pos==1)
			{
            pos=cnt;
			}
		to->toCells(j,12,name.SubString(1,pos));
		name.Delete(1,pos);
		j++;
		}
	 to->toCells(j,12,name);
	 to->toCells(j,17,SPList->operator [](i)->Get_kol());
	 String kod=(String)SPList->operator [](i)->Get_pp();
	 while (kod.Length()<2)
		{
		kod="0"+kod;
		}
	 to->toCells(j,18,kod);
	 to->toCells(j,19,SPList->operator [](i)->Get_prim());
	}
to->toCells(nl,11,Object->Get_Obd(true));
if (list==1)
	{
	to->toCells(35,11,Object->Get_Name());
	to->toCells(36,17,list);
	nl=37;
	}else
	{
	to->toCells(38,19,list);
	}
to->SetActiveSheet(to->GetFirstSheet());
to->Sheet_activate();
to->toCells(36,19,list);
to->Visible(true);
}
//управление исполнениями
void __fastcall TSPEditor::N13Click(TObject *Sender)
{
//управление
TIspList *wnd=new TIspList(this,DB,ISP);
wnd->ShowModal();
delete wnd;
}
void __fastcall TSPEditor::N12Click(TObject *Sender)
{
//переменная часть
//получить список исполнений для переменной части
TIspList *wnd=new TIspList(this,DB,ISP,false);
wnd->ShowModal();
int mr=wnd->ModalResult;
delete wnd;
if (mr=mrOk)
	{
	//сбор выделеного массива строк
	vector <int> ids;
	ids.clear();
	for (int row=SG1->Selection.Top; row<=SG1->Selection.Bottom; row++)
		{
		if (SG1->Cells[10][row]!=""&&SG1->Cells[11][row]!="1")
			{
			ids.push_back(SG1->Cells[10][row].ToInt());
			}
		}
	//копирование строк и вставка в массив
	for (int i=0; i <ISP.size(); i++)
		{
		if (ISP[i].selected)
			{
			for (int j=0; j<ids.size(); j++)
				{ //создание строк
				if (SPList->operator [](ids[j])->CanUse()&&!SPList->operator [](ids[j])->Get_ppp())
					{
					SpRow *t=new SpRow(
					DB,LUser,
					SPList->operator [](ids[j])->Get_ID(),ISP[i].id,SPList->operator [](ids[j])->Get_SpRazd(),SPList->operator [](ids[j])->Get_pp(),
					1,SPList->operator [](ids[j])->Get_ei(),SPList->operator [](ids[j])->Get_state(),SPList->operator [](ids[j])->Get_UserID(),
					SPList->operator [](ids[j])->Get_Obd(false),ISP[i].Get_Obd(false),
					SPList->operator [](ids[j])->Get_Name(),SPList->operator [](ids[j])->Get_SpRazdName(),
					SPList->operator [](ids[j])->Get_format(),SPList->operator [](ids[j])->Get_pos(),SPList->operator [](ids[j])->Get_prim(),
					SPList->operator [](ids[j])->Get_zona(),SPList->operator [](ids[j])->Get_ppName(),SPList->operator [](ids[j])->Get_eiName(),
					SPList->operator [](ids[j])->Get_User(),SPList->operator [](ids[j])->Get_CondName(),SPList->operator [](ids[j])->Get_DetCreator(),
					SPList->operator [](ids[j])->Get_DetUpdater(),UserName,
					UserName,
					"ins",SPList->operator [](ids[j])->Get_act_d(),
					SPList->operator [](ids[j])->Get_kol(),
					SPList->operator [](ids[j])->Get_Arhive(),
					SPList->operator [](ids[j])->Get_CanChild(),SPList->operator [](ids[j])->Get_Accept(),
					false,
					SPList->operator [](ids[j])->Get_DetCreated(),SPList->operator [](ids[j])->Get_DetUpdated(),
					Date(),Date());
					SPList->push_back(t);
					}
				}
			}
		}
	//удаление исходных строк
	for (int i = 0; i<ids.size(); i++)
		{
		if (SPList->operator [](ids[i])->CanUse())
			{
			SPList->operator [](ids[i])->Delete();
			}
		}
	SPList=SortMass(SPList);
	ShowSP();
	}
}
void __fastcall TSPEditor::N11Click(TObject *Sender)
{
//сбор выделеного массива строк
vector <int> ids;
ids.clear();
for (int row=SG1->Selection.Top; row<=SG1->Selection.Bottom; row++)
	{
	if (SG1->Cells[10][row]!=""&&SG1->Cells[11][row]!="1")
		{
		ids.push_back(SG1->Cells[10][row].ToInt());
		}
	}
//копирование строк и вставка в массив
bool find=false;
vector <IspData >::iterator j=ISP.begin();
while (j <ISP.end()&&!find)
	{//поиск идентификатора для обозначения
	if (j->main_isp)
		{
		find=true;
		}else
		{
		j++;
		}
	}
for (int i=0; i<ids.size(); i++)
	{//просмотр списка выделенного  //создание строк
	if (SPList->operator [](ids[i])->Get_ppp()&&SPList->operator [](ids[i])->CanUse())
		{
		SpRow *t=new SpRow(
		DB,LUser,
		SPList->operator [](ids[i])->Get_ID(),j->id,SPList->operator [](ids[i])->Get_SpRazd(),SPList->operator [](ids[i])->Get_pp(),
		0,SPList->operator [](ids[i])->Get_ei(),SPList->operator [](ids[i])->Get_state(),SPList->operator [](ids[i])->Get_UserID(),
		SPList->operator [](ids[i])->Get_Obd(false),j->Get_Obd(false),
		SPList->operator [](ids[i])->Get_Name(),SPList->operator [](ids[i])->Get_SpRazdName(),
		SPList->operator [](ids[i])->Get_format(),SPList->operator [](ids[i])->Get_pos(),SPList->operator [](ids[i])->Get_prim(),
		SPList->operator [](ids[i])->Get_zona(),SPList->operator [](ids[i])->Get_ppName(),SPList->operator [](ids[i])->Get_eiName(),
		SPList->operator [](ids[i])->Get_User(),SPList->operator [](ids[i])->Get_CondName(),SPList->operator [](ids[i])->Get_DetCreator(),
		SPList->operator [](ids[i])->Get_DetUpdater(),UserName,
		UserName,
		"ins",SPList->operator [](ids[i])->Get_act_d(),
		SPList->operator [](ids[i])->Get_kol(),
		SPList->operator [](ids[i])->Get_Arhive(),
		SPList->operator [](ids[i])->Get_CanChild(),SPList->operator [](ids[i])->Get_Accept(),
		false,
		SPList->operator [](ids[i])->Get_DetCreated(),SPList->operator [](ids[i])->Get_DetUpdated(),
		Date(),Date());
		SPList->push_back(t);
		}
	}

//удаление исходных строк
for (int i = 0; i<ids.size(); i++)
	{
	for (int j=0; j<SPList->size(); j++)
		{
		if (
			SPList->operator [](j)->Get_Obd(false)==SPList->operator [](ids[i])->Get_Obd(false)&&
			SPList->operator [](j)->Get_ppp()&&
			SPList->operator [](j)->CanUse()
			)
			{
			SPList->operator [](j)->Delete();
			}
		}
	}
SPList=SortMass(SPList);
ShowSP();
//поиск всех совпадений для каждой детали
//редактирование деталей в переменной части если количество станет <=0 то удалить строчку
}
