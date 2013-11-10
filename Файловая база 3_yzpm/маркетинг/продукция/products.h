// ---------------------------------------------------------------------------

#ifndef productsH
#define productsH
// ---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <ImgList.hpp>

#include "Select_params_prod.h"

// ---------------------------------------------------------------------------
class Tprod:public TFrame
	{
__published: // IDE-managed Components

	TImageList *ImageList1;
	TPanel *Panel1;
	TPanel *Panel4;
	TPanel *Panel8;
	TGroupBox *GroupBox2;
	TSpeedButton *next;
	TSpeedButton *prev;
	TLabeledEdit *E2;
	TLabeledEdit *E3;
	TButton *Search;
	TButton *Add;
	TButton *Edit;
	TButton *Del;
	TButton *SortClear;
	TPanel *Panel5;
	TStringGrid *SG;
	TPanel *Panel2;
	TSplitter *Splitter1;
	TStringGrid *colgrid;
	TPanel *Panel3;
	TButton *split;
	TButton *dogovor;
	TLabeledEdit *d_type;
	TLabeledEdit *d_num;
	TLabeledEdit *d_date;
	TLabeledEdit *ca_name;
	TLabeledEdit *pl_ca_name;
	TLabeledEdit *gr_ca_name;
	TLabeledEdit *lz_ca_name;
	TEdit *accept_date;
	TBitBtn *Accept_btn;
	TPanel *Panel6;
	TMemo *sp_prim;
	TLabel *Label1;
	TPanel *Panel7;
	TBitBtn *OK;
	TBitBtn *Cancel;
	TButton *gr_ca_select;
	TButton *pl_ca_select;
	TButton *lz_ca_select;
	TButton *split_d;
	TPanel *Panel9;
	TPanel *Panel10;
	TGroupBox *GroupBox1;
	TSpeedButton *sp_next;
	TSpeedButton *sp_prev;
	TLabeledEdit *sp_E2;
	TLabeledEdit *sp_E3;
	TLabeledEdit *sp_sum;
	TLabeledEdit *sp_sum_nds;
	TComboBox *nds;
	TLabel *Label2;
	TComboBox *valute;
	TLabel *Label3;
	TStringGrid *SG2;
	TLabel *Label4;
	TEdit *curs;
	TLabeledEdit *sp_date;
	TButton *Add_zak;
	TButton *Edit_zak;
	TButton *Del_zak;
	TLabeledEdit *sp_num;

	void __fastcall SGMouseUp(TObject *Sender, TMouseButton Button,
		TShiftState Shift, int X, int Y);
	void __fastcall SearchClick(TObject *Sender);
	void __fastcall SortClearClick(TObject *Sender);
	void __fastcall E3Change(TObject *Sender);
	void __fastcall E2Change(TObject *Sender);
	void __fastcall nextClick(TObject *Sender);
	void __fastcall SGFixedCellClick(TObject *Sender, int ACol, int ARow);
	void __fastcall SGDrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect,
		TGridDrawState State);
	void __fastcall splitClick(TObject *Sender);
	void __fastcall split_dClick(TObject *Sender);
	void __fastcall dogovorClick(TObject *Sender);
	void __fastcall ca_selectClick(TObject *Sender);
	void __fastcall SGSelectCell(TObject *Sender, int ACol, int ARow,
		bool &CanSelect);
	void __fastcall sp_E2Change(TObject *Sender);
	void __fastcall sp_E3Change(TObject *Sender);
	void __fastcall sp_nextClick(TObject *Sender);
	void __fastcall SG2DrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect, TGridDrawState State);
	void __fastcall valuteChange(TObject *Sender);
	void __fastcall AddClick(TObject *Sender);
	void __fastcall EditClick(TObject *Sender);
	void __fastcall DelClick(TObject *Sender);
	void __fastcall OKClick(TObject *Sender);
	void __fastcall CancelClick(TObject *Sender);
	void __fastcall Accept_btnClick(TObject *Sender);


private: // User declarations

	static int count;
	static cSQL *DB;
	const int &LUser;
	String UName;
	String sortparams, 		// ��������� ������
		podrids, 			// �������������� �������������
		order_by, 			// ��������� ����������
		mode; 				// ����� �������/���������������/���������
	bool 					//����� �������
		prod_Edit;			//���������� �� ����������/�������������� ������������

	TADOQuery *data; 		// �������� ������ ������������������
	TADOQuery *sp_data;		//�������� ������ ��� ������ ������� ������������
							//���������� ��� ���������� ������ � ����
	unsigned __int64 	sp_id, 		//������������� ������������
						dog_id, 	//������������� ��������
						gr_ca_id,   //������������� ���������������
						lz_ca_id,   //������������� ������ ����������
						pl_ca_id;   //������������� �����������

	TDateTime 	sp_SignDate,  		//���� ���������� ������������
				sp_CreateDate;      //���� �������� ������������


	void init(void);            //������������� ���� ������� � ���������� �����������
	void Comp_Activating(void); //��������� ������ ��� ����� ������ �����������
	void Find(void); 			// ����� ���������� �� ����
	void sp_Find(void); 		//�������� ���������� �� ������������
	void ShowData(void); 		// ����� ������ �����
	void ShowRowData(int Row); 	// ����������� ������ �� ���������� ������
	void Show_sp_Data(void);    //����������� ������� ������������
	void ColumnResize(void); 	// ��������� �������� ������� ����������

public: // User declarations
	__fastcall Tprod(TComponent *Owner, TWinControl *_p, const int &_LUser,
		cSQL *db);
	};

int Tprod::count=0;
cSQL *Tprod::DB=0;
#endif
