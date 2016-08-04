//---------------------------------------------------------------------------

#ifndef otchetnostH
#define otchetnostH
#include "SQL.h"
#include "Excel.h"
#include "params.h"
#include "kol_det.h"
#include "functions.h"
#include <ADODB.hpp>
#include <Dialogs.hpp>
#include <DB.hpp>
#include "komplect.h"
#include "pp_start_params.h"
#include "trb_params.h"
typedef struct
{
int Row;
int Rowmax;
}Row_range;
typedef struct
{
String obd;
String namd;
String dnte;
String mater;
String ei;
String masd;
String obm;
String vz;
String razz;
String kdz;
String masz;
String nrm;
String kim;
}detinfo;
class cReports
{
    public:
        cReports        (cSQL *r);
        ~cReports        ();

String user;
bool    CreateReport    (int type, String param);
    private:
cSQL *DB;
TPP_params *pp_params;
TTrbOptions *trb_params;
void    Showlist        (TADOQuery *rez);
void      SQL_To_XL       (TADOQuery *rez);

void     PlanPrDet        (String obd,String kol);
int     AddML            (String obd,String name,String name_mat,String prof_mat,int kol,int Lcount,int mlnumber);
int     AddReport        (String obd,String kol,int Lcount);
void    SaveFile        (String file_name,String file_ext, int Lcount);
void    OpenTemplate    (AnsiString templ);
void    TrimFile        (String file_name,String file_ext,String templ, int &Lcount, int max_list_no);

void      ShowDetInside    (TADOQuery *rez);

void    ShowSostIzd        (String obd);
void    SostIzd            (TADOQuery *rez,int &row, int lvl, int base_kol);

void      Mat_report        (TADOQuery *rez,String obd);

void      Texnologic            (String obd);
void      Tex_format_string    (int type,int Row);
void     Tex_new_list        (detinfo dt,int &Lcount,Row_range &r);

void    Mat_Ved_Komplect    (String obd,String zak,int kol);
void    Mat_Ved_razd        (TADOQuery *rez,const String &obd,const String &zak,const String &Title,int &list);

void    Trebovanie_Materialov    (String obd,String zak,int kol);

void    Boiler_Assemblies    (String obd,String zak,int kol,String ceu,String part);
void    Operation_Timing    (String obd,String zak,int kol,String ceu,String part);//140006
void    Cpu_Operation_Timing(String obd,String zak,int kol,String ceu,String part);//1400061
String     Get_Rascex        (String obd);

void    OriginDets			(String obd);

public:
void    WordWrap        (std::vector<String> &out,String in,const int max_len,String delimeter=" ");
    Tkoldet *koldet;
    Tparametr *parametr;
    String Templates;

    cExcel *XL;
};

#endif
