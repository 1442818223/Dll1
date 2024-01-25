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
_MessageBoxA MyMessageBoxA = 0; //���ϵ���

LONG WINAPI PvectoredExceptionHandler(_EXCEPTION_POINTERS* ExceptionInfo)
{
	if (ExceptionInfo->ExceptionRecord->ExceptionAddress == MyMessageBoxA) {
		printf("�쳣������!\n");
		ExceptionInfo->ContextRecord->Eip += 2; //ÿ��call������ײ� mov edi,edi��������HOOK�� ,���Ծ�����������


		DWORD arg2Addr = ExceptionInfo->ContextRecord->Esp + 8; //��Ӧ�Ĳ���2
		const char* str = "��hook��";
		*(char**)arg2Addr = (char*)str;



		return EXCEPTION_CONTINUE_EXECUTION;
	}
	return EXCEPTION_CONTINUE_SEARCH;
}

DWORD WINAPI ThreadProc(
	_In_ LPVOID lpParameter
)
{
	MessageBoxA(0, "helloThread", "��ʾ", MB_OK);
	return 0;
}

int main() {

	//SetUnhandledExceptionFilter();  //����ǰ���̵������̶߳������쳣 SEH


	//1.����Ӳ���ϵ�
	DWORD breakPoint0 = 0;
	HMODULE hModule = LoadLibraryA("user32.dll");//�еĻ��������þ��
	MyMessageBoxA = (_MessageBoxA)GetProcAddress(hModule, "MessageBoxA");
	breakPoint0 = (DWORD)MyMessageBoxA;
	//���ϵ��ַд�뵽DRO
	CONTEXT context{};
	context.ContextFlags = CONTEXT_DEBUG_REGISTERS;
	context.Dr0 = breakPoint0;                             
	context.Dr7 = 1;
	SetThreadContext(GetCurrentThread(), &context);//�쳣������
	AddVectoredExceptionHandler(1, PvectoredExceptionHandler);     //VEH
	//MessageBoxA �������쳣
	MessageBoxA(0, "hello", "��ʾ", MB_OK);


	HANDLE hThread = CreateThread(NULL, 0, ThreadProc, 0, CREATE_SUSPENDED, 0);
	SetThreadContext(hThread, &context);  //�����߳��쳣������  //Ҳ�����û��
	ResumeThread(hThread);



	system("pause");
	return 0;







}