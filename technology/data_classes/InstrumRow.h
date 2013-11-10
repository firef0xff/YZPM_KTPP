#ifndef InstrumRowH
#define InstrumRowH
#include "SQL.h"
#include "functions.h"
class InstrumRow
    {
    typedef InstrumRow * lnk ;
    typedef const InstrumRow * c_lnk;
    public:
    InstrumRow(cSQL *db,const unsigned __int64 &_OpID,const int &_row,
                        const String &_kod,
                        const String &_Text,
                        lnk _prev);
    InstrumRow(const InstrumRow &);
    ~InstrumRow();

    int  Count (void);

    bool SaveData    (lnk &r);
    void ChangeOpID    (unsigned __int64 _OpID,lnk &r,bool no_del=false);
    

    InstrumRow *      Get_Prev    (void) {return prev;};
    InstrumRow *      Get_Next    (void) {return next;};
    InstrumRow *      Get_First    (void);
    InstrumRow *      Get_Last    (void);
    InstrumRow *     Insert_line    (int pos,lnk  line_item);
    InstrumRow *       Copy_subline(int pos,int _count);
    void            Del_subline (lnk &r,int pos,int _count);
    void            Move_items    (int pos,int _count,int new_pos);

    InstrumRow *  operator [](const unsigned int &);

    bool         isUsed        (void)const{return  (action!="del")?true:false;};
    String         Get_Text    (void)const{return Text;};
    String         Get_kod     (void)const{return kod;};

    String        Get_action(void)const{return action;}

    bool         SetValues     (const String &_Text,const String &_kod);

    void          Set_Prev(lnk r){prev=r;};
    void          Set_Next(lnk r){next=r;};

    bool         Need_Save(void);
    private:
    InstrumRow(cSQL *db,const unsigned __int64 &_OpID,const String &_action, const int &_row,
                        const String &_kod,
                        const String &_Text,
                        lnk _prev);
    void Push_Back_Deleted (void);
    void Upd_Ofset    (void);    
    
    int OpID;
    unsigned int row;
    
    String kod;
    String Text;
    
    String action;
    cSQL *const DB;

    lnk  prev;
    lnk  next;

    unsigned int ofset;

    static int count;
    };
int  InstrumRow::count=0;
#endif
