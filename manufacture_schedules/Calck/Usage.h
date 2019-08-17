//---------------------------------------------------------------------------

#ifndef UsageH
#define UsageH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <ActnPopup.hpp>
#include <Menus.hpp>
#include <PlatformDefaultStyleActnCtrls.hpp>

#include "SQL.h"
#include "IconsData.h"
#include "string.h"
#include "functions.h"
#include "sstream.h"
#include "def_types.h"
#include <Buttons.hpp>
#include <Dialogs.hpp>
#include <map>
#include <xl_operations.h>
#include <boost/math/special_functions/round.hpp>

namespace data
{
class ZakazData
{
public:
    ZakazData(__uint64 zakaz_id, const AnsiString &zakaz)
        :zakaz_id(zakaz_id),zakaz(zakaz)
    {
    }
    virtual ~ZakazData()
    {}

    const __uint64 zakaz_id;
    const AnsiString zakaz;
};
class PartData : public ZakazData
{
public:
    PartData(long zakaz_id, const AnsiString &zakaz, __uint64 part_id, __uint64 part_no)
        :ZakazData(zakaz_id, zakaz),part_id(part_id),part_no(part_no)
    {}
    ~PartData()
    {}
    const __uint64 part_no;
    const __uint64 part_id;
};
class IzdData : public ZakazData
{
public:
    IzdData(long zakaz_id, const AnsiString &zakaz, __uint64 det_id, __uint64 kol, const AnsiString &obd)
        :ZakazData(zakaz_id, zakaz),det_id(det_id),kol(kol),obd(obd)
    {}
    ~IzdData()
    {}
    const __uint64 det_id;
    const __uint64 kol;
    const AnsiString obd;
};
}

namespace dbtmp
{

class NewOrdersQueue
{
public:
    struct Data
    {
        Data():
            record_id(0),
            det_id(0),
            kol(0),
            part_no(0),
            percent(0.0),
            ceh(""),
            utch(""),
            zakaz(""),
            obd("")
        {}
        __uint64 record_id;
        __uint64 det_id;
        __uint64 kol;
        __uint64 part_no;
        double percent;
        std::string ceh;
        std::string utch;
        std::string zakaz;

        std::string obd;
    };
    typedef std::list<Data> DataSet;

    NewOrdersQueue(cSQL *db):DB(db)
    {
        Create();
    }
    ~NewOrdersQueue()
    {
        Drop();
    }

    void AddZak (__uint64 zak_id, __uint64 kol, double persent, const std::string &ceh, const std::string &utch)
    {
        std::stringstream sql;
                sql << "insert ignore into `manufacture`.`new_orders_queue_tmp` (zakaz, det_id, obd, kol, percent, ceh, utch) "
                " select `c`.`zakaz`,`a`.`id`, `b`.`obd`, '"<<kol<<"', '"<<persent<<"', '"<<ceh<<"', '"<<utch<<"' "
                " from `market`.`zakaz` a "
                " join  `constructions`.`det_names` b on a.id = b.id "
                " join  `market`.`orders` c on a.zakaz_id = c.zakaz_id "
                " where a.zakaz_id = '"<<zak_id<<"'";
        DB->SendCommand(sql.str().c_str());
    }
    void AddDet (__uint64 zak_id,__uint64 det_id, __uint64 kol, double persent, const std::string &ceh, const std::string &utch)
    {
        std::stringstream sql;
                sql << "insert ignore into `manufacture`.`new_orders_queue_tmp` (zakaz, det_id, obd, kol, percent, ceh, utch) "
                " select ifnull(`c`.`zakaz`,'н/а'),`a`.`id`, `a`.`obd`, '"<<kol<<"', '"<<persent<<"', '"<<ceh<<"', '"<<utch<<"' "
                " from  `constructions`.`det_names` a "
                " left join  `market`.`zakaz` b on a.id = b.id and b.zakaz_id = '"<<zak_id<<"'"
                " left join  `market`.`orders` c on b.zakaz_id = c.zakaz_id "
                " where a.id = '"<<det_id<<"'";
        DB->SendCommand(sql.str().c_str());
    }
    void Clear (void)
    {
        DB->SendCommand("delete from `manufacture`.`new_orders_queue_tmp`;");
    }
    void Remove (__uint64 record_id)
    {
        std::stringstream sql;
        sql << "delete from `manufacture`.`new_orders_queue_tmp` where record_id = '"<< record_id<<"'" ;
        DB->SendCommand(sql.str().c_str());
    }
    DataSet& GetData (DataSet &out, __uint64 record_id = 0)
    {
        std::stringstream sql("select * from `manufacture`.`new_orders_queue_tmp` a ");
        std::stringstream where;
        if (record_id > 0)
            where << "where" << " `a`.`record_id` = '"<<record_id<<"'";

        sql << where.str();

        TADOQuery *rez = DB->SendSQL(sql.str().c_str());
        if (rez)
        {
            Data tmp;
            for (rez->First(); !rez->Eof; rez->Next())
            {
				tmp.record_id   = rez->FieldByName("record_id")->Value.operator __int64();
                tmp.det_id      = rez->FieldByName("det_id")->Value.operator __int64();
                tmp.kol         = rez->FieldByName("kol")->Value.operator __int64();
                tmp.percent     = rez->FieldByName("percent")->Value;
                tmp.ceh         = rez->FieldByName("ceh")->Value.operator AnsiString().c_str();
                tmp.utch        = rez->FieldByName("utch")->Value.operator AnsiString().c_str();
                tmp.zakaz       = rez->FieldByName("zakaz")->Value.operator AnsiString().c_str();
//                tmp.part_no     = rez->FieldByName("part_no")->Value.operator AnsiString().c_str();
                tmp.obd         = VinToGost(rez->FieldByName("obd")->Value).c_str();

                out.push_back(tmp);
            }
            delete rez;
		}
		return out;
    }

private:
    cSQL *DB;
    void Drop()
    {
        const char *sql = "Drop temporary table if exists `manufacture`.`new_orders_queue_tmp`;";
        DB->SendCommand(sql);
    }
    void Create()
    {
        const char *sql = "Create temporary table if not exists `manufacture`.`new_orders_queue_tmp`("
                "`record_id`  bigint UNSIGNED NOT NULL AUTO_INCREMENT ,"
                "`zakaz` varchar(6) NOT NULL,"
//                "`part_no` int(10) unsigned NOT NULL,"
                "`obd` varchar(100) NOT NULL,"
                "`kol`  bigint UNSIGNED NOT NULL ,"
                "`ceh`  char(2) NOT NULL ,"
                "`utch`  char(2) NOT NULL ,"
                "`det_id`  bigint UNSIGNED NOT NULL ,"
                "`percent`  double NOT NULL, "
                "PRIMARY KEY (`record_id`), "
                "UNIQUE KEY (`zakaz`,`det_id`) "
                ") ENGINE = MEMORY ";
        Drop();
        DB->SendCommand(sql);
    }
};
class StartedOrdersQueue
{
public:
    struct Data
    {
        Data():
            record_id(0),
            det_id(0),
            kol(0),
            part_no(0),
            percent(0.0),
            ceh(""),
            utch(""),
            zakaz(""),
            obd("")
        {}
        __uint64 record_id;
        __uint64 det_id;
        __uint64 kol;
        __uint64 part_no;
        double percent;
        std::string ceh;
        std::string utch;
        std::string zakaz;
        std::string obd;
    };
    typedef std::list<Data> DataSet;

