#include<Windows.h>
#include<stdio.h>
#include <stdlib.h>
#define BUFSIZE 1024
int main() {
	CHAR szLogicalDriveStrings[BUFSIZE];
	PCHAR szDrive;
	ZeroMemory(szLogicalDriveStrings, BUFSIZE);//����
	//GetLogicalDriveStrings�������̷���
	GetLogicalDriveStrings(BUFSIZE - 1, szLogicalDriveStrings);//�õ����̷��ַ�����:c:\\0d:\\0e:\\0ÿ���м����0
	// printf("%s\n"�� szLogicalDriveStrings); ���ִ�ӡ����\0��ֹͣ��
	szDrive = (PCHAR)szLogicalDriveStrings;
	
	do
	{     //�ȴ�ӡ��һ��
      		printf("%s\n", szDrive);
			 
			szDrive += (lstrlen(szDrive) + 1);
			

	} while (*szDrive!='\0');


	TCHAR buf[BUFSIZE]; 
	HANDLE hVol;
	BOOL bFlag;
	//FindFirstVolume �ҵ��ǵ�һ���̷��豸��//windows�ڲ�ʹ�õ�
	hVol = FindFirstVolume(buf,BUFSIZE);
	if (hVol == INVALID_HANDLE_VALUE)
	{
		printf(TEXT("No volumes found ! \n"));
		return  - 1;
	}
	printf("%s\n", buf);
	 //FindNextVolume �ҽ��������̷��豸��
	while (FindNextVolume(hVol, buf, BUFSIZE)) {
		printf("%s\n", buf);
	}
	bFlag = FindVolumeClose(hVol);
	if (!bFlag) {
		printf("�ر� FindFirstVolume�ľ�� ʧ��!\n");
		return  0;
	}


    system("pause");
	return 0;
}