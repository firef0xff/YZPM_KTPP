//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "contractors.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

__fastcall TContragents::TContragents(TComponent* Owner,const int &_LUser,cSQL *db)
	: TForm(Owner),LUser(_LUser)
{
if (count==0)
	{
	DB=db;
	DB1C=new cSQL(ADC1C);
	}
count++;
// расположение
Name=Name+String(count);

data=0;
SG->Cells[1][0]="ИНН";
SG->Cells[2][0]="Наименование";
SG->Cells[3][0]="Адрес";
mode="";
Select_id=0;
Select_name="";
id=0;
init();
Find();
AutoWidthSG(SG);
}
__fastcall 		TContragents::~TContragents(void)
{
count--;
delete data;
if (count==0)
	{
	DB=0;
	DB1C=0;
	}
}
void 			TContragents::init(void)
{
//загрузка прав пользователя
}
void __fastcall TContragents::splitClick(TObject *Sender)
{
TButton *btn=(TButton *)Sender;
if (btn)
	{
	if (btn->Tag)
		{
		Panel3->Height=190;
		btn->Tag=0;
		}else
		{
		Panel3->Height=10;
		btn->Tag=1;
		}
	}
}

void __fastcall TContragents::ADDClick(TObject *Sender)
{
mode="add";
Edit->Enabled=false;
Save->Enabled=true;
Cancel->Enabled=true;

Inn->ReadOnly=false;
Kpp->ReadOnly=false;
sName->ReadOnly=false;
fName->ReadOnly=false;
Phones->ReadOnly=false;
Addr_yur->ReadOnly=false;
Addr_fiz->ReadOnly=false;

Inn->Text="";
Kpp->Text="";
sName->Text="";
fName->Text="";
Phones->Text="";
Addr_yur->Text="";
Addr_fiz->Text="";

if (split->Tag==1)
	{
	splitClick(split);
	}
}
void __fastcall TContragents::EditClick(TObject *Sender)
{
mode="edit";
Save->Enabled=true;
Cancel->Enabled=true;

Inn->ReadOnly=false;
Kpp->ReadOnly=false;
sName->ReadOnly=false;
fName->ReadOnly=false;
Phones->ReadOnly=false;
Addr_yur->ReadOnly=false;
Addr_fiz->ReadOnly=false;
}
void __fastcall TContragents::SaveClick(TObject *Sender)
{
String msg="";
/*if (Inn->Text.Trim()=="")
	{
	msg="Укажите ИНН\n";
	}  */
if (sName->Text.Trim()=="")
	{
	msg="Укажите название\n";
	}
if (msg!="")
	{
	MessageDlg(msg,mtError,TMsgDlgButtons()<<mbOK,0);
	}else
	{
	if (mode=="add")
		{
		//проверить наличие в таблице по инн
		int mrez=mrYes;
		TADOQuery *rez=DB->SendSQL("select id from market.contractors where inn='"+Inn->Text.Trim()+"'");
		if (rez&&rez->RecordCount)
			{//добавить в таблицу
			mrez=mbNo;
			mrez=MessageDlg("Контрагент с таким инн существует. Продолжить?",mtError,TMsgDlgButtons()<<mbYes<<mbNo,0);
			}
		delete rez;
		if (mrez==mrYes)
			{
			DB->SendCommand("insert into market.contractors (inn,kpp,sname,fname,address_yur,address_fiz,phones,base)values('"+Inn->Text+"','"+Kpp->Text+"','"+ekran(sName->Text.Trim())+"','"+ekran(fName->Text.Trim())+"','"+ekran(Addr_yur->Text.Trim())+"','"+ekran(Addr_fiz->Text.Trim())+"','"+ekran(Phones->Text.Trim())+"','mysql')");
			}
		rez=DB->SendSQL("select id from market.contractors where inn='"+Inn->Text+"' and kpp='"+Kpp->Text+"' and sname='"+ekran(sName->Text.Trim())+"' and fname='"+ekran(fName->Text.Trim())+"' and address_yur='"+ekran(Addr_yur->Text.Trim())+"' and address_fiz='"+ekran(Addr_fiz->Text.Trim())+"'");
		if (rez&&rez->RecordCount)
			{
			id=rez->FieldByName("id")->Value.operator __int64();
			}
        delete rez;
		}
	if (mode=="edit")
		{//обновить таблицу
		if (id)
			{
			DB->SendCommand("update market.contractors set inn='"+Inn->Text+"',kpp='"+Kpp->Text+"',sname='"+ekran(sName->Text.Trim())+"',fname='"+ekran(fName->Text.Trim())+"',address_yur='"+ekran(Addr_yur->Text.Trim())+"',address_fiz='"+ekran(Addr_fiz->Text.Trim())+"',phones='"+ekran(Phones->Text.Trim())+"' where id='"+String(id)+"'");
			}
		}
	//запустить выравнивалку данных
	DB->SendCommand("Call market.refresh_contractors()");
	mode="";
	Edit->Enabled=true;
	Save->Enabled=false;
	Cancel->Enabled=false;

	Inn->ReadOnly=true;
	Kpp->ReadOnly=true;
	sName->ReadOnly=true;
	fName->ReadOnly=true;
	Phones->ReadOnly=true;
	Addr_yur->ReadOnly=true;
	Addr_fiz->ReadOnly=true;

	Name_params->Text=Inn->Text;
	Find();
	}
}
void __fastcall TContragents::CancelClick(TObject *Sender)
{
mode="";
Edit->Enabled=true;
Save->Enabled=false;
Cancel->Enabled=false;

Inn->ReadOnly=true;
Kpp->ReadOnly=true;
sName->ReadOnly=true;
fName->ReadOnly=true;
Phones->ReadOnly=true;
Addr_yur->ReadOnly=true;
Addr_fiz->ReadOnly=true;

ShowRowData(SG->Selection.Top);
}
void __fastcall TContragents::DELClick(TObject *Sender)
{
TADOQuery *rez=DB->SendSQL("Call market.contractor_del('"+String(id)+"')");
if (rez&&rez->RecordCount)
	{
	MessageDlg(rez->FieldByName("msg")->Value,mtError,TMsgDlgButtons()<<mbOK,0);
	}
Find();
}

