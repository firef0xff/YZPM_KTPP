//---------------------------------------------------------------------------

#ifndef zagotovkH
#define zagotovkH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include <Grids.hpp>
#include <Buttons.hpp>

#include "redaktor_formul.h"
//---------------------------------------------------------------------------
class Tzagotovka : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel2;
	TRadioGroup *RG1;
	TBitBtn *BB1;
	TLabel *Label1;
	TEdit *E1;
	TComboBox *CB1;
	TLabel *Label2;
	TBitBtn *BitBtn1;
	TButton *Button1;
	TLabeledEdit *mass;
	TLabeledEdit *nrm;
	TPanel *Panel1;
	TSplitter *Splitter1;
	TPanel *Panel3;
	TStringGrid *SG1;
	TLabeledEdit *LE1;
	TTreeView *TV;
	TPanel *Panel4;
	void __fastcall TVExpanding(TObject *Sender, TTreeNode *Node, bool &AllowExpansion);
	void __fastcall RG1Click(TObject *Sender);
	void __fastcall TVDblClick(TObject *Sender);
	void __fastcall BB1Click(TObject *Sender);
	void __fastcall BitBtn1Click(TObject *Sender);
	void __fastcall CB1Click(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);

private:	// User declarations
cSQL * const DB;
const int &LUser;
static int srtby;
String 	kz,masz,norma,razmzagot,kdz;
void FillTree(void);
public:		// User declarations
	__fastcall Tzagotovka(TComponent* Owner,cSQL *db,bool ReadOnly,const int &_LUser,String kz,String masz,String norma,String razmzagot);
String  Get_kz (void)const{return kz;}
String  Get_kdz (void)const{return kdz;}
String  Get_masz (void)const{return masz;}
String  Get_norma (void)const{return norma;}
String  Get_razmzagot (void)const{return razmzagot;}

};
int  Tzagotovka::srtby=-1;
#endif
