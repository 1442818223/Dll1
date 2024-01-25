#include <stdio.h>
#include <iostream>
#include <Windows.h>
#include <tlhelp32.h>
#include <Psapi.h>  // ��� Psapi.h ͷ�ļ�

using namespace std;

//��ȡ����ַ
DWORD_PTR GetProcessBaseAddress(DWORD processID)
{
    DWORD_PTR baseAddress = 0;
    HANDLE processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processID);

    if (processHandle)
    {
        HMODULE moduleArray[1024];  // ���費���г��� 1024 ��ģ��
        DWORD bytesRequired;
                                                                                //outģ���ܴ�С
        if (EnumProcessModules(processHandle, moduleArray, sizeof(moduleArray), &bytesRequired))
        {
            unsigned int moduleCount = bytesRequired / sizeof(HMODULE);

            if (moduleCount > 0)
            {
                baseAddress = (DWORD_PTR)moduleArray[0];//��һ��ģ��ͨ������ģ��
            }
            
        }
        else
        {
            // ���� EnumProcessModules ʧ�ܵ����
            cout << "EnumProcessModules failed with error " << GetLastError() << endl;
        }

        CloseHandle(processHandle);
    }
    else
    {
        // ���� OpenProcess ʧ�ܵ����
        cout << "OpenProcess failed with error " << GetLastError() << endl;
    }

    return baseAddress;
}

int main()
{
    HWND hwnd = FindWindowA(NULL, "Plants vs. Zombies");
    if (hwnd == NULL)
    {
        std::cout << "��Ϸδ��" << std::endl;
        return 0;
    }

    DWORD pId;
    GetWindowThreadProcessId(hwnd, &pId);
    std::cout << "���̵�id: " << pId << std::endl;

    HANDLE hPro;
    hPro = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pId);
    if (hPro == NULL) {
        std::cout << "���̴�ʧ��" << std::endl;
        return 0;
    }

    uintptr_t baseAddress = GetProcessBaseAddress(pId);

    if (baseAddress != 0) {
        cout << "�ɹ���ȡ��ģ���ַ: 0x" << hex << baseAddress << endl;


        /*
        BOOL ReadProcessMemory(
  HANDLE hProcess,  // Ŀ����̾��
  LPCVOID lpBaseAddress,   // ��ȡ���ݵ���ʼ��ַ
  LPVOID lpBuffer,  // ������ݵĻ�������ַ
  DWORD nSize,      // Ҫ��ȡ���ֽ���
  LPDWORD lpNumberOfBytesRead   // ʵ�ʶ�ȡ����ŵ�ַ
);

        
        */
        // [[[PlantsVsZombies.exe+0x331C50]+0x868]+0x5578]

        uintptr_t dwTemp;
    
       
        ReadProcessMemory(hPro, (LPCVOID)(baseAddress + 0x331C50), &dwTemp, sizeof(dwTemp),NULL );
       

        // 2. ��ȡ dwTemp + 0x868

        ReadProcessMemory(hPro, (LPCVOID)(dwTemp + 0x868), &dwTemp, sizeof(dwTemp), NULL);
   
        int ��;
        //// 3. ��ȡ dwTemp + 0x5578
        ReadProcessMemory(hPro, (LPCVOID)(dwTemp + 0x5578), &��, sizeof(��), NULL);
        cout << "��ǰ������: " << dec << �� << endl;
       
        int a;
        cout << "������Ҫ�޸ĵ�����ֵ:\n" << endl;
        cin >> a;
        WriteProcessMemory(hPro,(LPVOID)(dwTemp + 0x5578), &a, sizeof(a),NULL);

    }
    else {
        cout << "��ȡģ���ַʧ��" << endl;
    }

    CloseHandle(hPro);

    system("pause");
    return 0;
}


