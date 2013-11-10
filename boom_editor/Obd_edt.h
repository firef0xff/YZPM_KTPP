//---------------------------------------------------------------------------

#ifndef Obd_edtH
#define Obd_edtH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TObd_edit : public TForm
{
__published:	// IDE-managed Components
	TEdit *Edit1;
	TBitBtn *BitBtn2;
	TBitBtn *BitBtn1;
private:	// User declarations
public:		// User declarations
	__fastcall TObd_edit(TComponent* Owner);
};
#endif
