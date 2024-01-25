#include<Windows.h>
#include <stdio.h>
int main()
{
	TCHAR szSystemDirectory[MAX_PATH];
	TCHAR szWindowsDirectory[MAX_PATH];
	GetSystemDirectory(szSystemDirectory, MAX_PATH);
	GetWindowsDirectory(szWindowsDirectory, MAX_PATH);
	printf("系统目录:\t%s\n", szSystemDirectory);
	printf("Windows目录:\t%s\n", szWindowsDirectory);

	DWORD dwComputerNameLen = MAX_COMPUTERNAME_LENGTH + 1;
	TCHAR szComputerName[MAX_COMPUTERNAME_LENGTH + 1];
	GetComputerName(szComputerName, &dwComputerNameLen);
	printf("计算机名:%s\n", szComputerName);

	DWORD dwUserNameLen = 64;
	TCHAR szUserName[64];
	GetUserName(szUserName, &dwUserNameLen);
	printf("用户名:\t%s\n", szUserName);

	BOOL fResult;
	int aMouseInfo[3];             //获取鼠标参数
	fResult = SystemParametersInfo(SPI_GETMOUSE, 0, &aMouseInfo, 0);//SystemParametersInfo系统外设信息处理
	if (fResult)
		aMouseInfo[2] = 2 * aMouseInfo[2];//其中 aMouseInfo[2] 通常表示鼠标的灵敏度或速度。

	                     //设置鼠标参数               //表示设置鼠标参数并发送系统改变通知
	SystemParametersInfo(SPI_SETMOUSE, 0, aMouseInfo, SPIF_SENDCHANGE);
	printf("ok \n");


	system(" pause");
	return 0;
}