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

//встраивание звена в цепь
if (_prev)
    {          //создается рядовой узел
    prev=_prev;
    // эффект встраивания в цепь
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

{// копировщик для копирования всей цепочки
count++;
//вычисление начала цепочки
c_lnk first=&r;
while (first->prev)
    {
    first=first->prev;
    }
//копирование данных
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

ofset=0;//создан головной узел
// воссоздание остальной цепочки
c_lnk t=first->next;
lnk n=this;
while (t)
    {//цыкл воссоздания цепочки данных // репликация.
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
lnk first_line_item=line_item->Get_First();  //получение указателя первого звена вставляемой цепочки
lnk first_item=Get_First();           //получение указателя первого звена текущей цепочки
if (first_line_item!=first_item)                 //проверка факта вставки цепочки самой в себя (закольцовывание). Чтобы исключить этот феномен
    {
    //выяснение позиции вставки
    int _count=this->Count();                 //получение количества звеньев в цепочке
    if (_count<pos)                          //проверка выхода позиции за пределы цепочки.
        {
        pos=_count;                         //установка позиции на последний элемент цепочки (произойдет достраивание в конец цепочки)
        }
    if (pos<0)                          //проверка выхода позиции за пределы цепочки.
        {
        pos=0;                         //установка позиции на первый элемент цепочки (произойдет встраивание в цепочку перед нулевым элементом)
        }
    lnk section=this->operator [](pos);
    lnk tmp=first_line_item;
    //сканирование и адаптация цепочки
    while (tmp)
        {
        if (tmp->action!="del")
            {
            tmp->OpID=section->OpID;
            tmp->LUser=section->LUser;//замена сылки на пользователя на актуальную
            tmp->action="ins";
            }else
            {
            delete tmp;
            }
        tmp=tmp->next;
        }
    lnk last_line_item=line_item->Get_Last();
    //сцепка цепочек
    if (_count!=pos)
        {  //сцепка к указанному узлу сзади
        first_line_item->prev=section->prev;
        if (section->prev)
            {
            section->prev->next=first_line_item;
            }
        section->prev=last_line_item;
        last_line_item->next=section;
        }else
        {  //сцепка к указанному узлу спереди
        last_line_item->next=section->next;
        if (section->next)
            {
            section->next->prev=last_line_item;
            }
        section->next=first_line_item;
        first_line_item->prev=section;
        }
    //переписывание позиций массива
    first_item=Get_First();
    first_item->Upd_Ofset();
    }
return first_item;
}
NrmRow *      NrmRow::Copy_subline    (int pos,int _count)
{    //копировать только элементы без пометки del
    //проверка позиции
int cnt=this->Count();
if (cnt>pos)
    {//поиск первого неудаляемого
    lnk node=this->operator [](pos);
    while (node&&node->action=="del"&&_count>0)
        {
        pos++;
        _count--;
        node=node->next;
        }    
    if (node&&_count>0)//проверка начальных условий не нулевой узел и не вышедше за пределы количество копируемых
        {// создание первого узла цепочки
        lnk ret=new NrmRow(    node->DB,*node->LUser,node->OpID,node->action,node->kolod,
                            node->_prof,node->krop,node->_rr,node->en,node->kts,node->kvn,
                            node->ttp,node->ksht,node->tpz,node->tsht,node->CreateUser,
                            node->UpdateUser,node->CreateDate,node->UpdateDate,0
                            );
        for (int i=1; i<_count&&node->next; i++)
            {//создание остальных узлов цепочки
            node=node->next;
            if (node->action!="del")
                {//копировать только в слечае если узел не предназначен для удаления
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
{//удалять только с пометкой ins остальным пометку del
    //проверка позиции
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
                {// рядовой механизм перехода
                node=node->next;
                delete node->prev;
                }else
                {
                if (node->prev)
                    {//нужен если цикл дойдет до последнего элемента который нужно удалить
                    node=node->prev;
                    delete node->next;
                    }else
                    {//если удаляется единственных элемент
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
        } // установка связи с базовым классом для обновления указателя за который прицеплена цепь
    if (r){r->Push_Back_Deleted();}
    }
}
void        NrmRow::Move_items    (int pos,int _count,int new_pos)
{
if (_count>0&&pos!=new_pos)
    {
    // получить указатель на гловной хвостовой элементы элемент
    lnk first_move_item=this->operator [](pos);
    lnk last_move_item=this->operator [](pos+_count-1);
    // получить указатель на итем перед позицией вставки с учетом количества перемещаемых объектов
    // сравнить текущую позицию с требуемой, и при необходимости провести коррекцию реальной позиции для вставки
    int real_ins_pos;
    if (new_pos>pos)
        {
        real_ins_pos=new_pos+_count;
        }else
        {//нет нужды к корректировке позиции...
        real_ins_pos=new_pos;
        }
    //коррекция реальной позиции переноса
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
    //проверка на перемещения конца цепочки в коонец цепочки
    if (section!=last_move_item)
        {
            //сцепка цепочек
            // сшить образовавшуюся дыру
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
        // выбор границ вставки
        if (count!=real_ins_pos)
            {  //сцепка перед указанным узлом
            before=section->prev;
            after=section;
            }else
            {  //сцепка после указанного узла
            before=section;
            after=section->next;
            }
        // вставить объекты
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
        //переписывание позиций массива
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
        {//замены
        //замена ключей
        if (_prof!=__prof||_rr!=__rr)
            {
            if (action=="ins")
                {// вслуче инсерта при замене ключа просто заменить всю информацию
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
                { //в случае наличия строки в базе ставим метку на удаление и создаем
                new NrmRow(DB,*LUser,OpID,"ins",_kolod,__prof,_krop,__rr,_en,_kts,_kvn,
                _ttp,_ksht,_tpz,_tsht,CreateUser,UpdateUser,CreateDate,UpdateDate,this);
                action="del";
                Push_Back_Deleted();
                }
            }else
            {//при не изменности ключей проверка на изменение данных
            if (kolod!=_kolod||krop!=_krop||
                en!=_en||kts!=_kts||kvn!=_kvn||ttp!=_ttp||
                ksht!=_ksht||tpz!=_tpz||tsht!=_tsht)
                {//  в случае если данные изменены замена данных
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
        {//удаления
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
//удаление строк
//сбор данных
for (lnk   t=Get_Last();t&&t->action=="del";t=t->prev)
    {// собрать коллекцию для del потом коллекциюя для insвтромым пробегом запустить все upd
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
    //установка отметки и удалениеиз цепочки удаленных строк
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
        return effect;//ошибка в запросе удаления
        }
    }
//обновление строк  // и установка отметки выполнения
for (lnk  t=r->Get_First();t;t=t->next)
    {// собрать коллекцию для del потом коллекциюя для insвтромым пробегом запустить все upd
    if (t->action=="upd")
        {
        effect=r->DB->SendCommand("update technologic.operation_norms set ksht='"+Replace(String(t->ksht),",",".")+"',krop='"+t->krop+"',kolod='"+String(t->kolod)+"',EN='"+t->en+"',kts='"+t->kts+"',kvn='"+t->kvn+"',tpz='"+Replace(String(t->tpz),",",".")+"',ttp='"+t->ttp+"',tsht='"+Replace(String(t->tsht),",",".")+"',base='mysql',UpdateUser='"+*t->LUser+"',UpdateDate=CURRENT_TIMESTAMP() where OpUUID='"+String(t->OpID)+"' and prof='"+t->_prof+"' and rr='"+t->_rr+"'");
        if (effect){t->action="no";}else{return effect;} // ошибка выполнения запроса на изменение
        }
    }
//вставка строк
//сбор данных
for (lnk   t=r->Get_First();t;t=t->next)
    {// собрать коллекцию для del потом коллекциюя для insвтромым пробегом запустить все upd
    if (t->action=="ins"){ins=ins+"('"+String(t->OpID)+"','"+Replace(String(t->ksht),",",".")+"','"+t->_prof+"','"+t->krop+"','"+t->_rr+"','"+String(t->kolod)+"','"+t->en+"','"+t->kts+"','"+t->kvn+"','"+Replace(String(t->tpz),",",".")+"','"+t->ttp+"','"+Replace(String(t->tsht),",",".")+"','"+*(t->LUser)+"','"+*(t->LUser)+"',CURRENT_TIMESTAMP(),CURRENT_TIMESTAMP()),";}
    }
if (ins!="")
    {
    ins.Delete(ins.Length(),1);
    effect=r->DB->SendCommand("insert into technologic.operation_norms (OpUUID,ksht,prof,krop,rr,kolod,EN,kts,kvn,tpz,ttp,tsht,CreateUser,UpdateUser,CreateDate,UpdateDate)values"+ins);
    if (effect)
        { //отметка выполнения встави
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
        {//замена  ид
        if (Item->OpID!=_OpID)
            {
            Item->OpID=_OpID;
            Item->action="ins";
            }
        Item=Item->next;
        }else
        {//удаление помеченных на удаление
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
if (Last_Item)//возврат указателя на начало цепочки
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
    {// переход по номерам элементов для нахлждения
    lnk node=item->operator [](i);
    if (node->action=="del")
        {//метка найдена нужно определить их количество подрят
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
