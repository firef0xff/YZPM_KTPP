//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------

USEFORM("..\маркетинг\продукция\Agrements_select.cpp", Agreements_select);
USEFORM("..\маркетинг\продукция\products.cpp", prod); /* TFrame: File Type */
USEFORM("..\маркетинг\продукция\Select_params_prod.cpp", Sel_params_prod);
USEFORM("..\маркетинг\продукция\Add_zak.cpp", Zak_prop);
USEFORM("test.cpp", Form1);
USEFORM("..\маркетинг\contractors.cpp", Contragents);
USEFORM("..\маркетинг\договора\agreements_main.cpp", Agreements); /* TFrame: File Type */
USEFORM("..\маркетинг\договора\Select_params_agr.cpp", Sel_params_agr);
USEFORM("..\..\reports\kol_det.cpp", koldet);
USEFORM("..\..\reports\komplect.cpp", komplekt);
USEFORM("..\..\reports\params.cpp", parametr);
USEFORM("..\..\reports\pp_start_params.cpp", PP_params);
USEFORM("..\..\reports\trb_params.cpp", TrbOptions);
//---------------------------------------------------------------------------
WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
		Application->Initialize();
		Application->MainFormOnTaskBar = true;
		Application->CreateForm(__classid(TForm1), &Form1);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}
	return 0;
}
//---------------------------------------------------------------------------
