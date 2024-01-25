#include <Windows.h>
#include <stdio.h>

HANDLE g_hSema = 0;//�ź������


DWORD CALLBACK TestProc(LPVOID pParam) {
	while (1) {
		WaitForSingleObject(g_hSema, INFINITE);
		printf("*********\n");
	}
}
/*
* Windows API �����ڴ����ź�������ĺ�����
HANDLE CreateSemaphore(
  LPSECURITY_ATTRIBUTES lpSemaphoreAttributes,//һ��ָ�� SECURITY_ATTRIBUTES �ṹ��ָ�룬����ָ���´������ź�������İ�ȫ���ԡ�ͨ����Ϊ NULL����ʾʹ��Ĭ�ϰ�ȫ���ԡ�
  LONG                  lInitialCount,//�ź����ĳ�ʼ����ֵ����ָ�����ź������õĳ�ʼ��Դ������
  LONG                  lMaximumCount,//�ź�����������ֵ����ָ�����ź�������ӵ�е������Դ������
  LPCTSTR               lpName//�ź�����������ơ�����Ϊ NULL����ʾ����һ�������ź�������
);
*/
int main() {

	g_hSema = CreateSemaphore(NULL, 3, 10, NULL);//�����ź���
	                                  //10����˼������Ҫ�����ź�����ʼֵReleaseSemaphore�Ĵ�С���ܳ���10
	DWORD nID = 0;
	HANDLE hThread = CreateThread(NULL, 0, TestProc, NULL, 0, &nID);

	getchar();             //�������õ��ź������ܳ���ָ���ź�����������ֵ10
	ReleaseSemaphore(g_hSema, 5, NULL); //�����ź�����ʼֵΪ5

	WaitForSingleObject(hThread, INFINITE);
	CloseHandle(g_hSema);
}