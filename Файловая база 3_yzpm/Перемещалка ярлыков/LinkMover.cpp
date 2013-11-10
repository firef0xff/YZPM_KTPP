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
	GetModuleFileName(hInstance,&buff[0],buff_size);//�������� ������ ��� ������������ �����
	string 	exe_name(buff),
			odbc_name="ServerFBase.dsn",//��� ��������� ������
			odbc_destinate_path=programm_files+"\\Common Files\\ODBC\\Data Sources"; //������� ����� ������������ ���������

	int part_pos=exe_name.find_last_of('\\'), //��������� ������� ��������� ���� �����
		ext_pos=exe_name.find_last_of('.');   //������� ������ ���������� �����
	string 	exe_path=exe_name.substr(0,part_pos+1),//��������� ���� � �����
			prog_name=exe_name.substr(part_pos+1,ext_pos-(part_pos+1)),//�������� ��������(��� ���������� ��������� ��� ���������� � ����)
			resource_path=exe_path+"�������� �����������",//��������� ���� � ������� ��� �����������
			odbc_source=resource_path+"\\"+odbc_name,//���� � ��������� ������
			odbc_destinate=odbc_destinate_path+"\\"+odbc_name,//��� ������������� ��������� ������
			link_source=resource_path+"\\"+prog_name+".lnk",//��� �������������� ������
			link_destinate=GetSystemDir("Desktop")+"\\"+prog_name+".lnk";//��� ������������� ������
	//�������� ������� �����������
	bool rez(true);
	if (!FileExists(odbc_destinate_path))
	{//������� ���� ���� ��� ���
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
	//������� ������
	HKEY rKey;
	if (ERROR_SUCCESS==RegOpenKeyExA(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Shell Folders\\",0,
				 KEY_QUERY_VALUE,&rKey)) //������� ����
	{
		RegQueryValueEx(rKey,Path,NULL,NULL,buff,&path);//��������� ��������
		RegCloseKey(rKey);   //������� ����
	}

	return string(buff);
}
