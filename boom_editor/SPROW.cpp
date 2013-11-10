#pragma hdrstop
#include "SPROW.h"
#pragma package(smart_init)
		SpRow::SpRow		(cSQL *const db,const int &__User,
							const int &_id,	const int &_idparent,const int &_SpRazd,	const int &_pp,
							const int &_ppp,	const int &_ei,		const int &_state,	const int &_UserID,
							const String &_Obd,		const String &_Obu,
							const String &_Name,	const String &_SpRazdName,
							const String &_format,	const String &_pos,		const String &_prim,
							const String &_zona,		const String &_ppName,	const String &_eiName,
							const String &_User,		const String &_CondName,	const String &_DetCreator,
							const String &_DetUpdater,	const String &_RowCreator,
							const String &_RowUpdater,	const double &_kol,
							const bool &_arhive,	const bool &_CanChild,	const bool &_Accept,
							const TDateTime  &_DetCreated,	const TDateTime  &_DetUpdated,
							const TDateTime  &_RowCreated,	const TDateTime  &_RowUpdated
							):TreeRow(db,__User)//вариант для загрузки из базы напрямую
{
init();
//Obd
id=_id;
SpRazd=_SpRazd;
V_Obd=GostToVin(_Obd);
G_Obd=VinToGost(V_Obd);
Name=_Name.Trim();
SpRazdName=_SpRazdName.Trim();
//TreeRow
idparent=_idparent;
pp=_pp;
ppp=_ppp;
ei=_ei;
state=_state;
UserID=_UserID;
V_Obu=GostToVin(_Obu);
G_Obu=VinToGost(V_Obu);
format=_format.Trim();
pos=_pos.Trim();
prim=_prim.Trim();
zona=_zona.Trim();
ppName=_ppName.Trim();
eiName=_eiName.Trim();
User=_User.Trim();
CondName=_CondName.Trim();
DetCreator=_DetCreator.Trim();
DetUpdater=_DetUpdater.Trim();
RowCreator=_RowCreator.Trim();
RowUpdater=_RowUpdater.Trim();
kol=_kol;
Arhive=_arhive;
Set_Force(false);
CanChild=_CanChild;
Accept=_Accept;
DetCreated=_DetCreated;
DetUpdated=_DetUpdated;
RowCreated=_RowCreated;
RowUpdated=_RowUpdated;
//SPRow
id_t=id;
idp_t=idparent;        //изначальный id
G_Obd_t=G_Obd;	 //изначальное обозначенеие
V_Obd_t=V_Obd;	//изначальное обозначенеие
//проверит наличие в базе сравнить с ними и назначить дейстие
//проверка на наличие строки
action_row="no";	//метка действия со строкой
action_det="no"; //метка действия с параметрами детали
inBase=true;		//метка наличия строки в базе
count++;
}
		SpRow::SpRow		(cSQL *const db,const int &__User,
							const int &_pp,		const int &_ppp,const int &_SpRazd,
							const String &_Obd,		const String &_Obu,
							const String &_Name,	const String &_SpRazdName,
							const String &_format,	const String &_pos,		const String &_prim,
							const String &_zona,	const double &_kol
							):TreeRow(db,__User) //вариант для загрузки из файла
{
init();
//Obd
id=Get_id(_Obd);
V_Obd=GostToVin(_Obd);
G_Obd=VinToGost(V_Obd);
Name=_Name.Trim();
SpRazd=_SpRazd;
SpRazdName=_SpRazdName.Trim();
//TreeRow
idparent=Get_id(_Obu);
pp=_pp;
ppp=_ppp;
V_Obu=GostToVin(_Obu);
G_Obu=VinToGost(V_Obu);
format=_format.Trim();
pos=_pos.Trim();
prim=_prim.Trim();
zona=_zona.Trim();
kol=_kol;
Set_ei();
count++;
}
		SpRow::SpRow		(cSQL *const db,const int &__User,
							const int &_id,	const int &_idparent, const int &_SpRazd,	const int &_pp,
							const int &_ppp,	const int &_ei,		const int &_state,	const int &_UserID,
							const String &_Obd,		const String &_Obu,
							const String &_Name,	const String &_SpRazdName,
							const String &_format,	const String &_pos,		const String &_prim,
							const String &_zona,		const String &_ppName,	const String &_eiName,
							const String &_User,		const String &_CondName,	const String &_DetCreator,
							const String &_DetUpdater,	const String &_RowCreator,
							const String &_RowUpdater,
							const String &_action_row,  const String &_action_det,
							const double &_kol,
							const bool &_arhive,	const bool &_CanChild,	const bool &_Accept,
							const bool &_inBase,
							const TDateTime  &_DetCreated,	const TDateTime  &_DetUpdated,
							const TDateTime  &_RowCreated,	const TDateTime  &_RowUpdated
							):TreeRow(db,__User)//вариант для обработки
{
init();
//Obd
id=_id;
SpRazd=_SpRazd;
V_Obd=GostToVin(_Obd);
G_Obd=VinToGost(V_Obd);
Name=_Name.Trim();
SpRazdName=_SpRazdName.Trim();
//TreeRow
idparent=_idparent;
pp=_pp;
ppp=_ppp;
ei=_ei;
state=_state;
UserID=_UserID;
V_Obu=GostToVin(_Obu);
G_Obu=VinToGost(V_Obu);
format=_format.Trim();
pos=_pos.Trim();
prim=_prim.Trim();
zona=_zona.Trim();
ppName=_ppName.Trim();
eiName=_eiName.Trim();
User=_User.Trim();
CondName=_CondName.Trim();
DetCreator=_DetCreator.Trim();
DetUpdater=_DetUpdater.Trim();
RowCreator=_RowCreator.Trim();
RowUpdater=_RowUpdater.Trim();
kol=_kol;
Arhive=_arhive;
Set_Force(false);
CanChild=_CanChild;
Accept=_Accept;
DetCreated=_DetCreated;
DetUpdated=_DetUpdated;
RowCreated=_RowCreated;
RowUpdated=_RowUpdated;
//SPRow
id_t=id;
idp_t=idparent;    //изначальный id
G_Obd_t=G_Obd;	 //изначальное обозначенеие
V_Obd_t=V_Obd;	//изначальное обозначенеие
//проверит наличие в базе сравнить с ними и назначить дейстие
//проверка на наличие строки
action_row=_action_row;	//метка действия со строкой
action_det=_action_det; //метка действия с параметрами детали
inBase=_inBase;		//метка наличия строки в базе
count++;
}
		SpRow::~SpRow      (void)
{
count--;
}
void 	SpRow::init			(void)
{
id_t=0;
idp_t=0;
G_Obd_t="";
V_Obd_t="";
action_row="no";
action_det="no";
action_row_t="";
inBase=false;
}
SpRow & SpRow::operator =	(const SpRow &r)
{
if (this==&r) {return *this;}
//Obd
id=r.id;
SpRazd=r.SpRazd;
G_Obd=r.G_Obd;
V_Obd=r.V_Obd;
Name=r.Name;
SpRazdName=r.SpRazdName;
//TreeRow
idparent=r.idparent;
pp=r.pp;
ppp=r.ppp;
ei=r.ei;
state=r.state;
UserID=r.UserID;
V_Obu=r.V_Obu;
G_Obu=r.G_Obu;
format=r.format;
pos=r.pos;
prim=r.prim;
zona=r.zona;
ppName=r.ppName;
eiName=r.eiName;
User=r.User;
CondName=r.CondName;
DetCreator=r.DetCreator;
DetUpdater=r.DetUpdater;
RowCreator=r.RowCreator;
RowUpdater=r.RowUpdater;
kol=r.kol;
Arhive=r.Arhive;
Force=r.Force;
CanChild=r.CanChild;
Accept=r.Accept;
DetCreated=r.DetCreated;
DetUpdated=r.DetUpdated;
RowCreated=r.RowCreated;
RowUpdated=r.RowUpdated;
//SpRow
id_t=r.id_t;
idp_t=r.idp_t;
G_Obd_t=r.G_Obd_t;
V_Obd_t=r.V_Obd_t;
action_row=r.action_row;
action_det=r.action_det;
action_row_t=r.action_row_t;
inBase=r.inBase;
return *this;
}
bool   	SpRow::operator ==	(const SpRow &r)
{
if (this==&r) {return true;}
if (//Obd
	id==r.id&&
	SpRazd==r.SpRazd&&
	G_Obd==r.G_Obd&&
	V_Obd==r.V_Obd&&
	Name==r.Name&&
	SpRazdName==r.SpRazdName&&
	//TreeRow
	idparent==r.idparent&&
	pp==r.pp&&
	ppp==r.ppp&&
	ei==r.ei&&
	state==r.state&&
	UserID==r.UserID&&
	V_Obu==r.V_Obu&&
	G_Obu==r.G_Obu&&
	format==r.format&&
	pos==r.pos&&
	prim==r.prim&&
	zona==r.zona&&
	ppName==r.ppName&&
	eiName==r.eiName&&
	User==r.User&&
	CondName==r.CondName&&
	DetCreator==r.DetCreator&&
	DetUpdater==r.DetUpdater&&
	RowCreator==r.RowCreator&&
	RowUpdater==r.RowUpdater&&
	kol==r.kol&&
	Arhive==r.Arhive&&
	Force==r.Force&&
	CanChild==r.CanChild&&
	Accept==r.Accept&&
	DetCreated==r.DetCreated&&
	DetUpdated==r.DetUpdated&&
	RowCreated==r.RowCreated&&
	RowUpdated==r.RowUpdated&&
	//SpRow
	id_t==r.id_t&&
	idp_t==r.idp_t&&
	G_Obd_t==r.G_Obd_t&&
	V_Obd_t==r.V_Obd_t&&
	action_row==r.action_row&&
	action_det==r.action_det&&
	action_row_t==r.action_row_t&&
	inBase==r.inBase
	)
	{
	return true;
	}
return false;
}
bool   	SpRow::operator !=	(const SpRow &r)
{
if (this==&r) {return false;}
if (//Obd
	id==r.id&&
	SpRazd==r.SpRazd&&
	G_Obd==r.G_Obd&&
	V_Obd==r.V_Obd&&
	Name==r.Name&&
	SpRazdName==r.SpRazdName&&
	//TreeRow
	idparent==r.idparent&&
	pp==r.pp&&
	ppp==r.ppp&&
	ei==r.ei&&
	state==r.state&&
	UserID==r.UserID&&
	V_Obu==r.V_Obu&&
	G_Obu==r.G_Obu&&
	format==r.format&&
	pos==r.pos&&
	prim==r.prim&&
	zona==r.zona&&
	ppName==r.ppName&&
	eiName==r.eiName&&
	User==r.User&&
	CondName==r.CondName&&
	DetCreator==r.DetCreator&&
	DetUpdater==r.DetUpdater&&
	RowCreator==r.RowCreator&&
	RowUpdater==r.RowUpdater&&
	kol==r.kol&&
	Arhive==r.Arhive&&
	Force==r.Force&&
	CanChild==r.CanChild&&
	Accept==r.Accept&&
	DetCreated==r.DetCreated&&
	DetUpdated==r.DetUpdated&&
	RowCreated==r.RowCreated&&
	RowUpdated==r.RowUpdated&&
	//SpRow
	id_t==r.id_t&&
	idp_t==r.idp_t&&
	G_Obd_t==r.G_Obd_t&&
	V_Obd_t==r.V_Obd_t&&
	action_row==r.action_row&&
	action_det==r.action_det&&
	action_row_t==r.action_row_t&&
	inBase==r.inBase
	)
	{
	return false;
	}
return true;
}

