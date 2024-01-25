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
	                    
	//������              ��Ҫ���л�           ҳ���С               ҳ��
	hHeap1 = HeapCreate(HEAP_NO_SERIALIZE, si.dwPageSize * 2, si.dwPageSize * 10);
	if (hHeap1 == NULL)
	{
		printf("������ʧ��:%d\n", GetLastError());
		return 1;
	}
	printf("�����ѳɹ�,��ʼ��2ҳ�������10ҳ\n");

	hHeap2 = HeapCreate(HEAP_NO_SERIALIZE, 0, 0);
	if (hHeap1 == NULL)
	{
		printf("������ʧ��:%d\n", GetLastError());
		return 1;
	}
	printf("�����ѳɹ�,��ʼ��1ҳ����������\n");

	//��õ�ǰ���̶ѵĸ���
	dwHeapNum = GetProcessHeaps(0, NULL);
	if (dwHeapNum == 0) {
		printf("GetProcessHeaps error: %d\n", GetLastError());
		return 3;
	}
	printf("��ǰ����һ����%d����\n", dwHeapNum);

	//�ڶ��Ϸ����ڴ� 
	lpMem1 = HeapAlloc(hHeap1, HEAP_ZERO_MEMORY, si.dwPageSize * 3);
	if (lpMem1 == NULL)
	{
		printf("HeapAlloc error : %d\n", GetLastError());
		return 4;
	}
	printf("�ڶ��Ϸ����ڴ�ɹ�����ʼ��ַ:Ox%x\n", lpMem1);

	             //�����ڶ��Ϸ����ڴ��С(��ַ������ԭ���Ĳ�һ��)                            
	lpReAlloc1 = HeapReAlloc(hHeap1, HEAP_ZERO_MEMORY, lpMem1, si.dwPageSize * 11);
	                                                           //11ҳ�Ѿ������ѵĴ�С
	if (lpReAlloc1 == NULL)
	{
		printf("HeapRealloc error: %d\n", GetLastError());
	}

	SIZE_T dwHeapBlockSize;//��ȡ�ڶ��Ϸ�����ڴ�Ĵ�С
	dwHeapBlockSize = HeapSize(hHeap1, HEAP_NO_SERIALIZE, lpMem1);
	if (dwHeapBlockSize == -1)
	{
		printf("Get HeapBlockSize error: %d\n",GetLastError());
		return 6;
	}
	printf("���Ϸ�������ڿ��С;0x%x\n",dwHeapBlockSize);

	     //�ڶ����ͷ��ڴ�
	if (!HeapFree(hHeap1, HEAP_NO_SERIALIZE, lpMem1))
	{
		printf("HeapFree error:%d\n", GetLastError());
		return 7;
	}
	printf("�ڶ����ͷ��ڴ�ɹ�\n");

         //���ٶ�
	if (!HeapDestroy(hHeap1)) {
		printf("HeapDestroy error : %d\n", GetLastError());
		return 9;
	}
	printf("���ٶѳɹ�\n");

	//�ڽ��̵�Ĭ�϶��Ϸ����ڴ�
	hHeap3 = GetProcessHeap();
	lpMem3 = HeapAlloc(hHeap3, HEAP_NO_SERIALIZE, si.dwPageSize * 3); 
	if (lpMem3 == NULL)
	{
		printf("HeapAlloc error : %d\n", GetLastError());
		return 10;
	}
	//�ڽ���Ĭ�϶����ͷ��ڴ�
	printf("�ڽ���Ĭ�϶��Ϸ����ڴ�ɹ�\n");
	if (!HeapFree(hHeap3,HEAP_NO_SERIALIZE, lpMem3)) 
	{
		printf("HeapFree error : %d\n", GetLastError());
		return 11;
	}
	printf("�ڽ���Ĭ�϶����ͷ��ڴ�ɹ�\n");







	//GlobalAllocֻ���ڱ����̵Ķ��Ϸ����ڴ�
	HGLOBAL hMem;
	hMem = GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT, 1000);
	
	LPVOID lpMem;
	lpMem = GlobalLock(hMem);
	lstrcpy((LPTSTR)lpMem, _T("this is a string"));
	
	GlobalUnlock(hMem);

	SIZE_T memSize = GlobalSize(hMem);

	_tprintf(_T("�ڴ��ַ:Ox%.8x\n"),lpMem);
	_tprintf(_T("�ڴ��С:Ox%d\n"), memSize);
	_tprintf(_T("�ڴ�����: %s\n"), lpMem);
	
	//��ԭ������Ķ��ڴ������·�����ڴ�
	hMem = GlobalReAlloc(hMem, 2000, GHND);

	GlobalFree(hMem); 

	system("pause");
	return 0;
}
