#include <Windows.h>
#include <iostream>
#include <string.h>

int main()
{
    // 打开服务控制管理器
    SC_HANDLE hScManager = OpenSCManagerA(NULL, NULL, SC_MANAGER_ALL_ACCESS);

    if (hScManager == NULL)
    {
        // 打开失败时输出错误信息
        std::cerr << "Failed to open service control manager." << std::endl;
        return 1;
    }

    LPENUM_SERVICE_STATUSA lpService = NULL;  // 服务状态结构体指针
    DWORD realNeedSize = 0;  // 实际所需缓冲区大小
    DWORD serviceNumber = 0;  // 服务数量
    DWORD resumeHandle = 0;  // 用于恢复枚举的句柄

    // 第一次调用获取所需的缓冲区大小
    if (!EnumServicesStatusA(hScManager, SERVICE_WIN32, SERVICE_STATE_ALL, NULL, 0, &realNeedSize, &serviceNumber, &resumeHandle))
    {
        // 检查错误码是否为 ERROR_MORE_DATA
        if (GetLastError() != ERROR_MORE_DATA)
        {
            std::cerr << "Failed to enumerate services. Error: " << GetLastError() << std::endl;
            CloseServiceHandle(hScManager);
            return 1;
        }
    }

    // 使用实际需要的大小来分配缓冲区
    lpService = (LPENUM_SERVICE_STATUSA)malloc(realNeedSize);

    // 重新调用 EnumServicesStatusA 函数
    if (EnumServicesStatusA(hScManager, SERVICE_WIN32, SERVICE_STATE_ALL, lpService,
        realNeedSize, &realNeedSize, &serviceNumber, &resumeHandle))
    {
        // 遍历服务列表，检查是否存在包含 "VMware" 的服务
        for (DWORD i = 0; i < serviceNumber; i++)
        {
            if (strstr(lpService[i].lpDisplayName, "VMware") != nullptr)
            {
                std::cout << "检测到虚拟机：" << lpService[i].lpDisplayName << std::endl;
                MessageBoxA(0, "检测到虚拟机", "提示", MB_OK);
            }
        }
    }
    else
    {
        std::cerr << "Failed to enumerate services. Error: " << GetLastError() << std::endl;
    }

    // 关闭服务控制管理器句柄
    if (hScManager)
    {
        CloseServiceHandle(hScManager);
    }

    // 暂停等待用户输入
    system("pause");
    return 0;
}
