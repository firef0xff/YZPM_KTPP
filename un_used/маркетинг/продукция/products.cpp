// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "products.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

__fastcall Tprod::Tprod(TComponent *Owner, TWinControl *_p, const int &_LUser,
	cSQL *db):TFrame(Owner), LUser(_LUser)
{
	if(count==0)
	{
		DB=db;
	}
	count++ ;
	// ������������
	Align=alClient;
	Parent=_p;
	Name=Name+String(count);
	mode="";
	order_by="order by dog_Date desc";
	init();
	Comp_Activating();
	SGClear(SG, 0);
	SGClear(SG2, 22);
	SGClear(colgrid, 0);
	colgrid->Cells[0][0]=L"��������";
	colgrid->Cells[1][0]=L"�������";
	colgrid->Cells[2][0]=L"������������";
	colgrid->Cells[3][0]=L"�����";
	colgrid->Cells[4][0]=L"�����";
	colgrid->Cells[5][0]=L"���������";
	colgrid->Cells[6][0]=L"���������";
	colgrid->Cells[7][0]=L"��������";
	SG->Cells[0][0]="                  ";
	SG->Cells[1][0]="���";
	SG->Cells[2][0]="�";
	SG->Cells[3][0]="����";
	SG->Cells[4][0]="�����";
	SG->Cells[5][0]="�";
	SG->Cells[6][0]="���� ��.";
	SG->Cells[7][0]="���� ����.";
	SG->Cells[8][0]="������";
	SG->Cells[9][0]="             ";
	SG->Cells[10][0]="� ���  ";
	SG->Cells[11][0]="                     ";
	SG->Cells[12][0]="� ���           ";
	SG->Cells[13][0]="                  ";
	SG2->Cells[0][0]="�����";
	SG2->Cells[1][0]="������������";
	SG2->Cells[2][0]="�����������";
	SG2->Cells[3][0]="����������� ���";
	SG2->Cells[4][0]="��������";
	SG2->Cells[5][0]="���-��";
	SG2->Cells[6][0]="����";
	SG2->Cells[7][0]="�����";
	SG2->Cells[8][0]="����� � ���";
	SG2->Cells[9][0]="����������";
	SG2->Cells[10][0]="���-��, ��";
	SG2->Cells[11][0]="���-��, ��";
	SG2->Cells[12][0]="���-��, ��";
	SG2->Cells[13][0]="������-���";
	SG2->Cells[14][0]="���� �������";

	AutoWidthSG(SG);
	AutoWidthSG(SG2);
	ColumnResize();
	Find();
}

void Tprod::init(void)
{
	// �������� ���� �������
	TADOQuery *rez=
		DB->SendSQL
		("select a.prod_Edit,b.login from administration.privileges a join administration.logins b on a.Groupid=b.levelacss where b.LogID='"+
		String(LUser)+"'");
	if(rez&&rez->RecordCount)
	{
		prod_Edit=rez->FieldByName("prod_Edit")->Value.operator bool();
		UName=rez->FieldByName("login")->Value;
	}
	else
	{
		prod_Edit=false;
	}
	delete rez;

	Add->Enabled=prod_Edit;
	Edit->Enabled=prod_Edit;
	Del->Enabled=prod_Edit;

	// �������� ������ � �����
	// ������ �����
	valute->Items->Clear();
	rez=DB->SendSQL
		("select id,name from market.valute_list order by name desc");
	if(rez&&rez->RecordCount)
	{
		for(rez->First(); !rez->Eof; rez->Next())
		{
			valute->Items->AddObject(rez->FieldByName("name")->Value,
				(TObject *)rez->FieldByName("id")->Value.operator int());
		}
	}
	delete rez;
	valute->ItemIndex= -1;
	// ������ ���
	nds->Items->Clear();
	rez=DB->SendSQL("select nds from market.nds_list order by nds");
	if(rez&&rez->RecordCount)
	{
		for(rez->First(); !rez->Eof; rez->Next())
		{
			nds->Items->AddObject(rez->FieldByName("nds")->Value, 0);
		}
	}
	delete rez;
	nds->ItemIndex= -1;
	// ��������� �������������
	podrids="";
	rez=DB->SendSQL("Call market.Get_podr_list('"+String(LUser)+"')");
	if(rez&&rez->RecordCount)
	{
		for(rez->First(); !rez->Eof; rez->Next())
		{
			podrids=podrids+rez->FieldByName("id")
				->Value.operator UnicodeString()+",";
		}
	}
	delete rez;
	if(podrids!="")
	{
		podrids.Delete(podrids.Length(), 1);
	}
}

void Tprod::Comp_Activating(void)
{
	if(mode=="")
	{
		Accept_btn->Enabled=false;
		dogovor->Enabled=false;
		gr_ca_select->Enabled=false;
		lz_ca_select->Enabled=false;
		pl_ca_select->Enabled=false;
		valute->Enabled=false;
		curs->Enabled=false;
		nds->Enabled=false;
		sp_prim->ReadOnly=true;
	}
	else
	{
		Accept_btn->Enabled=true;
		dogovor->Enabled=true;
		gr_ca_select->Enabled=true;
		lz_ca_select->Enabled=true;
		pl_ca_select->Enabled=true;
		valute->Enabled=true;
		curs->Enabled=true;
		nds->Enabled=true;
		sp_prim->ReadOnly=false;
	}
}

