//��ע�����(notepad.exe)��ע��ģ��(thief.dll)λ������һ��(32λ��64λ)
#include <iostream>
#include <windows.h>
#include <string.h>
#include <string>
#include <tchar.h>
#include <tlhelp32.h>
#include <filesystem>
#include <locale>
#include <codecvt>

using namespace std;

DWORD dwProcessId = NULL;
HANDLE hProcess = NULL;

//�ж�Ҫע��Ľ����Ƿ�Ϊ64λ(ͨ��PEͷ���ж�)
BOOL IsProcess64Bit(DWORD dwProcessId) {
    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, dwProcessId);
    if (hProcess == NULL) {
        DWORD error = GetLastError();
        std::cerr << "OpenProcess failed. Error code: " << error << std::endl;
        return FALSE;
    }

    BOOL isWow64 = FALSE;
    if (!IsWow64Process(hProcess, &isWow64)) {
        DWORD error = GetLastError();
        std::cerr << "IsWow64Process failed. Error code: " << error << std::endl;
        CloseHandle(hProcess);
        return FALSE;
    }

    CloseHandle(hProcess);

    return isWow64 ? FALSE : TRUE;
}


// ��Ȩ����
BOOL EnablePrivilege(LPCTSTR privilegeName) {
    HANDLE hToken;
    TOKEN_PRIVILEGES tokenPrivileges;

    // �򿪵�ǰ���̵�����
    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) {
        _tprintf(_T("OpenProcessToken failed (%d)\n"), GetLastError());
        return FALSE;
    }

    // ��ȡ��Ȩ��LUID
    if (!LookupPrivilegeValue(NULL, privilegeName, &tokenPrivileges.Privileges[0].Luid)) {
        _tprintf(_T("LookupPrivilegeValue failed (%d)\n"), GetLastError());
        CloseHandle(hToken);
        return FALSE;
    }

    tokenPrivileges.PrivilegeCount = 1;
    tokenPrivileges.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

    // ������Ȩ
    if (!AdjustTokenPrivileges(hToken, FALSE, &tokenPrivileges, sizeof(TOKEN_PRIVILEGES), NULL, NULL)) {
        _tprintf(_T("AdjustTokenPrivileges failed (%d)\n"), GetLastError());
        CloseHandle(hToken);
        return FALSE;
    }

    CloseHandle(hToken);

    return TRUE;
}

