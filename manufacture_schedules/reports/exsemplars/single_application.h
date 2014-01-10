#ifndef SINGLE_APPLICATION_H
#define SINGLE_APPLICATION_H

#include <reports/report.h>
#include "functions.h"

namespace rep
{

class SingleApplication : public Report
{
public:
    SingleApplication(int set);
    ~SingleApplication();

    SingleApplication(const SingleApplication &r);

    void Build(void);
    boost::shared_ptr<rep::Report> SelfCopy (void) const;

private:
    struct ReportData
    {      
        std::string obd;

        std::string ei_kode;
        std::string norm;

        std::string nama;
        std::string prma;

        std::string ei_name;
    };
    typedef std::list<ReportData> DataList;

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

    //шаблоны
    std::string template_path;//путь к файлу шаблона
    std::string templ;

    //доп параметры
    std::string pp;

    //глобальные переменные
    size_t cur_lists;

    void ParseParams    (void);
    void LoadSettings   (void);
    void BuildReport    (void);
    void BuildData      (std::string part_id, std::string zakaz, std::string part_no);
};

}

#endif // SINGLE_APPLICATION_H
