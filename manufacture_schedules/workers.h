//---------------------------------------------------------------------------

#ifndef workersH
#define workersH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>

#include "SQL.h"
#include <ActnPopup.hpp>
#include <Menus.hpp>
#include <PlatformDefaultStyleActnCtrls.hpp>
#include <string>
#include "sstream.h"
//---------------------------------------------------------------------------
class TWorkersSettings : public TFrame
{
__published:	// IDE-managed Components
	TPanel *Panel2;
	TPanel *Panel1;
	TStringGrid *sgGroups;
	TPanel *Panel3;
	TStringGrid *sgWorkers;
	TPanel *Panel4;
	TPopupActionBar *PAB1;
	TPopupActionBar *PAB2;
	TMenuItem *N1;
	TMenuItem *N2;
	TMenuItem *N3;
	TMenuItem *N4;
	TMenuItem *N5;
	TMenuItem *N6;
	void __fastcall sgGroupsSelectCell(TObject *Sender, int ACol, int ARow, bool &CanSelect);
	void __fastcall N1Click(TObject *Sender);
	void __fastcall N6Click(TObject *Sender);
	void __fastcall N2Click(TObject *Sender);
	void __fastcall N3Click(TObject *Sender);
	void __fastcall N4Click(TObject *Sender);
	void __fastcall N5Click(TObject *Sender);


private:	// User declarations
	cSQL *DB;
	const int    &LUser;  //идентификатор пользователя

    void LoadGroups(void);
    void LoadWorkers(std::string group_id = "");
public:		// User declarations
	void OnShow(void);
	__fastcall TWorkersSettings(TComponent* Owner,cSQL *db,const int&_LUser);
};

#endif
