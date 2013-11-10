//---------------------------------------------------------------------------

#ifndef agreements_mainH
#define agreements_mainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <ImgList.hpp>

#include <ComCtrls.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include "contractors.h"
#include "Select_params_agr.h"
//---------------------------------------------------------------------------
class TAgreements : public TFrame
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TPanel *Panel2;
	TPanel *Panel3;
	TPanel *Panel4;
	TPanel *Panel8;
	TGroupBox *GroupBox2;
	TSpeedButton *next;
	TSpeedButton *prev;
	TLabeledEdit *E2;
	TLabeledEdit *E3;
	TStringGrid *SG;
	TPanel *Panel5;
	TButton *Add;
	TButton *Edit;
	TButton *Del;
	TImageList *ImageList1;
	TButton *split;
	TComboBox *podr_list;
	TComboBox *isp_list;
	TComboBox *dog_type;
	TComboBox *predm_dog;
	TLabel *Label1;
	TLabel *Label2;
	TEdit *suff;
	TEdit *num;
	TEdit *preff;
	TLabel *Label3;
	TPanel *Panel6;
	TLabel *Label4;
	TLabel *Label5;
	TLabel *Label6;
	TCheckBox *CB1;
	TDateTimePicker *StartDate;
	TDateTimePicker *EndDate;
	TLabel *Label7;
	TLabel *Label8;
	TBitBtn *Cancel;
	TBitBtn *OK;
	TDateTimePicker *CreateDate;
	TLabel *Label9;
	TEdit *accept_date;
	TBitBtn *Accept_btn;
	TComboBox *leaders_list;
	TLabel *Label10;
	TLabel *Label11;
	TEdit *ka_name;
	TLabel *Label12;
	TMemo *prim;
	TEdit *summ;
	TLabel *Label13;
	TLabel *Label14;
	TSpeedButton *Ka1c;
	TSplitter *Splitter1;
	TButton *Search;
	TButton *SortClear;
	void __fastcall splitClick(TObject *Sender);
	void __fastcall Ka1cClick(TObject *Sender);
	void __fastcall podr_listClick(TObject *Sender);
	void __fastcall isp_listClick(TObject *Sender);
	void __fastcall Accept_btnClick(TObject *Sender);
	void __fastcall FindClick(TObject *Sender);
	void __fastcall E2Change(TObject *Sender);
	void __fastcall nextClick(TObject *Sender);
	void __fastcall E3Change(TObject *Sender);
	void __fastcall SGDrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect, TGridDrawState State);
	void __fastcall SGFixedCellClick(TObject *Sender, int ACol, int ARow);
	void __fastcall SGSelectCell(TObject *Sender, int ACol, int ARow, bool &CanSelect);
	void __fastcall AddClick(TObject *Sender);
	void __fastcall EditClick(TObject *Sender);
	void __fastcall DelClick(TObject *Sender);
	void __fastcall OKClick(TObject *Sender);
	void __fastcall CancelClick(TObject *Sender);
	void __fastcall CB1Click(TObject *Sender);
	void __fastcall SortClearClick(TObject *Sender);


private:	// User declarations
	unsigned __int64 ka_id;
	unsigned __int64 id;
	String d_num;
	static int count;
	static cSQL *DB;
	const int &LUser;

	int	   num_ch;
	bool Agreement_Edit,
		 Agreement_Assign;
	String 	sortparams,//параметры поиска
			podrids,   //идентификаторы подразделений
			order_by,  //параметры сортировки
			mode,      //режим вставки/редактированиея/просмотра
			num_old;
	TDateTime SignDate;
	TADOQuery *data;
	void init (void);
	void Find(void);
	void ShowData(void);
	void ShowRowData(int row);
	void Comp_Activating(void);
public:		// User declarations
	__fastcall TAgreements(TComponent* Owner,TWinControl *_p,const int &_LUser,cSQL *db);
	__fastcall ~TAgreements(void);
	void Update_selected_dog(unsigned __int64 &_id,String &_num,String &_d_date,String &_type,String &_ca_name) const {_id=id;_num=d_num;_d_date=CreateDate->Date.FormatString("dd.mm.yyyy");_type=dog_type->Text.SubString(1,1).LowerCase();_ca_name=ka_name->Text;};
};
int TAgreements::count=0;
cSQL *TAgreements::DB=0;
#endif
