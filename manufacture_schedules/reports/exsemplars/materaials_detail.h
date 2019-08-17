#ifndef materaials_detailH
#define materaials_detailH

#include <reports/report.h>
#include "functions.h"

namespace rep
{

class MaterialsDetail : public Report
{
public:
    MaterialsDetail(int set);
    ~MaterialsDetail();

    MaterialsDetail(const MaterialsDetail &r);

    void Build(void);
    boost::shared_ptr<rep::Report> SelfCopy (void) const;

private:
    struct ReportData
    {
        std::string obd;
        std::string name;
        std::string kol_det;

        std::string obm;
        double norm;
        std::string material;

        std::string ei_name;
        std::string vz;
        std::string razz;
        std::string masz;
        std::string masd;

        std::string kol_zag;
        std::string kdz;
        std::string kim;
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
    bool disable_sp;

    //глобальные переменные
    size_t cur_lists;

    void ParseParams    (void);
    void LoadSettings   (void);
    void BuildReport    (void);
    void BuildData      (std::string part_id, std::string zakaz, std::string part_no);
};

}

#endif // MATERAIALS_DETAIL_H
