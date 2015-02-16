#ifndef functionsH
#define functionsH
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Grids.hpp>
#include <list>
#include <string>
#include "SQL.h"

void MkPjDir(AnsiString subpart,AnsiString part);
AnsiString GetDirName (void);
AnsiString GetFileName (void);
bool  DeleteDir(AnsiString DirName);

AnsiString ekran (AnsiString inpstr);
AnsiString Replace (AnsiString st,AnsiString Old,AnsiString New);
AnsiString Replace (AnsiString st,AnsiString Old,AnsiString New,int pos,int count);
AnsiString GetOnlyNum(String st);
bool   ischar (const char ch);
bool   isdigit(const char ch);

extern bool use_convertation;
AnsiString GostToVin(AnsiString Gost);
AnsiString GostToInt(AnsiString Gost);
AnsiString VinToGost (AnsiString Vin);
AnsiString GetGostNum(AnsiString st);

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
    void Rollback(void)
    {
        DB->SendCommand("ROLLBACK");
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

void    WordWrap        (std::list<std::string> &out,std::string in,const size_t max_len, std::string delimeter);

#endif
