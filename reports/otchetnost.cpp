// ---------------------------------------------------------------------------

#pragma hdrstop
#include "otchetnost.h"
#include  <math.h>

// ---------------------------------------------------------------------------
#pragma package(smart_init)

cReports::cReports(cSQL *r)
{
	DB=r;
	parametr=new Tparametr(0);
	pp_params=new TPP_params(0);
	trb_params=new TTrbOptions(0);
	koldet=new Tkoldet(0);
	koldet->DB=r;
	XL=new cExcel();
}

cReports::~cReports()
{
}
// ������

bool cReports::CreateReport(int type, String param)
{
	String sql;
	int modalresult=mrOk;
	TADOQuery *rez=DB->SendSQL
		("select value from administration.settings where property='template'");
	Templates=Trim(rez->FieldByName("Value")->Value);
	delete rez;
	rez=0;
	parametr->type=type;
	switch(type)
	{
	case 1:
		{
			sql="Call temporary_tables.det_list ('"+GostToVin(param)+"')";
			break;
		}
	case 2:
		{
			sql="Call temporary_tables.det_inside ('"+GostToVin(param)+"')";
			break;
		}
	case 3:
		{
			parametr->ShowModal();
			sql="";
			modalresult=parametr->ModalResult;
			break;
		}
	case 4:
		{
			parametr->ShowModal();
			sql="Call temporary_tables.report_by_raccex ('"+GostToVin(param)+
				"',"+parametr->cex->Text+")";
			modalresult=parametr->ModalResult;
			break;
		}
	case 5:
		{
			parametr->ShowModal();
			sql="Call temporary_tables.Mat_report ('"+GostToVin(param)+"',"+
				parametr->kol->Text+")";
			modalresult=parametr->ModalResult;
			break;
		}
	case 6:
		{
			koldet->obd=GostToVin(param);
			sql="";
			koldet->ShowModal();
			modalresult=koldet->ModalResult;
			break;
		}
	case 7:
		{
			modalresult=parametr->ShowModal();

			break;
		}
	case 8:
		{
			modalresult=parametr->ShowModal();
			break;
		}
	case 9:
		{
			modalresult=parametr->ShowModal();
			break;
		}
	case 10:
		{
			modalresult=parametr->ShowModal();
			break;
		}
	case 11:
		{
			modalresult=parametr->ShowModal();
			break;
		}
	default:
		{
			sql="";
			return false;
		}
	}

	if(modalresult==mrOk)
	{
		switch(type)
		{
		case 1:
			{
				ShowSostIzd(DB->SendSQL(sql));
				break;
			}
		case 2:
			{
				ShowDetInside(DB->SendSQL(sql));
				break;
			}
		case 3:
			{
				PlanPrDet(GostToVin(param), parametr->kol->Text);
				break;
			}
		case 4:
			{
				Showlist(DB->SendSQL(sql));
				break;
			}
		case 5:
			{
				Mat_report(DB->SendSQL(sql), param);
				break;
			}
		case 6:
			{
				Texnologic(param);
				break;
			}
		case 7:
			{
				Mat_Ved_Komplect(param, parametr->zak->Text,
					parametr->kol->Text.ToInt());
				break;
			}
		case 8:
			{
				Trebovanie_Materialov(param, parametr->zak->Text,
					parametr->kol->Text.ToInt());
				break;
			}
		case 9:
			{
				Boiler_Assemblies(param,parametr->zak->Text,parametr->kol->Text.ToInt(),parametr->cex->Text,parametr->part->Text);
				break;
			}
		case 10:
			{
				Operation_Timing(param,parametr->zak->Text,parametr->kol->Text.ToInt(),parametr->cex->Text,parametr->part->Text);
				break;
			}
		case 11:
			{
				Cpu_Operation_Timing(param,parametr->zak->Text,parametr->kol->Text.ToInt(),parametr->cex->Text,parametr->part->Text);
				break;
			}
		default:
			return false;
		}
		return true;
	}
	return false;
}

void cReports::Showlist(TADOQuery *rez)
{
	if(rez==0)
	{
		ShowMessage("������ ������������ �������/������ ����� ������.");
		return;
	}
	XL->Connect();
	XL->DisplayAlerts(false);
	XL->SetActiveBooks(XL->Books_New());
	XL->SetActiveBook(XL->GetFirstBook());
	XL->SetActiveSheets(XL->GetSheets());
	XL->SetActiveSheet(XL->GetFirstSheet());
	SQL_To_XL(rez);
	XL->Visible(true);
	delete rez;
}

void cReports::SQL_To_XL(TADOQuery *rez)
{
	if(rez==0)
	{
		ShowMessage("������ ������������ �������/������ ����� ������.");
		return;
	}
	int i;
	for(i=0; i<rez->FieldCount; i++)
	{
		XL->toCells(1, i+1, rez->Fields->operator[](i)->FieldName.Trim());
		XL->Set_format(XL->GetColumn(i+1), "\@");
	}
	rez->First();
	while(!rez->Eof)
	{
		for(i=0; i<rez->FieldCount; i++)
		{
			XL->toCells(rez->RecNo+1, i+1,
				Trim(rez->FieldByName(rez->Fields->operator[](i)->FieldName)
				->Value));
		}
		rez->Next();
	}
}

