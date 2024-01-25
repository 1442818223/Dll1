#include <Windows.h>
#include <TlHelp32.h>
#include <stdio.h>

int main() {
    // 创建当前进程的快照
    PROCESSENTRY32 processEntry = { 0 };//PROCESSENTRY32 是 Windows API 中的一个结构体，用于描述进程的信息。
    HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    // 检查是否成功创建了快照
    if (hProcessSnap == INVALID_HANDLE_VALUE)
        return -1;

    // 在使用结构之前设置结构的大小
    processEntry.dwSize = sizeof(PROCESSENTRY32);

    // 获取快照中的第一个进程
    BOOL bRet = Process32First(hProcessSnap, &processEntry);

    // 遍历快照中的所有进程
    while (bRet) {
        // 打印有关进程的信息
        wprintf(L"ProcessID: %lu, Name: %s\n", processEntry.th32ProcessID, processEntry.szExeFile);

        // 获取快照中的下一个进程
        bRet = Process32Next(hProcessSnap, &processEntry);
    }

    // 关闭对快照的句柄
    CloseHandle(hProcessSnap);

  
    system("pause");
    return 0;
}
