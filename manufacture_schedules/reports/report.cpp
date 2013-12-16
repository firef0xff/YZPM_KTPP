#include "report.h"

namespace rep
{
    ReportList& ReportList::Instance()
	{
        static ReportList item;
        return item;
    }
    void ReportList::Register(Report *r)
    {
        reports.insert(r);
    }
    void ReportList::UnRegister(Report *r)
    {
        ReportsSet::iterator it = reports.find(r);
        if (it != reports.end())
            reports.erase(it);
    }
    ReportList::ConstReportsSet ReportList::GetReports (int set) const
	{
        ConstReportsSet res;
        for (ReportsSet::const_iterator it = reports.begin(); it!=reports.end(); ++it)
        {
            Report const *ptr = *it;
            if (ptr->set & set)
            {
                res.insert(ptr);
            }
        }
        return res;
    }


    Report::Report(std::string r_nm, int set_):name(r_nm),set(set_)
    {
        ReportList::Instance().Register(this);
    }
    Report::~Report()
    {
        ReportList::Instance().UnRegister(this);
    }
    Report::Report (const Report &r):set(r.set),name(r.name),params(r.params)
    {
    }
    Report::ParamList& Report::Params(void)
    {
        return params;
    }
    std::string Report::ParamsValues(void) const
    {
        std::string s;
        for (ParamList::const_iterator it = params.begin(); it != params.end(); ++it)
        {
            const Parametr &lnk = *it;
            if (SystemParam(lnk.first))
            {
                continue;
            }
            s += lnk.first + " = " + lnk.second + "; ";
        }
        return s;
    }
    std::string Report::Name(void) const
    {
        return name;
    }

    bool Report::SystemParam(std::string param) const
    {
        static std::set<std::string> system_params;
        if(system_params.empty())
        {
            system_params.insert(REPORT_PATH);
            system_params.insert(REPORT_LIST_COUNT);
            system_params.insert(REPORT_USE_LISTING);
            system_params.insert(REPORT_OBJECT_ID);
            system_params.insert(REPORT_OBJECT_TYPE);
        }

        return system_params.find(param) != system_params.end();
    }
}


namespace  fake
{
    FakeReport::FakeReport (int set): rep::Report("Fake Report",set)
    {
        params["Цех"]="05";
        params["Участок"]="04";
        params[REPORT_LIST_COUNT] = "50";
        params[REPORT_PATH];
        params[REPORT_USE_LISTING] = REP_TRUE;
    }
    FakeReport::~FakeReport()
    {}

    FakeReport::FakeReport(const FakeReport &r):rep::Report(r)
    {

    }

    void FakeReport::Build(void) const
    {
        throw std::runtime_error("it is a fake report");
    }
    boost::shared_ptr<rep::Report> FakeReport::SelfCopy (void) const
    {
        return boost::shared_ptr<rep::Report>(new FakeReport(*this));
    }

}