void cReports::PlanPrDet(String obd, String kol)
{
	pp_params->ShowModal();
	if(pp_params->ModalResult!=mrOk)
	{
		return;
	}

	AnsiString file=Templates+"form140005.xlt";
	XL->Connect();
	XL->DisplayAlerts(false);
	//XL->Visible(true);
	OpenTemplate(file);
	// ������������ ����...
	int Lcount=0, RowMin, RowMax, RowCount=0, TitleRow=3, prizn=0;
	double itog=0, itogPZ=0;
	bool newlist;
	TADOQuery *rez=0;
	// �������� ������� ����� ������

	if(pp_params->P_pr->Checked)
	{
		rez=DB->SendSQL("Call temporary_tables.plan_pr_det ('"+obd+"',"+kol+",'"+parametr->cex->Text+"')");
		pp_params->ML->Enabled=!parametr->cex->Text.Length();
		if(rez==0)
		{
			ShowMessage("������ ������������ �������");
			return;
		}
		if(!rez->RecordCount)
		{
			ShowMessage("������ ����� ������.");
			delete rez;
			return;
		} // ���������
		newlist=true;
		rez->First();
		while(!rez->Eof) // ������ ������ �� ����
		{
			if(newlist)
			{
				XL->Sheet_Copy(XL->GetSheet(Lcount+1), XL->GetSheet(Lcount+1));
				// ���������� ����� ������� �� ���������� ����
				TitleRow=3;
				Lcount++ ;
				XL->SetActiveSheet(XL->GetSheet(Lcount));
				XL->Set_Sheet_Name(XL->GetSheet(Lcount),
					parametr->zak->Text+"-"+IntToStr(Lcount));
				XL->toCells(1, 1, "��� ���� "+Date()+
					"     ���� ������������ �������, ��. ������     ���� "+
					parametr->cex->Text+"     �� ������ "+parametr->zak->Text+
					"     ������ "+parametr->part->Text+
					"     �. 140005     ���� "+IntToStr(Lcount));
				newlist=false;
				RowCount=1;
				// ������� ����� �����
				XL->Range_Copy(XL->GetRows(7, 9));
				XL->Range_Paste(XL->GetRows(4, 6));
			}
			// ���������� ������� �������
			RowMin=TitleRow+RowCount*3-2;
			RowMax=TitleRow+RowCount*3;
			// �������� �������� �����������
			if(prizn<rez->FieldByName("prizn")->Value)
			{
				prizn=rez->FieldByName("prizn")->Value;
				TitleRow++ ;
				RowMin=TitleRow+RowCount*3-2;
				RowMax=TitleRow+RowCount*3;
				XL->Range_Merge(XL->GetRange(RowMin-1, 3, RowMin-1, 6));
				switch(prizn)
				{
				case 1:
					{
						XL->toCells(RowMin-1, 3,
							"������ ���. ������ � ���. ������");
						break;
					}
				case 2:
					{
						XL->toCells(RowMin-1, 3,
							"������������, ����., �������. ������");
						break;
					}
				default:
					break;
				}
			}
			// �����������
			XL->Sheet_activate(XL->GetSheet(Lcount+1));
			XL->Range_Copy(XL->GetRows(XL->GetSheet(Lcount+1), 4, 6));
			XL->Sheet_activate();
			XL->Range_Paste(XL->GetRows(RowMin, RowMax));
			// ���������� ������
			RowCount++ ;
			XL->toCells(RowMin, 1, IntToStr(rez->RecNo));
			XL->toCells(RowMax-1, 1, rez->FieldByName("namd")->Value);
			XL->toCells(RowMin, 2, VinToGost(rez->FieldByName("obd")->Value));
			XL->toCells(RowMin, 3, rez->FieldByName("kol")->Value);
			XL->toCells(RowMin, 4, rez->FieldByName("nama")->Value);
			XL->toCells(RowMax-1, 4, rez->FieldByName("prma")->Value);
			XL->toCells(RowMin, 5, rez->FieldByName("tsht")->Value);
			XL->toCells(RowMax-1, 5, rez->FieldByName("tpart")->Value);
			XL->toCells(RowMin, 7, Get_Rascex(rez->FieldByName("obd")->Value));
			itog=itog+rez->FieldByName("tpart")->Value;
			itogPZ=itogPZ+rez->FieldByName("tpzpart")->Value;
			XL->toCells(RowMin, 8, rez->FieldByName("ost")->Value);

			if(RowMin>68)
			{
				newlist=true;
				if (pp_params->trim_file)
				{
					TrimFile(pp_params->save_to_file,pp_params->file_ext,file,Lcount,pp_params->lists_in_file);
				}
			}
			rez->Next();
		}
		XL->toCells(RowMax+1, 4, "����� �� ������: ");
		XL->toCells(RowMax+1, 5, FloatToStr(itog));
		XL->toCells(RowMax+2, 4, "����� �� ������ ���: ");
		XL->toCells(RowMax+2, 5, FloatToStr(itogPZ));
	}
	/* �������� ����������� */
	if (pp_params->trim_file)
	{
		TrimFile(pp_params->save_to_file,pp_params->file_ext,file,Lcount,pp_params->lists_in_file);
	}
	Lcount=AddReport(obd, kol, Lcount);

	if (pp_params->trim_file)
	{
		TrimFile(pp_params->save_to_file,pp_params->file_ext,file,Lcount,pp_params->lists_in_file);
	}

	if(pp_params->ML->Enabled&&pp_params->ML->Checked)
	{
		for(rez->First(); !rez->Eof; rez->Next())
		{
			Lcount=AddML(rez->FieldByName("obd")->Value,
				rez->FieldByName("namd")->Value,
				rez->FieldByName("nama")->Value,
				rez->FieldByName("prma")->Value, rez->FieldByName("kol")->Value,
				Lcount, rez->RecNo);
			if (pp_params->trim_file)
			{
				TrimFile(pp_params->save_to_file,pp_params->file_ext,file,Lcount,pp_params->lists_in_file);
			}

		}
	}

	if (pp_params->save_to_file.Length())
	{
		if (pp_params->trim_file)
		{
			TrimFile(pp_params->save_to_file,pp_params->file_ext,file,Lcount,Lcount);
		}
		else
		{
        	SaveFile(pp_params->save_to_file,pp_params->file_ext,Lcount);
		}
		XL->Book_Close(XL->GetBook(1));
		XL->Disconnect();
	}
	else
	{
		while(Lcount&&Lcount<XL->GetSheetsCount())
		{
			XL->Sheet_Del(XL->GetSheet(XL->GetSheetsCount()));
		}
		XL->Sheet_activate(XL->GetFirstSheet());
		XL->Visible(true);
	}
	delete rez;
}
int cReports::AddML(String obd, String name, String name_mat, String prof_mat,
	int kol, int Lcount, int mlnumber)
{
	int page=0, kolzag=0, row_start, row_end=62;
	String Range;
	bool newpage=true;
	// ������ �� ������

	TADOQuery *rez=DB->SendSQL("Call temporary_tables.Marsh_list ('"+obd+"')");
	if(rez==0)
	{
		ShowMessage("������ ������������ �������");
		return Lcount;
	}
	while(!rez->Eof)
	{
		// ���� ���� ��� �������� ��
		if(newpage)
		{
			XL->Sheet_Copy(XL->GetSheet(Lcount+2), XL->GetSheet(Lcount+1),
				Variant().NoParam());
			Lcount++ ;
			page++ ;
			XL->SetActiveSheet(XL->GetSheet(Lcount));
			XL->Set_Sheet_Name(XL->GetSheet(Lcount),
				"��-"+IntToStr(mlnumber)+"-"+IntToStr(page));
			if(page==1)
			{
				// �������� �������/
				XL->Range_Copy(XL->GetRows(22, 26));
				XL->Range_Paste(XL->GetRows(18, 21));
				// ������ ������ ��� ������/
				if(rez->FieldByName("kdz")->Value.operator int())
				{
					kolzag=ceil(double(kol)/rez->FieldByName("kdz")
						->Value.operator int());
				}
				// ������ �����/
				XL->toCells(3, 3, "� �/� "+IntToStr(mlnumber)+" �� "+Date()+" "+
					VinToGost(obd)+" "+parametr->zak->Text+" "+
					parametr->part->Text);
				XL->toCells(3, 14, "� �/� "+IntToStr(mlnumber)+" �� "+Date()+
					" "+VinToGost(obd)+" "+parametr->zak->Text+" "+
					parametr->part->Text);
				XL->toCells(4, 3, name);
				XL->toCells(4, 14, name);
				XL->toCells(5, 4, kolzag);
				XL->toCells(6, 4, IntToStr(kol));
				XL->toCells(5, 16, kolzag);
				XL->toCells(6, 16, IntToStr(kol));
				XL->toCells(8, 4, rez->FieldByName("masz")->Value);
				XL->toCells(8, 6,
					FloatToStrF(rez->FieldByName("masz")->Value.operator double
					() *kol, ffGeneral, 9, 2));
				XL->toCells(8, 7, rez->FieldByName("vz")->Value);
				XL->toCells(8, 16, rez->FieldByName("masz")->Value);
				XL->toCells(8, 18,
					FloatToStrF(rez->FieldByName("masz")->Value.operator double
					() *kol, ffGeneral, 9, 2));
				XL->toCells(8, 20, rez->FieldByName("vz")->Value);
				XL->toCells(9, 4, rez->FieldByName("nrm")->Value);
				XL->toCells(9, 6,
					FloatToStrF(rez->FieldByName("nrm")->Value.operator double()
					*kol, ffGeneral, 9, 2));
				XL->toCells(9, 16, rez->FieldByName("nrm")->Value);
				XL->toCells(9, 18,
					FloatToStrF(rez->FieldByName("nrm")->Value.operator double()
					*kol, ffGeneral, 9, 2));
				XL->toCells(11, 20, name_mat+" "+prof_mat);
				XL->toCells(11, 12, VinToGost(obd));
				XL->toCells(11, 10, parametr->part->Text);
				XL->toCells(11, 8, parametr->zak->Text);
				XL->toCells(11, 6, "�� "+Date());
				XL->toCells(11, 5, IntToStr(mlnumber));

				XL->toCells(12, 1, name);
				XL->toCells(12, 17, rez->FieldByName("razz")->Value);
				XL->toCells(13, 4, Get_Rascex(obd));
				XL->toCells(13, 13, kolzag);
				XL->toCells(14, 13, IntToStr(kol));
				row_start=18;
			}
			else
			{
				// �������� ����� ������� ����� �������� ������ ����� ��������/
				XL->Range_Copy(XL->GetRows(22, 35));
				XL->Range_Paste(XL->GetRows(2, 15));
				XL->Range_Copy(XL->GetRows(16, 17));
				XL->Range_Paste(XL->GetRows(2, 3));
				XL->Range_Copy(XL->GetRows(22, 27));
				XL->Range_Paste(XL->GetRows(16, 21));
				row_start=4;
			}
			XL->toCells(1, 8, VinToGost(obd));
			XL->toCells(1, 7, parametr->part->Text);
			XL->toCells(1, 6, parametr->zak->Text);
			XL->toCells(1, 5, IntToStr(mlnumber));
			XL->toCells(1, 23, IntToStr(page));
			newpage=false;
		}
		// �����������
		XL->Range_Copy(XL->GetRows(XL->GetSheet(Lcount+2), 18, 21));
		// �������
		XL->Sheet_activate();
		XL->Range_Paste(XL->GetRows(row_start, row_start+4));
		// ����� ������/
		XL->toCells(row_start, 1, rez->FieldByName("ceu")->Value);
		XL->toCells(row_start+2, 1, rez->FieldByName("opr")->Value);
		XL->toCells(row_start, 2, Trim(rez->FieldByName("obo")->Value)+
			"                                     "+
			Trim(rez->FieldByName("kop")->Value)+" "+
			Trim(rez->FieldByName("nop")->Value));
		XL->toCells(row_start, 5, rez->FieldByName("rr")->Value);
		XL->toCells(row_start+2, 5, rez->FieldByName("kvn")->Value);
		XL->toCells(row_start, 7, rez->FieldByName("tpz")->Value);
		XL->toCells(row_start, 9, rez->FieldByName("tsht")->Value);
		if(row_start<row_end)
		{
			row_start+=4;
		}
		else
		{
			newpage=true;
		}
		rez->Next();
	}
	delete rez;
	return Lcount;
}
int cReports::AddReport(String obd, String kol, int Lcount)
{
	if(pp_params->T_cex->Checked)
	{
		TADOQuery *rez=
			DB->SendSQL("Call temporary_tables.plan_pr_det_times_by_ceu ('"+obd+
			"',"+kol+")");
		if(rez==0)
		{
			ShowMessage("������ ������������ �������");
			return Lcount;
		}
		if(!rez->RecordCount)
		{
			ShowMessage("������ ����� ������.");
			delete rez;
			return Lcount;
		} // ���������
		int i;
		XL->Sheet_activate(XL->GetSheet(Lcount+1));
		XL->Sheet_Add(XL->GetSheets());
		Lcount++ ;
		XL->SetActiveSheet(XL->GetSheet(Lcount));
		XL->Set_Sheet_Name(XL->GetSheet(Lcount), "������������ �� �����");
		SQL_To_XL(rez);
		delete rez;
	}
	if(pp_params->T_obor->Checked)
	{
		TADOQuery *rez=
			DB->SendSQL("Call temporary_tables.plan_pr_det_times_by_obo ('"+obd+
			"',"+kol+")");
		if(rez==0)
		{
			ShowMessage("������ ������������ �������");
			return Lcount;
		}
		if(!rez->RecordCount)
		{
			ShowMessage("������ ����� ������.");
			delete rez;
			return Lcount;
		} // ���������
		XL->Sheet_activate(XL->GetSheet(Lcount+1));
		XL->Sheet_Add(XL->GetSheets());
		Lcount++ ;
		XL->SetActiveSheet(XL->GetSheet(Lcount));
		XL->Set_Sheet_Name(XL->GetSheet(Lcount),
			"������������ �� ������������");
		SQL_To_XL(rez);
		delete rez;
	}
	return Lcount;
}

void cReports::OpenTemplate (AnsiString templ)
{
	XL->SetActiveBooks(XL->Books_Open(templ));
	// ������������� ���������� ���������� �� ����� ������
	XL->SetActiveBook(XL->GetFirstBook());
	XL->SetActiveSheets(XL->GetSheets());
	XL->SetActiveSheet(XL->GetFirstSheet());
}
void cReports::SaveFile		(String file_name,String file_ext, int Lcount)
{
	while(Lcount&&Lcount<XL->GetSheetsCount())
	{
		XL->Sheet_Del(XL->GetSheet(XL->GetSheetsCount()));
	}
	XL->Sheet_activate(XL->GetFirstSheet());
	XL->Books_Save(file_name+file_ext);
}
void cReports::TrimFile		(String file_name,String file_ext,String templ, int &Lcount, int max_list_no)
{
	static String prev_file_name="";
	static int file_no=0;

	if (Lcount&&Lcount>=max_list_no)
	{
		if (prev_file_name!=file_name)
		{
			file_no=0;
			prev_file_name=file_name;
		}
		else
		{
			++file_no;
		}

		String addin;
		if (file_no)
		{
			addin="_"+String(file_no);
		}
		SaveFile(file_name+addin,file_ext,Lcount);
		XL->Book_Close(XL->GetBook(1));
		OpenTemplate(templ);
		Lcount=0;
	}
}

