#ifndef NrmRowH
#define NrmRowH
#include "SQL.h"
#include "functions.h"
class NrmRow
	{
	typedef NrmRow * lnk ;
	typedef const NrmRow * c_lnk;
	public:
	NrmRow(cSQL *db,const String &_LUser,const unsigned __int64  &_OpID,const String &_action,
			const int &_kolod,	 const String  &__prof,
			const String  &_krop,const String  &__rr,
			const String  &_en,  const String  &_kts,
			const String  &_kvn, const String  &_ttp,
			const double  &_ksht,const double  &_tpz,
			const double  &_tsht,
			const String  &_CreateUser,
			const String  &_UpdateUser,
			const TDateTime  &_CreateDate,
			const TDateTime  &_UpdateDate,
			lnk _prev);
	NrmRow(const NrmRow &);
	~NrmRow();

	int  Count (void);

	bool SaveData(lnk &r);
	void ChangeOpID	(unsigned __int64  _OpID,lnk &r,bool no_del=false);
	
	NrmRow * 	Get_Prev	(void) {return prev;};
	NrmRow * 	Get_Next	(void) {return next;};
	NrmRow * 	Get_First	(void);
	NrmRow * 	Get_Last	(void);
	NrmRow *	Insert_line	(int pos,lnk line_item);
	NrmRow *  	Copy_subline(int pos,int _count);
	void		Del_subline (lnk &r,int pos,int _count);
	void		Move_items	(int pos,int _count,int new_pos);

	NrmRow * operator [](const unsigned int &);

	bool 		isUsed		(void)const{return  (action!="del")?true:false;};
	
   	int 		Get_Kolod	(void)const{return kolod;};

	String  	Get_Prof	(void)const{return _prof;};
	String  	Get_Krop	(void)const{return krop;};
	String  	Get_Rr		(void)const{return _rr;};
	String  	Get_En		(void)const{return en;};
	String  	Get_Kts		(void)const{return kts;};
	String  	Get_Kvn		(void)const{return kvn;};
	String  	Get_Ttp		(void)const{return ttp;};

	double  	Get_Ksht	(void)const{return ksht;};
	double  	Get_Tpz		(void)const{return tpz;};
	double  	Get_Tsht	(void)const{return tsht;};

	String  	Get_CreateUser	(void)const{return CreateUser;};
	String  	Get_UpdateUser	(void)const{return UpdateUser;};
	TDateTime  	Get_CreateDate	(void)const{return CreateDate;};
	TDateTime 	Get_UpdateDate	(void)const{return UpdateDate;};  

    String		Get_action(void)const{return action;}//для теста

	void  		Set_Prev(lnk r){prev=r;};
	void  		Set_Next(lnk r){next=r;};
	bool 		SetValues 	(const int &_kolod,	 const String  &__prof,
							const String  &_krop,const String  &__rr,
							const String  &_en,  const String  &_kts,
							const String  &_kvn, const String  &_ttp,
							const double  &_ksht,const double  &_tpz,
							const double  &_tsht);

	bool 		Need_Save(void);
   	private:
	void Push_Back_Deleted (void);
	void Upd_Ofset	(void);
	
	unsigned __int64  OpID;
	const String *LUser;

	int kolod;

	String  _prof;
	String  krop;
	String  _rr;
	String  en;
	String  kts;
	String  kvn;
	String  ttp;

	double  ksht;
	double  tpz;
	double  tsht;

	String  CreateUser;
	String  UpdateUser;
	TDateTime  CreateDate;
	TDateTime  UpdateDate;

	String action;
	cSQL *const DB;

	lnk  prev;
	lnk  next;

	unsigned int ofset;

	static int count;
	};
int  NrmRow::count=0;
#endif
