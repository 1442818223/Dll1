#include<Windows.h>
#include<stdio.h>
#include <tchar.h>
DWORD EnumerateFileInDirectory(LPCTSTR szPath)
{
/*
  LPTSTR lstrcat(
  LPTSTR lpString1,  // Ŀ���ַ��������ַ���2׷�ӵ����ַ�����ĩβ
  LPCTSTR lpString2  // Ҫ׷�ӵ��ַ���
   );
*/
	WIN32_FIND_DATA FindFileData;  //WIN32_FIND_DATA �ļ����Խṹ��
	HANDLE hListFile;
	TCHAR szFilePath[MAX_PATH];
	lstrcpy(szFilePath, szPath);
	lstrcat(szFilePath, TEXT("\\*")); //  \\*��ʾ��ӡ���е��ļ�
	   
/*
  FindFirstFile �������ڼ�����ָ�����ļ�����ƥ����ļ���Ŀ¼����Ϣ
  HANDLE FindFirstFile(
  LPCTSTR           lpFileName,           // �ļ��������ļ�·��
  LPWIN32_FIND_DATA lpFindFileData         // ָ�� WIN32_FIND_DATA �ṹ��ָ�룬���ڴ洢�ļ���Ϣ
  );
  ��������ɹ��������������ĵ�һ���ļ���Ŀ¼�ľ�����˾�������ں������Ҳ�����
*/
	hListFile = FindFirstFile(szFilePath, &FindFileData);
	if (hListFile == INVALID_HANDLE_VALUE)
	{
		printf("����:%d\n", GetLastError());
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
				printf("<����>");
			}
			if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN) {
				printf("<����>");
			}
			if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
				printf("<DIR>");
			}
			printf("\n");
			printf("\n");


			  //FindNextFile�ҽ��������ļ���Ŀ¼�ľ��,����ΪFindFirstFile�ɹ����صľ��
		} while (FindNextFile(hListFile, &FindFileData));
	}


	return 0;
}

int main()
{
	EnumerateFileInDirectory(TEXT("C:"));

	return 0;
}