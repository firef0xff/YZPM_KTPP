//---------------------------------------------------------------------------

#ifndef Select_params_prodH
#define Select_params_prodH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>

#include "Agrements_select.h"
//---------------------------------------------------------------------------
class TSel_params_prod : public TForm
{
__published:	// IDE-managed Components
	TEdit *ka_name;
	TEdit *dog_num;
	TComboBox *podr_list;
	TCheckBox *b_dog_num;
	TCheckBox *b_podr;
	TCheckBox *b_ka;
	TCheckBox *b_active;
	TSpeedButton *Ka1c;
	TBitBtn *OK;
	TBitBtn *Cancel;
	TSpeedButton *dog_select;
	TCheckBox *zak;
	TEdit *Zak_numb;
	TEdit *zak_name;
	TCheckBox *name;
	void __fastcall  Ka1cClick(TObject *Sender);
	void __fastcall OKClick(TObject *Sender);
	void __fastcall dog_selectClick(TObject *Sender);
	void __fastcall dog_numChange(TObject *Sender);
private:	// User declarations
	unsigned __int64 dog_id;
	unsigned __int64 ka_id;

	String sortparams;
	cSQL *DB;
	static int count;
	const int &LUser;

public:		// User declarations
	__fastcall TSel_params_prod(TComponent* Owner,const int &_LUser,cSQL *db);
	__fastcall ~TSel_params_prod(void);
String Get_Where(void)const{return sortparams;}
};
int TSel_params_prod::count=0;
#endif
