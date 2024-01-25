//Od����һ�����򣬳�������ִ�еĴ�����OEP������TLS�� TLS��������OEP֮ǰִ�С�
#include<Windows.h>        //�˳���������32λ,64λ�����д��
#include<iostream>
 
//һ,���ȼ��ϱ���ѡ��
#pragma comment(linker,"/INCLUDE:__tls_used") 


/*
_declspec(thread) �����������ֲ߳̾��洢��Thread Local Storage��TLS���Ĺؼ��֡�
�����߱���������������Ϊ�ֲ߳̾�������ÿ���̶߳������Լ��Ķ���ʵ����
�ڶ��̱߳���У�ʹ���ֲ߳̾��洢����ȷ��ÿ���̶߳Ա����ķ��ʶ��Ƕ����ģ������໥���š�
*/
_declspec(thread) int g_number = 100;

HANDLE hEvent = NULL;

DWORD WINAPI threadProc1(LPVOID lparam) {
	g_number = 200;
	printf("threadProc1 g_number=%d\n", g_number);

	SetEvent(hEvent);//���¼�����Ϊ���ź�
	return 0;
}
DWORD WINAPI threadProc2(LPVOID lparam) {
	
	WaitForSingleObject(hEvent, -1);

	printf("threadProc2 g_number=%d\n", g_number);
	return 0;
}


//TLS�ص������ı�׼��ʽ     //ģ���ַ        //����ԭ��    //�����ֶ� 
void NTAPI t_TlsCallBack_A(PVOID DllHandle, DWORD Reason, PVOID Reserved)
{

	if (Reason == DLL_PROCESS_ATTACH) {  //������̱�����ʱ
		printf("TLS����ִ����\n");
	}


}


/*
ע��TLS�����qCRT$XLX������
CRT��ʾʹ��C Runtime����
X��ʾ��ʶ�����
L��ʾTLS Callback section
XҲ���Ի���B~Y����һ���ַ�
*/
#pragma data_seg(".CRT$XLY")
//�洢�ص�������ַ                /////������0��β
PIMAGE_TLS_CALLBACK pTLS_CALLBACKs[]={ t_TlsCallBack_A,0} ;
#pragma data_seg()

int main() {
	                                   //��ʼʱ���ź�
	hEvent = CreateEventA(NULL, FALSE, FALSE, NULL);


	HANDLE hThread1 = CreateThread(NULL, NULL, threadProc1, NULL, NULL, NULL);
	HANDLE hThread2 = CreateThread(NULL, NULL, threadProc2, NULL, NULL, NULL);
	WaitForSingleObject(hThread1, -1);
	WaitForSingleObject(hThread2, -2);



	system("pause");
	return 0;
}