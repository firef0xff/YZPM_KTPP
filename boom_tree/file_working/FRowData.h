#ifndef FRowDataH
#define FRowDataH
#include "FileRow.h"
class FRowData:public FileRow
{
public:
	FRowData(cSQL *const _DB,const int &_LUser,const String &File,const int &id,const String &_base,const char &_type);
	FRowData(const FRowData &r);
	~FRowData(void);	
	void init(void);
	void UpdateVal(String obd);
	void UpdateVal(int id);
	bool SaveToBase(void);
	bool SaveToPC(const String &path);
	bool Delete(void);

	
	bool ItTrueClassName	(void)const{return (TrueClassName()=="FRowData")?true:false;};
	String TrueClassName 	(void)const{return "FRowData";};
	String Get_Text         (void)const{return Get_Obd(true)+"-"+Name;}
	String Get_inBaseFileName	(void)const{return inBaseFileName;};
	String Get_inProjectPath	(void)const{return inProjectPath;};
	String Get_Action			(void)const{return Action;};  
	bool Get_inbase				(void)const{return inbase;};
	
	
	void SetData 	(
					const int &_id,		const int &_SpRazd,
					const String &_Obd,	const String &_Name,
					const String &_SpRazdName,
					const int &_icoID,		const String &_FileName,	const String &_FilePath,
					const String &_Creator,	const String &_Updater,	const bool &_Accept,
					const TDateTime &_DateOfCreate,	const TDateTime &_DateOfUpdate,
					String &_inBaseFileName,	String &_inProjectPath
					);
	void SetAction	(const String &act)		{Action=act;}
	
	FRowData & operator =(const FRowData &);
	bool operator ==(const FRowData &);
	bool operator !=(const FRowData &);
	int Count(void)const{return count;};
protected:

private:
	static int count;
	String inBaseFileName;
	String inProjectPath;
	String Action;  
	const String &base;	
	bool inbase;
	const char &type;

	void SetData (TADOQuery *rez);
	void SetAction(void);
};

int FRowData::count=0;
#endif
