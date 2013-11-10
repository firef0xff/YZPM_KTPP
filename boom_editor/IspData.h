//---------------------------------------------------------------------------

#ifndef IspDataH
#define IspDataH
#include "functions.h"
class IspData
    {
    public:
    IspData();
    int id;
    bool main_isp;
    bool selected;
    String    Get_O_V_Obd(void) const{return O_V_Obd;}
    String  Get_Obd(bool gost)const{return gost?G_Obd:V_Obd;};
    void    Set_Obd(const String &r);
    private:
    String O_V_Obd; 
    String G_Obd;
    String V_Obd;
    };
#endif
