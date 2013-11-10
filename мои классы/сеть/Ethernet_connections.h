//---------------------------------------------------------------------------

#ifndef Ethernet_connectionsH
#define Ethernet_connectionsH
#include 	<winsock2.h>
#include   	<Iphlpapi.h>
#include 	<cstring.h>

//---------------------------------------------------------------------------
namespace my_ethernet_connections
	{
	const u_int BUFF_SIZE=1024;
	enum eProt {eUDP=0,eTCP=1};
	enum eType {eClient=0,eServer=2};
	enum  eErrCode
		{
		Success=0, //успешное выполнение
		//ошибки
		Wrong_prot_or_type=1,			//неверные протокол или тип соединения
		Wrong_protocol=2,               //неверный протокол
		Wrong_type=3,                   //неверный тип соединения
		Socet_system_initialize_error=4,//Неудалось инициализировать систему сокетов
		Overflow_socket_list=5,			//переполнение списка сокетов
		Can_not_create_socket=6,        //ошибка при создании сокета
		Wrong_addr=7,             		//неверный адрес
		Cannot_connect=8,				//неудалось подключиться
		Cannot_create_server=9,			//неудалось создать сервер
		Listen_Error=10,				//ошибка при прослушивании запросов на подключение
		Socket_Error=11                 //ошибка сокета (закрыто соединение)
		};
	class Ethernet
		{
		public:
			Ethernet (eProt _protocol,eType _type,u_short _tg_port,u_short _my_port,const char *_tg_addr);
			~Ethernet(void);
			eErrCode 	Connect(void);     //функция инициализации подключения
			void 		Disconnect(void); //функция для разрыва всех подключений
			eErrCode 	Send_data(const char *_buff,u_int size, const sockaddr_in & client);  //функция отправки сообщения
			eErrCode 	Get_data(char **_buff,u_int &size,sockaddr_in & client);     //функция получения данных
			sockaddr_in Get_Dest_addr_data (void) {return dest_addr;};//возвращение данных по адресу назначения чтобы можно было работать с удп
		private:
			//параметры соединения
			eProt c_protocol;	//протокол соединения
			eType c_type;		//тип соединения (клиент / сервер)
			//адреса соединения
			SOCKET  server_socket;//сокет сервера/подключения к серверу
			SOCKET	client_socket;//сокет подключенного клиента
			//данные узла назначения
			HOSTENT *host;
			sockaddr_in dest_addr;

			u_short my_port;//порт соединения программы
			u_short tg_port;//порт соединения c целью
			const char *tg_addr;//строка содержащая ip/host адрес цели




			eErrCode Connect_TCP_Client(void); //подключается как tcp клиент к серверу
			eErrCode Connect_UDP_Client(void); //подключается как udp клиент к серверу
			eErrCode Create_TCP_Server(void); //создается tcp сервер одидает подключений клиентов
			eErrCode Create_UDP_Server(void); //создается udp сервер одидает подключений клиентов
			void Disconnect(SOCKET  &_socket);//функция для разрыва соединения с сокетом

			eErrCode AddSocket (eProt protocol);//функция добавления нового сокета
		};
	};
#endif
