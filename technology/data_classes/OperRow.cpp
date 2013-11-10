#pragma hdrstop
#include "OperRow.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
	 OperRow::OperRow(cSQL *db,const String &_LUser,const unsigned __int64 &_OpID,const String &_action,
						const int &_id,	const int &_idtar,
						const int &_id_cntrl,
						const String &_ceh,		const String &_uch,
						const String &_opr,		const String &_oboID,
						const String &_OboName,
						const String &_OprName,	const String &_OprKod,
						const String &_Strop,	const String &_tara,
						const String &_control,	const String &_Instruct,
						const String  &_CreateUser,
						const String  &_UpdateUser,
						const TDateTime  &_CreateDate,
						const TDateTime  &_UpdateDate,
						lnk _prev):DB(db),prev(0),next(0),ofset(0),nrm(0),perex(0),instrum(0)
{
count++;
action=_action;

LUser=&_LUser;
id=_id;
OpID=_OpID;
idtar=_idtar;
id_cntrl=_id_cntrl;

ceh=_ceh;
uch=_uch;
opr=_opr;
oboID=_oboID;

OboName=_OboName;
OprName=_OprName;	
OprKod=_OprKod;
	
Strop=_Strop;
tara=_tara;
control=_control;
Instruct=_Instruct;

CreateUser=_CreateUser;
UpdateUser=_UpdateUser;
CreateDate=_CreateDate;
UpdateDate=_UpdateDate;
//�������� ������ �� �� �� ��������
Load_Oper_Data();
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
if (prev)
	{
	if (prev->opr.ToInt()>=opr.ToIntDef(10))
		{
		prev->Refresh_opr();
		}
	}else
	{
	if (opr.Trim()=="")
		{
		opr="010";
		}
	}
Upd_Ofset();
}
	 OperRow::OperRow(	cSQL *db,const String &_LUser,const unsigned __int64 &_OpID,
						const int &_id,	const int &_idtar,const String &_action,
						const int &_id_cntrl,
						const String &_ceh,		const String &_uch,
						const String &_opr,		const String &_oboID,
						const String &_OboName,
						const String &_OprName,	const String &_OprKod,
						const String &_Strop,	const String &_tara,
						const String &_control,	const String &_Instruct,
						const String  &_CreateUser,
						const String  &_UpdateUser,
						const TDateTime  &_CreateDate,
						const TDateTime  &_UpdateDate,
						lnk _prev,
						const NrmRow  	 *_nrm,
						const PerexRow 	 *_perex,
						const InstrumRow *_instrum
						):DB(db),prev(0),next(0),ofset(0),nrm(0),perex(0),instrum(0)
{
count++;
action=_action;

LUser=&_LUser;
id=_id;
OpID=_OpID;
idtar=_idtar;
id_cntrl=_id_cntrl;

ceh=_ceh;
uch=_uch;
opr=_opr;
oboID=_oboID;

OboName=_OboName;
OprName=_OprName;	
OprKod=_OprKod;

Strop=_Strop;
tara=_tara;
control=_control;
Instruct=_Instruct;

CreateUser=_CreateUser;
UpdateUser=_UpdateUser;
CreateDate=_CreateDate;
UpdateDate=_UpdateDate;
 //����������� ������ �� ��������
if (_nrm)nrm=new NrmRow(*_nrm);
if (_perex)perex=new PerexRow(*_perex);
if (_instrum)instrum=new	InstrumRow(*_instrum);
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
	 OperRow::OperRow(const OperRow &r):DB(r.DB),prev(0),next(0),ofset(0),nrm(0),perex(0),instrum(0)

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

LUser=first->LUser;
id=first->id;
OpID=first->OpID;
idtar=first->idtar;
id_cntrl=first->id_cntrl;

ceh=first->ceh;
uch=first->uch;
opr=first->opr;
oboID=first->oboID;

OboName=first->OboName;	
OprName=first->OprName;
OprKod=first->OprKod;

Strop=first->Strop;
Instruct=first->Instruct;

CreateUser=first->CreateUser;
UpdateUser=first->UpdateUser;
CreateDate=first->CreateDate;
UpdateDate=first->UpdateDate;
//����������� ������� ������
if (first->nrm)		{nrm=new NrmRow(*first->nrm);}else{nrm=0;}
if (first->perex)	{perex=new PerexRow(*first->perex);}else{perex=0;}
if (first->instrum)	{instrum=new InstrumRow(*first->instrum);}else{instrum=0;}
 //������ �������� ����
ofset=0;
c_lnk t=first->next;
lnk n=this;
while (t)
	{//���� ����������� ������� ������ // ����������.
	n=new OperRow(	t->DB,*t->LUser,t->OpID,
					t->id,t->idtar,t->action,t->id_cntrl,
					t->ceh,		t->uch,
					t->opr,		t->oboID,
					t->OboName,
					t->OprName,	t->OprKod,
					t->Strop,	t->tara,
					t->control,	t->Instruct,
					t->CreateUser,
					t->UpdateUser,
					t->CreateDate,
					t->UpdateDate,
					n,
					t->nrm,
					t->perex,
					t->instrum
					);
	t=t->next;
	}
}
	 OperRow::~OperRow()
{
// �������� ��������� �������
if (nrm)
	{
	nrm=nrm->Get_Last();//�������� � ����� � ������ ������� ����� ���������� �� ��������������� �������� �������
	while (nrm)
		{
		if (nrm->Get_Next())
			{
			delete nrm->Get_Next();
			nrm->Set_Next(0);
			}
		nrm=nrm->Get_Prev();
		}
	}
if (perex)
	{
	perex=perex->Get_Last();
	while (perex)
		{
		if (perex->Get_Next())
			{
			delete perex->Get_Next();
			perex->Set_Next(0);
			}
		perex=perex->Get_Prev();
		}
	}
if (instrum)
	{
	instrum=instrum->Get_Last();
	while (instrum)
		{
		if (instrum->Get_Next())
			{
			delete instrum->Get_Next();
			instrum->Set_Next(0);
			}
		instrum=instrum->Get_Prev();
		}
	}
// ������� ����� �� �������

if (next)
	{
	next->prev=prev;
	next->Upd_Ofset();
	}      
if (prev)
	{
	prev->next=next;
	prev->Refresh_opr();//��������������� ��������� ��������
	}
count--;
}