void Tprod::ColumnResize(void)
{
	colgrid->ColWidths[0]=SG->ColWidths[0];
	colgrid->ColWidths[1]=SG->ColWidths[1]+SG->ColWidths[2]+SG->ColWidths[3]+2;
	colgrid->ColWidths[2]=SG->ColWidths[4]+SG->ColWidths[5]+SG->ColWidths[6]+
		SG->ColWidths[7]+SG->ColWidths[8]+4;
	colgrid->ColWidths[3]=SG->ColWidths[9];
	colgrid->ColWidths[4]=SG->ColWidths[10];
	colgrid->ColWidths[5]=SG->ColWidths[11];
	colgrid->ColWidths[6]=SG->ColWidths[12];
	colgrid->ColWidths[7]=SG->ColWidths[13];
}

void __fastcall Tprod::SGMouseUp(TObject *Sender, TMouseButton Button,
	TShiftState Shift, int X, int Y)
{
	ColumnResize();
}

void __fastcall Tprod::SearchClick(TObject *Sender)
{
	TSel_params_prod *wnd=new TSel_params_prod(this, LUser, DB);
	wnd->ShowModal();
	if(wnd->ModalResult==mrOk)
	{
		sortparams=wnd->Get_Where();
	}
	else
	{
		sortparams="";
	}
	if(E2->Text=="1")
	{
		Find();
	}
	else
	{
		E2->Text="1"; // ���������� onChange � ������ ������� � �������� Find
	}
}

void __fastcall Tprod::SortClearClick(TObject *Sender)
{
	sortparams="";
	if(E2->Text=="1")
	{
		Find();
	}
	else
	{
		E2->Text="1"; // ���������� onChange � ������ ������� � �������� Find
	}
}

void __fastcall Tprod::E3Change(TObject *Sender)
{
	if(E3->Text==""||E3->Text=="0")
	{
		E3->Text="1";
	}
	if(E2->Text!="1")
	{
		E2->Text="1";
	}
	else
	{
		Find();
	}
}

void __fastcall Tprod::E2Change(TObject *Sender)
{
	if(E2->Text==""||E2->Text=="0")
	{
		E2->Text="1";
	}
	Find();
}

void __fastcall Tprod::nextClick(TObject *Sender)
{
	TSpeedButton *bt=(TSpeedButton *)Sender;
	switch(bt->Tag)
	{
	case 1:
		{
			E2->Text=String(E2->Text.ToInt()+1);
			break;
		}
	case -1:
		{
			if(E2->Text.ToInt()>1)
			{
				E2->Text=String(E2->Text.ToInt()-1);
			}
			break;
		}
	default:
		return;
	}
}

void __fastcall Tprod::sp_E3Change(TObject *Sender)
{
	if(sp_E3->Text==""||sp_E3->Text=="0")
	{
		sp_E3->Text="1";
	}
	if(sp_E2->Text!="1")
	{
		sp_E2->Text="1";
	}
	else
	{
		sp_Find();
	}
}

void __fastcall Tprod::sp_E2Change(TObject *Sender)
{
	if(sp_E2->Text==""||sp_E2->Text=="0")
	{
		sp_E2->Text="1";
	}
	sp_Find();
}

void __fastcall Tprod::sp_nextClick(TObject *Sender)
{
	TSpeedButton *bt=(TSpeedButton *)Sender;
	switch(bt->Tag)
	{
	case 1:
		{
			sp_E2->Text=String(sp_E2->Text.ToInt()+1);
			break;
		}
	case -1:
		{
			if(sp_E2->Text.ToInt()>1)
			{
				sp_E2->Text=String(sp_E2->Text.ToInt()-1);
			}
			break;
		}
	default:
		return;
	}
}

void Tprod::Find(void)
{
	String sql="";
	if(podrids!="")
	{
		sql="Call market.Get_market_productions('"+podrids+"','"+sortparams+
			"','"+order_by+"','"+String(E2->Text.ToInt()*E3->Text.ToInt()-
			E3->Text.ToInt())+"','"+E3->Text+"')";
		data=DB->SendSQL(sql);
		ShowData();
		// ShowRowData(SG->Selection.Top);
	}
}

void Tprod::sp_Find(void)
{
	String sql="";
	if(podrids!="")
	{
		sql="Call market.Get_sp_content('"+(String)sp_id+"','"+
			String(sp_E2->Text.ToInt()*sp_E3->Text.ToInt()-sp_E3->Text.ToInt())+
			"','"+sp_E3->Text+"')";
		sp_data=DB->SendSQL(sql);
		Show_sp_Data();
		// ShowRowData(SG->Selection.Top);
	}
}