BOOL  InJect(HWND hwnd, const wchar_t* pszDllFileName) {

    // ϵͳ���̱�������Ȩ���ܴ򿪣�������OpenProcess�����ʧ��
    EnablePrivilege(SE_DEBUG_NAME);
    /*
    SE_DEBUG_NAME ��һ�����ڱ�ʾ���е���Ȩ�޵� Windows ��Ȩ���ơ�
    �����Ȩ����һ�����̵����������̣��������ƹ�һЩ��ȫ���Ƶ�������
    ����Ȩʱ������Ը���ʵ����Ҫѡ��ͬ����Ȩ���ơ�
    */
    // 1.��Ŀ�����
    hProcess = OpenProcess(
        PROCESS_ALL_ACCESS,     // ��Ȩ��
        FALSE,                  // �Ƿ�̳�
        dwProcessId);           // ����PID
    if (NULL == hProcess)
    {
        MessageBox(NULL, L"��Ŀ�����ʧ��", L"����", MB_OK);
        return FALSE;
    }

    // 2.��Ŀ�����������ռ�
    LPVOID lpPathAddr = VirtualAllocEx(
        hProcess,                   // Ŀ����̾��
        NULL,                       // ָ�������ַ
        (wcslen(pszDllFileName) + 1) * sizeof(wchar_t),   // ����ռ��С
       //wcslen �����ڼ�����ַ��ַ������ȵĺ��������᷵���ַ������ַ�����������������β�Ŀ��ַ���L'\0'��
        MEM_RESERVE | MEM_COMMIT, // �ڴ��״̬    
        PAGE_READWRITE);            // �ڴ�����
    if (NULL == lpPathAddr)
    {
        MessageBox(NULL, L"��Ŀ�����������ռ�ʧ��", L"����", MB_OK);
        CloseHandle(hProcess);
        return FALSE;
    }

    // 3.��Ŀ�������д��Dll·��
    SIZE_T dwWriteSize = 0;
    if (FALSE == WriteProcessMemory(
        hProcess,                   // Ŀ����̾��
        lpPathAddr,                 // Ŀ����̵�ַ
        pszDllFileName,             // д��Ļ�����
        (wcslen(pszDllFileName) + 1) * sizeof(wchar_t),   // ��������С
        &dwWriteSize))              // ʵ��д���С
    {
        MessageBox(NULL, L"Ŀ�������д��Dll·��ʧ�ܣ�", L"����", MB_OK);
        CloseHandle(hProcess);
        return FALSE;
    }

    
    //��ȡLoadLibraryA�ĺ�����ַ
    //FARPROC��������Ӧ32λ��64λ

    /*Ϊʲô����Զ���̵߳�ʱ����� LoadLibrary �������ܰ� DLL ע�뵽Ŀ�������

����LoadLibrary ������ Kernel32.dll �е�һ����Ա

����Kernel32.dll ���DLL�Ǵ������̱����һ��DLL���������н������ڴ���ָ��� Kernel32.dll ��ͬһ����ַ

��������ֻҪ��ȡ����ǰ������ LoadLibrary �����ĵ�ַ�͹���*/

  // ��ȡ��ǰ������ LoadLibraryW �����ĵ�ַ
    LPTHREAD_START_ROUTINE pLoadLibraryW = (LPTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandle(L"Kernel32.dll"), "LoadLibraryW");

    // ��ȡĿ������� Kernel32.dll ģ��ľ��
    HMODULE hKernel32 = NULL;
    GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, (LPCTSTR)pLoadLibraryW, &hKernel32);

    // ��ȡĿ������� LoadLibraryW �����ĵ�ַ
    LPTHREAD_START_ROUTINE pFuncProcAddr = (LPTHREAD_START_ROUTINE)GetProcAddress(hKernel32, "LoadLibraryW");

    // 4.��Ŀ������д����߳�

      /*
        ��ָ�������У�����һ���߳�
        ��ͨ������̣߳����� LoadLibrary ����
        ͨ�� LoadLibrary �������� DLL ���뵽Ŀ�������
        HANDLE CreateRemoteThread(
        [in]  HANDLE                 hProcess, // ָ������
        [in]  LPSECURITY_ATTRIBUTES  lpThreadAttributes, // �����̰߳�ȫ���ԣ���ʾ�߳��Ƿ���Լ̳У�NULL�͹���
        [in]  SIZE_T                 dwStackSize, // ��ջ�ĳ�ʼ��С��0 ��ʾʹ�ÿ�ִ���ļ���Ĭ�ϴ�С
        [in]  LPTHREAD_START_ROUTINE lpStartAddress, // Զ�̽����У���Ҫִ�е��Ǹ�������ָ��
        [in]  LPVOID                 lpParameter, // Ŀǰ������ DLL·����ָ��
        [in]  DWORD                  dwCreationFlags, // 0 �߳��ڴ������������С�
        [out] LPDWORD                lpThreadId // [out] ��ǰ����Ҫ�������ֵ
        );
    */

    HANDLE hThread = CreateRemoteThread(
        hProcess,                   // Ŀ����̾��
        NULL,                       // ��ȫ����
        0,                          // ջ��С
        (LPTHREAD_START_ROUTINE)pFuncProcAddr,   // �ص�����
        lpPathAddr,                 // �ص���������
        0,                          // ��־
        NULL                        // �߳�ID
    );

    if (NULL == hThread)
    {
        DWORD dwError = GetLastError();
        LPVOID lpMsgBuf;
        FormatMessage(
            FORMAT_MESSAGE_ALLOCATE_BUFFER |
            FORMAT_MESSAGE_FROM_SYSTEM |
            FORMAT_MESSAGE_IGNORE_INSERTS,
            NULL,
            dwError,
            0, // Default language
            (LPWSTR)&lpMsgBuf,
            0,
            NULL
        );

        wprintf(L"CreateRemoteThread failed with error %d: %s\n", dwError, lpMsgBuf);
        MessageBox(NULL, L"�����߳�ʧ�ܣ�", L"����", MB_OK);
        LocalFree(lpMsgBuf);

        CloseHandle(hProcess);
        return FALSE;
    }


    // 5.�ȴ��߳̽���
    WaitForSingleObject(hThread, -1);

    // 6.������
    VirtualFreeEx(hProcess, lpPathAddr, 0, MEM_RELEASE);
    CloseHandle(hThread);
    CloseHandle(hProcess);
    return TRUE;
}

