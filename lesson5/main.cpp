#include<stdio.h>
#include<Windows.h>
#include <wchar.h>
int main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR  lpCmdLine, int nCmdShow) {
	//用于获取系统目录的路径
/*UINT GetSystemDirectory(   //UINT =unsigned int
  LPWSTR lpBuffer, // 用于存储系统目录路径的缓冲区
  UINT   uSize      // 缓冲区的大小，以字符为单位
);
*/

	/*
	typedef WCHAR TCHAR, *PTCHAR;  
	TCHAR: 这是一个宽字符类型别名，实际上是 WCHAR 的别名。
	在 Windows 编程中，TCHAR 是一个根据编译选项动态选择为 char 或 wchar_t 的类型的宽字符类型。
	如果编译选项为 Unicode，TCHAR 将被定义为 wchar_t；如果编译选项为非 Unicode（多字节字符集），
	则 TCHAR 将被定义为 char。这样设计的目的是为了方便编写同时支持 Unicode 和非 Unicode 版本的代码。

    PTCHAR: 这是一个指向 TCHAR 的指针类型别名。PTCHAR 实际上是 TCHAR* 的别名，表示指向宽字符的指针。
	*/
    TCHAR szSystemDir[MAX_PATH];//MAX_PATH系统自带宏定义260  
	GetSystemDirectory(szSystemDir, MAX_PATH);
	//printf("%s\n", szSystemDir);

	//wprintf 是打印宽字符字符串。
	wprintf(L"The system directory is:%ls\n", szSystemDir);

	/*HANDLE CreateFile( //文件存在就是打开文件 
LPCWSTR               lpFileName,          // 文件或设备的名称
DWORD                 dwDesiredAccess,     // 访问权限
DWORD                 dwShareMode,         // 共享模式
LPSECURITY_ATTRIBUTES lpSecurityAttributes,// 安全属性
DWORD                 dwCreationDisposition, // 如何创建或打开文件
DWORD                 dwFlagsAndAttributes,  // 文件属性和标志
HANDLE                hTemplateFile        // 指向一个用于复制文件或文件属性的可选模板文件的句柄
);
*/
	HANDLE hFile;
	hFile = CreateFile(L"systemroot.txt", //创建文件 文件存在的话就是打开文件
		GENERIC_WRITE,  //写
		0,
		NULL,
		CREATE_ALWAYS,  //创建文件
		FILE_ATTRIBUTE_NORMAL,
		NULL);   //通常为 NULL

/*
  BOOL WriteFile(
  HANDLE       hFile,                  // 文件句柄或 I/O 设备句柄
  LPCVOID      lpBuffer,               // 要写入的数据的缓冲区
  DWORD        nNumberOfBytesToWrite,  // 要写入的字节数
  LPDWORD      lpNumberOfBytesWritten, // 用于存储实际写入的字节数
  LPOVERLAPPED lpOverlapped            // 用于异步操作的 OVERLAPPED 结构
);
*/

	DWORD dwWritten;
	if (hFile != INVALID_HANDLE_VALUE) {
		                                    //wcslen用于计算宽字符长度 lstrlen计算窄字符长度
		if (!WriteFile(hFile, szSystemDir, wcslen(szSystemDir) * sizeof(WCHAR), &dwWritten, NULL)) {
			return GetLastError();
		}
	}
	
	CloseHandle(hFile);

}