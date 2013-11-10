//---------------------------------------------------------------------------

#ifndef tara_and_stropH
#define tara_and_stropH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <Buttons.hpp>
#include "SQL.h"
//---------------------------------------------------------------------------
class Ttarandsrop : public TForm
{
__published:	// IDE-managed Components
	TLabeledEdit *LE1;
	TPanel *Panel1;
	TPanel *Panel2;
	TPanel *Panel3;
	TSplitter *Splitter1;
	TTreeView *TV;
	TImage *img;
	TBitBtn *BitBtn1;
	TBitBtn *BitBtn2;
	TBitBtn *BitBtn3;
	void __fastcall TVExpanding(TObject *Sender, TTreeNode *Node, bool &AllowExpansion);
	void __fastcall BitBtn1Click(TObject *Sender);
	void __fastcall TVDblClick(TObject *Sender);
	void __fastcall BitBtn3Click(TObject *Sender);
	void __fastcall TVClick(TObject *Sender);
	void __fastcall TVDeletion(TObject *Sender, TTreeNode *Node);

private:	// User declarations
cSQL *const DB;
String type;
String id,text;
String base;
public:		// User declarations
	__fastcall Ttarandsrop(TComponent* Owner,cSQL *DB,String _type,String _id,String _text);
String Get_id(void)		const{return id;}
String Get_text(void)	const{return text;}
};
#endif