void __fastcall TContragents::Upd1CClick(TObject *Sender)
{
Update_contractors();
}
void __fastcall TContragents::FINDClick(TObject *Sender)
{
if (E2->Text=="1")
	{
	Find();
	}else
	{
	E2->Text="1";  //срабатывет onChange а ссылка который и вызывает Find
	}
}
void __fastcall TContragents::Name_paramsKeyPress(TObject *Sender, wchar_t &Key)
{
if (Key==13){FINDClick(0);}
}
void __fastcall TContragents::E2Change(TObject *Sender)
{
if (E2->Text==""||E2->Text=="0")
	{
	E2->Text="1";
	}
Find();
}
void __fastcall TContragents::E3Change(TObject *Sender)
{
if (E3->Text==""||E3->Text=="0")
	{
	E3->Text="1";
	}
if (E2->Text!="1") {E2->Text="1";} else {Find();}
}
void __fastcall TContragents::nextClick(TObject *Sender)
{
TSpeedButton *bt=(TSpeedButton *)Sender;
switch (bt->Tag)
	{
	case  1:{E2->Text=String(E2->Text.ToInt()+1);break;}
	case -1:{if (E2->Text.ToInt()>1) {E2->Text=String(E2->Text.ToInt()-1);}break;}
	default:return;
	}
}

void __fastcall TContragents::SGSelectCell(TObject *Sender, int ACol, int ARow, bool &CanSelect)
{
if (mode=="")
	{
	ShowRowData(ARow);
	}
}
void 			TContragents::Update_contractors(void)
{
TADOQuery *rez=0;
TADOQuery *rez1c=DB1C->SendSQL("select id as id1c, sp27850 as inn,sp27851 as kpp,descr as sname,sp48 as fname,sp50 as address_yur,sp3145 as address2_fiz,sp49 as phones from sc46");
if (rez1c&&rez1c->RecordCount)
	{
	for (rez1c->First(); !rez1c->Eof; rez1c->Next())
		{
		String
		id1c=ekran(Trim(rez1c->FieldByName("id1c")->Value)),
		inn=ekran(Trim(rez1c->FieldByName("inn")->Value)),
		kpp=ekran(Trim(rez1c->FieldByName("kpp")->Value)),
		sname=ekran(Trim(rez1c->FieldByName("sname")->Value)),
		fname=ekran(Trim(rez1c->FieldByName("fname")->Value)),
		address_yur=ekran(Trim(rez1c->FieldByName("address_yur")->Value)),
		address_fiz=ekran(Trim(rez1c->FieldByName("address2_fiz")->Value)),
		phones=ekran(Trim(rez1c->FieldByName("phones")->Value));
		rez=DB->SendSQL("select id from market.contractors where id1c='"+id1c+"'");
		if (rez)
			{
			if (rez->RecordCount)
				{
				DB->SendCommand("update market.contractors set inn='"+inn+"',kpp='"+kpp+"',sname='"+sname+"',fname='"+fname+"',address_yur='"+address_yur+"',address_fiz='"+address_fiz+"',phones='"+phones+"',base='1c' where id1c='"+id1c+"'");
				}else
				{
				DB->SendCommand("insert into market.contractors (inn,kpp,sname,fname,address_yur,address_fiz,phones,id1c,base)values('"+inn+"','"+kpp+"','"+sname+"','"+fname+"','"+address_yur+"','"+address_fiz+"','"+phones+"','"+id1c+"','1c')");
				}
			}
		delete rez;
		}
	DB->SendCommand("Call market.refresh_contractors()");
	}
delete rez1c;
}

