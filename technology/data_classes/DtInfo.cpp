#pragma hdrstop
#include "DtInfo.h"
#pragma package(smart_init)
	 DtInfo::DtInfo(cSQL *db, int _id,const int &_User):DB(db),LUserID(&_User)
{
count++;
//проверка уровня доступа пользователя
TADOQuery *rez=DB->SendSQL("Call administration.GetUserAccess('"+(String)*LUserID+"','"+(String)_id+"')");
if (rez&&rez->RecordCount)
	{
	LUser=rez->FieldByName("UserName")->Value;
	access=rez->FieldByName("access")->Value;
	LoadData(_id);
	}else
	{
	access=false;
	}
delete rez;
}
	 DtInfo::DtInfo(const DtInfo &isx):DB(isx.DB),LUserID(isx.LUserID)
{
count++;
// проверить ниже
id=isx.id;
obm=isx.obm;
ei=isx.ei;
eiName=isx.eiName;
vz=isx.vz;
kdz=isx.kdz;
masd=isx.masd;
masz=isx.masz;
nrm=isx.nrm;
razz=isx.razz;
pm=isx.pm;
napr=isx.napr;
CreateUser=isx.CreateUser;
ChangeUser=isx.ChangeUser;
CreateDate=isx.CreateDate;
ChangeDate=isx.ChangeDate;
operations=new OperRow(*isx.operations);
action=isx.action;
access=false;
LUser=isx.LUser;
}
	 DtInfo::~DtInfo()
{
// удаление связанных цепочек
if (operations)
	{
	operations=operations->Get_Last();//движемся с конца к началу цепочки чтобы деструктор не инициализировал пересчет позиций
	while (operations)
		{
		if (operations->Get_Next())
			{
			delete operations->Get_Next();
			operations->Set_Next(0);
			}
		operations=operations->Get_Prev();
		}
	}
count--;
}
void DtInfo::CheckAccept(void)
{
//проверка уровня доступа пользователя
TADOQuery *rez=DB->SendSQL("Call administration.GetUserAccess('"+(String)*LUserID+"','"+(String)id+"')");
if (rez&&rez->RecordCount)
	{
	access=rez->FieldByName("access")->Value;
	}else
	{
	access=false;
	}
delete rez;
}
void DtInfo::LoadData(int _id)
{
TADOQuery *rez=DB->SendSQL("Call technologic.GetDetInfo("+String(_id)+")");
if (rez&&rez->RecordCount)
	{
	id=rez->FieldByName("id")->Value;
	ei=rez->FieldByName("ei")->Value;
	eiName=rez->FieldByName("eiName")->Value;
	masd=rez->FieldByName("masd")->Value;
	obm=VinToGost(rez->FieldByName("obm")->Value);
	obmid=rez->FieldByName("obmid")->Value;
	vz=rez->FieldByName("vz")->Value;
	vzName=rez->FieldByName("vzName")->Value;
	kdz=rez->FieldByName("kdz")->Value;
	masz=rez->FieldByName("masz")->Value;
	nrm=rez->FieldByName("nrm")->Value;
	razz=rez->FieldByName("razz")->Value;
	pm=rez->FieldByName("pm")->Value;
	napr=rez->FieldByName("napr")->Value;
	CreateUser=rez->FieldByName("CreateUser")->Value;
	ChangeUser=rez->FieldByName("ChangeUser")->Value;
	CreateDate=rez->FieldByName("CreateDate")->Value.operator TDateTime();
	ChangeDate=rez->FieldByName("ChangeDate")->Value.operator TDateTime();
	action="no";
 	}else
	{
	id=_id;
	ei=0;
	eiName="";
	masd=0;
	obm="";
	obmid=0;
	vz=0;
	vzName="";
	kdz=1;
	masz=0;
	nrm=0;
	razz="";
	pm="";
	napr="";
	CreateUser="";
	ChangeUser="";
	CreateDate=0;
	ChangeDate=0;
	action="ins";
	}
delete rez;
rez=DB->SendSQL("call technologic.GetOperations('"+(String)id+"')");
if (rez&&rez->RecordCount)
	{
	OperRow *t=0;
	for (rez->First(); !rez->Eof; rez->Next())
		{
		t=new OperRow(	DB,LUser,
						rez->FieldByName("OpUUID")->Value.operator __int64(),
						"no",
						rez->FieldByName("id")->Value.operator int(),
						rez->FieldByName("ktar")->Value.operator int(),
						rez->FieldByName("ok69")->Value.operator int(),
						rez->FieldByName("cex")->Value.operator UnicodeString(),
						rez->FieldByName("utch")->Value.operator UnicodeString(),
						rez->FieldByName("opr")->Value.operator UnicodeString(),
						rez->FieldByName("oboID")->Value.operator UnicodeString(),
						rez->FieldByName("OboName")->Value.operator UnicodeString(),
						rez->FieldByName("OprName")->Value.operator UnicodeString(),
						rez->FieldByName("OprCode")->Value.operator UnicodeString(),
						rez->FieldByName("stro")->Value.operator UnicodeString(),
						rez->FieldByName("tara")->Value.operator UnicodeString(),
						rez->FieldByName("control")->Value.operator UnicodeString(),
						rez->FieldByName("ioht")->Value.operator UnicodeString(),
						rez->FieldByName("CreateUser")->Value.operator UnicodeString(),
						rez->FieldByName("UpdateUser")->Value.operator UnicodeString(),
						rez->FieldByName("CreateDate")->Value.operator TDateTime(),
						rez->FieldByName("UpdateDate")->Value.operator TDateTime(),
						t);
		}
	if (t) {operations=t->Get_First();}
	}else
	{
    operations=0;
	}
delete rez;
}
bool DtInfo::SaveData(void)
{
if (!access){return false;}
Get_pm();
bool effect=true;
String sql="",tei=(String)ei,tvz=(String)vz;
while (tei.Length()<3)
	{
	tei="0"+tei;
	}
while (tvz.Length()<3)
	{
	tvz="0"+tvz;
	}
if (action=="ins")
	{
	sql="insert into technologic.det_info (id,ei,masd,obmid,vz,kdz,masz,nrm,razz,pm,napr,CreateUser,CreateDate,ChangeUser,ChangeDate)values('"+(String)id+"','"+tei+"','"+Replace((String)masd,",",".")+"','"+(String)obmid+"','"+tvz+"','"+(String)kdz+"','"+Replace((String)masz,",",".")+"','"+Replace((String)nrm,",",".")+"','"+razz+"','"+pm+"','"+napr+"','"+LUser+"',CURRENT_TIMESTAMP(),'"+LUser+"',CURRENT_TIMESTAMP())";
	}
if (action=="upd")
	{
	sql="update technologic.det_info set ei='"+tei+"',masd='"+Replace((String)masd,",",".")+"',obmid='"+(String)obmid+"',vz='"+tvz+"',kdz='"+(String)kdz+"',masz='"+Replace((String)masz,",",".")+"',nrm='"+Replace((String)nrm,",",".")+"',razz='"+razz+"',pm='"+pm+"',napr='"+napr+"',ChangeUser='"+LUser+"',ChangeDate=CURRENT_TIMESTAMP(),base='mysql' where id='"+(String)id+"'";
	}
if (sql!="")
	{
	effect=DB->SendCommand(sql);
	if (effect)
		{
		action="no";
		}
	}
if (operations)
	{
	effect=effect*operations->SaveData(operations);
	}
if (action!="no")
	{
	effect=false;
	}
return effect;
}

