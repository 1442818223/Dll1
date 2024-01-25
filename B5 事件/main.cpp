#include <Windows.h>
#include <stdio.h>

HANDLE g_hEvent = 0;//�����¼����
DWORD CALLBACK PrintProc(LPVOID pParam) {
	while (1) {
		WaitForSingleObject(g_hEvent, INFINITE);//���źž���ͨ��WaitForSingleObject
		printf("****************\n");

		ResetEvent(g_hEvent);//���¼�����Ϊ���ź�
//������ResetEvent(g_hEvent);����Ҫ��CreateEvent�ĵڶ�����������Ϊfalse
	}
}

DWORD CALLBACK CtrlProc(LPVOID pParam) {
	while (1) {
		Sleep(1000);
		SetEvent(g_hEvent);//���¼�����Ϊ���ź�
	}
	return 0;
}

/*
* Windows API �����ڴ����¼�����ĺ�����
HANDLE CreateEvent(
  LPSECURITY_ATTRIBUTES lpEventAttributes,//һ��ָ�� SECURITY_ATTRIBUTES �ṹ��ָ�룬����ָ���´������¼�����İ�ȫ���ԡ�ͨ����Ϊ NULL����ʾʹ��Ĭ�ϰ�ȫ���ԡ�
  BOOL                  bManualReset,//һ������ֵ��ָ���¼���������͡����Ϊ TRUE�����¼��������ֶ����õģ����Ϊ FALSE�������Զ����õġ�
  BOOL                  bInitialState,//һ������ֵ��ָ���¼�����ĳ�ʼ״̬�����Ϊ TRUE�����¼������ʼʱ���źţ����Ϊ FALSE�����ʼʱ���źš�
  LPCTSTR               lpName//�¼���������ơ�����Ϊ NULL����ʾ����һ�������¼�����
);
*/
int main()
{                                    //��ʼʱ���ź�
	g_hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	                            //���Ϊ FALSE�������Զ���λ��(���̵߳�ʱ��Ƭ˳��)��
	DWORD nID = 0;
	HANDLE hThread[2] = { 0 };                  
	hThread[0] = CreateThread(NULL, 0, PrintProc, NULL, 0, &nID);
	hThread[1] = CreateThread(NULL, 0, CtrlProc, NULL, 0, &nID);
	WaitForMultipleObjects(2, hThread, TRUE, INFINITE);

	CloseHandle(g_hEvent);
	return 0;
}
