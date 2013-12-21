#include "xl_operations.h"

void OpenTemplate  (cExcel &xl,const std::string &templ)
{
    xl.SetActiveBooks(xl.Books_Open(templ.c_str()));
    // Инициализация переменных указателей на итемы екселя
    xl.SetActiveBook(xl.GetFirstBook());
    xl.SetActiveSheets(xl.GetSheets());
    xl.SetActiveSheet(xl.GetFirstSheet());
}
void SaveFile       (cExcel &xl, const std::string &name, const std::string &ext, const int &lists)
{
    while(lists&&lists<xl.GetSheetsCount())
    {
        xl.Sheet_Del(xl.GetSheet(xl.GetSheetsCount()));
    }
    xl.Sheet_activate(xl.GetFirstSheet());
    xl.Books_Save(name+ext);
}
void TrimFile       (cExcel &xl,const std::string &name, const std::string &ext, int &lists, int max_list_no, const std::string &templ)
{
    static std::string prev_file_name="";
    static int file_no=0;

    if (lists&&lists>=max_list_no)
    {
        if (prev_file_name!=name)
        {
            file_no=0;
            prev_file_name=name;
        }
        else
        {
            ++file_no;
        }

        String addin;
        if (file_no)
        {
            addin="_"+String(file_no);
        }
        SaveFile(name+addin,ext,lists);
        xl.Book_Close(xl.GetBook(1));
        OpenTemplate(xl, templ);
        lists=0;
    }
}
