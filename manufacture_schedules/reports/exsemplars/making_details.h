#ifndef MAKING_DETAILS_H
#define MAKING_DETAILS_H

#include <reports/report.h>

namespace rep
{

class MakingDetails : public Report
{
public:
    struct Data
    {
        std::string cex;
        std::string utch;
        std::string zakaz;
        std::string part;

        std::string vz;
        std::string obd;
        std::string name;

        std::string kol_req;
        std::string kol_maked;
        std::string kol_broken;
        std::string kol_unmaked;
        double trud_req;
        double trud_maked;
        double trud_broken;
        double trud_unmaked;
    };
    typedef std::pair<const std::string, Data> CexDataItem;
    typedef std::multimap<const std::string, Data> CexData;


    MakingDetails(int set);
    ~MakingDetails();

    MakingDetails(const MakingDetails &r);

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
    bool show_maked;
    bool show_un_maked;
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

#endif // MAKING_DETAILS_H
