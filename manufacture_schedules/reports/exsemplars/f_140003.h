#ifndef f_140003H
#define f_140003H

#include <reports/report.h>
#include "functions.h"

namespace rep
{

class F140003 : public Report
{
public:
    F140003(int set);
    ~F140003();

    F140003(const F140003 &r);

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

    //доп параметры
    std::string ceh;
    std::string utch;
    bool group_by_obd;

    //шаблоны
    std::string template_path;//путь к файлу шаблона
    std::string templ;

    //глобальные переменные
    size_t cur_lists;

    void ParseParams    (void);
    void LoadSettings   (void);
    void BuildReport    (void);
    void BuildData      (std::string part_id, std::string zakaz, std::string part_no);
};

}


#endif // F_140003_H