//ת���ַ�����
string ConvertToDoubleBackslashes(const string& input) {
   string result;

    for (char c : input) {
        if (c == '\\') {
            // ����б���滻Ϊ˫б��
            result += '\\';
        }
        result += c;
    }

    return result;
}

//�ж�dll·���Ƿ����
bool FileExists(const std::string& filePath) {
    DWORD fileAttributes = GetFileAttributesA(filePath.c_str());
    return (fileAttributes != INVALID_FILE_ATTRIBUTES && !(fileAttributes & FILE_ATTRIBUTE_DIRECTORY));
}

// ת��Ϊ���ַ��ַ���
std::wstring ConvertToWString(const std::string& narrowStr) {
    // ʹ��ֱ�ӳ�ʼ���б�����ַ���ת��
    return std::wstring{ narrowStr.begin(), narrowStr.end() };
}



// ���ݽ������ƻ�ȡ����ID
DWORD GetProcessByName(const wchar_t* processName) {
    PROCESSENTRY32 entry;
    entry.dwSize = sizeof(PROCESSENTRY32);

    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (Process32First(snapshot, &entry) == TRUE) {
        while (Process32Next(snapshot, &entry) == TRUE) {
            if (_wcsicmp(entry.szExeFile, processName) == 0) {
                CloseHandle(snapshot);
                return entry.th32ProcessID;
            }
        }
    }

    CloseHandle(snapshot);
    return 0;
}
// ���ݽ���ID��ģ�����ƻ�ȡģ����
HMODULE GetProcessModuleHandle(DWORD processId, const wchar_t* moduleName) {
    MODULEENTRY32 module;
    module.dwSize = sizeof(MODULEENTRY32);

    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, processId);

    if (Module32First(snapshot, &module) == TRUE) {
        while (Module32Next(snapshot, &module) == TRUE) {
            if (_wcsicmp(module.szModule, moduleName) == 0) {
                CloseHandle(snapshot);
                return module.hModule;
            }
        }
    }

    CloseHandle(snapshot);
    return NULL;
}
/// <summary>
/// ��ָ�������е�DLLж�ص�
/// </summary>
/// <param name="processName"></param>
/// <param name="dllPath"></param>
void UnInjectDll(const wchar_t* processName) {
    // ͨ���������ƻ�ȡ�ý��̾��
    DWORD dword = GetProcessByName(processName);
    if (dword == 0)
    {
        MessageBox(NULL, TEXT("û���ҵ�ָ������"), TEXT("����"), 0);
        return;
    }
    // ��ȡָ��������ָ��ģ����ڴ��ַ
    HMODULE hmodule = GetProcessModuleHandle(dword, L"WX_Read_Write.dll");

    // ��ָ������
    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dword);
    if (hProcess == NULL)
    {
        MessageBox(NULL, TEXT("ָ�����̴�ʧ��"), TEXT("����"), 0);
        return;
    }

    // ��ȡ Kernel32.dll ���ģ��
    HMODULE k32 = GetModuleHandle(TEXT("Kernel32.dll"));
    // �� Kernel32.dll ģ�����ҵ� LoadLibrary ����������ڴ��ַ
    LPVOID loadADD = GetProcAddress(k32, "FreeLibrary");

    HANDLE hThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)loadADD, (LPVOID)hmodule, 0, NULL);

    // �ͷ�ָ����ģ��
    CloseHandle(hThread);
    CloseHandle(hProcess);
}

