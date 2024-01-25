//Od加载一个程序，程序最先执行的代码是OEP但加上TLS后 TLS函数会在OEP之前执行。
#include<Windows.h>        //此程序适用于32位,64位另外的写法
#include<iostream>
 
//一,首先加上编译选项
#pragma comment(linker,"/INCLUDE:__tls_used") 


/*
_declspec(thread) 是用于声明线程局部存储（Thread Local Storage，TLS）的关键字。
它告诉编译器将变量声明为线程局部变量，每个线程都有其自己的独立实例。
在多线程编程中，使用线程局部存储可以确保每个线程对变量的访问都是独立的，不会相互干扰。
*/
_declspec(thread) int g_number = 100;

HANDLE hEvent = NULL;

DWORD WINAPI threadProc1(LPVOID lparam) {
	g_number = 200;
	printf("threadProc1 g_number=%d\n", g_number);

	SetEvent(hEvent);//将事件设置为有信号
	return 0;
}
DWORD WINAPI threadProc2(LPVOID lparam) {
	
	WaitForSingleObject(hEvent, -1);

	printf("threadProc2 g_number=%d\n", g_number);
	return 0;
}


//TLS回调函数的标准格式     //模块基址        //调用原因    //保留字段 
void NTAPI t_TlsCallBack_A(PVOID DllHandle, DWORD Reason, PVOID Reserved)
{

	if (Reason == DLL_PROCESS_ATTACH) {  //如果进程被创建时
		printf("TLS函数执行了\n");
	}


}


/*
注册TLS函数﹒CRT$XLX的作用
CRT表示使用C Runtime机制
X表示标识名随机
L表示TLS Callback section
X也可以换成B~Y任意一个字符
*/
#pragma data_seg(".CRT$XLY")
//存储回调函数地址                /////必须以0结尾
PIMAGE_TLS_CALLBACK pTLS_CALLBACKs[]={ t_TlsCallBack_A,0} ;
#pragma data_seg()

int main() {
	                                   //初始时无信号
	hEvent = CreateEventA(NULL, FALSE, FALSE, NULL);


	HANDLE hThread1 = CreateThread(NULL, NULL, threadProc1, NULL, NULL, NULL);
	HANDLE hThread2 = CreateThread(NULL, NULL, threadProc2, NULL, NULL, NULL);
	WaitForSingleObject(hThread1, -1);
	WaitForSingleObject(hThread2, -2);



	system("pause");
	return 0;
}