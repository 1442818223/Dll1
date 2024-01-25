//API文件操作
#include<Windows.h>
#include <stdio.h>

#define BUF_SIZE 256

//方法一:利用ReadFile/WriteFile进行文件复制
/*
int main(int argc, LPTSTR argv[])
{
	HANDLE hIn, hOut;
	DWORD nIn, nOut;
	CHAR buffer[BUF_SIZE];

	if (argc != 3)
	{
		printf("Usage : cpw file1 file2\n");
		return 1;
	}
			 //配置属性里面要选择多字节字符集才行
	hIn = CreateFile(argv[1], GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hIn == INVALID_HANDLE_VALUE) {
		printf(" Cannot open input file. Error: %x\n",GetLastError());
		return 2;
	}

	hOut = CreateFile(argv[2], GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hOut == INVALID_HANDLE_VALUE)
	{
		printf("Cannot open output file. Error: %x\n", GetLastError());
		return 3;
	}

	while (ReadFile(hIn, buffer, BUF_SIZE, &nIn, NULL) && nIn > 0) {
		WriteFile(hOut, buffer, nIn, &nOut, NULL);
		if (nIn != nOut)
		{
			printf("Fatal write error : %x\n", GetLastError());
			return 4;

		}
	}

	CloseHandle(hIn);
	CloseHandle(hOut);

	return 0;
}

*/

//方法二:利用CopyFile进行文件复制
int main(int argc, LPTSTR argv[])
{
	if (argc != 3)
	{
		printf("Usage : cpcf file1 file2\n");
		return 1;
	}


	/*
	BOOL CopyFile(
    LPCTSTR lpExistingFileName, // 源文件名
    LPCTSTR lpNewFileName,      // 目标文件名
    BOOL    bFailIfExists       // 如果设置为 TRUE，并且目标文件已存在，函数将返回 FALSE。
    );
	*/
	if (!CopyFile(argv[1], argv[2], FALSE)) {
		printf("CopyFile Error: %x]n", GetLastError());
		return 2;
	}

	return 0;
}