void 		OperRow::Upd_Ofset	(void)
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
void 		OperRow::Refresh_opr (void)
{
lnk item=this;
int n=10; //��� ���������
while (item->next)
	{
	if (item->next->action!="del")
		{
		// ��������� �������������
		int curr_opr=item->opr.ToIntDef(10); //������� ������� ����� ��������
		int tmp_opr=0;
		int next_opr=item->next->opr.ToIntDef(10); //������� ��������� ����� ��������
		n=10;  //������������� ��� � 10                1
		if (!(next_opr%100))
			{
			n=100;    //������������� ��� � 100
			}
		tmp_opr=curr_opr/n; //����������� �������� ������
		tmp_opr=tmp_opr*n;
		if (next_opr%10)          //�������� �� ��������� �� 0
			{
			if (curr_opr%10)
				{
				next_opr=tmp_opr+n+next_opr%10; //�������� �� ����� � ����� n � ����������� �� ������� �� �������
				}else
				{
				next_opr=tmp_opr+next_opr%10; //�������� �� ����� � ����� n � ����������� �� ������� �� �������
				}
			}else
			{
			next_opr=tmp_opr+n;   //��������  �� ����� � ����� n ��������� �����������
			}
		item->next->opr=(String)next_opr;
		while (item->next->opr.Length()<3)
			{
			item->next->opr="0"+item->next->opr;
			}
		if (item->next->action!="ins"){item->next->action="upd";}
		}
	item=item->next;
	}
}
int  		OperRow::Count 		(void)
{
lnk curr=this;
while (curr->next)
	{
	curr=curr->next;
	}
return curr->ofset+1;
}

OperRow* 	OperRow::Insert_line	(int pos,lnk line_item)
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
			tmp->id=section->id;
			tmp->OpID=0;
			tmp->LUser=section->LUser;   //������ ����� �� ������������ �� ����������
			tmp->action="ins";
			// ������ ��������������� � ��������� ��������
			if (tmp->nrm) 		{tmp->nrm->ChangeOpID(tmp->OpID,tmp->nrm,true);}
			if (tmp->perex) 	{tmp->perex->ChangeOpID(tmp->OpID,tmp->perex,true);}
			if (tmp->instrum) 	{tmp->instrum->ChangeOpID(tmp->OpID,tmp->instrum,true);}
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
	if (pos)
		{
		first_item->operator [](pos-1)->Refresh_opr();
		}else
		{
		first_item->Refresh_opr();
		}
	first_item->Upd_Ofset();
	}
