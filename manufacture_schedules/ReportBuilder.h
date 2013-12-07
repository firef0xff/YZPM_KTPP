//---------------------------------------------------------------------------

#ifndef ReportBuilderH
#define ReportBuilderH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Grids.hpp>
#include <ValEdit.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TReports : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TPanel *Panel2;
	TStringGrid *CatalogSG;
	TStringGrid *ScheduleSG;
	TPanel *Panel3;
	TSpeedButton *Add;
	TSpeedButton *Del;
	TBitBtn *BitBtn2;
	TBitBtn *BitBtn1;
private:	// User declarations
public:		// User declarations
	__fastcall TReports(TComponent* Owner);
};

#endif
