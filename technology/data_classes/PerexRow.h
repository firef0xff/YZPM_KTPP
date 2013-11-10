#ifndef PerexRowH
#define PerexRowH
#include "SQL.h"
#include "functions.h"
class PerexRow 
    {
    typedef PerexRow * lnk ;
    typedef const PerexRow * c_lnk;
    public:
    PerexRow(cSQL *db,const unsigned __int64 &_OpID,const int &_row,const String &_Text,lnk _prev);
    PerexRow(const PerexRow &);
    ~PerexRow();

    int  Count (void);
    bool SaveData(lnk &r);
    void ChangeOpID    (unsigned __int64 _OpID,lnk &r,bool no_del=false);
    

    PerexRow *     Get_Prev    (void) {return prev;};
    PerexRow *     Get_Next    (void) {return next;};
    PerexRow *     Get_First    (void);
    PerexRow *     Get_Last    (void);
    PerexRow *    Insert_line    (int pos,lnk line_item);
    PerexRow *  Copy_subline(int pos,int _count);
    void        Del_subline (lnk &r,int pos,int _count);
    void        Move_items    (int pos,int _count,int new_pos);

    PerexRow * operator [](const unsigned int &);

    bool         isUsed        (void)const{return  (action!="del")?true:false;};
    String         Get_Text    (void)const{return Text;};

    String        Get_action(void)const{return action;}//для теста

    bool         SetValues     (const String &_Text);

    void          Set_Prev(lnk r){prev=r;};
    void          Set_Next(lnk r){next=r;};

    bool         Need_Save(void);
    private:
    PerexRow(cSQL *db,const unsigned __int64 &_OpID,const String &_action, const int &_row,
                        const String &_Text,
                        lnk _prev);
    void Push_Back_Deleted (void);
    void Upd_Ofset    (void);
    
    unsigned __int64 OpID;
    int unsigned row;

    String Text;    
    
    String action;         
    cSQL *const DB;
    
    lnk prev;
    lnk next;

    unsigned int ofset;

    static int count;
    };
int  PerexRow::count=0;
#endif
