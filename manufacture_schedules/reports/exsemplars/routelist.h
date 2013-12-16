#ifndef ROUTELIST_H
#define ROUTELIST_H
#include <reports/report.h>

namespace rep
{

class RouteList : public Report
{
public:
    RouteList(int set);
    ~RouteList();

    RouteList(const RouteList &r);

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
    std::string type;

    //шаблоны
    std::string template_path;//путь к файлу шаблона

    //глобальные переменные
    size_t cur_lists;

    void ParseParams    (void);
    void LoadSettings   (void);
    void BuildReport    (void);
    void BuildData      (size_t det_id);
};

}
#endif // ROUTELIST_H
