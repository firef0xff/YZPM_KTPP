#pragma hdrstop
#include "PerexRow.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
	 PerexRow::PerexRow(cSQL *db,const unsigned __int64 &_OpID,const int &_row,
						const String &_Text,lnk _prev):DB(db),prev(0),next(0),ofset(0)
{
count++;
OpID=_OpID;
row=_row;
Text=_Text;
//����������� ����� � ����
if (_prev)
	{  		//��������� ������� ����
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
if (row!=ofset+1)
	{
	action="upd";
	}else
	{
	action="no";
	}
if (!row)
	{
	action="ins";
	}
}
	 PerexRow::PerexRow(cSQL *db,const unsigned __int64 &_OpID,const String &_action, const int &_row,
						const String &_Text,
						lnk _prev):DB(db),prev(0),next(0),ofset(0)
{   //���������� �������
count++;
action=_action;
OpID=_OpID;
Text=_Text;
if (action=="ins")
	{
	row=0;
	}else
	{
	row=_row;
	}
//����������� ����� � ����
if (_prev)
	{  		//��������� ������� ����
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
	 PerexRow::PerexRow(const PerexRow &r):DB(r.DB),prev(0),next(0),ofset(0)

{// ���������� ��� ����������� ���� �������
count++;
//���������� ������ �������
c_lnk first=&r;
while (first->prev)
	{
	first=first->prev;
	}
//����������� ������
OpID=first->OpID;
Text=first->Text;
action=first->action;
//��������� ������ � ����������� �� ��������
if (action=="ins")
	{
	row=0;
	}else
	{
	row=first->row;
	}
 //������ �������� ����
ofset=0;
c_lnk t=first->next;
lnk n=this;
while (t)
	{//���� ����������� ������� ������ // ����������.
	n=new PerexRow(t->DB,t->OpID,t->action,t->row,t->Text,n);
	t=t->next;
	}
}
	 PerexRow::~PerexRow()
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

void 		PerexRow::Upd_Ofset		(void)
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
	if ((i->ofset+1)!=i->row&&i->action!="ins"&&i->action!="del") {i->action="upd";}
	}
}
int  		PerexRow::Count 		(void)
{
lnk curr=this;
while (curr->next)
	{
	curr=curr->next;
	}
return curr->ofset+1;
}

PerexRow* 	PerexRow::Insert_line	(int pos,lnk line_item)
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
			tmp->action="ins";
			tmp->row=0;
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
PerexRow* 	PerexRow::Copy_subline	(int pos,int _count)
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
		lnk ret=new PerexRow(node->DB,node->OpID,node->action,node->row,node->Text,0);	
		for (int i=1; i<_count&&node->next; i++)
			{//�������� ��������� ����� �������
			node=node->next;
			if (node->action!="del")
				{//���������� ������ � ������ ���� ���� �� ������������ ��� ��������
				ret=new PerexRow(node->DB,node->OpID,node->action,node->row,node->Text,ret);							
				}
			}
		return ret->Get_First();	
		}
	}
return 0;
}
void		PerexRow::Del_subline 	(lnk &r,int pos,int _count)
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
void		PerexRow::Move_items	(int pos,int _count,int new_pos)
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

PerexRow * 	PerexRow::Get_First	(void)
{
lnk t=this;
while (t->prev)
	{
	t=t->prev;
	}
return t;
}
PerexRow *	PerexRow::Get_Last	(void)
{
lnk t=this;
while (t->next)
	{
	t=t->next;
	}
return t;
}
PerexRow *  PerexRow::operator [](const unsigned int &r)
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


bool PerexRow::SetValues (const String &_Text)
{   
if (action=="del"){return false;}
if (_Text!="")
	{//������
	if (Text!=_Text||(ofset+1)!=row)
		{
		if (action!="ins"){action="upd";}
		Text=_Text;
		return true;
		}else
		{
		return false;
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
	return true;
	}
}
bool PerexRow::SaveData	(lnk &r)
{

bool effect=true;
String del="",ins="";
//�������� �����
//���� ������
for (lnk   t=Get_Last();t&&t->action=="del";t=t->prev)
	{// ������� ��������� ��� del ����� ���������� ��� ins������� �������� ��������� ��� upd
	if (del=="")
		{
		del="('0','0'),('"+String(t->OpID)+"','"+String(t->row)+"'),";
		}else
		{
		del=del+"('"+String(t->OpID)+"','"+String(t->row)+"'),";
		}
	}
if (del!="")
	{
	del.Delete(del.Length(),1);
	del="("+del+")";
	effect=r->DB->SendCommand("delete from technologic.perexod where (OpUUID,strk) in "+del);
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
		effect=r->DB->SendCommand("update technologic.perexod set strk='"+String(t->ofset+1)+"',tpe='"+ekran(t->Text)+"',base='mysql' where OpUUID='"+String(t->OpID)+"' and strk='"+String(t->row)+"' limit 1");
		if (effect){t->row=t->ofset+1;t->action="no";}else{return effect;} // ������ ���������� ������� �� ���������
		}
	}
//������� �����
//���� ������
for (lnk   t=r->Get_First();t;t=t->next)
	{// ������� ��������� ��� del ����� ���������� ��� ins������� �������� ��������� ��� upd
	if (t->action=="ins"){ins=ins+"('"+String(t->OpID)+"','"+String(t->ofset+1)+"','"+ekran(t->Text)+"'),";}
	}
if (ins!="")
	{
	ins.Delete(ins.Length(),1);
	effect=r->DB->SendCommand("insert into technologic.perexod (OpUUID,strk,tpe)values"+ins);
	if (effect)
		{ //������� ���������� ������
		for (lnk  t=r->Get_First();t;t=t->next)
			{
			if (t->action=="ins"){t->row=t->ofset+1;t->action="no";}
			}
		}else
		{
		return effect;
		}
	}
return effect;
}

void PerexRow::ChangeOpID	(unsigned __int64 _OpID,lnk &r,bool no_del)
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
void PerexRow::Push_Back_Deleted (void)
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
bool PerexRow::Need_Save(void)
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
