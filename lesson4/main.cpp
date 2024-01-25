#include<stdio.h>
#include<Windows.h>
#include <wchar.h>

//ͨ��WIN32_FILE_ATTRIBUTE_DATA �е� FILETIME �������ʺϱ��صı�׼ʱ��
VOID ShowFileTime(PFILETIME lptime) {
	FILETIME ftLocal;
	SYSTEMTIME st;
	FileTimeToLocalFileTime(lptime, &ftLocal);
	FileTimeToSystemTime(&ftLocal, &st);
	printf("%d��%#02d��%#02d�գ�%#02d:%#02d:%#02d\n", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
	
}

int main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR  lpCmdLine, int nCmdShow) {
	/*
typedef struct _WIN32_FILE_ATTRIBUTE_DATA {
    DWORD dwFileAttributes;// �ļ������ԣ���ʾ�ļ������ԣ���ֻ�������ص�
    FILETIME ftCreationTime;//�ļ��Ĵ���ʱ��
    FILETIME ftLastAccessTime;//�ļ����ϴη���ʱ��
    FILETIME ftLastWriteTime;// �ļ����ϴ�д��ʱ��
    DWORD nFileSizeHigh;//�ļ���С�ĸ� 32 λ����λ DWORD��
    DWORD nFileSizeLow;//����С�ĵ� 32 λ����λ DWORD��
} WIN32_FILE_ATTRIBUTE_DATA, *LPWIN32_FILE_ATTRIBUTE_DATA;
*/
	WIN32_FILE_ATTRIBUTE_DATA wfad;

/*
	BOOL GetFileAttributesEx(
  LPCWSTR                lpFileName,    // �ļ���Ŀ¼������
  GET_FILEEX_INFO_LEVELS fInfoLevelId,  // ���ص���Ϣ����
  LPVOID                 lpFileInformation // ���ڴ洢�ļ�������Ϣ�Ľṹ��ָ��
);
*/
	if (!GetFileAttributesEx(L"main.cpp", GetFileExInfoStandard, &wfad)) {
		printf("��ȡ�ļ�����ʧ��:%d\n", GetLastError());
		return -1;
	}


	printf("����ʱ��:\n");
	ShowFileTime(&wfad.ftCreationTime);

	printf("������ʱ��:\n");
	ShowFileTime(&wfad.ftLastAccessTime);

	printf("���д��ʱ��:\n");
	ShowFileTime(&wfad.ftLastWriteTime);

}


