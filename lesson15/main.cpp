#include <Windows.h>
#include <stdio.h>
int main(int argc, PTCHAR argv[]) {
	//printf("个数:%d\n", argc);
	//printf("第一个:%s\n", argv[0]);
	//printf("第二个:%s\n", argv[1]);
	//printf("第三个:%s\n", argv[2]);

	if (0 == lstrcmp("-d", argv[1]) && argc == 3) {
		if (!DeleteFile(argv[2])) {
			printf("删除文件发生错误:%x\n", GetLastError());
		}
		else {
			printf("删除文件成功\n");
		}
	}

	else if (0 == lstrcmp("-c", argv[1]) && argc == 4) {
		if (!CopyFile(argv[2], argv[3], TRUE)) {
			if (GetLastError() == 0x50) {
				printf("文件%s已经存在,是否覆盖? y/n: ", argv[3]);
				if ('y' == getchar())
				{
					if (!CopyFile(argv[2], argv[3], FALSE)) {
						printf("复制文件发生错误:%d\n", GetLastError());
					}
					else {
						printf("复制文件成功\n");
					}
				}
				else {
					return 0;
				}
			}
		}
		else {
			printf("复制文件成功\n");
		}
	}

	else if (0 == lstrcmp("-m", argv[1]) && argc == 4) {
		if (!MoveFile(argv[2], argv[3])) {
			printf("重命名文件发生错误:%d\n", GetLastError());
		}
		else {
			printf("重命名文件成功.\n");
		}
	}
	else {
		printf("参数错误\n");
	}

	system(" pause");
	return 0;
}