#include<stdio.h>
#include<windows.h>
#include<iostream>
using namespace std;

//��������
//������->->�߼�->ӳ����а�ȫ�쳣�������->��

//SEH������
EXCEPTION_DISPOSITION myExceptHandler(
	struct _EXCEPTION_RECORD* ExceptionRecord,  //�����¼���쳣ʱ�������Ϣ
	PVOID EstablisherFrame,
	PCONTEXT pcontext,                 //�쳣ʱ�ĸ��ּĴ�����Ϣ�ᴫ����
	PVOID DispatcherContext) {
	
	MessageBoxA(0, "�쳣�������ִ����!", "��ʾ", MB_OK);//�˴�û�н���쳣����ѭ��,һֱ�ص����λ��
	//����Ҫ���
	pcontext->Eip = pcontext->Eip + 4;

	DWORD isDebuger = 0;
	_asm
	{
		mov eax, fs: [0x18]//teb
		mov eax, [eax + 0x30]//peb
		movzx eax, byte ptr[eax + 2]          //peb�ṹ���������Ƿ񱻼���ֵ,1Ϊ������
		mov isDebuger, eax
	}
	if (isDebuger) {
		MessageBoxA(0, "��⵽������", "����", MB_OK);
		exit(0);
	}


	return ExceptionContinueExecution;
}



//VEH������
LONG WINAPI PvectoredExceptionHandler(
	_EXCEPTION_POINTERS* ExceptionInfo
)
{
	printf("VEH�������쳣!\n");
	ExceptionInfo->ContextRecord->Eip += 4;

	
	return EXCEPTION_CONTINUE_EXECUTION;


}



int main() {

	                      
	                         //1��ʾ��������ͷ��,0β��
	AddVectoredExceptionHandler(1,PvectoredExceptionHandler);//VEH



	DWORD exceptionFunAddr = (DWORD)myExceptHandler;

	_asm
	{
		push exceptionFunAddr
		mov eax, fs: [0]
		push eax
		mov fs : [0] , esp                //��SEH�쳣��������ṹ��ϵͳ  Ҳ������SetThreadContext
	}


	char* str = NULL;
	str[0] = 'a';


	printf("hello,66666666666666666\n");

	system("pause");
	return 0;
}