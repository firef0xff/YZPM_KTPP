#ifndef ComboRowH
#define ComboRowH
#include "Classes.hpp"
class ComboRow
{
public:
	ComboRow(const int &_StateID,const String &_StateName,const bool &_StateAccept);
	~ComboRow(void);
int     GetStateID(void)	{return StateID;};
String  GetStateName(void)	{return StateName;};
bool 	GetStateAccept(void){return StateAccept;};
private:
int 	StateID;
String 	StateName;
bool 	StateAccept;
};
#endif
