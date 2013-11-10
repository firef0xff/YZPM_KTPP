//---------------------------------------------------------------------------

#ifndef SPROWH
#define SPROWH
#include "SQL.h"
#include "dircoder.h"
class SpRow
{
public:
bool PresenceInBase;
int SPrazd;
int ppp;
// функции доступа
String 		GetFormat	(void)		{return format.Trim();};
String 		GetZona		(void)		{return zona.Trim();};
String 		GetPos		(void)		{return pos.Trim();};
String 		GetObozn	(void)		{return obozn.Trim();};
String 		GetName		(void)		{return name.Trim();};
String 		GetKol		(void)		{return kol.Trim();};
String 		GetKod		(void)		{return kod.Trim();};
String 		GetPrim		(void)		{return prim.Trim();};
String		GetInitOBD  (void)      {return ObdFirst.Trim();};
String		Getid	 	(void)      {return id;};
void 		SetFormat	(String r)	{format=r;};
void  		SetZona		(String r)	{zona=r;};
void  		SetPos		(String r)	{pos=r;};
void  		SetObozn	(String r);
void  		SetName		(String r)	{name=r;};
void  		SetKol		(String r)	{kol=r;};
void  		SetKod		(String r)	{kod=r;};
void  		SetPrim		(String r)	{prim=r;};
void		ClearObdChanging()		{ObdFirst=obozn;id="";};
// вспомогательные
bool CheckPresenceInBase(void);
// функции операторы /конструкторы
	 SpRow				(cSQL * r);

SpRow & operator = 		(const SpRow &);
SpRow & operator + 		(const SpRow &);
void 	Clear			(void);
private:
// переменные
String format;
String zona;
String pos;
String obozn;
String name;
String kol;
String kod;
String prim;
String ObdFirst;
String id;
cSQL   *DB;
};
#endif