void			TContragents::Find(void)
{
String sql="select id,inn,kpp,sname,if (fname is not null,fname,'')as fname,if (address_yur is not null,address_yur,'')as address_yur,if (address_fiz is not null,address_fiz,'')as address_fiz, if (phones is not null,phones,'')as phones,id1c from market.contractors";
if (Name_params->Text.Trim()!="")
	{
	sql=sql+" where address_yur like '%"+Name_params->Text.Trim()+"%' or address_fiz like '%"+Name_params->Text.Trim()+"%' or phones like '%"+Name_params->Text.Trim()+"%' or inn like '%"+Name_params->Text.Trim()+"%' or sname like '%"+Name_params->Text.Trim()+"%' or fname like '%"+Name_params->Text.Trim()+"%' or kpp like '%"+Name_params->Text.Trim()+"%'";
	}
	sql=sql+" order by sname,inn limit "+String(E2->Text.ToInt()*E3->Text.ToInt()-E3->Text.ToInt())+","+E3->Text;
delete data;
data=DB->SendSQL(sql);
ShowData();
ShowRowData(SG->Selection.Top);
}
void			TContragents::ShowData(void)
{
SGClear(SG,0);
if (data&&data->RecordCount)
	{
	SG->RowCount=data->RecordCount+1;
	for (data->First(); !data->Eof; data->Next())
		{
		SG->Cells[1][data->RecNo]=data->FieldByName("inn")->Value;
		SG->Cells[2][data->RecNo]=data->FieldByName("sname")->Value;
		SG->Cells[3][data->RecNo]=data->FieldByName("address_fiz")->Value;
		if (SG->Cells[3][data->RecNo].Trim()=="")
			{
			SG->Cells[3][data->RecNo]=data->FieldByName("address_yur")->Value;
			}
		}
	AutoWidthSG(SG);
	}
}
void			TContragents::ShowRowData(int row)
{
if (data&&data->RecordCount&&row<=data->RecordCount&&mode=="")
	{
	data->RecNo=row;
	id=data->FieldByName("id")->Value.operator __int64();
	Inn->Text=data->FieldByName("inn")->Value;
	Kpp->Text=data->FieldByName("kpp")->Value;
	sName->Text=data->FieldByName("sname")->Value;
	fName->Text=data->FieldByName("fname")->Value;
	Phones->Text=data->FieldByName("phones")->Value;
	Addr_yur->Text=data->FieldByName("address_yur")->Value;
	Addr_fiz->Text=data->FieldByName("address_fiz")->Value;
	}
}
void __fastcall TContragents::OKClick(TObject *Sender)
{
if (data&&data->RecordCount&&SG->Selection.Top<=data->RecordCount)
	{
	data->RecNo=SG->Selection.Top;
	Select_id=data->FieldByName("id")->Value.operator __int64();;
	Select_name=data->FieldByName("sname")->Value;
	}
}
void __fastcall TContragents::SGDrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect,
          TGridDrawState State)
{ //рисовка сетки
static int color=0X00E0FFFF;
int bad_color=0x00DDDDFF;
if (ARow==1){color=0X00E0FFFF;}
if(ACol&&ARow)
	{   //разлинейка
	if ((ARow%2))
	  {
	  color=0X00E0FFFF;
	  }else
	  {
	  color=0x00e0FFe0;
	  }
	  if (data&&data->RecordCount)
	  {
	  data->RecNo=ARow;
		if (data->FieldByName("id1c")->Value.operator UnicodeString().Trim()!="")
		  {
		  SG->Canvas->Brush->Color=color;
		  }else
		  {
		  SG->Canvas->Brush->Color=bad_color;
		  }
	  }else
	  {
	  SG->Canvas->Brush->Color=color;
	  }
	SG->Font->Color=clBlack;
	SG->Canvas->FillRect(Rect);
	SG->Canvas->TextOutW(Rect.left+2,Rect.top+1,SG->Cells[ACol][ARow]);
	}
//выделенные поля
if (ACol>=SG->Selection.Left&&ACol<=SG->Selection.Right&&ARow>=SG->Selection.Top&&ARow<=SG->Selection.Bottom)                                     //выделение
	{
	SG->Canvas->Brush->Color=0x00FFE0E0;//clMenu;
	SG->Canvas->FillRect(Rect);
	SG->Font->Color=clBlack;
	SG->Canvas->Font->Color=clBlack;
	SG->Canvas->TextOutW(Rect.left+2,Rect.top+1,SG->Cells[ACol][ARow]);
	}
}