void Tprod::ShowData(void)
{
	SGClear(SG, 0);
	if(data&&data->RecordCount)
	{
		SG->RowCount=data->RecordCount+1;
		for(data->First(); !data->Eof; data->Next())
		{
			SG->Cells[0][data->RecNo]=data->FieldByName("ca_name")->Value;
			SG->Cells[1][data->RecNo]=data->FieldByName("dog_type")->Value;
			SG->Cells[2][data->RecNo]=data->FieldByName("dog_number")->Value;
			if(!data->FieldByName("dog_Date")->Value.IsNull())
			{
				SG->Cells[3][data->RecNo]=data->FieldByName("dog_Date")->Value;
			}
			if(data->FieldByName("cancel")->Value.operator bool())
			{
				SG->Cells[4][data->RecNo]="�����";
			}
			SG->Cells[5][data->RecNo]=data->FieldByName("sp_num")->Value;
			if(!data->FieldByName("sp_Date")->Value.IsNull())
			{
				SG->Cells[6][data->RecNo]=data->FieldByName("sp_Date")->Value;
			}
			if(!data->FieldByName("sp_Sign")->Value.IsNull())
			{
				SG->Cells[7][data->RecNo]=data->FieldByName("sp_Sign")->Value;
			}
			SG->Cells[8][data->RecNo]=data->FieldByName("sp_valute")->Value;
			if(!data->FieldByName("sp_sum")->Value.IsNull())
			{
				SG->Cells[9][data->RecNo]=data->FieldByName("sp_sum")->Value;
			}
			if(!data->FieldByName("sp_sum_nds")->Value.IsNull())
			{
				SG->Cells[10][data->RecNo]=
					data->FieldByName("sp_sum_nds")->Value;
			}
			if(!data->FieldByName("out_sum")->Value.IsNull())
			{
				SG->Cells[11][data->RecNo]=data->FieldByName("out_sum")->Value;
			}
			if(!data->FieldByName("ot_sum_nds")->Value.IsNull())
			{
				SG->Cells[12][data->RecNo]=
					data->FieldByName("ot_sum_nds")->Value;
			}
			if(!data->FieldByName("opl_sum")->Value.IsNull())
			{
				SG->Cells[13][data->RecNo]=data->FieldByName("opl_sum")->Value;
			}
		}
		AutoWidthSG(SG);
		ColumnResize();
	}
}

void Tprod::ShowRowData(int Row)
{
	if(data&&data->RecordCount&&Row>0&&mode=="")
	{
		data->RecNo=Row;

		sp_id=data->FieldByName("sp_id")->Value.operator __int64();
		// ������������� ������������
		dog_id=data->FieldByName("dog_id")->Value.operator __int64();
		// ������������� ��������
		gr_ca_id=data->FieldByName("gr_id")->Value.operator __int64();
		// ������������� ���������������
		lz_ca_id=data->FieldByName("lz_id")->Value.operator __int64();
		// ������������� ������ ����������
		pl_ca_id=data->FieldByName("pl_id")->Value.operator __int64();
		// ������������� �����������
		if(sp_E2->Text=="1")
		{
			sp_Find();
		}
		else
		{
			sp_E2->Text="1";
			// ���������� onChange � ������ ������� � �������� Find
		}
		// ���������� ������ �� �������� � ������������
		d_num->Text=data->FieldByName("dog_number")->Value;
		if(data->FieldByName("sp_Date")->Value.operator TDateTime().Val)
		{
			sp_CreateDate=data->FieldByName("sp_Date")
				->Value.operator TDateTime();
			sp_date->Text=sp_CreateDate.FormatString("dd.mm.yyyy");
		}
		else
		{
			sp_CreateDate=0;
			sp_date->Text=="";
		}
		if(!data->FieldByName("sp_Sign")->Value.IsNull()&&data->FieldByName
			("sp_Sign")->Value.operator TDateTime().Val)
		{
			sp_SignDate=data->FieldByName("sp_Sign")
				->Value.operator TDateTime();
			accept_date->Text=sp_SignDate.FormatString("dd.mm.yyyy");
		}
		else
		{
			sp_SignDate.Val=0;
			accept_date->Text=="";
		}
		d_type->Text=data->FieldByName("dog_type")->Value;
		if(!data->FieldByName("dog_Date")->Value.IsNull()&&data->FieldByName
			("dog_Date")->Value.operator TDateTime().Val)
		{
			d_date->Text=data->FieldByName("dog_Date")->Value.operator TDateTime
				().FormatString("dd.mm.yyyy");
		}
		else
		{
			d_date->Text=="";
		}
		ca_name->Text=data->FieldByName("ca_name")->Value;
		pl_ca_name->Text=data->FieldByName("pl_name")->Value;
		lz_ca_name->Text=data->FieldByName("lz_name")->Value;
		gr_ca_name->Text=data->FieldByName("gr_name")->Value;
		sp_prim->Text=data->FieldByName("sp_prim")->Value;
		if(!data->FieldByName("sp_sum")->Value.IsNull())
		{
			sp_sum->Text=data->FieldByName("sp_sum")->Value;
		}
		else
		{
			sp_sum->Text="";
		}
		if(!data->FieldByName("sp_sum_nds")->Value.IsNull())
		{
			sp_sum_nds->Text=data->FieldByName("sp_sum_nds")->Value;
		}
		else
		{
			sp_sum_nds->Text="";
		}
		sp_num->Text=data->FieldByName("sp_num")->Value;
		nds->ItemIndex=nds->Items->IndexOf(data->FieldByName("nds")->Value);
		valute->ItemIndex=
			valute->Items->IndexOf(data->FieldByName("sp_valute")->Value);
		valuteChange(0);
	}
	// ��������� ����������� � �����
}

