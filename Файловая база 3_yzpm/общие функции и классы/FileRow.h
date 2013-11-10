

#ifndef FileRowH
#define FileRowH

#include "Obd.h"

class FileRow:public Obd
	{
	public:
	
	FileRow(cSQL *db,const int &User);
	FileRow(const FileRow &);
	~FileRow(void);
	bool UpdateVal (void);
	
	bool ItTrueClassName (void)const{return TrueClassName()=="FileRow"?true:false;}
	String TrueClassName (void)const{return "FileRow";};
	virtual bool CanUse	(void)		const{return (id>0&&Get_Obd(false)!=""&&FilePath!="")?true:false;};

	int	Get_icoID		(void)const{return icoID;};
	String 	Get_Text 	(void)const{return FileName+" - "+DateOfUpdate.DateString();};
	String	Get_FileName(void)const{return FileName;};
	String	Get_FilePath(void)const{return FilePath;};
	String	Get_Creator	(void)const{return Creator;};
	String	Get_Updater	(void)const{return Updater;};
	bool Get_Accept		(void)const{return Accept;};
	TDateTime Get_DateOfCreate	(void)const{return DateOfCreate;};
	TDateTime Get_DateOfUpdate	(void)const{return DateOfUpdate;};

	
	bool SetData 	(//базовые
						const int &_id,		const int &_SpRazd,
						const String &_Obd,	const String &_Name,
						const String &_SpRazdName,
						// свои
						const int &_icoID,		const String &_FileName,	const String &_FilePath,
						const String &_Creator,	const String &_Updater,	const bool &_Accept,
						const TDateTime &_DateOfCreate,	const TDateTime &_DateOfUpdate);
	
	FileRow & operator =	(const FileRow &r);
	
	bool   operator ==(const FileRow &r)const;
	bool   operator !=(const FileRow &r)const;

	int Count(void)const{return count;};

	protected:
	
	int icoID;
	const int &LUser;
	String FileName;
	String FilePath;
	String Creator;
	String Updater;
	bool Accept;
	TDateTime DateOfCreate;
	TDateTime DateOfUpdate;
	
	void init(void);
	void SetObd    	(const String &r);
	void SetId   	(const int &ID){id=ID;};	
	private:
	
	static int  count;
	};
int 	FileRow::count=0;
#endif





