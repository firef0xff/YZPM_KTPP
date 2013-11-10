

#ifndef DetSelectorH
#define DetSelectorH

#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include "ClassConnector.h"

class TObdSelector : public TFrame
{
__published:	
	TSpeedButton 	*BackSP;
	TSpeedButton 	*NextSP;
	TComboBox		*FastNavigator;
	void __fastcall FastNavigatorClick(TObject *Sender);
	void __fastcall FastNavigatorDropDown(TObject *Sender);
	void __fastcall FastNavigatorKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall SpChange(TObject *Sender);
private:	
	char ListSize;
	cSQL *const DB;
	ClassConnector *const owner;
	void  			SetText(const String &Text);
	void  			ComboClear(void);
public:		
	__fastcall TObdSelector(TComponent* Owner, ClassConnector *const Own,TWinControl *_p,cSQL *const db,char _ListSize=10);
	__fastcall ~TObdSelector();
	void   			LoadDet  	(Obd *det);
};
#endif