void cReports::ShowDetInside(TADOQuery *rez)
{
	if(rez==0)
	{
		ShowMessage("������ ������������ �������");
		return;
	}
	if(!rez->RecordCount)
	{
		ShowMessage("������ ����� ������.");
		delete rez;
		return;
	} // ���������
	// ���������
	int row;
	XL->Connect();
	XL->DisplayAlerts(false);
	XL->SetActiveBooks(XL->Books_New());
	XL->SetActiveBook(XL->GetFirstBook());
	XL->SetActiveSheets(XL->GetSheets());
	XL->SetActiveSheet(XL->GetFirstSheet());

	XL->toCells(2, 1, "�����������");
	XL->toCells(2, 2, "������������");
	XL->toCells(2, 3, "����������");
	XL->toCells(2, 4, "����");
	XL->toCells(1, 1, "������");
	XL->Range_Border(XL->GetRange(2, 1, 2, 4), 7, 1, 3, 1); // ������� �����
	XL->Range_Border(XL->GetRange(2, 1, 2, 4), 10, 1, 3, 1); // ������� ������
	XL->Range_Border(XL->GetRange(2, 1, 2, 4), 8, 1, 3, 1); // ������� �������
	XL->Range_Border(XL->GetRange(2, 1, 2, 4), 9, 1, 3, 1); // ������� ������
	XL->HorizontalAlignment(XL->GetRange(1, 1, 1, 4), -4108);
	XL->Range_ColWidth(XL->GetRange(1, 1, 1, 1), 30);
	XL->Range_ColWidth(XL->GetRange(1, 2, 1, 2), 50);
	XL->Range_ColWidth(XL->GetRange(1, 3, 1, 3), 15);
	XL->Range_ColWidth(XL->GetRange(1, 4, 1, 4), 30);
	row=3;
	rez->First();
	XL->Set_format(XL->GetColumn(1), "\@");
	String Obd_old="";
	size_t count=0;
	double kol=0;
	while(!rez->Eof)
	{
		String Obd=VinToGost(rez->FieldByName("obd")->Value);
		if(Obd!=Obd_old)
		{
			if (Obd_old!="")
			{
				if (count!=1)
				{
					XL->toCells(row, 2, "�����");
					XL->toCells(row, 3, kol);
					row++;
				}
				row++;
			}
			XL->toCells(row, 1, Obd);
			Obd_old=Obd;
			kol=0;
			count=1;
			if(!rez->FieldByName("namd")->Value.IsNull())
			{
				XL->toCells(row, 2, Trim(rez->FieldByName("namd")->Value));
			}
		}else
		{
        	count++;
		}
		kol+=(double)rez->FieldByName("kol")->Value;
		XL->toCells(row, 3, Trim(rez->FieldByName("kol")->Value));
		XL->toCells(row, 4, VinToGost(rez->FieldByName("obu")->Value));
		row++ ;
		rez->Next();
	}
	delete rez;
	XL->Range_Merge(XL->GetRange(1, 1, 1, 4));
	XL->Range_Border(XL->GetRange(3, 1, row-1, 4), 12, 1, 2, 1);
	// ���������� ���������������
	XL->Range_Border(XL->GetRange(3, 1, row-1, 4), 7, 1, 3, 1); // ������� �����
	XL->Range_Border(XL->GetRange(3, 1, row-1, 4), 10, 1, 3, 1);
	// ������� ������
	XL->Range_Border(XL->GetRange(3, 1, row-1, 4), 8, 1, 3, 1);
	// ������� �������
	XL->Range_Border(XL->GetRange(3, 1, row-1, 4), 9, 1, 3, 1);
	// ������� ������
	XL->Range_Border(XL->GetRange(1, 1, row-1, 4), 11, 1, 3, 1);
	// ���������� ������������
	XL->Visible(true);
}

void cReports::ShowSostIzd(TADOQuery *rez)
{
	if(rez==0)
	{
		ShowMessage("������ ������������ �������");
		return;
	}
	if(!rez->RecordCount)
	{
		ShowMessage("������ ����� ������.");
		delete rez;
		return;
	}
	// ���������
	int row;
	XL->Connect();
	XL->DisplayAlerts(false);
	XL->SetActiveBooks(XL->Books_New());
	XL->SetActiveBook(XL->GetFirstBook());
	XL->SetActiveSheets(XL->GetSheets());
	XL->SetActiveSheet(XL->GetFirstSheet());
	XL->toCells(2, 1, "�����������");
	XL->toCells(2, 2, "������������");
	XL->toCells(2, 3, "����������");
	XL->toCells(1, 1, "������");
	XL->Range_Border(XL->GetRange(2, 1, 2, 3), 7, 1, 3, 1); // ������� �����
	XL->Range_Border(XL->GetRange(2, 1, 2, 3), 10, 1, 3, 1); // ������� ������
	XL->Range_Border(XL->GetRange(2, 1, 2, 3), 8, 1, 3, 1); // ������� �������
	XL->Range_Border(XL->GetRange(2, 1, 2, 3), 9, 1, 3, 1); // ������� ������

	XL->Range_ColWidth(XL->GetRange(1, 1, 1, 1), 30);
	XL->Range_ColWidth(XL->GetRange(1, 2, 1, 2), 50);
	XL->Range_ColWidth(XL->GetRange(1, 3, 1, 4), 15);
	XL->Set_format(XL->GetColumn(1), "\@");
	row=3;
	SostIzd(rez, row, 0, ""); // ����� ������� ������  �����������
	XL->Range_Merge(XL->GetRange(1, 1, 1, 3));
	XL->HorizontalAlignment(XL->GetRange(1, 1, 1, 3), -4108);
	/* ��� ������� ����� �� ����������� ���� */
	XL->Range_Border(XL->GetRange(3, 1, row-1, 3), 12, 1, 2, 1);
	// ���������� ���������������
	XL->Range_Border(XL->GetRange(3, 1, row-1, 3), 7, 1, 3, 1); // ������� �����
	XL->Range_Border(XL->GetRange(3, 1, row-1, 3), 10, 1, 3, 1);
	// ������� ������
	XL->Range_Border(XL->GetRange(3, 1, row-1, 3), 8, 1, 3, 1);
	// ������� �������
	XL->Range_Border(XL->GetRange(3, 1, row-1, 3), 9, 1, 3, 1);
	// ������� ������
	XL->Range_Border(XL->GetRange(1, 1, row-1, 3), 11, 1, 3, 1);
	// ���������� ������������
	delete rez;
	XL->Visible(true);
}

void cReports::SostIzd(TADOQuery *rez, int &row, int lvl, String obd)
{
	if(rez==0)
	{
		ShowMessage("������ ������������ �������");
		return;
	}
	if(!rez->RecordCount)
	{
		ShowMessage("������ ����� ������.");
		delete rez;
		return;
	} // ���������
	int tmprow;
	String tab="";
	while(tab.Length()<lvl*5)
	{
		tab=tab+" ";
	}
	rez->First();
	while(!rez->Eof)
	{
		if(Trim(rez->FieldByName("obu")->Value)==obd&&Trim
			(rez->FieldByName("lvl")->Value)==lvl)
		{
			XL->toCells(row, 1,
				tab+Trim(VinToGost(rez->FieldByName("obd")->Value)));
			if(!rez->FieldByName("namd")->Value.IsNull())
			{
				XL->toCells(row, 2, Trim(rez->FieldByName("namd")->Value));
			}
			XL->toCells(row, 3, Trim(rez->FieldByName("kol")->Value));
			row++ ;
			tmprow=rez->RecNo;
			SostIzd(rez, row, lvl+1, Trim(rez->FieldByName("obd")->Value));
			rez->RecNo=tmprow;
		}
		rez->Next();
	}
}

