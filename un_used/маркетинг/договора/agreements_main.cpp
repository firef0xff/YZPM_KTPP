//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "agreements_main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
__fastcall TAgreements::TAgreements(TComponent* Owner,TWinControl *_p,const int &_LUser,cSQL *db)
	: TFrame(Owner),LUser(_LUser)
{
if (count==0)
	{
	DB=db;
	}
count++;
// расположение
Align=alClient;
Parent=_p;
Name=Name+String(count);
podrids="";
mode="";
id=0;
d_num="";
order_by="order by DogDate desc";
init ();
Comp_Activating();
SGClear(SG,0);
SG->Cells[0][0]="Вид";
SG->Cells[1][0]="№ Договора";
SG->Cells[2][0]="Дата";
SG->Cells[3][0]="Контрагент";
SG->Cells[4][0]="Предмет договора";
SG->Cells[5][0]="Исп(пр-во)";
SG->Cells[6][0]="Начало действия";
SG->Cells[7][0]="Окончание действия";
SG->Cells[8][0]="Подписано";
SG->Cells[9][0]="Сумма";
SG->Cells[10][0]="Исполнитель";
AutoWidthSG(SG);
CreateDate->Date=Date();
StartDate->Date=Date();
EndDate->Date=Date();
Find();
}
__fastcall 		TAgreements::~TAgreements(void)
{
count--;
if (count==0)
	{
	DB=0;
	}
}
void 			TAgreements::init (void)
{
//проверка прав доступа
TADOQuery *rez=DB->SendSQL("select agreement_Edit,agreement_assign from administration.privileges a join administration.logins b on a.Groupid=b.levelacss where b.LogID='"+String(LUser)+"'");
if (rez&&rez->RecordCount)
	{
	Agreement_Edit=rez->FieldByName("Agreement_Edit")->Value.operator bool();
	Agreement_Assign=rez->FieldByName("agreement_assign")->Value.operator bool();
	}else
	{
	Agreement_Edit=false;
	Agreement_Assign=false;
	}
delete rez;

Add->Enabled=Agreement_Edit;
Edit->Enabled=Agreement_Edit;
Del->Enabled=Agreement_Edit;


//загрузка данных в комбы
//предметы договора
predm_dog->Items->Clear();
rez=DB->SendSQL("select predm_dog from market.subject_of_the_agreement order by predm_dog");
if (rez&&rez->RecordCount)
	{
	for (rez->First(); !rez->Eof; rez->Next())
		{
		predm_dog->Items->AddObject(rez->FieldByName("predm_dog")->Value,0);
		}
	}
delete rez;
predm_dog->ItemIndex=-1;
//подразделения
podrids="";
podr_list->Items->Clear();
rez=DB->SendSQL("Call market.Get_podr_list('"+String(LUser)+"')");
if (rez&&rez->RecordCount)
	{
	for (rez->First(); !rez->Eof; rez->Next())
		{
		podr_list->Items->AddObject(rez->FieldByName("name")->Value,(TObject *)rez->FieldByName("id")->Value.operator int());
		podrids=podrids+"'"+rez->FieldByName("id")->Value.operator UnicodeString()+"',";
		}
	}
delete rez;
if (podrids!="")
	{
	podrids.Delete(podrids.Length(),1);
	}
podr_list->ItemIndex=0;
podr_listClick(0);
}
void 			TAgreements::Comp_Activating(void)
{
if (mode=="")
	{
	Ka1c->Enabled=false;
	ka_name->Enabled=false;
	accept_date->Enabled=false;
	predm_dog->Enabled=false;
	CreateDate->Enabled=false;
	StartDate->Enabled=false;
	EndDate->Enabled=false;
	summ->Enabled=false;
	dog_type->Enabled=false;
	preff->Enabled=false;
	num->Enabled=false;
	suff->Enabled=false;
	CB1->Enabled=false;
	podr_list->Enabled=false;
	isp_list->Enabled=false;
	leaders_list->Enabled=false;
	prim->Enabled=false;
	Accept_btn->Enabled=false;
	}else
	{
	Ka1c->Enabled=true;
	ka_name->Enabled=true;
	accept_date->Enabled=true;
	predm_dog->Enabled=true;
	CreateDate->Enabled=true;
	StartDate->Enabled=true;
	EndDate->Enabled=true;
	summ->Enabled=true;
	dog_type->Enabled=true;
	preff->Enabled=true;
	num->Enabled=true;
	suff->Enabled=true;
	CB1->Enabled=true;
	podr_list->Enabled=true;
	isp_list->Enabled=Agreement_Assign;
	leaders_list->Enabled=true;
	prim->Enabled=true;
	Accept_btn->Enabled=true;
	}
}
void __fastcall TAgreements::podr_listClick(TObject *Sender)
{
//список исполнителей для выбранного подразделения
if (podr_list->ItemIndex>=0)
	{
	isp_list->Items->Clear();
	String sql;
	if (mode==""||mode=="upd")
		{
		sql="Call market.Get_isp_list_u('"+String(LUser)+"')";
		}else
		{
		sql="Call market.Get_isp_list('"+String((int)podr_list->Items->Objects[podr_list->ItemIndex])+"')";
		}
	TADOQuery *rez=DB->SendSQL(sql);
	if (rez&&rez->RecordCount)
		{
		for (rez->First(); !rez->Eof; rez->Next())
			{
			isp_list->Items->AddObject(rez->FieldByName("LogIn")->Value,(TObject*)rez->FieldByName("LogID")->Value.operator int());
			}
		}
	isp_list->ItemIndex=isp_list->Items->IndexOfObject((TObject*)LUser);
	delete rez;
	isp_listClick(0);
	}
}
void __fastcall TAgreements::isp_listClick(TObject *Sender)
{
if (podr_list->ItemIndex>=0&&isp_list->ItemIndex>=0)
	{
	//список руководителей  для выбранного исполнителя и подразделения
	leaders_list->Items->Clear();
	String sql;
	if (mode=="")
		{
		sql="Call market.Get_leaders_list_f()";
		}else
		{
		sql="Call market.Get_leaders_list('"+String((int)isp_list->Items->Objects[isp_list->ItemIndex])+"')";
		}
	TADOQuery *	rez=DB->SendSQL(sql);
	if (rez&&rez->RecordCount)
		{
		for (rez->First(); !rez->Eof; rez->Next())
			{
			leaders_list->Items->AddObject(rez->FieldByName("LogIn")->Value,(TObject*)rez->FieldByName("LogID")->Value.operator int());
			}
		}
	leaders_list->ItemIndex=0;
	delete rez;
	}
}
void __fastcall TAgreements::splitClick(TObject *Sender)
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
void __fastcall TAgreements::E2Change(TObject *Sender)
{
if (E2->Text==""||E2->Text=="0")
	{
	E2->Text="1";
	}
Find();
}
void __fastcall TAgreements::E3Change(TObject *Sender)
{
if (E3->Text==""||E3->Text=="0")
	{
	E3->Text="1";
	}
if (E2->Text!="1") {E2->Text="1";} else {Find();}
}
void __fastcall TAgreements::nextClick(TObject *Sender)
{
TSpeedButton *bt=(TSpeedButton *)Sender;
switch (bt->Tag)
	{
	case  1:{E2->Text=String(E2->Text.ToInt()+1);break;}
	case -1:{if (E2->Text.ToInt()>1) {E2->Text=String(E2->Text.ToInt()-1);}break;}
	default:return;
	}
}
void __fastcall TAgreements::Ka1cClick(TObject *Sender)
{
TContragents *wnd=new TContragents(this,LUser,DB);
wnd->ShowModal();
if (wnd->ModalResult==mrOk)
	{
	String _ka_name;
	wnd->Get_id(ka_id,_ka_name);
	ka_name->Text=_ka_name;
	}
delete wnd;
}
void __fastcall TAgreements::Accept_btnClick(TObject *Sender)
{
if (accept_date->Text=="")
	{
	SignDate=Date();
	accept_date->Text=SignDate.FormatString("dd.mm.yyyy");
	}
}
void __fastcall TAgreements::FindClick(TObject *Sender)
{
TSel_params_agr *wnd= new TSel_params_agr(this,LUser,DB);
wnd->ShowModal();
if (wnd->ModalResult==mrOk)
	{
	sortparams=wnd->Get_Where();
	}else
	{
	sortparams="";
	}
if (E2->Text=="1")
	{
	Find();
	}else
	{
	E2->Text="1";  //срабатывет onChange а ссылка который и вызывает Find
	}
}
void __fastcall TAgreements::SortClearClick(TObject *Sender)
{
sortparams="";
if (E2->Text=="1")
	{
	Find();
	}else
	{
	E2->Text="1";  //срабатывет onChange а ссылка который и вызывает Find
	}
}