return first_item;
}

OperRow* 	OperRow::Copy_subline	(int pos,int _count)
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
		lnk ret=new OperRow(	node->DB,*node->LUser,node->OpID,
								node->id,node->idtar,node->action,node->id_cntrl,
								node->ceh,		node->uch,
								node->opr,		node->oboID,
								node->OboName,
								node->OprName,	node->OprKod,
								node->Strop,    node->tara,
								node->control,	node->Instruct,
								node->CreateUser,
								node->UpdateUser,
								node->CreateDate,
								node->UpdateDate,
								0,
								node->nrm,
								node->perex,
								node->instrum
								);		
		for (int i=1; i<_count&&node->next; i++)
			{//�������� ��������� ����� �������
			node=node->next;
			if (node->action!="del")
				{//���������� ������ � ������ ���� ���� �� ������������ ��� ��������
				ret=new OperRow(node->DB,*node->LUser,node->OpID,
								node->id,node->idtar,node->action,node->id_cntrl,
								node->ceh,		node->uch,
								node->opr,		node->oboID,
								node->OboName,
								node->OprName,	node->OprKod,
								node->Strop,    node->tara,
								node->control,	node->Instruct,
								node->CreateUser,
								node->UpdateUser,
								node->CreateDate,
								node->UpdateDate,
								ret,
								node->nrm,
								node->perex,
								node->instrum
								);								
				}
			}
		return ret->Get_First();	
		}
	}
return 0;
}  
void		OperRow::Del_subline 	(lnk &r,int pos,int _count)
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
void		OperRow::Move_items	(int pos,int _count,int new_pos)
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
		Get_First()->opr="010";
		Get_First()->Refresh_opr();
		Get_First()->Upd_Ofset();
		}
	}
}

OperRow * 	OperRow::Get_First	(void)
{
lnk t=this;
while (t->prev)
	{
	t=t->prev;
	}
return t;
}
OperRow *	OperRow::Get_Last	(void)
{
lnk t=this;
while (t->next)
	{
	t=t->next;
	}
return t;
}
OperRow *  	OperRow::operator [](const unsigned int &r)
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


