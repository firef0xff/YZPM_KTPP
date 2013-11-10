//---------------------------------------------------------------------------

#ifndef instrumentH
#define instrumentH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ActnPopup.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include <PlatformDefaultStyleActnCtrls.hpp>
#include <ComCtrls.hpp>
#include <Grids.hpp>
#include "SQL.h"
//---------------------------------------------------------------------------
class Tinstr : public TForm
{
__published:	// IDE-managed Components
	TLabeledEdit *LE1;
	TLabeledEdit *LE2;
	TBitBtn *BitBtn1;
	TBitBtn *BitBtn2;
	TPanel *Panel1;
	TPanel *Panel2;
	TSplitter *Splitter1;
	TPanel *Panel3;
	TTreeView *TV;
	TStringGrid *StringGrid1;
	void __fastcall TVExpanding(TObject *Sender, TTreeNode *Node, bool &AllowExpansion);
	void __fastcall TVDblClick(TObject *Sender);
	void __fastcall BitBtn1Click(TObject *Sender);

private:	// User declarations
cSQL *const DB;
String kod,name;
public:		// User declarations
String Get_Name(void)const{return name;}
String Get_kod(void)const{return kod;}
	__fastcall Tinstr(TComponent* Owner,cSQL *db,String _kod,String _name);
};

#endif
