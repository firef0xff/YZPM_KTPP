//---------------------------------------------------------------------------

#ifndef SPROWH
#define SPROWH
#include "TreeRow.h"

class SpRow:public TreeRow
    {
    public:
        // инициализация
        SpRow        (cSQL *const db,const int &User,
                            const int &_id,    const int &_idparent,const int &_SpRazd,    const int &_pp,
                            const int &_ppp,    const int &_ei,        const int &_state,    const int &_UserID,
                            const String &_Obd,        const String &_Obu,
                            const String &_Name,    const String &_SpRazdName,
                            const String &_format,    const String &_pos,        const String &_prim,
                            const String &_zona,        const String &_ppName,    const String &_eiName,
                            const String &_User,        const String &_CondName,    const String &_DetCreator,
                            const String &_DetUpdater,    const String &_RowCreator,
                            const String &_RowUpdater,    const double &_kol,
                            const bool &_arhive,    const bool &_CanChild,    const bool &_Accept,
                            const TDateTime  &_DetCreated,    const TDateTime  &_DetUpdated,
                            const TDateTime  &_RowCreated,    const TDateTime  &_RowUpdated
                            );
        SpRow        (cSQL *const db,const int &User,
                            const int &_pp,        const int &_ppp,    const int &_SpRazd,
                            const String &_Obd,        const String &_Obu,
                            const String &_Name,    const String &_SpRazdName,
                            const String &_format,    const String &_pos,        const String &_prim,
                            const String &_zona,    const double &_kol
                            );
        SpRow        (cSQL *const db,const int &User,
                            const int &_id,    const int &_idparent, const int &_SpRazd,    const int &_pp,
                            const int &_ppp,    const int &_ei,        const int &_state,    const int &_UserID,
                            const String &_Obd,        const String &_Obu,
                            const String &_Name,    const String &_SpRazdName,
                            const String &_format,    const String &_pos,        const String &_prim,
                            const String &_zona,        const String &_ppName,    const String &_eiName,
                            const String &_User,        const String &_CondName,    const String &_DetCreator,
                            const String &_DetUpdater,    const String &_RowCreator,
                            const String &_RowUpdater,
                            const String &_action_row,  const String &_action_det,
                            const double &_kol,
                            const bool &_arhive,    const bool &_CanChild,    const bool &_Accept,
                            const bool &_inBase,
                            const TDateTime  &_DetCreated,    const TDateTime  &_DetUpdated,
                            const TDateTime  &_RowCreated,    const TDateTime  &_RowUpdated
                            );
      //    SpRow        (const SpRow &r);
        ~SpRow      (void);
        //функции доступа
        /*
        набор функций класса set для полей спецификации */
        String Get_Text (void);
        void    Correct_obd(void);
        void     SetObd (const String &r);
        void     SetObu ( const String &r);
        void     Set_pp             (const int &r);
        void     Set_ei             (const int &r);
        void     Set_ppp         (const int &r);
        void     Set_Name         (const String &r);
        void     Set_SpRazd      (const int &idr,const String &r);
        void     Set_format      (const String &r);
        void     Set_pos         (const String &r);
        void     Set_prim        (const String &r);
        void     Set_zona        (const String &r);
        void     Set_kol         (const double &r);
        void    Set_ID            (void);
        void    Set_IDp         (const int &r);
        bool     Load_det        (void);
        //удаление из спецификации
        void    Delete            (void){if (action_row_t==""){action_row_t=action_row;action_row="del";}};
        void    Recover            (void){if (action_row_t!=""){action_row=action_row_t;action_row_t="";}};
        void    Set_actions        (String row,String det){action_row=row;action_det=det;};
        String    Get_act_r        (void){return action_row;};
        String    Get_act_d        (void){return action_det;};
        //для удаления и обновления ключей
        int     Get_idp_t        (void){return idp_t;}
        int     Get_id_t        (void){return id_t;}
        // вспомогательные
        bool         isUsed        (void)const{return  (action_row!="del")?true:false;};
        //операторы
        SpRow &     operator =(const SpRow &);
        bool           operator ==    (const SpRow &);
        bool           operator !=    (const SpRow &);
        //идентификация
        bool ItTrueClassName (void)const{return TrueClassName()=="SpRow"?true:false;}
        String TrueClassName (void)const{return "SpRow";};

        bool CanUse    (void)const{return action_row=="del"?false:true;};

        int    Count    (void)const{return count;};
        bool UpdateVal     (void);
    protected:
        int     id_t;       //назальное значение идентификатора детали
        int     idp_t;      //начальное значение
        String     G_Obd_t;     //изначальное обозначенеие
        String     V_Obd_t;    //изначальное обозначенеие
        String     action_row;    //метка действия со строкой
        String  action_row_t;
        String  action_det; //метка действия с параметрами детали
        bool     inBase;        //метка наличия строки в базе
        //инициализация
        void    init    (void);
    private:
        bool     SetData     (void){return false;};
        bool     Load_row    (void);
        int     Get_id        (const String &obd);
        void    Set_ei        (void);
        void    Load_det    (const int &_id);
        void     Change_obd    (const String &obd);
        static int count;
    };
int SpRow::count=0;
#endif