bool OperRow::SetValues(const int &_idtar,
						const int &_id_cntrl,
						const String &_ceh,		const String &_uch,
						const String &_opr,		const String &_oboID,
						const String &_OboName,
						const String &_OprName,	const String &_OprKod,
						const String &_Strop,	const String &_tara,
						const String &_control,	const String &_Instruct)
{
if (action=="del"){return false;}
if (_idtar!=idtar||_id_cntrl!=id_cntrl||_ceh!=ceh||_uch!=uch||_opr!=opr||_oboID!=oboID||_OboName!=OboName||
	_OprName!=OprName||_OprKod!=OprKod||_Strop!=Strop||_tara!=tara||_control!=control||_Instruct!=Instruct)
	{
	if (_idtar!=0||_id_cntrl!=0||_ceh!=""||_uch!=""||
			_opr!=""||_oboID!=""||_OboName!=""||_OprName!=""||
			_OprKod!=""||_Strop!=""||_tara!=""||_control!=""||_Instruct!="")
		{//������
		//������ ������ �� ������������ ���� ���������. ���������� ����� ���� ������ ������� ���� �� ��� ��������� �� �������� �� ������
		ceh=_ceh;
		uch=_uch;
		if (opr!=_opr)
			{
			if (prev)
				{
				if (prev->opr.ToInt()>_opr.ToIntDef(10))
					{
					prev->Refresh_opr();
					}else
					{
                    opr=_opr;
					Refresh_opr();
					}
				}else
				{
				if (_opr.Trim()=="")
					{
					opr="010";
					}else
					{
					opr=_opr;
					}
				Refresh_opr();
				}
			}
		oboID=_oboID;
			
		idtar=_idtar;
		control=_control;
		tara=_tara;
		id_cntrl=_id_cntrl;
		OboName=_OboName;
		OprName=_OprName;
		OprKod=_OprKod;
		Strop=_Strop;
		Instruct=_Instruct;
		if (action!="ins"){action="upd";}
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
bool OperRow::SaveData	(lnk &r)
{

bool effect=true;
String del="",ins="";
//�������� �����
//���� ������
for (lnk   t=Get_Last();t&&t->action=="del";t=t->prev)
	{// ������� ��������� ��� del ������� �������� ��������� ��� upd � ins ������������ �� �������� ���������� �� ������ ���� ��� ������ ����
	del=del+String(t->OpID)+",";
	}
if (del!="")
	{
	del.Delete(del.Length(),1);
	del="("+del+")";
	effect=r->DB->SendCommand("delete from technologic.operation_list where OpUUID in "+del);
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

for (lnk  t=r->Get_First();t;t=t->next)
	{
	String oboid="Null";
	if (t->oboID.Length())
		{
		oboid="'"+t->oboID+"'";
		}
	String sql="";  unsigned __int64 ID=0;
	if (t->action=="upd")
		{//���������� �����
		sql="update technologic.operation_list set id='"+String(t->id)+"',cex='"+t->ceh+"',utch='"+t->uch+"',opr='"+t->opr
					+"',oprid='"+t->OprKod+"',oboID="+oboid+",ioht='"+t->Instruct+"',stro='"+t->Strop+"',ktar='"+String(t->idtar)+"',ok69='"
					+String(t->id_cntrl)+"',base='mysql',UpdateUser='"+*LUser+"',UpdateDate=CURRENT_TIMESTAMP() where OpUUID='"
					+String(t->OpID)+"'";
		}
	if (t->action=="ins")
		{//������� �����
		TADOQuery *rez=r->DB->SendSQL("call technologic.Get_New_OPUUID()");
		if (rez&&rez->RecordCount)
			{//������ ������
			ID=rez->FieldByName("OpUUID")->Value.operator __int64();
			sql="insert into technologic.operation_list (id,OpUUID,cex,utch,opr,oprid,oboID,ioht,stro,ktar,ok69,CreateUser,UpdateUser,CreateDate,UpdateDate)values('"+String(t->id)+"','"+String(ID)+"','"+t->ceh+"','"+t->uch+"','"+t->opr+"','"+t->OprKod+"',"+oboid+",'"+t->Instruct+"','"+t->Strop+"','"+String(t->idtar)+"','"+String(t->id_cntrl)+"','"+*LUser+"','"+*LUser+"',CURRENT_TIMESTAMP(),CURRENT_TIMESTAMP())";
			}
		delete rez;
		}
	if (sql!="")
		{
		effect=r->DB->SendCommand(sql);
		if (effect&&t->action=="ins")
			{//���������� �� ������� � ��������� �������� � ������� �������� � �������������� ��������
			t->OpID=ID;
			if (t->nrm) 	{t->nrm->ChangeOpID(ID,t->nrm);}
			if (t->perex) 	{t->perex->ChangeOpID(ID,t->perex);}
			if (t->instrum) {t->instrum->ChangeOpID(ID,t->instrum);}
			}
		}
	if (t->nrm) 	{effect=effect*t->nrm->SaveData(t->nrm);}
	if (t->perex) 	{effect=effect*t->perex->SaveData(t->perex);}
	if (t->instrum) {effect=effect*t->instrum->SaveData(t->instrum);}

	if (effect){t->action="no"; /* � ��������� ������� ����������*/ }else{return effect;} // ������ ���������� ������� �� ���������
	}
return effect;
}
void OperRow::UpdID	(int _id,lnk &r,bool no_del)
{
lnk Item=Get_First();
lnk Last_Item=0;
while (Item)
	{
	Last_Item=Item;
	if (Item->action!="del")
		{//������  ��
		if (Item->id!=_id)
			{
			Item->id=_id;
			Item->OpID=0;
			Item->action="ins";
			if (Item->nrm) {Item->nrm->ChangeOpID(Item->OpID,Item->nrm,no_del);}
			if (Item->perex) {Item->perex->ChangeOpID(Item->OpID,Item->perex,no_del);}
			if (Item->instrum) {Item->instrum->ChangeOpID(Item->OpID,Item->instrum,no_del);}
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

void OperRow::Push_Back_Deleted (void)
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
void OperRow::Load_Oper_Data (void)
{
if (OpID)
	{//�������� �� ������� �������������� �������� ���� ��� ��� �� � ������ �� ���� �� �������
	//�������� ���������
	String sql="Call technologic.GetPerexods("+String(OpID)+")";
	TADOQuery *rez=DB->SendSQL(sql);
	if (rez&&rez->RecordCount)
		{
		for (rez->First(); !rez->Eof; rez->Next())
			{
			perex=new PerexRow (DB,OpID,
								rez->FieldByName("strk")->Value.operator int(),
								rez->FieldByName("tpe")->Value.operator UnicodeString(),
								perex);
			}
		}else{perex=0;}
	delete rez;
	rez=0;
	//�������� ������������
	sql="Call technologic.GetInstrum("+String(OpID)+")";
	rez=DB->SendSQL(sql);
	if (rez&&rez->RecordCount)
		{
		for (rez->First(); !rez->Eof; rez->Next())
			{
			instrum=new InstrumRow(	DB,OpID,
									rez->FieldByName("strk")->Value.operator int(),
									rez->FieldByName("koin")->Value.operator UnicodeString(),
									rez->FieldByName("nain")->Value.operator UnicodeString(),
									instrum);
			}
		}else{instrum=0;}
	delete rez;
	rez=0;
	//�������� ����	
	sql="Call technologic.GetNorms("+String(OpID)+")";
	rez=DB->SendSQL(sql);
	if (rez&&rez->RecordCount)
		{
		for (rez->First(); !rez->Eof; rez->Next())
			{
			nrm=new NrmRow(	DB,*LUser,OpID,"no",
							rez->FieldByName("kolod")->Value.operator int(),
							rez->FieldByName("prof")->Value.operator UnicodeString(),
							rez->FieldByName("krop")->Value.operator UnicodeString(),
							rez->FieldByName("rr")->Value.operator UnicodeString(),
							rez->FieldByName("en")->Value.operator UnicodeString(),
							rez->FieldByName("kts")->Value.operator UnicodeString(),
							rez->FieldByName("kvn")->Value.operator UnicodeString(),
							rez->FieldByName("ttp")->Value.operator UnicodeString(),
							rez->FieldByName("ksht")->Value.operator double(),
							rez->FieldByName("tpz")->Value.operator double(),
							rez->FieldByName("tsht")->Value.operator double(),
							rez->FieldByName("CreateUser")->Value.operator UnicodeString(),
							rez->FieldByName("UpdateUser")->Value.operator UnicodeString(),
							rez->FieldByName("CreateDate")->Value.operator TDateTime(),
							rez->FieldByName("UpdateDate")->Value.operator TDateTime(),
							nrm);
			}
		}else{nrm=0;}
	delete rez;
	rez=0;
	}
}
bool OperRow::Need_Save(void)
{
bool Need_Save=false;
for (lnk i=Get_First(); i&&!Need_Save; i=i->Get_Next())
	{
	if (i->action=="no")
		{
	 	bool need_save_per=false,need_save_nrm=false,need_save_instr=false;
		if (i->perex)
			{
			need_save_per=i->perex->Need_Save();
			}
		if (i->nrm)
			{
			need_save_nrm=i->nrm->Need_Save();
			}
		if (i->instrum)
			{
			need_save_instr=i->instrum->Need_Save();
			}
		if (need_save_per||need_save_nrm||need_save_instr)
			{
			Need_Save=true;
			}
		}else
		{
		Need_Save=true;
		}
	}
return Need_Save;
}
bool OperRow::Can_Save(String &msg)
{
bool result=true;
for (OperRow* i=Get_First(); i; i=i->Get_Next())
	{
	if (i->action!="del")
		{
		if (!i->oboID.Length())
			{
			result=result*false;
			msg=msg+"\n�������� ��� ������������ � ������ "+String(i->ofset+1);
			}
		if (!i->OprKod.Length())
			{
			result=result*false;
			msg=msg+"\n��������� �������� � ������ "+String(i->ofset+1);
			}
		}
	}
return result;
}
