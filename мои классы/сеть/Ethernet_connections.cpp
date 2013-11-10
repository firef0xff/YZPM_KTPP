#pragma hdrstop
#include "Ethernet_connections.h"

#pragma package(smart_init)
using namespace my_ethernet_connections;

			Ethernet::Ethernet (eProt _protocol,eType _type,u_short _tg_port,u_short _my_port,const char *_tg_addr)
{
c_protocol=_protocol;
c_type=_type;
tg_port=_tg_port;
my_port=_my_port;
tg_addr=_tg_addr;
server_socket=0;
client_socket=0;
}
			Ethernet::~Ethernet(void)
{
Disconnect();
}
eErrCode	Ethernet::Connect(void)
{
eErrCode result=eErrCode::Success;
if (server_socket)// проверка на открыты сокеты если таковые имеются то очистка
	{
	Disconnect();
	}
WSAData info;  //инициализация библиотеки сокетов
if (WSAStartup(0x202,(WSAData*)&info))
	{
    result=eErrCode::Socet_system_initialize_error;
	}  //создание сокета
if (result==eErrCode::Success)
	{
	result=AddSocket(c_protocol);
	if (result==eErrCode::Success)
		{ //подключение
		switch (c_protocol+c_type)
			{
			case 0:{result=Connect_UDP_Client(); break;}
			case 1:{result=Connect_TCP_Client(); break;}
			case 2:{result=Create_UDP_Server(); break;}
			case 3:{result=Create_TCP_Server(); break;}
			default: result=eErrCode::Wrong_prot_or_type;
			}
		}
	}
return result;
}
eErrCode	Ethernet::Connect_TCP_Client(void)
{
eErrCode result=eErrCode::Success;

//создание и проверка адреса
dest_addr.sin_family=AF_INET;
dest_addr.sin_port=htons(tg_port);
//проверка правильность ip адреса
if (inet_addr(tg_addr)!=INADDR_NONE)
	{
	dest_addr.sin_addr.s_addr=inet_addr(tg_addr);
	}else
	{ //попытка работать с доменным адресом
	if (host=gethostbyname(tg_addr))
		{
		((unsigned long *)&dest_addr.sin_addr)[0]=((unsigned long **)host->h_addr_list)[0][0];
		}else
		{
		result=eErrCode::Wrong_addr;
		Disconnect(server_socket);
		}
	}
if (result==eErrCode::Success)
	{   //попытка подключиться
	if (connect (server_socket,(sockaddr *)&dest_addr,sizeof(dest_addr)))
		{ //при неудачной попытке
		result=eErrCode::Cannot_connect;
		Disconnect(server_socket);
		}
	}

return result;
}
eErrCode	Ethernet::Connect_UDP_Client(void)
{
eErrCode result=eErrCode::Success;
//создание и проверка адреса
dest_addr.sin_family=AF_INET;
dest_addr.sin_port=htons(tg_port);
//проверка правильность ip адреса
if (inet_addr(tg_addr)!=INADDR_NONE)
	{
	dest_addr.sin_addr.s_addr=inet_addr(tg_addr);
	}else
	{ //попытка работать с доменным адресом
	if (host=gethostbyname(tg_addr))
		{
		((unsigned long *)&dest_addr.sin_addr)[0]=((unsigned long **)host->h_addr_list)[0][0];
		}else
		{
		result=eErrCode::Wrong_addr;
		Disconnect(server_socket);
		}
	}
return result;
}
eErrCode	Ethernet::Create_TCP_Server(void)
{
eErrCode result=eErrCode::Success;

//создание и проверка адреса севера локальные данные
sockaddr_in local_addr;
local_addr.sin_family=AF_INET;
local_addr.sin_port=htons(my_port);  //порт приема
local_addr.sin_addr.s_addr=0;        //прием на все адреса

// вызываем bind для связывания
if (bind(server_socket,(sockaddr *)&local_addr,sizeof(local_addr)))
	{
	result=Cannot_create_server;
	}
//ожидание подключения клиента
if (result==eErrCode::Success)
	{
	if (listen(server_socket,1))
		{
		result=eErrCode::Listen_Error;
		}
	}
//извлечение данных клиента
if (result==eErrCode::Success)
	{
	sockaddr_in client_addr; // адрес клиента
	int client_addr_size=sizeof(client_addr); //размер адреса клиента
	client_socket=accept(server_socket,(sockaddr *)&client_addr,&client_addr_size);
	}
return result;
}
eErrCode	Ethernet::Create_UDP_Server(void)
{
eErrCode result=eErrCode::Success;

//создание и проверка адреса севера локальные данные
sockaddr_in local_addr;
local_addr.sin_family=AF_INET;
local_addr.sin_port=htons(my_port);  //порт приема
local_addr.sin_addr.s_addr=0;        //прием на все адреса
// вызываем bind для связывания
if (bind(server_socket,(sockaddr *)&local_addr,sizeof(local_addr)))
	{
	result=Cannot_create_server;
	}
return result;
}