void cReports::Mat_report(TADOQuery *rez, String obd)
{
	if(rez==0)
	{
		ShowMessage("������ ������������ �������");
		return;
	}
	if(!rez->RecordCount)
	{
		ShowMessage("������ ����� ������.");
		delete rez;
		return;
	} // ���������

	AnsiString file=Templates+"materials.xlt";
	XL->Connect();
	// XL->Visible(true);
	XL->DisplayAlerts(false);
	XL->SetActiveBooks(XL->Books_Open(file));
	// ������������� ���������� ���������� �� ����� ������
	XL->SetActiveBook(XL->GetFirstBook());
	XL->SetActiveSheets(XL->GetSheets());
	XL->SetActiveSheet(XL->GetFirstSheet());

	int row_start, row_end=36, Lcount=0;
	bool newpage=true;
	// �������� ������� ����� ������
	rez->First();
	while(!rez->Eof)
	{
		if(newpage)
		{
			row_start=5;
			XL->Sheet_Copy(XL->GetSheet(Lcount+1), XL->GetSheet(Lcount+1));
			Lcount++ ;
			XL->SetActiveSheet(XL->GetSheet(Lcount));
			XL->Set_Sheet_Name(XL->GetSheet(Lcount), "����-"+IntToStr(Lcount));
			// ������� �������/
			XL->Range_Copy(XL->GetRows(14, 19));
			XL->Range_Paste(XL->GetRows(8, 13));
			// ������ �����/
			XL->toCells(2, 5, VinToGost(obd)+" "+parametr->zak->Text);
			XL->toCells(1, 7, "���� "+IntToStr(Lcount));
			newpage=false;
		}
		// �����������
		if(row_start<row_end&&rez->RecNo<rez->RecordCount)
		{
			XL->Sheet_activate(XL->GetSheet(Lcount+1));
			XL->Range_Copy(XL->GetRows(XL->GetSheet(Lcount+1), 5, 6));
			XL->Sheet_activate();
			// �������
			XL->Range_Paste(XL->GetRows(row_start, row_start+2));
		}
		// ����� ������
		XL->toCells(row_start, 2, VinToGost(rez->FieldByName("���")->Value));
		XL->toCells(row_start, 3, rez->FieldByName("���������")->Value);
		XL->toCells(row_start, 4, rez->FieldByName("��������")->Value);
		XL->toCells(row_start, 5, rez->FieldByName("����� �� �������")->Value);
		XL->toCells(row_start, 6, rez->FieldByName("������� ���������")->Value);
		if(row_start<row_end)
		{
			row_start++ ;
		}
		else
		{
			newpage=true;
		}
		rez->Next();
	}
	delete rez;
	// ���������� ����������� ����������
	// 1 ������
	rez=DB->SendSQL("Call temporary_tables.Mat_report_detail ('"+GostToVin(obd)+
		"',"+parametr->kol->Text+")");
	if(rez==0)
	{
		XL->Visible(true);
		return;
	}
	// 2 ������
	newpage=true;
	row_end=49;
	String grp_param="null";
	double nrm_sum=0;
	int k=0, page=1;
	// �������� ������� ����� ������
	rez->First();
	while(!rez->Eof)
	{
		if(newpage)
		{
			row_start=4;
			k=0;
			XL->Sheet_Copy(XL->GetSheet(Lcount+2), Variant().NoParam(),
				XL->GetSheet(Lcount));
			Lcount++ ;
			XL->SetActiveSheet(XL->GetSheet(Lcount));
			XL->Set_Sheet_Name(XL->GetSheet(Lcount), "���-"+IntToStr(page));
			page++ ;
			XL->Range_Copy(XL->GetRows(8, 10));
			XL->Range_Paste(XL->GetRows(5, 7));
			// ������ �����/
			XL->toCells(1, 3, VinToGost(obd));
			XL->toCells(1, 9, parametr->zak->Text);
			XL->toCells(1, 10, "���� "+IntToStr(Lcount));
			newpage=false;
		}
		if(grp_param!=rez->FieldByName("���")->Value.operator UnicodeString()+
			rez->FieldByName("��������")->Value.operator UnicodeString()+
			rez->FieldByName("���������")->Value.operator UnicodeString())
		{
			if(grp_param!="null")
			{
				row_start+=1+k;
				// ����������� ������ ������,
				XL->Sheet_activate(XL->GetSheet(Lcount+2));
				XL->Range_Copy(XL->GetRows(XL->GetSheet(Lcount+2), 7, 7));
				XL->Sheet_activate();
				// �������
				XL->Range_Paste(XL->GetRows(row_start-1, row_start-1));

				// ������ ������ �� ������
				XL->toCells(row_start-1, 9, nrm_sum);
				// toCells(row_start-1,10,"��.");
			}
			else
			{
				row_start+=k;
			}
			// ����������� ������ ����� ,
			XL->Sheet_activate(XL->GetSheet(Lcount+2));
			XL->Range_Copy(XL->GetRows(XL->GetSheet(Lcount+2), 5, 5));
			XL->Sheet_activate();
			// �������
			XL->Range_Paste(XL->GetRows(row_start, row_start));
			// ��������� �������� ����������/
			k=1;
			nrm_sum=0;
			// ��������
			XL->toCells(row_start, 2,
				VinToGost(rez->FieldByName("���")->Value));
			XL->toCells(row_start, 3,
				rez->FieldByName("��������")->Value.operator UnicodeString()+
				" "+rez->FieldByName("���������")
				->Value.operator UnicodeString());
		}
		grp_param=rez->FieldByName("���")->Value.operator UnicodeString()+
			rez->FieldByName("��������")->Value.operator UnicodeString()+
			rez->FieldByName("���������")->Value.operator UnicodeString();
		// ����������� ������ ����� ������ ���������� �������� ����������/
		// �����������
		XL->Sheet_activate(XL->GetSheet(Lcount+2));
		XL->Range_Copy(XL->GetRows(XL->GetSheet(Lcount+2), 6, 6));
		XL->Sheet_activate();
		// �������
		XL->Range_Paste(XL->GetRows(row_start+k, row_start+k));
		// ����� ������/
		// ������
		XL->toCells(row_start+k, 1, VinToGost(rez->FieldByName("obd")->Value));
		XL->toCells(row_start+k, 2, rez->FieldByName("namd")->Value);
		XL->toCells(row_start+k, 3, rez->FieldByName("kol")->Value);
		XL->toCells(row_start+k, 4, rez->FieldByName("mass")->Value);
		// ���������
		XL->toCells(row_start+k, 5, rez->FieldByName("vz")->Value);
		XL->toCells(row_start+k, 6, rez->FieldByName("razz")->Value);
		XL->toCells(row_start+k, 7, rez->FieldByName("kolzag")->Value);
		XL->toCells(row_start+k, 8, rez->FieldByName("masz")->Value);
		// ���������
		XL->toCells(row_start+k, 9, rez->FieldByName("����� �� �������")
			->Value);
		nrm_sum=nrm_sum+rez->FieldByName("����� �� �������")->Value;
		XL->toCells(row_start+k, 10, rez->FieldByName("������� ���������")
			->Value);
		XL->toCells(row_start+k, 11, rez->FieldByName("���")->Value);
		if(row_start+k<row_end)
		{
			k++ ;
		}
		else
		{
			newpage=true;
		}
		rez->Next();
	}
	delete rez;
	// ����������� ������ ������,//
	// �����������
	XL->Sheet_activate(XL->GetSheet(Lcount+2));
	XL->Range_Copy(XL->GetRows(XL->GetSheet(Lcount+2), 7, 7));
	XL->Sheet_activate();
	// �������
	XL->Range_Paste(XL->GetRows(row_start+k, row_start+k));
	// ������ ������ �� ������/
	XL->toCells(row_start+k, 9, nrm_sum);
	// toCells(row_start+k,10,"��.");
	// 3 ����� �� �����
	// �����
	XL->Sheet_Del(XL->GetSheet(XL->GetSheetsCount()));
	XL->SetActiveSheet(XL->GetFirstSheet());
	XL->Sheet_activate();
	XL->Visible(true);
}

void cReports::Texnologic(String obd)
{
	TADOQuery *rez=0, *rez1=0;
	String sql, sql1;
	// ---------------------------------------------------------------------------
	sql="Call temporary_tables.teh_dt_info('"+GostToVin(obd)+"')";
	// ���������
	AnsiString file=Templates+"mok.xlt";
	XL->Connect();
	XL->DisplayAlerts(false);
	XL->SetActiveBooks(XL->Books_Open(file));
	// ������������� ���������� ���������� �� ����� ������
	XL->SetActiveBook(XL->GetFirstBook());
	XL->SetActiveSheets(XL->GetSheets());
	XL->SetActiveSheet(XL->GetFirstSheet());
	// ������������ ����...
	int Lcount=0;
	// �������� ����������/
	String zak="", napr="";
	detinfo dt;
	rez=DB->SendSQL(sql);
	if(rez==0)
	{
		ShowMessage("������ ������������ �������");
		XL->Visible(true);
		return;
	}
	if(rez->RecordCount)
	{
		rez->First();
		napr=rez->FieldByName("napr")->Value;
		dt.obd=obd;
		dt.namd=rez->FieldByName("namd")->Value;
		dt.dnte=rez->FieldByName("dnte")->Value;//.operator TDateTime().FormatString("dd.mm.yyyy");
		dt.mater=rez->FieldByName("material")->Value;
		dt.ei=rez->FieldByName("ei")->Value;
		dt.masd=rez->FieldByName("masd")->Value;
		dt.obm=VinToGost(rez->FieldByName("obm")->Value);
		dt.vz=rez->FieldByName("vz")->Value;
		dt.razz=rez->FieldByName("razz")->Value;
		dt.kdz=rez->FieldByName("kdz")->Value;
		dt.masz=rez->FieldByName("masz")->Value;
		dt.nrm=rez->FieldByName("nrm")->Value;
		dt.kim=rez->FieldByName("kim")->Value;
	}
	else
	{
		dt.obd=obd;
		dt.namd="";
		dt.dnte="";
		dt.mater="";
		dt.ei="";
		dt.masd="";
		dt.obm="";
		dt.vz="";
		dt.razz="";
		dt.kdz="";
		dt.masz="";
		dt.nrm="";
		dt.kim="";
	}

	Row_range r;
	Tex_new_list(dt, Lcount, r);
	// ������ �� ������������
	sql="Call temporary_tables.teh_oper('"+GostToVin(obd)+"')";
	delete rez;
	rez=DB->SendSQL(sql);
	if(rez==0)
	{
		ShowMessage("������ ������������ �������");
		XL->Visible(true);
		return;
	}
	rez->First();
	String krop, kolod, tpz, tsht, ksht;
	while(!rez->Eof)
	{
		// ����� ��������
		XL->toCells(r.Row, 1, "A");
		XL->toCells(r.Row, 6,
			rez->FieldByName("ceu")->Value.operator UnicodeString()
			.SubString(1, 2));
		XL->toCells(r.Row, 10,
			rez->FieldByName("ceu")->Value.operator UnicodeString()
			.SubString(3, 2));
		XL->toCells(r.Row, 18,
			rez->FieldByName("opr")->Value.operator UnicodeString());
		XL->toCells(r.Row, 23,
			rez->FieldByName("oper")->Value.operator UnicodeString());
		XL->toCells(r.Row, 52,
			rez->FieldByName("ioht")->Value.operator UnicodeString());
		Tex_format_string(1, r.Row); // ���������� ������/
		// ������ ������������
		if(rez->FieldByName("krop")->Value.operator UnicodeString()!="0")
		{
			krop=rez->FieldByName("krop")->Value.operator UnicodeString();
		}
		else
		{
			krop="";
		}
		if(rez->FieldByName("kolod")->Value.operator UnicodeString()!="0")
		{
			kolod=rez->FieldByName("kolod")->Value.operator UnicodeString();
		}
		else
		{
			kolod="";
		}
		if(rez->FieldByName("tpz")->Value.operator UnicodeString()!="0")
		{
			tpz=rez->FieldByName("tpz")->Value.operator UnicodeString();
		}
		else
		{
			tpz="";
		}
		if(rez->FieldByName("tsht")->Value.operator UnicodeString()!="0")
		{
			tsht=rez->FieldByName("tsht")->Value.operator UnicodeString();
		}
		else
		{
			tsht="";
		}
		if(rez->FieldByName("ksht")->Value.operator UnicodeString()!="0")
		{
			ksht=rez->FieldByName("ksht")->Value.operator UnicodeString();
		}
		else
		{
			ksht="";
		}
		r.Row++ ;
		if(r.Row>r.Rowmax)
		{
			Tex_new_list(dt, Lcount, r);
		}
		XL->toCells(r.Row, 1, "�");
		XL->toCells(r.Row, 10,
			rez->FieldByName("obo")->Value.operator UnicodeString());
		XL->toCells(r.Row, 52,
			rez->FieldByName("ttp")->Value.operator UnicodeString());
		XL->toCells(r.Row, 56, ksht);
		XL->toCells(r.Row, 61,
			rez->FieldByName("prof")->Value.operator UnicodeString());
		XL->toCells(r.Row, 68, krop);
		XL->toCells(r.Row, 72,
			rez->FieldByName("rr")->Value.operator UnicodeString());
		XL->toCells(r.Row, 76, kolod);
		XL->toCells(r.Row, 81,
			rez->FieldByName("en")->Value.operator UnicodeString());
		XL->toCells(r.Row, 86,
			rez->FieldByName("kvn")->Value.operator UnicodeString());
		XL->toCells(r.Row, 91, tpz);
		XL->toCells(r.Row, 98, tsht);
		XL->toCells(r.Row, 106, "");
		// ���������� ������/
		// ���������
		if(rez->FieldByName("stro")->Value.operator UnicodeString().Trim()!="")
		{
			r.Row++ ;
			if(r.Row>r.Rowmax)
			{
				Tex_new_list(dt, Lcount, r);
			}
			XL->toCells(r.Row, 1, "");
			XL->toCells(r.Row, 10,
				rez->FieldByName("stro")->Value.operator UnicodeString()
				.Trim());
			Tex_format_string(2, r.Row); // ���������� ������/
		}
		// ����
		if(rez->FieldByName("tara")->Value.operator UnicodeString().Trim()!="")
		{
			r.Row++ ;
			if(r.Row>r.Rowmax)
			{
				Tex_new_list(dt, Lcount, r);
			}
			XL->toCells(r.Row, 1, "");
			XL->toCells(r.Row, 10,
				rez->FieldByName("tara")->Value.operator UnicodeString()
				.Trim());
			Tex_format_string(2, r.Row); // ���������� ������/
		}
		// ������ �� ��������
		sql1="Call temporary_tables.teh_per('"+GostToVin(obd)+"','"+
			rez->FieldByName("opr")->Value.operator UnicodeString()+"')";
		rez1=DB->SendSQL(sql1);
		if(rez1==0)
		{
			ShowMessage("������ ������������ �������");
			XL->Visible(true);
			return;
		}
		rez1->First();
		while(!rez1->Eof)
		{
			// ����� ���������
			r.Row++ ;
			if(r.Row>r.Rowmax)
			{
				Tex_new_list(dt, Lcount, r);
			}
			XL->toCells(r.Row, 1, "�");
			XL->toCells(r.Row, 11,
				rez1->FieldByName("tpe")->Value.operator UnicodeString()
				.Trim());
			Tex_format_string(3, r.Row); // ���������� ������/
			rez1->Next();
		}
		delete rez1;
		// ������ �� ����������
		sql1="Call temporary_tables.teh_instr('"+GostToVin(obd)+"','"+
			rez->FieldByName("opr")->Value.operator UnicodeString()+"')";
		rez1=DB->SendSQL(sql1);
		if(rez1==0)
		{
			ShowMessage("������ ������������ �������");
			XL->Visible(true);
			return;
		}
		rez1->First();
		while(!rez1->Eof)
		{
			// ����� �����������
			r.Row++ ;
			if(r.Row>r.Rowmax)
			{
				Tex_new_list(dt, Lcount, r);
			}
			XL->toCells(r.Row, 1, "�");
			XL->toCells(r.Row, 12,
				rez1->FieldByName("nain")->Value.operator UnicodeString()
				.Trim());
			Tex_format_string(4, r.Row); // ���������� ������/
			rez1->Next();
		}
		delete rez1;
		// ��������
		if(rez->FieldByName("control")->Value.operator UnicodeString()
			.Trim()!="")
		{
			r.Row++ ;
			if(r.Row>r.Rowmax)
			{
				Tex_new_list(dt, Lcount, r);
			}
			XL->toCells(r.Row, 1, "A");
			XL->toCells(r.Row, 23, "69 �����������");
			XL->toCells(r.Row, 52, "�-����-56-2002");
			Tex_format_string(1, r.Row); // ���������� ������/
			if(rez->FieldByName("control")->Value.operator UnicodeString().Trim
				()!="��� ������")
			{
				r.Row++ ;
				if(r.Row>r.Rowmax)
				{
					Tex_new_list(dt, Lcount, r);
				}
				XL->toCells(r.Row, 1, "�");
				XL->toCells(r.Row, 11,
					rez->FieldByName("control")->Value.operator UnicodeString()
					.Trim());
				Tex_format_string(3, r.Row); // ���������� ������/
			}
		}
		r.Row++ ;
		if(r.Row>r.Rowmax)
		{
			Tex_new_list(dt, Lcount, r);
		}
		rez->Next();
	}
	delete rez;
	XL->toCells(r.Row, 11, napr);
	while(r.Row<=r.Rowmax)
	{
		Tex_format_string(3, r.Row); // ���������� ������/
		r.Row++ ;
	}
	int i;
	for(i=1; i<=Lcount; i++)
	{
		XL->SetActiveSheet(XL->GetSheet(i));
		XL->toCells(6, 103, IntToStr(Lcount));
	}
	while(Lcount<XL->GetSheetsCount())
	{
		XL->Sheet_Del(XL->GetSheet(XL->GetSheetsCount()));
	}
	XL->Sheet_activate(XL->GetFirstSheet());
	XL->Visible(true);
}

