#include <Windows.h>
#include <stdio.h>
#include <psapi.h>
#include <tchar.h>

//提权函数
BOOL UpdateProcessPrivilege(HANDLE hProcess, LPCTSTR lpPrivilegeName = SE_DEBUG_NAME) {
    HANDLE hToken;
    int iResult;

    // 打开进程令牌
    if (OpenProcessToken(hProcess, TOKEN_ALL_ACCESS, &hToken)) {
        LUID destLuid;

        // 查找特权的LUID
        if (LookupPrivilegeValue(NULL, lpPrivilegeName, &destLuid)) {
            TOKEN_PRIVILEGES TokenPrivileges;

            // 设置要启用的特权
            TokenPrivileges.PrivilegeCount = 1;
            TokenPrivileges.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
            TokenPrivileges.Privileges[0].Luid = destLuid;

            // 调整进程特权
            if (AdjustTokenPrivileges(hToken, FALSE, &TokenPrivileges, 0, NULL, NULL)) {
                // 检查是否成功
                iResult = GetLastError();
                if (iResult == ERROR_SUCCESS) {
                    CloseHandle(hToken);
                    return TRUE;
                }
            }
        }

        // 关闭令牌
        CloseHandle(hToken);
    }

    return FALSE;
}


int main() {

    UpdateProcessPrivilege(GetCurrentProcess()); //先给自己提权

    DWORD ProcessId[1024];
    DWORD cbNeeded;
    DWORD processcount;
                        //_out                        //_out   
    if (!EnumProcesses(ProcessId, sizeof(ProcessId), &cbNeeded)) {//#include <psapi.h>
        printf("Failed.\n");
        return -1;
    }

    processcount = cbNeeded / sizeof(DWORD); //实际计算进程的个数
    printf("当前一共有 %d 个进程\n", processcount);

    for (DWORD i = 0; i < processcount; i++) { //遍历出所有进程PID
        printf("ProcessID: %d\n",ProcessId[i]);
    }

/*
*  获取指定进程的全部模块信息
BOOL EnumProcessModules(  
  HANDLE  hProcess, //要查询的进程的句柄。
  HMODULE *lphModule,//用于接收模块句柄的数组。这是一个输出参数。
  DWORD   cb,//指定 lphModule 数组的大小（以字节为单位）。
  LPDWORD lpcbNeeded//接收函数所需的缓冲区大小的变量的指针。这是一个输出参数。
);
*/
    HMODULE hMods[1024];
    for (DWORD i = 0; i < processcount; i++) {     
        HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, ProcessId[i]);
        if (hProcess) {
            printf(" \nProcessID: %d打开成功\n",ProcessId[i]);
                                         //out接收模块句柄         //out模块总大小
            if (EnumProcessModules(hProcess, hMods, sizeof(hMods), &cbNeeded)) {
                for (int j = 0; j < (cbNeeded / sizeof(HMODULE)); j++) {
                    TCHAR szModName[MAX_PATH];
                    if (GetModuleFileNameEx(hProcess, hMods[j], szModName, sizeof(szModName)/sizeof(TCHAR)))
                    {
                        wprintf(L"\t%d %s (Ox%08x)\n",j,szModName,hMods[j]);
                    }
                }
            }
        }
        else
        {
        printf("\nProcessID: %d打开失败\n",ProcessId[i]);
        }
        CloseHandle(hProcess);
    }



    system("pause");
    return 0;
}
