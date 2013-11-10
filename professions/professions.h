#ifndef professionsH
#define professionsH
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>

#include "SQL.h"
#include "functions.h"
#include <Buttons.hpp>
#include <Grids.hpp>
#include <ExtCtrls.hpp>
class TProfessinos : public TForm
{
__published:	// IDE-managed Components
	TStringGrid *SG1;
	TBitBtn *cancel;
	TBitBtn *ok;
	TComboBox *CB;
	TPanel *Panel2;
	TStringGrid *SG2;
	TSplitter *Splitter1;
	void __fastcall CBClick(TObject *Sender);
	void __fastcall okClick(TObject *Sender);
	void __fastcall SG2SelectCell(TObject *Sender, int ACol, int ARow, bool &CanSelect);

private:
cSQL *const DB;
static int filter;
void init (void);
String prof;
public:
	__fastcall TProfessinos(TComponent* Owner,cSQL *db,bool ReadOnly);
String Get_prof(void)const{return prof;}
};
int TProfessinos::filter=1;
#endif
