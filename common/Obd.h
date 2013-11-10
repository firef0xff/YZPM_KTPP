

#ifndef ObdH
#define ObdH
#include "SQL.h"
#include "functions.h"


class Obd
    {
    public:
        
           Obd(cSQL *const db);
        Obd(cSQL *const db,const String &_obd);
        Obd(cSQL *const db,const int &_id);
        Obd(const Obd &);
        virtual~Obd(void);
    
        String    Get_Obd        (bool gost)    const{return gost?G_Obd:V_Obd;};
        String    Get_Text    (void)        const{return G_Obd+" - "+Name;};
        String    Get_Name    (void)        const{return Name;};
        String     Get_SpRazdName(void)    const{return SpRazdName;};
        int     Get_SpRazd    (void)      const{return SpRazd;};
        int        Get_ID        (void)        const{return id;};
        bool     UpdateVal     (void)            {return Get_Val(1);};
        
        bool    SetObd    (const String &r);
        bool    SetId    (const int &ID);
        bool     SetData (const int &_id,const int &_SpRazd,const String &_Obd,const String &_Name,const String &_SpRazdName);
        
        Obd &     operator =    (const Obd &);
        bool     operator ==    (const Obd &);
        bool     operator !=    (const Obd &);
        int    Count    (void)const{return count;};
        
        bool ItTrueClassName (void)const{return TrueClassName()=="Obd"?true:false;};
        virtual String TrueClassName (void)const{return "Obd";};        
        virtual bool CanUse    (void)        const{return (id>0&&Get_Obd(false)!="")?true:false;};
    protected:
        
        int    id;
        int    SpRazd;
        String G_Obd;
        String V_Obd;
        String Name;
        String SpRazdName;
        
        cSQL *const DB;
        
        void init (void);
    private:
        
        static int  count;
        bool     Get_Val     (char type);
    };
int Obd::count=0;
#endif
