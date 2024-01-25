#include "pch.h"

DWORD g_unhookfun = NULL;   // 要hook的函数地址
char g_oldcode[5] = { 0 };  // 存储原始函数的前五个字节
char g_newcode[5] = { 0xE9, 0, 0, 0, 0 };  // 存储跳转指令和偏移量

// 用于替代MessageBoxW的自定义函数
int WINAPI MyMessageBoxW(
    _In_opt_ HWND hWnd,
    _In_opt_ LPCWSTR lpText, _In_opt_ LPCWSTR lpCaption, _In_ UINT uType)
{
    UninstallHook();  // 先卸载钩子
    int result = MessageBoxW(hWnd, L"51HOOK", lpCaption, uType);  // 调用原始MessageBoxW
    InstallHook();    // 重新安装钩子
    return result;
}

// 安装钩子的函数
BOOL InstallHook() {
    DWORD oldProtect = 0;
    VirtualProtect((DWORD*)g_unhookfun, 5, PAGE_EXECUTE_READWRITE, &oldProtect);  // 修改内存页属性为可读写执行
    memcpy((DWORD*)g_unhookfun, g_newcode, 5);  // 将新的跳转指令写入原始函数地址
    VirtualProtect((DWORD*)g_unhookfun, 5, oldProtect, &oldProtect);  // 恢复内存页属性
    return TRUE;
}

// 卸载钩子的函数
BOOL UninstallHook() {
    DWORD oldProtect = 0;
    VirtualProtect((DWORD*)g_unhookfun, 5, PAGE_EXECUTE_READWRITE, &oldProtect);  // 修改内存页属性为可读写执行
    memcpy((DWORD*)g_unhookfun, g_oldcode, 5);  // 将原始函数的前五个字节写回原始函数地址
    VirtualProtect((DWORD*)g_unhookfun, 5, oldProtect, &oldProtect);  // 恢复内存页属性
    return TRUE;
}

// 初始化钩子
BOOL InitHook() {
    HMODULE hModule = LoadLibraryA("user32.dll");  // 加载user32.dll
    if (hModule == NULL) {
        return FALSE;
    }

    g_unhookfun = (DWORD)GetProcAddress(hModule, "MessageBoxW");  // 获取MessageBoxW函数的地址
    if (g_unhookfun == NULL) {
        FreeLibrary(hModule);
        return FALSE;
    }

    memcpy(g_oldcode, (char*)g_unhookfun, 5);  // 保存原始函数地址的前五个字节(e9+地址)***********
                           //高              低
    DWORD offset = (DWORD)MyMessageBoxW - (g_unhookfun + 5);  // 计算跳转偏移量
    memcpy(&g_newcode[1], &offset, 4);  // 将偏移量写入新的跳转指令中

    return TRUE;
}

// DLL入口函数
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD callReason, LPVOID lpReserved)
{
    if (callReason == DLL_PROCESS_ATTACH)
    {
        InitHook();     // 初始化钩子
        InstallHook();  // 安装钩子
    }
    else if (callReason == DLL_PROCESS_DETACH) {
        UninstallHook();  // 卸载钩子
    }
    return TRUE;
}
