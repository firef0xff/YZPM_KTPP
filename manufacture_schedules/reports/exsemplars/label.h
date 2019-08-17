#ifndef labelH
#define labelH
#include <reports/report.h>

namespace rep
{

class Lable : public Report
{
public:
    Lable(int set);
    ~Lable();

    Lable(const Lable &r);

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
};

}
#endif // LABLE_H
