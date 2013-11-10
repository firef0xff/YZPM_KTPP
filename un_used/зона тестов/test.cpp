#include <vcl.h>
#pragma hdrstop

#include "test.h"
#include "otchetnost.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
#include "Add_zak.h"
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
DB=new cSQL(ADC);
DB->Connect();

/*//забика данных
LUser=35;
new TAgreements(this,ts2,LUser,DB);
new Tprod(this,ts1,LUser,DB);
TZak_prop *pr=new TZak_prop(this);
	//pr->Align=alClient;
	pr->Parent=ts;
	pr->Show();
	int *select=new int[3];
	select[0]=2;
	select[1]=240387;
	select[2]=240397;         */

}
void __fastcall TForm1::Button2Click(TObject *Sender)
{
vector <String> log=DB->Get_log();
Memo1->Lines->Clear();
for (vector <String>::iterator i=log.begin(); i<log.end(); i++)
	{
	Memo1->Lines->Add(*i);
	}
}



void __fastcall TForm1::Button9Click(TObject *Sender)
{

	cReports *rep=new cReports(DB);
	rep->CreateReport(11,Edit2->Text);

	/*std::vector<String> s;
	String w="1231  1234  88999  223";
	rep->WordWrap(s,w,10,"  ");

	String ss;
	for (int i = 0; i < s.size(); ++i)
	{
		ss+=s[i]+"\n";

	}
	ShowMessage(ss);

	return;       */
}
//---------------------------------------------------------------------------

