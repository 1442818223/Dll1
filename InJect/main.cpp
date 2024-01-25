//被注入程序(notepad.exe)和注入模块(thief.dll)位数必须一致(32位或64位)
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

//判断要注入的进程是否为64位(通过PE头来判断)
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


// 提权函数
BOOL EnablePrivilege(LPCTSTR privilegeName) {
    HANDLE hToken;
    TOKEN_PRIVILEGES tokenPrivileges;

    // 打开当前进程的令牌
    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) {
        _tprintf(_T("OpenProcessToken failed (%d)\n"), GetLastError());
        return FALSE;
    }

    // 获取特权的LUID
    if (!LookupPrivilegeValue(NULL, privilegeName, &tokenPrivileges.Privileges[0].Luid)) {
        _tprintf(_T("LookupPrivilegeValue failed (%d)\n"), GetLastError());
        CloseHandle(hToken);
        return FALSE;
    }

    tokenPrivileges.PrivilegeCount = 1;
    tokenPrivileges.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

    // 启用特权
    if (!AdjustTokenPrivileges(hToken, FALSE, &tokenPrivileges, sizeof(TOKEN_PRIVILEGES), NULL, NULL)) {
        _tprintf(_T("AdjustTokenPrivileges failed (%d)\n"), GetLastError());
        CloseHandle(hToken);
        return FALSE;
    }

    CloseHandle(hToken);

    return TRUE;
}

