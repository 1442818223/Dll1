#include <Windows.h>
#include <stdio.h>
int main(int argc, PTCHAR argv[]) {
	//printf("����:%d\n", argc);
	//printf("��һ��:%s\n", argv[0]);
	//printf("�ڶ���:%s\n", argv[1]);
	//printf("������:%s\n", argv[2]);

	if (0 == lstrcmp("-d", argv[1]) && argc == 3) {
		if (!DeleteFile(argv[2])) {
			printf("ɾ���ļ���������:%x\n", GetLastError());
		}
		else {
			printf("ɾ���ļ��ɹ�\n");
		}
	}

	else if (0 == lstrcmp("-c", argv[1]) && argc == 4) {
		if (!CopyFile(argv[2], argv[3], TRUE)) {
			if (GetLastError() == 0x50) {
				printf("�ļ�%s�Ѿ�����,�Ƿ񸲸�? y/n: ", argv[3]);
				if ('y' == getchar())
				{
					if (!CopyFile(argv[2], argv[3], FALSE)) {
						printf("�����ļ���������:%d\n", GetLastError());
					}
					else {
						printf("�����ļ��ɹ�\n");
					}
				}
				else {
					return 0;
				}
			}
		}
		else {
			printf("�����ļ��ɹ�\n");
		}
	}

	else if (0 == lstrcmp("-m", argv[1]) && argc == 4) {
		if (!MoveFile(argv[2], argv[3])) {
			printf("�������ļ���������:%d\n", GetLastError());
		}
		else {
			printf("�������ļ��ɹ�.\n");
		}
	}
	else {
		printf("��������\n");
	}

	system(" pause");
	return 0;
}