#pragma hdrstop

#include "Obd.h"
#pragma package(smart_init)



		Obd::Obd	(cSQL *const db):DB(db)
{
count++;
init();
}
		Obd::Obd	(cSQL *const db,const String &_obd):DB(db)
{
count++;
SetObd(_obd);
}
		Obd::Obd	(cSQL *db,const int &_id):DB(db)
{
count++;
SetId(_id);
}
		Obd::Obd	(const Obd &r):DB(r.DB)
{
count++;
id=r.id;
SpRazd=r.SpRazd;
G_Obd=r.G_Obd;
V_Obd=r.V_Obd;
Name=r.Name;
SpRazdName=r.SpRazdName;
}
		Obd::~Obd	(void)
{
count--;
}


Obd & 	Obd::operator =	(const Obd &r)
{
if (this==&r) {return *this;}
id=r.id;
SpRazd=r.SpRazd;
G_Obd=r.G_Obd;
V_Obd=r.V_Obd;
Name=r.Name;
SpRazdName=r.SpRazdName;
return *this;
}
bool 	Obd::operator ==(const Obd &r)
{
if (this==&r) {return true;}
if (id==r.id&&
	SpRazd==r.SpRazd&&
	G_Obd==r.G_Obd&&
	V_Obd==r.V_Obd&&
	Name==r.Name&&
	SpRazdName==r.SpRazdName)
	{
	return true;
	}
return false;
}
bool 	Obd::operator !=(const Obd &r)
{
if (this==&r) {return false;}
if (id==r.id&&
	SpRazd==r.SpRazd&&
	G_Obd==r.G_Obd&&
	V_Obd==r.V_Obd&&
	Name==r.Name&&
	SpRazdName==r.SpRazdName)
	{
	return false;
	}
return true;
}


void 	Obd::init 		(void)
{
id=-1;
SpRazd=-1;
G_Obd="";
V_Obd="";
Name="";
SpRazdName="";
}
bool 	Obd::Get_Val (char type)
{
String sql="";
switch (type)
	{
	case 0:{sql="call constructions.Get_id('"+V_Obd+"')";break;}
	case 1:{sql="call constructions.Get_obd('"+String(id)+"')";break;}
	default:return false;
	}
TADOQuery *rez=DB->SendSQL(sql);
if (rez&&rez->RecordCount)
	{
	Name=rez->FieldByName("namd")->Value;
	id=rez->FieldByName("id")->Value;
	V_Obd=GostToVin(rez->FieldByName("obd")->Value);
	G_Obd=VinToGost(V_Obd);
	SpRazd=rez->FieldByName("razdSPID")->Value;
	SpRazdName=rez->FieldByName("Razdname")->Value;
	delete rez;
	}else
	{
	init();
	delete rez;
	}
return CanUse();
}


bool   	Obd::SetObd    	(const String &r)
{
if (ItTrueClassName())
	{
	V_Obd=GostToVin(r);
	return Get_Val (0);
	}
return false;
}
bool  	Obd::SetId   	(const int &ID)
{
if (ItTrueClassName())
	{
	id=ID;
	return Get_Val (1);
	}
return false;
}
bool 	Obd::SetData 	(const int &_id,const int &_SpRazd,const String &_Obd,const String &_Name,const String &_SpRazdName)
{
if (ItTrueClassName())
	{
	id=_id;
	SpRazd=_SpRazd;
	G_Obd=VinToGost(_Obd);
	V_Obd=GostToVin(_Obd);
	Name=_Name.Trim();
	SpRazdName=_SpRazdName.Trim();
	}
return CanUse();
}
