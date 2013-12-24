#include "xl_operations.h"

void OpenTemplate  (cExcel &xl,const std::string &templ)
{
    xl.SetActiveBooks(xl.Books_Open(templ.c_str()));
    // Инициализация переменных указателей на итемы екселя
    xl.SetActiveBook(xl.GetFirstBook());
    xl.SetActiveSheets(xl.GetSheets());
    xl.SetActiveSheet(xl.GetFirstSheet());
}
void RemoveTemplates(cExcel &xl,const size_t &lists)
{
    while(lists&&lists<xl.GetSheetsCount())
    {
        xl.Sheet_Del(xl.GetSheet(xl.GetSheetsCount()));
    }
    xl.Sheet_activate(xl.GetFirstSheet());
}
void SaveFile       (cExcel &xl, const std::string &name, const std::string &ext, const size_t &lists)
{
    RemoveTemplates(xl,lists);
    xl.Books_Save((name+ext).c_str());
}
void TrimFile       (cExcel &xl,const std::string &name, const std::string &ext, size_t &lists, int max_list_no, const std::string &templ)
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

		std::stringstream addin;
        if (file_no)
		{
			addin << "_" << file_no;
        }
        SaveFile(xl, name+addin.str(),ext,lists);
        xl.Book_Close(xl.GetBook(1));
        OpenTemplate(xl, templ);
        lists=0;
    }
}
