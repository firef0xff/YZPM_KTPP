//---------------------------------------------------------------------------

#ifndef LocationH
#define LocationH
//---------------------------------------------------------------------------

#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include "SQL.h"
//---------------------------------------------------------------------------
class TLocationForm : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TEdit *_eLocationCab;
	TButton *_bChangeLocation;
	TLabel *Label2;
	TEdit *_eLocationStack;
	TLabel *Label3;
	TEdit *_eLocationRack;
	void __fastcall _bChangeLocationClick(TObject *Sender);
private:	// User declarations
	cSQL * DB;
	String SQL;
public:		// User declarations
	__fastcall TLocationForm(TComponent* Owner, int id,cSQL *db);
};
//---------------------------------------------------------------------------
extern PACKAGE TLocationForm *LocationForm;
//---------------------------------------------------------------------------
#endif
