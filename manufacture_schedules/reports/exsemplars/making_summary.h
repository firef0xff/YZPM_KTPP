#ifndef making_summaryH
#define making_summaryH

#include <reports/report.h>

namespace rep
{

class MakingSummary : public Report
{
public:
    struct Data
    {
        std::string cex;
        std::string utch;
        std::string zakaz;
        std::string part;
        std::string oper;

        double trud_req;
        double trud_maked;
        double trud_broken;
        double trud_unmaked;
    };
    typedef std::pair<const std::string, Data> CexDataItem;
    typedef std::multimap<const std::string, Data> CexData;


    MakingSummary(int set);
    ~MakingSummary();

    MakingSummary(const MakingSummary &r);

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

    bool use_podr; //группировать по подразделению
    bool use_oper; //группировать по операции
    bool no_duplicate;//убрать дублирующиеся записи
    bool use_objects;//использовать объект ограничения
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

#endif // MAKING_SUMMARY_H
