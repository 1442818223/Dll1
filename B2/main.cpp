#include <Windows.h>
#include<iostream>
DWORD  TestProc(LPVOID pszText) {
	char* a = (char*)pszText;

	while (1) {
		Sleep(1000);
		std::cout << a << std::endl;
		printf("�߳�1:%s\n", a);
	}

	return 0;

}

DWORD TestProc2(LPVOID pszText) {

	char* a = (char*)pszText;

	while (1) {
		Sleep(1000);
		std::cout << a << std::endl;
		printf("�߳�2:%s\n", a);

	}

	return 0;
}
/*
* Windows API �����ڴ���һ���µ��̵߳ĺ�����
HANDLE CreateThread(
  LPSECURITY_ATTRIBUTES   lpThreadAttributes,//һ��ָ�� SECURITY_ATTRIBUTES �ṹ��ָ�룬����ָ�����̵߳İ�ȫ���ԣ�ͨ����Ϊ NULL��
  SIZE_T                  dwStackSize,//���̵߳ĳ�ʼ��ջ��С����Ϊ 0 ��ʾʹ��Ĭ�ϴ�С��
  LPTHREAD_START_ROUTINE  lpStartAddress,//һ��ָ���̺߳�����ָ�룬�߳̽������������ʼִ�С�
  __drv_aliasesMem LPVOID lpParameter,//���ݸ��̺߳����Ĳ�����
  DWORD                   dwCreationFlags,//�̵߳Ĵ�����־�������Ƿ����������̵߳ȡ�
  LPDWORD                 lpThreadId//��ָ��������̱߳�ʶ���ı�����ָ�룬����������̱߳�ʶ����������Ϊ NULL��
);
*/
int main() {
	DWORD nID = 0;
	const char* pszText = "wodedsasfas";
	HANDLE hThread = CreateThread(NULL, 0, TestProc, (LPVOID)pszText, 0, &nID);


	WaitForSingleObject(hThread,INFINITE);//ע��:һֱ�ȴ�(��������).ֱ���߳�һִ����Ż�������###########

	                                                                   //�����ú��ȹ���
	HANDLE hThread2 = CreateThread(NULL, 0, TestProc2, (LPVOID)pszText, CREATE_SUSPENDED, &nID);


	getchar();

	SuspendThread(hThread);//ʹ�̹߳���
	ResumeThread(hThread2);//ʹ�ָ̻߳� 



	while (1) {
		Sleep(1000);
	}

	return 0;
}
