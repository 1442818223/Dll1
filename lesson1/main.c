#include<stdio.h>
#include<Windows.h>
#include <wchar.h>


int main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR  lpCmdLine, int nCmdShow) {

	//下面这么写在c++里面不行
   //    LPSTR  SW = "dwadwa";  //typedef char* LPSTR;

	LPSTR szString = "Windows data type ,string";  //CHAR   窄字符

	printf("%s", szString);


	// 通过窄字符计算宽字符字符串的长度**********
	//size_t mbstowcs(wchar_t *dest, const char *src, size_t n);
	  //dest：指向用于存储宽字符的缓冲区的指针。可以为 NULL，此时函数将仅计算转换后的字符数，而不进行实际的转换。
	size_t wideStrLen = mbstowcs(NULL, szString, 0);//mbstowcs函数用于将多字节字符转换为宽字符
	if (wideStrLen == (size_t)-1) {   //(size_t)-1 通常被用作错误指示符，表示函数执行失败。           
		perror("mbstowcs failed");
		return EXIT_FAILURE;
	}

	// 分配缓冲区
	wchar_t* wszString = (wchar_t*)malloc((wideStrLen + 1) * sizeof(wchar_t));
	if (wszString == NULL) {
		perror("Memory allocation failed");
		return EXIT_FAILURE;
	}

	// 进行转换
//errno_t mbstowcs_s(size_t * pReturnValue, wchar_t* wcstr, size_t sizeInWords, const char* mbstr, size_t count);
	//pReturnValue：用于存储成功转换的字符数（不包括 null 终止符）的指针
	//wcstr：指向用于存储宽字符的缓冲区的指针。
	//sizeInWords：缓冲区的大小（以宽字符为单位），即 wcstr 缓冲区的元素个数。
	//mbstr：指向要转换的多字节字符串的指针。
	//count：要转换的多字节字符数，包括 null 终止符在内。
	mbstowcs_s(NULL, wszString, wideStrLen + 1, szString, wideStrLen);//如果操作成功，返回零。

	//// 输出宽字符的字符串
	//wprintf(L"Wide String: %ls\n", wszString);

	//// 释放内存
	//free(wszString);


	MessageBox(NULL, wszString, TEXT("标题"), MB_OK); //LPCWSTR= WCHAR

	wchar_t lpString[120]; //char

	/*void CopyMemory(
		_Out_       PVOID Destination,    PVOID=void*
		_In_  const VOID * Source,
		_In_        SIZE_T Length
	);*/
	//CopyMemory(lpString, wszString, lstrlen(wszString) + 1);
	//CopyMemory 是一个执行原始内存复制的函数。如果你想复制字符串，最好使用 strcpy（窄字符串）或 wcscpy（宽字符串）。
	wcscpy_s(lpString, sizeof(lpString) / sizeof(wchar_t), wszString);

	MessageBox(NULL, lpString, TEXT("标题"), MB_OK);

	DWORD dwMax = 0xFFFFFFFFFF;  //unsigned long
	INT iMax; //int

	HANDLE h; //句柄
	HICON hicon;//图标句柄
	HINSTANCE hinstance;//实例句柄
	HKEY hYey;//注册表句柄
	HMODULE hModule;//模块句柄
	HWND hWnd;//窗口句柄

	/*HANDLE CreateFile(
  LPCWSTR               lpFileName,          // 文件或设备的名称
  DWORD                 dwDesiredAccess,     // 访问权限
  DWORD                 dwShareMode,         // 共享模式
  LPSECURITY_ATTRIBUTES lpSecurityAttributes,// 安全属性
  DWORD                 dwCreationDisposition, // 如何创建或打开文件
  DWORD                 dwFlagsAndAttributes,  // 文件属性和标志
  HANDLE                hTemplateFile        // 指向一个用于复制文件或文件属性的可选模板文件的句柄
);
*/
	HANDLE hFileRead;
	hFileRead = CreateFile(L"侠盗猎车手5（GTA5）.txt", //创建文件 文件存在的话就是打开文件
		GENERIC_READ,  //读
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,  //打开文件
		FILE_ATTRIBUTE_NORMAL,
		NULL);   //通常为 NULL
	if (hFileRead == INVALID_HANDLE_VALUE) {
		printf("Cannot open file. Error: %x\n", GetLastError());
		return -1;
	}
	DWORD nIn;
	CHAR buffer[256];
	DWORD BUF_SIZE = 256;
	/*BOOL ReadFile(
  HANDLE       hFile,          // 文件句柄或 I/O 设备句柄
  LPVOID       lpBuffer,       // 用于存储读取数据的缓冲区
  DWORD        nNumberOfBytesToRead, // 要读取的字节数
  LPDWORD      lpNumberOfBytesRead,   // 用于存储实际读取的字节数
  LPOVERLAPPED lpOverlapped    // 用于异步操作的 OVERLAPPED 结构
);
*/
	while (ReadFile(hFileRead,
		buffer,
		BUF_SIZE,
		&nIn,
		NULL) && nIn > 0)
	{
		printf("%s\n", buffer);

	}
	CloseHandle(hFileRead);

}
