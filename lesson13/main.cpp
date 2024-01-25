#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
	BOOL bResult;
	//��
	DWORD dwTotalClusters;
	DWORD dwFreeClusters;
	//����
	DWORD dwSectPerClust;
	//�����ֽ���
	DWORD dwBytesPerSect;
	bResult = GetDiskFreeSpace(TEXT("C:"), &dwSectPerClust, &dwBytesPerSect, &dwFreeClusters, &dwTotalClusters);
	if (bResult) {
		printf("\nʹ��GetDiskFreeSpace��ȡ���̿ռ���Ϣ\n"); 
		printf("�ܴ�����:\t\t\t%d\n", dwTotalClusters);  
		printf("���еĴ�����:\t\t\t%d\n", dwFreeClusters);
		printf("ÿ�ص���������:\t \t \t%d\n", dwSectPerClust);
		printf("ÿ�����ֽ���:\t \t \t%d\n", dwBytesPerSect);

		printf("����������: \t\t\t%I64d\n",(DWORD64)dwTotalClusters * (DWORD64)dwSectPerClust * (DWORD64)dwBytesPerSect);
		printf("���̿�������: \t\t\t%I64d\n",(DWORD64)dwFreeClusters * (DWORD64)dwSectPerClust * (DWORD64)dwBytesPerSect);


	}
	
	DWORD64 qwFreeBytes,qwFreeBytesToCaller, qwTotalBytes;
	bResult = GetDiskFreeSpaceEx(TEXT("C:"),
		(PULARGE_INTEGER)&qwFreeBytesToCaller,
		(PULARGE_INTEGER)&qwTotalBytes,
		(PULARGE_INTEGER)&qwFreeBytes);
	if (bResult) {
		printf("\nʹ��GetDiskFreeSpaceEx��ȡ���̿ռ���Ϣ\n"); 
		printf("����������:\t \t \t%I64d\n", qwTotalBytes);//I64����ʾ64λ�������͡�d����ʾ�������һ��ʮ��������
		printf("���õĴ��̿�������:\t \t%I64d \n",qwFreeBytes);
		printf("���̿�������:\t \t \t%I64d\n",qwFreeBytesToCaller);
	}


	system("pause");
	return 0;
}