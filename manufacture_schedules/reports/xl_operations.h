#ifndef xl_operationsH
#define xl_operationsH
#include <string>
#include "sstream.h"
#include "Excel.h"

void OpenTemplate   (cExcel &xl,const std::string &templ);
void RemoveTemplates(cExcel &xl,const size_t &lists);
void SaveFile       (cExcel &xl,const std::string &name,const std::string &ext, const size_t &lists, size_t &file_no);
void TrimFile       (cExcel &xl, const std::string &name, const std::string &ext, size_t &lists, int max_list_no, const std::string &templ, size_t &file_no);


#endif // XL_OPERATIONS_H
