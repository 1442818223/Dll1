#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#pragma comment (lib, "ws2_32.lib")   // ���ӵ� Winsock ��
#include <stdio.h>
#include <WinSock2.h>

void main(int argc, char** argv)
{
	WSADATA wsaData;   // ���ڴ洢 Winsock �����Ϣ
	SOCKET SendingSocket;  // �������ݵ��׽��־��
	SOCKADDR_IN ReceiverAddr;  // ���շ���ַ�ṹ
	int ReceiverAddrSize = sizeof(ReceiverAddr);

	if (argc <= 1) {
		printf("��������!!\n");
		system("pause");
		return;
	}

	// ��ʼ�� Winsock ��
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	// ���� UDP �׽���
	SendingSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	ReceiverAddr.sin_family = AF_INET;  // IPv4
	ReceiverAddr.sin_port = htons(5150);  // �������˿ں�
	ReceiverAddr.sin_addr.S_un.S_addr = inet_addr(argv[1]);  // ������ IP ��ַ

	while (1) {
		char buffer[1024] = "\0";
		printf(" Input message \n");
		scanf("%s", buffer);

		if (strcmp(buffer, "bye") == 0)
			break;

		// �������ݵ�������
		if (sendto(SendingSocket, buffer, sizeof(buffer), 0, (SOCKADDR*)&ReceiverAddr, sizeof(ReceiverAddr)) != SOCKET_ERROR)
		{
			// ���շ���������Ӧ
			if (recvfrom(SendingSocket, buffer, sizeof(buffer), 0, (SOCKADDR*)&ReceiverAddr, &ReceiverAddrSize) != SOCKET_ERROR)
			{
				printf("Received from server: %s\n", buffer);
			}
		}
	}

	closesocket(SendingSocket);
	WSACleanup();
}
