//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
#include "ToOasu.h"

//---------------------------------------------------------------------------
USEFORM("main_one.cpp", OASUtrasfer);
//---------------------------------------------------------------------------
TOASUtrasfer *OASUtrasfer;
WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{

	try
		{
		Application->Initialize();
		Application->MainFormOnTaskBar = true;
		Application->CreateForm(__classid(TOASUtrasfer), &OASUtrasfer);
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
