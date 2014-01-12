#ifndef ROUTELIST_H
#define ROUTELIST_H
#include <reports/report.h>
#include <xl_operations.h>
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
    std::string element;
    std::string type;

    //шаблоны
    std::string template_path;//путь к файлу шаблона
    std::string templ;

    //глобальные переменные
    size_t cur_lists;

    void ParseParams    (void);
    void LoadSettings   (void);
    void BuildReport    (void);
    void BuildData      (cExcel &xl, size_t det_id, string part_id, std::string part_no, std::string list_no, std::string zakaz);
};

}
#endif // ROUTELIST_H
