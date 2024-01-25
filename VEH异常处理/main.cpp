#include<stdio.h>
#include<windows.h>
#include<iostream>
using namespace std;

//编译配置
//连接器->->高级->映像具有安全异常处理程序->否

//SEH处理函数
EXCEPTION_DISPOSITION myExceptHandler(
	struct _EXCEPTION_RECORD* ExceptionRecord,  //这里记录着异常时保存的信息
	PVOID EstablisherFrame,
	PCONTEXT pcontext,                 //异常时的各种寄存器信息会传过来
	PVOID DispatcherContext) {
	
	MessageBoxA(0, "异常处理代码执行了!", "提示", MB_OK);//此处没有解决异常会死循环,一直回到这个位置
	//所以要解决
	pcontext->Eip = pcontext->Eip + 4;

	DWORD isDebuger = 0;
	_asm
	{
		mov eax, fs: [0x18]//teb
		mov eax, [eax + 0x30]//peb
		movzx eax, byte ptr[eax + 2]          //peb结构里面存的有是否被检测的值,1为被调试
		mov isDebuger, eax
	}
	if (isDebuger) {
		MessageBoxA(0, "检测到调试器", "警告", MB_OK);
		exit(0);
	}


	return ExceptionContinueExecution;
}



//VEH处理函数
LONG WINAPI PvectoredExceptionHandler(
	_EXCEPTION_POINTERS* ExceptionInfo
)
{
	printf("VEH处理了异常!\n");
	ExceptionInfo->ContextRecord->Eip += 4;

	
	return EXCEPTION_CONTINUE_EXECUTION;


}



int main() {

	                      
	                         //1表示插入链表头部,0尾部
	AddVectoredExceptionHandler(1,PvectoredExceptionHandler);//VEH



	DWORD exceptionFunAddr = (DWORD)myExceptHandler;

	_asm
	{
		push exceptionFunAddr
		mov eax, fs: [0]
		push eax
		mov fs : [0] , esp                //将SEH异常处理链表结构给系统  也可以用SetThreadContext
	}


	char* str = NULL;
	str[0] = 'a';


	printf("hello,66666666666666666\n");

	system("pause");
	return 0;
}