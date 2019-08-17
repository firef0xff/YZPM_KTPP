#ifndef trud_reportH
#define trud_reportH

#include <reports/report.h>

namespace rep
{

class TrudReport : public Report
{
    struct Data
    {
        std::string cex;
        std::string tab_no;
        std::string fio;
        double trud;
    };
    typedef std::pair<const std::string, Data> CexDataItem;
    typedef std::multimap<const std::string, Data> CexData;

public:
    TrudReport(int set);
    ~TrudReport();

    TrudReport(const TrudReport &r);

    void Build(void);
    boost::shared_ptr<rep::Report> SelfCopy (void) const;

private:

    //соединение в бд
    cSQL *DB;
    //настройки размещения отчета
    std::string path;
    bool use_listing;
    size_t lists_by_file;
    //объект построения отчета
    std::string object;
    std::string element;
    std::string type;

    std::string date_from;
    std::string date_to;

    //шаблоны
    std::string template_path;//путь к файлу шаблона
    std::string templ;

    //глобальные переменные
    size_t cur_lists;
    bool surcharge;

    void ParseParams    (void);
    void LoadSettings   (void);
    void BuildReport    (void);
};

class TrudReport2 : public Report
{
    struct Data
    {
        std::string tab_no;
        std::string fio;
        std::string reason;
        double trud;
    };
    typedef std::list<Data> CexData;

public:
    TrudReport2(int set);
    ~TrudReport2();

    TrudReport2(const TrudReport2 &r);

    void Build(void);
    boost::shared_ptr<rep::Report> SelfCopy (void) const;

private:

    //соединение в бд
    cSQL *DB;
    //настройки размещения отчета
    std::string path;
    bool use_listing;
    size_t lists_by_file;
    //объект построения отчета
    std::string object;
    std::string element;
    std::string type;

    std::string date_from;
    std::string date_to;

    //шаблоны
    std::string template_path;//путь к файлу шаблона
    std::string templ;

    //глобальные переменные
    size_t cur_lists;

    void ParseParams    (void);
    void LoadSettings   (void);
    void BuildReport    (void);
};

}
#endif // TRUD_REPORT_H