void cReports::Tex_format_string(int type, int Row)
{
	switch(type)
	{
	case 1:
		{
			XL->Range_Merge(XL->GetRange(Row, 52, Row, 110));
			XL->Range_Border(XL->GetRange(Row, 52, Row, 110), 10, 1, 2, 0);

			XL->Range_Merge(XL->GetRange(Row, 6, Row, 9));
			XL->Range_Border(XL->GetRange(Row, 6, Row, 9), 10, 1, 2, 0);

			XL->Range_Merge(XL->GetRange(Row, 10, Row, 13));
			XL->Range_Border(XL->GetRange(Row, 10, Row, 13), 10, 1, 2, 0);

			XL->Range_Merge(XL->GetRange(Row, 18, Row, 22));
			XL->Range_Border(XL->GetRange(Row, 18, Row, 22), 10, 1, 2, 0);
			XL->Range_Border(XL->GetRange(Row, 18, Row, 22), 7, 1, 2, 0);
			XL->GetRange(Row, 6, Row, 51).OlePropertyGet("Font").OlePropertySet
				("Bold", true);
			XL->GetRange(Row, 6, Row, 51).OlePropertyGet("Font").OlePropertySet
				("Size", "14");
			break;
		}
	case 2:
		{
			XL->Range_Merge(XL->GetRange(Row, 10, Row, 110));
		}
	case 3:
		{
			XL->Range_Merge(XL->GetRange(Row, 11, Row, 110));
		}
	case 4:
		{
			XL->Range_Merge(XL->GetRange(Row, 12, Row, 110));
		}
	default:
		break;
	}
}

void cReports::Tex_new_list(detinfo dt, int &Lcount, Row_range &r)
{
	// ����������� ������� �����
	if(!Lcount)
	{
		XL->Sheet_Copy(XL->GetSheet(XL->GetSheetsCount()-1),
			XL->GetSheet(XL->GetSheetsCount()-1));
	}
	else
	{
		XL->Sheet_Copy(XL->GetSheet(XL->GetSheetsCount()),
			XL->GetSheet(XL->GetSheetsCount()-1));
	}
	Lcount++ ;
	XL->SetActiveSheet(XL->GetSheet(Lcount));
	XL->Set_Sheet_Name(XL->GetSheet(Lcount), "���� "+IntToStr(Lcount));
	// ���������� ����� � ��������� �������� ����������
	XL->toCells(6, 107, IntToStr(Lcount));
	if(Lcount==1)
	{
		XL->toCells(8, 10, user); // ������ ����� ���� ������� ������������
		XL->toCells(8, 32, dt.dnte);
		XL->toCells(8, 54, dt.obd);
		XL->toCells(8, 81, koldet->CB2->Text+"                      "+
			koldet->E1->Text+" ��.");
		// ��� ������ � ���������� ������ ����� ������� �� ������ �������� ���������� �� ����������� ����
		XL->toCells(11, 44, dt.namd);
		XL->toCells(13, 6, dt.mater);
		XL->toCells(15, 6, dt.ei);
		XL->toCells(15, 10, dt.masd);
		XL->toCells(15, 17, dt.obm);
		XL->toCells(15, 30, dt.vz);
		XL->toCells(15, 38, dt.razz);
		XL->toCells(15, 64, dt.kdz);
		XL->toCells(15, 70, dt.masz);
		XL->toCells(15, 77, dt.nrm);
		XL->toCells(15, 90, dt.kim);
		r.Row=18;
		r.Rowmax=31;
	}
	else
	{
		XL->toCells(6, 87, dt.obd);
		XL->toCells(8, 71, dt.namd);
		XL->toCells(8, 98, koldet->CB2->Text+"                      "+
			koldet->E1->Text+" ��.");
		// l�� ������ � ���������� ������ ����� ������� �� ������ �������� ���������� �� ����������� ����
		r.Row=13;
		r.Rowmax=29;
	}
	return;
}

void cReports::Mat_Ved_Komplect(String obd, String zak, int kol)
{
	Tkomplekt *komplekt=new Tkomplekt(0);
	komplekt->ShowModal();
	if(komplekt->ModalResult!=mrOk)
	{
		delete komplekt;
		return;
	} // ���������
	AnsiString file=Templates+"materials_by_types.xlt";
	XL->Connect();
	XL->DisplayAlerts(false);
	XL->SetActiveBooks(XL->Books_Open(file));
	// ������������� ���������� ���������� �� ����� ������
	XL->SetActiveBook(XL->GetFirstBook());
	XL->SetActiveSheets(XL->GetSheets());
	XL->SetActiveSheet(XL->GetFirstSheet());
	// ���� ���������� ����������
	int list=0;
	if(komplekt->materials->Checked)
	{
		String Title="��������� ����������";
		Mat_Ved_razd(DB->SendSQL("Call temporary_tables.bordereau_all('"+
			GostToVin(obd)+"',"+String(kol)+")"), obd, zak, Title, list);
	}
	if(komplekt->litho->Checked)
	{
		String Title="��������� ���������� �� ������, ���������� �� �����";
		Mat_Ved_razd(DB->SendSQL("Call temporary_tables.bordereau_litho('"+
			GostToVin(obd)+"',"+String(kol)+")"), obd, zak, Title, list);
	}
	if(komplekt->shtamping->Checked)
	{
		String Title="��������� ���������� �� ������, ���������� �� �������";
		Mat_Ved_razd(DB->SendSQL("Call temporary_tables.bordereau_stamping('"+
			GostToVin(obd)+"',"+String(kol)+")"), obd, zak, Title, list);
	}
	if(komplekt->cooperation->Checked)
	{
		String Title="��������� ���������� �� ������, ���������� �� ����������";
		Mat_Ved_razd(DB->SendSQL
			("Call temporary_tables.bordereau_cooperation('"+GostToVin(obd)+
			"',"+String(kol)+")"), obd, zak, Title, list);
	}
	// ����� ������
	if(list)
	{
		while(list<XL->GetSheetsCount())
		{
			XL->Sheet_Del(XL->GetSheet(XL->GetSheetsCount()));
		}
	}
	XL->Sheet_activate(XL->GetFirstSheet());
	XL->Visible(true);
	delete komplekt;
}
void cReports::Mat_Ved_razd(TADOQuery *rez, const String &obd,
	const String &zak, const String &Title, int &list)
{
	if(rez==0)
	{
		ShowMessage("������ ������������ �������");
		return;
	}
	if(!rez->RecordCount)
	{
		delete rez;
		return;
	}
	int str=0, Row=0, RowMax=13, StartPos=6, Pos, templ=XL->GetSheetsCount();
	// ����������� ������
	rez->First();
	while(!rez->Eof)
	{
		if(!Row)
		{
			XL->Sheet_Copy(XL->GetSheet(templ), XL->GetSheet(templ));
			list++ ;
			str++ ;
			XL->SetActiveSheet(XL->GetSheet(list));
			XL->Set_Sheet_Name(XL->GetSheet(list), zak+"-"+IntToStr(list));
			XL->toCells(1, 2, DateToStr(Date()));
			XL->toCells(1, 3, Title+" ("+VinToGost(obd)+")");
			XL->toCells(1, 12, "����� "+zak);
			XL->toCells(1, 15, "���� "+IntToStr(str));
			Row++ ;
			templ++ ;
		}
		// ����� ������

		Pos=(Row-1)*3+StartPos;
		// ����������� ������ �������
		if(Row>1)
		{
			XL->Sheet_activate(XL->GetSheet(templ));
			XL->Range_Copy(XL->GetRows(XL->GetSheet(templ), 6, 8));
			XL->Sheet_activate();
			XL->Range_Paste(XL->GetRows(Pos, Pos+3));
		}
		// �����
		XL->toCells(Pos, 1, VinToGost(rez->FieldByName("�����������")->Value));
		XL->toCells(Pos+1, 1, rez->FieldByName("������������")->Value);
		XL->toCells(Pos, 4, rez->FieldByName("���-��")->Value);
		XL->toCells(Pos, 5, rez->FieldByName("��. ���.")->Value);
		XL->toCells(Pos+1, 5, rez->FieldByName("snameei")->Value);
		XL->toCells(Pos, 6, rez->FieldByName("����� ������")->Value);
		XL->toCells(Pos, 7, VinToGost(rez->FieldByName("obm")->Value));
		XL->toCells(Pos+1, 7, rez->FieldByName("��������")->Value);
		XL->toCells(Pos, 8, rez->FieldByName("��� ���������")->Value);
		XL->toCells(Pos+1, 8, rez->FieldByName("������� ���.")->Value);
		XL->toCells(Pos, 9, rez->FieldByName("���-�� ���. � ���.")->Value);
		XL->toCells(Pos, 10, rez->FieldByName("����� ���.")->Value);
		XL->toCells(Pos, 11, rez->FieldByName("����� �������")->Value);
		XL->toCells(Pos, 12,
			Get_Rascex(rez->FieldByName("�����������")->Value));
		Row++ ;
		if(Row>13)
		{
			Row=0;
		}
		rez->Next();
	}
	delete rez;
}

