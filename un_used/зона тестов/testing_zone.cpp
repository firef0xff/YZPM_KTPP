//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------

USEFORM("..\маркетинг\продукция\Agrements_select.cpp", Agreements_select);
USEFORM("..\маркетинг\продукция\products.cpp", prod); /* TFrame: File Type */
USEFORM("..\маркетинг\продукция\Select_params_prod.cpp", Sel_params_prod);
USEFORM("..\отчетность\params.cpp", parametr);
USEFORM("..\отчетность\pp_start_params.cpp", PP_params);
USEFORM("..\отчетность\trb_params.cpp", TrbOptions);
USEFORM("..\отчетность\kol_det.cpp", koldet);
USEFORM("..\отчетность\komplect.cpp", komplekt);
USEFORM("..\интерфейс запусков\manufacture.cpp", ManufactureControl); /* TFrame: File Type */
USEFORM("test.cpp", Form1);
USEFORM("..\маркетинг\договора\agreements_main.cpp", Agreements); /* TFrame: File Type */
USEFORM("..\маркетинг\договора\Select_params_agr.cpp", Sel_params_agr);
USEFORM("..\маркетинг\продукция\Add_zak.cpp", Zak_prop);
USEFORM("..\интерфейс запусков\ZakazCreator.cpp", ZakazWnd);
USEFORM("..\интерфейс запусков\ZapCreator.cpp", ZapuskWnd);
USEFORM("..\маркетинг\contractors.cpp", Contragents);
USEFORM("..\интерфейс запусков\IzdAppender.cpp", IzdAppenderWnd);
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
