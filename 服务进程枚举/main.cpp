#include <Windows.h>
#include <iostream>
#include <string.h>

int main()
{
    // �򿪷�����ƹ�����
    SC_HANDLE hScManager = OpenSCManagerA(NULL, NULL, SC_MANAGER_ALL_ACCESS);

    if (hScManager == NULL)
    {
        // ��ʧ��ʱ���������Ϣ
        std::cerr << "Failed to open service control manager." << std::endl;
        return 1;
    }

    LPENUM_SERVICE_STATUSA lpService = NULL;  // ����״̬�ṹ��ָ��
    DWORD realNeedSize = 0;  // ʵ�����軺������С
    DWORD serviceNumber = 0;  // ��������
    DWORD resumeHandle = 0;  // ���ڻָ�ö�ٵľ��

    // ��һ�ε��û�ȡ����Ļ�������С
    if (!EnumServicesStatusA(hScManager, SERVICE_WIN32, SERVICE_STATE_ALL, NULL, 0, &realNeedSize, &serviceNumber, &resumeHandle))
    {
        // ���������Ƿ�Ϊ ERROR_MORE_DATA
        if (GetLastError() != ERROR_MORE_DATA)
        {
            std::cerr << "Failed to enumerate services. Error: " << GetLastError() << std::endl;
            CloseServiceHandle(hScManager);
            return 1;
        }
    }

    // ʹ��ʵ����Ҫ�Ĵ�С�����仺����
    lpService = (LPENUM_SERVICE_STATUSA)malloc(realNeedSize);

    // ���µ��� EnumServicesStatusA ����
    if (EnumServicesStatusA(hScManager, SERVICE_WIN32, SERVICE_STATE_ALL, lpService,
        realNeedSize, &realNeedSize, &serviceNumber, &resumeHandle))
    {
        // ���������б�����Ƿ���ڰ��� "VMware" �ķ���
        for (DWORD i = 0; i < serviceNumber; i++)
        {
            if (strstr(lpService[i].lpDisplayName, "VMware") != nullptr)
            {
                std::cout << "��⵽�������" << lpService[i].lpDisplayName << std::endl;
                MessageBoxA(0, "��⵽�����", "��ʾ", MB_OK);
            }
        }
    }
    else
    {
        std::cerr << "Failed to enumerate services. Error: " << GetLastError() << std::endl;
    }

    // �رշ�����ƹ��������
    if (hScManager)
    {
        CloseServiceHandle(hScManager);
    }

    // ��ͣ�ȴ��û�����
    system("pause");
    return 0;
}
