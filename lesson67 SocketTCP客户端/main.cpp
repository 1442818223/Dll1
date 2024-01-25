#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment (lib, "ws2_32.lib")   // ���ӵ� Winsock ��

#include <WinSock2.h>  // Windows �׽��� API ͷ�ļ�
#include <stdio.h>

void main(int argc, char** argv) {
    WSADATA wsaData;   // ���ڴ洢 Winsock �����Ϣ
    SOCKET s;           // �׽��־��
    SOCKADDR_IN ServerAddr;  // ��������ַ�ṹ
    int Ret;            // �洢�������õķ���ֵ
    int Port = 5150;    // �������˿ں�

    if (argc <= 1) {
        printf("�����в�������\n");
        system("pause");
        return;
    }


    // ��ʼ�� Winsock ��
    if ((Ret = WSAStartup(MAKEWORD(2, 2), &wsaData)) != 0) {
        printf("WSAStartup failed with error %d\n", Ret);
        return;
    }

    // �����׽���
    if ((s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET) {
        printf("socket failed with error %d\n", WSAGetLastError());
        WSACleanup();
        return;
    }

    // ��ʼ����������ַ�ṹ
    ServerAddr.sin_family = AF_INET;
    ServerAddr.sin_port = htons(Port);
    ServerAddr.sin_addr.S_un.S_addr = inet_addr(argv[1]);  // �������в�����ȡ������ IP ��ַ

    // ���ӵ�������
    printf("We are trying to connect to %s:%d...\n", inet_ntoa(ServerAddr.sin_addr), htons(ServerAddr.sin_port));
    if (connect(s, (SOCKADDR*)&ServerAddr, sizeof(ServerAddr)) == SOCKET_ERROR) {
        printf("connect failed with error %d\n", WSAGetLastError());
        closesocket(s);
        WSACleanup();
        return;
    }

    // ���ӳɹ�
    printf("Our connection succeeded.\n");
    printf("We will now try to send a hello message.\n");

    // ������Ϣ��������
    if ((Ret = send(s, "hello", 5, 0)) == SOCKET_ERROR) {
        printf("send failed with error %d\n", WSAGetLastError());
        closesocket(s);
        WSACleanup();
        return;
    }

    // ��Ϣ���ͳɹ�
    printf("We successfully sent %d bytes.\n", Ret);
    printf("We are closing the connection.\n");

    // �ر��׽���
    closesocket(s);
    WSACleanup();
}
