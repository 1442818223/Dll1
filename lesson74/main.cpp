#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <tchar.h>


int main()
{

	//���������ڴ��ǰ�4096�ֽڴ�С�ĵ�ַ����ȥ�����
	SIZE_T sizevirtual = 4000;//����ϣ����4000�ֽ�,�����ǰ�ҳ�ֵ�,һҳ4096
	LPVOID lpRound = (LPVOID)0x100000ff;//����ϣ�������λ�ø��������Ƿ���  ,ʵ���ǰ�4096�ֽڴ�С�ĵ�ַ����ȥ�����   
	MEMORY_BASIC_INFORMATION mbi;


/*
LPVOID VirtualAlloc(
  LPVOID lpAddress,   // ָ����������ڴ�������׵�ַ��һ��Ϊ NULL����ʾ��ϵͳ�Զ�ѡ��
  SIZE_T dwSize,      // ָ����������ڴ�����Ĵ�С�����ֽ�Ϊ��λ
  DWORD  flAllocationType,   // ָ���ڴ�ķ������ͣ����� MEM_COMMIT ��ʾ�ύ�ڴ棬MEM_RESERVE ��ʾ�����ڴ�
  DWORD  flProtect   // ָ���ڴ�����ķ���Ȩ�ޣ����� PAGE_READWRITE ��ʾ�ɶ�д
);
*/                                                    //  Ԥ��           �ύ        ҳ������:����д
	LPVOID lpAddress = VirtualAlloc(lpRound, sizevirtual, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	if (lpAddress == NULL) {
		printf("VirtualAlloc error: %d\n", GetLastError());
		return 1;
	}
	printf("Alloc : MEM_COMMIT|MEM_RESERVE\n");

	CopyMemory(lpAddress,_T("hello"), lstrlen(_T("hello"))*sizeof(TCHAR)); 
	_tprintf(_T("�����ڴ��е�����:%s\n"), lpAddress);
	

/*
typedef struct _MEMORY_BASIC_INFORMATION {
  PVOID  BaseAddress;      // �ڴ��Ļ���ַ
  PVOID  AllocationBase;   // �����ڴ��Ļ���ַ
  DWORD  AllocationProtect;// �����ڴ��ķ��ʱ�������
  SIZE_T RegionSize;       // �ڴ��Ĵ�С�����ֽ�Ϊ��λ
  DWORD  State;            // �ڴ���״̬������ MEM_COMMIT��MEM_RESERVE ��
  DWORD  Protect;          // �ڴ���ҳ�汣������
  DWORD  Type;             // �ڴ������ͣ����� MEM_PRIVATE��MEM_IMAGE ��
} MEMORY_BASIC_INFORMATION, *PMEMORY_BASIC_INFORMATION;
*/
	//��ѯ������ڴ���Ϣ
	VirtualQuery(lpAddress, &mbi, sizeof(mbi));
	printf("BaseAddress:0x%x\n", mbi.BaseAddress);//ʵ��
	printf("AllocationBase:Ox%x\n", mbi.AllocationBase);//ʵ��
	printf("AllocationProtect:Ox%x\n", mbi.Protect);//�������ʱ�ı�������
	printf("RegionSize : %u\n", mbi.RegionSize);//ʵ�ʷ��䵽�Ĵ�С(��ҳ)
	printf("State : Ox%x\n", mbi.State);//�ڴ������ͣ����� MEM_PRIVATE��MEM_IMAGE ��
	printf("Protect : Ox%x\n", mbi.Protect);//ʵ�ʵı�������
	printf("Type :Ox%x\n", mbi.Type);// �ڴ������ͣ����� MEM_PRIVATE��MEM_IMAGE ��

	//�ͷ��ڴ�
	if (!VirtualFree(lpRound,sizevirtual, MEM_DECOMMIT)) {
		printf("VirtualFree error : %d", GetLastError()); 
		return 2; 
	}
	printf("Free: DECOMMIT\n");

		return 0;

}