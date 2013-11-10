 #pragma hdrstop
#include "NrmRow.h"
#pragma package(smart_init)
     NrmRow::NrmRow    (cSQL *db,const String &_LUser,const unsigned __int64 &_OpID,const String &_action,
            const int &_kolod,     const String  &__prof,
            const String  &_krop,const String  &__rr,
            const String  &_en,  const String  &_kts,
            const String  &_kvn, const String  &_ttp,
            const double  &_ksht,const double  &_tpz,
            const double  &_tsht,
            const String  &_CreateUser,
            const String  &_UpdateUser,
            const TDateTime  &_CreateDate,
            const TDateTime  &_UpdateDate,
            lnk _prev):DB(db),prev(0),next(0),ofset(0)
{
count++;
action=_action;
OpID=_OpID; 
LUser=&_LUser;  

kolod=_kolod;
_prof=__prof;
krop=_krop;      
_rr=__rr;
en=_en;
kts=_kts;  
kvn=_kvn;
ttp=_ttp;

ksht=_ksht;
tpz=_tpz;
tsht=_tsht;

CreateUser=_CreateUser;
UpdateUser=_UpdateUser;
CreateDate=_CreateDate; 
UpdateDate=_UpdateDate; 

//����������� ����� � ����
if (_prev)
    {          //��������� ������� ����
    prev=_prev;
    // ������ ����������� � ����
    next=prev->next;
    prev->next=this;
    if (next)
        {
        next->prev=this;
        }
    }
Upd_Ofset();
}
     NrmRow::NrmRow(const NrmRow &r):DB(r.DB),prev(0),next(0),ofset(0)

{// ���������� ��� ����������� ���� �������
count++;
//���������� ������ �������
c_lnk first=&r;
while (first->prev)
    {
    first=first->prev;
    }
//����������� ������
action=first->action;
OpID=first->OpID;
LUser=first->LUser;  

kolod=first->kolod;
_prof=first->_prof;
krop=first->krop;
_rr=first->_rr;
en=first->en;         
kts=first->kts;  
kvn=first->kvn;
ttp=first->ttp;

ksht=first->ksht;
tpz=first->tpz;
tsht=first->tsht;

CreateUser=first->CreateUser;
UpdateUser=first->UpdateUser;
CreateDate=first->CreateDate; 
UpdateDate=first->UpdateDate; 

ofset=0;//������ �������� ����
// ����������� ��������� �������
c_lnk t=first->next;
lnk n=this;
while (t)
    {//���� ����������� ������� ������ // ����������.
    n=new NrmRow(t->DB,*t->LUser,t->OpID,t->action,t->kolod,t->_prof,t->krop,t->_rr,t->en,t->kts,t->kvn,t->ttp,t->ksht,t->tpz,t->tsht,t->CreateUser,t->UpdateUser,t->CreateDate,t->UpdateDate,n);
    t=t->next;
    }
}
     NrmRow::~NrmRow()
{
if (prev)
    {
    prev->next=next;
    }
if (next)
    {
    next->prev=prev;
    next->Upd_Ofset();
    }
count--;
}

void         NrmRow::Upd_Ofset    (void)
{
for (lnk i=this; i; i=i->next)
    {
    if (i->prev)
        {
        i->ofset=i->prev->ofset+1;
        }else
        {
        i->ofset=0;
        }
    }
}
int          NrmRow::Count         (void)
{
lnk curr=this;
while (curr->next)
    {
    curr=curr->next;
    }
return curr->ofset+1;
}

