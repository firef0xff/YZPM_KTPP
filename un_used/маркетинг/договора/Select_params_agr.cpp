// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Select_params_agr.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

__fastcall TSel_params_agr::TSel_params_agr(TComponent *Owner,
	const int &_LUser, cSQL *db):TForm(Owner), LUser(_LUser), DB(db)
	{
	count++ ;
	cd_max->Date=Date();
	cd_min->Date=Date();
	sign_max->Date=Date();
	sign_min->Date=Date();
	sortparams="";
	// предмет договора
	predm_dog->Items->Clear();
	TADOQuery *rez=
		DB->SendSQL
		("select predm_dog from market.subject_of_the_agreement order by predm_dog");
	if(rez&&rez->RecordCount)
		{
		for(rez->First(); !rez->Eof; rez->Next())
			{
			predm_dog->Items->AddObject
				(rez->FieldByName("predm_dog")->Value, 0);
			}
		}
	delete rez;
	// подразделения
	predm_dog->ItemIndex= -1;
	podr_list->Items->Clear();
	rez=DB->SendSQL("Call market.Get_podr_list('"+String(LUser)+"')");
	if(rez&&rez->RecordCount)
		{
		for(rez->First(); !rez->Eof; rez->Next())
			{
			podr_list->Items->AddObject(rez->FieldByName("name")->Value,
				(TObject *)rez->FieldByName("id")->Value.operator int());
			}
		}
	delete rez;
	podr_list->ItemIndex=0;
	// список исполнителей для выбранного подразделения
	isp_list->Items->Clear();
	rez=DB->SendSQL("Call market.Get_isp_list_U('"+String(LUser)+"')");
	if(rez&&rez->RecordCount)
		{
		for(rez->First(); !rez->Eof; rez->Next())
			{
			isp_list->Items->AddObject(rez->FieldByName("LogIn")->Value,
				(TObject *)rez->FieldByName("LogID")->Value.operator int());
			}
		}
	isp_list->ItemIndex=isp_list->Items->IndexOfObject((TObject *)LUser);
	delete rez;
	}

__fastcall TSel_params_agr::~TSel_params_agr(void)
	{
	count-- ;
	}

void __fastcall TSel_params_agr::Ka1cClick(TObject *Sender)
	{
	TContragents *wnd=new TContragents(this, LUser, DB);
	wnd->ShowModal();
	if(wnd->ModalResult==mrOk)
		{
		String _ka_name;
		wnd->Get_id(ka_id, _ka_name);
		ka_name->Text=_ka_name;
		}
	delete wnd;
	}

void __fastcall TSel_params_agr::OKClick(TObject *Sender)
	{
	String add=" and ";
	if(b_type->Checked)
		{
		/* if (sortparams=="")
		 {
		 sortparams="Where ";
		 add=" ";
		 }else
		 {
		 add=" and ";
		 } */
		sortparams=sortparams+add+"(a.type='"+dog_type->Items->operator[]
			(dog_type->ItemIndex).SubString(1, 1)+"')";
		}
	if(b_dog_num->Checked)
		{
		/* if (sortparams=="")
		 {
		 sortparams="Where ";
		 add=" ";
		 }else
		 {
		 add=" and ";
		 } */
		sortparams=sortparams+add+
			"(trim(concat(a.indication1,' ',if (a.indication3!=''or a.indication2!=0,if(a.indication3='',CONCAT('15/',YEAR(a.DogDate),'/',a.indication2),CONCAT(a.indication2,'-',a.indication3)),''),' ',a.indication4)) like '%"+
			dog_num->Text.Trim()+"%')";
		}
	if(b_cd->Checked)
		{
		/* if (sortparams=="")
		 {
		 sortparams="Where ";
		 add=" ";
		 }else
		 {
		 add=" and ";
		 } */
		sortparams=sortparams+add+"(a.DogDate BETWEEN '"+
			cd_min->Date.FormatString("yyyy-mm-dd")+"' and '"+
			cd_max->Date.FormatString("yyyy-mm-dd")+"')";
		}
	if(b_sign_dt->Checked)
		{
		/* if (sortparams=="")
		 {
		 sortparams="Where ";
		 add=" ";
		 }else
		 {
		 add=" and ";
		 } */
		sortparams=sortparams+add+"(a.SignDate BETWEEN '"+
			sign_min->Date.FormatString("yyyy-mm-dd")+"' and '"+
			sign_max->Date.FormatString("yyyy-mm-dd")+"')";
		}
	if(b_summ->Checked)
		{
		/* if (sortparams=="")
		 {
		 sortparams="Where ";
		 add=" ";
		 }else
		 {
		 add=" and ";
		 } */
		sortparams=sortparams+add+"(a.Summ BETWEEN '"+summ_min->Text.Trim()+
			"' and '"+summ_max->Text.Trim()+"')";
		}
	if(b_podr->Checked)
		{
		/* if (sortparams=="")
		 {
		 sortparams="Where ";
		 add=" ";
		 }else
		 {
		 add=" and ";
		 } */
		sortparams=sortparams+add+"(a.podrid='"+
			String((int)podr_list->Items->Objects[podr_list->ItemIndex])+"')";
		}
	if(b_isp->Checked)
		{
		/* if (sortparams=="")
		 {
		 sortparams="Where ";
		 add=" ";
		 }else
		 {
		 add=" and ";
		 } */
		sortparams=sortparams+add+"(a.Isp='"+isp_list->Items->operator[]
			(isp_list->ItemIndex)+"')";
		}
	if(b_predm->Checked)
		{
		/* if (sortparams=="")
		 {
		 sortparams="Where ";
		 add=" ";
		 }else
		 {
		 add=" and ";
		 } */
		sortparams=sortparams+add+"(a.predm like'%"+predm_dog->Text.Trim
			()+"%')";
		}
	if(b_ka->Checked)
		{
		/* if (sortparams=="")
		 {
		 sortparams="Where ";
		 add=" ";
		 }else
		 {
		 add=" and ";
		 } */
		sortparams=sortparams+add+"(a.contractor_id='"+String(ka_id)+"')";
		}
	if(b_active->Checked)
		{
		/* if (sortparams=="")
		 {
		 sortparams="Where ";
		 add=" ";
		 }else
		 {
		 add=" and ";
		 } */
		sortparams=sortparams+add+"('"+Date().FormatString("yyyy-mm-dd")+
			"' BETWEEN a.StartDate and a.EndDate)";
		}
	TDateTime dt=0;
	switch(b_signed->ItemIndex)
		{
	case 1:
			{
			/* if (sortparams=="")
			 {
			 sortparams="Where ";
			 add=" ";
			 }else
			 {
			 add=" and ";
			 } */
			sortparams=sortparams+add+"(signdate='"+dt.FormatString
				("yyyy-mm-dd")+"')";
			break;
			}
	case 2:
			{
			/* if (sortparams=="")
			 {
			 sortparams="Where ";
			 add=" ";
			 }else
			 {
			 add=" and ";
			 } */
			sortparams=sortparams+add+"(signdate!='"+dt.FormatString
				("yyyy-mm-dd")+"')";
			break;
			}
	default:
		break;
		}
	}
