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
        std::string vz;

        std::string obd;
        std::string name;

        std::string kol_det;
        std::string kol_zag;

        std::string razz;

        std::string ml_no;
        std::string order_no;

        std::string nama;
        std::string prma;

        double mass;
        double norm;

        double trud;
        double trud_part;

        std::list<std::string> pm;

        int prizn;

        size_t Rows(void) const
        {
            return 2 > pm.size()?2:pm.size();
        }
        void SetPm(std::string pm_)
        {
            WordWrap(pm, pm_, 33, " ");
        }
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
