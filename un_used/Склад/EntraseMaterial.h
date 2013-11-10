//---------------------------------------------------------------------------

#ifndef EntraseMaterialH
#define EntraseMaterialH
#ifndef nullptr
	#define nullptr 0
#endif
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>


#include "SQL.h"
#include "Obd.h"
#include "functions.h"
#include <Mask.hpp>
#include <Buttons.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
//---------------------------------------------------------------------------
class TwndEntarseMaterial : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TPanel *pnGeometry;
	TPanel *lblsgGeometry;
	TStringGrid *sgGeometry;
	TLabeledEdit *leObe;
	TLabeledEdit *leName;
	TLabeledEdit *LabeledEdit2;
	TPanel *pnProp;
	TComboBox *cbReason;
	TLabel *Label1;
	TLabeledEdit *leContrAgent;
	TLabeledEdit *LabeledEdit6;
	TLabeledEdit *LabeledEdit7;
	TMaskEdit *MaskEdit1;
	TLabel *Label2;
	TLabeledEdit *LabeledEdit3;
	TButton *btContrAgent;
	TBitBtn *BitBtn1;
	TBitBtn *BitBtn2;
	TComboBox *cbGeometry;
	TADOConnection *ADC;
	TComboBox *cbEi;
	TLabel *Label3;
	void __fastcall sgGeometryDblClick(TObject *Sender);
	void __fastcall cbGeometryExit(TObject *Sender);
	void __fastcall cbGeometryClick(TObject *Sender);
	void __fastcall sgGeometrySelectCell(TObject *Sender, int ACol, int ARow, bool &CanSelect);
	void __fastcall sgGeometrySetEditText(TObject *Sender, int ACol, int ARow, const UnicodeString Value);
	void __fastcall leObeKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall btContrAgentClick(TObject *Sender);



private:	// User declarations
	cSQL *DB;
	const int &LUser;
	Obd  *ekz;         		 //указатель на заносимый экземпл€р
	unsigned __int64 ka_id;  //идентификатор контрагента
	//const int &LUser;

	void 	init 		(void), //инициализаци€ класса
			Check_Obe	(void),	//проверка обозначени€
			Del_Row		(TStringGrid *sg, int Row);	//удаление строки
public:		// User declarations
	__fastcall TwndEntarseMaterial(TComponent* Owner);
	__fastcall TwndEntarseMaterial(TComponent* Owner,const int &_LUser,cSQL *db);
	__fastcall ~TwndEntarseMaterial();
};
//---------------------------------------------------------------------------
extern PACKAGE TwndEntarseMaterial *wndEntarseMaterial;
//---------------------------------------------------------------------------
#endif
