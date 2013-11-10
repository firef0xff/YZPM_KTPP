
#pragma hdrstop
#include "FRowData.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

		FRowData::FRowData(cSQL *const _DB,const int &_LUser,const String &File,const int &id,const String &_base,const char &_type)
:FileRow(_DB,_LUser),type(_type),base(_base)
{
count++;
init();
FileName=ExtractFileName(File);
inProjectPath=ExtractFilePath(File);
switch (type)
	{
	case 0:{UpdateVal(FileName);break;}//загрузка файлов в базу
	case 1:{UpdateVal(id);break;}//получение файлов из базы
	case 2:{UpdateVal(id);break;}//удаление файлов из базы
	default:{UpdateVal(FileName);break;}
	}
}
		FRowData::FRowData(const FRowData &r):FileRow(r),type(r.type),base(r.base)
{
count++;
inBaseFileName=r.inBaseFileName;
inProjectPath=r.inProjectPath;
Action=r.Action;  
inbase=r.inbase;
}
		FRowData::~FRowData(void)
{
count--;
}
void 	FRowData::init(void)
{
inBaseFileName="";
FilePath="";
Action="Нет";  
inbase=false;
}
void 	FRowData::UpdateVal(String obd)
{
SetData(DB->SendSQL("Call constructions.FindObdForFile('"+GostToVin(obd)+"','"+FileName+"','"+String(LUser)+"')"));
}
void 	FRowData::UpdateVal(int id)
{
SetData(DB->SendSQL("Call constructions.GetDataForFileAndID('"+String(id)+"','"+FileName+"','"+String(LUser)+"')"));
}
void 	FRowData::SetData (TADOQuery *rez)
{
if (rez&&rez->RecordCount)
	{
	//данные для сетки
	SetId(rez->FieldByName("id")->Value);
	SpRazd=rez->FieldByName("razdSPID")->Value;
	SetObd(rez->FieldByName("obd")->Value);
	Name=rez->FieldByName("DetName")->Value;
	SpRazdName=rez->FieldByName("Razdname")->Value;
	Accept=rez->FieldByName("Accept")->Value;
	FilePath=rez->FieldByName("FileInBase")->Value.operator UnicodeString();
	inBaseFileName=rez->FieldByName("InBaseName")->Value.operator UnicodeString();
	String _FileName=rez->FieldByName("InProjName")->Value;
	String _inProjectPath=rez->FieldByName("FileInProj")->Value;
	if (FilePath==""&&inBaseFileName=="")
		{
		inbase=false;
		}else
		{
		FileName=_FileName;
		if (type)
			{
			inProjectPath=_inProjectPath;
			}
        inbase=true;
		}
	icoID=rez->FieldByName("icoID")->Value;
	//информация о добавлении
	Creator=rez->FieldByName("Creator")->Value;
	Updater=rez->FieldByName("Updater")->Value;
	if (rez->FieldByName("DateOfCreate")->Value.IsNull())
		{
		DateOfCreate=0;
		}else
		{
		DateOfCreate=rez->FieldByName("DateOfCreate")->Value.operator TDateTime();
		}
	if (rez->FieldByName("DateOfUpdate")->Value.IsNull())
		{
		DateOfUpdate=0;
		}else
		{
		DateOfUpdate=rez->FieldByName("DateOfUpdate")->Value.operator TDateTime();
		}
	SetAction();
	}
delete rez;
}
void 	FRowData::SetData 	(
				const int &_id,		const int &_SpRazd,
				const String &_Obd,	const String &_Name,
				const String &_SpRazdName,
				const int &_icoID,		const String &_FileName,	const String &_FilePath,
				const String &_Creator,	const String &_Updater,	const bool &_Accept,
				const TDateTime &_DateOfCreate,	const TDateTime &_DateOfUpdate,

				String &_inBaseFileName,	String &_inProjectPath
				)
{
	//данные для сетки
id=_id;
SpRazd=_SpRazd;
SetObd(_Obd);
Name=_Name;
SpRazdName=_SpRazdName;
Accept=_Accept;
FilePath=_FilePath;
inBaseFileName=_inBaseFileName;
FileName=_FileName;
inProjectPath=_inProjectPath;
if (FilePath==""&&inBaseFileName=="")
	{
	inbase=false;
	}else
	{
	inbase=true;
	}
icoID=_icoID;
	//информация о добавлении
Creator=_Creator;
Updater=_Updater;
DateOfCreate=_DateOfCreate;
DateOfUpdate=_DateOfUpdate;
SetAction();
}
bool 	FRowData::SaveToBase(void)
{
String from="",to="",sql="";
if (Action=="Обновить")
	{
	from=inProjectPath+FileName;
	to=base+FilePath+inBaseFileName;
	if(CopyFile(from.c_str(),to.c_str(),false))//false=замена существующего   //замена файла в архиве
		{
		sql="Call constructions.UpdateFile('"+ekran(FilePath)+"','"+ekran(inBaseFileName)+"','"+ekran(String(LUser))+"')";    //нет корректировки базы только корректировка даты обновления файла в базе
		return DB->SendCommand(sql);
		}else
		{
		return false;  // вероятно ошибка связи возвращаем фолс чтоб файл остался в списке
		}
	}else
	{
	inBaseFileName=GetFileName();
	FilePath=GetDirName();
	from=inProjectPath+FileName;
	to=base+FilePath+inBaseFileName;
	MkPjDir(FilePath,base);
	int i=0;                        //добавление файла к архиву
	while (!CopyFile(from.c_str(),to.c_str(),true)&&i<1000) /// обработака случая когда идет свопадение имен и файл не копируется
		{
		inBaseFileName=GetFileName();
		if (FilePath.Length()<20)   FilePath=FilePath+GetDirName(); else FilePath=GetDirName();
		inBaseFileName=String(inBaseFileName.ToIntDef(0)+1);
		to=base+FilePath+inBaseFileName;
		MkPjDir(FilePath,base);
		i++;
		}
	if (i>=1000)
		{
		return false;
		}else
		{  //добавление строки в базу заполнени упд и адд дат
		sql="Call constructions.AddFile('"+String(id)+"','"+ekran(FilePath)+"','"+ekran(inProjectPath)+"','"+ekran(FileName)+"','"+ekran(inBaseFileName)+"','"+String(LUser)+"')";
		return DB->SendCommand(sql);
		}
	}
}
bool 	FRowData::SaveToPC(const String &path)
{
String from="",to="";
from=base+FilePath+inBaseFileName;
to=path+FileName;
if(CopyFile(from.c_str(),to.c_str(),true))//false=замена существующего
	{
	return true;
	}else
	{
	return false;  // вероятно ошибка связи возвращаем фолс чтоб файл остался в списке
	}
}
bool 	FRowData::Delete(void)
{
//удалить файл
String from="",sql="";
from=base+FilePath+inBaseFileName;
if(DeleteFile(from.c_str()))
	{
	sql="Call constructions.DelFile('"+ekran(FilePath)+"','"+ekran(inBaseFileName)+"','"+String(LUser)+"')";
	return DB->SendCommand(sql);  // при ошибке запроса файл останется в базе потому должен остаться и в списке
	}else
	{
	return false;  // вероятно ошибка связи возвращаем фолс чтоб файл остался в списке
	}
}
void 	FRowData::SetAction(void)//public???
{
switch (type)
	{
	case 0: {
			if (Accept)
				{
				if (inbase)
					{
					Action="Обновить";
					}else
					{
					Action="Добавить";
					}
				}else
				{
				Action="Нет";
				}
			break;
			}
	case 1: {
			if (Accept)
				{
				if (inbase)
					{
					Action="Получить";
					}else
					{
					Action="Нет";
					}
				}else
				{
				Action="Нет";
				}
			break;
			}
	case 2: {
			if (Accept)
				{
				if (inbase)
					{
					Action="Удалить";
					}else
					{
					Action="Нет";
					}
				}else
				{
				Action="Нет";
				}
			break;
			}
	default:break;
	}
} 