NrmRow *    NrmRow::Insert_line    (int pos,lnk line_item)
{
lnk first_line_item=line_item->Get_First();  //��������� ��������� ������� ����� ����������� �������
lnk first_item=Get_First();           //��������� ��������� ������� ����� ������� �������
if (first_line_item!=first_item)                 //�������� ����� ������� ������� ����� � ���� (���������������). ����� ��������� ���� �������
    {
    //��������� ������� �������
    int _count=this->Count();                 //��������� ���������� ������� � �������
    if (_count<pos)                          //�������� ������ ������� �� ������� �������.
        {
        pos=_count;                         //��������� ������� �� ��������� ������� ������� (���������� ������������ � ����� �������)
        }
    if (pos<0)                          //�������� ������ ������� �� ������� �������.
        {
        pos=0;                         //��������� ������� �� ������ ������� ������� (���������� ����������� � ������� ����� ������� ���������)
        }
    lnk section=this->operator [](pos);
    lnk tmp=first_line_item;
    //������������ � ��������� �������
    while (tmp)
        {
        if (tmp->action!="del")
            {
            tmp->OpID=section->OpID;
            tmp->LUser=section->LUser;//������ ����� �� ������������ �� ����������
            tmp->action="ins";
            }else
            {
            delete tmp;
            }
        tmp=tmp->next;
        }
    lnk last_line_item=line_item->Get_Last();
    //������ �������
    if (_count!=pos)
        {  //������ � ���������� ���� �����
        first_line_item->prev=section->prev;
        if (section->prev)
            {
            section->prev->next=first_line_item;
            }
        section->prev=last_line_item;
        last_line_item->next=section;
        }else
        {  //������ � ���������� ���� �������
        last_line_item->next=section->next;
        if (section->next)
            {
            section->next->prev=last_line_item;
            }
        section->next=first_line_item;
        first_line_item->prev=section;
        }
    //������������� ������� �������
    first_item=Get_First();
    first_item->Upd_Ofset();
    }
return first_item;
}
NrmRow *      NrmRow::Copy_subline    (int pos,int _count)
{    //���������� ������ �������� ��� ������� del
    //�������� �������
int cnt=this->Count();
if (cnt>pos)
    {//����� ������� ������������
    lnk node=this->operator [](pos);
    while (node&&node->action=="del"&&_count>0)
        {
        pos++;
        _count--;
        node=node->next;
        }    
    if (node&&_count>0)//�������� ��������� ������� �� ������� ���� � �� ������� �� ������� ���������� ����������
        {// �������� ������� ���� �������
        lnk ret=new NrmRow(    node->DB,*node->LUser,node->OpID,node->action,node->kolod,
                            node->_prof,node->krop,node->_rr,node->en,node->kts,node->kvn,
                            node->ttp,node->ksht,node->tpz,node->tsht,node->CreateUser,
                            node->UpdateUser,node->CreateDate,node->UpdateDate,0
                            );
        for (int i=1; i<_count&&node->next; i++)
            {//�������� ��������� ����� �������
            node=node->next;
            if (node->action!="del")
                {//���������� ������ � ������ ���� ���� �� ������������ ��� ��������
            ret=new NrmRow(    node->DB,*node->LUser,node->OpID,node->action,node->kolod,
                            node->_prof,node->krop,node->_rr,node->en,node->kts,node->kvn,
                            node->ttp,node->ksht,node->tpz,node->tsht,node->CreateUser,
                            node->UpdateUser,node->CreateDate,node->UpdateDate,ret
                            );                            
                }
            }
        return ret->Get_First();    
        }
    }
return 0;
}
void        NrmRow::Del_subline     (lnk &r,int pos,int _count)
{//������� ������ � �������� ins ��������� ������� del
    //�������� �������
int cnt=this->Count();
r=0;
if (cnt>pos)
    {
    lnk node=this->operator [](pos);
    for (int i=0; i<_count&&node; i++)
        {
         if (node->action=="ins")
            {
            if (node->next)
                {// ������� �������� ��������
                node=node->next;
                delete node->prev;
                }else
                {
                if (node->prev)
                    {//����� ���� ���� ������ �� ���������� �������� ������� ����� �������
                    node=node->prev;
                    delete node->next;
                    }else
                    {//���� ��������� ������������ �������
                    delete node;
                    node=0;
                    r=0;
                    }
                }
            }else
            {
            r=node;
            node->action="del";
            node=node->next;
            }
        }
    if (node)
        {
        r=node->Get_First();
        }else
        {
        if (r)
            {
            r=r->Get_First();
            }
        } // ��������� ����� � ������� ������� ��� ���������� ��������� �� ������� ���������� ����
    if (r){r->Push_Back_Deleted();}
    }
}
void        NrmRow::Move_items    (int pos,int _count,int new_pos)
{
if (_count>0&&pos!=new_pos)
    {
    // �������� ��������� �� ������� ��������� �������� �������
    lnk first_move_item=this->operator [](pos);
    lnk last_move_item=this->operator [](pos+_count-1);
    // �������� ��������� �� ���� ����� �������� ������� � ������ ���������� ������������ ��������
    // �������� ������� ������� � ���������, � ��� ������������� �������� ��������� �������� ������� ��� �������
    int real_ins_pos;
    if (new_pos>pos)
        {
        real_ins_pos=new_pos+_count;
        }else
        {//��� ����� � ������������� �������...
        real_ins_pos=new_pos;
        }
    //��������� �������� ������� ��������
    if (real_ins_pos<0)
        {
        real_ins_pos=0;
        }
    int count=Count();
    if (real_ins_pos>count)
        {
        real_ins_pos=count;
        }
    lnk section=this->operator [](real_ins_pos);
    //�������� �� ����������� ����� ������� � ������ �������
    if (section!=last_move_item)
        {
            //������ �������
            // ����� �������������� ����
        if (first_move_item->prev)
            {
            first_move_item->prev->next=last_move_item->next;
            }
        if (last_move_item->next)
            {
            last_move_item->next->prev=first_move_item->prev;
            }
        lnk before=0;
        lnk after=0;
        // ����� ������ �������
        if (count!=real_ins_pos)
            {  //������ ����� ��������� �����
            before=section->prev;
            after=section;
            }else
            {  //������ ����� ���������� ����
            before=section;
            after=section->next;
            }
        // �������� �������
        first_move_item->prev=before;
        if (before)
            {
            before->next=first_move_item;
            }
        last_move_item->next=after;
        if (after)
            {
            after->prev=last_move_item;
            }
        //������������� ������� �������
        Get_First()->Upd_Ofset();
        }
    }
}

