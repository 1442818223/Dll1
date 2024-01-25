#include <Windows.h>
#include <stdio.h>
#include <psapi.h>
#include <tchar.h>

//��Ȩ����
BOOL UpdateProcessPrivilege(HANDLE hProcess, LPCTSTR lpPrivilegeName = SE_DEBUG_NAME) {
    HANDLE hToken;
    int iResult;

    // �򿪽�������
    if (OpenProcessToken(hProcess, TOKEN_ALL_ACCESS, &hToken)) {
        LUID destLuid;

        // ������Ȩ��LUID
        if (LookupPrivilegeValue(NULL, lpPrivilegeName, &destLuid)) {
            TOKEN_PRIVILEGES TokenPrivileges;

            // ����Ҫ���õ���Ȩ
            TokenPrivileges.PrivilegeCount = 1;
            TokenPrivileges.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
            TokenPrivileges.Privileges[0].Luid = destLuid;

            // ����������Ȩ
            if (AdjustTokenPrivileges(hToken, FALSE, &TokenPrivileges, 0, NULL, NULL)) {
                // ����Ƿ�ɹ�
                iResult = GetLastError();
                if (iResult == ERROR_SUCCESS) {
                    CloseHandle(hToken);
                    return TRUE;
                }
            }
        }

        // �ر�����
        CloseHandle(hToken);
    }

    return FALSE;
}


int main() {

    UpdateProcessPrivilege(GetCurrentProcess()); //�ȸ��Լ���Ȩ

    DWORD ProcessId[1024];
    DWORD cbNeeded;
    DWORD processcount;
                        //_out                        //_out   
    if (!EnumProcesses(ProcessId, sizeof(ProcessId), &cbNeeded)) {//#include <psapi.h>
        printf("Failed.\n");
        return -1;
    }

    processcount = cbNeeded / sizeof(DWORD); //ʵ�ʼ�����̵ĸ���
    printf("��ǰһ���� %d ������\n", processcount);

    for (DWORD i = 0; i < processcount; i++) { //���������н���PID
        printf("ProcessID: %d\n",ProcessId[i]);
    }

/*
*  ��ȡָ�����̵�ȫ��ģ����Ϣ
BOOL EnumProcessModules(  
  HANDLE  hProcess, //Ҫ��ѯ�Ľ��̵ľ����
  HMODULE *lphModule,//���ڽ���ģ���������顣����һ�����������
  DWORD   cb,//ָ�� lphModule ����Ĵ�С�����ֽ�Ϊ��λ����
  LPDWORD lpcbNeeded//���պ�������Ļ�������С�ı�����ָ�롣����һ�����������
);
*/
    HMODULE hMods[1024];
    for (DWORD i = 0; i < processcount; i++) {     
        HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, ProcessId[i]);
        if (hProcess) {
            printf(" \nProcessID: %d�򿪳ɹ�\n",ProcessId[i]);
                                         //out����ģ����         //outģ���ܴ�С
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
        printf("\nProcessID: %d��ʧ��\n",ProcessId[i]);
        }
        CloseHandle(hProcess);
    }



    system("pause");
    return 0;
}