void cReports::Trebovanie_Materialov	(String obd,String zak,int kol)
{
	if (trb_params->ShowModal()!=mrOk)
	{
    	return;
	}
	//�������������
	AnsiString file=Templates+"materials_trb.xlt";
	XL->Connect();
	XL->DisplayAlerts(false);
	//XL->Visible(true);
	OpenTemplate(file);
	const int row_start=19, row_end=25, head_row=11, org_row=7;
	int Lcount=0,ofset=-1;
	//������� ������ �����

	TADOQuery *rez=0;
	String sql;
	if (trb_params->MatReceiver=="")
	{
		sql = "Call temporary_tables.Get_Start_Podr_for_uzel('"+GostToInt(obd)+"')";
		rez=DB->SendSQL(sql);
		if (!rez)
		{
			ShowMessage("������ ��� ���������� �������");
			return;
		}
		rez->First();
	}

	do
	{
		bool newpage=true;
		//������� ������ ���������� ��� ����
		String cex;
		String utch;
		if (rez)
		{
			cex=rez->FieldByName("cex")->Value;
			utch=rez->FieldByName("utch")->Value;
		}
		sql = "Call temporary_tables.Get_Materials_Order('"+GostToInt(obd)+"',"+String(kol)+",'"+cex+"','"+utch+"')";
		TADOQuery *rez2=DB->SendSQL(sql);
		if (!rez2)
		{
			continue;
		}
		String old_sklad="";
		int row=0;
		for (rez2->First(); !rez2->Eof; rez2->Next())
		{
			String date=Now().FormatString("dd.mm.yy");
			String sklad=rez2->FieldByName("�����")->Value;
			String podr=cex+utch;
			if (trb_params->MatReceiver!="")
			{
				podr=trb_params->MatReceiver;
			}
			String ss=rez2->FieldByName("���������� ����")->Value;
			String material1=Trim(rez2->FieldByName("���������")->Value);
			String material2=Trim(rez2->FieldByName("��������")->Value);
			String kod=VinToGost(rez2->FieldByName("���")->Value);
			String eik="";
			if (!rez2->FieldByName("ei")->Value.IsNull())
				eik=rez2->FieldByName("ei")->Value;
			String ei=rez2->FieldByName("������� ���������")->Value;
			String request=rez2->FieldByName("����� �� �������")->Value;
			String price=rez2->FieldByName("����")->Value;
			double cost=rez2->FieldByName("�����")->Value;
			if (old_sklad!=sklad)
			{
				newpage=true;
				old_sklad=sklad;
			}

			if(newpage)
			{
				if (ofset)
				{
					ofset=0;
				}
				else
				{
					ofset=30;
				}
				if (!ofset)
				{
					XL->Sheet_Copy(XL->GetSheet(Lcount+1),XL->GetSheet(Lcount+1), Variant().NoParam());
					Lcount++ ;
					XL->SetActiveSheet(XL->GetSheet(Lcount));

					XL->Set_Sheet_Name(XL->GetSheet(Lcount), "����-"+IntToStr(Lcount));
				}
				// ������ �����/
				XL->toCells(head_row+ofset, 1, date);
				XL->toCells(head_row+ofset, 5, sklad);
				XL->toCells(head_row+ofset, 8, podr);
				if (trb_params->Organization!="")
				{
					XL->toCells(org_row+ofset, 4, trb_params->Organization);
				}
				newpage=false;
				row=row_start;
			}
			//����������
			XL->toCells(row+ofset, 1, ss);
			XL->toCells(row+ofset, 2, zak);
			if (24<(material1.Length()+material2.Length()))
			{
				XL->toCells(row+ofset, 4, material1);
				row++;
				XL->toCells(row+ofset, 4, material2);
			}
			else
			{
				XL->toCells(row+ofset, 4, material1+" "+material2);
			}
			XL->toCells(row+ofset, 7, kod);
			XL->toCells(row+ofset, 8, eik);
			XL->toCells(row+ofset, 9, ei);
			XL->toCells(row+ofset, 10, request);
			//XL->toCells(row+ofset, 13, price);
			//XL->toCells(row+ofset, 14, cost);
			row++;
			if (row>row_end||trb_params->OneRow->Checked)
			{
				newpage=true;
				if (trb_params->trim_file&&ofset)
				{
					TrimFile(trb_params->save_to_file,trb_params->file_ext,file,Lcount,trb_params->lists_in_file);
				}
			}
		}
		delete rez2;
		if (rez)
		{
			rez->Next();
		}
	}
	while (rez&&!rez->Eof);
	if (rez)
	{
    	delete rez;
	}


    if (trb_params->save_to_file.Length())
	{
		if (trb_params->trim_file)
		{
			TrimFile(trb_params->save_to_file,trb_params->file_ext,file,Lcount,Lcount);
		}
		else
		{
			SaveFile(trb_params->save_to_file,trb_params->file_ext,Lcount);
		}
		XL->Book_Close(XL->GetBook(1));
		XL->Disconnect();
	}
	else
	{
		while(Lcount&&Lcount<XL->GetSheetsCount())
		{
			XL->Sheet_Del(XL->GetSheet(XL->GetSheetsCount()));
		}
		XL->Sheet_activate(XL->GetFirstSheet());
		XL->Visible(true);
	}
}

void cReports::Boiler_Assemblies	(String obd,String zak,int kol,String ceu,String part)
{
	if (ceu.Length()!=4)
	{
        ShowMessage("�� ������ ���/�������");
		return;
	}
//�������������
	AnsiString file=Templates+"boiler_assembly.xlt";
	XL->Connect();
	XL->DisplayAlerts(false);
	//XL->Visible(true);
	OpenTemplate(file);
	const int row_start=5, row_end=64, head_row=1;
	int Lcount=0;
	//������� ������ �����

	String sql = "Call temporary_tables.boiler_assemblies('"+GostToInt(obd)+"',"+String(kol)+",'"+ceu.SubString(1,2)+"','"+ceu.SubString(3,2)+"')";
	TADOQuery *rez=DB->SendSQL(sql);
	if (!rez)
	{
		ShowMessage("������ ��� ���������� �������");
		return;
	}
	bool newpage=true;
	int row(row_start);
	double sum_mass=0.0,sum_trud=0.0;
	for (rez->First(); !rez->Eof; rez->Next())
	{

		int prt=rez->FieldByName("part")->Value;
		String date=Now().FormatString("dd.mm.yy");
		String obd=VinToGost(rez->FieldByName("obd")->Value);
		String name=rez->FieldByName("namd")->Value;
		String vz=rez->FieldByName("vz")->Value;
		int kol_det=rez->FieldByName("kol")->Value;
		String razz=rez->FieldByName("razz")->Value;
		String mat_name;
		String mat_prof;
		if (!rez->FieldByName("nama")->Value.IsNull())
			mat_name+=rez->FieldByName("nama")->Value;
		if (!rez->FieldByName("goma")->Value.IsNull())
			mat_name+=" "+rez->FieldByName("goma")->Value;

		if (!rez->FieldByName("prma")->Value.IsNull())
			mat_prof+=rez->FieldByName("prma")->Value;
		if (!rez->FieldByName("gopr")->Value.IsNull())
			mat_prof+=" "+rez->FieldByName("gopr")->Value;

		if (mat_name==""&&mat_prof==""&&!rez->FieldByName("mat_name")->Value.IsNull())
			mat_name+=rez->FieldByName("mat_name")->Value;


		double mass=rez->FieldByName("masd")->Value;
		double norm=rez->FieldByName("nrm")->Value;
		double trud=rez->FieldByName("ed_trud")->Value;
		double trud_common=rez->FieldByName("summ_trud")->Value;
		String nar_no;
		String ml_no;
		String pm=Get_Rascex(obd);//rez->FieldByName("pm")->Value;
		pm+=" "+rez->FieldByName("napr")->Value;
        String last_op;
		if(newpage)
		{
			XL->Sheet_Copy(XL->GetSheet(Lcount+1),XL->GetSheet(Lcount+1), Variant().NoParam());
			Lcount++ ;
			XL->SetActiveSheet(XL->GetSheet(Lcount));

			XL->Set_Sheet_Name(XL->GetSheet(Lcount), "����-"+IntToStr(Lcount));
			// ������ �����/
			XL->toCells(head_row, 3,  date	);
			XL->toCells(head_row, 9,  ceu	);
			XL->toCells(head_row, 11, zak	);
			XL->toCells(head_row, 13, part	);
			XL->toCells(head_row, 16, Lcount);
			newpage=false;
			row=row_start;
		}
		XL->Range_Copy(XL->GetRows(row, row+1));
		XL->Range_Paste(XL->GetRows(row+2, row+3));
		XL->toCells(row, 	1, vz		);
		XL->toCells(row, 	2, obd		);
		XL->toCells(row+1, 	2, name		);
		XL->toCells(row, 	5, kol_det	);
		XL->toCells(row, 	6, razz		);
		XL->toCells(row, 	7, mat_name	);
		XL->toCells(row+1, 	7, mat_prof	);
		if (!prt)
		{
			sum_mass+=mass;
			sum_trud+=trud_common;
			XL->toCells(row, 	8, mass		);
			XL->toCells(row+1, 	8, norm		);
			XL->toCells(row, 	9, trud   		);
			XL->toCells(row+1, 	9, trud_common  );
		}
		XL->toCells(row,   10, ml_no   	);
		XL->toCells(row+1, 10, nar_no  	);
		XL->toCells(row,   11, pm   	);
		XL->toCells(row,   12, last_op  );

		row+=2;
		if (row>row_end)
		{
			newpage=true;
		}
	}
	delete rez;
	XL->Sheet_activate(XL->GetSheet(Lcount+1));
	XL->Range_Copy(XL->GetRows(XL->GetSheet(Lcount+1), 9, 10));
	XL->Sheet_activate();
	XL->Range_Paste(XL->GetRows(row+1, row+2));
	XL->toCells(row+1, 	8, sum_mass		);
	XL->toCells(row+1, 	9, sum_trud   	);
	while(Lcount&&Lcount<XL->GetSheetsCount())
	{
		XL->Sheet_Del(XL->GetSheet(XL->GetSheetsCount()));
	}
	XL->Sheet_activate(XL->GetFirstSheet());
	XL->Visible(true);
}

