#include <Windows.h>
#include <TlHelp32.h>
#include <stdio.h>

int main() {
    // ������ǰ���̵Ŀ���
    PROCESSENTRY32 processEntry = { 0 };//PROCESSENTRY32 �� Windows API �е�һ���ṹ�壬�����������̵���Ϣ��
    HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    // ����Ƿ�ɹ������˿���
    if (hProcessSnap == INVALID_HANDLE_VALUE)
        return -1;

    // ��ʹ�ýṹ֮ǰ���ýṹ�Ĵ�С
    processEntry.dwSize = sizeof(PROCESSENTRY32);

    // ��ȡ�����еĵ�һ������
    BOOL bRet = Process32First(hProcessSnap, &processEntry);

    // ���������е����н���
    while (bRet) {
        // ��ӡ�йؽ��̵���Ϣ
        wprintf(L"ProcessID: %lu, Name: %s\n", processEntry.th32ProcessID, processEntry.szExeFile);

        // ��ȡ�����е���һ������
        bRet = Process32Next(hProcessSnap, &processEntry);
    }

    // �رնԿ��յľ��
    CloseHandle(hProcessSnap);

  
    system("pause");
    return 0;
}