void Tprod::Show_sp_Data(void)
{
	SGClear(SG2, 22);
	if(sp_data&&sp_data->RecordCount)
	{
		SG2->RowCount=sp_data->RecordCount+1;
		for(sp_data->First(); !sp_data->Eof; sp_data->Next())
		{
			SG2->Cells[0][sp_data->RecNo]=
				sp_data->FieldByName("zak_no")->Value; // "�����";
			SG2->Cells[1][sp_data->RecNo]=
				sp_data->FieldByName("name")->Value; // "������������";
			SG2->Cells[2][sp_data->RecNo]=sp_data->FieldByName("obi")->Value;
			// "�����������";
			SG2->Cells[3][sp_data->RecNo]=
				sp_data->FieldByName("obivin")->Value; // "����������� ���";
			SG2->Cells[4][sp_data->RecNo]=
				sp_data->FieldByName("supply")->Value; // "��������";
			SG2->Cells[5][sp_data->RecNo]=
				sp_data->FieldByName("z_kol")->Value; // "���-��";
			SG2->Cells[6][sp_data->RecNo]=
				sp_data->FieldByName("price")->Value; // "����";
			SG2->Cells[7][sp_data->RecNo]=
				sp_data->FieldByName("summ")->Value; // "�����";
			if(!sp_data->FieldByName("summ_nds")->Value.IsNull())
			{
				SG2->Cells[8][sp_data->RecNo]=
					sp_data->FieldByName("summ_nds")->Value; // "����� � ���";
			}
			SG2->Cells[9][sp_data->RecNo]=
				sp_data->FieldByName("prim")->Value; // "����������";
			if(!sp_data->FieldByName("s_kol")->Value.IsNull())
			{
				SG2->Cells[10][sp_data->RecNo]=
					sp_data->FieldByName("s_kol")->Value; // "���-��, ��";  //
			}
			if(!sp_data->FieldByName("ex_kol")->Value.IsNull())
			{
				SG2->Cells[11][sp_data->RecNo]=
					sp_data->FieldByName("ex_kol")->Value; // "���-��, ��";  //
			}
			if(!sp_data->FieldByName("ship_kol")->Value.IsNull())
			{
				SG2->Cells[12][sp_data->RecNo]=
					sp_data->FieldByName("ship_kol")->Value;
				// "���-��, ��";  //
			}
			if(sp_data->FieldByName("prime_cost")->Value.operator double())
			{
				SG2->Cells[13][sp_data->RecNo]=
					sp_data->FieldByName("prime_cost")->Value;
				// "������-���";  //
			}
			if(!sp_data->FieldByName("pc_date")->Value.IsNull()
				&&sp_data->FieldByName("pc_date")
				->Value.operator TDateTime().Val)
			{
				SG2->Cells[14][sp_data->RecNo]=
					sp_data->FieldByName("pc_date")->Value.operator TDateTime()
					.FormatString("dd.mm.yyyy"); // "���� �������";//
			}
			SG2->Cells[15][sp_data->RecNo]=sp_data->RecNo;
			SG2->Cells[16][sp_data->RecNo]=
				sp_data->FieldByName("id_content")->Value;
			SG2->Cells[17][sp_data->RecNo]=sp_data->FieldByName("sp_id")->Value;
			SG2->Cells[18][sp_data->RecNo]=sp_data->FieldByName("nds")->Value;
			if(!sp_data->FieldByName("ship_nds")->Value.IsNull())
			{
				SG2->Cells[19][sp_data->RecNo]=
					sp_data->FieldByName("ship_nds")->Value;
			}
			SG2->Cells[20][sp_data->RecNo]=sp_data->FieldByName("zkom")->Value;
			SG2->Cells[21][sp_data->RecNo]=sp_data->FieldByName("pos")->Value;
			SG2->Cells[22][sp_data->RecNo]=sp_data->FieldByName("ei_id")->Value;
			SG2->Cells[23][sp_data->RecNo]=sp_data->FieldByName("razd")->Value;
			if(!sp_data->FieldByName("calc_id")->Value.IsNull())
			{
				SG2->Cells[24][sp_data->RecNo]=
					sp_data->FieldByName("calc_id")->Value;
			}
			if(!sp_data->FieldByName("demand_id")->Value.IsNull())
			{
				SG2->Cells[25][sp_data->RecNo]=
					sp_data->FieldByName("demand_id")->Value;
			}
			if(!sp_data->FieldByName("ppo_vz")->Value.IsNull())
			{
				SG2->Cells[26][sp_data->RecNo]=
					sp_data->FieldByName("ppo_vz")->Value;
			}
			SG2->Cells[27][sp_data->RecNo]=
				sp_data->FieldByName("ppo_resurs")->Value;
			SG2->Cells[28][sp_data->RecNo]=
				sp_data->FieldByName("ppo_price_resurs")->Value;
			if(!sp_data->FieldByName("ppo_cex")->Value.IsNull())
			{
				SG2->Cells[29][sp_data->RecNo]=
					sp_data->FieldByName("ppo_cex")->Value;
			}
			SG2->Cells[30][sp_data->RecNo]=sp_data->FieldByName("ppf_r")->Value;
			SG2->Cells[31][sp_data->RecNo]=
				sp_data->FieldByName("ppf_size")->Value;
			if(!sp_data->FieldByName("ppf_vid")->Value.IsNull())
			{
				SG2->Cells[32][sp_data->RecNo]=
					sp_data->FieldByName("ppf_vid")->Value;
			}
			if(!sp_data->FieldByName("ppf_type_pf")->Value.IsNull())
			{
				SG2->Cells[33][sp_data->RecNo]=
					sp_data->FieldByName("ppf_type_pf")->Value;
			}
			SG2->Cells[34][sp_data->RecNo]=
				sp_data->FieldByName("ppf_isp")->Value;
			SG2->Cells[35][sp_data->RecNo]=
				sp_data->FieldByName("ppf_model")->Value;
			SG2->Cells[36][sp_data->RecNo]=
				sp_data->FieldByName("ppf_ves")->Value;
		}
		AutoWidthSG(SG2);
	}
}

