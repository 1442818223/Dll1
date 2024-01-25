#include <Windows.h>
#include<iostream>

HANDLE g_hMutex = 0;//接收互斥句柄

DWORD  TestProc(LPVOID pszText) {
	char* a = (char*)pszText;

	while (1) {
		WaitForSingleObject(g_hMutex, INFINITE);//等
		
		for (int i = 0; i < strlen(a); i++) {
			printf("%c", a[i]);
			Sleep(125);
		}
		printf("\n");

		ReleaseMutex(g_hMutex);//释放
	}

	return 0;

}

DWORD TestProc2(LPVOID pszText) {

	char* a = (char*)pszText;
	while (1) {
		WaitForSingleObject(g_hMutex, INFINITE);//等
		
		for (int i = 0; i < strlen(a); i++) {
			printf("%c", a[i]);
			Sleep(125);
		}
		printf("\n");

		ReleaseMutex(g_hMutex);//释放
	}

	return 0;
}

/*
* Windows API 中用于创建互斥对象的函数。
HANDLE CreateMutex(
  LPSECURITY_ATTRIBUTES lpMutexAttributes,//一个指向 SECURITY_ATTRIBUTES 结构的指针，用于指定新创建的互斥对象的安全属性。通常设为 NULL，表示使用默认安全属性。
  BOOL                  bInitialOwner,//一个布尔值，指定初始所有者。如果为 TRUE，则调用线程拥有互斥对象的所有权；如果为 FALSE，则互斥对象的所有权由系统保持。
  LPCTSTR               lpName//互斥对象的名称。可以为 NULL，表示创建一个无名的互斥对象
);
*/
int main() {
	g_hMutex = CreateMutex(NULL, FALSE, NULL);//创建


	DWORD nID = 0;
	const char* pszText = "********";
	const char* pszText2 = "--------";
	HANDLE hThread = CreateThread(NULL, 0, TestProc, (LPVOID)pszText, 0, &nID);

	HANDLE hThread2 = CreateThread(NULL, 0, TestProc2, (LPVOID)pszText2, 0, &nID);


	getchar();

	CloseHandle(g_hMutex);//释放

	return 0;
}
