#include"pch.h"


HINSTANCE g_hInstance = NULL;
HHOOK g_hhook = NULL;


/*
* 每一种钩子类型都有对应的处理函数类型
LRESULT CALLBACK KeyboardProc(
  int    nCode,//钩子代码，如果小于 0，表示钩子过程必须将消息传递给 CallNextHookEx 而不处理它。如果大于等于 0，则可以处理消息。
  WPARAM wParam,//
  LPARAM lParam//
)
*/
LRESULT CALLBACK KeyboardProc(
    int code,
    WPARAM wParam,
    LPARAM lParam
)
{
    // 判断是否为键盘动作
    if (code == HC_ACTION)
    {
        // 下面实现照抄即可
        BYTE KeyState[256]{ 0 }; // 存储键盘键的状态
        // 获取当前键盘状态
        if (GetKeyboardState(KeyState))
        {
            WCHAR wkeyCode = 0; // 存储虚拟键码对应的 Unicode 字符

            // 将虚拟键码转换为 Unicode 字符
            if (ToAscii((UINT)wParam, 0, KeyState, (LPWORD)&wkeyCode, 0))
            {
                CHAR strinfo[50] = { 0 }; // 存储输出的调试信息
                // 格式化字符串写入 strinfo 中
                sprintf_s(strinfo, _countof(strinfo), "HOOK到的字符:%c", wkeyCode);

                // 将调试信息输出到调试窗口
                OutputDebugStringA(strinfo);
            }
        }
    }

    // 调用下一个钩子过程，传递键盘事件给下一个钩子或目标窗口
    return CallNextHookEx(g_hhook, code, wParam, lParam);
}





/*
* 用于安装钩子的函数
HHOOK SetWindowsHookExA(
  int       idHook,        // 钩子类型，例如 WH_KEYBOARD 表示键盘钩子
  HOOKPROC  lpfn,          // 指向钩子过程的指针
  HINSTANCE hMod,          // 包含钩子过程的 DLL 的句柄，通常为 NULL
  DWORD     dwThreadId     // 要安装钩子的线程标识符，为 0 表示全局钩子
);
*/
BOOL InstallHook() {          //根据钩子类型查询钩子函数类型                        
    g_hhook = SetWindowsHookExA(WH_KEYBOARD, KeyboardProc, g_hInstance, 0);
    if (g_hhook)
    {
        return TRUE;
    }
    return FALSE;
}



BOOL unInstallHook() {

    return UnhookWindowsHookEx(g_hhook); //卸载
}




//非模版创建的DLL文件要在 配置属性->配置类型->动态库(.dll)
BOOL WINAPI DllMain(
    HINSTANCE hinstDLL,
    DWORD fdwReason,
    LPVOID lpReserved)
{
    if (fdwReason == DLL_PROCESS_ATTACH) {
        g_hInstance = hinstDLL;
        OutputDebugStringA("DLL加载成功\n");
    }
    else if (fdwReason == DLL_PROCESS_DETACH) {
        OutputDebugStringA("DLL卸载\n");
    }

    return TRUE;
}




