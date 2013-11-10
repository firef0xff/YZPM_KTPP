//---------------------------------------------------------------------------

#include <vcl.h>
#include <windows.h>
#include "otchetnost.h"
#include "SQL.h"
#pragma hdrstop
#pragma argsused


int WINAPI DllEntryPoint(HINSTANCE hinst, unsigned long reason, void* lpReserved)
{
    return 1;
}
extern "C" __export  void Init (AnsiString user,cSQL *DB);
extern "C" __export  bool Report (AnsiString type,AnsiString param);
cReports *REPORT;
extern "C" __export  void Init (AnsiString user,cSQL *DB)
{
REPORT=new cReports(DB);
REPORT->user=user;
}
extern "C" __export  bool Report (AnsiString type,AnsiString param)
{
return REPORT->CreateReport(StrToInt(type),param);
}
