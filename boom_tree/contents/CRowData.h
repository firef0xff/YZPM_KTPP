#ifndef CRowDataH
#define CRowDataH
#include <Classes.hpp>
class CRowData
    {
    public:
    CRowData(const bool &_MassAction,        const int &_id,const int &_CurrState,
            const int &_NextState,            const int &_PrevState,
            const String &_text,            const String &_CurrStateName,
            const String &_NextStateName,    const String &_PrevStateName,
            const bool &_Accept,      const bool &_Arhive,    const bool &_NextAccept,
            const bool &_PrevAccept);

    ~CRowData(void);
    int GetCurrState(void)            const{return CurrState;}
    int GetNextState(void)            const{return NextState;}
    int GetSelectedState(void)        const{return SelectedState;}
    String GetSelectedStateName()     const{return SelectedStateName;}
    bool GetSelectedAccept()         const{return SelectedAccept;}
    bool GetArhive(void)            const{return Arhive;}
    bool TurnCurrState(void);
    bool TurnNextState(void);
    bool TurnPrevState(void);
    void SetNextState(const int &StateID,const String &StateName,const bool &StateAccept);
    void SetPrevState(const int &StateID,const String &StateName,const bool &StateAccept);
    String GetText(void);
    int GetID(void){return id;};
    private:
    
    int CurrState;
    int NextState;
    int PrevState;
    String CurrStateName;
    String NextStateName;
    String PrevStateName;
    
    bool Accept;
    bool Arhive;
    bool NextAccept;
    bool PrevAccept;
    
    static int count;
    
    const bool &MassAction;
    int id;
    String text;
    int SelectedState;
    String SelectedStateName;
    bool SelectedAccept;
    };
int CRowData::count=0;

#endif
