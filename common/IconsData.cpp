#pragma hdrstop
#include "IconsData.h"
#pragma package(smart_init)

			IconsData::IconsData(TComponent* Owner):isEmpty(true)
{
IMGList=new TImageList(Owner);
IMGList->Height=24;
IMGList->Width=24;
StateList=new TImageList(Owner);
StateList->Height=24;
StateList->Width=24;
mass.clear();
}
			IconsData::~IconsData(void)
{
delete IMGList;
delete StateList;
mass.clear();
}
void 		IconsData::LoadCollation(int inbase, int InList, bool Accept, int type)
{
collation tmp;
if (GetInList(inbase,Accept,type)==-1)
	{
	tmp.inbase=inbase;
	tmp.InList=InList;
	tmp.Accept=Accept;
	tmp.type=type;
	mass.push_back(tmp);
	}else
	{
	vector<collation>::iterator i;
	for (i=mass.begin(); i!=mass.end(); i++)
		{
		if (i->inbase==inbase&&i->Accept==Accept&&i->type==type)
			{
			i->InList=InList;
			}
		}
	}
isEmpty=false;
}
int 		IconsData::GetInList(int inbase, bool Accept, int type)
{
vector<collation>::iterator i;
for (i=mass.begin(); i!=mass.end(); i++)
	{
	if (i->inbase==inbase&&i->Accept==Accept&&i->type==type)
		{
		return i->InList;
		}
	}
return -1;
}
IconsData & IconsData::operator = (const IconsData &r)
{
if (this==&r) {return *this;}
isEmpty=r.isEmpty;
mass=r.mass;
return *this;
}