#define _WINSOCK_DEPRECATED_NO_WARNINGS

#pragma comment (lib, "ws2_32.lib")
#include <stdio.h>
#include <WinSock2.h>

void main(void)
{
	WSADATA wsaData;
	SOCKET ListeningSocket;
	
	SOCKADDR_IN ServerAddr;
	int	Port = 5150;

	SOCKADDR_IN ClientAddr;
	int	ClientAddrLen;
	SOCKET	NewConnection;

	char		DataBuffer[1024];

	int	Ret;


/*
* ��ʼ�� Winsock ��ĺ�����
int WSAStartup(
  WORD      wVersionRequested,//����� Winsock �汾��ͨ������ MAKEWORD(2, 2) ��ʾ���� Winsock 2.2 �汾��
  LPWSADATA lpWSAData//ָ�� WSADATA �ṹ��ָ�룬���ڽ��չ��� Winsock ʵ�ֵ���Ϣ��
);
*/  	
	if ((Ret = WSAStartup(MAKEWORD(2, 2), &wsaData)) != 0) {
		printf("WSAStartup failed with error %d\n", Ret);
		return;
	}

/*
* �����׽���
int socket(int domain,//�׽���ʹ�õ�Э���壨��ַ�壩��
int type,//�׽��ֵ����ͣ������� SOCK_STREAM�����׽��֣��� TCP���� SOCK_DGRAM�����ݱ��׽��֣��� UDP���ȡ�
int protocol);//�׽���ʹ�õľ���Э�飬ͨ������ 0����ʾʹ��Ĭ��Э�顣
*/                               //IPv4     //TCP       //��ʾʹ�� TCP Э��
	if ((ListeningSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET) {
		printf("socket failed with error %d \n",WSAGetLastError());
		WSACleanup();//���� Windows �׽��ֿ�ĺ�����
		return;
	}


	ServerAddr.sin_family = AF_INET;//���÷������׽��ֵĵ�ַ�塣AF_INET ��Ӧ������ IPv4 �Ļ�������ַ�塣
	ServerAddr.sin_port = htons(Port);//�����˷������˿ڡ�htons �������˿ںŴ������ֽ�˳��ת��Ϊ�����ֽ�˳��
	ServerAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);//���÷������� IP ��ַ��INADDR_ANY ��ʾ������Ը������κο�������ӿ��ϵ����ӡ�
	
/*
* ��һ���׽��ְ󶨵�һ���ض��ĵ�ַ��IP ��ַ�Ͷ˿ںţ�
int bind(
  SOCKET         s,//Ҫ�󶨵��׽��֡�
  const sockaddr *name,//ָ�� sockaddr �ṹ��ָ�룬���а���Ҫ�󶨵��ĵ�ַ��Ϣ��
  int            namelen//name �ṹ�ĳ��ȡ�
);
*/
	if (bind(ListeningSocket, (SOCKADDR*)&ServerAddr, sizeof(ServerAddr)) == SOCKET_ERROR) {
		printf("bind failed with error %d\n", WSAGetLastError()); closesocket(ListeningSocket);
		WSACleanup();
		return;
	}

/*
* ���׽��ֱ��Ϊ����״̬��ʹ����Խ�����������
int listen(
  SOCKET s,//Ҫ�������׽��֡�
  int    backlog//�����ڶ����еȴ������ӵ������Ŀ��
);
*/
	if (listen(ListeningSocket, 5) == SOCKET_ERROR) {
		printf("listen failed with error %d\n", WSAGetLastError()); 
		closesocket(ListeningSocket);
		WSACleanup();
		return;
	}


	printf("We are waiting a connection on port %d.\n", Port);
	printf("Listen(���ڼ���)...\n");


/*
* ����һ���µ����ӡ�
SOCKET accept(
  SOCKET   s,//Ҫ�������ӵļ����׽��֡�
  sockaddr *addr,//���ڴ洢���ӷ���ַ��Ϣ�Ļ�������
  int      *addrlen// �������ĳ��ȣ����ú�����Ϊʵ�ʵ�ַ���ȡ�
);
*/
	ClientAddrLen = sizeof(SOCKADDR);
	if ((NewConnection = accept(ListeningSocket, (SOCKADDR*)&ClientAddr, &ClientAddrLen)) == INVALID_SOCKET)
	{
		printf("accept failed with error %d\n", WSAGetLastError());
		closesocket(ListeningSocket);
		WSACleanup();
		return;
	}

	printf("We successfully got a connection from %s:%d \n",inet_ntoa(ClientAddr.sin_addr), ntohs(ClientAddr.sin_port));



	closesocket(ListeningSocket);   //ֻ����һ���ͻ�������
	printf("We are waiting to receive data\n");

/*
* ���ڽ������ݡ�
int recv(
  SOCKET s,//Ҫ�������ݵ��׽��֡�
  char   *buf,//���ڴ洢�������ݵĻ�������
  int    len,//�������ĳ��ȡ�
  int    flags//��־������ͨ����������Ϊ 0��
);
*/
	if ((Ret=recv(NewConnection, DataBuffer,sizeof(DataBuffer), 0)) == SOCKET_ERROR) {
		printf("recv failed with error %d\n", WSAGetLastError());
		closesocket(NewConnection);
		WSACleanup();
		return;
	}

	printf("We successfully received %d bytes.\n", Ret);
	DataBuffer[Ret] = '\O';
	printf("%s\n",DataBuffer);
	printf("We are now going to close the client connection.\n");
	closesocket(NewConnection);
	WSACleanup();

	system(" pause");
}