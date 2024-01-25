#include <Windows.h>
#include <iostream>
#include <comdef.h>
#include <Wbemidl.h>
#include <cstdint>
#pragma comment(lib, "wbemuuid.lib")//��ָʾ���������ӵ���Ϊ "wbemuuid.lib" �Ŀ��ļ�

/*
WMI��Windows Management Instrumentation����һ�����ڹ���ͼ��� Windows ����ϵͳ�ı�׼��������
ͨ�� WMI������Բ�ѯ�ͼ��Ӹ���ϵͳ��Ӧ�ó�����Ϣ��������һЩ�����ʹ�� WMI ��ѯ����Ϣ���

����ϵͳ��Ϣ�� ��������ϵͳ�汾����װ���ڡ�ע�����Ϣ�ȡ�
Ӳ����Ϣ�� �������������ڴ桢������������������������Ӳ���������Ϣ��
������Ϣ�� �����������ӡ�������������IP ��ַ����Ϣ��
������Ϣ�� �����Ѱ�װ�ķ��񡢷����״̬��������Ϣ��
�����Ϣ�� �����Ѱ�װ���������װ·����ж����Ϣ�ȡ�
���ܼ�������Ϣ�� ���� CPU ʹ���ʡ��ڴ�ʹ���ʡ����̻������ͳ����Ϣ��
�¼���־��Ϣ�� ����ϵͳ����ȫ��Ӧ�ó����¼���־�е��¼���Ϣ��
*/


// ����Ƿ��� Windows 11 ����߰汾
bool IsWindows11OrNewer()
{
    // ��ʼ�� COM ��
    HRESULT hr = CoInitializeEx(0, COINIT_MULTITHREADED);
    if (FAILED(hr))
    {
        std::cerr << "Failed to initialize COM library" << std::endl;
        return false;
    }

    // ��ʼ����ȫ����
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

    // ���� WMI ��λ��
    IWbemLocator* pLoc = nullptr;
    hr = CoCreateInstance(CLSID_WbemLocator, 0, CLSCTX_INPROC_SERVER, IID_IWbemLocator, (LPVOID*)&pLoc);

    if (FAILED(hr))
    {
        CoUninitialize();
        std::cerr << "Failed to create IWbemLocator object" << std::endl;
        return false;
    }

    // ���� WMI ����
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

    // ִ�� WMI ��ѯ
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

    // ������ѯ���
    IWbemClassObject* pclsObj = nullptr;
    ULONG uReturn = 0;

    while (pEnumerator)
    {
        hr = pEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);

        if (uReturn == 0)
            break;

        VARIANT vtProp;
        // ��ȡ Version ����ֵ
        hr = pclsObj->Get(L"Version", 0, &vtProp, 0, 0);

        if (SUCCEEDED(hr))
        {
            // ��ӡ Version ����ֵ
            std::wcout << L"Version : " << vtProp.bstrVal << std::endl;
            VariantClear(&vtProp);
        }

        pclsObj->Release();
    }

    // �ͷ���Դ
    pSvc->Release();
    pLoc->Release();
    pEnumerator->Release();
    CoUninitialize();

    return true;
}



void ShowSystemInfo()
{
    SYSTEM_INFO si;
    GetSystemInfo(&si); //.8: ��ʾ������� 8 λ������������� 8 λ��������䡣
    printf("�ڴ��ҳ��С:0x%.8X�������ڴ���ʼ:0x%.8X�������ڴ����:0x%.8X \n",
        si.dwPageSize, si.lpMinimumApplicationAddress, si.lpMaximumApplicationAddress);

    printf("����������:%d\n", si.dwNumberOfProcessors);

    printf("����������:");
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

    printf("�������ܹ�:");
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
