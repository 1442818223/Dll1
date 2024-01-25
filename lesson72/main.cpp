#include <stdio.h>
#include <windows.h>
#include <string.h>
#include<tchar.h>
#include <locale.h>


int main()
{
	HANDLE hHeap1, hHeap2, hHeap3;
	DWORD dwHeapNum;
	PVOID lpMem1, lpMem2, lpMem3;
	PVOID lpReAlloc1, lpReAlloc2;


	SYSTEM_INFO si;
	GetSystemInfo(&si);
	                    
	//创建堆              不要序列化           页面大小               页数
	hHeap1 = HeapCreate(HEAP_NO_SERIALIZE, si.dwPageSize * 2, si.dwPageSize * 10);
	if (hHeap1 == NULL)
	{
		printf("创建堆失败:%d\n", GetLastError());
		return 1;
	}
	printf("创建堆成功,初始大2页，最大是10页\n");

	hHeap2 = HeapCreate(HEAP_NO_SERIALIZE, 0, 0);
	if (hHeap1 == NULL)
	{
		printf("创建堆失败:%d\n", GetLastError());
		return 1;
	}
	printf("创建堆成功,初始大1页，可以增长\n");

	//获得当前进程堆的个数
	dwHeapNum = GetProcessHeaps(0, NULL);
	if (dwHeapNum == 0) {
		printf("GetProcessHeaps error: %d\n", GetLastError());
		return 3;
	}
	printf("当前进程一共有%d个堆\n", dwHeapNum);

	//在堆上分配内存 
	lpMem1 = HeapAlloc(hHeap1, HEAP_ZERO_MEMORY, si.dwPageSize * 3);
	if (lpMem1 == NULL)
	{
		printf("HeapAlloc error : %d\n", GetLastError());
		return 4;
	}
	printf("在堆上分配内存成功，起始地址:Ox%x\n", lpMem1);

	             //重新在堆上分配内存大小(地址可能与原来的不一样)                            
	lpReAlloc1 = HeapReAlloc(hHeap1, HEAP_ZERO_MEMORY, lpMem1, si.dwPageSize * 11);
	                                                           //11页已经超过堆的大小
	if (lpReAlloc1 == NULL)
	{
		printf("HeapRealloc error: %d\n", GetLastError());
	}

	SIZE_T dwHeapBlockSize;//获取在堆上分配的内存的大小
	dwHeapBlockSize = HeapSize(hHeap1, HEAP_NO_SERIALIZE, lpMem1);
	if (dwHeapBlockSize == -1)
	{
		printf("Get HeapBlockSize error: %d\n",GetLastError());
		return 6;
	}
	printf("堆上分配的内在块大小;0x%x\n",dwHeapBlockSize);

	     //在堆上释放内存
	if (!HeapFree(hHeap1, HEAP_NO_SERIALIZE, lpMem1))
	{
		printf("HeapFree error:%d\n", GetLastError());
		return 7;
	}
	printf("在堆上释放内存成功\n");

         //销毁堆
	if (!HeapDestroy(hHeap1)) {
		printf("HeapDestroy error : %d\n", GetLastError());
		return 9;
	}
	printf("销毁堆成功\n");

	//在进程的默认堆上分配内存
	hHeap3 = GetProcessHeap();
	lpMem3 = HeapAlloc(hHeap3, HEAP_NO_SERIALIZE, si.dwPageSize * 3); 
	if (lpMem3 == NULL)
	{
		printf("HeapAlloc error : %d\n", GetLastError());
		return 10;
	}
	//在进程默认堆上释放内存
	printf("在进程默认堆上分配内存成功\n");
	if (!HeapFree(hHeap3,HEAP_NO_SERIALIZE, lpMem3)) 
	{
		printf("HeapFree error : %d\n", GetLastError());
		return 11;
	}
	printf("在进程默认堆上释放内存成功\n");







	//GlobalAlloc只能在本进程的堆上分配内存
	HGLOBAL hMem;
	hMem = GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT, 1000);
	
	LPVOID lpMem;
	lpMem = GlobalLock(hMem);
	lstrcpy((LPTSTR)lpMem, _T("this is a string"));
	
	GlobalUnlock(hMem);

	SIZE_T memSize = GlobalSize(hMem);

	_tprintf(_T("内存地址:Ox%.8x\n"),lpMem);
	_tprintf(_T("内存大小:Ox%d\n"), memSize);
	_tprintf(_T("内存内容: %s\n"), lpMem);
	
	//在原来分配的堆内存上重新分配堆内存
	hMem = GlobalReAlloc(hMem, 2000, GHND);

	GlobalFree(hMem); 

	system("pause");
	return 0;
}
