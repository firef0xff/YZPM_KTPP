//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------

USEFORM("..\���������\���������\Agrements_select.cpp", Agreements_select);
USEFORM("..\���������\���������\products.cpp", prod); /* TFrame: File Type */
USEFORM("..\���������\���������\Select_params_prod.cpp", Sel_params_prod);
USEFORM("..\����������\params.cpp", parametr);
USEFORM("..\����������\pp_start_params.cpp", PP_params);
USEFORM("..\����������\trb_params.cpp", TrbOptions);
USEFORM("..\����������\kol_det.cpp", koldet);
USEFORM("..\����������\komplect.cpp", komplekt);
USEFORM("..\��������� ��������\manufacture.cpp", ManufactureControl); /* TFrame: File Type */
USEFORM("test.cpp", Form1);
USEFORM("..\���������\��������\agreements_main.cpp", Agreements); /* TFrame: File Type */
USEFORM("..\���������\��������\Select_params_agr.cpp", Sel_params_agr);
USEFORM("..\���������\���������\Add_zak.cpp", Zak_prop);
USEFORM("..\��������� ��������\ZakazCreator.cpp", ZakazWnd);
USEFORM("..\��������� ��������\ZapCreator.cpp", ZapuskWnd);
USEFORM("..\���������\contractors.cpp", Contragents);
USEFORM("..\��������� ��������\IzdAppender.cpp", IzdAppenderWnd);
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
