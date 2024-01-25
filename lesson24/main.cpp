#include <Windows.h>
#include <iostream>
#include <comdef.h>
#include <Wbemidl.h>
#include <cstdint>
#pragma comment(lib, "wbemuuid.lib")//它指示编译器链接到名为 "wbemuuid.lib" 的库文件

/*
WMI（Windows Management Instrumentation）是一种用于管理和监视 Windows 操作系统的标准化技术。
通过 WMI，你可以查询和监视各种系统和应用程序信息。以下是一些你可以使用 WMI 查询的信息类别：

操作系统信息： 包括操作系统版本、安装日期、注册表信息等。
硬件信息： 包括处理器、内存、磁盘驱动器、网络适配器等硬件组件的信息。
网络信息： 包括网络连接、网络适配器、IP 地址等信息。
服务信息： 包括已安装的服务、服务的状态和配置信息。
软件信息： 包括已安装的软件、安装路径、卸载信息等。
性能计数器信息： 包括 CPU 使用率、内存使用率、磁盘活动等性能统计信息。
事件日志信息： 包括系统、安全和应用程序事件日志中的事件信息。
*/


// 检查是否是 Windows 11 或更高版本
bool IsWindows11OrNewer()
{
    // 初始化 COM 库
    HRESULT hr = CoInitializeEx(0, COINIT_MULTITHREADED);
    if (FAILED(hr))
    {
        std::cerr << "Failed to initialize COM library" << std::endl;
        return false;
    }

    // 初始化安全设置
    hr = CoInitializeSecurity(
        NULL,
        -1,
        NULL,
        NULL,
        RPC_C_AUTHN_LEVEL_DEFAULT,
        RPC_C_IMP_LEVEL_IMPERSONATE,
        NULL,
        EOAC_NONE,
        NULL);

    if (FAILED(hr))
    {
        CoUninitialize();
        std::cerr << "Failed to initialize security" << std::endl;
        return false;
    }

    // 创建 WMI 定位器
    IWbemLocator* pLoc = nullptr;
    hr = CoCreateInstance(CLSID_WbemLocator, 0, CLSCTX_INPROC_SERVER, IID_IWbemLocator, (LPVOID*)&pLoc);

    if (FAILED(hr))
    {
        CoUninitialize();
        std::cerr << "Failed to create IWbemLocator object" << std::endl;
        return false;
    }

    // 连接 WMI 服务
    IWbemServices* pSvc = nullptr;
    hr = pLoc->ConnectServer(
        _bstr_t(L"ROOT\\CIMV2"),
        NULL,
        NULL,
        0,
        NULL,
        0,
        0,
        &pSvc);

    if (FAILED(hr))
    {
        pLoc->Release();
        CoUninitialize();
        std::cerr << "Failed to connect to WMI" << std::endl;
        return false;
    }

    // 执行 WMI 查询
    IEnumWbemClassObject* pEnumerator = nullptr;
    hr = pSvc->ExecQuery(
        bstr_t("WQL"),
        bstr_t("SELECT * FROM Win32_OperatingSystem"),
        WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
        NULL,
        &pEnumerator);

    if (FAILED(hr))
    {
        pSvc->Release();
        pLoc->Release();
        CoUninitialize();
        std::cerr << "Query for operating system information failed" << std::endl;
        return false;
    }

    // 遍历查询结果
    IWbemClassObject* pclsObj = nullptr;
    ULONG uReturn = 0;

    while (pEnumerator)
    {
        hr = pEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);

        if (uReturn == 0)
            break;

        VARIANT vtProp;
        // 获取 Version 属性值
        hr = pclsObj->Get(L"Version", 0, &vtProp, 0, 0);

        if (SUCCEEDED(hr))
        {
            // 打印 Version 属性值
            std::wcout << L"Version : " << vtProp.bstrVal << std::endl;
            VariantClear(&vtProp);
        }

        pclsObj->Release();
    }

    // 释放资源
    pSvc->Release();
    pLoc->Release();
    pEnumerator->Release();
    CoUninitialize();

    return true;
}



void ShowSystemInfo()
{
    SYSTEM_INFO si;
    GetSystemInfo(&si); //.8: 表示至少输出 8 位，并且如果不足 8 位则用零填充。
    printf("内存分页大小:0x%.8X，可用内存起始:0x%.8X，可用内存结束:0x%.8X \n",
        si.dwPageSize, si.lpMinimumApplicationAddress, si.lpMaximumApplicationAddress);

    printf("处理器个数:%d\n", si.dwNumberOfProcessors);

    printf("处理器类型:");
    switch (si.dwProcessorType) {
    case PROCESSOR_INTEL_386:
        printf("386\n");
        break;
    case PROCESSOR_INTEL_486:      
        printf("486\n");
        break;
    case PROCESSOR_INTEL_PENTIUM:
        printf("pentium\n");
        break;
    }

    printf("\n");

    printf("处理器架构:");
    switch (si.wProcessorArchitecture) {
    case PROCESSOR_ARCHITECTURE_INTEL:
        printf("intel\n");
        break;
    case PROCESSOR_ARCHITECTURE_IA64:
        printf("64 bits intel\n"); break;
    case PROCESSOR_ARCHITECTURE_AMD64:
        printf("64 bits AMD\n");
        break;
    case PROCESSOR_ARCHITECTURE_UNKNOWN:
        printf("UNKNOWN\n");
        break;
    }
}

int main()
{
    if (IsWindows11OrNewer())
    {
        std::wcout << L"Windows 11 or newer" << std::endl;
    }
    else
    {
        std::wcout << L"Not Windows 11 or newer" << std::endl;
    }


    printf("\n");


    ShowSystemInfo();

    return 0;
}