    StartedOrdersQueue(cSQL *db):DB(db)
    {
        Create();
    }
    ~StartedOrdersQueue()
    {
        Drop();
    }

    void AddPart (__uint64 part_id, double persent, const std::string &ceh, const std::string &utch)
    {
        std::stringstream sql;
                sql << "insert ignore into `manufacture`.`started_orders_queue_tmp` (zakaz, part_no, det_id, obd, kol, percent, ceh, utch) "
                " select `c`.`zakaz`, `b`.`part_no`, `a`.`det_id`, `d`.`obd`, `a`.`kol`, '"<<persent<<"', '"<<ceh<<"', '"<<utch<<"' "
                " from `manufacture`.`part_content` a "
                " join `manufacture`.`parts` b on `b`.`part_id` =  `a`.`part_id` "
                " join `manufacture`.`zakaz_list` c on `c`.`zak_id` = `b`.`zak_id` "
                " join `manufacture`.`det_names` d on `d`.`det_id` = `a`.`det_id`"
                " where `a`.`part_id` = '"<<part_id<<"' and `a`.`in_work` is not null";
        DB->SendCommand(sql.str().c_str());
    }
    void Clear (void)
    {
        DB->SendCommand("delete from `manufacture`.`started_orders_queue_tmp`;");
    }    
    void Remove (__uint64 record_id)
    {
        std::stringstream sql;
        sql << "delete from `manufacture`.`started_orders_queue_tmp` where record_id = '"<< record_id<<"'" ;
        DB->SendCommand(sql.str().c_str());
    }
    DataSet& GetData (DataSet &out, __uint64 record_id = 0)
    {
        std::stringstream sql("select * from `manufacture`.`started_orders_queue_tmp` a ");
        std::stringstream where;
        if (record_id > 0)
            where << "where" << " `a`.`record_id` = '"<<record_id<<"'";

        sql << where.str();

        TADOQuery *rez = DB->SendSQL(sql.str().c_str());
        if (rez)
        {
            Data tmp;
            for (rez->First(); !rez->Eof; rez->Next())
            {
                tmp.record_id   = rez->FieldByName("record_id")->Value.operator __int64();
                tmp.det_id      = rez->FieldByName("det_id")->Value.operator __int64();
                tmp.kol         = rez->FieldByName("kol")->Value.operator __int64();
                tmp.percent     = rez->FieldByName("percent")->Value;
                tmp.ceh         = rez->FieldByName("ceh")->Value.operator AnsiString().c_str();
                tmp.utch        = rez->FieldByName("utch")->Value.operator AnsiString().c_str();
                tmp.zakaz       = rez->FieldByName("zakaz")->Value.operator AnsiString().c_str();
                tmp.part_no     = rez->FieldByName("part_no")->Value.operator __int64();
                tmp.obd         = VinToGost(rez->FieldByName("obd")->Value).c_str();

                out.push_back(tmp);
            }
            delete rez;
        }
        return out;
    }

private:
    cSQL *DB;
    void Drop()
    {
        const char *sql = "Drop temporary table if exists `manufacture`.`started_orders_queue_tmp`;";
        DB->SendCommand(sql);
    }
    void Create()
    {
        const char *sql = "Create temporary table if not exists `manufacture`.`started_orders_queue_tmp`("
                "`record_id`  bigint UNSIGNED NOT NULL AUTO_INCREMENT ,"
                "`zakaz` varchar(6) NOT NULL,"
                "`part_no` int(10) unsigned NOT NULL,"
                "`obd` varchar(100) NOT NULL,"
                "`kol`  bigint UNSIGNED NOT NULL ,"
                "`ceh`  char(2) NOT NULL ,"
                "`utch`  char(2) NOT NULL ,"
                "`det_id`  bigint UNSIGNED NOT NULL ,"
                "`percent`  double NOT NULL, "
                "PRIMARY KEY (`record_id`), "
                "UNIQUE KEY (`zakaz`,`part_no`,`det_id`) "
                ") ENGINE = MEMORY ";
        Drop();
        DB->SendCommand(sql);
    }
};
}

