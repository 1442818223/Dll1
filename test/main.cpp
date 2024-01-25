#include <Windows.h>
#include <iostream>
#include <tlhelp32.h>
// ���� NT_HEADER ��
#define NT_HEADER(base) ((PIMAGE_NT_HEADERS)((ULONG_PTR)base + ((PIMAGE_DOS_HEADER)base)->e_lfanew))

// ���� StrICmp ����
bool StrICmp(const char* str1, const char* str2, bool caseSensitive) {
    if (caseSensitive) {
        return strcmp(str1, str2) == 0;
    }
    else {
        return _stricmp(str1, str2) == 0;
    }
}
 
// ��ȡָ�����̵�ģ����
HMODULE GetModuleHandleOfProcess(DWORD processId, const wchar_t* moduleName)
{
    // ��������
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, processId);

    if (snapshot == INVALID_HANDLE_VALUE)
    {
        return nullptr;
    }

    // ��ʼ�� MODULEENTRY32 �ṹ
    MODULEENTRY32 moduleEntry;
    moduleEntry.dwSize = sizeof(moduleEntry);

    // ����ģ��
    if (Module32First(snapshot, &moduleEntry))
    {
        do
        {
            // ����Ƿ�ΪĿ��ģ��
            if (wcscmp(moduleEntry.szModule, moduleName) == 0)
            {
                // �رտ��վ��������ģ����
                CloseHandle(snapshot);
                return moduleEntry.hModule;
            }
        } while (Module32Next(snapshot, &moduleEntry));
    }

    // δ�ҵ�Ŀ��ģ�飬�رտ��վ�������� nullptr
    CloseHandle(snapshot);
    return nullptr;
}

//��ȡ����������ַ�ĺ���       ���ַ���:1,PE��ʽ 2,GetProcAddress
PVOID GetExportedFunctionAddress(HMODULE hModule, const char* functionName, bool caseSensitive) {
    if (!hModule) return nullptr;

    // ���� PE ͷ
    PIMAGE_NT_HEADERS NT_Head = NT_HEADER(hModule);
    PIMAGE_EXPORT_DIRECTORY ExportDir = (PIMAGE_EXPORT_DIRECTORY)((ULONG64)hModule + NT_Head->OptionalHeader.DataDirectory[0].VirtualAddress);

    // �����������еĺ���
    for (ULONG i = 0; i < ExportDir->NumberOfNames; i++) {
        // ��ȡ����������
        USHORT Ordinal = ((USHORT*)((ULONG64)hModule + ExportDir->AddressOfNameOrdinals))[i];
        const char* ExpName = (const char*)hModule + ((ULONG*)((ULONG64)hModule + ExportDir->AddressOfNames))[i];

        // ��鵼����������
        if (StrICmp(functionName, ExpName, caseSensitive))
            return (PVOID)((ULONG64)hModule + ((ULONG*)((ULONG64)hModule + ExportDir->AddressOfFunctions))[Ordinal]);
    }

    return nullptr;
}

int main() {
    // ���� DLL
    HMODULE hModule = LoadLibrary(TEXT("D:\\VS_PROJECT\\Dll1\\x64\\Release\\Dll1.dll"));
    if (!hModule) {
        DWORD error = GetLastError();
        std::cerr << "Failed to load DLL. Error code: " << error << std::endl;
        return 1;
    }

    // ���÷�װ�ĺ�����ȡ����������ַ
    const char* functionName = "Demow";
    PVOID functionAddress = GetExportedFunctionAddress(hModule, functionName, true);

    if (functionAddress) {
        std::cout << "Address of " << functionName << " function: " << functionAddress << std::endl;
    }
    else {
        DWORD error = GetLastError();
        std::cerr << "Failed to get function address. Error code: " << error << std::endl;
    }

    // �ͷ� DLL
    FreeLibrary(hModule);

    return 0;
}