void __fastcall Tprod::SGFixedCellClick(TObject *Sender, int ACol, int ARow)
{
	// ����������
	String field="";
	switch(ACol)
	{
	case 0:
		{
			field="ca_name";
			break;
		}
	case 1:
		{
			field="dog_type";
			break;
		}
	case 2:
		{
			field="dog_number";
			break;
		}
	case 3:
		{
			field="dog_Date";
			break;
		}
	case 4:
		{
			field="cansel";
			break;
		}
	case 5:
		{
			field="sp_num";
			break;
		}
	case 6:
		{
			field="sp_Date";
			break;
		}
	case 7:
		{
			field="sp_Sign";
			break;
		}
	case 8:
		{
			field="sp_valute";
			break;
		}
	default:
		return;
	}
	// ����������� ������� ����������
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
	// �������� ������� ��������� ������
	order_by.Delete(pos, field.Length()+order.Length()+2);
	// ������� ������ ���������
	order_by.Insert(kor+field+" "+order+",", 10);
	order_by=order_by.Trim();
	if(order_by[order_by.Length()]==',')
	{
		order_by.Delete(order_by.Length(), 1);
	}
	Find();
}

void __fastcall Tprod::SGSelectCell(TObject *Sender, int ACol, int ARow,
	bool &CanSelect)
{
	ShowRowData(ARow);
}

void __fastcall Tprod::SGDrawCell(TObject *Sender, int ACol, int ARow,
	TRect &Rect, TGridDrawState State)
{
	// ������� �����
	static int color=0X00E0FFFF;
	int bad_color=0x00DDDDFF;
	if(ARow==1)
	{
		color=0X00E0FFFF;
	}
	if( /* ACol&& */ ARow)
	{ // ����������
		if((ARow%2))
		{
			color=0X00E0FFFF;
		}
		else
		{
			color=0x00e0FFe0;
		}
		if(data&&data->RecordCount)
		{
			data->RecNo=ARow;
			if(data->FieldByName("ca_id")->Value.IsNull()==false
				/** &&data->FieldByName("ka_base")->Value.operator UnicodeString()=="1c" */
				)
			{
				SG->Canvas->Brush->Color=color;
			}
			else
			{
				SG->Canvas->Brush->Color=bad_color;
			}
		}
		else
		{
			SG->Canvas->Brush->Color=color;
		}
		SG->Font->Color=clBlack;
		SG->Canvas->FillRect(Rect);
		SG->Canvas->TextOutW(Rect.left+2, Rect.top+1, SG->Cells[ACol][ARow]);
	}
	// ���������� ����
	if(ACol>=SG->Selection.Left&&ACol<=SG->Selection.Right&&ARow>=
		SG->Selection.Top&&ARow<=SG->Selection.Bottom) // ���������
	{
		SG->Canvas->Brush->Color=0x00FFE0E0; // clMenu;
		SG->Canvas->FillRect(Rect);
		SG->Font->Color=clBlack;
		SG->Canvas->Font->Color=clBlack;
		SG->Canvas->TextOutW(Rect.left+2, Rect.top+1, SG->Cells[ACol][ARow]);
	}
}

void __fastcall Tprod::SG2DrawCell(TObject *Sender, int ACol, int ARow,
	TRect &Rect, TGridDrawState State)
{
	// ������� �����
	static int color=0X00E0FFFF;
	int bad_color=0x00DDDDFF;
	if(ARow==1)
	{
		color=0X00E0FFFF;
	}
	if( /* ACol&& */ ARow)
	{ // ����������
		if((ARow%2))
		{
			color=0X00E0FFFF;
		}
		else
		{
			color=0x00e0FFe0;
		}
		SG2->Canvas->Brush->Color=color;
		SG2->Font->Color=clBlack;
		SG2->Canvas->FillRect(Rect);
		SG2->Canvas->TextOutW(Rect.left+2, Rect.top+1, SG2->Cells[ACol][ARow]);
	}
	// ���������� ����
	if(ACol>=SG2->Selection.Left&&ACol<=SG2->Selection.Right&&ARow>=
		SG2->Selection.Top&&ARow<=SG2->Selection.Bottom) // ���������
	{
		SG2->Canvas->Brush->Color=0x00FFE0E0; // clMenu;
		SG2->Canvas->FillRect(Rect);
		SG2->Font->Color=clBlack;
		SG2->Canvas->Font->Color=clBlack;
		SG2->Canvas->TextOutW(Rect.left+2, Rect.top+1, SG2->Cells[ACol][ARow]);
	}
}

void __fastcall Tprod::splitClick(TObject *Sender)
{
	TButton *btn=(TButton *)Sender;
	if(btn)
	{
		if(btn->Tag)
		{
			Panel3->Height=258;
			btn->Tag=0;
		}
		else
		{
			Panel3->Height=10;
			btn->Tag=1;
		}
	}
}

