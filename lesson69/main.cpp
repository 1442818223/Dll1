#include<Windows.h>
#include <stdio.h>
int main()
{
/*
typedef struct _MEMORYSTATUSEX {
  DWORD dwLength;              // �ṹ��Ĵ�С�����ֽ�Ϊ��λ������ָ���ṹ��İ汾��Ϣ
  DWORD dwMemoryLoad;          // ��ʾ�����ڴ�ʹ���ʣ���Χ�� 0 �� 100
  DWORDLONG ullTotalPhys;      // ��ʾ�����ڴ���ܴ�С�����ֽ�Ϊ��λ
  DWORDLONG ullAvailPhys;      // ��ʾ�����ڴ�Ŀ��ô�С�����ֽ�Ϊ��λ
  DWORDLONG ullTotalPageFile;  // ��ʾ�����ļ����ܴ�С�����ֽ�Ϊ��λ
  DWORDLONG ullAvailPageFile;  // ��ʾ�����ļ��Ŀ��ô�С�����ֽ�Ϊ��λ
  DWORDLONG ullTotalVirtual;   // ��ʾ�����ڴ���ܴ�С�����ֽ�Ϊ��λ
  DWORDLONG ullAvailVirtual;   // ��ʾ�����ڴ�Ŀ��ô�С�����ֽ�Ϊ��λ
  DWORDLONG ullAvailExtendedVirtual;  // ������δʹ��
} MEMORYSTATUSEX, *LPMEMORYSTATUSEX;
�����ļ�:�ڲ���ϵͳ�У������ڴ���ָ�������ڴ治��ʱ��ͨ�����������ݴ洢�������ϵĽ����ļ��У���ʵ�ֳ������������ڴ�ռ����չ��
ҳ�潻��:����������ʱ������ϵͳ�������һ���ּ��ص������ڴ��С���������ڴ治�㣬����ϵͳ�Ὣ�����ҳ�潻���������ϵĽ����ļ��С�
*/
	MEMORYSTATUSEX memstatusex;
	memstatusex.dwLength = sizeof(memstatusex);
	GlobalMemoryStatusEx(&memstatusex);
	
	printf("ȫ�������ڴ�:%I64u G\n", memstatusex.ullTotalPhys /1024 /1024 /1024);
	printf("���������ڴ�:%I64u G\n",  memstatusex.ullAvailPhys /1024 /1024 /1024);

	printf("ȫ��ҳ���ļ�:%I64u G\n", memstatusex.ullTotalPageFile / 1024 / 1024 / 1024);
	printf("����ҳ���ļ�:%I64u G\n", memstatusex.ullAvailPageFile / 1024 / 1024 / 1024);

	printf("ȫ�������ڴ�:%I64u G\n", memstatusex.ullTotalVirtual / 1024 / 1024 / 1024);
	printf("���������ڴ�:%I64u G\n", memstatusex.ullAvailVirtual / 1024 / 1024 / 1024);
	

	
	system(" pause");
	return 0;
}