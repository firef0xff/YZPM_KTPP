


#pragma hdrstop

#include "FileRow.h"
#pragma package(smart_init)



		FileRow::FileRow(cSQL *db,const int &User):Obd(db),LUser(User)
{
count++;
init();
}
		FileRow::FileRow(const FileRow &r):Obd(r),LUser(r.LUser)
{
count++;
icoID=r.icoID;
FileName=r.FileName;
FilePath=r.FilePath;
Creator=r.Creator;
Updater=r.Updater;
Accept=r.Accept;
DateOfCreate=r.DateOfCreate;
DateOfUpdate=r.DateOfUpdate;
}
		FileRow::~FileRow(void)
{
count--;
}
void 	FileRow::init(void)
{
	//переменные
icoID=-1;
FileName="";
FilePath="";
Creator="";
Updater="";
Accept=false;
DateOfCreate=0;
DateOfUpdate=0;
}
bool 	FileRow::UpdateVal (void)
{
String sql="call constructions.UpdateFileInfo('"+String(id)+"','"+FileName+"','"+String(LUser)+"')";
TADOQuery *rez=DB->SendSQL(sql);
if (rez&&rez->RecordCount)
	{
		//базовые
	SetId(rez->FieldByName("id")->Value);
	SpRazd=rez->FieldByName("razdSPID")->Value;
	SetObd(rez->FieldByName("obd")->Value);
	Name=rez->FieldByName("namd")->Value;
	SpRazdName=rez->FieldByName("Razdname")->Value;
	// свои
	icoID=rez->FieldByName("icoID")->Value;
	FileName=rez->FieldByName("FileName")->Value;
	FilePath=rez->FieldByName("FilePath")->Value;
	Creator=rez->FieldByName("Creator")->Value;
	Updater=rez->FieldByName("Updater")->Value;
	Accept=rez->FieldByName("Accept")->Value;
	if (!rez->FieldByName("DateOfCreate")->Value.IsNull()){DateOfCreate=rez->FieldByName("DateOfCreate")->Value.operator TDateTime();}
	if (!rez->FieldByName("DateOfUpdate")->Value.IsNull()){DateOfUpdate=rez->FieldByName("DateOfUpdate")->Value.operator TDateTime();}
	delete rez;
	}else
	{
	init();
	Obd::init();
	delete rez;
	}
return CanUse();
}
bool 	FileRow::SetData	(//базовые
						const int &_id,		const int &_SpRazd,
						const String &_Obd,	const String &_Name,
						const String &_SpRazdName,
						// свои
						const int &_icoID,		const String &_FileName,	const String &_FilePath,
						const String &_Creator,	const String &_Updater,	const bool &_Accept,
						const TDateTime &_DateOfCreate,	const TDateTime &_DateOfUpdate
						)
{
if (ItTrueClassName())
	{
	SetId(_id);
	SetObd(_Obd);
	SpRazd=_SpRazd;
	Name=_Name.Trim();
	SpRazdName=_SpRazdName.Trim();
	icoID=_icoID;
	FileName=_FileName.Trim();
	FilePath=_FilePath.Trim();
	Creator=_Creator.Trim();
	Updater=_Updater.Trim();
	Accept=_Accept;
	DateOfCreate=_DateOfCreate;
	DateOfUpdate=_DateOfUpdate;
	}
return CanUse();
}
FileRow & 	FileRow::operator =(const FileRow &r)
{
if (this==&r) {return *this;}
//базовые
id=r.id;
SpRazd=r.SpRazd;
G_Obd=r.G_Obd;
V_Obd=r.V_Obd;
Name=r.Name;
SpRazdName=r.SpRazdName;
// свои
icoID=r.icoID;
FileName=r.FileName;
FilePath=r.FilePath;
Creator=r.Creator;
Updater=r.Updater;
Accept=r.Accept;
DateOfCreate=r.DateOfCreate;
DateOfUpdate=r.DateOfUpdate;
return *this;
}
bool 	FileRow::operator ==(const FileRow &r)const
{
if (this==&r) {return true;}
if (
	//базовые
	id!=r.id&&
	SpRazd!=r.SpRazd&&
	G_Obd!=r.G_Obd&&
	V_Obd!=r.V_Obd&&
	Name!=r.Name&&
	SpRazdName!=r.SpRazdName&&
	// свои
	icoID!=r.icoID&&
	FileName!=r.FileName&&
	FilePath!=r.FilePath&&
	Creator!=r.Creator&&
	Updater!=r.Updater&&
	Accept!=r.Accept&&
	DateOfCreate!=r.DateOfCreate&&
	DateOfUpdate!=r.DateOfUpdate
	){return false;}else{return true;}
}
bool 	FileRow::operator !=(const FileRow &r)const
{
if (this==&r) {return false;}
if (
	//базовые
	id!=r.id&&
	SpRazd!=r.SpRazd&&
	G_Obd!=r.G_Obd&&
	V_Obd!=r.V_Obd&&
	Name!=r.Name&&
	SpRazdName!=r.SpRazdName&&
	// свои
	icoID!=r.icoID&&
	FileName!=r.FileName&&
	FilePath!=r.FilePath&&
	Creator!=r.Creator&&
	Updater!=r.Updater&&
	Accept!=r.Accept&&
	DateOfCreate!=r.DateOfCreate&&
	DateOfUpdate!=r.DateOfUpdate
	){return true;}else{return false;}
}
void 	FileRow::SetObd    	(const String &r)
{
V_Obd=GostToVin(r);
G_Obd=VinToGost(r);
}