void __fastcall Tprod::split_dClick(TObject *Sender)
{
	TButton *btn=(TButton *)Sender;
	if(btn)
	{
		if(btn->Tag)
		{
			Panel6->Height=177;
			btn->Tag=0;
		}
		else
		{
			Panel6->Height=57;
			btn->Tag=1;
		}
	}
}

void __fastcall Tprod::dogovorClick(TObject *Sender)
{
	if(mode=="")
	{
		return;
	}
	TAgreements_select *wnd=new TAgreements_select(this, LUser, DB);
	wnd->ShowModal();
	if(wnd->ModalResult==mrOk)
	{
		String _d_num="", _d_type="", _ca_name="", _d_date;

		wnd->Update_selected_dog(dog_id, _d_num, _d_date, _d_type, _ca_name);
		d_num->Text=_d_num;
		d_type->Text=_d_type;
		ca_name->Text=_ca_name;
		d_date->Text=_d_date;
	}
	delete wnd;
}

void __fastcall Tprod::ca_selectClick(TObject *Sender)
{
	if(mode=="")
	{
		return;
	}
	TComponent *btn=(TButton *)Sender;
	TContragents *wnd=new TContragents(this, LUser, DB);
	wnd->ShowModal();
	if(wnd->ModalResult==mrOk)
	{
		String _ka_name;
		unsigned __int64 ka_id;
		wnd->Get_id(ka_id, _ka_name);
		switch(btn->Tag)
		{
		case 0:
			{
				pl_ca_name->Text=_ka_name;
				pl_ca_id=ka_id;
				break;
			} // ����������
		case 1:
			{
				gr_ca_name->Text=_ka_name;
				gr_ca_id=ka_id;
				break;
			} // ���������������
		case 2:
			{
				lz_ca_name->Text=_ka_name;
				lz_ca_id=ka_id;
				break;
			} // ������
		default:
			{
				delete wnd;
				return;
			}
		}
	}
	delete wnd;
}

void __fastcall Tprod::valuteChange(TObject *Sender)
{
	if(valute->ItemIndex>=0)
	{
		TADOQuery *rez=
			DB->SendSQL("call market.Get_valute_curs('"+
			String((int)valute->Items->Objects[valute->ItemIndex])+"')");
		if(rez&&rez->RecordCount)
		{
			curs->Text=rez->FieldByName("cours")->Value;
			if(rez->FieldByName("cours")->Value.operator int()!=1)
			{
				curs->ReadOnly=false;
			}
			else
			{
				curs->ReadOnly=true;
			}
		}
		else
		{
			curs->Text="";
		}
	}
}

// ������ ���������� �������� ������ ����
void __fastcall Tprod::AddClick(TObject *Sender)
{
	mode="ins";
	Comp_Activating();
	Cancel->Enabled=true;
	OK->Enabled=true;

	Add->Enabled=false;
	Del->Enabled=false;
	Edit->Enabled=false;

	// ������� ����������� ������������

	accept_date->Text="";
	ca_name->Text="";
	d_date->Text="";
	d_num->Text="";
	d_type->Text="";
	gr_ca_name->Text="";
	lz_ca_name->Text="";
	pl_ca_name->Text="";
	sp_prim->Text="";
	sp_sum->Text="";
	sp_sum_nds->Text="";
	sp_num->Text="";

	sp_id=0; // ������������� ������������
	dog_id=0; // ������������� ��������
	gr_ca_id=0; // ������������� ���������������
	lz_ca_id=0; // ������������� ������ ����������
	pl_ca_id=0; // ������������� �����������

	sp_CreateDate=Date(); // ���� �������� ������������
	sp_date->Text=sp_CreateDate.FormatString("dd.mm.yyyy");
	sp_SignDate=0; // ���� �������

	nds->ItemIndex=0;
	valute->ItemIndex=0;
	valuteChange(0);
	SGClear(SG2, 22);
	AutoWidthSG(SG2);

	split_d->Tag=1;
	split_d->Click();
	delete sp_data; // ������� ������ ������������ ����������� �����
	sp_data=0;
}

void __fastcall Tprod::EditClick(TObject *Sender)
{
	mode="upd";
	Comp_Activating();
	Cancel->Enabled=true;
	OK->Enabled=true;
	Add->Enabled=false;
	Del->Enabled=false;
	Edit->Enabled=false;
	/*
	 ������������� ����� �����������
	 */
	split_d->Tag=1;
	split_d->Click();
}

void __fastcall Tprod::DelClick(TObject *Sender)
{
	TADOQuery *rez=DB->SendSQL("Call market.sp_del('"+String(sp_id)+"')");
	if(rez&&rez->RecordCount)
	{
		MessageDlg(rez->FieldByName("msg")->Value, mtError,
			TMsgDlgButtons()<<mbOK, 0);
	}
	Find();
}

