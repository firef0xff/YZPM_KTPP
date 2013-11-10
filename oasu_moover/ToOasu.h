//---------------------------------------------------------------------------

#ifndef ToOasuH
#define ToOasuH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include <Buttons.hpp>
#include "SQL.h"
#include "Excel.h"
#include "Obd.h"
//---------------------------------------------------------------------------
class TOASUtrasfer : public TForm//,public ClassConnector
{
__published:	// IDE-managed Components
	TPageControl *PageControl1;
	TTabSheet *TS3;
	TPanel *Panel1;
	TPanel *Panel3;
	TStringGrid *table;
	TButton *Button1;
	TADOConnection *ADC;
	TRadioGroup *_table;
	void __fastcall _tableClick(TObject *Sender);
	void __fastcall TS3Show(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall SpeedButton1Click(TObject *Sender);

private:	// User declarations
cSQL *DB;
const int &LUser;
static size_t count;
void init_interface(void);
//загрузка и удаление данных
void  Load (const Obd *const det){};
void  Load_sel(Obd *det){};
public:		// User declarations
	__fastcall TOASUtrasfer(TComponent* Owner,int &_LUser,cSQL *db);
	__fastcall TOASUtrasfer(TComponent* Owner,TWinControl *_p,String _name, int &_LUser,cSQL *db);
	__fastcall TOASUtrasfer(TComponent* Owner);
	__fastcall ~TOASUtrasfer(void);
};
size_t TOASUtrasfer::count=0;
#endif
