#include <Windows.h>
#include <stdio.h>

HANDLE g_hEvent = 0;//接收事件句柄
DWORD CALLBACK PrintProc(LPVOID pParam) {
	while (1) {
		WaitForSingleObject(g_hEvent, INFINITE);//有信号就能通过WaitForSingleObject
		printf("****************\n");

		ResetEvent(g_hEvent);//将事件重置为无信号
//不调用ResetEvent(g_hEvent);就需要将CreateEvent的第二个参数设置为false
	}
}

DWORD CALLBACK CtrlProc(LPVOID pParam) {
	while (1) {
		Sleep(1000);
		SetEvent(g_hEvent);//将事件设置为有信号
	}
	return 0;
}

/*
* Windows API 中用于创建事件对象的函数。
HANDLE CreateEvent(
  LPSECURITY_ATTRIBUTES lpEventAttributes,//一个指向 SECURITY_ATTRIBUTES 结构的指针，用于指定新创建的事件对象的安全属性。通常设为 NULL，表示使用默认安全属性。
  BOOL                  bManualReset,//一个布尔值，指定事件对象的类型。如果为 TRUE，则事件对象是手动重置的；如果为 FALSE，则是自动重置的。
  BOOL                  bInitialState,//一个布尔值，指定事件对象的初始状态。如果为 TRUE，则事件对象初始时有信号；如果为 FALSE，则初始时无信号。
  LPCTSTR               lpName//事件对象的名称。可以为 NULL，表示创建一个无名事件对象；
);
*/
int main()
{                                    //初始时无信号
	g_hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	                            //如果为 FALSE，则是自动复位的(按线程的时间片顺序)。
	DWORD nID = 0;
	HANDLE hThread[2] = { 0 };                  
	hThread[0] = CreateThread(NULL, 0, PrintProc, NULL, 0, &nID);
	hThread[1] = CreateThread(NULL, 0, CtrlProc, NULL, 0, &nID);
	WaitForMultipleObjects(2, hThread, TRUE, INFINITE);

	CloseHandle(g_hEvent);
	return 0;
}
