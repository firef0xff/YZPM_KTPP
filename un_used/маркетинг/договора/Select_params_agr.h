//---------------------------------------------------------------------------

#ifndef Select_params_agrH
#define Select_params_agrH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>

#include "contractors.h"
//---------------------------------------------------------------------------
class TSel_params_agr : public TForm
{
__published:	// IDE-managed Components
	TEdit *ka_name;
	TEdit *dog_num;
	TEdit *summ_min;
	TEdit *summ_max;
	TComboBox *predm_dog;
	TComboBox *isp_list;
	TComboBox *podr_list;
	TComboBox *dog_type;
	TGroupBox *GroupBox1;
	TGroupBox *GroupBox2;
	TGroupBox *GroupBox3;
	TDateTimePicker *cd_max;
	TDateTimePicker *cd_min;
	TDateTimePicker *sign_max;
	TDateTimePicker *sign_min;
	TLabel *Label9;
	TLabel *Label5;
	TLabel *Label6;
	TLabel *Label7;
	TLabel *Label8;
	TLabel *Label11;
	TCheckBox *b_sign_dt;
	TCheckBox *b_summ;
	TCheckBox *b_cd;
	TCheckBox *b_type;
	TCheckBox *b_dog_num;
	TCheckBox *b_isp;
	TCheckBox *b_podr;
	TCheckBox *b_predm;
	TCheckBox *b_ka;
	TCheckBox *b_active;
	TSpeedButton *Ka1c;
	TRadioGroup *b_signed;
	TBitBtn *OK;
	TBitBtn *Cancel;
	void __fastcall  Ka1cClick(TObject *Sender);
	void __fastcall OKClick(TObject *Sender);
private:	// User declarations

	String sortparams;
	cSQL *DB;
	static int count;
	const int &LUser;
	unsigned __int64 ka_id;

public:		// User declarations
	__fastcall TSel_params_agr(TComponent* Owner,const int &_LUser,cSQL *db);
	__fastcall ~TSel_params_agr(void);
String Get_Where(void)const{return sortparams;}
};
int TSel_params_agr::count=0;
#endif
