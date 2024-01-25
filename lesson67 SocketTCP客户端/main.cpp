#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment (lib, "ws2_32.lib")   // 链接到 Winsock 库

#include <WinSock2.h>  // Windows 套接字 API 头文件
#include <stdio.h>

void main(int argc, char** argv) {
    WSADATA wsaData;   // 用于存储 Winsock 库的信息
    SOCKET s;           // 套接字句柄
    SOCKADDR_IN ServerAddr;  // 服务器地址结构
    int Ret;            // 存储函数调用的返回值
    int Port = 5150;    // 服务器端口号

    if (argc <= 1) {
        printf("命令行参数不够\n");
        system("pause");
        return;
    }


    // 初始化 Winsock 库
    if ((Ret = WSAStartup(MAKEWORD(2, 2), &wsaData)) != 0) {
        printf("WSAStartup failed with error %d\n", Ret);
        return;
    }

    // 创建套接字
    if ((s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET) {
        printf("socket failed with error %d\n", WSAGetLastError());
        WSACleanup();
        return;
    }

    // 初始化服务器地址结构
    ServerAddr.sin_family = AF_INET;
    ServerAddr.sin_port = htons(Port);
    ServerAddr.sin_addr.S_un.S_addr = inet_addr(argv[1]);  // 从命令行参数获取服务器 IP 地址

    // 连接到服务器
    printf("We are trying to connect to %s:%d...\n", inet_ntoa(ServerAddr.sin_addr), htons(ServerAddr.sin_port));
    if (connect(s, (SOCKADDR*)&ServerAddr, sizeof(ServerAddr)) == SOCKET_ERROR) {
        printf("connect failed with error %d\n", WSAGetLastError());
        closesocket(s);
        WSACleanup();
        return;
    }

    // 连接成功
    printf("Our connection succeeded.\n");
    printf("We will now try to send a hello message.\n");

    // 发送消息给服务器
    if ((Ret = send(s, "hello", 5, 0)) == SOCKET_ERROR) {
        printf("send failed with error %d\n", WSAGetLastError());
        closesocket(s);
        WSACleanup();
        return;
    }

    // 消息发送成功
    printf("We successfully sent %d bytes.\n", Ret);
    printf("We are closing the connection.\n");

    // 关闭套接字
    closesocket(s);
    WSACleanup();
}
