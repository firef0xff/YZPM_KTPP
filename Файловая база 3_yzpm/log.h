//---------------------------------------------------------------------------

#ifndef logH
#define logH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "SQL.h"
//---------------------------------------------------------------------------
class TLogForm : public TForm
{
__published:	// IDE-managed Components
	TMemo *Memo1;
private:	// User declarations
public:		// User declarations
	__fastcall TLogForm(TComponent* Owner,vector <String> log);
};
#endif
