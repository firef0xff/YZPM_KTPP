#ifndef STATEMENTS_SET_H
#define STATEMENTS_SET_H
#include <reports/report.h>
#include "functions.h"

namespace rep
{

class StatementsSet : public Report
{
public:
    StatementsSet(int set);
    ~StatementsSet();

    StatementsSet(const Complect05 &r);

    void Build(void);
    boost::shared_ptr<rep::Report> SelfCopy (void) const;

private:
    struct ObectData
    {
        std::string det_id;
        std::string obd;
        std::string name;
        std::string zakaz;
        std::string part_no;
        int izd_kol;
    };
    struct ReportData
    {
        struct ObuData
        {
            std::string obu;
            double kol;
            std::string ei;
        };
        typedef std::map<std::string, ObuData> ObuDataList;

        std::string obd;
        std::string name;
        std::string sort;
        ObuDataList obu_list;
    };
    typedef std::map<std::string, ReportData> DataList;

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

    //шаблоны
    std::string template_path;//путь к файлу шаблона
    std::string templ;

    //глобальные переменные
    size_t cur_lists;

    bool build_all;
    bool build_cooperation;
    bool build_forging;
    bool build_litho;
    bool build_stamping;

    void ParseParams    (void);
    void LoadSettings   (void);
    void BuildReport    (void);

    void BuildDataAll           (const ObectData &obj);
    void BuildDataCooperation   (const ObectData &obj);
    void BuildDataForging       (const ObectData &obj);
    void BuildDataLitho         (const ObectData &obj);
    void BuildDataStamping      (const ObectData &obj);
};

}

#endif // STATEMENTS_SET_H
