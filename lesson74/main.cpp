#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <tchar.h>


int main()
{

	//分配虚拟内存是按4096字节大小的地址对齐去分配的
	SIZE_T sizevirtual = 4000;//我们希望分4000字节,但都是按页分的,一页4096
	LPVOID lpRound = (LPVOID)0x100000ff;//我们希望在这个位置附近给我们分配  ,实际是按4096字节大小的地址对齐去分配的   
	MEMORY_BASIC_INFORMATION mbi;


/*
LPVOID VirtualAlloc(
  LPVOID lpAddress,   // 指定欲分配的内存区域的首地址，一般为 NULL，表示由系统自动选择
  SIZE_T dwSize,      // 指定欲分配的内存区域的大小，以字节为单位
  DWORD  flAllocationType,   // 指定内存的分配类型，例如 MEM_COMMIT 表示提交内存，MEM_RESERVE 表示保留内存
  DWORD  flProtect   // 指定内存区域的访问权限，例如 PAGE_READWRITE 表示可读写
);
*/                                                    //  预定           提交        页面属性:读和写
	LPVOID lpAddress = VirtualAlloc(lpRound, sizevirtual, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	if (lpAddress == NULL) {
		printf("VirtualAlloc error: %d\n", GetLastError());
		return 1;
	}
	printf("Alloc : MEM_COMMIT|MEM_RESERVE\n");

	CopyMemory(lpAddress,_T("hello"), lstrlen(_T("hello"))*sizeof(TCHAR)); 
	_tprintf(_T("虚拟内存中的数据:%s\n"), lpAddress);
	

/*
typedef struct _MEMORY_BASIC_INFORMATION {
  PVOID  BaseAddress;      // 内存块的基地址
  PVOID  AllocationBase;   // 分配内存块的基地址
  DWORD  AllocationProtect;// 用于内存块的访问保护属性
  SIZE_T RegionSize;       // 内存块的大小，以字节为单位
  DWORD  State;            // 内存块的状态，比如 MEM_COMMIT、MEM_RESERVE 等
  DWORD  Protect;          // 内存块的页面保护属性
  DWORD  Type;             // 内存块的类型，比如 MEM_PRIVATE、MEM_IMAGE 等
} MEMORY_BASIC_INFORMATION, *PMEMORY_BASIC_INFORMATION;
*/
	//查询分配的内存信息
	VirtualQuery(lpAddress, &mbi, sizeof(mbi));
	printf("BaseAddress:0x%x\n", mbi.BaseAddress);//实际
	printf("AllocationBase:Ox%x\n", mbi.AllocationBase);//实际
	printf("AllocationProtect:Ox%x\n", mbi.Protect);//申请分配时的保护属性
	printf("RegionSize : %u\n", mbi.RegionSize);//实际分配到的大小(按页)
	printf("State : Ox%x\n", mbi.State);//内存块的类型，比如 MEM_PRIVATE、MEM_IMAGE 等
	printf("Protect : Ox%x\n", mbi.Protect);//实际的保护属性
	printf("Type :Ox%x\n", mbi.Type);// 内存块的类型，比如 MEM_PRIVATE、MEM_IMAGE 等

	//释放内存
	if (!VirtualFree(lpRound,sizevirtual, MEM_DECOMMIT)) {
		printf("VirtualFree error : %d", GetLastError()); 
		return 2; 
	}
	printf("Free: DECOMMIT\n");

		return 0;

}