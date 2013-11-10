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
		Success=0, //�������� ����������
		//������
		Wrong_prot_or_type=1,			//�������� �������� ��� ��� ����������
		Wrong_protocol=2,               //�������� ��������
		Wrong_type=3,                   //�������� ��� ����������
		Socet_system_initialize_error=4,//��������� ���������������� ������� �������
		Overflow_socket_list=5,			//������������ ������ �������
		Can_not_create_socket=6,        //������ ��� �������� ������
		Wrong_addr=7,             		//�������� �����
		Cannot_connect=8,				//��������� ������������
		Cannot_create_server=9,			//��������� ������� ������
		Listen_Error=10,				//������ ��� ������������� �������� �� �����������
		Socket_Error=11                 //������ ������ (������� ����������)
		};
	class Ethernet
		{
		public:
			Ethernet (eProt _protocol,eType _type,u_short _tg_port,u_short _my_port,const char *_tg_addr);
			~Ethernet(void);
			eErrCode 	Connect(void);     //������� ������������� �����������
			void 		Disconnect(void); //������� ��� ������� ���� �����������
			eErrCode 	Send_data(const char *_buff,u_int size, const sockaddr_in & client);  //������� �������� ���������
			eErrCode 	Get_data(char **_buff,u_int &size,sockaddr_in & client);     //������� ��������� ������
			sockaddr_in Get_Dest_addr_data (void) {return dest_addr;};//����������� ������ �� ������ ���������� ����� ����� ���� �������� � ���
		private:
			//��������� ����������
			eProt c_protocol;	//�������� ����������
			eType c_type;		//��� ���������� (������ / ������)
			//������ ����������
			SOCKET  server_socket;//����� �������/����������� � �������
			SOCKET	client_socket;//����� ������������� �������
			//������ ���� ����������
			HOSTENT *host;
			sockaddr_in dest_addr;

			u_short my_port;//���� ���������� ���������
			u_short tg_port;//���� ���������� c �����
			const char *tg_addr;//������ ���������� ip/host ����� ����




			eErrCode Connect_TCP_Client(void); //������������ ��� tcp ������ � �������
			eErrCode Connect_UDP_Client(void); //������������ ��� udp ������ � �������
			eErrCode Create_TCP_Server(void); //��������� tcp ������ ������� ����������� ��������
			eErrCode Create_UDP_Server(void); //��������� udp ������ ������� ����������� ��������
			void Disconnect(SOCKET  &_socket);//������� ��� ������� ���������� � �������

			eErrCode AddSocket (eProt protocol);//������� ���������� ������ ������
		};
	};
#endif
