//---------------------------------------------------------------------------

#include <windows.h>
#pragma hdrstop

#include <tchar.h>
#include <windows.h>
#include <cstring.h>
//---------------------------------------------------------------------------
using namespace std;
#pragma argsused
const int buff_size=1024;
bool FileExists(string name);
string GetSystemDir(char *Path);
WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	char buff[buff_size]={0};
	GetEnvironmentVariable("ProgramFiles",buff,buff_size);
	string  programm_files(buff);
	GetModuleFileName(hInstance,&buff[0],buff_size);//получено полное им€ запускаемого файла
	string 	exe_name(buff),
			odbc_name="ServerFBase.dsn",//им€ источника данных
			odbc_destinate_path=programm_files+"\\Common Files\\ODBC\\Data Sources"; //целевое место расположени€ источника

	int part_pos=exe_name.find_last_of('\\'), //получение позиции оконцини€ пути файла
		ext_pos=exe_name.find_last_of('.');   //позици€ начала расширени€ файла
	string 	exe_path=exe_name.substr(0,part_pos+1),//получение пути к файлу
			prog_name=exe_name.substr(part_pos+1,ext_pos-(part_pos+1)),//название прграммы(им€ запущенной программы без разрешени€ и пути)
			resource_path=exe_path+"комплект перемещени€",//получение пути к €рлыкам дл€ перемещени€
			odbc_source=resource_path+"\\"+odbc_name,//путь к источнику данных
			odbc_destinate=odbc_destinate_path+"\\"+odbc_name,//им€ перемещенного источника данных
			link_source=resource_path+"\\"+prog_name+".lnk",//им€ перемеща€емого €рлыка
			link_destinate=GetSystemDir("Desktop")+"\\"+prog_name+".lnk";//им€ перемещенного €рлыка
	//проверка наличи€ дирректории
	bool rez(true);
	if (!FileExists(odbc_destinate_path))
	{//создаем путь если его нет
		string subpart=programm_files+"\\Common Files\\ODBC";
		rez=CreateDirectory(subpart.c_str(),NULL);
		rez=CreateDirectory(odbc_destinate_path.c_str(),NULL);
	}
	CopyFile(link_source.c_str(),link_destinate.c_str(),false);
	CopyFile(odbc_source.c_str(),odbc_destinate.c_str(),false);
	return 0;
}
bool FileExists(string name)
{
	return GetFileAttributes(name.c_str())!=INVALID_FILE_ATTRIBUTES;
}
string GetSystemDir(char *Path)
{
	char buff[buff_size]={0};
	DWORD path=sizeof(buff);
	//открыть реестр
	HKEY rKey;
	if (ERROR_SUCCESS==RegOpenKeyExA(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Shell Folders\\",0,
				 KEY_QUERY_VALUE,&rKey)) //октрыть ключ
	{
		RegQueryValueEx(rKey,Path,NULL,NULL,buff,&path);//прочитать параметр
		RegCloseKey(rKey);   //закрыть ключ
	}

	return string(buff);
}
