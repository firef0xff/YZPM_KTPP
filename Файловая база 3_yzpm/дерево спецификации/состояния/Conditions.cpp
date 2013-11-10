
#include <vcl.h>
#pragma hdrstop

#include "Conditions.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"


__fastcall TCond::TCond(TComponent* Owner,TTreeView &Tree,
						const bool &_MassAction,cSQL *db,IconsData *_IcoData,const int &User)
	: TForm(Owner),MassAction(_MassAction),LUser(User)
{
DB=db;
IcoData=_IcoData;
TV->StateImages=IcoData->GetStateList();
TV->Images=IcoData->GetImgList();

IDS="";
CRowData *row=0;
Obd *bag=0;
TreeRow *Row=0;
TTreeNode *node=0;

String ids="";
String sql;
TADOQuery *rez=0;

if (_MassAction)
	{
	RG2->Enabled=true;
	for (unsigned int i=0; i<Tree.SelectionCount; i++)
		{
		bag=(Obd *)Tree.Selections[i]->Data;
		if (bag&&bag->TrueClassName()=="TreeRow")
			{
			Row=(TreeRow*)bag;
			ids=ids+String(Row->Get_ID())+",";// собрать все выделенные ид деталей и узлов
			}
		}
	ids.Delete(ids.Length(),1);  //-- переменную сделать общекласовой (потребуется при массовых действиях)
	IDS=ids;
	sql="Call constructions.GetTreeConditions('"+ids+"','"+LUser+"')";
	rez=DB->SendSQL(sql);
	if (rez&&rez->RecordCount)     //  получить возможные смены, там где (GetTreeConditions)
		{                          //  значений нет оставить принятие решения при нажатии на кнопку смены
		rez->First();
		while (!rez->Eof)
			{
			int id,CurrState,NextState,PrevState;
			String text,CurrStateName,NextStateName,PrevStateName;
			bool Accept,Arhive,NextAccept,PrevAccept;

			CurrState=rez->FieldByName("CurrState")->Value;
			CurrStateName=rez->FieldByName("CurrName")->Value;
			Accept=true;
			Arhive=rez->FieldByName("Arhive")->Value;
			NextState=rez->FieldByName("NextState")->Value;
			NextStateName=rez->FieldByName("NextName")->Value;
			NextAccept=rez->FieldByName("NextAccept")->Value;
			PrevState=rez->FieldByName("PrevState")->Value;
			PrevStateName=rez->FieldByName("PrevName")->Value;
			PrevAccept=rez->FieldByName("PrevAccept")->Value;
			id=-1;
			text="";

			row=new CRowData(MassAction,id,CurrState,NextState,PrevState,
							text,CurrStateName,NextStateName,PrevStateName,
							Accept,Arhive,NextAccept,PrevAccept);

			node=TV->Items->AddObject(0,CurrStateName,row);
			node->ImageIndex=IcoData->GetInList(CurrState,Accept,3);
			node->SelectedIndex=node->ImageIndex;
			node->ExpandedImageIndex=node->ImageIndex;
			node->StateIndex=IcoData->GetInList(row->GetSelectedState(),Accept,0);
			rez->Next();
			}
		}
	delete rez;
	rez=0;
	}else
	{
	RG2->Enabled=false;
	for (unsigned int i=0; i<Tree.SelectionCount; i++)
		{
		bag=(Obd *)Tree.Selections[i]->Data;
		if (bag&&bag->TrueClassName()=="TreeRow")
		   	{
			Row=(TreeRow*)bag;
			if (Row->Get_Accept())
				{
				row=new CRowData(MassAction,Row->Get_ID(),Row->Get_state(),-1,-1,
								Row->Get_Text(),Row->Get_CondName(),"","",
								Row->Get_Accept(),Row->Get_Arhive(),false,false);
				node=TV->Items->AddObject(0,row->GetText(),row);
				node->ImageIndex=IcoData->GetInList(Row->Get_SpRazd(),true,1);
				node->SelectedIndex=node->ImageIndex;
				node->ExpandedImageIndex=node->ImageIndex;
				node->StateIndex=IcoData->GetInList(row->GetSelectedState(),row->GetSelectedAccept(),0);
				if (!ids.Pos(String(row->GetSelectedState())+","))
					{
					ids=ids+String(row->GetSelectedState())+","; // коллекционировать ид состояний,
					}
				}
			}
		}
	ids.Delete(ids.Length(),1);
	if (ids!="")
		{
		sql="Call constructions.GetAvailableConditions('"+ids+"','"+LUser+"')" ;
		rez=DB->SendSQL(sql);
		if (rez&&rez->RecordCount)     //  получить возможные смены, там где (GetAvailableConditions)
			{                          //  значений нет оставить принятие решения при нажатии на кнопку смены
			rez->First();
			while (!rez->Eof)
				{
				for (node=TV->Items->GetFirstNode();node; node=node->getNextSibling())
					{
					row=(CRowData*)node->Data;
					if (row->GetCurrState()==rez->FieldByName("CurrState")->Value)
						{
						row->SetNextState(rez->FieldByName("NextState")->Value,rez->FieldByName("NextName")->Value,rez->FieldByName("NextAccept")->Value);
						row->SetPrevState(rez->FieldByName("PrevState")->Value,rez->FieldByName("PrevName")->Value,rez->FieldByName("PrevAccept")->Value);
						}
					}
				rez->Next();
				}
			}
		delete rez;
		}
	}
}
void __fastcall TCond::FormShow(TObject *Sender)
{
SetFocus();
}
void __fastcall TCond::nextClick(TObject *Sender)
{
CRowData* row=0;
if (!RG1->ItemIndex)
	{
	for (TTreeNode *node=TV->Items->GetFirstNode();node; node=node->getNextSibling())
		{
		row=(CRowData*)node->Data;
		if (!row->TurnNextState())
			{
			if (row->GetArhive())
				{
				SelectNextState(row);
				}
			}
		node->StateIndex=IcoData->GetInList(row->GetSelectedState(),row->GetSelectedAccept(),0);
		}
	}else
	{
	for (unsigned int i=0; i<TV->SelectionCount; i++)
		{
		row=(CRowData*)TV->Selections[i]->Data;
		row->TurnNextState();
		if (!row->TurnNextState())
			{
			if (row->GetArhive())
				{
				SelectNextState(row);
				}
			}
		TV->Selections[i]->StateIndex=IcoData->GetInList(row->GetSelectedState(),row->GetSelectedAccept(),0);
		}
	}
TVClick(TV);
}
void __fastcall TCond::currentClick(TObject *Sender)
{
CRowData* row=0;
if (!RG1->ItemIndex)
	{
	for (TTreeNode *node=TV->Items->GetFirstNode();node; node=node->getNextSibling())
		{
		row=(CRowData*)node->Data;
		row->TurnCurrState();
		 node->StateIndex=IcoData->GetInList(row->GetSelectedState(),row->GetSelectedAccept(),0);
		}
	}else
	{
	for (unsigned int i=0; i<TV->SelectionCount; i++)
		{
		row=(CRowData*)TV->Selections[i]->Data;
		row->TurnCurrState();
		TV->Selections[i]->StateIndex=IcoData->GetInList(row->GetSelectedState(),row->GetSelectedAccept(),0);
		}
	}
TVClick(TV);
}
void __fastcall TCond::prevClick(TObject *Sender)
{
CRowData* row=0;
if (!RG1->ItemIndex)
	{
	for (TTreeNode *node=TV->Items->GetFirstNode();node; node=node->getNextSibling())
		{
		row=(CRowData*)node->Data;
		if (!row->TurnPrevState())
			{
			row->TurnCurrState();
			}
		 node->StateIndex=IcoData->GetInList(row->GetSelectedState(),row->GetSelectedAccept(),0);
		}
	}else
	{
	for (unsigned int i=0; i<TV->SelectionCount; i++)
		{
		row=(CRowData*)TV->Selections[i]->Data;
		if (!row->TurnPrevState())
			{
			row->TurnCurrState();
			}
		TV->Selections[i]->StateIndex=IcoData->GetInList(row->GetSelectedState(),row->GetSelectedAccept(),0);
		}
	}
TVClick(TV);
}
void __fastcall TCond::BitBtn3Click(TObject *Sender)
{
//кнопка применить
if (!RG1->ItemIndex)
	{
	for (TTreeNode *node=TV->Items->GetFirstNode();node; node=node->getNextSibling())
		{
		ChangeCondition((CRowData*)node->Data);
		}
	}else
	{
	for (unsigned int i=0; i<TV->SelectionCount; i++)
		{
		ChangeCondition((CRowData*)TV->Selections[i]->Data);
		}
	}
if (MassAction)
	{
	DB->SendCommand("Call constructions.ChangeStates('"+IDS+"','0','0','"+IntToStr(RG2->ItemIndex+1)+"')");
	}
}
void  			TCond::SelectNextState(CRowData *row)
{
TStSelect *wnd=new TStSelect(this,DB,IcoData,row->GetSelectedState(),LUser);
CRowData *Row=0;
wnd->ShowModal();    //спросить куда отправить
if (wnd->ModalResult==mrOk)
	{
	for (TTreeNode *node=TV->Items->GetFirstNode(); node; node=node->GetNext())
		{
		if (!RG1->ItemIndex)
			{
			Row=(CRowData *)node->Data;
			if (Row->GetCurrState()==row->GetCurrState()&&Row->GetNextState()==-1)
				{
				Row->SetNextState(wnd->NextState,wnd->NextStateName,wnd->NextStateAccept);
				Row->TurnNextState();
				}
			}else
			{
			if (node->Selected)
				{
				Row=(CRowData *)node->Data;
				if (Row->GetCurrState()==row->GetCurrState()&&Row->GetNextState()==-1)
					{
					Row->SetNextState(wnd->NextState,wnd->NextStateName,wnd->NextStateAccept);
					Row->TurnNextState();
					}
				}
			}
		}
	}
delete wnd;
}
bool  			TCond::ChangeCondition(CRowData *row)
{
// сменить состояние на GetSelectedState  в зависимости от режима смены состояний
if (!row) {return false;}
//if (row->GetCurrState()==row->GetSelectedState()){return true;}
String sql="";
if (MassAction)
	{
	sql="Call constructions.ChangeStates('0','"+String(row->GetCurrState())+"','"+String(row->GetSelectedState())+"','0')";
	}else
	{
	sql="Call constructions.ChangeState("+String(row->GetID())+","+String(row->GetSelectedState())+")";
	}
if(sql.Length())
	{
	DB->SendCommand(sql);
	return true;
	}
return false;
}

void __fastcall TCond::TVMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
TTreeView *TView=(TTreeView *)Sender;
if (!TView->Items->Count||!TView->GetNodeAt(X,Y)) {return;}
if (Shift.ToInt()!=17&&Shift.ToInt()!=12&&Shift.ToInt()!=20&&Shift.ToInt()!=9)
{
TView->ClearSelection();
}
if (Shift.ToInt()!=12&&Shift.ToInt()!=9)
{
TView->Select(TView->GetNodeAt(X,Y),Shift);
TView->GetNodeAt(X,Y)->Focused=true;
}
TView->Repaint();
}

void __fastcall TCond::TVClick(TObject *Sender)
{
TTreeView *TView=(TTreeView *)Sender;
if (!TView->Items->Count||!TView->Selected) {return;}
CRowData *row;
row=(CRowData *)TView->Selected->Data;
if (row)
	{
	IMG->Picture->Bitmap=0;
	TImageList *ico=IcoData->GetStateList();
	ico->GetBitmap(IcoData->GetInList(row->GetSelectedState(),row->GetSelectedAccept(),0),IMG->Picture->Bitmap);
	CondName->Caption=row->GetSelectedStateName();
	}
}
//---------------------------------------------------------------------------

