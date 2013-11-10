//---------------------------------------------------------------------------

#ifndef Izd_UnrollH
#define Izd_UnrollH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>

#include "Vector.h"
#include "IconsData.h"
#include "select_params.h"
#include "Obd.h"
#include <ImgList.hpp>
#include <ActnPopup.hpp>
#include <Menus.hpp>
#include <PlatformDefaultStyleActnCtrls.hpp>

#define nullptr 0
//---------------------------------------------------------------------------
class TList_Editor : public TForm
{
__published:    // IDE-managed Components
    TPanel *Panel1;
    TPanel *Panel2;
    TSplitter *Splitter1;
    TPanel *Panel3;
    TPanel *Panel4;
    TTreeView *Tree;
    TStringGrid *Grid;
    TPanel *Panel6;
    TPanel *Panel7;
    TPanel *Panel8;
    TGroupBox *GroupBox2;
    TSpeedButton *next;
    TSpeedButton *prev;
    TLabeledEdit *E2;
    TLabeledEdit *E3;
    TSpeedButton *Add;
    TSpeedButton *SpeedButton2;
    TSpeedButton *Find_params;
    TImageList *States;
    TPopupActionBar *PAB1;
    TPopupActionBar *PAB2;
    TMenuItem *N1;
    TMenuItem *N2;
    TMenuItem *N3;
    TMenuItem *N4;
    TMenuItem *N5;
    TMenuItem *N6;
    TMenuItem *N7;
    TMenuItem *N8;
    TMenuItem *N9;
    TMenuItem *N10;
    TMenuItem *N11;
    TMenuItem *N12;
    TMenuItem *N13;
    TMenuItem *N14;
    TPanel *Panel9;
    TMenuItem *N18;
    TLabeledEdit *SP_Kol;
    TLabeledEdit *ABS_Kol;
    TGroupBox *Kol;
    TLabeledEdit *ALL_Kol;
    TBitBtn *Change_kol;
    TBitBtn *Reset_kol;
    TMenuItem *N15;
    TPageControl *PC;
    TTabSheet *TS1;
    TTabSheet *TS2;
    TMemo *Errs_list;
    TTreeView *Errs;
    TSplitter *Splitter2;
    TPopupActionBar *PAB3;
    TMenuItem *MenuItem1;
    TMenuItem *MenuItem2;
    TMenuItem *N31;
    TMenuItem *N24;
    TMenuItem *N25;
    TMenuItem *MenuItem3;
    TMenuItem *N16;
    TMenuItem *N17;
    TMenuItem *Excel;
    void __fastcall Find_paramsClick(TObject *Sender);
    void __fastcall ChgListClick(TObject *Sender);
    void __fastcall E2Change(TObject *Sender);
    void __fastcall E3Change(TObject *Sender);
    void __fastcall GridFixedCellClick(TObject *Sender, int ACol, int ARow);
    void __fastcall GridDrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect, TGridDrawState State);
    void __fastcall TreeDeletion(TObject *Sender, TTreeNode *Node);
    void __fastcall TreeExpanding(TObject *Sender, TTreeNode *Node, bool &AllowExpansion);
    void __fastcall GridSelectCell(TObject *Sender, int ACol, int ARow, bool &CanSelect);
    void __fastcall WorkClick(TObject *Sender);
    void __fastcall AddClick(TObject *Sender);
    void __fastcall DelClick(TObject *Sender);
    void __fastcall Upd_list_Click(TObject *Sender);
    void __fastcall TreeItems_Add_Click(TObject *Sender);
    void __fastcall TreeItems_del_Click(TObject *Sender);
    void __fastcall TreeItems_Activation(TObject *Sender);
    void __fastcall N9Click(TObject *Sender);
    void __fastcall N10Click(TObject *Sender);
    void __fastcall PAB1Popup(TObject *Sender);
    void __fastcall Change_kol_Click(TObject *Sender);
    void __fastcall Update_Tree(TObject *Sender);
    void __fastcall TreeMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
    void __fastcall ABS_KolChange(TObject *Sender);
    void __fastcall Next_Step_Click(TObject *Sender);
    void __fastcall ErrsMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
    void __fastcall ExcelClick(TObject *Sender);
    void __fastcall N16Click(TObject *Sender);
    void __fastcall OutFunctions(TObject *Sender);



