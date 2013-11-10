//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Select_params_prod.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
__fastcall TSel_params_prod::TSel_params_prod(TComponent* Owner,const int &_LUser,cSQL *db)
	: TForm(Owner),LUser(_LUser),DB(db)
{
count++;
sortparams="";
dog_id=0;
//подразделение
TADOQuery *rez=DB->SendSQL("Call market.Get_podr_list('"+String(LUser)+"')");
if (rez&&rez->RecordCount)
	{
	for (rez->First(); !rez->Eof; rez->Next())
		{
		podr_list->Items->AddObject(rez->FieldByName("name")->Value,(TObject *)rez->FieldByName("id")->Value.operator int());
		}
	}
delete rez;
podr_list->ItemIndex=0;
}
__fastcall TSel_params_prod::~TSel_params_prod(void)
{
count--;
}
void __fastcall TSel_params_prod::Ka1cClick(TObject *Sender)
{
TContragents *wnd=new TContragents(this,LUser,DB);
wnd->ShowModal();
if (wnd->ModalResult==mrOk)
	{
	String _ka_name;
	wnd->Get_id(ka_id,_ka_name);
	ka_name->Text=_ka_name;
	}
delete wnd;
}
void __fastcall TSel_params_prod::OKClick(TObject *Sender)
{
String add=" and ";

if (b_dog_num->Checked)
	{
	/*if (sortparams=="")
		{
		sortparams="Where ";
		add=" ";
		}else
		{
		add=" and ";
		}  */
	if (dog_id)
		{
		sortparams=sortparams+add+"a.id=\""+String(dog_id)+"\"";
		}else
		{
		sortparams=sortparams+add+"(trim(concat(a.indication1,\" \",if (a.indication3!=\"\"or a.indication2!=0,if(a.indication3=\"\",CONCAT(\"15/\",YEAR(a.DogDate),\"/\",a.indication2),CONCAT(a.indication2,\"-\",a.indication3)),\"\"),\" \",a.indication4)) like \"%"+dog_num->Text.Trim()+"%\")";
		}
	}
if (b_podr->Checked)
	{
   /*	if (sortparams=="")
		{
		sortparams="Where ";
		add=" ";
		}else
		{
		add=" and ";
		}*/
	sortparams=sortparams+add+"(a.podrid=\""+String((int)podr_list->Items->Objects[podr_list->ItemIndex])+"\")";
	}

if (b_ka->Checked)
	{
   /*	if (sortparams=="")
		{
		sortparams="Where ";
		add=" ";
		}else
		{
		add=" and ";
		}     */
	sortparams=sortparams+add+"(a.contractor_id=\""+String(ka_id)+"\")";
	}
if (b_active->Checked)
	{
   /*	if (sortparams=="")
		{
		sortparams="Where ";
		add=" ";
		}else
		{
		add=" and ";
		}  */
	sortparams=sortparams+add+"(\""+Date().FormatString("yyyy-mm-dd")+"\" BETWEEN a.StartDate and a.EndDate)";
	}
if (zak->Checked)
	{
   /*	if (sortparams=="")
		{
		sortparams="Where ";
		add=" ";
		}else
		{
		add=" and ";
		}  */
	sortparams=sortparams+add+"( d.zakaz like \"%"+Zak_numb->Text+"%\")";
	}
if (name->Checked)
	{
   /*	if (sortparams=="")
		{
		sortparams="Where ";
		add=" ";
		}else
		{
		add=" and ";
		}  */
	sortparams=sortparams+add+"(d.name like \"%"+zak_name->Text+"%\")";
	}
}

void __fastcall TSel_params_prod::dog_selectClick(TObject *Sender)
{
TAgreements_select *wnd=new TAgreements_select(this,LUser,DB);
wnd->ShowModal();
if (wnd->ModalResult==mrOk)
	{
	String d_num="";
	wnd->Update_selected_dog(dog_id,d_num);
	dog_num->Text=d_num;
	dog_num->Tag=1;
	}
delete wnd;
}
void __fastcall TSel_params_prod::dog_numChange(TObject *Sender)
{
if (dog_num->Tag)
	{
	dog_id=0;
	dog_num->Tag=0;
	}
}
