#ifndef XL_OPERATIONS_H
#define XL_OPERATIONS_H
#include <string>
#include "Excel.h"

void OpenTemplate   (cExcel &xl,const std::string &templ);
void SaveFile       (cExcel &xl,const std::string &name,const std::string &ext, const int &lists);
void TrimFile       (cExcel &xl, const std::string &name, const std::string &ext, int &lists, int max_list_no, const std::string &templ);


#endif // XL_OPERATIONS_H
