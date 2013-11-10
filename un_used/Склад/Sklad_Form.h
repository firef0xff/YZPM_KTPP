//---------------------------------------------------------------------------

#ifndef Sklad_FormH
#define Sklad_FormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TSklad : public TForm
{
__published:	// IDE-managed Components
	TPageControl *PageControl1;
	TTabSheet *TabSheet1;
	TTabSheet *TabSheet2;
	TPanel *View_Kont;
	TPanel *Panel2;
	TPanel *Panel3;
	TPanel *Panel4;
	TSplitter *Splitter1;
	TPanel *Panel7;
	TPanel *Panel5;
	TPanel *View_Zagr;
	TPanel *Panel8;
	TPanel *Panel9;
	TTabSheet *TabSheet3;
	TPanel *Panel11;
	TPanel *Panel12;
	TPanel *Panel13;
	TPanel *Panel15;
	TPanel *Panel18;
	TPanel *Panel19;
	TStringGrid *potr_materials;
	TStringGrid *Mater_detail;
	TPanel *Panel20;
	TSplitter *Splitter2;
	TPageControl *materials_lists;
	TTabSheet *TabSheet4;
	TTabSheet *TabSheet5;
	TTabSheet *TabSheet6;
	TTreeView *TreeView1;
	TPanel *Panel14;
	TGroupBox *GroupBox3;
	TSpeedButton *Snext;
	TSpeedButton *Sprev;
	TLabeledEdit *SE2;
	TLabeledEdit *SE3;
	TPanel *Panel17;
	TLabel *Label3;
	TEdit *E1;
	TButton *StartSearch;
	TRadioGroup *SearchParams;
	TPageControl *PageControl2;
	TTabSheet *TabSheet7;
	TTabSheet *TabSheet8;
	TSplitter *Splitter3;
	TStringGrid *Std_izd;
	TStringGrid *Vspom_materials;
	TStringGrid *Materials;
	TTabSheet *TabSheet9;
	TStringGrid *Change_materials;
	TSpeedButton *SpeedButton1;
	TButton *Button1;
	TLabel *Free_percent;
	TLabel *Label2;
	TLabel *Use_percent;
	TLabel *Label5;
	TPanel *Panel16;
	TPanel *Panel21;
	TImage *R_Graph;
	TStringGrid *StringGrid1;
	TComboBox *Sort_Params;
	TLabel *Label1;
	TLabel *Label4;
	TEdit *Edit1;
	TComboBox *Find_params;
	TStringGrid *StringGrid2;
	TImage *Image1;
	TLabel *Label6;
	void __fastcall PanelEnter(TObject *Sender);
	void __fastcall PanelExit(TObject *Sender);
	void __fastcall PanelMouseEnter(TObject *Sender);
	void __fastcall R_GraphClick(TObject *Sender);
	void __fastcall Panel7Click(TObject *Sender);


private:	// User declarations
void expand_pannel_h(TPanel *Panel,bool exp);
public:		// User declarations
	__fastcall TSklad(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TSklad *Sklad;
//---------------------------------------------------------------------------
#endif