FRowData & 	FRowData::operator =(const FRowData &r)
{
if (this==&r) {return *this;}
id=r.id;
SpRazd=r.SpRazd;
icoID=r.icoID;
//const int &LUser;
G_Obd=r.G_Obd;
V_Obd=r.V_Obd;
Name=r.Name;
SpRazdName=r.SpRazdName;
FileName=r.FileName;
FilePath=r.FilePath;
Creator=r.Creator;
Updater=r.Updater;
DateOfCreate=r.DateOfCreate;
DateOfUpdate=r.DateOfUpdate;
inBaseFileName=r.inBaseFileName;
inProjectPath=r.inProjectPath;
Action=r.Action;
//const String &base;
inbase=r.inbase;
Accept=r.Accept;
//const char & type;
return *this;
}
bool 		FRowData::operator ==(const FRowData &r)
{
if (this==&r) {return true;}
if 	(
	id==r.id&&
	SpRazd==r.SpRazd&&
	icoID==r.icoID&&
	LUser==r.LUser&&
	G_Obd==r.G_Obd&&
	V_Obd==r.V_Obd&&
	Name==r.Name&&
	SpRazdName==r.SpRazdName&&
	FileName==r.FileName&&
	FilePath==r.FilePath&&
	Creator==r.Creator&&
	Updater==r.Updater&&
	DateOfCreate==r.DateOfCreate&&
	DateOfUpdate==r.DateOfUpdate&&
	inBaseFileName==r.inBaseFileName&&
	inProjectPath==r.inProjectPath&&
	Action==r.Action&&
	base==r.base&&
	inbase==r.inbase&&
	Accept==r.Accept&&
	type==r.type
	)
	{
	return true;
	}else
	{
	return false;
	}
}
bool 		FRowData::operator !=(const FRowData &r)
{
if (this==&r) {return false;}
if 	(
	id==r.id&&
	SpRazd==r.SpRazd&&
	icoID==r.icoID&&
	LUser==r.LUser&&
	G_Obd==r.G_Obd&&
	V_Obd==r.V_Obd&&
	Name==r.Name&&
	SpRazdName==r.SpRazdName&&
	FileName==r.FileName&&
	FilePath==r.FilePath&&
	Creator==r.Creator&&
	Updater==r.Updater&&
	DateOfCreate==r.DateOfCreate&&
	DateOfUpdate==r.DateOfUpdate&&
	inBaseFileName==r.inBaseFileName&&
	inProjectPath==r.inProjectPath&&
	Action==r.Action&&
	base==r.base&&
	inbase==r.inbase&&
	Accept==r.Accept&&
	type==r.type
	)
	{
	return false;
	}else
	{
	return true;
	}
}
