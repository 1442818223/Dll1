#include<Windows.h>
#include <stdio.h>
int main()
{
	TCHAR szSystemDirectory[MAX_PATH];
	TCHAR szWindowsDirectory[MAX_PATH];
	GetSystemDirectory(szSystemDirectory, MAX_PATH);
	GetWindowsDirectory(szWindowsDirectory, MAX_PATH);
	printf("ϵͳĿ¼:\t%s\n", szSystemDirectory);
	printf("WindowsĿ¼:\t%s\n", szWindowsDirectory);

	DWORD dwComputerNameLen = MAX_COMPUTERNAME_LENGTH + 1;
	TCHAR szComputerName[MAX_COMPUTERNAME_LENGTH + 1];
	GetComputerName(szComputerName, &dwComputerNameLen);
	printf("�������:%s\n", szComputerName);

	DWORD dwUserNameLen = 64;
	TCHAR szUserName[64];
	GetUserName(szUserName, &dwUserNameLen);
	printf("�û���:\t%s\n", szUserName);

	BOOL fResult;
	int aMouseInfo[3];             //��ȡ������
	fResult = SystemParametersInfo(SPI_GETMOUSE, 0, &aMouseInfo, 0);//SystemParametersInfoϵͳ������Ϣ����
	if (fResult)
		aMouseInfo[2] = 2 * aMouseInfo[2];//���� aMouseInfo[2] ͨ����ʾ���������Ȼ��ٶȡ�

	                     //����������               //��ʾ����������������ϵͳ�ı�֪ͨ
	SystemParametersInfo(SPI_SETMOUSE, 0, aMouseInfo, SPIF_SENDCHANGE);
	printf("ok \n");


	system(" pause");
	return 0;
}