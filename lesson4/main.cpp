#include<stdio.h>
#include<Windows.h>
#include <wchar.h>

//通过WIN32_FILE_ATTRIBUTE_DATA 中的 FILETIME 解析出适合本地的标准时间
VOID ShowFileTime(PFILETIME lptime) {
	FILETIME ftLocal;
	SYSTEMTIME st;
	FileTimeToLocalFileTime(lptime, &ftLocal);
	FileTimeToSystemTime(&ftLocal, &st);
	printf("%d年%#02d月%#02d日，%#02d:%#02d:%#02d\n", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
	
}

int main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR  lpCmdLine, int nCmdShow) {
	/*
typedef struct _WIN32_FILE_ATTRIBUTE_DATA {
    DWORD dwFileAttributes;// 文件的属性，表示文件的特性，如只读、隐藏等
    FILETIME ftCreationTime;//文件的创建时间
    FILETIME ftLastAccessTime;//文件的上次访问时间
    FILETIME ftLastWriteTime;// 文件的上次写入时间
    DWORD nFileSizeHigh;//文件大小的高 32 位（高位 DWORD）
    DWORD nFileSizeLow;//件大小的低 32 位（低位 DWORD）
} WIN32_FILE_ATTRIBUTE_DATA, *LPWIN32_FILE_ATTRIBUTE_DATA;
*/
	WIN32_FILE_ATTRIBUTE_DATA wfad;

/*
	BOOL GetFileAttributesEx(
  LPCWSTR                lpFileName,    // 文件或目录的名称
  GET_FILEEX_INFO_LEVELS fInfoLevelId,  // 返回的信息级别
  LPVOID                 lpFileInformation // 用于存储文件属性信息的结构体指针
);
*/
	if (!GetFileAttributesEx(L"main.cpp", GetFileExInfoStandard, &wfad)) {
		printf("获取文件属性失败:%d\n", GetLastError());
		return -1;
	}


	printf("创建时间:\n");
	ShowFileTime(&wfad.ftCreationTime);

	printf("最后访问时间:\n");
	ShowFileTime(&wfad.ftLastAccessTime);

	printf("最后写入时间:\n");
	ShowFileTime(&wfad.ftLastWriteTime);

}


