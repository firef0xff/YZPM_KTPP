#pragma hdrstop
#include "Z_Data.h"
#pragma package(smart_init)

Z_Data::Z_Data(int _z1,int _z2,int _z3,int _z4):z1(_z1),z2(_z2),z3(_z3),z4(_z4)
{
u=(z1/z2)*(z3/z4);
}
Z_Data::Z_Data(const Z_Data &r):z1(r.z1),z2(r.z2),z3(r.z3),z4(r.z4),u(r.u)
{}
Z_Data::~Z_Data(void)
{

}
Z_Data& Z_Data::operator =	(const Z_Data &r)
{
if (this==&r) {return *this;}
z1=r.z1;
z2=r.z2;
z3=r.z3;
z4=r.z4;
u=r.u;
return *this;
}
bool 	Z_Data::operator ==	(const Z_Data &r)
{
if (this==&r){return true;}
if (z1==r.z1&&
	z2==r.z2&&
	z3==r.z3&&
	z4==r.z4&&
	u==r.u)
	{
	return true;
	}
	else
	{
	return false;
	}
}
bool 	Z_Data::operator !=	(const Z_Data &r)
{
if (this==&r){return false;}
if (z1==r.z1&&
	z2==r.z2&&
	z3==r.z3&&
	z4==r.z4&&
	u==r.u)
	{
	return false;
	}
	else
	{
	return true;
	}
}
