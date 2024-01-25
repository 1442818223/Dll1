#define _WINSOCK_DEPRECATED_NO_WARNINGS

#pragma comment (lib, "ws2_32.lib")   // ���ӵ� Winsock ��
#include <stdio.h>
#include <WinSock2.h>

void main(void)
{
	WSADATA wsaData;   // ���ڴ洢 Winsock �����Ϣ
	SOCKET ReceivingSocket;  // �������ݵ��׽��־��
	SOCKADDR_IN ReceiverAddr;  // ��������ַ�ṹ
	SOCKADDR_IN SenderAddr;    // �����ߵ�ַ�ṹ
	int SenderAddrSize;        // �����ߵ�ַ�ṹ�Ĵ�С
	SenderAddrSize = sizeof(SenderAddr);

	int Ret;

	// ��ʼ�� Winsock ��
	if ((Ret = WSAStartup(MAKEWORD(2, 2), &wsaData)) != 0)
	{
		printf("WSAStartup failed with error %d\n", Ret);
		return;
	}
	else
	{
		if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) // �жϰ汾�Ƿ���ȷ
		{
			printf("Error: not winsock 2.2\n");
			WSACleanup();
			return;
		}
	}

	// ���� UDP �׽���
	if ((ReceivingSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == INVALID_SOCKET)
	{
		printf("ERROR: socket failed with error %d\n", WSAGetLastError());
		WSACleanup();
		return;
	}

	ReceiverAddr.sin_family = AF_INET;  // IPv4
	ReceiverAddr.sin_port = htons(5150);  // �������˿ں�
	ReceiverAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);  // �κη��͹����� IP ������

	// ���׽��ְ󶨵���������ַ
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

		// �������Կͻ��˵�����
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

			// ���յ�������ԭ�����ͻؿͻ���
			sendto(ReceivingSocket, buffer, sizeof(buffer), 0, (SOCKADDR*)&SenderAddr, SenderAddrSize);
		}

		Sleep(500);  // ��ͣһ��ʱ�䣬�������Ƶ�������
	}

	closesocket(ReceivingSocket);
	WSACleanup();
}
