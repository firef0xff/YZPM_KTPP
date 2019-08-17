#ifndef zakaz_trud_reportH
#define zakaz_trud_reportH

#include <reports/report.h>

namespace rep
{

class ZakazTrudReport : public Report
{
    struct Data
    {
        std::string zakaz;
        std::string tab_no;
        std::string fio;
        std::string reason;
        double trud;
    };
    typedef std::pair<const std::string, Data> CexDataItem;
    typedef std::multimap<const std::string, Data> CexData;

public:
    ZakazTrudReport(int set);
    ~ZakazTrudReport();

    ZakazTrudReport(const ZakazTrudReport &r);

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
    bool use_zakaz_group;
    bool surcharge;

    //шаблоны
    std::string template_path;//путь к файлу шаблона
    std::string templ;

    //глобальные переменные
    size_t cur_lists;

    void ParseParams    (void);
    void LoadSettings   (void);
    void BuildReport    (void);
};

class ZakazTrudReport2 : public Report
{
    struct Data
    {
        std::string zakaz;
        std::string tab_no;
        std::string fio;
        std::string reason;
        double trud;
    };
    typedef std::pair<const std::string, Data> CexDataItem;
    typedef std::multimap<const std::string, Data> CexData;

public:
    ZakazTrudReport2(int set);
    ~ZakazTrudReport2();

    ZakazTrudReport2(const ZakazTrudReport2 &r);

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
    bool use_zakaz_group;

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

#endif // ZAKAZ_TRUD_REPORT_H
