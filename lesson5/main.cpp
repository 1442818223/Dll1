#include<stdio.h>
#include<Windows.h>
#include <wchar.h>
int main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR  lpCmdLine, int nCmdShow) {
	//���ڻ�ȡϵͳĿ¼��·��
/*UINT GetSystemDirectory(   //UINT =unsigned int
  LPWSTR lpBuffer, // ���ڴ洢ϵͳĿ¼·���Ļ�����
  UINT   uSize      // �������Ĵ�С�����ַ�Ϊ��λ
);
*/

	/*
	typedef WCHAR TCHAR, *PTCHAR;  
	TCHAR: ����һ�����ַ����ͱ�����ʵ������ WCHAR �ı�����
	�� Windows ����У�TCHAR ��һ�����ݱ���ѡ�̬ѡ��Ϊ char �� wchar_t �����͵Ŀ��ַ����͡�
	�������ѡ��Ϊ Unicode��TCHAR ��������Ϊ wchar_t���������ѡ��Ϊ�� Unicode�����ֽ��ַ�������
	�� TCHAR ��������Ϊ char��������Ƶ�Ŀ����Ϊ�˷����дͬʱ֧�� Unicode �ͷ� Unicode �汾�Ĵ��롣

    PTCHAR: ����һ��ָ�� TCHAR ��ָ�����ͱ�����PTCHAR ʵ������ TCHAR* �ı�������ʾָ����ַ���ָ�롣
	*/
    TCHAR szSystemDir[MAX_PATH];//MAX_PATHϵͳ�Դ��궨��260  
	GetSystemDirectory(szSystemDir, MAX_PATH);
	//printf("%s\n", szSystemDir);

	//wprintf �Ǵ�ӡ���ַ��ַ�����
	wprintf(L"The system directory is:%ls\n", szSystemDir);

	/*HANDLE CreateFile( //�ļ����ھ��Ǵ��ļ� 
LPCWSTR               lpFileName,          // �ļ����豸������
DWORD                 dwDesiredAccess,     // ����Ȩ��
DWORD                 dwShareMode,         // ����ģʽ
LPSECURITY_ATTRIBUTES lpSecurityAttributes,// ��ȫ����
DWORD                 dwCreationDisposition, // ��δ�������ļ�
DWORD                 dwFlagsAndAttributes,  // �ļ����Ժͱ�־
HANDLE                hTemplateFile        // ָ��һ�����ڸ����ļ����ļ����ԵĿ�ѡģ���ļ��ľ��
);
*/
	HANDLE hFile;
	hFile = CreateFile(L"systemroot.txt", //�����ļ� �ļ����ڵĻ����Ǵ��ļ�
		GENERIC_WRITE,  //д
		0,
		NULL,
		CREATE_ALWAYS,  //�����ļ�
		FILE_ATTRIBUTE_NORMAL,
		NULL);   //ͨ��Ϊ NULL

/*
  BOOL WriteFile(
  HANDLE       hFile,                  // �ļ������ I/O �豸���
  LPCVOID      lpBuffer,               // Ҫд������ݵĻ�����
  DWORD        nNumberOfBytesToWrite,  // Ҫд����ֽ���
  LPDWORD      lpNumberOfBytesWritten, // ���ڴ洢ʵ��д����ֽ���
  LPOVERLAPPED lpOverlapped            // �����첽������ OVERLAPPED �ṹ
);
*/

	DWORD dwWritten;
	if (hFile != INVALID_HANDLE_VALUE) {
		                                    //wcslen���ڼ�����ַ����� lstrlen����խ�ַ�����
		if (!WriteFile(hFile, szSystemDir, wcslen(szSystemDir) * sizeof(WCHAR), &dwWritten, NULL)) {
			return GetLastError();
		}
	}
	
	CloseHandle(hFile);

}