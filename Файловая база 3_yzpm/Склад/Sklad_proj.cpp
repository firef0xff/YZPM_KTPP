//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
USEFORM("Sklad_Form.cpp", Sklad);
USEFORM("Manufacturing_Materials.cpp", Materials_Need);
USEFORM("EntraseMaterial.cpp", wndEntarseMaterial);
USEFORM("..\маркетинг\contractors.cpp", Contragents);
//---------------------------------------------------------------------------
WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
		Application->Initialize();
		Application->MainFormOnTaskBar = true;
		Application->CreateForm(__classid(TMaterials_Need), &Materials_Need);
		//Application->CreateForm(__classid(TAreaEdit), &AreaEdit);
		//Application->CreateForm(__classid(TwndEntarseMaterial), &wndEntarseMaterial);
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
