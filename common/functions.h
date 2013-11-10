

#ifndef functionsH
#define functionsH
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Grids.hpp>
#include "SQL.h"

void MkPjDir(String subpart,String part);
String GetDirName (void);
String GetFileName (void);
bool  DeleteDir(AnsiString DirName);

String ekran (String inpstr);
String Replace (String st,String Old,String New);
String Replace (String st,String Old,String New,int pos,int count);
String GetOnlyNum(String st);
bool   ischar (const char ch);
bool   isdigit(const char ch);

String GostToVin(AnsiString Gost);
String GostToInt(AnsiString Gost);
String VinToGost (String Vin);
String GetGostNum(String st);

void AutoWidthSG(TStringGrid *sg,int minwdth=40);
void  SGClear (TStringGrid *SG,int RightOfset=0);

template<typename T>
void shellSort(T a[], long size);
int increment(long inc[], long size);
template<typename T>
void change (T &el1,T &el2);

template<typename T>
void insertSort (T a[], long size);

class Transaction
{
	public:
	Transaction(cSQL *db):commited(false),DB(db)
	{
    	DB->SendCommand("START TRANSACTION");
	}
	~Transaction()
	{
		if (!commited)
		{
			DB->SendCommand("ROLLBACK");
		}
	}
	void Commit(void)
	{
		DB->SendCommand("COMMIT");
		commited = true;
	}
	private:
	bool commited;
	cSQL *DB;
};
#endif