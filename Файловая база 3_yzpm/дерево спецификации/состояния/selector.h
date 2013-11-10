

#ifndef selectorH
#define selectorH
#include "SQL.h"
#include "IconsData.h"
#include "ComboRow.h"
#include <Buttons.hpp>
#include <Classes.hpp>
#include <Controls.hpp>
#include <ExtCtrls.hpp>
#include <StdCtrls.hpp>

class TStSelect : public TForm
{
__published:	
	TBitBtn *BitBtn1;
	TBitBtn *BitBtn2;
	TComboBox *CB1;
	TImage *IMG;
	TLabel *L1;
	void __fastcall CB1Click(TObject *Sender);
	void __fastcall BitBtn2Click(TObject *Sender);
private:	
cSQL 		*DB;
IconsData 	*IcoData;
void 		ComboClear(void);
public:		
int 	NextState;
String 	NextStateName;
bool 	NextStateAccept;
	__fastcall 	TStSelect::TStSelect(TComponent* Owner,cSQL *db,IconsData *_IcoData,const int &State,const int &User);
	__fastcall ~TStSelect(void);
};
#endif
