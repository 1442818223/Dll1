#include<Windows.h>
#include <stdio.h>
int main()
{
/*
typedef struct _MEMORYSTATUSEX {
  DWORD dwLength;              // 结构体的大小，以字节为单位，用于指定结构体的版本信息
  DWORD dwMemoryLoad;          // 表示物理内存使用率，范围从 0 到 100
  DWORDLONG ullTotalPhys;      // 表示物理内存的总大小，以字节为单位
  DWORDLONG ullAvailPhys;      // 表示物理内存的可用大小，以字节为单位
  DWORDLONG ullTotalPageFile;  // 表示交换文件的总大小，以字节为单位
  DWORDLONG ullAvailPageFile;  // 表示交换文件的可用大小，以字节为单位
  DWORDLONG ullTotalVirtual;   // 表示虚拟内存的总大小，以字节为单位
  DWORDLONG ullAvailVirtual;   // 表示虚拟内存的可用大小，以字节为单位
  DWORDLONG ullAvailExtendedVirtual;  // 保留，未使用
} MEMORYSTATUSEX, *LPMEMORYSTATUSEX;
交换文件:在操作系统中，虚拟内存是指在物理内存不足时，通过将部分数据存储到磁盘上的交换文件中，以实现程序运行所需内存空间的扩展。
页面交换:当程序运行时，操作系统将程序的一部分加载到物理内存中。如果物理内存不足，操作系统会将不活动的页面交换到磁盘上的交换文件中。
*/
	MEMORYSTATUSEX memstatusex;
	memstatusex.dwLength = sizeof(memstatusex);
	GlobalMemoryStatusEx(&memstatusex);
	
	printf("全部物理内存:%I64u G\n", memstatusex.ullTotalPhys /1024 /1024 /1024);
	printf("可用物理内存:%I64u G\n",  memstatusex.ullAvailPhys /1024 /1024 /1024);

	printf("全部页面文件:%I64u G\n", memstatusex.ullTotalPageFile / 1024 / 1024 / 1024);
	printf("可用页面文件:%I64u G\n", memstatusex.ullAvailPageFile / 1024 / 1024 / 1024);

	printf("全部虚拟内存:%I64u G\n", memstatusex.ullTotalVirtual / 1024 / 1024 / 1024);
	printf("可用虚拟内存:%I64u G\n", memstatusex.ullAvailVirtual / 1024 / 1024 / 1024);
	

	
	system(" pause");
	return 0;
}