void			TAgreements::Find(void)
{
String sql="";
if (podrids!="")
	{
	sql+="select a.id,a.type,a.predm,";
	sql+="a.podrid,a.StartDate,a.EndDate,a.SignDate,a.Summ,";
	sql+="trim(concat(a.indication1,' ',if (a.indication3!=''or a.indication2!=0,if(a.indication3='',CONCAT('15/',YEAR(a.DogDate),'/',a.indication2),CONCAT(a.indication2,'-',a.indication3)),''),' ',a.indication4)) dog_num,";
	sql+="a.DogDate,a.Isp,a.leader,if (a.contractor_id is not null,a.contractor_id,0) contractor_id,a.prim,";
	sql+="a.indication1,a.indication2,a.indication3,a.indication4,";
	sql+="a.CreateUser,a.UpdateUser,a.CreateDate,a.UpdateDate,a.base,";
	sql+="if (b.sname is not null,b.sname,'') podr,if (c.sname is not null,c.sname,'') kontr,if (c.base is not null,c.base,'') ka_base";
	sql+=" from market.dog_list a";
	sql+=" join market.podr_list b on b.podrid=a.podrid";
	sql+=" left join market.contractors c on c.id=a.contractor_id";
	sql+=" where a.podrid in ("+podrids+")";
	if (sortparams!="")
		{
		sql=sql+sortparams;
		}
		sql=sql+order_by+" limit "+String(E2->Text.ToInt()*E3->Text.ToInt()-E3->Text.ToInt())+","+E3->Text;
	delete data;
	data=DB->SendSQL(sql);
	ShowData();
	ShowRowData(SG->Selection.Top);
	}
}

