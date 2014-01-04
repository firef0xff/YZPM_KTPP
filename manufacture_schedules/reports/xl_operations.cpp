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
void SaveFile       (cExcel &xl, const std::string &name, const std::string &ext, const size_t &lists, size_t &file_no)
{
	RemoveTemplates(xl,lists);

	std::stringstream addin;
	if (file_no)
	{
		addin << "_" << file_no;
	}

	std::string file_name = name + addin.str();

	if (!ext.empty())
	{
		file_name += "."+name;
	}
	xl.Books_Save(file_name.c_str());
	++file_no;
}
void TrimFile       (cExcel &xl,const std::string &name, const std::string &ext, size_t &lists, int max_list_no, const std::string &templ, size_t &file_no)
{
    if (lists&&lists>=max_list_no)
    {
		SaveFile(xl, name,ext,lists,file_no);
        xl.Book_Close(xl.GetBook(1));
        OpenTemplate(xl, templ);
        lists=0;
    }
}
