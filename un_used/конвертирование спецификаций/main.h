//---------------------------------------------------------------------------

#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------
class TForm3 : public TForm
{
__published:	// IDE-managed Components
	TButton *Button1;
	TLabeledEdit *LE1;
	TLabeledEdit *LE2;
	TButton *Button2;
	TOpenDialog *OD;
	TButton *Button3;
	TStringGrid *SG;
	TLabeledEdit *LE;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall SGSetEditText(TObject *Sender, int ACol, int ARow, const UnicodeString Value);

private:	// User declarations
String sp,templ;
String Format(String s);
public:		// User declarations
	__fastcall TForm3(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm3 *Form3;
//---------------------------------------------------------------------------
#endif
