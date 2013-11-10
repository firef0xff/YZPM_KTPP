//---------------------------------------------------------------------------

#ifndef GTUSdialogH
#define GTUSdialogH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>

#include "SQL.h"
#include <Buttons.hpp>

#ifndef nullptr
	#define nullptr 0
#endif
//---------------------------------------------------------------------------
class TGTUSGroupSelector : public TForm
{
__published:	// IDE-managed Components
	TComboBox *cbGroups;
	TBitBtn *BitBtn2;
	TBitBtn *BitBtn1;
	TLabel *Label3;
	void __fastcall BitBtn1Click(TObject *Sender);
private:	// User declarations
	cSQL *DB;
public:		// User declarations
	__fastcall TGTUSGroupSelector(TComponent* Owner,cSQL *db,String Table,String param);
	String Name;
	int ID;
};

#endif
