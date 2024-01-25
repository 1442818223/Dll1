#include <Windows.h>
#include <iostream>
#include <tlhelp32.h>
// 定义 NT_HEADER 宏
#define NT_HEADER(base) ((PIMAGE_NT_HEADERS)((ULONG_PTR)base + ((PIMAGE_DOS_HEADER)base)->e_lfanew))

// 定义 StrICmp 函数
bool StrICmp(const char* str1, const char* str2, bool caseSensitive) {
    if (caseSensitive) {
        return strcmp(str1, str2) == 0;
    }
    else {
        return _stricmp(str1, str2) == 0;
    }
}
 
// 获取指定进程的模块句柄
HMODULE GetModuleHandleOfProcess(DWORD processId, const wchar_t* moduleName)
{
    // 创建快照
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, processId);

    if (snapshot == INVALID_HANDLE_VALUE)
    {
        return nullptr;
    }

    // 初始化 MODULEENTRY32 结构
    MODULEENTRY32 moduleEntry;
    moduleEntry.dwSize = sizeof(moduleEntry);

    // 遍历模块
    if (Module32First(snapshot, &moduleEntry))
    {
        do
        {
            // 检查是否为目标模块
            if (wcscmp(moduleEntry.szModule, moduleName) == 0)
            {
                // 关闭快照句柄并返回模块句柄
                CloseHandle(snapshot);
                return moduleEntry.hModule;
            }
        } while (Module32Next(snapshot, &moduleEntry));
    }

    // 未找到目标模块，关闭快照句柄并返回 nullptr
    CloseHandle(snapshot);
    return nullptr;
}

//获取导出函数地址的函数       两种方法:1,PE方式 2,GetProcAddress
PVOID GetExportedFunctionAddress(HMODULE hModule, const char* functionName, bool caseSensitive) {
    if (!hModule) return nullptr;

    // 解析 PE 头
    PIMAGE_NT_HEADERS NT_Head = NT_HEADER(hModule);
    PIMAGE_EXPORT_DIRECTORY ExportDir = (PIMAGE_EXPORT_DIRECTORY)((ULONG64)hModule + NT_Head->OptionalHeader.DataDirectory[0].VirtualAddress);

    // 遍历导出表中的函数
    for (ULONG i = 0; i < ExportDir->NumberOfNames; i++) {
        // 获取序数和名称
        USHORT Ordinal = ((USHORT*)((ULONG64)hModule + ExportDir->AddressOfNameOrdinals))[i];
        const char* ExpName = (const char*)hModule + ((ULONG*)((ULONG64)hModule + ExportDir->AddressOfNames))[i];

        // 检查导出函数名称
        if (StrICmp(functionName, ExpName, caseSensitive))
            return (PVOID)((ULONG64)hModule + ((ULONG*)((ULONG64)hModule + ExportDir->AddressOfFunctions))[Ordinal]);
    }

    return nullptr;
}

int main() {
    // 加载 DLL
    HMODULE hModule = LoadLibrary(TEXT("D:\\VS_PROJECT\\Dll1\\x64\\Release\\Dll1.dll"));
    if (!hModule) {
        DWORD error = GetLastError();
        std::cerr << "Failed to load DLL. Error code: " << error << std::endl;
        return 1;
    }

    // 调用封装的函数获取导出函数地址
    const char* functionName = "Demow";
    PVOID functionAddress = GetExportedFunctionAddress(hModule, functionName, true);

    if (functionAddress) {
        std::cout << "Address of " << functionName << " function: " << functionAddress << std::endl;
    }
    else {
        DWORD error = GetLastError();
        std::cerr << "Failed to get function address. Error code: " << error << std::endl;
    }

    // 释放 DLL
    FreeLibrary(hModule);

    return 0;
}