void cReports::Operation_Timing	(String obd,String zak,int kol,String ceu,String part) //140006
{
 	if (ceu.Length()!=4)
	{
        ShowMessage("�� ������ ���/�������");
		//return;
	}
//�������������
	AnsiString file=Templates+"manufacture_forms.xlt";
	XL->Connect();
	XL->DisplayAlerts(false);
	//XL->Visible(true);
	OpenTemplate(file);
	const int row_start=4, row_end=54, head_row=1;
	int Lcount=0,TemplPos=4;
	const int timing_len=52,way_len=46,name_len=30,row_H=2;
	std::vector<String> timing,way,name;


   	String sql = "Call temporary_tables.rp140006('"+GostToInt(obd)+"',"+String(kol)+",'"+ceu.SubString(1,2)+"','"+ceu.SubString(3,2)+"',0)";
	TADOQuery *rez=DB->SendSQL(sql);
	if (!rez)
	{
		ShowMessage("������ ��� ���������� �������");
		return;
	}
	bool newpage=true;
	int row(row_start);
	double sum_trud=0.0;
	int prizn(0),npp(1);
	bool no_data=true;
	for (rez->First(); !rez->Eof; rez->Next())
	{
		no_data=false;
		String date=Now().FormatString("dd.mm.yy");
		String obd=VinToGost(rez->FieldByName("obd")->Value);
		int kol_det=rez->FieldByName("kol")->Value;

		double trud=rez->FieldByName("tsht")->Value;
		double trud_common=rez->FieldByName("tpart")->Value;

		WordWrap(way,Get_Rascex(obd),way_len);
		WordWrap(timing,rez->FieldByName("timing")->Value,timing_len,"  ");
		WordWrap(name,rez->FieldByName("namd")->Value,name_len);

		int curr_prizn=rez->FieldByName("prizn")->Value;

		//������� ��� �����
		int add_cnt=((timing.size()>way.size())?timing.size():way.size())-row_H;
		int add_nm=name.size()-row_H/2;
		add_cnt=(add_cnt>add_nm)?add_cnt:add_nm;
		int row_need=row_H+(add_cnt>0?add_cnt:0);
		if(prizn!=curr_prizn)
        	row_need++;
		if (row+row_need>row_end)
		{
			// �����������
			XL->Range_Copy(XL->GetRows(XL->GetSheet(Lcount+TemplPos), 10, 10));
			// �������
			XL->Sheet_activate();
			XL->Range_Paste(XL->GetRows(row, row));
			newpage=true;
		}

		if(newpage)
		{
			XL->Sheet_Copy(XL->GetSheet(Lcount+TemplPos),XL->GetSheet(Lcount+1), Variant().NoParam());
			Lcount++ ;
			XL->SetActiveSheet(XL->GetSheet(Lcount));

			XL->Set_Sheet_Name(XL->GetSheet(Lcount), "����-"+IntToStr(Lcount));
			// ������ �����/
			XL->toCells(head_row, 3,  date	);
			if (!ceu.Length())
			{
				XL->toCells(head_row, 9,  ""	);
				XL->toCells(head_row, 10,  ""	);
			}
			else
			{
            	XL->toCells(head_row, 10,  ceu	);
			}
			XL->toCells(head_row, 11, zak);
			XL->toCells(head_row, 12, part);
			XL->toCells(head_row, 16, Lcount);
			newpage=false;

			// �����������
			XL->Range_Copy(XL->GetRows( 14, 24));
			// �������
			XL->Range_Paste(XL->GetRows(4, 13));

			row=row_start;
		}

        // �������� �������� �����������
		if(prizn!=curr_prizn)
		{
			// �����������
			XL->Range_Copy(XL->GetRows(XL->GetSheet(Lcount+TemplPos), 8, 8));
			// �������
			XL->Sheet_activate();
			XL->Range_Paste(XL->GetRows(row, row));

			prizn=curr_prizn;
			//c���������� ������ ��� ������
			switch(prizn)
			{
			case 1:
				{
					XL->toCells(row, 1,"������ ���. ������ � ���. ������");
					break;
				}
			case 2:
				{
					XL->toCells(row, 1,"������������, ����., �������. ������");
					break;
				}
			default:
				break;
			}
			row++;
		}
        //���������� ������
		// �����������
		XL->Range_Copy(XL->GetRows(XL->GetSheet(Lcount+TemplPos), 5, 6));
		// �������
		XL->Sheet_activate();
		XL->Range_Paste(XL->GetRows(row, row+1));

		while (add_cnt>0)
		{
        	// �����������
			XL->Range_Copy(XL->GetRows(XL->GetSheet(Lcount+TemplPos), 6, 6));
			// �������
			XL->Sheet_activate();
			XL->Range_Paste(XL->GetRows(row+row_H+add_cnt-1, row+row_H+add_cnt-1));
			add_cnt--;
		}


		XL->toCells(row, 	1, npp++    );
		XL->toCells(row, 	2, obd		);
		//XL->toCells(row+1, 	2, name		);
		XL->toCells(row, 	6, kol_det	);

		sum_trud+=trud_common;
		XL->toCells(row, 	7, trud			);
		XL->toCells(row+1, 	7, trud_common	);

		int add_timing(0),add_way(0),add_name(0);
		for (int i = 0; i < name.size(); ++i)
		{
			XL->toCells(row+1+i,2, name.at(i));
			if ((i+1)>(row_H/2))
			{
            	add_name++;
			}
		}
		for (int i = 0; i < timing.size(); ++i)
		{
			XL->toCells(row+i,8, timing.at(i));
			if ((i+1)>row_H)
			{
            	add_timing++;
			}
		}
		for (int i = 0; i < way.size(); ++i)
		{
			XL->toCells(row+i,12, way.at(i));
			if ((i+1)>row_H)
			{
            	add_way++;
			}
		}
		int addrows=add_timing>add_way?add_timing:add_way;
		addrows=addrows>add_name?addrows:add_name;
		row+=row_H+addrows;
	}
	delete rez;
    if (no_data)
	{
		XL->Book_Close(XL->GetBook(1));
	}
	else
	{
		// �����������
		XL->Range_Copy(XL->GetRows(XL->GetSheet(Lcount+TemplPos), 12, 12));
		// �������
		XL->Sheet_activate();
		XL->Range_Paste(XL->GetRows(row, row));

		XL->toCells(row, 	7, sum_trud   	);

		sql = "Call temporary_tables.rp140006('"+GostToInt(obd)+"',"+String(kol)+",'"+ceu.SubString(1,2)+"','"+ceu.SubString(3,2)+"',1)";
		rez=DB->SendSQL(sql);
		if (rez)
		{
			String summary;
			for (rez->First(); !rez->Eof; rez->Next())
			{
				summary+=rez->FieldByName("oprid")->Value;
				summary+=" - ";
				summary+=rez->FieldByName("trud")->Value;
				summary+="  ";
			}
			XL->toCells(row, 	8, summary   	);
			delete rez;
		}

		for (int i= 1; i <= Lcount ; ++i)
		{
			XL->Sheet_activate(XL->GetSheet(i));
			XL->toCells(head_row,  19, Lcount );
		}

		while(Lcount&&Lcount<XL->GetSheetsCount())
		{
			XL->Sheet_Del(XL->GetSheet(XL->GetSheetsCount()));
		}
		XL->Sheet_activate(XL->GetFirstSheet());
	}
	XL->Visible(true);
}

