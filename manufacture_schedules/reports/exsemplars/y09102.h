#ifndef Y09102_H
#define Y09102_H
#include <reports/report.h>
#include <xl_operations.h>
#include "functions.h"
#include "sstream.h"
#include <boost/math/special_functions/round.hpp>

namespace rep
{

class Y09102 : public Report
{
public:
    Y09102(int set);
    ~Y09102();

    Y09102(const Y09102 &r);

    void Build(void);
    boost::shared_ptr<rep::Report> SelfCopy (void) const;

private:

    class Data
    {
    public:
        Data():plan(0.0),dificit(0.0)
        {
        }

        void AddRow(const std::string &obo, const std::string &part, double ksm, double plan_, double dificit_)
        {
            obo_data[obo] = ksm;
            zakaz_data[part] += plan_;
            plan += plan_;
            dificit += dificit_;
        }

        size_t getOboCount(void) const
        {
            return obo_data.size();
        }
        double getKsm (void) const
        {
            double res = 0.0;
            for(std::map<const std::string, double>::const_iterator it = obo_data.begin(), end = obo_data.end(); it!=end; ++it)
            {
                const std::pair<const std::string, double> &lnk = *it;
                res+=lnk.second;
            }
            if (obo_data.size())
                res = res/obo_data.size();

            return res;
        }

        double getPlanLoad      (void) const
        {
            return plan;
        }
        double getDificitLoad   (void) const
        {
            return dificit;
        }
		double getMaximimLoad   (double sm) const
		{
			double res = 8.0*sm*getOboCount()*getKsm()*0.92;
			return boost::math::round(res*1000)/1000;
        }
        double getDelta         (double sm) const
        {
            return boost::math::round((getMaximimLoad(sm) - plan)*1000)/1000;;
        }

        std::list<std::string> getZakazStrings(void) const
        {
            std::list<std::string> res;
            std::stringstream buf;
            for(std::map<const std::string, double>::const_iterator it = zakaz_data.begin(), end = zakaz_data.end(); it!=end; ++it)
            {
                const std::pair<const std::string, double> &lnk = *it;
                buf << lnk.first << "-" << lnk.second << "; ";
            }
			WordWrap(res,buf.str(), 95 ," ");
			return res;
        }

        size_t getRowsCount     (void) const
        {
            return getZakazStrings().size()+1;
        }

    private:
        std::map<const std::string, double> obo_data;
        std::map<const std::string, double> zakaz_data;

        std::list<std::string> zakaz_strings;

        double plan;
        double dificit;

    };

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
	double sm;

    void ParseParams    (void);
    void LoadSettings   (void);
    void BuildReport    (void);

    void CheckList (cExcel &xl, size_t &row, size_t row_size);
};

}

#endif // Y09102_H