void 	SpRow::SetObd (const String &r)
{
//тут несколько вариантов действий
if (action_row!="del")
	{
	if (V_Obd!=r&&G_Obd!=r)
		{
		if (id>0&&inBase)
			{//1 деталь есть в базе   и строка есть в базе
			int _id=Get_id(r);
			if (_id)//проверить на наличие в базе обозначения на которое меняется
				{//если есть то замена детали
				Load_det(_id);
				if (action_row!="ins")
					{
					action_row="upd";
					}
				}else
				{//если нет то замена только обозначения
				if (Accept)
					{//замена обозначения
					Change_obd(r);
					}
				}
			}else
			{//2 детали нет в базе
			//замена обозначения
			Change_obd(r);
			}
		}
	}
}
void	SpRow::SetObu (const String &r)
{
if (V_Obu!=r&&G_Obu!=r)
	{
	V_Obu=GostToVin(r);
	G_Obu=VinToGost(r);
	}
}
void	SpRow::Set_ID (void)
{
id=Get_id(V_Obd); //используютсфя при сохранении для обновления данных о своем ид
}
void	SpRow::Set_IDp(const int &r)
{ //ограничение на удаляемые строки нет, но если ид изначально 0 то сохранить проступающий ид как первоначальный с ним будет работать алгоритм удаления
//idparent=Get_id(V_Obu);
idparent=r; //групповой алгоритм обработки эффективнее
}
void	SpRow::Correct_obd(void)
{
if (V_Obd==""&&V_Obd_t!="")
	{
	V_Obd=V_Obd_t;
	G_Obd=G_Obd_t;
	}
}
void 	SpRow::Set_pp 			(const int &r)
{
if (action_row!="del")
	{
	if (pp!=r)
		{
		String kod=(String)r;
		while (kod.Length()<2)
			{
			kod="0"+kod;
			}
		TADOQuery *rez=DB->SendSQL("Call catalogs.Get_ppName('"+kod+"')");
		if (rez&&rez->RecordCount)
			{
			pp=r;
			ppName=rez->FieldByName("ppName")->Value;
			if (action_det!="ins")
				{
				action_det="upd";
				}
			}
         delete rez;
		}
	}
}
void 	SpRow::Set_ei 			(const int &r)
{
if (action_row!="del")
	{
	if (ei!=r)
		{
		String kod=(String)r;
		while (kod.Length()<3)
			{
			kod="0"+kod;
			}
		TADOQuery *rez=DB->SendSQL("Call catalogs.Get_eiName('"+kod+"')");
		if (rez&&rez->RecordCount)
			{
			eiName=rez->FieldByName("eiName")->Value;
			ei=r;
			if (action_row!="ins")
				{
				action_row="upd";
				}
			}
		delete rez;
		}
	}
}
void 	SpRow::Set_ppp 		(const int &r)
{
if (action_row!="del")
	{
	if (ppp!=r)
		{
		ppp=r;
		if (action_row!="ins")
			{
			action_row="upd";
			}
		}
	}
}
void 	SpRow::Set_Name 		(const String &r)
{
if (action_row!="del")
	{
	if (Name!=r)
		{
		Name=r;
		if (action_det!="ins")
			{
			action_det="upd";
			}
		}
	}
}
void 	SpRow::Set_SpRazd  (const int &idr,const String &r)
{
if (action_row!="del")
	{
	if (SpRazd!=idr||SpRazdName!=r)
		{
		SpRazd=idr;
        SpRazdName=r;
		if (action_det!="ins")
			{
			action_det="upd";
			}
		}
	}
}
void 	SpRow::Set_format      (const String &r)
{
if (action_row!="del")
	{
	if (format!=r)
		{
		format=r;
		if (action_det!="ins")
			{
			action_det="upd";
			}
		}
	}
}
void 	SpRow::Set_pos         (const String &r)
{
if (action_row!="del")
	{
	if (pos!=r)
		{
		pos=r;
		if (action_row!="ins")
			{
			action_row="upd";
			}
		}
	}
}
void 	SpRow::Set_prim        (const String &r)
{
if (action_row!="del")
	{
	if (prim!=r)
		{
		prim=r;
		if (action_row!="ins")
			{
			action_row="upd";
			}
		}
	}
}
void 	SpRow::Set_zona        (const String &r)
{
if (action_row!="del")
	{
	if (zona!=r)
		{
		zona=r;
		if (action_row!="ins")
			{
			action_row="upd";
			}
		}
	}
}
void 	SpRow::Set_kol         (const double &r)
{
if (action_row!="del")
	{
	if (kol!=r)
		{
		kol=r;
		if (action_row!="ins")
			{
			action_row="upd";
			}
		}
	}
}

