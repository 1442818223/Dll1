#include<Windows.h>
#include<stdio.h>
#include <stdlib.h>
#define BUFSIZE 1024
int main() {
	CHAR szLogicalDriveStrings[BUFSIZE];
	PCHAR szDrive;
	ZeroMemory(szLogicalDriveStrings, BUFSIZE);//清零
	//GetLogicalDriveStrings找所有盘符名
	GetLogicalDriveStrings(BUFSIZE - 1, szLogicalDriveStrings);//得到的盘符字符串是:c:\\0d:\\0e:\\0每个中间隔个0
	// printf("%s\n"， szLogicalDriveStrings); 这种打印遇到\0就停止了
	szDrive = (PCHAR)szLogicalDriveStrings;
	
	do
	{     //先打印第一个
      		printf("%s\n", szDrive);
			 
			szDrive += (lstrlen(szDrive) + 1);
			

	} while (*szDrive!='\0');


	TCHAR buf[BUFSIZE]; 
	HANDLE hVol;
	BOOL bFlag;
	//FindFirstVolume 找的是第一个盘符设备号//windows内部使用的
	hVol = FindFirstVolume(buf,BUFSIZE);
	if (hVol == INVALID_HANDLE_VALUE)
	{
		printf(TEXT("No volumes found ! \n"));
		return  - 1;
	}
	printf("%s\n", buf);
	 //FindNextVolume 找接下来的盘符设备号
	while (FindNextVolume(hVol, buf, BUFSIZE)) {
		printf("%s\n", buf);
	}
	bFlag = FindVolumeClose(hVol);
	if (!bFlag) {
		printf("关闭 FindFirstVolume的句柄 失败!\n");
		return  0;
	}


    system("pause");
	return 0;
}