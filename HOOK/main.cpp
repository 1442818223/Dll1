#include<windows.h>
#include<iostream>
//hook函数

//定义MessageBoxW的函数指针(类型)
using PFN = int (WINAPI*)(
	_In_opt_ HWND hWnd,
	_In_opt_ LPCWSTR lpText,
	_In_opt_ LPCWSTR lpcaption,
	_In_ UINT uType);
PFN pfn = nullptr;   //指向同一个地方

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
* 用于更改指定地址范围的访问权限和属性。
BOOL VirtualProtect(
  LPVOID lpAddress,//指向要更改的内存区域的起始地址。
  SIZE_T dwSize,// 要更改的内存区域的大小，以字节为单位。
  DWORD  flNewProtect,//新的访问权限和属性。
  PDWORD lpflOldProtect//指向变量的指针，该变量将接收原始访问权限和属性。
);
*/
void Hook32(void* src, void* dst, int len) {
	DWORD old;
	VirtualProtect(src, len, PAGE_EXECUTE_READWRITE, &old);
	memset(src, 0x90, len);//避免尾部与下条指令相结合
	*(BYTE*)src = 0xe9;          //强制类型转换了,否则就算不出来
	uintptr_t ralativeAddress = (uintptr_t)dst - (uintptr_t)src - 5; //跳转是走跳的那条指令下面的那条指令开始计算的(0,1,2,3...)
	*(DWORD*)((BYTE*)src + 1) = ralativeAddress; //jmp到我们写的MyMsgBoxW上面去
	VirtualProtect(src, len, old, &old);
}


//使用 Trampoline 创建了一个网关函数，将 MessageBoxW 的执行流重定向到 MyMsgBoxW。
// 然后通过 Trampoline 函数，将原始的 MessageBoxW 临时重定向到网关函数。
/*
* 用于在进程的虚拟地址空间中分配内存。   需要时才映射到物理内存
LPVOID VirtualAlloc(
  LPVOID lpAddress,//指定所分配内存的首地址，如果为 NULL，系统会自动选择一个地址。
  SIZE_T dwSize,//指定分配的内存大小，以字节为单位。
  DWORD  flAllocationType,//内存分配的类型。
  DWORD  flProtect// 分配的内存页的访问保护。
);
*/   
void* Trampoline(void* src, void* dst, int len)
{                                         //5:一个字节jmp(e9)+4个字节地址(32位)   
	BYTE* gateway = (BYTE*)VirtualAlloc(0, len + 5, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	memcpy(gateway, src, len);
	*(gateway + len ) = 0xe9;
	*(DWORD*)(gateway + len + 1) = (BYTE*)src - gateway - 5;  //jmp要HOOK的函数
	                                   //系统函数永远在高位原则
	Hook32(src, dst, len);            
	return gateway;
}

int main()
{          
//程序运行在 Windows 操作系统中，并且已经链接了用户界面库（user32.dll）时。
// 在 Windows 操作系统中，许多 API 函数是以动态链接库（DLL）的形式提供的。
// 这些函数的地址在运行时可以被解析，因此可以通过直接使用函数名来获取其地址
	pfn = (PFN)Trampoline(MessageBoxW, MyMsgBoxW, 5);//布置过程
	//gateway的前len个长度仍然保存的是原函数,强转成PFN以便使用原始的函数
	pfn(0, L"123456", 0, 0);//函数指针

	MessageBoxW(0, L"Hello", 0, 0);
	MessageBoxW(0, L"Hello", 0, 0);
	MessageBoxW(0, L"Hello", 0, 0);
	

	
	return 0;
}
