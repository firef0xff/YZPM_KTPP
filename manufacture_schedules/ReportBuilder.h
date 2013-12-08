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
#include <set>
#include <string>
#include <boost/shared_ptr.hpp>

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
	TStringGrid *ScheduleSG;
	TPanel *Panel3;
	TBitBtn *BitBtn2;
	TBitBtn *BitBtn1;
	TComboBox *ReportsList;
	TSpeedButton *Add;
	TSpeedButton *Del;
	void __fastcall AddClick(TObject *Sender);
	void __fastcall DelClick(TObject *Sender);
	void __fastcall ScheduleSGDrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect,
		  TGridDrawState State);
public:		// User declarations
    __fastcall TReports(TComponent* Owner, Reports_set set, __uint64  id);


private:	// User declarations
    void UpdateRepListSG (void);

	class TSchedule
	{
        typedef std::pair<std::string, std::string> Var;
        typedef std::vector<Var> VarSet;
    public:
        TSchedule(std::string func_name_, std::string rep_name_):func_name(func_name_),rep_name(rep_name_)
        {}

        std::string ReportName(void)
        {
            return rep_name;
        }

        std::string GetVariables(void)
        {
            std::string s;
            for (VarSet::const_iterator it = values.begin(); it != values.end(); ++it)
            {
                const Var &lnk = *it;

                s += lnk.first + " = " + lnk.second + "; ";
            }

            return s;
        }

        std::string GetCommandSring(void)
        {
            std::string s;

            s += func_name + "(";

            const char * delim = "";
            for (VarSet::const_iterator it = values.begin(); it != values.end(); ++it)
            {
                const Var &lnk = *it;

                s += "'" + std::string(delim) + lnk.second + "'";
                delim = ",";
            }
            s += ")";
            return s;
        }

        void AddVar (std::string name, std::string value)
        {
            values.push_back(Var(name, value));
        }
    private:
        std::string func_name;
        std::string rep_name;
        VarSet values;
    };

	typedef std::vector<boost::shared_ptr<TSchedule> > ScheduleList;
    Reports_set selected_set;
    __uint64  object_id;
    ScheduleList schedules;
};

class ReportList
{
public:
    struct Report
    {
		Report(std::string f_nm, std::string r_nm, int set_):func_name(f_nm),rep_name(r_nm),set(set_)
        {
            ReportList::Instance().Register(this);
        }
		~Report()
        {
            ReportList::Instance().UnRegister(this);
        }

        const std::string func_name;
        const std::string rep_name;
        const int set;
    };
    typedef std::set<Report *> ReportsSet;

    static ReportList& Instance()
    {
        static ReportList item;
        return item;
    }
    void Register(Report *r)
    {
        reports.insert(r);
    }
    void UnRegister(Report *r)
    {
        ReportsSet::iterator it = reports.find(r);
        if (it != reports.end())
            reports.erase(it);
    }
    ReportsSet GetReports (int set)
    {
        ReportsSet res;
		for (ReportsSet::iterator it = reports.begin(); it!=reports.end(); ++it)
        {
            Report *ptr = *it;
            if (ptr->set & set)
            {
                res.insert(ptr);
            }
		}
		return res;
    }
private:
    ReportList(){}
    ReportList(const ReportList &){}
    void operator = (const ReportList &){}

    ReportsSet reports;
};

#endif
