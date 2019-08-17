//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
USEFORM("manufacture_schedules\surcharge\surcharge_list.cpp", SurchargeList);
USEFORM("manufacture_schedules\workers.cpp", WorkersSettings); /* TFrame: File Type */
USEFORM("manufacture_schedules\ZakazCreator.cpp", ZakazWnd);
USEFORM("manufacture_schedules\report_params.cpp", RepParams);
USEFORM("orders_editor\OrderContent_set.cpp", ZakazContent_set);
USEFORM("orders_editor\Orders.cpp", Orders_editor); /* TFrame: File Type */
USEFORM("orders_editor\Order_set.cpp", Zakaz_set);
USEFORM("manufacture_schedules\ZapCreator.cpp", ZapuskWnd);
USEFORM("prepare_products_list\Izd_Unroll.cpp", List_Editor);
USEFORM("technology\support_modules\catalog_workpieces\redaktor_formul.cpp", Fomul_Editor);
USEFORM("technology\support_modules\catalog_workpieces\zagotovk.cpp", zagotovka);
USEFORM("technology\support_modules\instrument.cpp", instr);
USEFORM("technology\TechnologyView.cpp", TechView); /* TFrame: File Type */
USEFORM("technology\technology.cpp", TechWnd); /* TFrame: File Type */
USEFORM("technology\support_modules\symblos.cpp", Symbol);
USEFORM("technology\support_modules\tara_and_strop.cpp", tarandsrop);
USEFORM("technology\support_modules\tecniksave.cpp", TB);
USEFORM("reports\komplect.cpp", komplekt);
USEFORM("reports\otchethost.cpp", Otchet);
USEFORM("reports\kol_det.cpp", koldet);
USEFORM("prepare_products_list\List_add.cpp", ListAdd);
USEFORM("prepare_products_list\select_params.cpp", List_sel_params);
USEFORM("professions\professions.cpp", Professinos);
USEFORM("sklad\Add_mat.cpp", Mater_add);
USEFORM("sklad\material.cpp", materials);
USEFORM("sklad\Mater_zam.cpp", Mat_zam);
USEFORM("searcher\SearchModule.cpp", Search); /* TFrame: File Type */
USEFORM("reports\params.cpp", parametr);
USEFORM("reports\pp_start_params.cpp", PP_params);
USEFORM("reports\trb_params.cpp", TrbOptions);
USEFORM("common\DetSelector.cpp", ObdSelector); /* TFrame: File Type */
USEFORM("log.cpp", LogForm);
USEFORM("Login\dialogs\GTUSdialog.cpp", GTUSGroupSelector);
USEFORM("Login\dialogs\Input_wnd.cpp", newItem);
USEFORM("boom_tree\file_working\files.cpp", FileDisigner);
USEFORM("boom_editor\Obd_edt.cpp", Obd_edit);
USEFORM("boom_editor\razdel.cpp", rzd);
USEFORM("boom_editor\SPEdit.cpp", SPEditor);
USEFORM("boom_editor\Isp_editor.cpp", IspList);
USEFORM("boom_tree\contents\Conditions.cpp", Cond);
USEFORM("boom_tree\contents\selector.cpp", StSelect);
USEFORM("boom_editor\sp_params.cpp", spparams);
USEFORM("boom_tree\BomTree.cpp", SpTree); /* TFrame: File Type */
USEFORM("Login\dialogs\NextStateSelector.cpp", Next_State_Selector);
USEFORM("main.cpp", mForm);
USEFORM("manufacture_schedules\Calck\add_data_wnd.cpp", CalckAddParams);
USEFORM("manufacture_schedules\Calck\Usage.cpp", ResourceUsage); /* TFrame: File Type */
USEFORM("Login\Settings_wnd.cpp", Settings);
USEFORM("Login\dialogs\RightSelect.cpp", fselRight);
USEFORM("Login\dialogs\User_Data.cpp", UserData);
USEFORM("Login\loginwin.cpp", LogIn);
USEFORM("manufacture_schedules\ReportBuilder.cpp", Reports);
USEFORM("manufacture_schedules\manufacture.cpp", ManufactureControl); /* TFrame: File Type */
USEFORM("manufacture_schedules\EditWorkerData.cpp", WorkerData);
USEFORM("manufacture_schedules\EditWorkerGroup.cpp", WorkerGroup);
USEFORM("manufacture_schedules\IzdAppender.cpp", IzdAppenderWnd);
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
