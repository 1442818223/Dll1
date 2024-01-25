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
* 初始化 Winsock 库的函数。
int WSAStartup(
  WORD      wVersionRequested,//请求的 Winsock 版本，通常传入 MAKEWORD(2, 2) 表示请求 Winsock 2.2 版本。
  LPWSADATA lpWSAData//指向 WSADATA 结构的指针，用于接收关于 Winsock 实现的信息。
);
*/  	
	if ((Ret = WSAStartup(MAKEWORD(2, 2), &wsaData)) != 0) {
		printf("WSAStartup failed with error %d\n", Ret);
		return;
	}

/*
* 创建套接字
int socket(int domain,//套接字使用的协议族（地址族）。
int type,//套接字的类型，可以是 SOCK_STREAM（流套接字，如 TCP）或 SOCK_DGRAM（数据报套接字，如 UDP）等。
int protocol);//套接字使用的具体协议，通常传入 0，表示使用默认协议。
*/                               //IPv4     //TCP       //表示使用 TCP 协议
	if ((ListeningSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET) {
		printf("socket failed with error %d \n",WSAGetLastError());
		WSACleanup();//清理 Windows 套接字库的函数。
		return;
	}


	ServerAddr.sin_family = AF_INET;//设置服务器套接字的地址族。AF_INET 对应于用于 IPv4 的互联网地址族。
	ServerAddr.sin_port = htons(Port);//设置了服务器端口。htons 函数将端口号从主机字节顺序转换为网络字节顺序
	ServerAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);//设置服务器的 IP 地址。INADDR_ANY 表示服务器愿意接受任何可用网络接口上的连接。
	
/*
* 将一个套接字绑定到一个特定的地址（IP 地址和端口号）
int bind(
  SOCKET         s,//要绑定的套接字。
  const sockaddr *name,//指向 sockaddr 结构的指针，其中包含要绑定到的地址信息。
  int            namelen//name 结构的长度。
);
*/
	if (bind(ListeningSocket, (SOCKADDR*)&ServerAddr, sizeof(ServerAddr)) == SOCKET_ERROR) {
		printf("bind failed with error %d\n", WSAGetLastError()); closesocket(ListeningSocket);
		WSACleanup();
		return;
	}

/*
* 将套接字标记为监听状态，使其可以接受连接请求
int listen(
  SOCKET s,//要监听的套接字。
  int    backlog//定义在队列中等待的连接的最大数目。
);
*/
	if (listen(ListeningSocket, 5) == SOCKET_ERROR) {
		printf("listen failed with error %d\n", WSAGetLastError()); 
		closesocket(ListeningSocket);
		WSACleanup();
		return;
	}


	printf("We are waiting a connection on port %d.\n", Port);
	printf("Listen(正在监听)...\n");


/*
* 接受一个新的连接。
SOCKET accept(
  SOCKET   s,//要接受连接的监听套接字。
  sockaddr *addr,//用于存储连接方地址信息的缓冲区。
  int      *addrlen// 缓冲区的长度，调用后会更新为实际地址长度。
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



	closesocket(ListeningSocket);   //只接收一个客户端连接
	printf("We are waiting to receive data\n");

/*
* 用于接收数据。
int recv(
  SOCKET s,//要接收数据的套接字。
  char   *buf,//用于存储接收数据的缓冲区。
  int    len,//缓冲区的长度。
  int    flags//标志参数，通常可以设置为 0。
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