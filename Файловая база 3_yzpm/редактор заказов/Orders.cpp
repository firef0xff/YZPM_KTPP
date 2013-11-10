//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Orders.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

__fastcall 	TOrders_editor::TOrders_editor(TComponent* Owner,TWinControl *_p, int &_LUser,cSQL *db,IconsData *_IcoData,int **_selected):
	TFrame(Owner),LUser(_LUser),selected(_selected)
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

	if (Parent->ClassNameIs("TTabSheet"))
	{
		((TTabSheet*)Parent)->Caption="Заказы     ";
	}

	OrderEdit=false;
	OrderView=false;

	String sql="call administration.Get_Rights('"+String(LUser)+"')";
	TADOQuery *rez=DB->SendSQL(sql);
	if(rez&&rez->RecordCount)
	{
		for (rez->First(); !rez->Eof; rez->Next())
		{
			const String val=rez->FieldByName("progname")->Value;
			if (val=="OrderEdit")
			{
				OrderEdit=true;
			}
			if (val=="OrderView")
			{
				OrderView=true;
			}
		}
	}
	delete rez;
	N1->Enabled=OrderEdit;
	N2->Enabled=OrderEdit;
	N3->Enabled=OrderEdit;
	N4->Enabled=OrderEdit;

	Panel3->Enabled=OrderView;
	Panel8->Enabled=OrderView;

	//init

	ZakazList->Cells[1][0]="№ заказа";
	ZakazList->Cells[2][0]="Описание";
	AutoWidthSG(ZakazList);
	Detalise->Cells[1][0]="Кол-во";
	Detalise->Cells[2][0]="Обозначение";
	Detalise->Cells[3][0]="Наименование";
	AutoWidthSG(Detalise);
}
__fastcall	TOrders_editor::~TOrders_editor(void)
{
count--;
if (count==0)
	{
	DB=0;
	IcoData=0;
	}
}

void __fastcall TOrders_editor::FindClick(TObject *Sender)
{
	SGClear(ZakazList,1);
	String sql="Call market.getZakazes('"+SeartchStr->Text+"',"+String(FindType->ItemIndex)+","+String(E2->Text.ToInt()*E3->Text.ToInt()-E3->Text.ToInt())+","+E3->Text+")";
	TADOQuery *rez=DB->SendSQL(sql);
	if (rez&&rez->RecordCount)
	{
		for (rez->First(); !rez->Eof; rez->Next())
		{
			int row=ZakazList->RowCount-1;
			ZakazList->Cells[1][row]=rez->FieldByName("zakaz")->Value;
			ZakazList->Cells[2][row]=rez->FieldByName("description")->Value;
			ZakazList->Cells[3][row]=rez->FieldByName("zakaz_id")->Value;
			ZakazList->RowCount++;
		}
		if (ZakazList->RowCount>2) 
		{
			--ZakazList->RowCount;
		}
		AutoWidthSG(ZakazList);
	}
	delete rez;
	bool can_select;
	ZakazListSelectCell(ZakazList,ZakazList->Col,ZakazList->Row,can_select);
}
void __fastcall TOrders_editor::ZakazListSelectCell(TObject *Sender, int ACol, int ARow,
          bool &CanSelect)
{
	SGClear(Detalise,2);
	String zakaz_id=ZakazList->Cells[3][ARow];
	
	if (zakaz_id=="") 
	{
		return ;    
	}
	String sql="Call market.getZakazContent("+ZakazList->Cells[3][ARow]+")";
	TADOQuery *rez=DB->SendSQL(sql);
	if (rez&&rez->RecordCount)
	{
		for (rez->First(); !rez->Eof; rez->Next())
		{
			int row=Detalise->RowCount-1;
			Detalise->Cells[1][row]=rez->FieldByName("kol")->Value;
			Detalise->Cells[2][row]=VinToGost(rez->FieldByName("obd")->Value);
			Detalise->Cells[3][row]=rez->FieldByName("namd")->Value;
			Detalise->Cells[4][row]=rez->FieldByName("zakaz_id")->Value;
			Detalise->Cells[5][row]=rez->FieldByName("id")->Value;
			Detalise->RowCount++;
		}
		if (Detalise->RowCount>2) 
		{
			--Detalise->RowCount;    
		}
		AutoWidthSG(Detalise);
	}
	delete rez;	
}
//---------------------------------------------------------------------------

void __fastcall TOrders_editor::pageClick(TObject *Sender)
{
	if (!Sender) 
	{
		return;	
	}
	TSpeedButton *btn=(TSpeedButton *)Sender;
	E2->Text=String(E2->Text.ToIntDef(1)+btn->Tag);
	Find->Click();
}
void __fastcall TOrders_editor::E2Change(TObject *Sender)
{
	if (E2->Text=="0") 
	{
		E2->Text="1";	
	}	
}
void __fastcall TOrders_editor::EnterPress(TObject *Sender, wchar_t &Key)
{
	if (Key==13) 
	{
		Find->Click();		
	}
}
//---------------------------------------------------------------------------

