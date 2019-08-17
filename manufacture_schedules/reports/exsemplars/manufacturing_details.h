#ifndef manufacturing_detailsH
#define manufacturing_detailsH

#include <reports/report.h>
#include "functions.h"
#include <xl_operations.h>

namespace rep
{

class ManufacturingDetails : public Report
{
public:
    ManufacturingDetails(int set);
    ~ManufacturingDetails();

    ManufacturingDetails(const ManufacturingDetails &r);

    void Build(void);
    boost::shared_ptr<rep::Report> SelfCopy (void) const;

private:
    struct ObectData
    {
        std::string det_id;
        std::string part_id;
        std::string obd;
        std::string name;
        std::string zakaz;
        std::string part_no;
        int izd_kol;
    };
    struct ReportData
    {
        std::string det_id;
        std::string obd; //`Обозначение`
        std::string name;//`Наименование`
        std::string kol;//`Кол-во`
        std::string ei;//`Ед. изм.`
        std::string mass;//`Масса детали`
        std::string obm;//obm
        std::string name_ei;//snameei
        std::string mater;//`Материал`
        std::string vz;//`Код заготовки`, "
        std::string kdz;//`Кол-во дет. в заг.`, "
        std::string masz;//`Масса заг.`, "
        std::string razz;//`Размеры заг.`, "
        std::string nrm;//`Норма расхода`, "
        std::string pm;//`Рассцеховка` "
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
    void BuildData      (DataList *data, const ObectData &obj);
    void DataToExcel    (const DataList &data, const ObectData &obj);

    void CheckList   (bool &new_page,
                         const size_t row_size,
                         const size_t start_row,
                         const size_t end_row,
                         const size_t template_page,
                         const size_t max_page_no,

                         const std::string &file_name,
                         const std::string &teml_file,

                         const std::string &title,

                         const ObectData &obj,

                         size_t &cur_row,
                         size_t &file_no,
                         size_t &list_no,
                         cExcel &xl);
};

}
#endif // MANUFACTURING_DETAILS_H
