#ifndef COMPLECTS_H
#define COMPLECTS_H
#include <reports/report.h>
#include "functions.h"
#include <xl_operations.h>

namespace rep
{

class Complect05 : public Report
{
public:
    Complect05(int set);
    ~Complect05();

    Complect05(const Complect05 &r);

    void Build(void);
    boost::shared_ptr<rep::Report> SelfCopy (void) const;

private:
    struct ReportData
    {
		struct ObuData
		{
			std::string obu;
            double kol;
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

    void ParseParams    (void);
    void LoadSettings   (void);
    void BuildReport    (void);
    void BuildData      (std::string det_id, std::string obd, std::string name,
                         std::string zakaz, std::string part_no);
    void CheckList      (bool &new_page,
                         const size_t row_size,
                         const size_t start_row,
                         const size_t end_row,
                         const size_t template_page,
                         const size_t max_page_no,

                         const std::string &file_name,
                         const std::string &teml_file,

                         const std::string &zakaz,
                         const std::string &obd,
                         const std::string &name,
                         const std::string &part_no,

                         size_t &cur_row,
                         size_t &file_no,
                         size_t &list_no,
                         cExcel &xl);
};

class Complect06 : public Report
{
public:
    Complect06(int set);
    ~Complect06();

    Complect06(const Complect05 &r);

    void Build(void);
    boost::shared_ptr<rep::Report> SelfCopy (void) const;

private:
    struct ReportData
    {
        struct ObuData
        {
            std::string obu;
            double kol;
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

    void ParseParams    (void);
    void LoadSettings   (void);
    void BuildReport    (void);
    void BuildData      (std::string det_id, std::string obd, std::string name,
                         std::string zakaz, std::string part_no);
    void CheckList      (bool &new_page,
                         const size_t row_size,
                         const size_t start_row,
                         const size_t end_row,
                         const size_t template_page,
                         const size_t max_page_no,

                         const std::string &file_name,
                         const std::string &teml_file,

                         const std::string &zakaz,
                         const std::string &obd,
                         const std::string &name,
                         const std::string &part_no,

                         size_t &cur_row,
                         size_t &file_no,
                         size_t &list_no,
                         cExcel &xl);
};
}
#endif // COMPLECTS_H
