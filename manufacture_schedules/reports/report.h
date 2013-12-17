#ifndef REPORT_H
#define REPORT_H
#include <string>
#include <map>
#include <set>
#include <list>
#include <boost/shared_ptr.hpp>
#include <boost/function.hpp>
#include <SQL.h>

#define REPORT_PATH         "report_path"
#define REPORT_LIST_COUNT   "report_list_count"
#define REPORT_USE_LISTING  "report_use_listing"
#define REPORT_OBJECT_ID    "report_object_id"
#define REPORT_ELEMENT_ID   "report_element_id"
#define REPORT_OBJECT_TYPE  "report_object_type"
#define REP_TRUE    "1"
#define REP_FALSE   "0"
#define REP_NULL    ""

namespace rep
{

class Report;

class ReportList
{
    typedef std::set<Report *> ReportsSet;
public:
    typedef std::set<Report const*> ConstReportsSet;

    static ReportList& Instance();

    void Register(Report *r);
    void UnRegister(Report *r);
    ConstReportsSet GetReports(int set) const;

    void DbConnection (cSQL *db_);
    cSQL * DbConnection (void);
private:
    ReportList():db(0){}
    ReportList(const ReportList &){}
    void operator = (const ReportList &){}

    cSQL *db;
    ReportsSet reports;
};

class Report
{
public:
    typedef std::pair<const std::string, std::string> Parametr;
    typedef std::map<const std::string, std::string> ParamList;

    Report(std::string r_nm, int set_);
    virtual ~Report();

    virtual void Build (void) = 0;
    ParamList& Params(void);
    std::string Name(void) const;
    std::string ParamsValues(void) const;

    virtual boost::shared_ptr<Report> SelfCopy (void) const =0;
protected:
    Report (const Report &r);

    const std::string name;
    const int set;
    ParamList params;
private:
    bool SystemParam(std::string) const;
    friend class ReportList;
};

}

namespace  fake
{

class FakeReport :public rep::Report
{
public:
    FakeReport (int set);
    ~FakeReport();

    FakeReport(const FakeReport &r);

    void Build(void);
	boost::shared_ptr<rep::Report> SelfCopy (void) const;
};

}

#endif // REPORT_H
