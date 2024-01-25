#include <stdio.h>
#include <Windows.h>
#include <WtsApi32.h>

#pragma comment(lib, "WtsApi32.lib")//让链接器链接时加上WtsApi32.lib

int main() {
    DWORD i;
    const wchar_t* szServerName = L"DESKTOP-RF6SRB6"; //电脑名
    HANDLE hWtsServer = WTSOpenServer(const_cast<LPWSTR>(szServerName)); // 打开 WTS 服务器// 转换为 LPWSTR
  
/*
* 用于列举在 Terminal Services 或 Remote Desktop Session Host （RD Session Host）服务器上运行的进程的函数。
BOOL WTSEnumerateProcesses(  
  IN  HANDLE hServer,//指定要获取进程信息的服务器的句柄。
  IN  DWORD  Reserved,//保留参数，必须为 0。
  IN  DWORD  Version,//指定 WTS_PROCESS_INFO 结构的版本号。当前支持的版本为 1。
  OUT PWTS_PROCESS_INFO *ppProcessInfo,//接收指向 WTS_PROCESS_INFO 结构数组的指针。该数组包含进程信息。
  OUT DWORD             *pCount//接收 进程 信息数组中的元素数量。
);
*/
    PWTS_PROCESS_INFO pWtspi;
    DWORD dwCount;
    // 获取当前 WTS 服务器上的进程信息
    if (!WTSEnumerateProcesses(hWtsServer, 0, 1, &pWtspi, &dwCount)) {
        wprintf(L"Error!"); 
        return -1;
    }

    // 遍历并打印每个进程的信息
    for (i = 0; i < dwCount; i++) {
        wprintf(L"ProcessID: %d(%s)\n", pWtspi[i].ProcessId, pWtspi[i].pProcessName); // 使用宽字符打印
    }

    // 关闭 WTS 服务器句柄
    WTSCloseServer(hWtsServer);

    system("pause");
    return 0;
}
