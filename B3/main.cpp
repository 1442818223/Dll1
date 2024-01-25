#include <Windows.h>
#include<iostream>

//原子锁函数(只能对运算符做原子锁操作)


long g_value = 0;

DWORD  TestProc1(LPVOID q) {                 //函数类型必须写对
	for (int i = 0; i < 100000; i++) {
		//g_value++;
		InterlockedIncrement(&g_value); //原子锁做++
	}
	return 0;
}
DWORD  TestProc2(LPVOID q) {
	for (int i = 0; i < 100000; i++) {
		//g_value++;
		InterlockedIncrement(&g_value);  //锁住执行后,要是时间片耗尽,没执行完跳到另一个线程去,此时g_value还是上锁状态,
	}                                    //那么线程二就不会去上锁,也不会执行,直到时间耗尽,在回来
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