void			TAgreements::ShowData(void)
{
SGClear(SG,0);
if (data&&data->RecordCount)
	{
	SG->RowCount=data->RecordCount+1;
	for (data->First(); !data->Eof; data->Next())
		{
		SG->Cells[0][data->RecNo]=data->FieldByName("type")->Value;
		SG->Cells[1][data->RecNo]=data->FieldByName("dog_num")->Value;
		if (!data->FieldByName("DogDate")->Value.IsNull()&&data->FieldByName("DogDate")->Value.operator TDateTime().Val!=0)
			{
			SG->Cells[2][data->RecNo]=data->FieldByName("DogDate")->Value;
			}
		SG->Cells[3][data->RecNo]=data->FieldByName("kontr")->Value;
		SG->Cells[4][data->RecNo]=data->FieldByName("predm")->Value;
		SG->Cells[5][data->RecNo]=data->FieldByName("podr")->Value;
		if (!data->FieldByName("StartDate")->Value.IsNull()&&data->FieldByName("StartDate")->Value.operator TDateTime().Val!=0)
			{
			SG->Cells[6][data->RecNo]=data->FieldByName("StartDate")->Value;
			}
		if (!data->FieldByName("EndDate")->Value.IsNull()&&data->FieldByName("EndDate")->Value.operator TDateTime().Val!=0)
			{
			SG->Cells[7][data->RecNo]=data->FieldByName("EndDate")->Value;
			}
		if (!data->FieldByName("SignDate")->Value.IsNull()&&data->FieldByName("SignDate")->Value.operator TDateTime().Val!=0)
			{
			SG->Cells[8][data->RecNo]=data->FieldByName("SignDate")->Value;
			}
		if (data->FieldByName("Summ")->Value.operator double()!=0)
			{
			SG->Cells[9][data->RecNo]=data->FieldByName("Summ")->Value;
			}
		SG->Cells[10][data->RecNo]=data->FieldByName("Isp")->Value;
		}
	AutoWidthSG(SG);
	}
}
void			TAgreements::ShowRowData(int row)
{
if (mode=="")
	{
	if (data&&data->RecordCount&&row<=data->RecordCount&&mode=="")
		{
		data->RecNo=row;
		id=data->FieldByName("id")->Value.operator __int64();
		ka_name->Text=data->FieldByName("kontr")->Value;
		ka_id=data->FieldByName("contractor_id")->Value.operator __int64();
		if (!data->FieldByName("SignDate")->Value.IsNull()&&data->FieldByName("SignDate")->Value.operator TDateTime().Val!=0)
			{
			SignDate=data->FieldByName("SignDate")->Value.operator TDateTime();
			accept_date->Text=data->FieldByName("SignDate")->Value.operator TDateTime().FormatString("dd.mm.yyyy");
			}else
			{
			accept_date->Text="";
			}
		predm_dog->Text=data->FieldByName("predm")->Value;
		if (!data->FieldByName("DogDate")->Value.IsNull())
			{
			CreateDate->Date=data->FieldByName("DogDate")->Value.operator TDateTime();
			}else
			{
            CreateDate->Date=0;
			}
		if (!data->FieldByName("StartDate")->Value.IsNull())
			{
			StartDate->Date=data->FieldByName("StartDate")->Value.operator TDateTime();
			}else
			{
			StartDate->Date=0;
			}
		if (!data->FieldByName("EndDate")->Value.IsNull())
			{
			EndDate->Date=data->FieldByName("EndDate")->Value.operator TDateTime();
			}else
			{
			EndDate->Date=0;
			}

		if (data->FieldByName("Summ")->Value.operator double()!=0)
			{
			summ->Text=data->FieldByName("Summ")->Value.operator UnicodeString();
			}else
			{
			summ->Text="";
			}
		for (int i=0; i<dog_type->Items->Count; i++)
			{
			if (dog_type->Items->operator [](i).SubString(1,1).LowerCase()==data->FieldByName("type")->Value.operator UnicodeString())
				{
				dog_type->ItemIndex=i;
				break;
				}
			}
		podr_list->ItemIndex=podr_list->Items->IndexOfObject((TObject *)data->FieldByName("podrid")->Value.operator int());
		isp_list->ItemIndex=isp_list->Items->IndexOf(data->FieldByName("Isp")->Value.operator UnicodeString());
		leaders_list->ItemIndex=leaders_list->Items->IndexOf(data->FieldByName("leader")->Value.operator UnicodeString());
		prim->Text=data->FieldByName("prim")->Value.operator UnicodeString();
		preff->Text=data->FieldByName("indication1")->Value.operator UnicodeString();
		suff->Text=data->FieldByName("indication4")->Value.operator UnicodeString();
		num_ch=data->FieldByName("indication2")->Value;
		num_old=data->FieldByName("indication3")->Value.operator UnicodeString().Trim();
		if (data->FieldByName("DogDate")->Value.operator TDateTime().FormatString("yyyy")<"2009")
			{
			if (num_ch&&num_old!="")
				{
				num->Text=Trim((String)num_ch+"-"+num_old);
				CB1->Checked=true;
				}else
				{
                num->Text="";
				CB1->Checked=false;
				}
			}else
			{
			if (num_ch)
				{
				num->Text=Trim("15/"+data->FieldByName("DogDate")->Value.operator TDateTime().FormatString("yyyy")+"/"+(String)num_ch);
				CB1->Checked=true;
				}else
				{
				num->Text="";
				CB1->Checked=false;
				}
			}
		d_num=preff->Text+num->Text+suff->Text;
		}
	}
}
void __fastcall TAgreements::SGDrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect,
          TGridDrawState State)
{
 //рисовка сетки
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
		if (data->FieldByName("contractor_id")->Value.IsNull()==false&&data->FieldByName("ka_base")->Value.operator UnicodeString()=="1c")
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
void __fastcall TAgreements::SGFixedCellClick(TObject *Sender, int ACol, int ARow)

{
//сортировка
String field="";
switch (ACol)
	{
	case 0:{field="type";break;}
	case 1:{field="dog_num";break;}
	case 2:{field="DogDate";break;}
	case 3:{field="kontr";break;}
	case 4:{field="predm";break;}
	case 5:{field="podr";break;}
	case 6:{field="StartDate";break;}
	case 7:{field="EndDate";break;}
	case 8:{field="SignDate";break;}
	case 9:{field="Summ";break;}
	case 10:{field="Isp";break;}
	default:return;
	}
//определение порядка сортировки
String order="desc",kor="";
int pos=order_by.Pos(field);
if (pos==10)
	{
	kor=" ";
	String o_order=order_by.SubString(pos+field.Length()+1,4);
	if (o_order=="desc")
		{
		order="asc ";
		}else
		{
		order="desc";
		}
	}
//удаление старого вхождения строки
order_by.Delete(pos,field.Length()+order.Length()+2);
//вставка нового вхождения
order_by.Insert(kor+field+" "+order+",",10);
order_by=order_by.Trim();
if (order_by[order_by.Length()]==',')
	{
	order_by.Delete(order_by.Length(),1);
	}
Find();
}
void __fastcall TAgreements::SGSelectCell(TObject *Sender, int ACol, int ARow, bool &CanSelect)

{
ShowRowData(ARow);
}
void __fastcall TAgreements::AddClick(TObject *Sender)
{
mode="ins";
Comp_Activating();
Cancel->Enabled=true;
OK->Enabled=true;

Add->Enabled=false;
Del->Enabled=false;
Edit->Enabled=false;

ka_name->Text="";
id=0;
ka_id=0;
accept_date->Text="";
predm_dog->Text="";
CreateDate->Date=Date();
StartDate->Date=Date();
EndDate->Date=Date();
summ->Text="";
dog_type->ItemIndex=0;
podr_list->ItemIndex=0;
podr_listClick(0);
prim->Text="";
preff->Text="";
suff->Text="";
num->Text="";
num_ch=0;
num_old="";
SignDate=0;
if (CB1->Checked)
	{
	CB1Click(0);
	}else
	{
	CB1->Checked=true;
	}
if (split->Tag==1)
	{
	splitClick(split);
	}
}
void __fastcall TAgreements::EditClick(TObject *Sender)
{
mode="upd";
Comp_Activating();
Cancel->Enabled=true;
OK->Enabled=true;
Add->Enabled=false;
Del->Enabled=false;
Edit->Enabled=false;
podr_list->ItemIndex=0;
int uid=-1,lid=-1;
if (isp_list->ItemIndex>=0)
	{
	uid=(int)isp_list->Items->Objects[isp_list->ItemIndex];
	}
if (leaders_list->ItemIndex>=0)
	{
	lid=(int)leaders_list->Items->Objects[leaders_list->ItemIndex];
	}
podr_listClick(0);
if (uid<0)
	{
	uid=LUser;
	leaders_list->ItemIndex=0;
	}else
	{
	isp_list->ItemIndex=isp_list->Items->IndexOfObject((TObject*)uid);
	leaders_list->ItemIndex=leaders_list->Items->IndexOfObject((TObject*)lid);
	}
if (split->Tag==1)
	{
	splitClick(split);
	}
}

void __fastcall TAgreements::DelClick(TObject *Sender)
{
TADOQuery *rez=DB->SendSQL("Call market.dog_del('"+String(id)+"')");
if (rez&&rez->RecordCount)
	{
	MessageDlg(rez->FieldByName("msg")->Value,mtError,TMsgDlgButtons()<<mbOK,0);
	}
Find();
}

void __fastcall TAgreements::OKClick(TObject *Sender)
{
if (podr_list->ItemIndex==-1||isp_list->ItemIndex==-1) {return;}
//контрагент
String msg="";
if (!ka_id)
	{
	msg=msg+"Не выбран контрагент";
	}
if (predm_dog->Text=="")
	{
	msg=msg+"\nНе указан предмет договора";
	}
if ((preff->Text+num->Text+suff->Text).Trim()=="")
	{
	msg=msg+"\nНе указан номер договора";
	}
if (msg=="")
	{
	String sql="";
	if (mode=="ins")
		{
		sql="insert into market.dog_list ";
		sql+="(type,predm,podrid,StartDate,EndDate,SignDate,Summ,DogDate,Isp,leader,";
		sql+="contractor_id,prim,indication1,indication2,indication3,indication4,";
		sql+="CreateUser,UpdateUser,CreateDate,UpdateDate) ";
		sql+="select ";
		sql+="'"+dog_type->Text.SubString(1,1).LowerCase()+"',";
		sql+="'"+predm_dog->Text.Trim()+"',";
		sql+="'"+String((int)podr_list->Items->Objects[podr_list->ItemIndex])+"',";
		sql+="'"+StartDate->Date.FormatString("yyyy-mm-dd")+"',";
		sql+="'"+EndDate->Date.FormatString("yyyy-mm-dd")+"',";
		sql+="'"+SignDate.FormatString("yyyy-mm-dd")+"',";
		if (summ->Text.Trim()!="")
			{
			sql+="'"+summ->Text.Trim()+"',";
			}else
			{
			sql+="'0',";
			}
		sql+="'"+CreateDate->Date.FormatString("yyyy-mm-dd")+"',";
		sql+="'"+isp_list->Text+"',";
		sql+="'"+leaders_list->Text+"',";
		sql+="'"+String(ka_id)+"',";
		sql+="'"+prim->Text+"',";
		sql+="'"+preff->Text+"',";
		sql+="'"+(String)num_ch+"',";
		sql+="'"+num_old+"',";
		sql+="'"+suff->Text+"',";
		sql+="Login,Login,current_timestamp(),current_timestamp() ";
		sql+="from administration.logins where logid='"+String(LUser)+"'";
		Edit->Enabled=true;
		}
	if (mode=="upd")
		{
		sql="update market.dog_list a join administration.logins b on b.logid='"+String(LUser)+"' set ";
		sql+=" a.type='"+dog_type->Text.SubString(1,1).LowerCase()+"',";
		sql+=" a.predm='"+predm_dog->Text.Trim()+"',";
		sql+=" a.podrid='"+String((int)podr_list->Items->Objects[podr_list->ItemIndex])+"',";
		sql+=" a.StartDate='"+StartDate->Date.FormatString("yyyy-mm-dd")+"',";
		sql+=" a.EndDate='"+EndDate->Date.FormatString("yyyy-mm-dd")+"',";
		sql+=" a.SignDate='"+SignDate.FormatString("yyyy-mm-dd")+"',";
		if (summ->Text.Trim()!="")
			{
			sql+=" a.Summ='"+summ->Text.Trim()+"',";
			}else
			{
			sql+=" a.Summ='0',";
			}
		sql+=" a.DogDate='"+CreateDate->Date.FormatString("yyyy-mm-dd")+"',";
		sql+=" a.Isp='"+isp_list->Text+"',";
		sql+=" a.leader='"+leaders_list->Text+"',";
		sql+=" a.contractor_id='"+String(ka_id)+"',";
		sql+=" a.prim='"+prim->Text+"',";
		sql+=" a.indication1='"+preff->Text+"',";
		sql+=" a.indication2='"+(String)num_ch+"',";
		sql+=" a.indication3='"+num_old+"',";
		sql+=" a.indication4='"+suff->Text+"',";
		sql+=" a.UpdateUser=b.Login,";
		sql+=" a.UpdateDate=current_timestamp()";
		sql+=" where a.id='"+String(id)+"'";
		Add->Enabled=true;
		}
	if (sql!="")
		{
        DB->SendCommand(sql);
		}
	Del->Enabled=true;
	Cancel->Enabled=false;
	OK->Enabled=false;
	mode="";
	Comp_Activating();
	podr_listClick(0);
	Find();
	}else
	{
	MessageDlg(msg,mtError,TMsgDlgButtons()<<mbOK,0);
	}
}
void __fastcall TAgreements::CancelClick(TObject *Sender)
{
mode="";
Edit->Enabled=true;
Add->Enabled=true;
Del->Enabled=true;
Cancel->Enabled=false;
OK->Enabled=false;
Comp_Activating();
podr_listClick(0);
ShowRowData(SG->Selection.Top);
}
void __fastcall TAgreements::CB1Click(TObject *Sender)
{
if (mode!="")
	{
	if (num->Text!="")
		{
		num->Text="";
		}else
		{
		if (mode=="ins")
			{
			TADOQuery *rez=DB->SendSQL("Call market.Get_dog_num()");
			if (rez&&rez->RecordCount)
				{
				num->Text=rez->FieldByName("num")->Value.operator UnicodeString();
				num_ch=rez->FieldByName("num_ch")->Value;
				}
			}
		if (mode=="upd")
			{
			if (CreateDate->Date.FormatString("yyyy")<"2009")
				{
				num->Text=Trim((String)num_ch+"-"+num_old);
				}else
				{
				num->Text=Trim("15/"+CreateDate->Date.FormatString("yyyy")+"/"+(String)num_ch);
				}
			}
		}
	}
}

//---------------------------------------------------------------------------

