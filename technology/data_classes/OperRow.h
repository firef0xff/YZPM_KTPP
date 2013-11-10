#ifndef OperRowH
#define OperRowH

#include "NrmRow.h"
#include "PerexRow.h"
#include "InstrumRow.h"
class OperRow
	{
	typedef OperRow * lnk ;
	typedef const OperRow * c_lnk;
	public:
	OperRow(cSQL *db,const String &_LUser,const unsigned __int64 &_OpID,const String &_action,
			const int &_id,	const int &_idtar,
			const int &_id_cntrl,
			const String &_ceh,		const String &_uch,
			const String &_opr,		const String &_oboID,
			const String &_OboName,
			const String &_OprName,	const String &_OprKod,
			const String &_Strop,	const String &_tara,
			const String &_control,	const String &_Instruct,
			const String  &_CreateUser,
			const String  &_UpdateUser,
			const TDateTime  &_CreateDate,
			const TDateTime  &_UpdateDate,
			lnk _prev);
	OperRow(const OperRow &);
	~OperRow();

	int  Count (void);

	bool SaveData	(lnk &r);
	void UpdID	(int _id,lnk &r,bool no_del=false);


	OperRow * 	Get_Prev	(void) {return prev;};
	OperRow * 	Get_Next	(void) {return next;};
	OperRow * 	Get_First	(void);
	OperRow * 	Get_Last	(void);
	OperRow *	Insert_line	(int pos,lnk line_item);
	OperRow *   Copy_subline(int pos,int _count);
	void		Del_subline (lnk &r,int pos,int _count);
	void		Move_items	(int pos,int _count,int new_pos);

	OperRow * operator [](const unsigned int &);

	bool 		isUsed		(void)const{return  (action!="del")?true:false;};
	
	int 		Get_idtar	(void)const{return idtar;};	//ktar
	int 		Get_id_cntrl(void)const{return id_cntrl;};//ok69
unsigned __int64 Get_OpID	(void)const{return OpID;};
	String 		Get_ceh		(void)const{return ceh;};
	String 		Get_uch		(void)const{return uch;};
	String 		Get_opr		(void)const{return opr;};
	String 		Get_oboID	(void)const{return oboID;};
	
	String 		Get_OboName	(void)const{return OboName;};//наименование оборудования
	String 		Get_OprName	(void)const{return OprName;};//наименование и код операции
	String 		Get_OprKod	(void)const{return OprKod;};//код операции
	
	String 		Get_Strop	(void)const{return Strop;}; //stro
	String 		Get_Tara	(void)const{return tara;}
	String 		Get_Control	(void)const{return control;}
	String 		Get_Instruct(void)const{return Instruct;}; //ioht

	String  	Get_CreateUser	(void)const{return CreateUser;};
	String  	Get_UpdateUser	(void)const{return UpdateUser;};
	TDateTime  	Get_CreateDate	(void)const{return CreateDate;};
	TDateTime 	Get_UpdateDate	(void)const{return UpdateDate;};

	NrmRow* 	Get_nrm(void)const{return nrm;};
	PerexRow* 	Get_perex(void)const{return perex;};
	InstrumRow* Get_instrum(void)const{return instrum;};

	String		Get_action(void)const{return action;}//для теста

	void 		Set_nrm(NrmRow* r) 			{if (r){nrm=r->Get_First();}else{nrm=r;}};
	void 		Set_perex(PerexRow* r) 		{if (r){perex=r->Get_First();}else{perex=r;}};
	void 		Set_instrum(InstrumRow* r) 	{if (r){instrum=r->Get_First();}else{instrum=r;}};

	void  		Set_Prev(lnk r){prev=r;};
	void  		Set_Next(lnk r){next=r;};
	bool  		SetValues  (const int &_idtar,
							const int &_id_cntrl,
							const String &_ceh,		const String &_uch,
							const String &_opr,		const String &_oboID,
							const String &_OboName,
							const String &_OprName,	const String &_OprKod,
							const String &_Strop,	const String &_tara,
							const String &_control,	const String &_Instruct);
	bool 		Need_Save(void);
	bool    	Can_Save(String &msg);
private:
	OperRow(cSQL *db,const String &_LUser,const unsigned __int64 &_OpID,
			const int &_id,	const int &_idtar,const String &_action,
			const int &_id_cntrl,
			const String &_ceh,		const String &_uch,
			const String &_opr,		const String &_oboID,
			const String &_OboName,
			const String &_OprName,	const String &_OprKod,			
			const String &_Strop,	const String &_tara,
			const String &_control,	const String &_Instruct,
			const String  &_CreateUser,
			const String  &_UpdateUser,
			const TDateTime  &_CreateDate,
			const TDateTime  &_UpdateDate,
			lnk _prev,
			const NrmRow  		 *_nrm,
			const PerexRow 		 *_perex,
			const InstrumRow 	 *_instrum
			);//конструктор репликатор !! внимание отличается расположением дополнительными параметрами, не загружает цепочки данных, а копирует из исходного
	void Push_Back_Deleted (void);
	void Load_Oper_Data (void);
	void Upd_Ofset	(void);
	void Refresh_opr (void);
	
	const String *LUser;

	int id;
	unsigned __int64 OpID;
	int idtar;	//ktar	
	int id_cntrl;//ok69

	
	String ceh;//цех
	String uch;//участок
	String opr;//операция
	String oboID;//код оборудования
	String OboName;//наименование оборудования		
	String OprName;//наименование и код операции
	String OprKod;//код операции	
	
	String Strop; //stro
	String tara;   //тара
	String control; //контроль
	String Instruct; //ioht

	String  CreateUser;
	String  UpdateUser;
	TDateTime  CreateDate;
	TDateTime  UpdateDate;

	String action;
	cSQL *const DB;

	NrmRow 		* nrm;
	PerexRow 	* perex;
	InstrumRow 	* instrum;
	
	lnk  prev;
	lnk  next;

	unsigned int ofset;

	static int count;
	};
int  OperRow::count=0;
#endif  
  