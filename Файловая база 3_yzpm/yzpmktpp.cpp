//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
USEFORM("�������� �������\Order_set.cpp", Zakaz_set);
USEFORM("�������� �������\OrderContent_set.cpp", ZakazContent_set);
USEFORM("�������� �������\Orders.cpp", Orders_editor); /* TFrame: File Type */
USEFORM("�������� ������������\razdel.cpp", rzd);
USEFORM("�������� ������������\SPEdit.cpp", SPEditor);
USEFORM("�������� ������������\Isp_editor.cpp", Form2);
USEFORM("�������� ������������\Obd_edt.cpp", Obd_edit);
USEFORM("����������\otchethost.cpp", Otchet);
USEFORM("���������� ������ �������\select_params.cpp", List_sel_params);
USEFORM("�����\SearchModule.cpp", Search); /* TFrame: File Type */
USEFORM("���������� ������ �������\Izd_Unroll.cpp", List_Editor);
USEFORM("���������� ������ �������\List_add.cpp", ListAdd);
USEFORM("����������\��������������� ������\���������� ���������\zagotovk.cpp", zagotovka);
USEFORM("����������\��������������� ������\tecniksave.cpp", TB);
USEFORM("����������\��������������� ������\���������� ���������\redaktor_formul.cpp", Fomul_Editor);
USEFORM("���������� ���������\professions.cpp", Professinos);
USEFORM("����������\technology.cpp", TechWnd); /* TFrame: File Type */
USEFORM("�������� ������������\sp_params.cpp", spparams);
USEFORM("����������\��������������� ������\symblos.cpp", Symbol);
USEFORM("����������\��������������� ������\tara_and_strop.cpp", tarandsrop);
USEFORM("����������\TechnologyView.cpp", TechView); /* TFrame: File Type */
USEFORM("����������\��������������� ������\instrument.cpp", instr);
USEFORM("������ ������������\������ � �������\files.cpp", FileDisigner);
USEFORM("������ ������������\BomTree.cpp", SpTree); /* TFrame: File Type */
USEFORM("������ ������������\���������\selector.cpp", StSelect);
USEFORM("������ ������������\���������\Conditions.cpp", Cond);
USEFORM("log.cpp", LogForm);
USEFORM("main.cpp", mForm);
USEFORM("���������\Add_mat.cpp", Mater_add);
USEFORM("���������\material.cpp", materials);
USEFORM("����� ������� � ������\DetSelector.cpp", ObdSelector); /* TFrame: File Type */
USEFORM("�����\Settings_wnd.cpp", Settings);
USEFORM("�����\�������\GTUSdialog.cpp", GTUSGroupSelector);
USEFORM("��������� ��������\manufacture.cpp", ManufactureControl); /* TFrame: File Type */
USEFORM("�����\loginwin.cpp", LogIn);
USEFORM("�����\�������\RightSelect.cpp", fselRight);
USEFORM("�����\�������\User_Data.cpp", UserData);
USEFORM("�����\�������\Input_wnd.cpp", newItem);
USEFORM("�����\�������\NextStateSelector.cpp", Next_State_Selector);
USEFORM("��������� ��������\IzdAppender.cpp", IzdAppenderWnd);
USEFORM("��������� ��������\ZakazCreator.cpp", ZakazWnd);
USEFORM("��������� ��������\ZapCreator.cpp", ZapuskWnd);
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
