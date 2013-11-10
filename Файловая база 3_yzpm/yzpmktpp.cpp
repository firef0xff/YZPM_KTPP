//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
USEFORM("редактор заказов\Order_set.cpp", Zakaz_set);
USEFORM("редактор заказов\OrderContent_set.cpp", ZakazContent_set);
USEFORM("редактор заказов\Orders.cpp", Orders_editor); /* TFrame: File Type */
USEFORM("редактор спецификаций\razdel.cpp", rzd);
USEFORM("редактор спецификаций\SPEdit.cpp", SPEditor);
USEFORM("редактор спецификаций\Isp_editor.cpp", Form2);
USEFORM("редактор спецификаций\Obd_edt.cpp", Obd_edit);
USEFORM("отчетность\otchethost.cpp", Otchet);
USEFORM("подготовка списка деталей\select_params.cpp", List_sel_params);
USEFORM("поиск\SearchModule.cpp", Search); /* TFrame: File Type */
USEFORM("подготовка списка деталей\Izd_Unroll.cpp", List_Editor);
USEFORM("подготовка списка деталей\List_add.cpp", ListAdd);
USEFORM("технология\вспомогательные модули\справочник заготовок\zagotovk.cpp", zagotovka);
USEFORM("технология\вспомогательные модули\tecniksave.cpp", TB);
USEFORM("технология\вспомогательные модули\справочник заготовок\redaktor_formul.cpp", Fomul_Editor);
USEFORM("справочник профессий\professions.cpp", Professinos);
USEFORM("технология\technology.cpp", TechWnd); /* TFrame: File Type */
USEFORM("редактор спецификаций\sp_params.cpp", spparams);
USEFORM("технология\вспомогательные модули\symblos.cpp", Symbol);
USEFORM("технология\вспомогательные модули\tara_and_strop.cpp", tarandsrop);
USEFORM("технология\TechnologyView.cpp", TechView); /* TFrame: File Type */
USEFORM("технология\вспомогательные модули\instrument.cpp", instr);
USEFORM("дерево спецификации\работа с файлами\files.cpp", FileDisigner);
USEFORM("дерево спецификации\BomTree.cpp", SpTree); /* TFrame: File Type */
USEFORM("дерево спецификации\состояния\selector.cpp", StSelect);
USEFORM("дерево спецификации\состояния\Conditions.cpp", Cond);
USEFORM("log.cpp", LogForm);
USEFORM("main.cpp", mForm);
USEFORM("материалы\Add_mat.cpp", Mater_add);
USEFORM("материалы\material.cpp", materials);
USEFORM("общие функции и классы\DetSelector.cpp", ObdSelector); /* TFrame: File Type */
USEFORM("Логин\Settings_wnd.cpp", Settings);
USEFORM("Логин\диалоги\GTUSdialog.cpp", GTUSGroupSelector);
USEFORM("интерфейс запусков\manufacture.cpp", ManufactureControl); /* TFrame: File Type */
USEFORM("Логин\loginwin.cpp", LogIn);
USEFORM("Логин\диалоги\RightSelect.cpp", fselRight);
USEFORM("Логин\диалоги\User_Data.cpp", UserData);
USEFORM("Логин\диалоги\Input_wnd.cpp", newItem);
USEFORM("Логин\диалоги\NextStateSelector.cpp", Next_State_Selector);
USEFORM("интерфейс запусков\IzdAppender.cpp", IzdAppenderWnd);
USEFORM("интерфейс запусков\ZakazCreator.cpp", ZakazWnd);
USEFORM("интерфейс запусков\ZapCreator.cpp", ZapuskWnd);
//---------------------------------------------------------------------------
WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	String desktop="%desktop%";
	try
	{
		Application->Initialize();
		Application->MainFormOnTaskBar = true;
		Application->CreateForm(__classid(TmForm), &mForm);
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
