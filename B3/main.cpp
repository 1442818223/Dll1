#include <Windows.h>
#include<iostream>

//ԭ��������(ֻ�ܶ��������ԭ��������)


long g_value = 0;

DWORD  TestProc1(LPVOID q) {                 //�������ͱ���д��
	for (int i = 0; i < 100000; i++) {
		//g_value++;
		InterlockedIncrement(&g_value); //ԭ������++
	}
	return 0;
}
DWORD  TestProc2(LPVOID q) {
	for (int i = 0; i < 100000; i++) {
		//g_value++;
		InterlockedIncrement(&g_value);  //��סִ�к�,Ҫ��ʱ��Ƭ�ľ�,ûִ����������һ���߳�ȥ,��ʱg_value��������״̬,
	}                                    //��ô�̶߳��Ͳ���ȥ����,Ҳ����ִ��,ֱ��ʱ��ľ�,�ڻ���
	return 0;
}

int main() {

	DWORD nID = 0;
	HANDLE hThread[2];
	hThread[0] = CreateThread(NULL, 0, TestProc1, NULL, 0, &nID);
	hThread[1] = CreateThread(NULL, 0, TestProc2, NULL, 0, &nID);
	WaitForMultipleObjects(2, hThread, TRUE, INFINITE);

	printf(" % d\n", g_value);

	return 0;



}