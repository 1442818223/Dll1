#include <stdio.h>
#include <windows.h>
#include <string.h>

#define MEM_BLOCK_SIZE 32

int main()
{

	HANDLE hHeap = GetProcessHeap();
	LPVOID lpMem1;
	LPVOID lpMem2;
	                     
	         //在当前进程的堆上分配内存    清零            
	lpMem1 = HeapAlloc(hHeap, HEAP_ZERO_MEMORY,MEM_BLOCK_SIZE);
	                     //不清零
	lpMem2 = HeapAlloc(hHeap, 0, MEM_BLOCK_SIZE);

	//指定MEM_BLOCK_SIZE大小填充为0xAA       
	FillMemory(lpMem1,MEM_BLOCK_SIZE, 0xAA);

	//让第一块内存中的MEM_BLOCK_SIZE大小的数据拷贝到第二块
	MoveMemory(lpMem2, lpMem1, MEM_BLOCK_SIZE); //与 MoveMemory 不同的是，CopyMemory 在复制完数据后，源区域的内容仍然有效。
	CopyMemory(lpMem2, lpMem1,MEM_BLOCK_SIZE);


	HeapFree(hHeap,0, lpMem1); 
	HeapFree(hHeap,0, lpMem2);


}