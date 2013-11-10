#pragma hdrstop

#include "ComPort.h"

#pragma package(smart_init)
//������������ /����������
		COMPort::COMPort (const wchar_t * const portName,
							COMMTIMEOUTS *_Timeouts,
							unsigned int CommMask,
							unsigned int InputBuffer,
							unsigned int Outputbuffer)
{
	ComDCM=0;
	port_name=portName;
	PortHandle =CreateFileW(portName,GENERIC_READ | GENERIC_WRITE,0,NULL,OPEN_EXISTING,
						FILE_ATTRIBUTE_NORMAL,NULL);
	if (PortHandle == (HANDLE)-1)
		{
			PortHandle = 0;
			throw Exception("COMPort: failed to open.");
		}
	SetCommMask(PortHandle, CommMask);
	SetupComm(PortHandle, InputBuffer, Outputbuffer);

	TimeOuts=_Timeouts;
	if(!SetCommTimeouts(PortHandle, TimeOuts))
	{
		PortHandle = 0;
		throw Exception("������ ��������� COMMTIMEOUTS");
	}
}
		COMPort::COMPort ( const wchar_t * const portName )
{
	ComDCM=0;
	port_name=portName;
	PortHandle =CreateFileW(portName,GENERIC_READ | GENERIC_WRITE,0,NULL,OPEN_EXISTING,
						FILE_ATTRIBUTE_NORMAL,NULL);

	if (PortHandle == (HANDLE)-1)
	{
		PortHandle = 0;
		throw Exception("COMPort: failed to open.");
	}

	SetCommMask(PortHandle, EV_RXCHAR);
	SetupComm(PortHandle, 1024, 1024);

	TimeOuts=new COMMTIMEOUTS();
	TimeOuts->ReadIntervalTimeout = 0xFFFFFFFF;
	TimeOuts->ReadTotalTimeoutMultiplier = 0;
	TimeOuts->ReadTotalTimeoutConstant = 0;
	TimeOuts->WriteTotalTimeoutMultiplier = 0;
	TimeOuts->WriteTotalTimeoutConstant =0;

	if(!SetCommTimeouts(PortHandle, TimeOuts))
	{
		PortHandle = 0;
		throw Exception("������ ��������� COMMTIMEOUTS");
	}
	if (!Set_DCB_Settings(BR_9600,NOparity,OFF,ONE))
	{
		CloseHandle(PortHandle);
		PortHandle = 0;
		throw Exception("������ ��������� DCB");
	}
}
		COMPort::~COMPort()
{
	// close serial port device
	//delete []port_name;
	delete ComDCM;
	delete TimeOuts;
	if (!CloseHandle (PortHandle))
	{
	   throw Exception("COMPort: failed to close.");
	}
}
//��������� �����
bool 	COMPort::Set_DCB_Settings(BaudRates BaudRate,Patitys patity,fPatitys f_parity,StopBits stop_bits)
{
	if (!ComDCM)
	{
		ComDCM=Get_port_Settings();
	}
	ComDCM->BaudRate =BaudRate;
	ComDCM->ByteSize = 8;
	ComDCM->Parity = patity;
	ComDCM->StopBits = stop_bits;
	ComDCM->fAbortOnError = FALSE;
	ComDCM->fDtrControl = DTR_CONTROL_DISABLE;
	ComDCM->fRtsControl = RTS_CONTROL_DISABLE;
	ComDCM->fBinary = TRUE;
	ComDCM->fParity = f_parity;
	ComDCM->fInX = FALSE;
	ComDCM->fOutX = FALSE;
	ComDCM->XonChar = (unsigned char)0x11;
	ComDCM->XoffChar = (unsigned char)0x13;
	ComDCM->fErrorChar = FALSE;
	ComDCM->fNull = FALSE;
	ComDCM->fOutxCtsFlow = FALSE;
	ComDCM->fOutxDsrFlow = FALSE;
	ComDCM->XonLim = 1024;
	ComDCM->XoffLim = 1024;
	ComDCM->fDsrSensitivity=FALSE;
	return SetCommState(PortHandle, ComDCM);
}
bool 	COMPort::Set_DCB_Settings(DCB * DCB_Settings)
{
	if (ComDCM)
	{
		delete ComDCM;
	}
	ComDCM=DCB_Settings;
	return SetCommState(PortHandle, ComDCM);
}
//���������� � �����
bool 	COMPort::IsOK() const
{
	return PortHandle != 0;
}
DCB * 	COMPort::Get_port_Settings(void)
{
	DCB *Result=new DCB();
	Result->DCBlength = sizeof(DCB);
	GetCommState(PortHandle, Result);
	return Result;
}
 //����� ������/��������
void 	COMPort::Write	(const BYTE* buff,	size_t len)
{
	DWORD feedback;
	if(!WriteFile(PortHandle, buff, len, &feedback, 0) || feedback !=len)
	{
		throw Exception("������ ������");
	}
	// In some cases it's worth uncommenting
	//FlushFileBuffers(m_Handle);
 }
void 	COMPort::Read(BYTE *buff,	size_t &len)
{
	//DWORD begin = GetTickCount();
	DWORD feedback =0;

	if(!ReadFile(PortHandle, buff,len, &feedback, NULL))
	{
		throw Exception("������ ������");
	}
	len=feedback;
}
bool 	COMPort::Clear_Com_Buff	(Purge_flags flags)
{
	return PurgeComm(PortHandle,flags);
}
//���������� ������ �����
bool 	COMPort::DTR_On(unsigned int w8_before,unsigned int w8_after)
{
	if (w8_before)
	{
		Sleep(w8_before);
	}
	bool result=EscapeCommFunction(PortHandle,SETDTR);
	if (w8_after)
	{
		Sleep(w8_after);
	}
	return result;
}
bool 	COMPort::DTR_oFF(unsigned int w8_before,unsigned int w8_after)
{
	if (w8_before)
	{
		Sleep(w8_before);
	}
	bool result=EscapeCommFunction(PortHandle,CLRDTR);
	if (w8_after)
	{
		Sleep(w8_after);
	}
	return result;
}
