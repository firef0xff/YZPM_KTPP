

#ifndef TreeRowH
#define TreeRowH
#include "Obd.h"

class TreeRow:public Obd
    {
    public:
        TreeRow        (cSQL *const db,const int &User);
        TreeRow        (const TreeRow &r);
        ~TreeRow    (void);
        bool UpdateVal     (void);
        void Set_Force(const bool force){Force=force;};
        
        String Get_Text (void)    const{return G_Obd+" - "+Name+" - "+String(kol)+eiName;};
        int Get_ParentID(void)    const{return idparent;};
        int Get_pp(void)        const{return pp;};
        int Get_ppp(void)        const{return ppp;};
        int Get_ei(void)        const{return ei;};
        int Get_state(void)        const{return state;};
        int Get_UserID(void)    const{return UserID;};
        String Get_Obu(bool gost)const{return gost?G_Obu:V_Obu;};
        String Get_format(void)    const{return format;};
        String Get_pos(void)    const{return pos;};
        String Get_prim(void)    const{return prim;};
        String Get_zona(void)    const{return zona;};
        String Get_ppName(void)    const{return ppName;};
        String Get_eiName(void)    const{return eiName;};
        String Get_User(void)    const{return User;};
        String Get_CondName(void)    const{return CondName;};
        String Get_DetCreator(void)    const{return DetCreator;};
        String Get_DetUpdater(void)    const{return DetUpdater;};
        String Get_RowCreator(void)    const{return RowCreator;};
        String Get_RowUpdater(void)    const{return RowUpdater;};
        double Get_kol(void)        const{return kol;};
        bool Get_Arhive(void)        const{return Arhive;};
        bool Get_Force(void)        const{return Force;};
        bool Get_CanChild(void)        const{return CanChild;};
        bool Get_Accept(void)        const{return Accept;};
        TDateTime  Get_DetCreated(void)    const{return DetCreated;};
        TDateTime  Get_DetUpdated(void)    const{return DetUpdated;};
        TDateTime  Get_RowCreated(void)    const{return RowCreated;};
        TDateTime  Get_RowUpdated(void)    const{return RowUpdated;};
        
        bool SetData(
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
        
        TreeRow &     operator =(const TreeRow &);
        bool           operator ==    (const TreeRow &);
        bool           operator !=    (const TreeRow &);
        
        bool ItTrueClassName (void)const{return TrueClassName()=="TreeRow"?true:false;}
        String TrueClassName (void)const{return "TreeRow";};
        bool CanUse    (void)        const{return (id>0&&Get_Obd(false)!="")?true:false;};
        
        int    Count    (void)const{return count;};
    private:
        static int count;

    protected:

        int idparent;
        int pp;
        int ppp;
        int ei;
        int state;
        int UserID;
        String V_Obu;
        String G_Obu;
        String format;
        String pos;
        String prim;
        String zona;
        String ppName;
        String eiName;
        String User;
        String CondName;
        String DetCreator;
        String DetUpdater;
        String RowCreator;
        String RowUpdater;
        double kol;
        bool Arhive;
        bool Force;
        bool CanChild;
        bool Accept;
        TDateTime  DetCreated;
        TDateTime  DetUpdated;
        TDateTime  RowCreated;
        TDateTime  RowUpdated;

        const int &LUser;

        void init        (void);
        void SetObu     (const String &r);
        void SetObd     (const String &r);
        void SetId       (const int &r);
    };

int  TreeRow::count=0;
#endif
