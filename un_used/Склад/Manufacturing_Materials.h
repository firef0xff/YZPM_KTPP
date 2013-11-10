//---------------------------------------------------------------------------

#ifndef Manufacturing_MaterialsH
#define Manufacturing_MaterialsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>

#include "Obd.h"
#include "IconsData.h"
#include <ADODB.hpp>
#include <DB.hpp>
#include <ActnPopup.hpp>
#include <Menus.hpp>
#include <PlatformDefaultStyleActnCtrls.hpp>

#define nullptr 0

//---------------------------------------------------------------------------
class TMaterials_Need : public TForm
{
__published:	// IDE-managed Components
	TSplitter *Splitter2;
	TPanel *Panel18;
	TSplitter *Splitter3;
	TPageControl *materials_lists;
	TTabSheet *TabSheet4;
	TStringGrid *Std_izd;
	TTabSheet *TabSheet5;
	TTabSheet *TabSheet6;
	TPanel *Panel15;
	TTreeView *Tree;
	TPanel *Panel17;
	TLabel *Label3;
	TSpeedButton *SpeedButton1;
	TEdit *E1;
	TButton *StartSearch;
	TRadioGroup *SearchParams;
	TPanel *Panel14;
	TGroupBox *GroupBox3;
	TSpeedButton *next;
	TSpeedButton *prev;
	TLabeledEdit *E2;
	TLabeledEdit *E3;
	TPanel *Panel19;
	TPageControl *PageControl2;
	TTabSheet *TabSheet7;
	TStringGrid *Mater_detail;
	TTabSheet *TabSheet8;
	TStringGrid *potr_materials;
	TTabSheet *TabSheet9;
	TStringGrid *Change_materials;
	TTabSheet *TabSheet1;
	TStringGrid *Dets;
	TStringGrid *Materials;
	TStringGrid *Vspom_mat;
	TADOConnection *ADC;
	TPopupActionBar *PAB1;
	TMenuItem *N8;
	TMenuItem *N9;
	TMenuItem *N10;
	TMenuItem *N18;
	void __fastcall PanelEnter(TObject *Sender);
	void __fastcall PanelExit(TObject *Sender);
	void __fastcall PanelMouseEnter(TObject *Sender);
	void __fastcall CngListClick(TObject *Sender);
	void __fastcall E2Change(TObject *Sender);
	void __fastcall E3Change(TObject *Sender);
	void __fastcall TreeDeletion(TObject *Sender, TTreeNode *Node);
	void __fastcall StartSearchClick(TObject *Sender);
	void __fastcall TreeExpanding(TObject *Sender, TTreeNode *Node, bool &AllowExpansion);
	void __fastcall N9Click(TObject *Sender);
	void __fastcall N10Click(TObject *Sender);
	void __fastcall N18Click(TObject *Sender);
	void __fastcall E1KeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall TreeMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall materials_listsChange(TObject *Sender);
	void __fastcall ContentGridsDrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect,
          TGridDrawState State);

