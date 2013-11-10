//---------------------------------------------------------------------------

#ifndef Agrements_selectH
#define Agrements_selectH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
#include "agreements_main.h"
class TAgreements_select : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TPanel *Panel2;
	TBitBtn *OK;
	TBitBtn *Cancel;
	void __fastcall OKClick(TObject *Sender);
private:	// User declarations
	unsigned __int64 	id;
	String 	d_num,
			d_type,
			ca_name,
			d_date;
	TAgreements *frm;
public:		// User declarations
	__fastcall TAgreements_select(TComponent* Owner,const int &_LUser,cSQL *db);
	void Update_selected_dog(unsigned __int64 &_id,String &_num,String &_d_date,String &_type,String &_ca_name) const {_id=id;_num=d_num;_d_date=d_date;_type=d_type;_ca_name=ca_name;};
	void Update_selected_dog(unsigned __int64 &_id,String &_num) const {_id=id;_num=d_num;};
};
#endif
