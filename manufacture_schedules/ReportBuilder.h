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

#include <vector>
#include <report.h>

//#define __fastcall
//#define __published public

typedef unsigned long long __uint64 ;
enum Reports_set
{
    UNKNOWN = 0,
    STARTUP = 1,
    ORDER = 2,
    PART = 4,
    PRODUCT = 8
};


//---------------------------------------------------------------------------
class TReports : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel2;
	TPanel *Panel3;
	TBitBtn *BitBtn2;
	TBitBtn *Build;
	TComboBox *ReportsList;
	TSpeedButton *Add;
	TSpeedButton *Del;
	TStringGrid *ScheduleSG;
	void __fastcall AddClick(TObject *Sender);
	void __fastcall DelClick(TObject *Sender);
	void __fastcall ScheduleSGDrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect,
		  TGridDrawState State);
	void __fastcall BuildClick(TObject *Sender);
	void __fastcall ScheduleSGDblClick(TObject *Sender);
public:		// User declarations
    __fastcall TReports(TComponent* Owner, cSQL *DB, Reports_set set, __uint64  id, __uint64 sub_id = 0);


private:	// User declarations
    void UpdateRepListSG (void);

    typedef std::vector<boost::shared_ptr<rep::Report> > ScheduleList;
    Reports_set selected_set;
    __uint64  object_id;
    __uint64  element_id;
    ScheduleList schedules;
};

#endif