//ֻȡ·��������ļ���
std::string GetFileNameFromPath(const std::string& fullPath) {
    // �������һ��·���ָ�����λ��
    size_t lastSlash = fullPath.find_last_of("\\/");

    // ����ҵ���·���ָ������򷵻طָ�������Ĳ�����Ϊ�ļ���
    if (lastSlash != std::string::npos) {
        return fullPath.substr(lastSlash + 1);
    }
    else {
        // ���û���ҵ�·���ָ�����������·�������ļ���
        return fullPath;
    }
}

int main()
{
A1:
    system("cls");
    // �ָ�Ĭ���ı���ɫ
    system("color");

    cout << "�����봰�ڱ���: ";
    string windowTitle;
    getline(cin, windowTitle);
    HWND hwnd = FindWindowA(NULL, windowTitle.c_str());
    if (hwnd == NULL) {
        MessageBox(NULL, L"�Ҳ�������", L"����", MB_OK);
        windowTitle = { 0 };
        goto A1;
       
    }
  
    GetWindowThreadProcessId(hwnd, &dwProcessId);

    BOOL isTargetProcess64Bit = IsProcess64Bit(dwProcessId);
    if (isTargetProcess64Bit) {
        cout << "Ŀ������� 64 λ�ģ�ʹ�� 64 λ��ע������ DLL\n" << endl;

        MessageBox(NULL, L"���32λע����", L"����", MB_OK);
        return 0;
        // ���� DLL �ļ�·��Ϊ 64 λ�汾��·��
        // pszDllFileName = L"D:\\VS_PROJECT\\Dll1\\x64\\Release\\Dll1.dll"; //x64
    }
    else {
        cout << " Ŀ������� 32 λ�ģ�ʹ�� 32 λ��ע������ DLL\n" << endl;
      
        // ���� DLL �ļ�·��Ϊ 32 λ�汾��·��
       // pszDllFileName = L"D:\\VS_PROJECT\\Dll1\\Release\\Dll1.dll";//x86    
    }

    A2:
    string userPath;
    cout << "������DLL·��: ";
    getline(cin, userPath);
    userPath =ConvertToDoubleBackslashes(userPath);
    if (FileExists(userPath)) {
        cout << "·������\n" << endl;
    }
    else {
        cout << "·��������\n" << endl;
        userPath = { 0 };
        goto A2;
        
    }
   
    std::wstring pszDllFileName = ConvertToWString(userPath);


    system("cls");
    while (1) {
        // �ָ�Ĭ���ı���ɫ
        system("color");

        printf("������:%s\n", windowTitle.c_str());
        printf("DLL��:%s\n", GetFileNameFromPath(userPath).c_str());


        int uMsg;
        system("color 0c");
        cout << "��ѡ��Ҫ���еĲ���:\n" << endl;
        cout << "1:ע��\n" << endl;
        cout << "2:ж��\n" << endl;
        cout << "3:���������������DLL·��\n" << endl;
        cout << "4:�˳�������\n" << endl;

        cin >> uMsg;

        switch (uMsg)
        {
        case 1:

            InJect(hwnd, pszDllFileName.c_str());
            uMsg = 0;
            break;
        case 2:
            UnInjectDll(pszDllFileName.c_str());
            uMsg = 0;
            break;
        case 3:
            cin.ignore(); // Clear the newline character from the buffer
            hwnd = 0;
            pszDllFileName = { 0 };
            goto A1;
            break;
            hwnd = 0;
            pszDllFileName = { 0 };
            goto A1;
            break;
        case 4:
            return 0;
        default:
            uMsg = 0;
            break;

        }
        system("pause");
       
    }
    std::cout << "Hello World!\n";
   
}