//32λ�汾
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
//    // ��ȡ����Ļ�������С
//    ZwQuerySystemInformation(SystemProcessesAndThreadsInformation, nullptr, 0, &cbBuffer);
//
//    // ���仺����
//    pBuffer = malloc(cbBuffer);
//    if (pBuffer == nullptr) {
//        wcout << L"Error: -2" << endl;
//        return -2;
//    }
//
//    // ��ȡϵͳ��Ϣ
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


//64λ�汾
#include <iostream>
#include <Windows.h>
#include <NTSecAPI.h>

using namespace std;

// �������ڻ�ȡϵͳ��Ϣ�ĺ���ָ������
typedef NTSTATUS(WINAPI* ZWQUERYSYSTEMINFORMATION)(
    DWORD,
    PVOID,
    ULONG,
    PULONG
    );

// ����ϵͳ��Ϣ�ṹ��
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

// �������ڻ�ȡ���̺��߳���Ϣ�ı�ʶ
#define SystemProcessesAndThreadsInformation 5

int main() {
    // ��ȡ ntdll.dll ģ����
    HMODULE hNtDLL = GetModuleHandle(L"ntdll.dll");//GetModuleHandleֻ�ܻ�ȡ�����̵�dllģ����

    // ���ģ�����Ƿ���Ч
    if (!hNtDLL) {
        wcout << L"Error: -1" << endl;
        return -1;
    }

    // ��ȡ ZwQuerySystemInformation ����ָ��
    ZWQUERYSYSTEMINFORMATION ZwQuerySystemInformation = (ZWQUERYSYSTEMINFORMATION)GetProcAddress(hNtDLL, "ZwQuerySystemInformation");

    // ��麯��ָ���Ƿ���Ч
    if (!ZwQuerySystemInformation) {
        wcout << L"Error: -1" << endl;
        return -1;
    }

    // ���û�������С
    ULONG cbBuffer = 0;
    PVOID pBuffer = nullptr;

    // ��ȡ����Ļ�������С
    ZwQuerySystemInformation(SystemProcessesAndThreadsInformation, nullptr, 0, &cbBuffer);

    // ���仺����
    pBuffer = malloc(cbBuffer);
    if (pBuffer == nullptr) {
        wcout << L"Error: -2" << endl;
        return -2;
    }

    // ��ȡϵͳ��Ϣ
    NTSTATUS status = ZwQuerySystemInformation(SystemProcessesAndThreadsInformation, pBuffer, cbBuffer, nullptr);
    if (status == 0) {
        // ת��Ϊϵͳ��Ϣ�ṹ��ָ��
        PSYSTEM_PROCESS_INFORMATION pInfo = (PSYSTEM_PROCESS_INFORMATION)pBuffer;

        for (;;) {
            // ��ӡ����ID�ͽ�����
            wprintf(L"ProcessID: %d (%.*ls)\n", pInfo->ProcessId, pInfo->ProcessName.Length / sizeof(wchar_t), pInfo->ProcessName.Buffer);
                                    //.* ��ʾҪʹ�ú�������ṩ������������pInfo->ProcessName.Length / sizeof(wchar_t)����ָ���ַ����Ŀ��
                                    //ls ��ʾ���һ�����ַ���
                                    
            // �ж��Ƿ�Ϊ��������һ�����
            if (pInfo->NextEntryDelta == 0) {
                break;
            }

            // �ƶ�����һ�����
            pInfo = (PSYSTEM_PROCESS_INFORMATION)(((PUCHAR)pInfo) + pInfo->NextEntryDelta);
        }
    }
    else {
        wcout << L"ZwQuerySystemInformation failed with status: " << status << endl;
    }

    // �ͷ��ڴ�
    free(pBuffer);

    // ��ͣ����ִ�У��ȴ��û�����
    system("pause");
    return 0;
}
