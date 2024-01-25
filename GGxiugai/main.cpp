#include <stdio.h>
#include <iostream>
#include <Windows.h>
#include <tlhelp32.h>
#include <Psapi.h>  // 添加 Psapi.h 头文件

using namespace std;

//获取基地址
DWORD_PTR GetProcessBaseAddress(DWORD processID)
{
    DWORD_PTR baseAddress = 0;
    HANDLE processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processID);

    if (processHandle)
    {
        HMODULE moduleArray[1024];  // 假设不会有超过 1024 个模块
        DWORD bytesRequired;
                                                                                //out模块总大小
        if (EnumProcessModules(processHandle, moduleArray, sizeof(moduleArray), &bytesRequired))
        {
            unsigned int moduleCount = bytesRequired / sizeof(HMODULE);

            if (moduleCount > 0)
            {
                baseAddress = (DWORD_PTR)moduleArray[0];//第一个模块通常是主模块
            }
            
        }
        else
        {
            // 处理 EnumProcessModules 失败的情况
            cout << "EnumProcessModules failed with error " << GetLastError() << endl;
        }

        CloseHandle(processHandle);
    }
    else
    {
        // 处理 OpenProcess 失败的情况
        cout << "OpenProcess failed with error " << GetLastError() << endl;
    }

    return baseAddress;
}

int main()
{
    HWND hwnd = FindWindowA(NULL, "Plants vs. Zombies");
    if (hwnd == NULL)
    {
        std::cout << "游戏未打开" << std::endl;
        return 0;
    }

    DWORD pId;
    GetWindowThreadProcessId(hwnd, &pId);
    std::cout << "进程的id: " << pId << std::endl;

    HANDLE hPro;
    hPro = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pId);
    if (hPro == NULL) {
        std::cout << "进程打开失败" << std::endl;
        return 0;
    }

    uintptr_t baseAddress = GetProcessBaseAddress(pId);

    if (baseAddress != 0) {
        cout << "成功获取了模块基址: 0x" << hex << baseAddress << endl;


        /*
        BOOL ReadProcessMemory(
  HANDLE hProcess,  // 目标进程句柄
  LPCVOID lpBaseAddress,   // 读取数据的起始地址
  LPVOID lpBuffer,  // 存放数据的缓存区地址
  DWORD nSize,      // 要读取的字节数
  LPDWORD lpNumberOfBytesRead   // 实际读取数存放地址
);

        
        */
        // [[[PlantsVsZombies.exe+0x331C50]+0x868]+0x5578]

        uintptr_t dwTemp;
    
       
        ReadProcessMemory(hPro, (LPCVOID)(baseAddress + 0x331C50), &dwTemp, sizeof(dwTemp),NULL );
       

        // 2. 读取 dwTemp + 0x868

        ReadProcessMemory(hPro, (LPCVOID)(dwTemp + 0x868), &dwTemp, sizeof(dwTemp), NULL);
   
        int 读;
        //// 3. 读取 dwTemp + 0x5578
        ReadProcessMemory(hPro, (LPCVOID)(dwTemp + 0x5578), &读, sizeof(读), NULL);
        cout << "当前阳光数: " << dec << 读 << endl;
       
        int a;
        cout << "输入想要修改的阳光值:\n" << endl;
        cin >> a;
        WriteProcessMemory(hPro,(LPVOID)(dwTemp + 0x5578), &a, sizeof(a),NULL);

    }
    else {
        cout << "获取模块基址失败" << endl;
    }

    CloseHandle(hPro);

    system("pause");
    return 0;
}


