#include<stdio.h>
#include<Windows.h>
#include <wchar.h>


int main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR  lpCmdLine, int nCmdShow) {

	//������ôд��c++���治��
   //    LPSTR  SW = "dwadwa";  //typedef char* LPSTR;

	LPSTR szString = "Windows data type ,string";  //CHAR   խ�ַ�

	printf("%s", szString);


	// ͨ��խ�ַ�������ַ��ַ����ĳ���**********
	//size_t mbstowcs(wchar_t *dest, const char *src, size_t n);
	  //dest��ָ�����ڴ洢���ַ��Ļ�������ָ�롣����Ϊ NULL����ʱ������������ת������ַ�������������ʵ�ʵ�ת����
	size_t wideStrLen = mbstowcs(NULL, szString, 0);//mbstowcs�������ڽ����ֽ��ַ�ת��Ϊ���ַ�
	if (wideStrLen == (size_t)-1) {   //(size_t)-1 ͨ������������ָʾ������ʾ����ִ��ʧ�ܡ�           
		perror("mbstowcs failed");
		return EXIT_FAILURE;
	}

	// ���仺����
	wchar_t* wszString = (wchar_t*)malloc((wideStrLen + 1) * sizeof(wchar_t));
	if (wszString == NULL) {
		perror("Memory allocation failed");
		return EXIT_FAILURE;
	}

	// ����ת��
//errno_t mbstowcs_s(size_t * pReturnValue, wchar_t* wcstr, size_t sizeInWords, const char* mbstr, size_t count);
	//pReturnValue�����ڴ洢�ɹ�ת�����ַ����������� null ��ֹ������ָ��
	//wcstr��ָ�����ڴ洢���ַ��Ļ�������ָ�롣
	//sizeInWords���������Ĵ�С���Կ��ַ�Ϊ��λ������ wcstr ��������Ԫ�ظ�����
	//mbstr��ָ��Ҫת���Ķ��ֽ��ַ�����ָ�롣
	//count��Ҫת���Ķ��ֽ��ַ��������� null ��ֹ�����ڡ�
	mbstowcs_s(NULL, wszString, wideStrLen + 1, szString, wideStrLen);//��������ɹ��������㡣

	//// ������ַ����ַ���
	//wprintf(L"Wide String: %ls\n", wszString);

	//// �ͷ��ڴ�
	//free(wszString);


	MessageBox(NULL, wszString, TEXT("����"), MB_OK); //LPCWSTR= WCHAR

	wchar_t lpString[120]; //char

	/*void CopyMemory(
		_Out_       PVOID Destination,    PVOID=void*
		_In_  const VOID * Source,
		_In_        SIZE_T Length
	);*/
	//CopyMemory(lpString, wszString, lstrlen(wszString) + 1);
	//CopyMemory ��һ��ִ��ԭʼ�ڴ渴�Ƶĺ�����������븴���ַ��������ʹ�� strcpy��խ�ַ������� wcscpy�����ַ�������
	wcscpy_s(lpString, sizeof(lpString) / sizeof(wchar_t), wszString);

	MessageBox(NULL, lpString, TEXT("����"), MB_OK);

	DWORD dwMax = 0xFFFFFFFFFF;  //unsigned long
	INT iMax; //int

	HANDLE h; //���
	HICON hicon;//ͼ����
	HINSTANCE hinstance;//ʵ�����
	HKEY hYey;//ע�����
	HMODULE hModule;//ģ����
	HWND hWnd;//���ھ��

	/*HANDLE CreateFile(
  LPCWSTR               lpFileName,          // �ļ����豸������
  DWORD                 dwDesiredAccess,     // ����Ȩ��
  DWORD                 dwShareMode,         // ����ģʽ
  LPSECURITY_ATTRIBUTES lpSecurityAttributes,// ��ȫ����
  DWORD                 dwCreationDisposition, // ��δ�������ļ�
  DWORD                 dwFlagsAndAttributes,  // �ļ����Ժͱ�־
  HANDLE                hTemplateFile        // ָ��һ�����ڸ����ļ����ļ����ԵĿ�ѡģ���ļ��ľ��
);
*/
	HANDLE hFileRead;
	hFileRead = CreateFile(L"�����Գ���5��GTA5��.txt", //�����ļ� �ļ����ڵĻ����Ǵ��ļ�
		GENERIC_READ,  //��
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,  //���ļ�
		FILE_ATTRIBUTE_NORMAL,
		NULL);   //ͨ��Ϊ NULL
	if (hFileRead == INVALID_HANDLE_VALUE) {
		printf("Cannot open file. Error: %x\n", GetLastError());
		return -1;
	}
	DWORD nIn;
	CHAR buffer[256];
	DWORD BUF_SIZE = 256;
	/*BOOL ReadFile(
  HANDLE       hFile,          // �ļ������ I/O �豸���
  LPVOID       lpBuffer,       // ���ڴ洢��ȡ���ݵĻ�����
  DWORD        nNumberOfBytesToRead, // Ҫ��ȡ���ֽ���
  LPDWORD      lpNumberOfBytesRead,   // ���ڴ洢ʵ�ʶ�ȡ���ֽ���
  LPOVERLAPPED lpOverlapped    // �����첽������ OVERLAPPED �ṹ
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