void __fastcall TOrders_editor::N1Click(TObject *Sender)
{
// добавить	
	TZakaz_set *wnd=new TZakaz_set(this);
	if (wnd->ShowModal()==mrOk)
	{
		DB->SendCommand("Call market.setZakaz('"+wnd->Zakaz->Text+"','"+wnd->Description->Text+"')");
		SeartchStr->Text=wnd->Zakaz->Text;
		FindType->ItemIndex=0;
		Find->Click();
	}
	delete wnd;
}
void __fastcall TOrders_editor::N5Click(TObject *Sender)
{
// редактировать
	TZakaz_set *wnd=new TZakaz_set(this);	
	wnd->Zakaz->Text=ZakazList->Cells[1][ZakazList->Row];
	wnd->Description->Text=ZakazList->Cells[2][ZakazList->Row];
	wnd->Zakaz->Enabled=false;
	if (wnd->ShowModal()==mrOk)
	{
		DB->SendCommand("Call market.setZakaz('"+wnd->Zakaz->Text+"','"+wnd->Description->Text+"')");
		Find->Click();
	}	
	delete wnd;
}
void __fastcall TOrders_editor::N2Click(TObject *Sender)
{
// удалить	
	if (MessageBox(Handle,_T("Удалить выделенные заказы?"),_T("Внимание!"),MB_ICONWARNING|MB_YESNO)==6  ) 
	{
		for (int row = ZakazList->Selection.Top; row <=ZakazList->Selection.Bottom; ++row) 
		{
			String zakaz_id=ZakazList->Cells[3][row];
			if (zakaz_id=="") 
			{
				continue ;    
			}
			DB->SendCommand("Call market.delZakaz("+zakaz_id+")");			
		}
		Find->Click();	
	}
}

void __fastcall TOrders_editor::N3Click(TObject *Sender)
{
// добавить
	String zakaz_id=ZakazList->Cells[3][ZakazList->Row];
	if (zakaz_id=="") 
	{
		return;
    }
			
	TZakazContent_set *wnd=new TZakazContent_set(this);	
	if (selected&&*selected&&**selected) 
	{
		wnd->Obd->Text=Obd(DB,*(*selected+1)).Get_Obd(true);    
	}
	wnd->Kol->Text="1";

	if (wnd->ShowModal()==mrOk) 
	{
		Obd obd(DB,wnd->Obd->Text.Trim());
		
		if (obd.Get_ID()>0)
		{	
			DB->SendCommand("Call market.setZakazContent("+zakaz_id+","+String(obd.Get_ID())+","+wnd->Kol->Text+")");		
		}
		else
		{
        	ShowMessage("Изделие не найдено.");
		}
	}
	delete wnd;
	bool can_select;
	ZakazListSelectCell(ZakazList,ZakazList->Col,ZakazList->Row,can_select);
}
void __fastcall TOrders_editor::N6Click(TObject *Sender)
{
// редактировать
	String zakaz_id=Detalise->Cells[4][Detalise->Row];
	Obd obd(DB,String(Detalise->Cells[5][Detalise->Row]).Trim().ToIntDef(0));
	if (!obd.Get_ID()>0||zakaz_id=="") 
	{
		return;	
	}
	TZakazContent_set *wnd=new TZakazContent_set(this);	
	wnd->Obd->Text=obd.Get_Obd(true);    
	wnd->Kol->Text=Detalise->Cells[1][Detalise->Row];;
    wnd->Obd->Enabled=false;
	if (wnd->ShowModal()==mrOk) 
	{
		DB->SendCommand("Call market.setZakazContent("+zakaz_id+","+String(obd.Get_ID())+","+wnd->Kol->Text+")");		
	}
	delete wnd;
	bool can_select;
	ZakazListSelectCell(ZakazList,ZakazList->Col,ZakazList->Row,can_select);	
}
void __fastcall TOrders_editor::N4Click(TObject *Sender)
{
	if (MessageBox(Handle,_T("Удалить выделенные изделия из заказа?"),_T("Внимание!"),MB_ICONWARNING|MB_YESNO)==6  ) 
	{
		for (int row = Detalise->Selection.Top; row <=Detalise->Selection.Bottom; ++row) 
		{
			String zakaz_id=Detalise->Cells[4][row];
			String id=Detalise->Cells[5][row];
	
			if (zakaz_id==""||id=="") 
			{
				continue;    
			}
			DB->SendCommand("Call market.delZakazContent("+zakaz_id+","+id+")");
		}
		bool can_select;
		ZakazListSelectCell(ZakazList,ZakazList->Col,ZakazList->Row,can_select);													
	}
}

