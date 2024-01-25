#include <iostream>
#include<stdio.h>
#include<windows.h>


int main()
{


	//1.打开目标进程                                         //PID
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, 0);

	DWORD buffSize = strlen("d://test.dl1") + 1;
	//2.申请远程内存空间
	char* str = (char*)VirtualAllocEx(hProcess, 0, buffSize, MEM_COMMIT, PAGE_READWRITE);


	DWORD realWrite = 0;
	//3.将dll文件路径写入到内存
	WriteProcessMemory(hProcess, str, "d://test.dll", buffSize, &realWrite);

	//4.创建远程线程             //基本上每个进程都会加载KENER32.DLL这个模块,这个模块又恰巧包含LoadLibraryA,和LPTHREAD_START_ROUTINE类型一致
	HANDLE hThread = CreateRemoteThread(hProcess, 0, 0, (LPTHREAD_START_ROUTINE)LoadLibraryA, str, 0, 0);
	WaitForSingleObject(hThread, -1);

	VirtualFreeEx(hProcess, str, 0, MEM_RELEASE);
	CloseHandle(hThread);
	CloseHandle(hProcess);


	return 0;
}
