#ifndef ClassConnectorH
#define ClassConnectorH
#include "Obd.h"
class ClassConnector
{
public:
	virtual void Load (const Obd *const det)=0;
	virtual void Load_sel(Obd *det)=0;
private:
};
#endif
