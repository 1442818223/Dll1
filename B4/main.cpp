#include <Windows.h>
#include<iostream>

HANDLE g_hMutex = 0;//���ջ�����

DWORD  TestProc(LPVOID pszText) {
	char* a = (char*)pszText;

	while (1) {
		WaitForSingleObject(g_hMutex, INFINITE);//��
		
		for (int i = 0; i < strlen(a); i++) {
			printf("%c", a[i]);
			Sleep(125);
		}
		printf("\n");

		ReleaseMutex(g_hMutex);//�ͷ�
	}

	return 0;

}

DWORD TestProc2(LPVOID pszText) {

	char* a = (char*)pszText;
	while (1) {
		WaitForSingleObject(g_hMutex, INFINITE);//��
		
		for (int i = 0; i < strlen(a); i++) {
			printf("%c", a[i]);
			Sleep(125);
		}
		printf("\n");

		ReleaseMutex(g_hMutex);//�ͷ�
	}

	return 0;
}

/*
* Windows API �����ڴ����������ĺ�����
HANDLE CreateMutex(
  LPSECURITY_ATTRIBUTES lpMutexAttributes,//һ��ָ�� SECURITY_ATTRIBUTES �ṹ��ָ�룬����ָ���´����Ļ������İ�ȫ���ԡ�ͨ����Ϊ NULL����ʾʹ��Ĭ�ϰ�ȫ���ԡ�
  BOOL                  bInitialOwner,//һ������ֵ��ָ����ʼ�����ߡ����Ϊ TRUE��������߳�ӵ�л�����������Ȩ�����Ϊ FALSE���򻥳���������Ȩ��ϵͳ���֡�
  LPCTSTR               lpName//�����������ơ�����Ϊ NULL����ʾ����һ�������Ļ������
);
*/
int main() {
	g_hMutex = CreateMutex(NULL, FALSE, NULL);//����


	DWORD nID = 0;
	const char* pszText = "********";
	const char* pszText2 = "--------";
	HANDLE hThread = CreateThread(NULL, 0, TestProc, (LPVOID)pszText, 0, &nID);

	HANDLE hThread2 = CreateThread(NULL, 0, TestProc2, (LPVOID)pszText2, 0, &nID);


	getchar();

	CloseHandle(g_hMutex);//�ͷ�

	return 0;
}
