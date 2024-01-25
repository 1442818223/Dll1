#include<Windows.h>
#include<stdio.h>
#include <tchar.h>
DWORD EnumerateFileInDirectory(LPCTSTR szPath)
{
/*
  LPTSTR lstrcat(
  LPTSTR lpString1,  // 目标字符串，将字符串2追加到此字符串的末尾
  LPCTSTR lpString2  // 要追加的字符串
   );
*/
	WIN32_FIND_DATA FindFileData;  //WIN32_FIND_DATA 文件属性结构体
	HANDLE hListFile;
	TCHAR szFilePath[MAX_PATH];
	lstrcpy(szFilePath, szPath);
	lstrcat(szFilePath, TEXT("\\*")); //  \\*表示打印所有的文件
	   
/*
  FindFirstFile 函数用于检索与指定的文件名相匹配的文件或目录的信息
  HANDLE FindFirstFile(
  LPCTSTR           lpFileName,           // 文件名或者文件路径
  LPWIN32_FIND_DATA lpFindFileData         // 指向 WIN32_FIND_DATA 结构的指针，用于存储文件信息
  );
  如果函数成功，返回搜索到的第一个文件或目录的句柄。此句柄可用于后续查找操作。
*/
	hListFile = FindFirstFile(szFilePath, &FindFileData);
	if (hListFile == INVALID_HANDLE_VALUE)
	{
		printf("错误:%d\n", GetLastError());
		return 1;
	}

	else
	{
		do {

			if (lstrcmp(FindFileData.cFileName,TEXT(".")) == 0 ||
				lstrcmp(FindFileData.cFileName,TEXT("..")) == 0)
			{
				continue;
			}

			_tprintf(_T("%s\n"), FindFileData.cFileName);

			if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_ENCRYPTED) {
				printf("<加密>");
			}
			if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN) {
				printf("<隐藏>");
			}
			if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
				printf("<DIR>");
			}
			printf("\n");
			printf("\n");


			  //FindNextFile找接下来的文件或目录的句柄,参数为FindFirstFile成功返回的句柄
		} while (FindNextFile(hListFile, &FindFileData));
	}


	return 0;
}

int main()
{
	EnumerateFileInDirectory(TEXT("C:"));

	return 0;
}