private:	// User declarations
	//встроенные классы данных
	enum Tree_data_types{det=0,zakaz=1,part=2};
	enum Grid_data_types{made=0,standart=1,materials=2,support_materials=3};
	class Tree_data:public Obd
	{ //тип данных прикрепляемый к узлу дерева
	public:
		//конструкторы
		Tree_data(cSQL *const db,Tree_data_types _Type,String _val):Obd(db)
		{
			Type=_Type;
			idp=0;
			eid=0;
			eidp=0;
			sp_kol=0;
			abs_kol=0;
			all_kol=0;

			V_Obu="";
			G_Obu="";
			Ei="шт.";
			create_date=0;
			val=_val;
		}
		Tree_data(cSQL *const db,unsigned __int64 &_eid):Obd(db)
		{
			// извлеч данные по eid
			Type=0;
			val="";
			eid=_eid;
			create_date=0;
			Update();
		}
		Tree_data(cSQL *const db,int &_id,int &_idp,int &_SpRazd,
					unsigned __int64 &_eid,unsigned __int64 &_eidp,
					double &_sp_kol,double &_abs_kol,double &_all_kol,
					const String &_Name,const String &_V_Obd,const String &_V_Obu,
					const String &_SpRazdName, const String &_Ei, const String &_val,
					const Tree_data_types &_Type, const TDateTime _date
				 ):Obd(db)
		{
			Type=_Type;
			val=_val;
			Name=_Name;
			id=_id;
			V_Obd=_V_Obd;
			G_Obd=VinToGost(V_Obd);
			SpRazd=_SpRazd;
			SpRazdName=_SpRazdName;

			idp=_idp;
			eid=_eid;
			eidp=_eidp;
			sp_kol=_sp_kol;
			abs_kol=_abs_kol;
			all_kol=_all_kol;

			V_Obu=_V_Obu;
			G_Obu=VinToGost(V_Obu);

			Ei=_Ei;

			create_date=_date;
		}
		Tree_data(const Tree_data &r):Obd(r)
		{
			Type=r.Type;
			idp=r.idp;
			eid=r.eid;
			eidp=r.eidp;
			sp_kol=r.sp_kol;
			abs_kol=r.abs_kol;
			all_kol=r.all_kol;
			V_Obu=r.V_Obu;
			G_Obu=r.G_Obu;
			Ei=r.Ei;
			val=r.val;
			create_date=r.create_date;
		}
		~Tree_data()
		{}
		//операторы
		Tree_data &operator=	(const Tree_data &r)
		{
			if (this!=&r)
			{
				*((Obd*)this)=(Obd)r;
				Type=r.Type;
				idp=r.idp;
				eid=r.eid;
				eidp=r.eidp;
				sp_kol=r.sp_kol;
				abs_kol=r.abs_kol;
				all_kol=r.all_kol;
				V_Obu=r.V_Obu;
				G_Obu=r.G_Obu;
				Ei=r.Ei;
				val=r.val;
				create_date=r.create_date;
			}
			return *this;
		}
		bool       operator==	(const Tree_data &r)	const
		{
			if 	((*((Obd*)this)==(Obd)r)&&
				Type==r.Type&&
				idp==r.idp&&
				eid==r.eid&&
				eidp==r.eidp&&
				sp_kol==r.sp_kol&&
				abs_kol==r.abs_kol&&
				all_kol==r.all_kol&&
				V_Obu==r.V_Obu&&
				G_Obu==r.G_Obu&&
				Ei==r.Ei&&
				val==r.val&&
				create_date==r.create_date
				)
			{
				return true;
			}else
			{
				return false;
			}
		}
		bool       operator!=	(const Tree_data &r)	const
		{
        	return !(*this==r);
		}
		//функции

		double	Get_sp_kol 	(void)	const
		{
			return  sp_kol;
		}
		double 	Get_abs_kol (void)	const
		{
			return  abs_kol;
		}
		double 	Get_all_kol (void)	const
		{
			return  all_kol;
		}
		void 	Set_abs_kol	(double _abs_kol)
		{
			abs_kol=_abs_kol;
		}
		void 	Set_all_kol	(double _all_kol)
		{
			all_kol=_all_kol;
		}
		String	Get_Obu		(bool gost)	const
		{
			return gost?G_Obu:V_Obu;
		}

		unsigned __int64 	Get_eid(void)	const
		{
			return eid;
		}
		Tree_data_types     Get_Type(void)	const
		{
			return Type;
		}

		String 	Get_val (void)
		{
        	return val;
		}
		String 	Get_EI	(void)
		{
			return Ei;
		}

		String	Get_Text	(void)
		{
			switch (Type)
			{
			case 1:{return val+" - заказ";}
			case 2:{return val+" - партия от "+create_date.FormatString("dd.mm.yyyy");}
			default:return Obd::Get_Text();
			}
		}
		//сервис
		bool ItTrueClassName (void)const
		{
			return TrueClassName()=="Tree_data"?true:false;
		}
		virtual String TrueClassName (void)const
		{
			return "Tree_data";
		}

		void	Update	(void)
		{
			if (Type){return;}
			TADOQuery *rez=DB->SendSQL("call manufacture.Get_node('"+String(eid)+"')");
			if (rez&&rez->RecordCount)
			{
				id=rez->FieldByName("idc")->Value.operator int();
				idp=rez->FieldByName("idp")->Value.operator int();
				SpRazd=rez->FieldByName("razdSPID")->Value.operator int();

				eid=rez->FieldByName("eidc")->Value.operator __int64();
				eidp=rez->FieldByName("eidp")->Value.operator __int64();

				sp_kol=rez->FieldByName("sp_kol")->Value.operator double();
				abs_kol=rez->FieldByName("abs_kol")->Value.operator double();
				all_kol=rez->FieldByName("all_kol")->Value.operator double();

				SpRazdName=rez->FieldByName("SpRazdName")->Value;
				Name=rez->FieldByName("Name")->Value;
				V_Obd=GostToVin(rez->FieldByName("obd")->Value);
				G_Obd=VinToGost(V_Obd);
				V_Obu=GostToVin(rez->FieldByName("obu")->Value);
				G_Obu=VinToGost(V_Obu);

				Ei=rez->FieldByName("Ei")->Value;
				create_date=rez->FieldByName("create_date")->Value.operator TDateTime();
			}else
			{
				idp=0;
				eid=0;
				eidp=0;
				sp_kol=0;
				abs_kol=0;
				V_Obu="";
				G_Obu="";
				Ei="шт.";
				create_date=0;
			}
			delete rez;
		}
	private:
		//мне нужны от класса следующие данные  (закоментированные переменные наследуются от базового класса)
			//рабочая информация
		//int    id;  			//идентификатор узла
		int    idp;   			//идентификатор предка
		Tree_data_types  Type;	//тип элемента дерева
		unsigned __int64 eid,	//уникальный идентификатор узла развертки
						 eidp;  //уникальный идентификатор предка развертки
		double 	sp_kol,			//количество у узла развертки установленное по спецификации
				abs_kol,		//количество у узла развертки пересчитанное на количество всего
				all_kol;        //общее количество узлов в загруженной спецификации

			//вспомогательная информация для отображения
		//int    SpRazd;        //идентификатор раздела спецификации
		//String G_Obd;         //Обозначение узла ГОСТ
		//String V_Obd;         //Обозначение узла СТП
		String G_Obu;           //Обозначение предка узла ГОСТ
		String V_Obu;           //Обозначение предка узла СТП
		String Ei;				//единици измерения

		String val;				//значение для запросов
        TDateTime create_date;  //дата запуска
		//String Name;          //Наименование узла
		//String SpRazdName;    //Название раздела спецификации узла

	};
	class Grid_data
	{
	public:
		Grid_data(void)
		{
			V_Obd="";
			G_Obd="";
			Name="";
			EI="";
			Need_kol=0.0;
			Sklad_kol=0.0;
			Lacking_kol=0.0;
			id=-1;
			Type=-1;
		}
		Grid_data(	String	_Obd,	String	_Name,	String	_EI,
					double	_Need_kol,	double	_Sklad_kol, double	_Lacking_kol,
					unsigned int	_id,	Grid_data_types	_Type)
		{
			V_Obd=GostToVin(_Obd);
			G_Obd=VinToGost(V_Obd);
			Name=_Name;
			EI=_EI;
			Need_kol=_Need_kol;
			Sklad_kol=_Sklad_kol;
			Lacking_kol=_Lacking_kol;
			id=_id;
			Type=_Type;
		}
		Grid_data(const Grid_data &r)
		{
			V_Obd=r.V_Obd;
			G_Obd=r.G_Obd;
			Name=r.Name;
			EI=r.EI;
			Need_kol=r.Need_kol;
			Sklad_kol=r.Sklad_kol;
			Lacking_kol=r.Lacking_kol;
			id=r.id;
			Type=r.Type;
		}
		~Grid_data(void)
		{}

		//операторы
		Grid_data& operator =(const Grid_data &r)
		{
			if (this!=&r)
			{
				V_Obd=r.V_Obd;
				G_Obd=r.G_Obd;
				Name=r.Name;
				EI=r.EI;
				Need_kol=r.Need_kol;
				Sklad_kol=r.Sklad_kol;
				Lacking_kol=r.Lacking_kol;
				id=r.id;
				Type=r.Type;
			}
			return *this;
		}
		bool operator ==(const Grid_data &r)
		{
			if (this!=&r)
			{
				if 	(
					V_Obd==r.V_Obd&&
					G_Obd==r.G_Obd&&
					Name==r.Name&&
					EI==r.EI&&
					Need_kol==r.Need_kol&&
					Sklad_kol==r.Sklad_kol&&
					Lacking_kol==r.Lacking_kol&&
					id==r.id&&
					Type==r.Type
					)
				{
				return true;
				}else
				{
				return false;
				}
			}else
			{
				return true;
			}
		}
		bool operator !=(const Grid_data &r)
		{
        	return !(*this==r);
		}

		//доступ
		String 	Get_Obd		(bool Gost=true)
		{
			return Gost?G_Obd:V_Obd;
		}
		String	Get_Name	(void)
		{
			return Name;
		}
		String	Get_EI		(void)
		{
        	return EI;
		}

		double	Get_need_kol 	(void)
		{
			return Need_kol;
		}
		double	Get_sklad_kol   (void)
		{
			return Sklad_kol;
		}
		double	Get_lacking_kol (void)
		{
			return Lacking_kol;
		}

		unsigned int Get_id   (void)
		{
			return id;
		}

		Grid_data_types Get_Type  (void)
		{
			return  Type;
		}

	private:
		String 	V_Obd,   //обозначение
				G_Obd,
				Name,    //наименование
				EI;      //идиницы измерения
		double	Need_kol,    //необходимое количество
				Sklad_kol,   //количество на складе (не заразервированого материала)
                Lacking_kol; //недостающее количество
		unsigned int id;     //id детали
		Grid_data_types Type; //тип списка для которого эта строка
	};
	typedef vector <Grid_data> Grid_rows;
	//приватные переменные
	cSQL *DB;
	const int &LUser;
	IconsData *IcoData;
	Grid_rows 	made_rows,
				standart_rows,
				material_rows,
				support_material_rows;
	//функции
	void 	init			(void),//инициализация компонентов формы
			Find			(void),//поиск заказов (дерево)
			Set_Tree_Ico	(TTreeNode *node),			//назначение иконок для дерева
			Read_Data		(TTreeNode *node),			//считывает данные по выбранному узлу /*перечень входящих, количество, материалы*/
			ShowGridTab     (TTabSheet *tab),			//обновить содержимое вкладки
			expand_pannel_h	(TPanel *Panel,bool exp);	//сворачивание / складывание панели
public:		// User declarations
	__fastcall TMaterials_Need(TComponent* Owner);
	__fastcall TMaterials_Need(TComponent* Owner, TWinControl *_p, String _name,
							const int &_LUser,cSQL *db,IconsData *_IcoData);
	/*__fastcall TMaterials_Need(TComponent* Owner, TWinControl *_p, String _name,
							const int &_LUser,cSQL *db,IconsData *_IcoData,int **_select,
							void *_OpenTree,void* _AddTexTab,void* _LoadTexToCurrTab,
							void* _AddTexViewTab,void* _LoadexViewToCurrTab);*/
	__fastcall ~TMaterials_Need(void);
};

#endif
