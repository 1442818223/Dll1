#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
	BOOL bResult;
	//簇
	DWORD dwTotalClusters;
	DWORD dwFreeClusters;
	//扇区
	DWORD dwSectPerClust;
	//扇区字节数
	DWORD dwBytesPerSect;
	bResult = GetDiskFreeSpace(TEXT("C:"), &dwSectPerClust, &dwBytesPerSect, &dwFreeClusters, &dwTotalClusters);
	if (bResult) {
		printf("\n使用GetDiskFreeSpace获取磁盘空间信息\n"); 
		printf("总簇数量:\t\t\t%d\n", dwTotalClusters);  
		printf("空闲的簇数量:\t\t\t%d\n", dwFreeClusters);
		printf("每簇的扇区数量:\t \t \t%d\n", dwSectPerClust);
		printf("每扇区字节数:\t \t \t%d\n", dwBytesPerSect);

		printf("磁盘总容量: \t\t\t%I64d\n",(DWORD64)dwTotalClusters * (DWORD64)dwSectPerClust * (DWORD64)dwBytesPerSect);
		printf("磁盘空闲容量: \t\t\t%I64d\n",(DWORD64)dwFreeClusters * (DWORD64)dwSectPerClust * (DWORD64)dwBytesPerSect);


	}
	
	DWORD64 qwFreeBytes,qwFreeBytesToCaller, qwTotalBytes;
	bResult = GetDiskFreeSpaceEx(TEXT("C:"),
		(PULARGE_INTEGER)&qwFreeBytesToCaller,
		(PULARGE_INTEGER)&qwTotalBytes,
		(PULARGE_INTEGER)&qwFreeBytes);
	if (bResult) {
		printf("\n使用GetDiskFreeSpaceEx获取磁盘空间信息\n"); 
		printf("磁盘总容量:\t \t \t%I64d\n", qwTotalBytes);//I64：表示64位整数类型。d：表示输出的是一个十进制整数
		printf("可用的磁盘空闲容量:\t \t%I64d \n",qwFreeBytes);
		printf("磁盘空闲容量:\t \t \t%I64d\n",qwFreeBytesToCaller);
	}


	system("pause");
	return 0;
}