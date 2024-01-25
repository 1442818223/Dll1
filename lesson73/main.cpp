#include <stdio.h>
#include <windows.h>
#include <string.h>

#define MEM_BLOCK_SIZE 32

int main()
{

	HANDLE hHeap = GetProcessHeap();
	LPVOID lpMem1;
	LPVOID lpMem2;
	                     
	         //�ڵ�ǰ���̵Ķ��Ϸ����ڴ�    ����            
	lpMem1 = HeapAlloc(hHeap, HEAP_ZERO_MEMORY,MEM_BLOCK_SIZE);
	                     //������
	lpMem2 = HeapAlloc(hHeap, 0, MEM_BLOCK_SIZE);

	//ָ��MEM_BLOCK_SIZE��С���Ϊ0xAA       
	FillMemory(lpMem1,MEM_BLOCK_SIZE, 0xAA);

	//�õ�һ���ڴ��е�MEM_BLOCK_SIZE��С�����ݿ������ڶ���
	MoveMemory(lpMem2, lpMem1, MEM_BLOCK_SIZE); //�� MoveMemory ��ͬ���ǣ�CopyMemory �ڸ��������ݺ�Դ�����������Ȼ��Ч��
	CopyMemory(lpMem2, lpMem1,MEM_BLOCK_SIZE);


	HeapFree(hHeap,0, lpMem1); 
	HeapFree(hHeap,0, lpMem2);


}