//---------------------------------------------------------------------------

#ifndef TechnologyViewH
#define TechnologyViewH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>

#include "Obd.h"
#include "DtInfo.h"
#include "OperRow.h"
//---------------------------------------------------------------------------
class TTechView : public TFrame
{
__published:	// IDE-managed Components
private:	// User declarations

public:		// User declarations
	__fastcall TTechView(TComponent* Owner,TWinControl *_p,String _name, int user,cSQL *db);
};
#endif
