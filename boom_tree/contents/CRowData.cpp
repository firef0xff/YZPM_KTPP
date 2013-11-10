#pragma hdrstop

#include "CRowData.h"
#pragma package(smart_init)
        CRowData::CRowData(const bool &_MassAction,        const int &_id,const int &_CurrState,
            const int &_NextState,            const int &_PrevState,
            const String &_text,            const String &_CurrStateName,
            const String &_NextStateName,    const String &_PrevStateName,
            const bool &_Accept,    const bool &_Arhive,    const bool &_NextAccept,
            const bool &_PrevAccept):MassAction(_MassAction)
{
count++;

CurrState=_CurrState;
CurrStateName=_CurrStateName;
if (!MassAction)
    {
    id=_id;
    text=_text;
    }else{id=-1;text="";}
Accept=_Accept;
Arhive=_Arhive;
NextAccept=_NextAccept;
PrevAccept=_PrevAccept;
NextState=_NextState;
PrevState=_PrevState;
NextStateName=_NextStateName;
PrevStateName=_PrevStateName;
TurnCurrState();
}
        CRowData::~CRowData(void)
{
count--;
}
void     CRowData::SetNextState(const int &StateID,const String &StateName,const bool &StateAccept)
{
NextAccept=StateAccept;
NextStateName=StateName;
NextState=StateID;
}
void     CRowData::SetPrevState(const int &StateID,const String &StateName,const bool &StateAccept)
{
PrevAccept=StateAccept;
PrevStateName=StateName;
PrevState=StateID;
}
bool     CRowData::TurnCurrState(void)
{
SelectedState=CurrState;
SelectedStateName=CurrStateName;
SelectedAccept=Accept;
return true;
}
bool     CRowData::TurnNextState(void)
{
if (NextState>0)
    {
    SelectedState=NextState;
    SelectedStateName=NextStateName;
    SelectedAccept=NextAccept;
    }else
    {
    return false;
    }
return true;
}
bool     CRowData::TurnPrevState(void)
{
if (PrevState>0)
    {
    SelectedState=PrevState;
    SelectedStateName=PrevStateName;
    SelectedAccept=PrevAccept;
    }else
    {
    return false;
    }
return true;
}
String     CRowData::GetText(void)
{
if (MassAction)
    {
    return CurrStateName;
    }else
    {
    return text;
    }
}