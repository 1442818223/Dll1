#include <Windows.h>
#include<iostream>
DWORD  TestProc(LPVOID pszText) {
	char* a = (char*)pszText;

	while (1) {
		Sleep(1000);
		std::cout << a << std::endl;
		printf("线程1:%s\n", a);
	}

	return 0;

}

DWORD TestProc2(LPVOID pszText) {

	char* a = (char*)pszText;

	while (1) {
		Sleep(1000);
		std::cout << a << std::endl;
		printf("线程2:%s\n", a);

	}

	return 0;
}
/*
* Windows API 中用于创建一个新的线程的函数。
HANDLE CreateThread(
  LPSECURITY_ATTRIBUTES   lpThreadAttributes,//一个指向 SECURITY_ATTRIBUTES 结构的指针，用于指定新线程的安全属性，通常设为 NULL。
  SIZE_T                  dwStackSize,//新线程的初始堆栈大小，设为 0 表示使用默认大小。
  LPTHREAD_START_ROUTINE  lpStartAddress,//一个指向线程函数的指针，线程将从这个函数开始执行。
  __drv_aliasesMem LPVOID lpParameter,//传递给线程函数的参数。
  DWORD                   dwCreationFlags,//线程的创建标志，例如是否立即启动线程等。
  LPDWORD                 lpThreadId//个指向接收新线程标识符的变量的指针，如果不关心线程标识符，可以设为 NULL。
);
*/
int main() {
	DWORD nID = 0;
	const char* pszText = "wodedsasfas";
	HANDLE hThread = CreateThread(NULL, 0, TestProc, (LPVOID)pszText, 0, &nID);


	WaitForSingleObject(hThread,INFINITE);//注意:一直等待(阻塞在这).直到线程一执行完才会往下走###########

	                                                                   //创建好后先挂起
	HANDLE hThread2 = CreateThread(NULL, 0, TestProc2, (LPVOID)pszText, CREATE_SUSPENDED, &nID);


	getchar();

	SuspendThread(hThread);//使线程挂起
	ResumeThread(hThread2);//使线程恢复 



	while (1) {
		Sleep(1000);
	}

	return 0;
}
