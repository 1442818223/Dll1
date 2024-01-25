// pch.cpp: 与预编译标头对应的源文件

#include "pch.h"


/* 告诉连接器 链接时需要的库*/
//#pragma comment (lib, "Psapi.lib")
/* 函数声明　*/



BOOL WINAPI DllMain(
    HINSTANCE hinstDLL,  // DLL模块的句柄
    DWORD fdwReason,     // 调用的情况
    LPVOID lpReserved)  // reserved
{
    // 在不同的情况下都会调用 DllMain 函数，分别处理
    switch (fdwReason)
    {
        // 加载Dll
    case DLL_PROCESS_ATTACH:
    break;
    // 新建线程
    case DLL_THREAD_ATTACH:
        break;
        // 线程退出
    case DLL_THREAD_DETACH:
        break;
        // 释放Dll
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}


//关键注释1:
//CALLBACK:如果是窗体(windows系统所需的回调函数)去调用我们的DLL 必须加上,否则不必加 
//extern "C" 如果是c++生成时避免编译时函数名被修改;  可将extern "C"放到头文件去用if宏定义
//__declspec(dllexport) 申明是DLL导出函数
//extern "C" __declspec(dllexport) BOOL CALLBACK EdrCenterTextA(HDC hdc, PRECT prc, PCSTR pString) {
//}
//extern "C" __declspec(dllexport) BOOL CALLBACK EdrCenterTextW(HDC hdc,PRECT prc,PCWSTR pString){
//}

//关键注释2: 此时已将extern "C" __declspec(dllexport)通过区分是否为c/c++环境重命名为EXPORT
EXPORT BOOL CALLBACK EdrCenterTextA(HDC hdc, PRECT prc, PCSTR pString) {
    int iLength;
    SIZE size;

    // 获取文本的长度
    iLength = lstrlenA(pString);

    // 获取文本的尺寸
/*
  BOOL GetTextExtentPoint32A( 用于获取指定字符串在设备上下文环境（HDC）中的逻辑尺寸。
  HDC    hdc, //设备上下文句柄，表示要在哪个设备上下文环境中进行文本测量。
  LPCSTR lpString,// 要测量的字符串。
  int    c, //字符串的长度，如果为 -1，则函数将自动计算字符串的长度。
  LPSIZE lpSize//指向 SIZE 结构的指针，该结构接收文本的逻辑宽度和高度。
  );
*/
    GetTextExtentPoint32A(hdc, pString, iLength, &size);

    // 计算文本在矩形中居中的位置，然后绘制文本
    return TextOutA(hdc,
        (prc->right - prc->left - size.cx) / 2,
        (prc->bottom - prc->top - size.cy) / 2,
        pString,
        iLength);
}

EXPORT BOOL CALLBACK EdrCenterTextW(HDC hdc,PRECT prc,PCWSTR pString){
    int iLength;
    SIZE size;

    // 获取文本的长度
    iLength = lstrlenW(pString);

    // 获取文本的尺寸
    GetTextExtentPoint32W(hdc, pString, iLength, &size);

    // 计算文本在矩形中居中的位置，然后绘制文本
    return TextOutW(hdc,
        (prc->right - prc->left - size.cx) / 2,
        (prc->bottom - prc->top - size.cy) / 2,
        pString,
        iLength);
}


EXPORT DWORD DemoA() {
    MessageBoxA(NULL, "这是动态链接库的函数", "DLL", MB_OK);
    Sleep(10000);
    return 0;
}
EXPORT DWORD Demow() {
    MessageBoxW(NULL,L"这是动态链接库的函数",L"DLL", MB_OK);
    Sleep(10000);
    return 0;
}