void cReports::Cpu_Operation_Timing	(String obd,String zak,int kol,String ceu,String part) //140006
{
 	if (ceu.Length()!=4)
	{
        ShowMessage("�� ������ ���/�������");
		//return;
	}
//�������������
	AnsiString file=Templates+"manufacture_forms.xlt";
	XL->Connect();
	XL->DisplayAlerts(false);
	//XL->Visible(true);
	OpenTemplate(file);
	const int row_start=4, row_end=54, head_row=1;
	int Lcount=0,TemplPos=5;
	const int timing_len=37,way_len=25,name_len=30,obo_name_len=12,row_H=2;
	std::vector<String> timing,way,name,obo_name;


   	String sql = "Call temporary_tables.rp1400061('"+GostToInt(obd)+"',"+String(kol)+",'"+ceu.SubString(1,2)+"','"+ceu.SubString(3,2)+"',0)";
	TADOQuery *rez=DB->SendSQL(sql);
	if (!rez)
	{
		ShowMessage("������ ��� ���������� �������");
		return;
	}
	bool newpage=true;
	int row(row_start);
	double sum_trud=0.0;
	int prizn(0),npp(1);
	bool no_data=true;
	for (rez->First(); !rez->Eof; rez->Next())
	{
        no_data=false;
		String date=Now().FormatString("dd.mm.yy");
		String obd=VinToGost(rez->FieldByName("obd")->Value);
		int kol_det=rez->FieldByName("kol")->Value;

		double trud=rez->FieldByName("tsht")->Value;
		double trud_common=rez->FieldByName("tpart")->Value;

		String obo_opr = rez->FieldByName("obo_opr")->Value;
		String obo_id = rez->FieldByName("obo_id")->Value;

		WordWrap(way,Get_Rascex(obd),way_len);
		WordWrap(timing,rez->FieldByName("timing")->Value,timing_len,"  ");
		WordWrap(name,rez->FieldByName("namd")->Value,name_len);
		WordWrap(obo_name,rez->FieldByName("obo_name")->Value,obo_name_len);

		int curr_prizn=rez->FieldByName("prizn")->Value;

		//������� ��� �����
		int add_way=way.size()-row_H;
		int add_timing=timing.size()-row_H;
		int add_obo_nm=obo_name.size()-row_H;
		int add_nm=name.size()-row_H/2;

		int add_cnt=add_way>add_timing?add_way:add_timing;
			add_cnt=add_cnt>add_obo_nm?add_cnt:add_obo_nm;
			add_cnt=add_cnt>add_nm?add_cnt:add_nm;
		int row_need=row_H+(add_cnt>0?add_cnt:0);
		if(prizn!=curr_prizn)
			row_need++;
		if (row+row_need>row_end)
		{
			// �����������
			XL->Range_Copy(XL->GetRows(XL->GetSheet(Lcount+TemplPos), 10, 10));
			// �������
			XL->Sheet_activate();
			XL->Range_Paste(XL->GetRows(row, row));
			newpage=true;
		}

		if(newpage)
		{
			XL->Sheet_Copy(XL->GetSheet(Lcount+TemplPos),XL->GetSheet(Lcount+1), Variant().NoParam());
			Lcount++ ;
			XL->SetActiveSheet(XL->GetSheet(Lcount));

			XL->Set_Sheet_Name(XL->GetSheet(Lcount), "����-"+IntToStr(Lcount));
			// ������ �����/
			XL->toCells(head_row, 3,  date	);
			if (!ceu.Length())
			{
				XL->toCells(head_row, 9,  ""	);
				XL->toCells(head_row, 10,  ""	);
			}
			else
			{
            	XL->toCells(head_row, 10,  ceu	);
			}
			XL->toCells(head_row, 13, zak);
			XL->toCells(head_row, 14, part);
			XL->toCells(head_row, 19, Lcount);
			newpage=false;

			// �����������
			XL->Range_Copy(XL->GetRows( 14, 24));
			// �������
			XL->Range_Paste(XL->GetRows(4, 13));

			row=row_start;
		}

        // �������� �������� �����������
		if(prizn!=curr_prizn)
		{
			// �����������
			XL->Range_Copy(XL->GetRows(XL->GetSheet(Lcount+TemplPos), 8, 8));
			// �������
			XL->Sheet_activate();
			XL->Range_Paste(XL->GetRows(row, row));

			prizn=curr_prizn;
			//c���������� ������ ��� ������
			switch(prizn)
			{
			case 1:
				{
					XL->toCells(row, 1,"������ ���. ������ � ���. ������");
					break;
				}
			case 2:
				{
					XL->toCells(row, 1,"������������, ����., �������. ������");
					break;
				}
			default:
				break;
			}
			row++;
		}
        //���������� ������
		// �����������
		XL->Range_Copy(XL->GetRows(XL->GetSheet(Lcount+TemplPos), 5, 6));
		// �������
		XL->Sheet_activate();
		XL->Range_Paste(XL->GetRows(row, row+1));

		while (add_cnt>0)
		{
        	// �����������
			XL->Range_Copy(XL->GetRows(XL->GetSheet(Lcount+TemplPos), 6, 6));
			// �������
			XL->Sheet_activate();
			XL->Range_Paste(XL->GetRows(row+row_H+add_cnt-1, row+row_H+add_cnt-1));
			add_cnt--;
		}


		XL->toCells(row, 	1, npp++    );
		XL->toCells(row, 	2, obd		);
		//XL->toCells(row+1, 	2, name		);
		XL->toCells(row, 	6, kol_det	);

		sum_trud+=trud_common;
		XL->toCells(row, 	7, trud			);
		XL->toCells(row+1, 	7, trud_common	);
		XL->toCells(row, 	12,obo_opr		);
		XL->toCells(row, 	13,obo_id		);

		int fact_add_timing(0),fact_add_way(0),fact_add_name(0),fact_add_obo_name(0);
		for (int i = 0; i < name.size(); ++i)
		{
			XL->toCells(row+1+i,2, name.at(i));
			if ((i+1)>(row_H/2))
			{
				fact_add_name++;
			}
		}
		for (int i = 0; i < timing.size(); ++i)
		{
			XL->toCells(row+i,8, timing.at(i));
			if ((i+1)>row_H)
			{
				fact_add_timing++;
			}
		}
		for (int i = 0; i < way.size(); ++i)
		{
			XL->toCells(row+i,17, way.at(i));
			if ((i+1)>row_H)
			{
				fact_add_way++;
			}
		}
		for (int i = 0; i < obo_name.size(); ++i)
		{
			XL->toCells(row+i,16, obo_name.at(i));
			if ((i+1)>row_H)
			{
				fact_add_obo_name++;
			}
		}
		int addrows=fact_add_timing>fact_add_way?fact_add_timing:fact_add_way;
		addrows=addrows>fact_add_name?addrows:fact_add_name;
		addrows=addrows>fact_add_obo_name?addrows:fact_add_obo_name;
		row+=row_H+addrows;
	}
	delete rez;
	if (no_data)
	{
		XL->Book_Close(XL->GetBook(1));
		/*XL->Sheet_Add(XL->GetSheets(),XL->GetFirstSheet());
		while(1<XL->GetSheetsCount())
		{
			XL->Sheet_Del(XL->GetSheet(XL->GetSheetsCount()));
		}*/
	}
	else
	{
		// �����������
		XL->Range_Copy(XL->GetRows(XL->GetSheet(Lcount+TemplPos), 12, 12));
		// �������
		XL->Sheet_activate();
		XL->Range_Paste(XL->GetRows(row, row));

		XL->toCells(row, 	7, sum_trud   	);

		sql = "Call temporary_tables.rp1400061('"+GostToInt(obd)+"',"+String(kol)+",'"+ceu.SubString(1,2)+"','"+ceu.SubString(3,2)+"',1)";
		rez=DB->SendSQL(sql);
		if (rez)
		{
			String summary;
			for (rez->First(); !rez->Eof; rez->Next())
			{
				summary+=rez->FieldByName("oprid")->Value;
				summary+=" - ";
				summary+=rez->FieldByName("trud")->Value;
				summary+="  ";
			}
			XL->toCells(row, 	8, summary   	);
			delete rez;
		}

		for (int i= 1; i <= Lcount ; ++i)
		{
			XL->Sheet_activate(XL->GetSheet(i));
			XL->toCells(head_row,  22, Lcount );
		}

		while(Lcount&&Lcount<XL->GetSheetsCount())
		{
			XL->Sheet_Del(XL->GetSheet(XL->GetSheetsCount()));
		}
		XL->Sheet_activate(XL->GetFirstSheet());
    }
	XL->Visible(true);
}


void    cReports::WordWrap		(std::vector<String> &out,String in,const int max_len,String delimeter)
{
    out.clear();
	while (int len=in.Length())
	{
		if (max_len>=len)
		{
			out.push_back(in);
			in="";
		}
		else
		{
			int pos(0);
			int del_size=delimeter.Length();
			for (int i = max_len-(del_size-1); i != 0 && !pos; --i)
			{
				String s=in.SubString(i,del_size);
				if ( s == delimeter )
				{
                	pos=i;
				}
			}
			String s=in.SubString(1,pos?pos-1:max_len);
			if (s!="")
			{
				out.push_back(s);
			}
			in.Delete(1,pos?pos+(del_size-1):max_len);
		}
	}
}

String cReports::Get_Rascex(String obd)
{
	String OBD=GostToVin(obd);
	int id=0;
	TADOQuery *rez=DB->SendSQL("Call constructions.Get_id('"+OBD+"')");
	if(rez&&rez->RecordCount)
	{
		id=rez->FieldByName("id")->Value;
	}
	delete rez;
	String sql=
		"Select concat(cex,utch)as ceu,opr from technologic.operation_list where id='"+
		(String)id+"' order by opr", sql1=
		"Select napr,pm from technologic.det_info where id='"+(String)id+
		"'limit 0,1", sql2="Select sklad from sklad.materials where obmid='"+
		(String)id+"'", result="", last="";
	if(OBD.SubString(1, 9)=="000000000"&&OBD.Length()==15)
	{ // ���� ���������� �� ������������ �������
		rez=DB->SendSQL(sql);
		if(rez&&rez->RecordCount)
		{ // ���������� ����������
			for(rez->First(); !rez->Eof; rez->Next())
			{
				if(Trim(rez->FieldByName("ceu")->Value)!=""&&Trim
					(rez->FieldByName("ceu")->Value)!=last)
				{
					last=Trim(rez->FieldByName("ceu")->Value);
					result=result+last+" ";
				}
			}
		}
		else
		{
			delete rez;
			return result;
		}
		delete rez;
		rez=0;
		rez=DB->SendSQL(sql1);
		if(rez&&rez->RecordCount)
		{ // ����� �����������
			if(result=="")
			{
				result=Trim(rez->FieldByName("pm")->Value)+" ";
			}
			if(Trim(rez->FieldByName("napr")->Value)!=last)
			{
				last=Trim(rez->FieldByName("napr")->Value);
				result=result+last.Trim();
			}
		}
		else
		{
			delete rez;
			return result.Trim();
		}
		delete rez;
		rez=0;
		rez=DB->SendSQL(sql2);
		if(rez&&rez->RecordCount)
		{ // ����������� ������
			if(result=="")
			{
				result="1600?? "+Trim(rez->FieldByName("sklad")->Value);
			}
			else
			{
				if(Trim(rez->FieldByName("sklad")->Value)!=last)
				{
					last=Trim(rez->FieldByName("sklad")->Value);
					result=result+last;
				}
			}
		}
		else
		{
			result=result+"����???";
		}
	}
	else
	{
		rez=DB->SendSQL(sql);
		if(rez&&rez->RecordCount)
		{ // ����������
			for(rez->First(); !rez->Eof; rez->Next())
			{
				if(Trim(rez->FieldByName("ceu")->Value)!=""&&Trim
					(rez->FieldByName("ceu")->Value)!=last)
				{
					last=Trim(rez->FieldByName("ceu")->Value);
					result=result+last+" ";
				}
			}
		}
		else
		{
			delete rez;
			return result;
		}
		delete rez;
		rez=0;
		rez=DB->SendSQL(sql1);
		if(rez&&rez->RecordCount)
		{
			for(rez->First(); !rez->Eof; rez->Next())
			{
				if(result=="")
				{
					result=Trim(rez->FieldByName("pm")->Value)+" ";
				}
				if(Trim(rez->FieldByName("napr")->Value)!=last)
				{
					last=Trim(rez->FieldByName("napr")->Value);
					result=result+last.Trim();
				}
			}
		}
		else
		{
			result=result+"����???";
		}
		delete rez;
		rez=0;
	}

	return result.Trim();
}
