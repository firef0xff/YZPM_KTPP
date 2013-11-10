//---------------------------------------------------------------------------

#ifndef DtInfoH
#define DtInfoH


#include "OperRow.h"

class DtInfo
	{
	public:
	
	DtInfo(cSQL *db,int _id,const int &_User);
	DtInfo(const DtInfo &);
	~DtInfo();
	bool SaveData(void);
    void CheckAccept(void);
	
    int 	Get_id(void)const{return id;};
	int 	Get_ei(void)const{return ei;};
	int 	Get_vz(void)const{return vz;};
	int 	Get_kdz(void)const{return kdz;};
	double 	Get_masd(void)const{return masd;};
	double 	Get_masz(void)const{return masz;};
	double 	Get_nrm(void)const{return nrm;};
	String 	Get_eiName(void)const{return eiName;};
	String 	Get_vzName(void)const{return vzName;};
	String 	Get_obm(void)const{return obm;};
	String 	Get_razz(void)const{return razz;};
	String 	Get_pm(void);
	String 	Get_napr(void)const{return napr;};
	String 	Get_CreateUser(void)const{return CreateUser;};
	String 	Get_ChangeUser(void)const{return ChangeUser;};
	String& Get_LUser(void){return LUser;}
	TDateTime Get_CreateDate(void)const{return CreateDate;};
	TDateTime Get_ChangeDate(void)const{return ChangeDate;};

	OperRow * Get_Operations(void)const{return operations;};
	void 	  Set_Operations(OperRow *r){if (r){operations=r->Get_First();}else{operations=r;}};

	bool 	Need_Save(void);
	bool    Can_Save(String &msg);
	bool 	Get_Access(void)const{return access;}
	
	void Set_ei(int r);
	void Set_vz(int r);
	void Set_kdz(int r){if (kdz!=r){kdz=r;if (action=="no"){action="upd";}}};
	void Set_masd(double r){if (masd!=r){masd=r;if (action=="no"){action="upd";}}};
	void Set_masz(double r){if (masz!=r){masz=r;if (action=="no"){action="upd";}}};
	void Set_nrm(double r){if (nrm!=r){nrm=r;if (action=="no"){action="upd";}}};
	void Set_obm(String r);
	void Set_razz(String r){if (razz!=r){razz=r;if (action=="no"){action="upd";}}};
	void Set_napr(String r){if (napr!=r){napr=r;if (action=="no"){action="upd";}}};

	private:
	
	void LoadData(int _id);

	
	const int *LUserID;
	String LUser;
	bool access;
	
	int id;
	int vz;
	int kdz;
	int ei;
	int obmid;
	double masd;
	double masz;
	double nrm;
	String eiName; 
	String vzName; 
	String obm;
	String razz;
	String pm;
	String napr;
	String CreateUser;
	String ChangeUser;
	TDateTime CreateDate;
	TDateTime ChangeDate;
	
	OperRow * operations;
	
	String action;
	cSQL * const DB;
	
	static int count;
	};
int DtInfo::count=0;
#endif
