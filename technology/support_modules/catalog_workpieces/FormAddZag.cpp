//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "FormAddZag.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormAddZagCode *FormAddZagCode;
//---------------------------------------------------------------------------
__fastcall TFormAddZagCode::TFormAddZagCode(TComponent* Owner,cSQL *db, String parentID, bool edit)
	: TForm(Owner),DB(db), pID(parentID), editZag(edit)
{
	eCode->Text = pID;

	cbUse->Items->Clear();
	int firstItemID = 0;

	if(pID.Length() > 2)
	{
		TADOQuery *rez=DB->SendSQL("select * from `billets`.`vz_groups`");
		if (rez&&rez->RecordCount)
		{
			for (rez->First(); !rez->Eof; rez->Next())
			{
				cbUse->Items->AddObject(rez->FieldByName("name")->Value,(TObject *)rez->FieldByName("vz_grp_id")->Value.operator int());
			}
		}

		delete rez;
	}
	else
	{
		cbUse->Items->AddObject("", 0);
    }

	if(!editZag)
	{
		if(cbUse->Items->Count > 0) cbUse->ItemIndex = 0;
	}
	else
	{
		TADOQuery *rez=DB->SendSQL("select `name`, `parent`, `vz_grp_id` from `billets`.`vz_tree` where `kod`='" + pID + "'");
		if (rez&&rez->RecordCount)
		{
			rez->First();

			eName->Text = rez->FieldByName("name")->Value;
			lastpID = pID;
			pID = rez->FieldByName("parent")->Value;
			if(SameText(pID, "0")) pID = "";
			if(cbUse->Items->Count > 0) cbUse->ItemIndex = rez->FieldByName("vz_grp_id")->Value - 1;
			if(cbUse->ItemIndex < 0) cbUse->ItemIndex = 0;
		}

		delete rez;
    }
}
//---------------------------------------------------------------------------

void __fastcall TFormAddZagCode::bOkClick(TObject *Sender)
{
    ModalResult=mrNone;

	if((eCode->Text != "") && (eName->Text != ""))
	{
		if((eCode->Text.Length() == pID.Length()+1) && (SameText(eCode->Text.SubString(0, pID.Length()), pID)))
		{
			if(!editZag)
			{
				if(DB->SendCommand("insert into `billets`.`vz_tree` (`kod`, `name`, `parent`, `vz_grp_id`) values('" + eCode->Text + "', '" + eName->Text + "', '" + pID + "', '" + IntToStr((int)cbUse->Items->Objects[cbUse->ItemIndex]) + "')"))
				{
					ModalResult=mrOk;
				}
				else
				{
					ShowMessage("Не удалось добавить данные в базу");
				}
			}
			else
			{
				if(DB->SendCommand("update `billets`.`vz_tree` set `kod`='" + eCode->Text + "', `name`='" + eName->Text + "', `vz_grp_id`='" + IntToStr((int)cbUse->Items->Objects[cbUse->ItemIndex]) + "' where `kod`='" + lastpID + "'"))
				{
					if(lastpID.Length() < 3)
					{
						if(DB->SendCommand("call `billets`.ZagUpdateInner(" + lastpID + ", " + eCode->Text + ")"))
						{
                            ModalResult=mrOk;
                        }
						else
						{
							ShowMessage("Не удалось обновить вложенные данные в базе");
						}
					}
					else
					{
						ModalResult=mrOk;
					}
				}
				else
				{
					ShowMessage("Не удалось обновить данные в базе");
				}
            }
		}
		else
		{
			ShowMessage("Неверный код заготовки");
		}
	}
	else
	{
		ShowMessage("Не все поля заполнены");
	}
}
//---------------------------------------------------------------------------