eErrCode	Ethernet::AddSocket (eProt protocol)
{
eErrCode result=eErrCode::Success;
//создание сокета
int prot=0;
//определени протокола
switch (c_protocol)
	{
	case eProt::eTCP:{prot=SOCK_STREAM;break;}
	case eProt::eUDP:{prot=SOCK_DGRAM;break;}
	default: result=eErrCode::Wrong_protocol;
	}
if (result==eErrCode::Success)
	{
	//созданние соета и помещение его в массив
	server_socket=socket(AF_INET,prot,0);
	if (server_socket==INVALID_SOCKET)
		{
		server_socket=0;
		result=eErrCode::Can_not_create_socket;
		}
	}
return result;
}

void		Ethernet::Disconnect(void)
{
//разрыв всех соединений
Disconnect(server_socket);
Disconnect(client_socket);
WSACleanup();
}
void		Ethernet::Disconnect(SOCKET  &_socket)
{
closesocket(_socket);
_socket=0;
}

eErrCode	Ethernet::Send_data(const char *_buff,u_int size, const sockaddr_in & client)
{
eErrCode result=eErrCode::Success;
SOCKET send_sock;//сокет по которому будет сделана отправка
switch (c_type+c_protocol)
	{
	case 0:{send_sock=server_socket; break;}
	case 1:{send_sock=server_socket; break;}
	case 2:{send_sock=server_socket; break;}
	case 3:{send_sock=client_socket; break;}
	default:result=eErrCode::Wrong_prot_or_type;
	}
if (result==eErrCode::Success)
	{
	switch (c_protocol)
		{
		case eProt::eTCP:{send(send_sock,_buff,size,0);break;}
		case eProt::eUDP:{sendto(send_sock,_buff,size,0,(sockaddr *) &client,sizeof(client));break;}
		default: result=eErrCode::Wrong_protocol;
		}
	}
return result;
}
eErrCode	Ethernet::Get_data(char **_buff,u_int &size,sockaddr_in & client)
{
eErrCode result=eErrCode::Success;
SOCKET get_sock;//сокет по которому будет сделана отправка
switch (c_type+c_protocol)
	{
	case 0:{get_sock=server_socket; break;}
	case 1:{get_sock=server_socket; break;}
	case 2:{get_sock=server_socket; break;}
	case 3:{get_sock=client_socket; break;}
	default:result=eErrCode::Wrong_prot_or_type;
	}
if (result==eErrCode::Success)
	{
	int bytes_get=0;//получено байтов
	char __buff[BUFF_SIZE]="";  //максимальный размер буфера 1024 символа
	int client_address_size=sizeof(client);

	switch (c_protocol)
		{
		case eProt::eTCP:{bytes_get=recv(get_sock,&__buff[0],sizeof(__buff),0);break;}
		case eProt::eUDP:{bytes_get=recvfrom(get_sock,&__buff[0],sizeof(__buff)-1,0,(sockaddr *) &client, &client_address_size);break;}
		default: result=eErrCode::Wrong_protocol;
		}
	if (*_buff)
		{
		delete [] *_buff;
		}
	if (bytes_get!=SOCKET_ERROR)
		{
		*_buff=new char[bytes_get+1];
		strcpy(*_buff,__buff);
		size=bytes_get+1;
		}else
		{
		*_buff=new char[1];
		*_buff="";
		result=eErrCode::Socket_Error;
		}
	}
return result;
}
