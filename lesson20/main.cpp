//递归遍历所有文件
#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <stdio.h>
#include <tchar.h>

DWORD dwTotalFileNum = 0;//计数器

DWORD ListAllFileInDirectory(LPCTSTR szPath) {
    WIN32_FIND_DATA FindFileData;
    HANDLE hListFile;
    TCHAR szFilePath[MAX_PATH];
    TCHAR szFullPath[MAX_PATH];

    lstrcpy(szFilePath, szPath);
    lstrcat(szFilePath, TEXT("\\*"));
                
               //1,
    hListFile = FindFirstFile(szFilePath, &FindFileData);
    if (hListFile == INVALID_HANDLE_VALUE) {
        _tprintf(_T("错误:%d\n"), GetLastError());
        return 1;
    }
    else {
        do {
            if (lstrcmp(FindFileData.cFileName, TEXT(".")) == 0 ||
                lstrcmp(FindFileData.cFileName, TEXT("..")) == 0) {
                continue;
            }

            _stprintf(szFullPath, _T("%s\\%s"), szPath, FindFileData.cFileName);//格式化字符串
            dwTotalFileNum++;

            _tprintf(_T("\n%d\t%s\t"), dwTotalFileNum, szFullPath);

            if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                _tprintf(_T("<DIR>"));
                ListAllFileInDirectory(szFullPath);
            }

            printf("\n");
         
                 //2,
        } while (FindNextFile(hListFile, &FindFileData));
    }
    return 0;
}

int main() {

    ListAllFileInDirectory(TEXT("D:\\XFTP\\Languages"));

    _tprintf(_T("\n"));
    system("pause");
    return 0;
}
