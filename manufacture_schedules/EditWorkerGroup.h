//---------------------------------------------------------------------------

#ifndef EditWorkerGroupH
#define EditWorkerGroupH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TWorkerGroup : public TForm
{
__published:	// IDE-managed Components
	TLabeledEdit *group_name;
	TBitBtn *ok;
	TBitBtn *cancel;
	TLabeledEdit *r_kol;
private:	// User declarations
public:		// User declarations
	__fastcall TWorkerGroup(TComponent* Owner);
};

#endif
