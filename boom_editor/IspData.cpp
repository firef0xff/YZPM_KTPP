//---------------------------------------------------------------------------
#pragma hdrstop

#include "IspData.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
	IspData::IspData()
{
id=0;
main_isp=false;
selected=false;
O_V_Obd="";
G_Obd="";
V_Obd="";
}
void 		IspData::Set_Obd 		(const String &r)
{
V_Obd=GostToVin(r);
G_Obd=VinToGost(r);
if (O_V_Obd=="")
	{
	O_V_Obd=V_Obd;
	}
}