namespace calck
{
class EquipmentLoad
{
public:
    class Data
    {
    public:
        Data():plan(0.0),dificit(0.0)
        {
        }

        void AddRow(const std::string &obo, const std::string &part, double ksm, double plan_, double dificit_)
        {
            obo_data[obo] = ksm;
            zakaz_data[part] += dificit_;
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
            return boost::math::round((getMaximimLoad(sm) - dificit)*1000)/1000;;
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
    typedef std::map<const std::string, Data> RecordData;
    typedef std::map<const std::string, RecordData> DataSet;

    class SummaryInfo
    {
    public:
        SummaryInfo()
            :plan(0.0),deficit(0.0)
        {}
        void Add(double plan, double deficit)
        {
            this->plan += plan;
            this->deficit += deficit;
        }
        const double& GetPlan(void) const
        {
            return plan;
        }
        const double& GetDeficit(void) const
        {
            return deficit;
        }

    private:
        double plan;
        double deficit;
    };

    typedef std::map<const std::string, SummaryInfo> SummaryDetains;

    EquipmentLoad (cSQL *db,dbtmp::StartedOrdersQueue &st_queue,dbtmp::NewOrdersQueue &new_queue)
        :DB(db),path(""),use_listing(false),lists_by_file(10),templ("Y09102.xlt"),template_page(1)
    {
        Create();
        CalckStartedDets(st_queue);
        CalckPlannedDets(new_queue);
    }
    ~EquipmentLoad()
    {
        Drop();
    }

    DataSet& GetData (DataSet &out, SummaryDetains &summary_details, SummaryInfo &summary)
    {
        const char * sql = "select * from `manufacture`.`equipment_load_tmp` "
                " group by cex,utch, obo_group, oboid, zakaz_no, part_no";

        out.clear();
        summary = SummaryInfo();
        summary_details.clear();

        TADOQuery *rez = DB->SendSQL(sql);
        if (rez)
        {
            for (rez->First(); !rez->Eof; rez->Next())
            {
                std::string cex_name    =   (rez->FieldByName("cex_name")->Value.operator AnsiString()).c_str();
                std::string obo_group   =   (rez->FieldByName("obo_group")->Value.operator AnsiString()).c_str();
                std::string zakaz_no    =   (rez->FieldByName("zakaz_no")->Value.operator AnsiString()).c_str();
                std::string part_no     =   (rez->FieldByName("part_no")->Value.operator AnsiString()).c_str();
                std::string oboid       =   (rez->FieldByName("oboid")->Value.operator AnsiString()).c_str();

                double plan     =   rez->FieldByName("plan")->Value.operator double();
                double deficit  =   rez->FieldByName("deficit")->Value.operator double();
                double ksm      =   rez->FieldByName("ksm")->Value.operator double();

                Data &lnk = out[cex_name][obo_group];
                std::string inst_id = zakaz_no+" "+part_no;
                lnk.AddRow(oboid, inst_id, ksm, plan, deficit);
                summary_details[inst_id].Add(plan,deficit);
                summary.Add(plan,deficit);
            }
            delete rez;
        }
        return out;
    }
    void ToExcel(size_t days)
    {
        //инициализация
        TADOQuery *rez = DB->SendSQL("select value from administration.settings where property='template'");
        if (rez)
        {
            template_path = rez->FieldByName("Value")->Value.operator AnsiString().Trim().c_str();
            delete rez;
            rez = 0;
        }
        else
        {
            throw std::runtime_error("Не задан путь к шаблонам");
        }

        cur_lists = 0;
        file_no = 0;
        page_no = 0;

        //отчет

        DataSet rep_data;
        SummaryDetains summary_details;
        SummaryInfo summary;
        if (GetData(rep_data,summary_details, summary).size())
        {
            //включаем ексель
            cExcel xl;
            xl.Connect();
            xl.Visible(false);
            xl.DisplayAlerts(false);


            OpenTemplate(xl, template_path + templ);

            size_t row = 0;
            size_t empty_row_tmpl = 5;
            size_t group_row_tmpl = 3;
            size_t data_row_tmpl = 6;
            for (DataSet::const_iterator it_1 = rep_data.begin(); it_1!=rep_data.end(); ++it_1)
            {
                const RecordData &lnk = it_1->second;

                CheckList(xl, row, 1);

                // копирование
                xl.Range_Copy(xl.GetRows(xl.GetSheet(cur_lists+template_page), empty_row_tmpl, empty_row_tmpl));
                // вставка
                xl.Sheet_activate();
                xl.Range_Paste(xl.GetRows(row, row));

                xl.toCells(row, 1, it_1->first.c_str());//добавлям строчку цеха

                ++row;

                for (RecordData::const_iterator it_2 = lnk.begin(); it_2!=lnk.end(); ++it_2)
                {

                    const std::string &group = it_2->first;

                    const Data &lnk = it_2->second;

                    size_t rows_count = lnk.getRowsCount();
                    CheckList(xl, row, rows_count);

                    // копирование
                    xl.Range_Copy(xl.GetRows(xl.GetSheet(cur_lists+template_page), group_row_tmpl, group_row_tmpl));
                    // вставка
                    xl.Sheet_activate();
                    xl.Range_Paste(xl.GetRows(row, row));

                    if (rows_count > 1)
                    {
                        // копирование
                        xl.Range_Copy(xl.GetRows(xl.GetSheet(cur_lists+template_page), data_row_tmpl, data_row_tmpl));
                        xl.Sheet_activate();
                        for (size_t ofset = 1; ofset < rows_count; ++ofset)
                        {
                            xl.Range_Paste(xl.GetRows(row+ofset, row+ofset));
                        }
                    }
                    //добавляем данные по группе

                    xl.toCells(row, 1, group.c_str()         );
                    xl.toCells(row, 3, lnk.getOboCount()     );
                    xl.toCells(row, 4, lnk.getKsm()          );
                    xl.toCells(row, 5, lnk.getPlanLoad()     );
                    xl.toCells(row, 6, lnk.getDificitLoad()  );
                    xl.toCells(row, 7, lnk.getMaximimLoad(days));
                    xl.toCells(row, 8, lnk.getDelta(days)      );
                    xl.toCells(row, 9, ""                    );

                    std::list<std::string> dt = lnk.getZakazStrings();
                    size_t ofset = 1;
                    for (std::list<std::string>::const_iterator it = dt.begin(); it!=dt.end(); ++it)
                    {
                        const std::string &s = *it;
                        xl.toCells(row + ofset, 1, s.c_str());
                        ++ofset ;
                    }

                    row += rows_count;
                }
            }
            //вывод итогов
            CheckList(xl, row, 1);
            // копирование
            xl.Range_Copy(xl.GetRows(xl.GetSheet(cur_lists+template_page), data_row_tmpl, data_row_tmpl));
            // вставка
            xl.Sheet_activate();
            xl.Range_Paste(xl.GetRows(row, row));

            row += 1;

            for (SummaryDetains::const_iterator it = summary_details.begin(),end = summary_details.end(); it!=end; it++)
            {
                const SummaryInfo &lnk = it->second;
                CheckList(xl, row, 1);

                // копирование
                xl.Range_Copy(xl.GetRows(xl.GetSheet(cur_lists+template_page), data_row_tmpl, data_row_tmpl));
                // вставка
                xl.Sheet_activate();
                xl.Range_Paste(xl.GetRows(row, row));

                std::stringstream ss;
                ss<<it->first<<" План:"<<lnk.GetPlan()<<" Дефицит:"<<lnk.GetDeficit();
                xl.toCells(row, 1, ss.str().c_str());
                row += 1;
            }

            CheckList(xl, row, 1);
            // копирование
            xl.Range_Copy(xl.GetRows(xl.GetSheet(cur_lists+template_page), data_row_tmpl, data_row_tmpl));
            // вставка
            xl.Sheet_activate();
            xl.Range_Paste(xl.GetRows(row, row));
            row += 1;

            CheckList(xl, row, 1);
            // копирование
            xl.Range_Copy(xl.GetRows(xl.GetSheet(cur_lists+template_page), data_row_tmpl, data_row_tmpl));
            // вставка
            xl.Sheet_activate();
            xl.Range_Paste(xl.GetRows(row, row));

            std::stringstream ss;
            ss<<"Итого "<<" План:"<<summary.GetPlan()<<" Дефицит:"<<summary.GetDeficit();
            xl.toCells(row, 1, ss.str().c_str());

            if (!path.empty())//закрываем Excel в зависимости от опции сохранения в файл
            {
                SaveFile(xl,path ,"",cur_lists,file_no);
                xl.Book_Close(xl.GetBook(1));
                xl.Disconnect();
            }
            else
            {
                RemoveTemplates(xl,cur_lists);
                xl.Visible(true);
            }
        }
    }
    void ToCells (TStringGrid *sg, size_t days)
    {
		SGClear(sg);
        DataSet rep_data;
        SummaryDetains summary_details;
        SummaryInfo summary;
        if (GetData(rep_data,summary_details,summary).size())
        {
            for (DataSet::const_iterator it_1 = rep_data.begin(); it_1!=rep_data.end(); ++it_1)
            {
                const RecordData &lnk = it_1->second;
                sg->Cells[1][sg->RowCount - 1] = it_1->first.c_str();//добавлям строчку цеха
                ++sg->RowCount;
                for (RecordData::const_iterator it_2 = lnk.begin(); it_2!=lnk.end(); ++it_2)
                {
                    const std::string &group = it_2->first;
                    const Data &lnk = it_2->second;

                    //добавляем данные по группе
                    sg->Cells[1][sg->RowCount - 1] = group.c_str();
                    sg->Cells[2][sg->RowCount - 1] = lnk.getOboCount();
                    sg->Cells[3][sg->RowCount - 1] = lnk.getKsm();
                    sg->Cells[4][sg->RowCount - 1] = lnk.getPlanLoad();
                    sg->Cells[5][sg->RowCount - 1] = lnk.getDificitLoad();
                    sg->Cells[6][sg->RowCount - 1] = lnk.getMaximimLoad(days);
                    sg->Cells[7][sg->RowCount - 1] = lnk.getDelta(days);
                    sg->Cells[8][sg->RowCount - 1] = "";

                    /*std::list<std::string> dt = lnk.getZakazStrings();
                    size_t ofset = 1;
                    for (std::list<std::string>::const_iterator it = dt.begin(); it!=dt.end(); ++it)
                    {
                        const std::string &s = *it;
                        xl.toCells(row + ofset, 1, s.c_str());
                    }*/

                    ++sg->RowCount;
                }
            }

            ++sg->RowCount;

            for (SummaryDetains::const_iterator it = summary_details.begin(),end = summary_details.end(); it!=end; it++)
            {
                const SummaryInfo &lnk = it->second;

                sg->Cells[1][sg->RowCount - 1] = it->first.c_str();
                sg->Cells[2][sg->RowCount - 1] = " План:";
                sg->Cells[3][sg->RowCount - 1] = lnk.GetPlan();
                sg->Cells[4][sg->RowCount - 1] = " Дефицит:";
                sg->Cells[5][sg->RowCount - 1] = lnk.GetDeficit();
                ++sg->RowCount;
            }

            ++sg->RowCount;

            sg->Cells[1][sg->RowCount - 1] = "Итого";
            sg->Cells[2][sg->RowCount - 1] = " План:";
            sg->Cells[3][sg->RowCount - 1] = summary.GetPlan();
            sg->Cells[4][sg->RowCount - 1] = " Дефицит:";
            sg->Cells[5][sg->RowCount - 1] = summary.GetDeficit();
            ++sg->RowCount;
        }
        if (sg->RowCount > 2)
            --sg->RowCount;
        AutoWidthSG(sg);
    }

        //настройки размещения отчета
    std::string path;
    bool use_listing;
	size_t lists_by_file;
private:

    //шаблоны
    std::string template_path;//путь к файлу шаблона
    std::string templ;
    size_t template_page;

    //глобальные переменные
    size_t cur_lists;
    size_t page_no;
    size_t file_no;

    cSQL *DB;
    void Drop()
    {
        const char *sql = "Drop temporary table if exists `manufacture`.`equipment_load_tmp`;";
        DB->SendCommand(sql);
    }
    void Create()
    {

        const char *sql = "Create temporary table if not exists `manufacture`.`equipment_load_tmp`("
                "`cex_name` char(25) NOT NULL,"
                "`utch_name` char(25) NOT NULL,"
                "`cex`  char(2) NOT NULL ,"
                "`utch`  char(2) NOT NULL ,"
                "`obo_group` varchar(128) NOT NULL,"
                "`zakaz_no` varchar(6) NOT NULL,"
                "`part_no` varchar(30) NOT NULL,"
                "`oboid` varchar(5) NOT NULL,"
                "`plan` double NOT NULL,"
                "`deficit` double  NOT NULL,"
                "`ksm` double NOT NULL"
                ") ENGINE = MEMORY ";
        Drop();
        DB->SendCommand(sql);
    }

    void CalckStartedDets (dbtmp::StartedOrdersQueue &queue)
    {
        // извлеч по 1 и развернуть
        dbtmp::StartedOrdersQueue::DataSet dt;
        queue.GetData(dt);

        const char *step1_tmp_drop = "drop temporary table if exists `manufacture`.`step_1`;";
        const char *step1_tmp_create = " create temporary table if not exists `manufacture`.`step_1`("
                                    " `det_id` bigint(20) unsigned NOT NULL, "
                                    " `zakaz` varchar(6) NOT NULL, "
                                    " `part_no` bigint(20) unsigned NOT NULL, "
                                    " `ceh`  char(2) NOT NULL ,"
                                    " `utch`  char(2) NOT NULL ,"
                                    " `percent`  double NOT NULL, "
                                    " key det_id (`det_id`),"
                                    " unique key un(`det_id`, `zakaz`, `part_no`)"
                                    " ) ENGINE = MEMORY";

        //этап 1 получить список деталей
        DB->SendCommand(step1_tmp_drop);
        DB->SendCommand(step1_tmp_create);
        for (dbtmp::StartedOrdersQueue::DataSet::const_iterator it = dt.begin(), end = dt.end(); it!=end; ++it)
        {
            const dbtmp::StartedOrdersQueue::Data &lnk = *it;
            std::stringstream sql;
            sql<< "Call `manufacture`.`GetContent`(0,0,0,"<<lnk.det_id<<",0)";
            DB->SendCommand(sql.str().c_str());

            sql.str("");

            sql << "insert into `manufacture`.`step_1` (`zakaz`,`part_no`,`det_id`, `ceh`, `utch`, `percent`) "
                   "select DISTINCT '"<<lnk.zakaz<<"', '"<<lnk.part_no<<"', `a`.`det_id`, '"<<lnk.ceh<<"', '"<<lnk.utch<<"', '"<<lnk.percent<<"' "
                   "from `manufacture`.`output` a "
                   "join `manufacture`.`marsh_lists` b on `a`.`det_id` = `b`.`det_id` ";
            DB->SendCommand(sql.str().c_str());
        }

        //этап 2 получить нормы для деталей с оборудованием
        std::stringstream sql;
        sql <<
               "insert into `manufacture`.`equipment_load_tmp` (cex_name, utch_name, cex, utch, obo_group, zakaz_no, part_no, oboid, plan, deficit, ksm) "
			   "select "
			   "IFNULL(g1.npodr, 'Н/а цех' )     as cex_name, "
			   "IFNULL(g2.npodr, 'Н/а участок' )     as utch_name, "
               "c.cex        as cex, "
               "c.utch       as utch, "
               "IFNULL(f.name, 'Неизвестная группа')       as obo_group, "
               "a.zakaz      as zakaz_no, "
               "a.part_no    as part_no, "
               "c.oboID      as oboid, "
               "ROUND(sum( "
               "if (`c`.`cex` = '03' and `c`.`utch` = '04', "
               "IFNULL(`d`.`tsht`*ceil(d1.kol_request/ifnull(`h`.`kdz`,1))/d1.kol_request*d1.kol_request+if(d1.kol_request>0,`d`.`tpz`,0),0)*a.percent/100, "
               "IFNULL(`d`.`tsht`*`d`.`ksht`*`d`.`krop`/`d`.`kolod`*d1.kol_request+if(d1.kol_request>0,`d`.`tpz`,0),0)*a.percent/100)),3) as plan, "
               "ROUND(sum( "
               "if (`c`.`cex` = '03' and `c`.`utch` = '04', "
               "IFNULL(`d`.`tsht`*ceil(d1.kol_request/ifnull(`h`.`kdz`,1))/d1.kol_request*(d1.kol_request - d1.kol_maked)+if((d1.kol_request - d1.kol_maked)>0,`d`.`tpz`,0),0)*a.percent/100, "
               "IFNULL(`d`.`tsht`*`d`.`ksht`*`d`.`krop`/`d`.`kolod`*(d1.kol_request - d1.kol_maked)+if((d1.kol_request - d1.kol_maked)>0,`d`.`tpz`,0),0)*a.percent/100)),3) as deficit, "
               "e.ksme as ksm "

               "from `manufacture`.`step_1` a "
               "join `manufacture`.`operation_list` c   on `c`.`det_id` = `a`.`det_id` "
               "join `manufacture`.`operation_norms` d  on `d`.`OpUUID` = `c`.`OpUUID` "
               "join `manufacture`.`orders` d1  on `d1`.`operation_id` = `c`.`OpUUID` "

               " join `equipment`.`obor_list` e     on `e`.`oboID` = `c`.`oboID` "
               " left join `equipment`.`obor_groups` e1  on `e1`.`oboID` = `e`.`oboID` "
               " left join `equipment`.`groups` f        on `f`.`group_id` = `e1`.`group_id` "

               " left join `catalogs`.`podr_list` g1     on `g1`.`cex` = `c`.`cex` and `g1`.`utch` = '' "
               " left join `catalogs`.`podr_list` g2     on `g2`.`cex` = `c`.`cex` and `g2`.`utch` = `c`.`utch` "
               " left join `manufacture`.`det_info` h    on `h`.`det_id` = `a`.`det_id` "
               "where if(a.ceh !='', c.cex = a.ceh, 1) and if(a.utch !='', c.utch = a.utch, 1) "
               "group by c.cex,c.utch,f.name, c.oboID, a.zakaz, a.part_no";
        DB->SendCommand(sql.str().c_str());
        DB->SendCommand(step1_tmp_drop);
    }
    void CalckPlannedDets (dbtmp::NewOrdersQueue &queue)
    {
        // извлеч по 1 и развернуть
        dbtmp::NewOrdersQueue::DataSet dt;
        queue.GetData(dt);
        const char *step1_tmp_drop = "drop temporary table if exists `manufacture`.`step_1`;";
        const char *step1_tmp_create = " create temporary table if not exists `manufacture`.`step_1`("
                                    " `det_id` bigint(20) unsigned NOT NULL, "
                                    " `zakaz` varchar(6) NOT NULL, "
                                    " `part_no` bigint(20) unsigned NOT NULL, "
                                    " `kol` bigint(20) unsigned NOT NULL, "
                                    " `ceh`  char(2) NOT NULL ,"
                                    " `utch`  char(2) NOT NULL ,"
                                    " `percent`  double NOT NULL, "
                                    " key det_id (`det_id`),"
                                    " unique key un(`det_id`, `zakaz`, `part_no`)"
                                    " ) ENGINE = MEMORY";

        //этап 1 получить список деталей
        DB->SendCommand(step1_tmp_drop);
        DB->SendCommand(step1_tmp_create);
        for (dbtmp::NewOrdersQueue::DataSet::const_iterator it = dt.begin(), end = dt.end(); it!=end; ++it)
        {
            const dbtmp::NewOrdersQueue::Data &lnk = *it;
            std::stringstream sql;
            sql<< "Call `constructions`.`GetDetInUzel`("<<lnk.det_id<<","<<lnk.kol<<")";
            DB->SendCommand(sql.str().c_str());

            sql.str("");

            sql << "insert into `manufacture`.`step_1` (`zakaz`,`part_no`,`kol`,`det_id`, `ceh`, `utch`, `percent`) "
                   "select '"<<lnk.zakaz<<"', '"<<lnk.part_no<<"', `a`.`kol`,`a`.`idc`, '"<<lnk.ceh<<"', '"<<lnk.utch<<"', '"<<lnk.percent<<"' "
                   "from `constructions`.`output` a ";
            DB->SendCommand(sql.str().c_str());
        }

        //этап 2 получить нормы для деталей с оборудованием
        std::stringstream sql;
        sql <<
               "insert into `manufacture`.`equipment_load_tmp` (cex_name, utch_name, cex, utch, obo_group, zakaz_no, part_no, oboid, plan, deficit, ksm) "
               "select "
			   "IFNULL(g1.npodr, 'Н/а цех' )     as cex_name, "
			   "IFNULL(g2.npodr, 'Н/а участок' )     as utch_name, "
               "c.cex        as cex, "
               "c.utch       as utch, "
               "IFNULL(f.name, 'Неизвестная группа')       as obo_group, "
               "a.zakaz      as zakaz_no, "
               "a.part_no    as part_no, "
               "c.oboID      as oboid, "

               "ROUND(sum( "
               "if (`c`.`cex` = '03' and `c`.`utch` = '04', "
               "IFNULL(`d`.`tsht`*ceil(a.kol/ifnull(`h`.`kdz`,1))/a.kol*a.kol+if(a.kol>0,`d`.`tpz`,0),0)*a.percent/100, "
               "IFNULL(`d`.`tsht`*`d`.`ksht`*`d`.`krop`/`d`.`kolod`*a.kol+if(a.kol>0,`d`.`tpz`,0),0)*a.percent/100)),3) as plan, "

               "ROUND(sum( "
               "if (`c`.`cex` = '03' and `c`.`utch` = '04', "
               "IFNULL(`d`.`tsht`*ceil(a.kol/ifnull(`h`.`kdz`,1))/a.kol*a.kol+if(a.kol>0,`d`.`tpz`,0),0)*a.percent/100, "
               "IFNULL(`d`.`tsht`*`d`.`ksht`*`d`.`krop`/`d`.`kolod`*a.kol+if(a.kol>0,`d`.`tpz`,0),0)*a.percent/100)),3) as deficit, "

               "e.ksme as ksm "

               "from `manufacture`.`step_1` a "
               "join `technologic`.`operation_list` c   on `c`.`id` = `a`.`det_id` "
               "join `technologic`.`operation_norms` d  on `d`.`OpUUID` = `c`.`OpUUID` "

               " join `equipment`.`obor_list` e     on `e`.`oboID` = `c`.`oboID` "
               " left join `equipment`.`obor_groups` e1  on `e1`.`oboID` = `e`.`oboID` "
               " left join `equipment`.`groups` f        on `f`.`group_id` = `e1`.`group_id` "

               " left join `catalogs`.`podr_list` g1     on `g1`.`cex` = `c`.`cex` and `g1`.`utch` = '' "
               " left join `catalogs`.`podr_list` g2     on `g2`.`cex` = `c`.`cex` and `g2`.`utch` = `c`.`utch` "
               " left join `technologic`.`det_info` h    on `h`.`id` = `a`.`det_id` "
               "where if(a.ceh !='', c.cex = a.ceh, 1) and if(a.utch !='', c.utch = a.utch, 1) "
               "group by c.cex,c.utch,f.name, c.oboID, a.zakaz, a.part_no";
        DB->SendCommand(sql.str().c_str());
        DB->SendCommand(step1_tmp_drop);
    }

    void CheckList (cExcel &xl, size_t &row, size_t row_size)
    {

        const size_t start_row = 4, end_row = 58;

        bool new_page = !row + (row + row_size > end_row);//проанализировать количестко оставшихся строк

        if (new_page)
        {
            if (cur_lists)
            {
                if (use_listing && !path.empty())
                {//проверяем количество страниц, если выставлена опция
                    TrimFile(xl,path,"",cur_lists,lists_by_file,template_path + templ,file_no);
                }
            }

            //создать страницу
            xl.Sheet_Copy(xl.GetSheet(cur_lists+template_page), xl.GetSheet(cur_lists+1), Variant().NoParam());
            cur_lists++ ;
            page_no++;
            xl.SetActiveSheet(xl.GetSheet(cur_lists));
            std::stringstream buf;
            buf<<page_no;
            xl.Set_Sheet_Name(xl.GetSheet(cur_lists),("ФY09102-"+buf.str()).c_str());

            // почистить лист
            // копирование
            xl.Range_Copy(xl.GetRows(xl.GetSheet(cur_lists+template_page), 7, 9));
            // вставка
            xl.Sheet_activate();
            xl.Range_Paste(xl.GetRows(4, 6));

            //заполнить шапку

            xl.toCells(2,   1,   Now().FormatString("dd.mm.yyyy")           );

            row = start_row;
        }
    }
};

}
//---------------------------------------------------------------------------
class TResourceUsage : public TFrame
{
__published:	// IDE-managed Components
	TPageControl *PageControl1;
	TTabSheet *TabSheet1;
	TTabSheet *TabSheet2;
	TTreeView *ManufactureTree;
	TTreeView *DevelopTree;
	TPageControl *PageControl2;
	TTabSheet *TabSheet3;
	TPanel *Panel1;
	TPanel *Panel2;
	TSplitter *Splitter1;
	TSplitter *Splitter2;
	TLabel *Label1;
	TLabel *Label2;
	TStringGrid *zap_sg;
	TTabSheet *TabSheet4;
	TPanel *Panel3;
	TLabeledEdit *StartedParams;
	TPanel *Panel4;
	TLabeledEdit *NewParams;
	TCheckBox *Show_Closed;
	TPopupActionBar *PAB1;
	TMenuItem *AddStarted;
	TPopupActionBar *PAB2;
	TMenuItem *AddNew;
	TPopupActionBar *PAB3;
	TMenuItem *StartedClear;
	TMenuItem *StartedRemove;
	TPopupActionBar *PAB4;
	TMenuItem *NewClear;
	TMenuItem *NewRemove;
	TStringGrid *plan_sg;
	TButton *FindStarted;
	TButton *FindNew;
	TPanel *Panel5;
	TStringGrid *Previe;
	TBitBtn *ToExcel;
	TBitBtn *StartCalck;
	TRadioGroup *CalckPeroid;
	TLabeledEdit *MonthDays;
	TLabeledEdit *PeriodDays;
	TButton *SetFile;
	TLabeledEdit *FileName;
	TCheckBox *ActiveDelimiter;
	TEdit *Count;
	TLabel *Label3;
	TSaveDialog *SD;
    void __fastcall FindStartedClick(TObject *Sender);
    void __fastcall FindNewClick(TObject *Sender);
    void __fastcall TVDeletion(TObject *Sender, TTreeNode *Node);
	void __fastcall AddStartedClick(TObject *Sender);
	void __fastcall AddNewClick(TObject *Sender);
	void __fastcall StartedParamsKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall NewParamsKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall StartedClearClick(TObject *Sender);
	void __fastcall StartedRemoveClick(TObject *Sender);
	void __fastcall NewClearClick(TObject *Sender);
	void __fastcall NewRemoveClick(TObject *Sender);
	void __fastcall SetFileClick(TObject *Sender);
	void __fastcall ToExcelClick(TObject *Sender);
	void __fastcall FileNameChange(TObject *Sender);
	void __fastcall StartCalckClick(TObject *Sender);
private:	// User declarations
    const int &LUser;
	IconsData *IcoData;
    cSQL *DB;

    dbtmp::NewOrdersQueue new_orders;
    dbtmp::StartedOrdersQueue started_orders;
    calck::EquipmentLoad *calck_equipmen_load;

    void UpdateStarted(void);
    void UpdateNew(void);
    void UpdatePrevie(void);
    void RecalckEquipLoad(void);
    void CleanEquipLoad(void);


public:		// User declarations
	__fastcall TResourceUsage(TComponent* Owner,TWinControl *_p, int &_LUser,cSQL *db,IconsData *_IcoData);
};
#endif
