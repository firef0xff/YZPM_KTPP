#ifndef REP16_H
#define REP16_H
#include <reports/report.h>
#include <xl_operations.h>
#include "functions.h"
#include "sstream.h"
#include <boost/math/special_functions/round.hpp>

namespace rep
{

class Rep16 : public Report
{
public:
	Rep16(int set);
	~Rep16();

    Rep16(const Rep16 &r);

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
    size_t page_no;
    size_t file_no;
	size_t template_page;

	struct OpData
	{
		std::string tsht;
		std::string count;
		std::string date;
	};
	struct Data
	{
		std::string obd;
		std::string name;
		std::string mater;
		std::string raz_zag;
		std::string kod_mat;
		std::string count;
	};
	typedef 	std::vector<Data> DataSet;
	typedef 	std::map< std::string, OpData > DataOpers;
	typedef 	std::map< std::string, DataOpers > DataOpersSet;

    void ParseParams    (void);
    void LoadSettings   (void);
	void BuildReport    (void);

	//формирует шапку для заказа с нужным количеством операций и коопераций
	void StartXL();
	void StopXL();
	void AddPage( std::string const& zak );
	void CreateHead     ( std::string const& zak, int op, int coop, int rows );
	void PrintBody( DataSet const& , DataOpersSet const&, DataOpersSet const& );

	boost::shared_ptr<cExcel>  mXL;

    //void CheckList (cExcel &xl, size_t &row, size_t row_size);
};

}

#endif // Y09102_H