BOOL  InJect(HWND hwnd, const wchar_t* pszDllFileName) {

    // 系统进程必须先提权才能打开，否则在OpenProcess步骤会失败
    EnablePrivilege(SE_DEBUG_NAME);
    /*
    SE_DEBUG_NAME 是一个用于表示具有调试权限的 Windows 特权名称。
    这个特权允许一个进程调试其他进程，并具有绕过一些安全限制的能力。
    在提权时，你可以根据实际需要选择不同的特权名称。
    */
    // 1.打开目标进程
    hProcess = OpenProcess(
        PROCESS_ALL_ACCESS,     // 打开权限
        FALSE,                  // 是否继承
        dwProcessId);           // 进程PID
    if (NULL == hProcess)
    {
        MessageBox(NULL, L"打开目标进程失败", L"错误", MB_OK);
        return FALSE;
    }

    // 2.在目标进程中申请空间
    LPVOID lpPathAddr = VirtualAllocEx(
        hProcess,                   // 目标进程句柄
        NULL,                       // 指定申请地址
        (wcslen(pszDllFileName) + 1) * sizeof(wchar_t),   // 申请空间大小
       //wcslen 是用于计算宽字符字符串长度的函数。它会返回字符串中字符的数量，不包括结尾的空字符（L'\0'）
        MEM_RESERVE | MEM_COMMIT, // 内存的状态    
        PAGE_READWRITE);            // 内存属性
    if (NULL == lpPathAddr)
    {
        MessageBox(NULL, L"在目标进程中申请空间失败", L"错误", MB_OK);
        CloseHandle(hProcess);
        return FALSE;
    }

    // 3.在目标进程中写入Dll路径
    SIZE_T dwWriteSize = 0;
    if (FALSE == WriteProcessMemory(
        hProcess,                   // 目标进程句柄
        lpPathAddr,                 // 目标进程地址
        pszDllFileName,             // 写入的缓冲区
        (wcslen(pszDllFileName) + 1) * sizeof(wchar_t),   // 缓冲区大小
        &dwWriteSize))              // 实际写入大小
    {
        MessageBox(NULL, L"目标进程中写入Dll路径失败！", L"错误", MB_OK);
        CloseHandle(hProcess);
        return FALSE;
    }

    
    //获取LoadLibraryA的函数地址
    //FARPROC可以自适应32位与64位

    /*为什么创建远程线程的时候调用 LoadLibrary 函数就能把 DLL 注入到目标进程中

　　LoadLibrary 函数是 Kernel32.dll 中的一个成员

　　Kernel32.dll 这个DLL是创建进程必须的一个DLL，并且所有进程在内存中指向的 Kernel32.dll 是同一个地址

　　所以只要获取到当前进程中 LoadLibrary 函数的地址就够了*/

  // 获取当前进程中 LoadLibraryW 函数的地址
    LPTHREAD_START_ROUTINE pLoadLibraryW = (LPTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandle(L"Kernel32.dll"), "LoadLibraryW");

    // 获取目标进程中 Kernel32.dll 模块的句柄
    HMODULE hKernel32 = NULL;
    GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, (LPCTSTR)pLoadLibraryW, &hKernel32);

    // 获取目标进程中 LoadLibraryW 函数的地址
    LPTHREAD_START_ROUTINE pFuncProcAddr = (LPTHREAD_START_ROUTINE)GetProcAddress(hKernel32, "LoadLibraryW");

    // 4.在目标进程中创建线程

      /*
        在指定进程中，创建一个线程
        并通过这个线程，调用 LoadLibrary 函数
        通过 LoadLibrary 函数，把 DLL 载入到目标进程中
        HANDLE CreateRemoteThread(
        [in]  HANDLE                 hProcess, // 指定进程
        [in]  LPSECURITY_ATTRIBUTES  lpThreadAttributes, // 设置线程安全属性，表示线程是否可以继承，NULL就够了
        [in]  SIZE_T                 dwStackSize, // 堆栈的初始大小，0 表示使用可执行文件的默认大小
        [in]  LPTHREAD_START_ROUTINE lpStartAddress, // 远程进程中，需要执行的那个函数的指针
        [in]  LPVOID                 lpParameter, // 目前进程中 DLL路径的指针
        [in]  DWORD                  dwCreationFlags, // 0 线程在创建后立即运行。
        [out] LPDWORD                lpThreadId // [out] 当前不需要这个返回值
        );
    */

    HANDLE hThread = CreateRemoteThread(
        hProcess,                   // 目标进程句柄
        NULL,                       // 安全属性
        0,                          // 栈大小
        (LPTHREAD_START_ROUTINE)pFuncProcAddr,   // 回调函数
        lpPathAddr,                 // 回调函数参数
        0,                          // 标志
        NULL                        // 线程ID
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
        MessageBox(NULL, L"创建线程失败！", L"错误", MB_OK);
        LocalFree(lpMsgBuf);

        CloseHandle(hProcess);
        return FALSE;
    }


    // 5.等待线程结束
    WaitForSingleObject(hThread, -1);

    // 6.清理环境
    VirtualFreeEx(hProcess, lpPathAddr, 0, MEM_RELEASE);
    CloseHandle(hThread);
    CloseHandle(hProcess);
    return TRUE;
}

//转义字符过程
string ConvertToDoubleBackslashes(const string& input) {
   string result;

    for (char c : input) {
        if (c == '\\') {
            // 将单斜杠替换为双斜杠
            result += '\\';
        }
        result += c;
    }

    return result;
}

//判断dll路径是否存在
bool FileExists(const std::string& filePath) {
    DWORD fileAttributes = GetFileAttributesA(filePath.c_str());
    return (fileAttributes != INVALID_FILE_ATTRIBUTES && !(fileAttributes & FILE_ATTRIBUTE_DIRECTORY));
}

// 转换为宽字符字符串
std::wstring ConvertToWString(const std::string& narrowStr) {
    // 使用直接初始化列表进行字符串转换
    return std::wstring{ narrowStr.begin(), narrowStr.end() };
}