NrmRow *     NrmRow::Get_First    (void)
{
lnk t=this;
while (t->prev)
    {
    t=t->prev;
    }
return t;
}
NrmRow *     NrmRow::Get_Last    (void)
{
lnk t=this;
while (t->next)
    {
    t=t->next;
    }
return t;
}
NrmRow *     NrmRow::operator [](const unsigned int &r)
{
if (r==ofset)
    {
    return this;
    }else
    {
    if (r<ofset)
        {
        if (prev)
            {
            return prev->operator [](r);
            }else
            {
            return this;
            }
        }else
        {
        if (next)
            {
            return next->operator [](r);
            }else
            {
            return this;
            }
        }
    }
}


bool NrmRow::SetValues (const int &_kolod,const String  &__prof,const String  &_krop,const String  &__rr,
                        const String  &_en,  const String  &_kts,const String  &_kvn, const String  &_ttp,
                        const double  &_ksht,const double  &_tpz,const double  &_tsht)
{
if (action=="del"){return false;}
if (_kolod!=kolod||__prof!=_prof||_krop!=krop||__rr!=_rr||_en!=en||_kts!=kts||_kvn!=kvn||_ttp!=ttp||_ksht!=ksht||_tpz!=tpz||_tsht!=tsht)
    {
    if (_kolod!=0||__prof!=""||_krop!=""||__rr!=""||
            _en!=""||_kts!=""||_kvn!=""||_ttp!=""||
            _ksht!=0||_tpz!=0||_tsht!=0)
        {//������
        //������ ������
        if (_prof!=__prof||_rr!=__rr)
            {
            if (action=="ins")
                {// ������ ������� ��� ������ ����� ������ �������� ��� ����������
                _prof=__prof;
                _rr=__rr;
                kolod=_kolod;
                krop=_krop;
                en=_en;
                kts=_kts;
                kvn=_kvn;
                ttp=_ttp;
                ksht=_ksht;
                tpz=_tpz;
                tsht=_tsht;
                }else
                { //� ������ ������� ������ � ���� ������ ����� �� �������� � �������
                new NrmRow(DB,*LUser,OpID,"ins",_kolod,__prof,_krop,__rr,_en,_kts,_kvn,
                _ttp,_ksht,_tpz,_tsht,CreateUser,UpdateUser,CreateDate,UpdateDate,this);
                action="del";
                Push_Back_Deleted();
                }
            }else
            {//��� �� ���������� ������ �������� �� ��������� ������
            if (kolod!=_kolod||krop!=_krop||
                en!=_en||kts!=_kts||kvn!=_kvn||ttp!=_ttp||
                ksht!=_ksht||tpz!=_tpz||tsht!=_tsht)
                {//  � ������ ���� ������ �������� ������ ������
                if (action!="ins"){action="upd";}
                kolod=_kolod;
                krop=_krop;
                en=_en;
                kts=_kts;
                kvn=_kvn;
                ttp=_ttp;
                ksht=_ksht;
                tpz=_tpz;
                tsht=_tsht;
                }
            }
        }else
        {//��������
        if (action=="ins")
            {
            delete this;
            }else
            {
            action="del";
            Push_Back_Deleted();
            }
        }
    return true;
    }else
    {
    return false;
    }
}
bool NrmRow::SaveData    (lnk &r)
{
bool effect=true;
String del="",ins="";
//�������� �����
//���� ������
for (lnk   t=Get_Last();t&&t->action=="del";t=t->prev)
    {// ������� ��������� ��� del ����� ���������� ��� ins������� �������� ��������� ��� upd
    if (del=="")
        {
        del="('0','0','0'),('"+String(t->OpID)+"','"+t->_prof+"','"+t->_rr+"'),";
        }else
        {
        del=del+"('"+String(t->OpID)+"','"+t->_prof+"','"+t->_rr+"'),";
        }
    }
if (del!="")
    {
    del.Delete(del.Length(),1);
    del="("+del+")";
    effect=r->DB->SendCommand("delete from technologic.operation_norms where (OpUUID,prof,rr) in "+del);
    //��������� ������� � ���������� ������� ��������� �����
    if (effect)
        {
        lnk t=r->Get_First();
        while (t)
            {
            if (t->action=="del")
                {
                if (t->prev)
                    {
                    t=t->prev;
                    if (t->next==r) {r=t;}
                    delete t->next;
                    t=t->next;
                    }else
                    {
                    if (t->next)
                        {
                        t=t->next;
                        if (t->prev==r) {r=t;}
                        delete t->prev;
                        }else
                        {
                        delete t;
                        r=0;return effect;
                        }
                    }
                }else
                {
                t=t->next;
                }
            }
        }else
        {
        return effect;//������ � ������� ��������
        }
    }
//���������� �����  // � ��������� ������� ����������
for (lnk  t=r->Get_First();t;t=t->next)
    {// ������� ��������� ��� del ����� ���������� ��� ins������� �������� ��������� ��� upd
    if (t->action=="upd")
        {
        effect=r->DB->SendCommand("update technologic.operation_norms set ksht='"+Replace(String(t->ksht),",",".")+"',krop='"+t->krop+"',kolod='"+String(t->kolod)+"',EN='"+t->en+"',kts='"+t->kts+"',kvn='"+t->kvn+"',tpz='"+Replace(String(t->tpz),",",".")+"',ttp='"+t->ttp+"',tsht='"+Replace(String(t->tsht),",",".")+"',base='mysql',UpdateUser='"+*t->LUser+"',UpdateDate=CURRENT_TIMESTAMP() where OpUUID='"+String(t->OpID)+"' and prof='"+t->_prof+"' and rr='"+t->_rr+"'");
        if (effect){t->action="no";}else{return effect;} // ������ ���������� ������� �� ���������
        }
    }
//������� �����
//���� ������
for (lnk   t=r->Get_First();t;t=t->next)
    {// ������� ��������� ��� del ����� ���������� ��� ins������� �������� ��������� ��� upd
    if (t->action=="ins"){ins=ins+"('"+String(t->OpID)+"','"+Replace(String(t->ksht),",",".")+"','"+t->_prof+"','"+t->krop+"','"+t->_rr+"','"+String(t->kolod)+"','"+t->en+"','"+t->kts+"','"+t->kvn+"','"+Replace(String(t->tpz),",",".")+"','"+t->ttp+"','"+Replace(String(t->tsht),",",".")+"','"+*(t->LUser)+"','"+*(t->LUser)+"',CURRENT_TIMESTAMP(),CURRENT_TIMESTAMP()),";}
    }
if (ins!="")
    {
    ins.Delete(ins.Length(),1);
    effect=r->DB->SendCommand("insert into technologic.operation_norms (OpUUID,ksht,prof,krop,rr,kolod,EN,kts,kvn,tpz,ttp,tsht,CreateUser,UpdateUser,CreateDate,UpdateDate)values"+ins);
    if (effect)
        { //������� ���������� ������
        for (lnk  t=r->Get_First();t;t=t->next)
            {
            if (t->action=="ins"){t->action="no";}
            }
        }else
        {
        return effect;
        }
    }
return effect;
}
void NrmRow::ChangeOpID    (unsigned __int64 _OpID,lnk &r,bool no_del)
{
lnk Item=Get_First();
lnk Last_Item=0;
while (Item)
    {
    Last_Item=Item;
    if (Item->action!="del")
        {//������  ��
        if (Item->OpID!=_OpID)
            {
            Item->OpID=_OpID;
            Item->action="ins";
            }
        Item=Item->next;
        }else
        {//�������� ���������� �� ��������
        if (no_del)
            {
            if (Item->next)
                {
                Item=Item->next;
                delete Item->prev;
                }else
                {
                if (Item->prev)
                    {
                    Item=Item->prev;
                    delete Item->next;
                    }else
                    {
                    delete Item;
                    Item=0;
                    Last_Item=0;
                    }
                }
            }
        }
    }
if (Last_Item)//������� ��������� �� ������ �������
    {
    r=Last_Item->Get_First();
    }
    else
    {
    r=0;
    }
}

void NrmRow::Push_Back_Deleted (void)
{
int i=0,count=Count(),ps=count;
lnk item=Get_First();
while (i<count)
    {// ������� �� ������� ��������� ��� ����������
    lnk node=item->operator [](i);
    if (node->action=="del")
        {//����� ������� ����� ���������� �� ���������� ������
        int c=1;
        lnk snod=node;
        while (snod->next&&snod->next->action=="del")
            {
            snod=snod->next;
            c++;
            }
        node->Move_items(node->ofset,c,ps);
        count-=c;
        }else
        {
        i++;
        }
    }
}
bool NrmRow::Need_Save(void)
{
bool Need_Save=false;
for (lnk i=Get_First(); i&&!Need_Save; i=i->Get_Next())
    {
    if (i->action!="no")
        {
        Need_Save=true;
        }
    }
return Need_Save;
}
