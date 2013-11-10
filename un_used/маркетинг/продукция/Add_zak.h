//---------------------------------------------------------------------------

#ifndef Add_zakH
#define Add_zakH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TZak_prop : public TForm
{
__published:	// IDE-managed Components
	TGroupBox *Ad_composition;
	TStringGrid *StringGrid1;
	TPanel *Panel1;
	TComboBox *ComboBox3;
	TPanel *Panel2;
	TGroupBox *Facilities;
	TLabeledEdit *LabeledEdit10;
	TLabeledEdit *LabeledEdit11;
	TGroupBox *Prim_box;
	TMemo *Memo1;
	TGroupBox *Pokovki;
	TLabel *Label3;
	TComboBox *ComboBox2;
	TLabeledEdit *LabeledEdit4;
	TLabeledEdit *LabeledEdit9;
	TGroupBox *Product;
	TLabeledEdit *LabeledEdit1;
	TLabeledEdit *LabeledEdit2;
	TLabeledEdit *LabeledEdit3;
	TGroupBox *Zak_no;
	TComboBox *Zak_pref;
	TEdit *Edit1;
	TGroupBox *Zak_params;
	TLabel *Label1;
	TLabel *Label2;
	TLabeledEdit *z_kol;
	TLabeledEdit *LabeledEdit5;
	TComboBox *ComboBox1;
	TLabeledEdit *LabeledEdit6;
	TLabeledEdit *LabeledEdit7;
	TLabeledEdit *LabeledEdit8;
	TButtonedEdit *ButtonedEdit1;
	TBitBtn *Cancel;
	TBitBtn *OK;
private:	// User declarations
	void	Use_add_composition(bool on);//выключатель спользования механизмов добавления дополнительного состава

	bool    Using_add_composition;       //триггер спользования механизмов добавления дополнительного состава
public:		// User declarations
	__fastcall TZak_prop(TComponent* Owner);
};

#endif
