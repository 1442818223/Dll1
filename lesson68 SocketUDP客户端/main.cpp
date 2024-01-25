#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#pragma comment (lib, "ws2_32.lib")   // 链接到 Winsock 库
#include <stdio.h>
#include <WinSock2.h>

void main(int argc, char** argv)
{
	WSADATA wsaData;   // 用于存储 Winsock 库的信息
	SOCKET SendingSocket;  // 发送数据的套接字句柄
	SOCKADDR_IN ReceiverAddr;  // 接收方地址结构
	int ReceiverAddrSize = sizeof(ReceiverAddr);

	if (argc <= 1) {
		printf("参数不够!!\n");
		system("pause");
		return;
	}

	// 初始化 Winsock 库
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	// 创建 UDP 套接字
	SendingSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	ReceiverAddr.sin_family = AF_INET;  // IPv4
	ReceiverAddr.sin_port = htons(5150);  // 服务器端口号
	ReceiverAddr.sin_addr.S_un.S_addr = inet_addr(argv[1]);  // 服务器 IP 地址

	while (1) {
		char buffer[1024] = "\0";
		printf(" Input message \n");
		scanf("%s", buffer);

		if (strcmp(buffer, "bye") == 0)
			break;

		// 发送数据到服务器
		if (sendto(SendingSocket, buffer, sizeof(buffer), 0, (SOCKADDR*)&ReceiverAddr, sizeof(ReceiverAddr)) != SOCKET_ERROR)
		{
			// 接收服务器的响应
			if (recvfrom(SendingSocket, buffer, sizeof(buffer), 0, (SOCKADDR*)&ReceiverAddr, &ReceiverAddrSize) != SOCKET_ERROR)
			{
				printf("Received from server: %s\n", buffer);
			}
		}
	}

	closesocket(SendingSocket);
	WSACleanup();
}