String 	DtInfo::Get_pm(void)
{
String tmp="";
if (operations)
	{
	for (OperRow *i=operations->Get_First(); i; i=i->Get_Next())
		{
		if (i->isUsed()&&tmp.SubString(tmp.Length()-4,5).Trim()!=i->Get_ceh()+i->Get_uch())
			{
			tmp=tmp.Trim()+" "+i->Get_ceh()+i->Get_uch();
			}
		}
	}
if (tmp!=pm)
	{
	if (action=="no")
		{
		action="upd";
		}
	pm=tmp;
	}
return pm;
}
void 	DtInfo::Set_ei(int r)
{
if (!r)
	{
	ei=0;
    eiName="";
	}
if (ei!=r)
	{
	String kod=(String)r;
	while (kod.Length()<3)
		{
		kod="0"+kod;
		}
	TADOQuery * rez=DB->SendSQL("Call catalogs.Get_eiName('"+kod+"')");
	if (rez&&rez->RecordCount)
		{
		ei=r;
		eiName=rez->FieldByName("eiName")->Value;
		if (action=="no")
			{
			action="upd";
			}
		}
	delete rez;
	}
}
void 	DtInfo::Set_vz(int r)
{
if (vz!=r)
	{
	String kod=(String)r;
	while (kod.Length()<3)
		{
		kod="0"+kod;
		}
	TADOQuery * rez=DB->SendSQL("Call billets.Get_vzName('"+kod+"')");
	if (rez&&rez->RecordCount)
		{
		vz=r;
		vzName=rez->FieldByName("vzName")->Value;
		if (action=="no")
			{
			action="upd";
			}
		}
	delete rez;
	}
}
void 	DtInfo::Set_obm(String r)
{
if (obm!=r)
	{
	TADOQuery *rez=DB->SendSQL("Call constructions.Get_id('"+GostToVin(r)+"')");
	if (rez&&rez->RecordCount)
		{
		obmid=rez->FieldByName("id")->Value;
		obm=VinToGost(rez->FieldByName("obd")->Value);
		if(action=="no")
			{
			action="upd";
			}
		}
	delete rez;
	}
}
bool 	DtInfo::Need_Save(void)
{
bool Need_save=action!="no"?true:false;
if (!Need_save&&operations)
	{
	Need_save=operations->Need_Save();
	}
return Need_save;
}
bool    DtInfo::Can_Save(String &msg)
{
bool result=true;
msg="Недостаточно данных.";
if (!vz)
	{
	result=result*false;
	msg=msg+"\nНеуказан код заготовки";
	}
if (!ei)
	{
	result=result*false;
	msg=msg+"\nНеуказаны еденицы измерения";
	}
if (!obmid)
	{
	result=result*false;
	msg=msg+"\nНеуказан материал";
	}
if (operations)
	{
	result=result*operations->Can_Save(msg);
	}
return result;
}
