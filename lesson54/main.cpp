#include <stdio.h>
#include <Windows.h>
#include <WtsApi32.h>

#pragma comment(lib, "WtsApi32.lib")//������������ʱ����WtsApi32.lib

int main() {
    DWORD i;
    const wchar_t* szServerName = L"DESKTOP-RF6SRB6"; //������
    HANDLE hWtsServer = WTSOpenServer(const_cast<LPWSTR>(szServerName)); // �� WTS ������// ת��Ϊ LPWSTR
  
/*
* �����о��� Terminal Services �� Remote Desktop Session Host ��RD Session Host�������������еĽ��̵ĺ�����
BOOL WTSEnumerateProcesses(  
  IN  HANDLE hServer,//ָ��Ҫ��ȡ������Ϣ�ķ������ľ����
  IN  DWORD  Reserved,//��������������Ϊ 0��
  IN  DWORD  Version,//ָ�� WTS_PROCESS_INFO �ṹ�İ汾�š���ǰ֧�ֵİ汾Ϊ 1��
  OUT PWTS_PROCESS_INFO *ppProcessInfo,//����ָ�� WTS_PROCESS_INFO �ṹ�����ָ�롣���������������Ϣ��
  OUT DWORD             *pCount//���� ���� ��Ϣ�����е�Ԫ��������
);
*/
    PWTS_PROCESS_INFO pWtspi;
    DWORD dwCount;
    // ��ȡ��ǰ WTS �������ϵĽ�����Ϣ
    if (!WTSEnumerateProcesses(hWtsServer, 0, 1, &pWtspi, &dwCount)) {
        wprintf(L"Error!"); 
        return -1;
    }

    // ��������ӡÿ�����̵���Ϣ
    for (i = 0; i < dwCount; i++) {
        wprintf(L"ProcessID: %d(%s)\n", pWtspi[i].ProcessId, pWtspi[i].pProcessName); // ʹ�ÿ��ַ���ӡ
    }

    // �ر� WTS ���������
    WTSCloseServer(hWtsServer);

    system("pause");
    return 0;
}
