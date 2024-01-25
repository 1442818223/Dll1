#define _WINSOCK_DEPRECATED_NO_WARNINGS

#pragma comment (lib, "ws2_32.lib")   // 链接到 Winsock 库
#include <stdio.h>
#include <WinSock2.h>

void main(void)
{
	WSADATA wsaData;   // 用于存储 Winsock 库的信息
	SOCKET ReceivingSocket;  // 接收数据的套接字句柄
	SOCKADDR_IN ReceiverAddr;  // 服务器地址结构
	SOCKADDR_IN SenderAddr;    // 发送者地址结构
	int SenderAddrSize;        // 发送者地址结构的大小
	SenderAddrSize = sizeof(SenderAddr);

	int Ret;

	// 初始化 Winsock 库
	if ((Ret = WSAStartup(MAKEWORD(2, 2), &wsaData)) != 0)
	{
		printf("WSAStartup failed with error %d\n", Ret);
		return;
	}
	else
	{
		if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) // 判断版本是否正确
		{
			printf("Error: not winsock 2.2\n");
			WSACleanup();
			return;
		}
	}

	// 创建 UDP 套接字
	if ((ReceivingSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == INVALID_SOCKET)
	{
		printf("ERROR: socket failed with error %d\n", WSAGetLastError());
		WSACleanup();
		return;
	}

	ReceiverAddr.sin_family = AF_INET;  // IPv4
	ReceiverAddr.sin_port = htons(5150);  // 服务器端口号
	ReceiverAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);  // 任何发送过来的 IP 都可以

	// 将套接字绑定到服务器地址
	if (bind(ReceivingSocket, (SOCKADDR*)&ReceiverAddr, sizeof(ReceiverAddr)) == SOCKET_ERROR)
	{
		printf("ERROR: bind failed with error %d\n", WSAGetLastError());
		closesocket(ReceivingSocket);
		WSACleanup();
		return;
	}

	while (1)
	{
		char buffer[1024] = "\0";
		printf("waiting for message from others...\n");

		// 接收来自客户端的数据
		if (recvfrom(ReceivingSocket, buffer, sizeof(buffer), 0, (SOCKADDR*)&SenderAddr, &SenderAddrSize) == SOCKET_ERROR)
		{
			printf("Error: recvfrom failed with error %d\n", WSAGetLastError());
			closesocket(ReceivingSocket);
			WSACleanup();
			return;
		}
		else
		{
			printf("Received datagram from %s -- %s\n", inet_ntoa(SenderAddr.sin_addr), buffer);

			// 将收到的数据原样发送回客户端
			sendto(ReceivingSocket, buffer, sizeof(buffer), 0, (SOCKADDR*)&SenderAddr, SenderAddrSize);
		}

		Sleep(500);  // 暂停一段时间，避免过于频繁的输出
	}

	closesocket(ReceivingSocket);
	WSACleanup();
}
