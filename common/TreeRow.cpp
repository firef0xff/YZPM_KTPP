


#pragma hdrstop

#include "TreeRow.h"
#pragma package(smart_init)

            TreeRow::TreeRow        (cSQL *const db,const int &User):Obd(db),LUser(User)
{
count++;
init();
}
            TreeRow::TreeRow        (const TreeRow &r):Obd(r),LUser(r.LUser)
{
count++;
idparent=r.idparent;
pp=r.pp;
ppp=r.ppp;
ei=r.ei;
state=r.state;
UserID=r.UserID;
V_Obu=r.V_Obu;
G_Obu=r.G_Obu;
format=r.format;
pos=r.pos;
prim=r.prim;
zona=r.zona;
ppName=r.ppName;
eiName=r.eiName;
User=r.User;
CondName=r.CondName;
DetCreator=r.DetCreator;
DetUpdater=r.DetUpdater;
RowCreator=r.RowCreator;
RowUpdater=r.RowUpdater;
kol=r.kol;
Arhive=r.Arhive;
Force=r.Force;
CanChild=r.CanChild;
Accept=r.Accept;
DetCreated=r.DetCreated;
DetUpdated=r.DetUpdated;
RowCreated=r.RowCreated;
RowUpdated=r.RowUpdated;
}
            TreeRow::~TreeRow        (void)
{
count--;
}