void __fastcall Tprod::OKClick(TObject *Sender)
{ /* �������� ������� ����������
	 �������� ������� ��������
	 � �������
	 */
	String msg="";
	if(!dog_id)
	{
		msg="�� ������ �������";
	}
	if(!(SG2->RowCount-1))
	{
		msg="������ ������������";
	}
	/* ���������� */
	if(msg=="")
	{
		String sql="", gr_ca_id_t, lz_ca_id_t, pl_ca_id_t, sign;
		if(gr_ca_id)
		{
			gr_ca_id_t=(String)gr_ca_id;
		}
		else
		{
			gr_ca_id_t="NULL";
		}
		if(lz_ca_id)
		{
			lz_ca_id_t=(String)lz_ca_id;
		}
		else
		{
			lz_ca_id_t="NULL";
		}
		if(lz_ca_id)
		{
			pl_ca_id_t=(String)lz_ca_id;
		}
		else
		{
			pl_ca_id_t="NULL";
		}
		if(sp_SignDate.Val)
		{
			sign="'"+sp_SignDate.FormatString("yyyy-mm-dd")+"'";
		}
		else
		{
			sign="NULL";
		}
		if(mode=="ins")
		{
			if(sp_num->Text=="")
			{
				sp_num->Text="1";
			}
			// �������� ������� ������������ � ��������� ������� ���� ��� �� ���������� ��������� ���� �� �� ������������ +1
			TADOQuery *rez=
				DB->SendSQL
				("select id from market.specifications where iddog='"+
				String(dog_id)+"' and spNum='"+sp_num->Text+"'");
			if(rez)
			{
				if(rez->RecordCount)
				{
					TADOQuery *rez1=
						DB->SendSQL
						("select max(spNum)+1 sp_num from market.specifications where iddog='"+
						String(dog_id)+"'");
					if(rez1&&rez1->RecordCount)
					{
						sp_num->Text=rez1->FieldByName("sp_num")->Value;
					}
					else
					{
						delete rez1;
						return;
					} // �� ������� ����� ����� ������������
					delete rez1;
				}
			}
			else
			{
				delete rez;
				return;
			} // ����� �� ������ ��� ������������� �������
			delete rez;
			rez=0;
			// ������������ ����� ���� �� �������
			String sql="";
			sql=sql+
				"insert into market.specifications (iddog,spNum,prim,nds,valute,gruz_ca_id,";
			sql=sql+
				"plat_ca_id,liz_ca_id,SignDate,CreateDate,UpdateDate,CreateUser,";
			sql=sql+"UpdateUser,cancelDate,cancelreason)values(";
			sql=sql+"'"+String(dog_id)+"','"+sp_num->Text+"','"+sp_prim->Text+
				"','"+nds->Text+"','"+valute->Text+"',"+gr_ca_id_t+",";
			sql=sql+pl_ca_id_t+","+lz_ca_id_t+","+sign+
				",CURRENT_TIMESTAMP(),CURRENT_TIMESTAMP(),'"+UName+"',";
			sql=sql+"'"+UName+"',NULL,'')";
			DB->SendCommand(sql);
			// ���������� �� ����������� ������������
			rez=DB->SendSQL
				("select id from market.specifications where iddog='"+
				String(dog_id)+"' and spNum='"+sp_num->Text+"'");
			if(rez&&rez->RecordCount)
			{
				sp_id=rez->FieldByName("id")->Value.operator __int64();
			}
			else
			{
				delete rez;
				return;
			} // ��������� ��� ������� ������
			// ��� ������� ������������ �� �������
			if(sp_id)
			{
				for(int i=1; i<SG2->RowCount; i++)
				{
					String sql="", zkom=SG2->Cells[20][i], zakaz=
						SG2->Cells[0][i], pos=SG2->Cells[21][i], name=
						SG2->Cells[1][i], obi=SG2->Cells[2][i], obivin=
						SG2->Cells[3][i], kol=SG2->Cells[5][i], price=
						SG2->Cells[6][i], per_suppl=SG2->Cells[4][i], ei_id=
						SG2->Cells[22][i], razd=SG2->Cells[23][i], prim=
						SG2->Cells[9][i], prime_cost=SG2->Cells[13][i],
						PC_Get_Date=SG2->Cells[14][i], calc_id=
						SG2->Cells[24][i], demand_id=SG2->Cells[25][i], ppo_vz=
						SG2->Cells[26][i], ppo_resurs=SG2->Cells[27][i],
						ppo_price_resurs=SG2->Cells[28][i], ppo_cex=
						SG2->Cells[29][i], ppf_r=SG2->Cells[30][i], ppf_size=
						SG2->Cells[31][i], ppf_vid=SG2->Cells[32][i],
						ppf_type_pf=SG2->Cells[33][i], ppf_isp=
						SG2->Cells[34][i], ppf_model=SG2->Cells[35][i], ppf_ves=
						SG2->Cells[36][i];

					if(calc_id=="")
					{
						calc_id="NULL";
					}
					else
					{
						calc_id="'"+calc_id+"'";
					}
					if(demand_id=="")
					{
						demand_id="NULL";
					}
					else
					{
						demand_id="'"+demand_id+"'";
					}
					if(ppo_vz=="")
					{
						ppo_vz="NULL";
					}
					else
					{
						ppo_vz="'"+ppo_vz+"'";
					}
					if(ppo_cex=="")
					{
						ppo_cex="NULL";
					}
					else
					{
						ppo_cex="'"+ppo_cex+"'";
					}
					if(ppf_vid=="")
					{
						ppf_vid="NULL";
					}
					else
					{
						ppf_vid="'"+ppf_vid+"'";
					}
					if(ppf_type_pf=="")
					{
						ppf_type_pf="NULL";
					}
					else
					{
						ppf_type_pf="'"+ppf_type_pf+"'";
					}

					sql=sql+
						"insert into market.specifications (id_spec,zkom,zakaz,pos,name,obi,obivin,kol,price,per_suppl,ei_id,";
					sql=sql+
						"razd,prim,prime_cost,PC_Get_Date,calc_id,demand_id,ppo_vz,ppo_resurs,ppo_price_resurs,ppo_cex,ppf_r,";
					sql=sql+
						"ppf_size,ppf_vid,ppf_type_pf,ppf_isp,ppf_model,ppf_ves,CreateDate,UpdateDate,CreateUser,UpdateUser) values(";
					sql=sql+"'"+String(sp_id)+"','"+zkom+"','"+zakaz+"','"+pos+
						"','"+name+"',";
					sql=sql+"'"+obi+"','"+obivin+"','"+kol+"','"+price+"','"+
						per_suppl+"',";
					sql=sql+"'"+ei_id+"','"+razd+"','"+prim+"','"+prime_cost+
						"','"+PC_Get_Date+"',";
					sql=sql+calc_id+","+demand_id+","+ppo_vz+",'"+ppo_resurs+
						"','"+ppo_price_resurs+"',";
					sql=sql+ppo_cex+",'"+ppf_r+"','"+ppf_size+"',"+ppf_vid+","+
						ppf_type_pf+",";
					sql=sql+"'"+ppf_isp+"','"+ppf_model+"','"+ppf_ves+
						"',CURRENT_TIMESTAMP(),CURRENT_TIMESTAMP(),'"+UName+
						"','"+UName+"')";
					// ������������ ����� � ������� ���� ������� ����������

					// a.zakaz, 			 #0#����� ������
					// a.name,			 #1#�������� ������
					// a.obi,			 #2#����������� ������
					// a.obivin,			 #3#����������� ������ ������ ���
					// a.per_suppl,		 #4#���� ��������
					// a.kol,			 #5#���������� ����������
					// a.price,			 #6#���� ����� �����
					// a.prim,			 #9#���������� � ������
					// a.prime_cost, 	 #13#�������������
					// a.pc_date,		 #14#���� ������� �������������
					// a.id_content,	  #16#������������� ������
					// a.sp_id,			 #17#������������� ������������
					// a.zkom, 			 #20# '������� ������� zkom'
					// a.pos, 			 #21# '������� � ������������ �������� zpoz'
					// a.ei_id, 			 #22# 'zgrs �� ��� 0=401 1=419 ����� � ���������'
					// a.razd, 			 #23# '������ �� �������� ������������ ������ ������ ������ razd'
					// a.calc_id, 		 #24# '������������� ����������� ������ nklk'
					// a.demand_id, 		 #25# '������������� ������ nzav'
					// a.ppo_vz, 		 #26# '��� ��������� zvid'
					// a.ppo_resurs,		 #27# '���������� ����������� �������� zves (�� ��� ���������)'
					// a.ppo_price_resurs,#28# '���� ������� ������� zckg (1 �� � 1 �/� ��������������)'
					// a.ppo_cex, 		 #29# '��� ����������� ����� zceu'
					// a.ppf_r, 			 #30# '������ ��������� zrad'
					// a.ppf_size, 		 #31# '������ ��������� zraz'
					// a.ppf_vid, 		 #32# '��� ��������� zvid'
					// a.ppf_type_pf, 	 #33# '��� ��������� zpvd'
					// a.ppf_isp, 		 #34# '���������� zisp'
					// a.ppf_model, 		 #35# '������ ����� znos'
					// a.ppf_ves 		 #36# 'zves'

					// ���� ����
					// a.calc_id, 			#24 null# '������������� ����������� ������ nklk'
					// a.demand_id, 			#25 null# '������������� ������ nzav'
					// a.ppo_vz, 			#26 null# '��� ��������� zvid'
					// a.ppo_cex, 			#29 null# '��� ����������� ����� zceu'
					// a.ppf_vid, 			#32 null# '��� ��������� zvid'
					// a.ppf_type_pf, 		#33 null# '��� ��������� zpvd'

					DB->SendCommand(sql);
				}
			}
		}
		if(mode=="upd")
		{ // �������������� �����, ���� �����������
			// �������� ������� ������� � ���� ��� ���������� �������� ��� ������� ��������
		}
		Del->Enabled=true;
		Cancel->Enabled=false;
		OK->Enabled=false;
		mode="";
		Comp_Activating();
		Find();
	}
	else
	{
		MessageDlg(msg, mtError, TMsgDlgButtons()<<mbOK, 0);
	}
}

void __fastcall Tprod::CancelClick(TObject *Sender)
{
	mode="";
	Edit->Enabled=true;
	Add->Enabled=true;
	Del->Enabled=true;
	Cancel->Enabled=false;
	OK->Enabled=false;
	Comp_Activating();
	ShowRowData(SG->Selection.Top);
}

void __fastcall Tprod::Accept_btnClick(TObject *Sender)
{
	if(accept_date->Text=="")
	{
		sp_SignDate=Date();
		accept_date->Text=sp_SignDate.FormatString("dd.mm.yyyy");
	}
}
// ---------------------------------------------------------------------------



