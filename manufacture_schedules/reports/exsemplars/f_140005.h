#ifndef F_140005_H
#define F_140005_H
#include <reports/report.h>
#include "functions.h"

namespace rep
{

class F140005 : public Report
{
public:
    F140005(int set);
    ~F140005();

    F140005(const F140005 &r);

    void Build(void);
    boost::shared_ptr<rep::Report> SelfCopy (void) const;

private:
    struct ReportData
    {
        std::string ml_no;
        std::string obd;
        std::string name;
        std::string kol;
        std::string ost;
        int prizn;
        std::string nama;
        std::string prma;
        double tpz;
        double tsht;
        double tpz_part;
        double tsht_part;
        std::string order_no;
        std::list<std::string> pm;

        size_t Rows(void) const
        {
            return 2 > pm.size()?2:pm.size();
        }
        void SetPm(std::string pm_)
        {
            WordWrap(pm, pm_, 29, " ");
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

#endif // F_140005_H
