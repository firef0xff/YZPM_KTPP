//---------------------------------------------------------------------------


#pragma hdrstop

#include "SPROW.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
		SpRow::SpRow				(cSQL * r)
{
DB=r;
Clear();
}
void 	SpRow::Clear				(void)
{
format="";
zona="";
pos="";
obozn="";
name="";
kol="";
kod="";
prim="";
ObdFirst="";
ppp=0;
PresenceInBase=false;
SPrazd=0;
id="";
}
SpRow & SpRow::operator =			(const SpRow &r)
{
if (this==&r) {return *this;}
this->format=r.format;
this->zona=r.zona;
this->pos=r.pos;
this->obozn=r.obozn;
this->name=r.name;
this->kol=r.kol;
this->kod=r.kod;
this->prim=r.prim;
this->ObdFirst=r.ObdFirst;
this->PresenceInBase=r.PresenceInBase;
this->DB=r.DB;
this->SPrazd=r.SPrazd;
this->ppp=r.ppp;
this->id=r.id;
return *this;
}
SpRow & SpRow::operator +			(const SpRow &r)
{
if (this==&r) {return *this;}
this->format=this->format+r.format;
this->zona=this->zona+r.zona;
this->pos=this->pos+r.pos;
this->obozn=this->obozn+r.obozn;
this->name=this->name+r.name;
this->kol=this->kol+r.kol;
this->kod=this->kod+r.kod;
this->prim=this->prim+r.prim;
this->ObdFirst="";
this->PresenceInBase=false;
this->ppp=0;
this->id="";
return *this;
}
void  	SpRow::SetObozn				(String r)
{
if (ObdFirst=="")// цеплянеи исходного обозначения
	{
	if (obozn=="")
		{
		ObdFirst=r;
		}else
		{
		ObdFirst=obozn;
		}
	}
// восстановление на исходное если обозначение стерто
if (r=="")
	{
	obozn=ObdFirst;
	}else
	{
	obozn=r;
	}
// идентификатор получается в ходе проверки на наличие в базе
PresenceInBase=CheckPresenceInBase();
}
bool 	SpRow::CheckPresenceInBase	(void)
{
String sql="select obd from det_names where obd='"+GostToVin(obozn)+"'";
TADOQuery *rez=DB->SendSQL(sql);
if (rez->RecordCount)
	{ // обновление значения идентификатора в случае если obozn=obdfirst
	if (obozn==ObdFirst)
		{
		id=rez->FieldByName("obd")->Value;
		}
	delete rez;
	return true;
	}
delete rez;
return false;
}
