//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Mater_zam.h"
#include "main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

__fastcall TMat_zam::TMat_zam(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TMat_zam::BitBtn2Click(TObject *Sender)
{   /*
String sql="Update det_info set obm='"+new_mat->Text.UpperCase().Trim()+
"' where obm='"+old_mat->Text.UpperCase().Trim()+"'";
if (!Db->SendCommand(sql)){Form2->Error(0);return;}
sql="Update detinfo_new set obm='"+new_mat->Text.UpperCase().Trim()+
"' where obm='"+old_mat->Text.UpperCase().Trim()+"'";
if (!Db->SendCommand(sql)){Form2->Error(0);return;}
if (old_mat->Text.UpperCase().Trim().Pos("NA")&&CB1->Checked)
{
sql="delete from materials where obm='"+old_mat->Text.UpperCase().Trim()+"'";
if (!Db->SendCommand(sql)){Form2->Error(0);return;}
sql="delete from materials_new where obm='"+old_mat->Text.UpperCase().Trim()+"'";
if (!Db->SendCommand(sql)){Form2->Error(0);return;}
}                                                   */
}
//---------------------------------------------------------------------------