private:    // User declarations
    cSQL *DB;
    const int &LUser;

    String     sortparams,        //параметры поиска
            order_by,        //параметры сортировки
            states,            //ограничения по типам
            types;          //ограничения по состояниям

    void      init         (void),            //инициализация
            GetLists     (void),            //получить содержимое списка листов
            UpdateSort    (int ACol),        //обновить параметры сортировки
            ShowList    (void),            //функция отображения списка
            ShowData    (size_t row),    //отображение данных листа
            Set_list_Block (TMenuItem *it,int row,bool free=false),            //функция блокировки и разблокировки списка
            Upd_Branch    (TTreeNode *node),                                    //функция обновления данных в дереве
            Set_img        (TTreeNode *node),                                     //функция назначения иконок ноду
            Show_Kol    (TTreeNode *node);                                  //показывает количество по ноду

    bool    inTree        (int id,bool root=false);    //проверяет наличие узла в дереве по id и уровню
    size_t     CheckErrors    (unsigned __int64 list_no); //проверяет наличие ошибок

    class Tree_data:public Obd
    {
    public:
        //конструкторы
        Tree_data(cSQL *const db):Obd(db)
        {
            idp=0;
            eid=0;
            eidp=0;
            sp_kol=0;
            abs_kol=0;
            all_kol=0;
            active=false;
            V_Obu="";
            G_Obu="";
            Ei="шт.";
        }
        Tree_data(cSQL *const db,unsigned __int64 &_eid):Obd(db)
        {
            // извлеч данные по eid
            eid=_eid;
            Update();
        }
        Tree_data(cSQL *const db,int &_id,int &_idp,int &_SpRazd,
                    unsigned __int64 &_eid,unsigned __int64 &_eidp,
                    double &_sp_kol,double &_abs_kol,double &_all_kol,
                    bool &_active,
                    const String &_Name,const String &_V_Obd,const String &_V_Obu,const String &_SpRazdName, const String &_Ei
                 ):Obd(db)
        {

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
            active=_active;

            V_Obu=_V_Obu;
            G_Obu=VinToGost(V_Obu);

            Ei=_Ei;
        }
        Tree_data(const Tree_data &r):Obd(r)
        {
            idp=r.idp;
            eid=r.eid;
            eidp=r.eidp;
            sp_kol=r.sp_kol;
            abs_kol=r.abs_kol;
            all_kol=r.all_kol;
            active=r.active;
            V_Obu=r.V_Obu;
            G_Obu=r.G_Obu;
            Ei=r.Ei;
        }
        ~Tree_data()
        {}
        //операторы
        Tree_data &operator=    (const Tree_data &r)
        {
            if (this!=&r)
            {
                *((Obd*)this)=(Obd)r;
                idp=r.idp;
                eid=r.eid;
                eidp=r.eidp;
                sp_kol=r.sp_kol;
                abs_kol=r.abs_kol;
                all_kol=r.all_kol;
                active=r.active;
                V_Obu=r.V_Obu;
                G_Obu=r.G_Obu;
                Ei=r.Ei;
            }
            return *this;
        }
        bool       operator==    (const Tree_data &r)    const
        {
            if     ((*((Obd*)this)==(Obd)r)&&
                idp==r.idp&&
                eid==r.eid&&
                eidp==r.eidp&&
                sp_kol==r.sp_kol&&
                abs_kol==r.abs_kol&&
                all_kol==r.all_kol&&
                active==r.active&&
                V_Obu==r.V_Obu&&
                G_Obu==r.G_Obu&&
                Ei==r.Ei
                )
            {
                return true;
            }else
            {
                return false;
            }
        }
        bool       operator!=    (const Tree_data &r)    const
        {
            return !(*this==r);
        }

        //функции
        void    Set_active (bool _active,bool mass,unsigned __int64 list_no, unsigned int user)
        {
            DB->SendCommand("call processed_list.Set_Active('"+String(eid)+"','"+String((int)_active)+"','"+String((int)mass)+"','"+String(list_no)+"','"+String(user)+"')");
            TADOQuery *rez=DB->SendSQL("call processed_list.Get_Active('"+String(eid)+"')");
            if (rez&&rez->RecordCount)
            {
                active=rez->FieldByName("active")->Value.operator bool();
            }
        }
        bool    Get_active (void)    const
        {
            return  active;
        }

        double    Get_sp_kol (void)    const
        {
            return  sp_kol;
        }
        double     Get_abs_kol (void)    const
        {
            return  abs_kol;
        }
        double     Get_all_kol (void)    const
        {
            return  all_kol;
        }
        void     Set_abs_kol    (double _abs_kol)
        {
            abs_kol=_abs_kol;
        }
        void     Set_all_kol    (double _all_kol)
        {
            all_kol=_all_kol;
        }
        String    Get_Obu    (bool gost)    const
        {
            return gost?G_Obu:V_Obu;
        }
        unsigned __int64 Get_eid(void)    const
        {
            return eid;
        }

        String     Get_EI    (void)
        {
            return Ei;
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

        void    Update    (void)
        {
            TADOQuery *rez=DB->SendSQL("call processed_list.Get_node('"+String(eid)+"')");
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

                active=rez->FieldByName("active")->Value.operator bool();

                SpRazdName=rez->FieldByName("SpRazdName")->Value;
                Name=rez->FieldByName("Name")->Value;
                V_Obd=GostToVin(rez->FieldByName("obd")->Value);
                G_Obd=VinToGost(V_Obd);
                V_Obu=GostToVin(rez->FieldByName("obu")->Value);
                G_Obu=VinToGost(V_Obu);

                Ei=rez->FieldByName("Ei")->Value;
            }else
            {
                idp=0;
                eid=0;
                eidp=0;
                sp_kol=0;
                abs_kol=0;
                active=false;
                V_Obu="";
                G_Obu="";
                Ei="шт.";
            }
            delete rez;
        }
    private:
        //мне нужны от класса следующие данные  (закоментированные переменные наследуются от базового класса)
            //рабочая информация
        //int    id;              //идентификатор узла
        int    idp;               //идентификатор предка
        unsigned __int64 eid,    //уникальный идентификатор узла развертки
                         eidp;  //уникальный идентификатор предка развертки
        double     sp_kol,            //количество у узла развертки установленное по спецификации
                abs_kol,        //количество у узла развертки пересчитанное на количество всего
                all_kol;        //общее количество узлов в загруженной спецификации
        bool    active;         //триггер активации
            //вспомогательная информация для отображения
        //int    SpRazd;        //идентификатор раздела спецификации
        //String G_Obd;         //Обозначение узла ГОСТ
        //String V_Obd;         //Обозначение узла СТП
        String G_Obu;           //Обозначение предка узла ГОСТ
        String V_Obu;           //Обозначение предка узла СТП
        String Ei;                //единици измерения
        //String Name;          //Наименование узла
        //String SpRazdName;    //Название раздела спецификации узла

    };
    class List_data //готов
    {//сделать полноценный класс
    public:
        List_data()
        {
            List_No=0;
            Type_id=0;
            CreateUser="";
            UpdateUser="";
            Type_Name="";
            CreateDate=0;
            UpdateDate=0;
            blocked=true;
        }
        List_data(    const unsigned __int64 &_List_No,const unsigned int &_Type_id,
                    const String &_CreateUser,const String &_UpdateUser,const String &_Type_Name,
                    const TDateTime &_CreateDate,const TDateTime &_UpdateDate,
                    const bool &_blocked)
        {
            List_No=_List_No;
            Type_id=_Type_id;
            CreateUser=_CreateUser;
            UpdateUser=_UpdateUser;
            Type_Name=_Type_Name;
            CreateDate=_CreateDate;
            UpdateDate=_UpdateDate;
            blocked=_blocked;
        }
        List_data(const List_data&r)
        {
            List_No=r.List_No;
            Type_id=r.Type_id;
            CreateUser=r.CreateUser;
            UpdateUser=r.UpdateUser;
            Type_Name=r.Type_Name;
            CreateDate=r.CreateDate;
            UpdateDate=r.UpdateDate;
            blocked=r.blocked;
        }
        ~List_data(void)
        {}
        List_data & operator= (const List_data &r)
        {
            if (this!=&r)
            {
                List_No=r.List_No;
                Type_id=r.Type_id;
                CreateUser=r.CreateUser;
                UpdateUser=r.UpdateUser;
                Type_Name=r.Type_Name;
                CreateDate=r.CreateDate;
                UpdateDate=r.UpdateDate;
                blocked=r.blocked;
            }
            return *this;
        }

        unsigned int    Get_List_No        (void)    const
        {
            return List_No;
        }
        unsigned int    Get_Type_id     (void)    const
        {
            return Type_id;
        }
        String            Get_CreateUser  (void)    const
        {
            return CreateUser;
        }
        String            Get_UpdateUser  (void)    const
        {
            return UpdateUser;
        }
        String            Get_Type_Name   (void)    const
        {
            return Type_Name;
        }
        TDateTime        Get_CreateDate  (void)    const
        {
            return CreateDate;
        }
        TDateTime        Get_UpdateDate  (void)    const
        {
            return UpdateDate;
        }
        bool            Get_blocked     (void)     const
        {
            return blocked;
        }
        void            Set_blocked        (bool block)
        {
            blocked=block;
        }
    private:
        unsigned __int64    List_No;//номер листа
        unsigned    int        Type_id;//идентификатор назначения
        String        CreateUser,    //создатель
                    UpdateUser, //обновитель
                    Type_Name;  //назначение
        TDateTime   CreateDate,    //дата создания
                    UpdateDate; //дата модификации
        bool        blocked;    //индикатор заблокированности листа
    };

    typedef  vector <List_data> V_List;
    typedef void (*outFunc)(Obd *Det);

    outFunc OpenTree;                //показать в дереве
    outFunc AddTexTab;              //редактировать технологию
    outFunc AddTexViewTab;          //показать технологию
    outFunc LoadTexToCurrTab;       //редактировать технологию   новая вкладка
    outFunc LoadexViewToCurrTab;    //показать технологию        новая вкладка

    V_List     list;
    List_data *Active_list;
    IconsData *IcoData;
    bool     ReadOnly,    //доступ только чтение
            inWork;        //статус в работе (разрешение на изменение содержимого списка)
    int     **Selected;
    int        StateID;    //минимально доступное состояние для пользователя
    String    StateName;  //минимально доступное состояние для пользователя
public:        // User declarations
    __fastcall TList_Editor(TComponent* Owner, TWinControl *_p, String _name,
                            const int &_LUser,cSQL *db,IconsData *_IcoData,int **_select,
                            void *_OpenTree,void* _AddTexTab,void* _LoadTexToCurrTab,
                            void* _AddTexViewTab,void* _LoadexViewToCurrTab);
    __fastcall ~TList_Editor();
};

#endif
