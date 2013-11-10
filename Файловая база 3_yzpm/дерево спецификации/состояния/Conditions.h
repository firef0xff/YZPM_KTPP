
#ifndef ConditionsH
#define ConditionsH

#include "selector.h"
#include "CRowData.h"
#include "TreeRow.h"

#include <Buttons.hpp>
#include <Classes.hpp>
#include <ComCtrls.hpp>
#include <Controls.hpp>
#include <ExtCtrls.hpp>
#include <StdCtrls.hpp>


class TCond : public TForm
{
__published:	
	TPanel 		*Panel1;
	TButton 	*prev;
	TButton 	*next;
	TButton 	*current;
	TRadioGroup *RG1;
	TImage 		*IMG;
	TLabel 		*CondName;
	TBitBtn 	*BitBtn3;
	TBitBtn 	*BitBtn4;
	TTreeView 	*TV;
	TRadioGroup *RG2;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall nextClick(TObject *Sender);
	void __fastcall currentClick(TObject *Sender);
	void __fastcall prevClick(TObject *Sender);
	void __fastcall BitBtn3Click(TObject *Sender);
	void __fastcall TVMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall TVClick(TObject *Sender);
private:	
cSQL 		*DB;
IconsData 	*IcoData;
const int &LUser;
bool 		MassAction;
String 		IDS;
bool  ChangeCondition(CRowData *row);
void  SelectNextState(CRowData *row);
public:		
	__fastcall TCond(TComponent* Owner,TTreeView &Tree,const bool &_MassAction,cSQL *db,IconsData *_IcoData,const int &User);
};
#endif