void	SpRow::Load_det	(const int &_id)
{
TADOQuery *rez=DB->SendSQL("Call constructions.LoadDet('"+(String)_id+"','"+(String)LUser+"')");
if (rez&&rez->RecordCount)
	{
	id=rez->FieldByName("idchild")->Value;				//OBD
	SpRazd=rez->FieldByName("razdSPID")->Value;			//OBD
	pp=rez->FieldByName("pp")->Value;					//TreeRow
	state=rez->FieldByName("state")->Value;				//TreeRow
	UserID=rez->FieldByName("UserID")->Value;			//TreeRow

	V_Obd=rez->FieldByName("obd")->Value;				//OBD
	G_Obd=VinToGost(V_Obd);								//OBD

	Name=rez->FieldByName("name")->Value;				//OBD
	format=rez->FieldByName("format")->Value;           //treerow
	SpRazdName=rez->FieldByName("Razdname")->Value;		//OBD
	ppName=rez->FieldByName("ppname")->Value;			//TreeRow
	User=rez->FieldByName("User")->Value;				//TreeRow
	CondName=rez->FieldByName("CondName")->Value;		//TreeRow

	DetCreator=rez->FieldByName("DetCreator")->Value;	//TreeRow
	DetUpdater=rez->FieldByName("DetUpdater")->Value;	//TreeRow

	Arhive=rez->FieldByName("arhive")->Value;			//TreeRow
	Force=false;										//TreeRow
	CanChild=rez->FieldByName("CanChild")->Value;		//TreeRow
	Accept=rez->FieldByName("Accept")->Value;			//TreeRow

	DetCreated=rez->FieldByName("DetCreated")->Value.operator TDateTime();		//TreeRow
	DetUpdated=rez->FieldByName("DetUpdated")->Value.operator TDateTime();		//TreeRow
	action_det="no";
	}
}
void 	SpRow::Change_obd	(const String &obd)
{
V_Obd=GostToVin(obd);
G_Obd=VinToGost(V_Obd);
id=Get_id(obd);
if (!id)
	{
	action_det="ins";
	}else
	{
	if (action_det!="del")
		{
		action_det="upd";
		}
	}
}
int 	SpRow::Get_id	(const String &obd)
{
int toret=0;
TADOQuery *rez=DB->SendSQL("Call constructions.Get_id('"+GostToVin(obd)+"')");
if (rez&&rez->RecordCount)
	{
	toret=rez->FieldByName("id")->Value;
	}
return toret;
}
void	SpRow::Set_ei		(void)
{
//TADOQuery *rez=DB->SendSQL("Call sklad.Get_Material('"+V_Obd+"')");
//if (rez&&rez->RecordCount&&rez->FieldByName("ei")->Value.operator int()!=0)
//	{
//	ei=rez->FieldByName("ei")->Value;
//	eiName=rez->FieldByName("eiName")->Value;
//	}else
//	{
//	delete rez;
TADOQuery *	rez=DB->SendSQL("select kodei as ei, snameei as einame from catalogs.dimensionality where nameei like 'штук_'");
	if (rez&&rez->RecordCount)
		{
		ei=rez->FieldByName("ei")->Value;
		eiName=rez->FieldByName("eiName")->Value;
		}
//	}
//delete rez;
}
//_____________________________________________________________________________________
bool 	SpRow::UpdateVal 	(void)
{
return Load_row();
}
bool 	SpRow::Load_det	(void)
{
Load_det(id_t);
id_t=id;
return true;
}
bool 	SpRow::Load_row	(void)
{
bool result=false;
TADOQuery *rez=DB->SendSQL("Call UpdateRowInfo('"+(String)idp_t+"','"+(String)id_t+"','"+(String)LUser+"')");
if (rez&&rez->RecordCount)
	{
	idparent=rez->FieldByName("idparent")->Value;       //TreeRow
	id=rez->FieldByName("idchild")->Value;				//OBD
	SpRazd=rez->FieldByName("razdSPID")->Value;			//OBD
	prim=rez->FieldByName("prim")->Value;
	pos=rez->FieldByName("pos")->Value;
	ppp=rez->FieldByName("ppp")->Value;
	pp=rez->FieldByName("pp")->Value;					//TreeRow
	state=rez->FieldByName("state")->Value;				//TreeRow
	UserID=rez->FieldByName("UserID")->Value;			//TreeRow
	ei=rez->FieldByName("ei")->Value;

	kol=rez->FieldByName("kol")->Value;

	V_Obd=rez->FieldByName("obd")->Value;				//OBD
	G_Obd=VinToGost(V_Obd);								//OBD
	V_Obu=rez->FieldByName("obu")->Value;
	G_Obu=VinToGost(V_Obu);

	zona=rez->FieldByName("zona")->Value;

	Name=rez->FieldByName("name")->Value;				//OBD
	format=rez->FieldByName("format")->Value;           //treerow
	eiName=rez->FieldByName("eiName")->Value;
	SpRazdName=rez->FieldByName("Razdname")->Value;		//OBD
	ppName=rez->FieldByName("ppname")->Value;			//TreeRow
	User=rez->FieldByName("User")->Value;				//TreeRow
	CondName=rez->FieldByName("CondName")->Value;		//TreeRow

	DetCreator=rez->FieldByName("DetCreator")->Value;	//TreeRow
	DetUpdater=rez->FieldByName("DetUpdater")->Value;	//TreeRow
	RowCreator=rez->FieldByName("RowCreator")->Value;
	RowUpdater=rez->FieldByName("RowUpdater")->Value;

	Arhive=rez->FieldByName("arhive")->Value;			//TreeRow
	Force=false;										//TreeRow
	CanChild=rez->FieldByName("CanChild")->Value;		//TreeRow
	Accept=rez->FieldByName("Accept")->Value;			//TreeRow

	DetCreated=rez->FieldByName("DetCreated")->Value.operator TDateTime();		//TreeRow
	DetUpdated=rez->FieldByName("DetUpdated")->Value.operator TDateTime();		//TreeRow
	RowUpdated=rez->FieldByName("RowUpdated")->Value.operator TDateTime();
	RowCreated=rez->FieldByName("RowCreated")->Value.operator TDateTime();
	action_det="no";
	action_row="no";

	result=true;
	}
delete rez;
return result;
}
