//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TSimple_fraction *Simple_fraction;
//---------------------------------------------------------------------------
__fastcall TSimple_fraction::TSimple_fraction(TComponent* Owner)
	: TForm(Owner)
{
db=new cSQL(ADOConnection1);
gears.push_back(20);
gears.push_back(30);
gears.push_back(46);
gears.push_back(19);
gears.push_back(67);
gears.push_back(23);
gears.push_back(35);
gears.push_back(45);
gears.push_back(34);
gears.push_back(63);
gears.push_back(12);
gears.push_back(43);
gears.push_back(42);
gears.push_back(87);
gears.push_back(68);
gears.push_back(65);
gears.push_back(75);
gears.push_back(59);
gears.push_back(79);
gears.push_back(37);
gears.push_back(26);
gears.push_back(33);
gears.push_back(49);
gears.push_back(59);
gears.push_back(61);
gears.push_back(28);
gears.push_back(36);
gears.push_back(51);
gears.push_back(92);
gears.push_back(84);
gears.push_back(52);
gears.push_back(56);
gears.push_back(42);
gears.push_back(11);
gears.push_back(64);
int count=gears.size();
results.clear();
int cnt=0;
for (int n=0; n<count; n++)
	{
	for (int m=0; m<count; m++)
		{
		if (n!=m)
			{
			for (int i=0; i<count; i++)
				{
				if (i!=m&&i!=n)
					{
					for (int j=0; j<count; j++)
						{
						if (j!=i&&j!=m &&j!=n)
							{
							Z_Data *t=new Z_Data(gears[n],gears[m],gears[i],gears[j]);
							results.push_back(t);
							}
						}
					}
				}
			}
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TSimple_fraction::isxKeyPress(TObject *Sender, wchar_t &Key)
{
TLabeledEdit * t=(TLabeledEdit *)Sender;
if (t)
	{
	if (isdigit(Key)||Key=='.'||Key==',')
		{
		if (Key==',')
			{
			Key='.';
			}
		if (Key=='.'&&t->Text.Pos("."))
			{
			Key=0;
			}
		}else
		{
        Key=0;
		}
	}
}
void 	TSimple_fraction::Get_NumbsLines(const String &str)
{//функция для получения разложения по числам
//получение числителя и знаменателя
String chisl,znam="1";
chisl=str;
while (chisl[1]=='0')
	{
	chisl.Delete(1,1);
	}
while (chisl.Pos(".")&&chisl.SubString(chisl.Length(),1)=="0")
	{
	chisl.Delete(chisl.Length(),1);
	}
int pos=chisl.Pos(".");
if (!pos) {pos=chisl.Length();}
while (znam.Length()<=(chisl.Length()-pos))
	{
	znam=znam+"0";
	}
chisl.Delete(chisl.Pos("."),1);
Get_multipliers(chisl);
Get_multipliers(znam);
//упрощение дроби
int pos_start=1,pos_end=1;
while (pos_end<=chisl.Length())
	{
	String Chislo="";
	int length=chisl.Length();
	if (chisl[pos_end]!='*')
		{
		pos_end++;
		if (pos_end==length-1)
			{
			Chislo=chisl.SubString(pos_start,pos_end+1-pos_start);
			pos_end=length;
			}
		}else
		{
		Chislo=chisl.SubString(pos_start,pos_end-pos_start);
		pos_start=pos_end+1;
		pos_end=pos_start;
		}
	if (Chislo!="")
		{
		while (znam.Pos(Chislo)&&chisl.Pos(Chislo))
			{
			znam.Delete(znam.Pos(Chislo),Chislo.Length());
			chisl.Delete(chisl.Pos(Chislo),Chislo.Length());
			pos_start=1;
			pos_end=1;
			}
		}
	}
while (znam.Pos("**"))
	{
	znam=Replace(znam,"**","*");
	}
while (chisl.Pos("**"))
	{
	chisl=Replace(chisl,"**","*");
	}
while (chisl[1]=='*')
	{
	chisl.Delete(1,1);
	}
while (znam[1]=='*')
	{
	znam.Delete(1,1);
	}
//вывод результата
Chislitel->Text=chisl;
Znamenatel->Text=znam;
}
void 	TSimple_fraction::Get_multipliers(String &str)
{// функция на разложение на множетили

unsigned long int isxchs=str.ToInt();
String rez="";
for (unsigned long int k=Get_Next_simple_numb(1); k<isxchs; k=Get_Next_simple_numb(k))
	{
	while (!(isxchs%k))
		{
		isxchs=isxchs/k;
		rez=rez+String(k)+"*";
		}
	}

if (rez.Pos("*"))
	{
	if (isxchs!=1)
		{
		rez=rez+String(isxchs);
		}else
		{
		rez.Delete(rez.Length(),1);
		}
	}else
	{
	rez=isxchs;
	}
str=rez;
}
unsigned long int 	TSimple_fraction::Get_Next_simple_numb(const unsigned long int &last)
{// функция получения следующего простого числа
static vector <unsigned long int> simples;
if (!simples.size())
	{
	simples.push_back(2);
	return 2;
	}
static unsigned long int dgt(2);
if (last>=dgt)
	{
	bool itSimple=false;
	while (itSimple==false)
	{
	dgt++;
	for (int i=0; i<simples.size(); i++)
		{
		unsigned long int d=simples[i];
		if (dgt!=d&&!(dgt%d))
			{
			itSimple=false;
			break;
			}//сломать цикл т.к. число не простое
			else
			{
			itSimple=true;
			}//считаем число простым и продолжаем проверку
		}
	}
	simples.push_back(dgt);
	return dgt;
	}else
	{
	if (last==1)
		{
		return simples[0];
		}else
		{
		for (int i=0; i<simples.size(); i++)
			{
			unsigned long int d=simples[i];
			if (last==d&&(i+1<simples.size()))
				{
				return simples[i+1];//вернуть следующее за последним число
				}
			}
		}
	}
}
void __fastcall TSimple_fraction::Label1Click(TObject *Sender)
{
Get_NumbsLines(isx->Text);
}
//---------------------------------------------------------------------------

