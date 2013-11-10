//---------------------------------------------------------------------------

#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <vector.h>
#include "functions.h"
#include "Z_Data.h"
#include "SQL.h"
#include <ADODB.hpp>
#include <DB.hpp>
//---------------------------------------------------------------------------

class TSimple_fraction : public TForm
{
__published:	// IDE-managed Components
	TLabeledEdit *isx;  //
	TLabel *Label1;
	TEdit *Chislitel;
	TEdit *Znamenatel;
	TLabel *Label2;
	TMemo *Memo1;
	TADOConnection *ADOConnection1;
	void __fastcall isxKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall Label1Click(TObject *Sender);
private:	// User declarations
	vector <Z_Data*> results;
	vector <int> gears;
	cSQL *db;
	void 	 Get_NumbsLines(const String &str);//функция для получения разложения по числам
	void 	 Get_multipliers(String &str); // функция на разложение на множетили
	unsigned long int		 Get_Next_simple_numb(const unsigned long int &last);// функция получения следующего простого числа
public:		// User declarations
	__fastcall TSimple_fraction(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TSimple_fraction *Simple_fraction;
//---------------------------------------------------------------------------
#endif
