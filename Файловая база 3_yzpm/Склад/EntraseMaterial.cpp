//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "EntraseMaterial.h"
#include "Agrements_select.h"
#include <ctype.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TwndEntarseMaterial *wndEntarseMaterial;
//--конструкторы
__fastcall 	TwndEntarseMaterial::TwndEntarseMaterial(TComponent* Owner)
	: TForm(Owner),LUser(25)
{
	DB=new cSQL(ADC);
	init();
}
__fastcall  TwndEntarseMaterial::TwndEntarseMaterial(TComponent* Owner,const int &_LUser,cSQL *db): TForm(Owner),LUser(_LUser),DB(db)
{
	init();
}
__fastcall  TwndEntarseMaterial::~TwndEntarseMaterial()
{
	if (ekz)
	{
    	delete ekz;
	}
}
//алгоритмы
void 		TwndEntarseMaterial::init 		(void)
{
	//сетка
	SGClear(sgGeometry,0);
	sgGeometry->Cells[1][0]=L"Тип контура";
	sgGeometry->Cells[2][0]=L"Сторона а,мм";
	sgGeometry->Cells[3][0]=L"Сторона b,мм";
	sgGeometry->Cells[4][0]=L"Высота h,мм";
	sgGeometry->Cells[0][sgGeometry->RowCount-1]=L"*";
	AutoWidthSG(sgGeometry);
	//комбо бокс
	cbGeometry->Items->Clear();
	TADOQuery *rez=DB->SendSQL("Call sklad.Get_Conturs");
	if (rez&&rez->RecordCount)
	{
		for (rez->First(); !rez->Eof; rez->Next())
		{
			cbGeometry->Items->AddObject(rez->FieldByName("Countur_name")->Value,nullptr);
		}
	}
	delete rez;
	//единици измрения
	cbEi->Items->Clear();
	rez=DB->SendSQL("Call catalogs.Get_ei_list('2')");
	if (rez&&rez->RecordCount)
	{
		for (rez->First(); !rez->Eof; rez->Next())
		{
			cbEi->Items->AddObject(rez->Fields->operator [](1)->Value.operator UnicodeString(),(TObject *)rez->Fields->operator [](0)->Value.operator int());
		}
	}
	delete rez;
	//обозначение и первичные данные
	ekz=new Obd(DB);
}
void 		TwndEntarseMaterial::Check_Obe	(void)
{
	ekz->SetObd(leObe->Text);
	if (ekz->CanUse())
	{
		leName->Text=ekz->Get_Name();
		leObe->Text=ekz->Get_Obd(true);
		//управление елементами интерфейса в зависимости от типа элемента
	}else
	{//сброс на исходные
		leName->Text="";
	}
}
void 		TwndEntarseMaterial::Del_Row	(TStringGrid *sg, int Row)
{
	if (sg)
	{
		if (sg->RowCount>2)
		{//удаление строки
			if (sg->RowCount-1>Row) //проверка нахождения строки в сетке
			{
				//копирование данных из нижестоящих строк
				for (size_t i=Row; i<sg->RowCount-1; i++)
				{
					for (size_t j=0; j<sg->ColCount; j++)
					{
						sg->Cells[j][i]=sg->Cells[j][i+1];
					}
				}
				sg->RowCount--;
				for (size_t j=0; j<sg->ColCount; j++)
				{
					sg->Cells[j][sg->RowCount-1]="";
				}
			}
		}else
		{//чистка строки
			SGClear(sg,0);
		}
		sg->Cells[0][sg->RowCount-1]="*";
	}
}

//события
// cbGeometry  активация и дезактивация
void __fastcall	TwndEntarseMaterial::sgGeometryDblClick(TObject *Sender)
{
	if (Sender==sgGeometry)
	{//блокиратор для вызова другими экземплярами
		TStringGrid *sg=sgGeometry;
		if (sg->Col==1)
		{
			TRect rect=sg->CellRect(sg->Col,sg->Row);
			cbGeometry->Top=sg->Top+rect.Top;
			cbGeometry->Left=sg->Left+rect.Left;
			cbGeometry->Width=rect.Width();
			cbGeometry->Height=rect.Height();
			cbGeometry->ItemIndex=cbGeometry->Items->IndexOf(sg->Cells[sg->Col][sg->Row]);
			cbGeometry->Show();
			cbGeometry->SetFocus();
		}
	}
}
void __fastcall TwndEntarseMaterial::cbGeometryExit(TObject *Sender)
{
	TComboBox *cb=dynamic_cast<TComboBox *>(Sender);
	if (cb)
	{
		cb->Hide();
	}
}
void __fastcall TwndEntarseMaterial::cbGeometryClick(TObject *Sender)
{
	if (Sender==cbGeometry)
	{//блокиратор для вызова другими экземплярами
		sgGeometry->Cells[sgGeometry->Col][sgGeometry->Row]=cbGeometry->Text;
		AutoWidthSG(sgGeometry);
		sgGeometry->SetFocus();
	}
}
void __fastcall TwndEntarseMaterial::sgGeometrySelectCell(TObject *Sender, int ACol,
          int ARow, bool &CanSelect)
{
	if (Sender==sgGeometry)
	{//блокиратор для вызова другими экземплярами
		TStringGrid *sg=sgGeometry;
		//вкл/выкл режима ввода в сетку
		if (ACol==1)
		{
			sg->Options>>goEditing;
		}else
		{
			sg->Options<<goEditing;
		}
		//управление добавлением удалением строк
		int Row=sg->Row;//текущая строка
		if (Row!=ARow)
		{
			//проверка на отсутствие параметров
			if (sg->Cells[2][Row]==""||sg->Cells[3][Row]==""||sg->Cells[4][Row]=="")
			{
				Del_Row(sg,Row);
			}
		}
	}
}
//управление вводом в сетку
void __fastcall TwndEntarseMaterial::sgGeometrySetEditText(TObject *Sender, int ACol,
		  int ARow, const UnicodeString Value)
{
	//обработка ввода текста
	if (Sender==sgGeometry)//блокиратор для вызова другими экземплярами
	{
		static String val="";
		if (val!=Value) //разрыв цикла вызовов событий
		{
			val=Value;
			TStringGrid *sg=sgGeometry;
			String val="";
			/*проанализировать строку на предмет букв и разделителя если нет то убрать символ*/
			bool  OneDecimall=true;
			for (size_t i=1; i<=Value.Length(); i++)
			{
				if (isdigit(Value[i])||(Value[i]==DecimalSeparator&&OneDecimall))
				{
					if (Value[i]==DecimalSeparator)
					{
						OneDecimall=false;
					}
					val+=Value[i];
				}
			}
			sg->Cells[ACol][ARow]=val;
			sg->EditorMode=true;
			if (ARow==sg->RowCount-1)
			{
				sg->Cells[0][ARow]="";
				sg->RowCount++;
				sg->Cells[0][sg->RowCount-1]="*";
			}
		}

	}
}
//отображение информации по экземпляру
void __fastcall TwndEntarseMaterial::leObeKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if (Key==13)
	{
    	Check_Obe();
	}
}
//выбор контрагента
void __fastcall TwndEntarseMaterial::btContrAgentClick(TObject *Sender)
{
	TContragents	*wnd=new TContragents(this,LUser,DB);
	if (wnd->ShowModal()==mrOk)
	{
		String ka_name;
		wnd->Get_id(ka_id,ka_name);
		leContrAgent->Text=ka_name;
	}
	delete wnd;
}
