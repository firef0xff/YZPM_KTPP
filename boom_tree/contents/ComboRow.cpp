#pragma hdrstop
#include "ComboRow.h"
#pragma package(smart_init)
    ComboRow::ComboRow(const int &_StateID,const String &_StateName,const bool &_StateAccept)
{
StateID=_StateID;
StateName=_StateName;
StateAccept=_StateAccept;
}
    ComboRow::~ComboRow(void)
{

}
