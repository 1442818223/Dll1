#include<windows.h>
#include<iostream>
//hook����

//����MessageBoxW�ĺ���ָ��(����)
using PFN = int (WINAPI*)(
	_In_opt_ HWND hWnd,
	_In_opt_ LPCWSTR lpText,
	_In_opt_ LPCWSTR lpcaption,
	_In_ UINT uType);
PFN pfn = nullptr;   //ָ��ͬһ���ط�

int WINAPI MyMsgBoxW(
	_In_opt_ HWND hWnd,
	_In_opt_ LPCWSTR lpText,
	_In_opt_ LPCWSTR lpcaption,
	_In_ UINT uType)
{
	lpText = L"22222";

	return pfn(hWnd, lpText, lpcaption, uType); 
}


/*
* ���ڸ���ָ����ַ��Χ�ķ���Ȩ�޺����ԡ�
BOOL VirtualProtect(
  LPVOID lpAddress,//ָ��Ҫ���ĵ��ڴ��������ʼ��ַ��
  SIZE_T dwSize,// Ҫ���ĵ��ڴ�����Ĵ�С�����ֽ�Ϊ��λ��
  DWORD  flNewProtect,//�µķ���Ȩ�޺����ԡ�
  PDWORD lpflOldProtect//ָ�������ָ�룬�ñ���������ԭʼ����Ȩ�޺����ԡ�
);
*/
void Hook32(void* src, void* dst, int len) {
	DWORD old;
	VirtualProtect(src, len, PAGE_EXECUTE_READWRITE, &old);
	memset(src, 0x90, len);//����β��������ָ������
	*(BYTE*)src = 0xe9;          //ǿ������ת����,������㲻����
	uintptr_t ralativeAddress = (uintptr_t)dst - (uintptr_t)src - 5; //��ת������������ָ�����������ָ�ʼ�����(0,1,2,3...)
	*(DWORD*)((BYTE*)src + 1) = ralativeAddress; //jmp������д��MyMsgBoxW����ȥ
	VirtualProtect(src, len, old, &old);
}


//ʹ�� Trampoline ������һ�����غ������� MessageBoxW ��ִ�����ض��� MyMsgBoxW��
// Ȼ��ͨ�� Trampoline ��������ԭʼ�� MessageBoxW ��ʱ�ض������غ�����
/*
* �����ڽ��̵������ַ�ռ��з����ڴ档   ��Ҫʱ��ӳ�䵽�����ڴ�
LPVOID VirtualAlloc(
  LPVOID lpAddress,//ָ���������ڴ���׵�ַ�����Ϊ NULL��ϵͳ���Զ�ѡ��һ����ַ��
  SIZE_T dwSize,//ָ��������ڴ��С�����ֽ�Ϊ��λ��
  DWORD  flAllocationType,//�ڴ��������͡�
  DWORD  flProtect// ������ڴ�ҳ�ķ��ʱ�����
);
*/   
void* Trampoline(void* src, void* dst, int len)
{                                         //5:һ���ֽ�jmp(e9)+4���ֽڵ�ַ(32λ)   
	BYTE* gateway = (BYTE*)VirtualAlloc(0, len + 5, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	memcpy(gateway, src, len);
	*(gateway + len ) = 0xe9;
	*(DWORD*)(gateway + len + 1) = (BYTE*)src - gateway - 5;  //jmpҪHOOK�ĺ���
	                                   //ϵͳ������Զ�ڸ�λԭ��
	Hook32(src, dst, len);            
	return gateway;
}

int main()
{          
//���������� Windows ����ϵͳ�У������Ѿ��������û�����⣨user32.dll��ʱ��
// �� Windows ����ϵͳ�У���� API �������Զ�̬���ӿ⣨DLL������ʽ�ṩ�ġ�
// ��Щ�����ĵ�ַ������ʱ���Ա���������˿���ͨ��ֱ��ʹ�ú���������ȡ���ַ
	pfn = (PFN)Trampoline(MessageBoxW, MyMsgBoxW, 5);//���ù���
	//gateway��ǰlen��������Ȼ�������ԭ����,ǿת��PFN�Ա�ʹ��ԭʼ�ĺ���
	pfn(0, L"123456", 0, 0);//����ָ��

	MessageBoxW(0, L"Hello", 0, 0);
	MessageBoxW(0, L"Hello", 0, 0);
	MessageBoxW(0, L"Hello", 0, 0);
	

	
	return 0;
}
