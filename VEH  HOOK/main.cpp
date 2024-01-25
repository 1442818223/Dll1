#include<stdio.h>
#include<windows.h>
#include<iostream>
using namespace std;


typedef int (WINAPI* _MessageBoxA)(
	HWND hWnd,
	LPCSTR lpText,
	LPCSTR lpCaption,
	UINT uType
	);
_MessageBoxA MyMessageBoxA = 0; //向上调用

LONG WINAPI PvectoredExceptionHandler(_EXCEPTION_POINTERS* ExceptionInfo)
{
	if (ExceptionInfo->ExceptionRecord->ExceptionAddress == MyMessageBoxA) {
		printf("异常处理器!\n");
		ExceptionInfo->ContextRecord->Eip += 2; //每个call里面的首部 mov edi,edi是留出来HOOK的 ,所以就这样处理下


		DWORD arg2Addr = ExceptionInfo->ContextRecord->Esp + 8; //对应的参数2
		const char* str = "被hook了";
		*(char**)arg2Addr = (char*)str;



		return EXCEPTION_CONTINUE_EXECUTION;
	}
	return EXCEPTION_CONTINUE_SEARCH;
}

DWORD WINAPI ThreadProc(
	_In_ LPVOID lpParameter
)
{
	MessageBoxA(0, "helloThread", "提示", MB_OK);
	return 0;
}

int main() {

	//SetUnhandledExceptionFilter();  //给当前进程的所有线程都设置异常 SEH


	//1.设置硬件断点
	DWORD breakPoint0 = 0;
	HMODULE hModule = LoadLibraryA("user32.dll");//有的话就算是拿句柄
	MyMessageBoxA = (_MessageBoxA)GetProcAddress(hModule, "MessageBoxA");
	breakPoint0 = (DWORD)MyMessageBoxA;
	//将断点地址写入到DRO
	CONTEXT context{};
	context.ContextFlags = CONTEXT_DEBUG_REGISTERS;
	context.Dr0 = breakPoint0;                             
	context.Dr7 = 1;
	SetThreadContext(GetCurrentThread(), &context);//异常处理器
	AddVectoredExceptionHandler(1, PvectoredExceptionHandler);     //VEH
	//MessageBoxA 触发了异常
	MessageBoxA(0, "hello", "提示", MB_OK);


	HANDLE hThread = CreateThread(NULL, 0, ThreadProc, 0, CREATE_SUSPENDED, 0);
	SetThreadContext(hThread, &context);  //设置线程异常处理器  //也可以用汇编
	ResumeThread(hThread);



	system("pause");
	return 0;







}