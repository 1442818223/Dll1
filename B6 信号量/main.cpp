#include <Windows.h>
#include <stdio.h>

HANDLE g_hSema = 0;//信号量句柄


DWORD CALLBACK TestProc(LPVOID pParam) {
	while (1) {
		WaitForSingleObject(g_hSema, INFINITE);
		printf("*********\n");
	}
}
/*
* Windows API 中用于创建信号量对象的函数。
HANDLE CreateSemaphore(
  LPSECURITY_ATTRIBUTES lpSemaphoreAttributes,//一个指向 SECURITY_ATTRIBUTES 结构的指针，用于指定新创建的信号量对象的安全属性。通常设为 NULL，表示使用默认安全属性。
  LONG                  lInitialCount,//信号量的初始计数值。它指定了信号量可用的初始资源数量。
  LONG                  lMaximumCount,//信号量的最大计数值。它指定了信号量可以拥有的最大资源数量。
  LPCTSTR               lpName//信号量对象的名称。可以为 NULL，表示创建一个无名信号量对象；
);
*/
int main() {

	g_hSema = CreateSemaphore(NULL, 3, 10, NULL);//创建信号量
	                                  //10的意思是往后要重置信号量初始值ReleaseSemaphore的大小不能超过10
	DWORD nID = 0;
	HANDLE hThread = CreateThread(NULL, 0, TestProc, NULL, 0, &nID);

	getchar();             //这里重置的信号量不能超过指定信号量的最大计数值10
	ReleaseSemaphore(g_hSema, 5, NULL); //重置信号量初始值为5

	WaitForSingleObject(hThread, INFINITE);
	CloseHandle(g_hSema);
}