// 根据进程名称获取进程ID
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
// 根据进程ID和模块名称获取模块句柄
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
/// 把指定进程中的DLL卸载掉
/// </summary>
/// <param name="processName"></param>
/// <param name="dllPath"></param>
void UnInjectDll(const wchar_t* processName) {
    // 通过进程名称获取该进程句柄
    DWORD dword = GetProcessByName(processName);
    if (dword == 0)
    {
        MessageBox(NULL, TEXT("没有找到指定进程"), TEXT("错误"), 0);
        return;
    }
    // 获取指定进程中指定模块的内存地址
    HMODULE hmodule = GetProcessModuleHandle(dword, L"WX_Read_Write.dll");

    // 打开指定进程
    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dword);
    if (hProcess == NULL)
    {
        MessageBox(NULL, TEXT("指定进程打开失败"), TEXT("错误"), 0);
        return;
    }

    // 获取 Kernel32.dll 这个模块
    HMODULE k32 = GetModuleHandle(TEXT("Kernel32.dll"));
    // 在 Kernel32.dll 模块中找到 LoadLibrary 这个函数的内存地址
    LPVOID loadADD = GetProcAddress(k32, "FreeLibrary");

    HANDLE hThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)loadADD, (LPVOID)hmodule, 0, NULL);

    // 释放指定的模块
    CloseHandle(hThread);
    CloseHandle(hProcess);
}

//只取路径后面的文件名
std::string GetFileNameFromPath(const std::string& fullPath) {
    // 查找最后一个路径分隔符的位置
    size_t lastSlash = fullPath.find_last_of("\\/");

    // 如果找到了路径分隔符，则返回分隔符后面的部分作为文件名
    if (lastSlash != std::string::npos) {
        return fullPath.substr(lastSlash + 1);
    }
    else {
        // 如果没有找到路径分隔符，则整个路径都是文件名
        return fullPath;
    }
}

int main()
{
A1:
    system("cls");
    // 恢复默认文本颜色
    system("color");

    cout << "请输入窗口标题: ";
    string windowTitle;
    getline(cin, windowTitle);
    HWND hwnd = FindWindowA(NULL, windowTitle.c_str());
    if (hwnd == NULL) {
        MessageBox(NULL, L"找不到窗口", L"错误", MB_OK);
        windowTitle = { 0 };
        goto A1;
       
    }
  
    GetWindowThreadProcessId(hwnd, &dwProcessId);

    BOOL isTargetProcess64Bit = IsProcess64Bit(dwProcessId);
    if (isTargetProcess64Bit) {
        cout << "目标进程是 64 位的，使用 64 位的注入器和 DLL\n" << endl;

        MessageBox(NULL, L"请打开32位注入器", L"错误", MB_OK);
        return 0;
        // 设置 DLL 文件路径为 64 位版本的路径
        // pszDllFileName = L"D:\\VS_PROJECT\\Dll1\\x64\\Release\\Dll1.dll"; //x64
    }
    else {
        cout << " 目标进程是 32 位的，使用 32 位的注入器和 DLL\n" << endl;
      
        // 设置 DLL 文件路径为 32 位版本的路径
       // pszDllFileName = L"D:\\VS_PROJECT\\Dll1\\Release\\Dll1.dll";//x86    
    }

    A2:
    string userPath;
    cout << "请输入DLL路径: ";
    getline(cin, userPath);
    userPath =ConvertToDoubleBackslashes(userPath);
    if (FileExists(userPath)) {
        cout << "路径存在\n" << endl;
    }
    else {
        cout << "路径不存在\n" << endl;
        userPath = { 0 };
        goto A2;
        
    }
   
    std::wstring pszDllFileName = ConvertToWString(userPath);


    system("cls");
    while (1) {
        // 恢复默认文本颜色
        system("color");

        printf("程序名:%s\n", windowTitle.c_str());
        printf("DLL名:%s\n", GetFileNameFromPath(userPath).c_str());


        int uMsg;
        system("color 0c");
        cout << "请选择要进行的操作:\n" << endl;
        cout << "1:注入\n" << endl;
        cout << "2:卸载\n" << endl;
        cout << "3:重新输入程序名和DLL路径\n" << endl;
        cout << "4:退出本程序\n" << endl;

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