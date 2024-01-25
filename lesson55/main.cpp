//32位版本
//#include <iostream>
//#include <Windows.h>
//#include <NTSecAPI.h>
//
//using namespace std;
//
//typedef DWORD(WINAPI* ZWQUERYSYSTEMINFORMATION)(
//    DWORD,
//    PVOID,
//    DWORD,
//    PDWORD
//    );
//
//#define SystemProcessesAndThreadsInformation 5
//
//typedef struct _SYSTEM_PROCESS_INFORMATION {
//    DWORD NextEntryDelta;
//    DWORD ThreadCount;
//    DWORD Reserved1[6];
//    FILETIME ftCreateTime;
//    FILETIME ftUserTime;
//    FILETIME ftKernelTime;
//    UNICODE_STRING ProcessName;
//    DWORD BasePriority;
//    DWORD ProcessId;
//    DWORD InheritedFromProcessId;
//    DWORD HandleCount;
//    DWORD Reserved2[2];
//    DWORD mCounters;
//    DWORD dCommitCharge;
//    PVOID ThreadInfos[1];
//} SYSTEM_PROCESS_INFORMATION, * PSYSTEM_PROCESS_INFORMATION;
//
//int main() {
//    HMODULE hNtDLL = GetModuleHandle(L"ntdll.dll");
//
//    if (!hNtDLL) {
//        wcout << L"Error: -1" << endl;
//        return -1;
//    }
//
//    ZWQUERYSYSTEMINFORMATION ZwQuerySystemInformation = (ZWQUERYSYSTEMINFORMATION)GetProcAddress(hNtDLL, "ZwQuerySystemInformation");
//
//    if (!ZwQuerySystemInformation) {
//        wcout << L"Error: -1" << endl;
//        return -1;
//    }
//
//    ULONG cbBuffer = 0x10000;
//    PVOID pBuffer = NULL;
//
//    // 获取所需的缓冲区大小
//    ZwQuerySystemInformation(SystemProcessesAndThreadsInformation, nullptr, 0, &cbBuffer);
//
//    // 分配缓冲区
//    pBuffer = malloc(cbBuffer);
//    if (pBuffer == nullptr) {
//        wcout << L"Error: -2" << endl;
//        return -2;
//    }
//
//    // 获取系统信息
//    if (ZwQuerySystemInformation(SystemProcessesAndThreadsInformation, pBuffer, cbBuffer, nullptr) == 0) {
//        PSYSTEM_PROCESS_INFORMATION pInfo = (PSYSTEM_PROCESS_INFORMATION)pBuffer;
//
//        for (;;) {
//            wprintf(L"ProcessID: %d (%ls)\n", pInfo->ProcessId, pInfo->ProcessName.Buffer);
//
//            if (pInfo->NextEntryDelta == 0) {
//                break;
//            }
//
//            pInfo = (PSYSTEM_PROCESS_INFORMATION)(((PUCHAR)pInfo) + pInfo->NextEntryDelta);
//        }
//    }
//    else {
//        wcout << L"ZwQuerySystemInformation failed." << endl;
//    }
//
//  
//    free(pBuffer);
//
//    system("pause");
//    return 0;
//}


//64位版本
#include <iostream>
#include <Windows.h>
#include <NTSecAPI.h>

using namespace std;

// 定义用于获取系统信息的函数指针类型
typedef NTSTATUS(WINAPI* ZWQUERYSYSTEMINFORMATION)(
    DWORD,
    PVOID,
    ULONG,
    PULONG
    );

// 定义系统信息结构体
typedef struct _SYSTEM_PROCESS_INFORMATION {
    ULONG NextEntryDelta;
    ULONG ThreadCount;
    ULONG Reserved1[6];
    FILETIME ftCreateTime;
    FILETIME ftUserTime;
    FILETIME ftKernelTime;
    UNICODE_STRING ProcessName;
    ULONG BasePriority;
    HANDLE ProcessId;
    HANDLE InheritedFromProcessId;
    ULONG HandleCount;
    ULONG Reserved2[2];
    ULONG mCounters;
    ULONG dCommitCharge;
    PVOID ThreadInfos[1];
} SYSTEM_PROCESS_INFORMATION, * PSYSTEM_PROCESS_INFORMATION;

// 定义用于获取进程和线程信息的标识
#define SystemProcessesAndThreadsInformation 5

int main() {
    // 获取 ntdll.dll 模块句柄
    HMODULE hNtDLL = GetModuleHandle(L"ntdll.dll");//GetModuleHandle只能获取本进程的dll模块句柄

    // 检查模块句柄是否有效
    if (!hNtDLL) {
        wcout << L"Error: -1" << endl;
        return -1;
    }

    // 获取 ZwQuerySystemInformation 函数指针
    ZWQUERYSYSTEMINFORMATION ZwQuerySystemInformation = (ZWQUERYSYSTEMINFORMATION)GetProcAddress(hNtDLL, "ZwQuerySystemInformation");

    // 检查函数指针是否有效
    if (!ZwQuerySystemInformation) {
        wcout << L"Error: -1" << endl;
        return -1;
    }

    // 设置缓冲区大小
    ULONG cbBuffer = 0;
    PVOID pBuffer = nullptr;

    // 获取所需的缓冲区大小
    ZwQuerySystemInformation(SystemProcessesAndThreadsInformation, nullptr, 0, &cbBuffer);

    // 分配缓冲区
    pBuffer = malloc(cbBuffer);
    if (pBuffer == nullptr) {
        wcout << L"Error: -2" << endl;
        return -2;
    }

    // 获取系统信息
    NTSTATUS status = ZwQuerySystemInformation(SystemProcessesAndThreadsInformation, pBuffer, cbBuffer, nullptr);
    if (status == 0) {
        // 转换为系统信息结构体指针
        PSYSTEM_PROCESS_INFORMATION pInfo = (PSYSTEM_PROCESS_INFORMATION)pBuffer;

        for (;;) {
            // 打印进程ID和进程名
            wprintf(L"ProcessID: %d (%.*ls)\n", pInfo->ProcessId, pInfo->ProcessName.Length / sizeof(wchar_t), pInfo->ProcessName.Buffer);
                                    //.* 表示要使用后面额外提供的整数参数（pInfo->ProcessName.Length / sizeof(wchar_t)）来指定字符串的宽度
                                    //ls 表示输出一个宽字符串
                                    
            // 判断是否为链表的最后一个结点
            if (pInfo->NextEntryDelta == 0) {
                break;
            }

            // 移动到下一个结点
            pInfo = (PSYSTEM_PROCESS_INFORMATION)(((PUCHAR)pInfo) + pInfo->NextEntryDelta);
        }
    }
    else {
        wcout << L"ZwQuerySystemInformation failed with status: " << status << endl;
    }

    // 释放内存
    free(pBuffer);

    // 暂停程序执行，等待用户输入
    system("pause");
    return 0;
}