TreeRow &     TreeRow::operator =        (const TreeRow &r)
{
if (this==&r) {return *this;}
//базовый класс
id=r.id;
SpRazd=r.SpRazd;
G_Obd=r.G_Obd;
V_Obd=r.V_Obd;
Name=r.Name;
SpRazdName=r.SpRazdName;
//текущий класс
idparent=r.idparent;
pp=r.pp;
ppp=r.ppp;
ei=r.ei;
state=r.state;
UserID=r.UserID;
V_Obu=r.V_Obu;
G_Obu=r.G_Obu;
format=r.format;
pos=r.pos;
prim=r.prim;
zona=r.zona;
ppName=r.ppName;
eiName=r.eiName;
User=r.User;
CondName=r.CondName;
DetCreator=r.DetCreator;
DetUpdater=r.DetUpdater;
RowCreator=r.RowCreator;
RowUpdater=r.RowUpdater;
kol=r.kol;
Arhive=r.Arhive;
Force=r.Force;
CanChild=r.CanChild;
Accept=r.Accept;
DetCreated=r.DetCreated;
DetUpdated=r.DetUpdated;
RowCreated=r.RowCreated;
RowUpdated=r.RowUpdated;
return *this;
}
bool           TreeRow::operator ==    (const TreeRow &r)
{
if (this==&r) {return true;}
if (//базовый класс
    id==r.id&&
    SpRazd==r.SpRazd&&
    G_Obd==r.G_Obd&&
    V_Obd==r.V_Obd&&
    Name==r.Name&&
    SpRazdName==r.SpRazdName&&
    //текущий класс
    idparent==r.idparent&&
    pp==r.pp&&
    ppp==r.ppp&&
    ei==r.ei&&
    state==r.state&&
    UserID==r.UserID&&
    V_Obu==r.V_Obu&&
    G_Obu==r.G_Obu&&
    format==r.format&&
    pos==r.pos&&
    prim==r.prim&&
    zona==r.zona&&
    ppName==r.ppName&&
    eiName==r.eiName&&
    User==r.User&&
    CondName==r.CondName&&
    DetCreator==r.DetCreator&&
    DetUpdater==r.DetUpdater&&
    RowCreator==r.RowCreator&&
    RowUpdater==r.RowUpdater&&
    kol==r.kol&&
    Arhive==r.Arhive&&
    Force==r.Force&&
    CanChild==r.CanChild&&
    Accept==r.Accept&&
    DetCreated==r.DetCreated&&
    DetUpdated==r.DetUpdated&&
    RowCreated==r.RowCreated&&
    RowUpdated==r.RowUpdated)
    {
    return true;
    }
return false;
}
bool           TreeRow::operator !=    (const TreeRow &r)
{
if (this==&r) {return false;}
if (//базовый класс
    id==r.id&&
    SpRazd==r.SpRazd&&
    G_Obd==r.G_Obd&&
    V_Obd==r.V_Obd&&
    Name==r.Name&&
    SpRazdName==r.SpRazdName&&
    //текущий класс
    idparent==r.idparent&&
    pp==r.pp&&
    ppp==r.ppp&&
    ei==r.ei&&
    state==r.state&&
    UserID==r.UserID&&
    V_Obu==r.V_Obu&&
    G_Obu==r.G_Obu&&
    format==r.format&&
    pos==r.pos&&
    prim==r.prim&&
    zona==r.zona&&
    ppName==r.ppName&&
    eiName==r.eiName&&
    User==r.User&&
    CondName==r.CondName&&
    DetCreator==r.DetCreator&&
    DetUpdater==r.DetUpdater&&
    RowCreator==r.RowCreator&&
    RowUpdater==r.RowUpdater&&
    kol==r.kol&&
    Arhive==r.Arhive&&
    Force==r.Force&&
    CanChild==r.CanChild&&
    Accept==r.Accept&&
    DetCreated==r.DetCreated&&
    DetUpdated==r.DetUpdated&&
    RowCreated==r.RowCreated&&
    RowUpdated==r.RowUpdated)
    {
    return false;
    }
return true;
}
void         TreeRow::init            (void)
{
idparent=-1;
pp=-1;
ppp=-1;
ei=-1;
state=-1;
UserID=-1;
V_Obu="";
G_Obu="";
format="";
pos="";
prim="";
zona="";
ppName="";
eiName="";
User="";
CondName="";
DetCreator="";
DetUpdater="";
RowCreator="";
RowUpdater="";
kol=0;
Arhive=false;
Force=false;
CanChild=false;
Accept=false;
DetCreated=0;
DetUpdated=0;
RowCreated=0;
RowUpdated=0;
}
void         TreeRow::SetObu         (const String &r)
{
V_Obu=GostToVin(r);
G_Obu=VinToGost(r);
}
void         TreeRow::SetObd         (const String &r)
{
V_Obd=GostToVin(r);
G_Obd=VinToGost(r);
}
void         TreeRow::SetId           (const int &r)
{
id=r;
}
bool         TreeRow::UpdateVal         (void)
{
String sql;
if (idparent>=0)
    {
    sql="call constructions.UpdateRowInfo('"+String(idparent)+"','"+String(id)+"','"+String(LUser)+"')";
    }else
    {
    sql="Call constructions.LoadDet('"+String(id)+"','"+String(LUser)+"')";
    }
TADOQuery *rez=DB->SendSQL(sql);
if (rez&&rez->RecordCount)
    {
    //базовый класс
    SetId(rez->FieldByName("idchild")->Value);
    SpRazd=rez->FieldByName("razdSPID")->Value;    
    SetObd(rez->FieldByName("obd")->Value.operator UnicodeString());    
    Name=rez->FieldByName("name")->Value.operator UnicodeString();
    SpRazdName=rez->FieldByName("Razdname")->Value;
    //текущий классс
    idparent=rez->FieldByName("idparent")->Value;    
    pp=rez->FieldByName("pp")->Value.operator UnicodeString().ToInt();
    ppp=rez->FieldByName("ppp")->Value.operator UnicodeString().ToInt();
    ei=rez->FieldByName("ei")->Value.operator UnicodeString().ToInt();    
    state=rez->FieldByName("state")->Value;    
    UserID=rez->FieldByName("UserID")->Value;
    SetObu(rez->FieldByName("obu")->Value.operator UnicodeString());    
    format=rez->FieldByName("format")->Value;    
    pos=rez->FieldByName("pos")->Value;    
    prim=rez->FieldByName("prim")->Value;
    zona=rez->FieldByName("zona")->Value;    
    ppName=rez->FieldByName("ppName")->Value.operator UnicodeString();    
    eiName=rez->FieldByName("eiName")->Value;        
    User=rez->FieldByName("User")->Value;
    CondName=rez->FieldByName("CondName")->Value;    
    DetCreator=rez->FieldByName("DetCreator")->Value;    
    DetUpdater=rez->FieldByName("DetUpdater")->Value;    
    RowCreator=rez->FieldByName("RowCreator")->Value;
    RowUpdater=rez->FieldByName("RowUpdater")->Value;
    kol=rez->FieldByName("kol")->Value;    
    Arhive=rez->FieldByName("arhive")->Value;
    CanChild=rez->FieldByName("CanChild")->Value;    
    Accept=rez->FieldByName("Accept")->Value;    
    if (!rez->FieldByName("DetCreated")->Value.IsNull()){DetCreated=rez->FieldByName("DetCreated")->Value.operator TDateTime();}
    if (!rez->FieldByName("DetUpdated")->Value.IsNull()){DetUpdated=rez->FieldByName("DetUpdated")->Value.operator TDateTime();}
    if (!rez->FieldByName("RowCreated")->Value.IsNull()){RowCreated=rez->FieldByName("RowCreated")->Value.operator TDateTime();}
    if (!rez->FieldByName("RowUpdated")->Value.IsNull()){RowUpdated=rez->FieldByName("RowUpdated")->Value.operator TDateTime();}    
    delete rez;
    }else
    {
    Obd::init();
    init();
    delete rez;
    }
return CanUse();
} 

bool         TreeRow::SetData(
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
                    )
{
if (ItTrueClassName())
    {
    SetId(_id);// базовый класс
    SpRazd=_SpRazd;
    SetObd(_Obd);
    Name=_Name.Trim();
    SpRazdName=_SpRazdName.Trim();
    // текущий класс
    idparent=_idparent;
    pp=_pp;
    ppp=_ppp;
    ei=_ei;
    state=_state;
    UserID=_UserID;
    SetObu(_Obu);
    format=_format.Trim();
    pos=_pos.Trim();
    prim=_prim.Trim();
    zona=_zona.Trim();
    ppName=_ppName.Trim();
    eiName=_eiName.Trim();
    User=_User.Trim();
    CondName=_CondName.Trim();
    DetCreator=_DetCreator.Trim();
    DetUpdater=_DetUpdater.Trim();
    RowCreator=_RowCreator.Trim();
    RowUpdater=_RowUpdater.Trim();
    kol=_kol;
    Arhive=_arhive;
    Set_Force(false);
    CanChild=_CanChild;
    Accept=_Accept;
    DetCreated=_DetCreated;
    DetUpdated=_DetUpdated;
    RowCreated=_RowCreated;
    RowUpdated=_RowUpdated;    
    }
return CanUse();
}                    