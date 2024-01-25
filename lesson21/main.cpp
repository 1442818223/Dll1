//��ȡ�ļ�����
#include<Windows.h>
#include <stdio.h>


DWORD ShowFileAttrInfo(DWORD dwAttribute) {

	printf("�ļ�����:\t");
	if (dwAttribute & FILE_ATTRIBUTE_ARCHIVE)
		printf("<ARCHIVE>\n");//���Դ浵�ļ�
	if (dwAttribute & FILE_ATTRIBUTE_COMPRESSED)
		printf("<ѹ��>\n");
	if (dwAttribute & FILE_ATTRIBUTE_READONLY)
		printf("<ֻ��>\n");
	if (dwAttribute & FILE_ATTRIBUTE_DIRECTORY)
		printf("<Ŀ¼>\n");
	if (dwAttribute & FILE_ATTRIBUTE_ENCRYPTED)
		printf("<����>\n");
	if (dwAttribute & FILE_ATTRIBUTE_HIDDEN)
		printf("<����>\n");
	if (dwAttribute & FILE_ATTRIBUTE_NORMAL)
		printf("<NORMAL>\n");
	if (dwAttribute & FILE_ATTRIBUTE_OFFLINE)
		printf("<OFFLINE>\n");
	if (dwAttribute & FILE_ATTRIBUTE_SYSTEM)
		printf("<ϵͳ�ļ�>\n");
	if (dwAttribute & FILE_ATTRIBUTE_TEMPORARY)
		printf("<��ʱ�ļ�>\n");

		return 0; 
}

                       //��32λ            //��32λ
DWORD ShowFileSize(DWORD dwFileSizeHigh,DWORD dwFileSizeLow) {
	ULONGLONG liFileSize;
	liFileSize = dwFileSizeHigh;
	liFileSize <<= 32;
	liFileSize += dwFileSizeLow;
	printf("�ļ���С:\t%I64u�ֽ�\n",liFileSize);
	return 0;
}

DWORD ShowFileTime(PFILETIME lptime)
{
	FILETIME ftLocal;
	SYSTEMTIME st;
	FileTimeToLocalFileTime(lptime, &ftLocal);
	FileTimeToSystemTime(&ftLocal, &st);

	printf("%4d��%#02d��%#02d�գ�%#02d:%#02d:%#O2d\n",
		st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
	return 0;
}

DWORD ShowFileAttributes(LPCTSTR szPath)
{
	WIN32_FILE_ATTRIBUTE_DATA wfad;
	printf("�ļ�:%s\n", szPath);     //GetFileExInfoStandard:������׼��Ϣ
	if (!GetFileAttributesEx(szPath, GetFileExInfoStandard, &wfad)) {
		printf("��ȡ�ļ�����ʧ��:%d\n", GetLastError());
		return 1;
	}

	printf("����ʱ��:\t");
	ShowFileTime(&(wfad.ftCreationTime));
	printf("����ʱ��:\t");
	ShowFileTime(&(wfad.ftLastAccessTime));
	printf("�޸�ʱ��:\t");
	ShowFileTime(&(wfad.ftLastWriteTime));

	ShowFileSize(wfad.nFileSizeHigh, wfad.nFileSizeLow);

	ShowFileAttrInfo(wfad.dwFileAttributes); 

}
int main() {
	ShowFileAttributes(TEXT("C:\\Users\\a0916\\Desktop\\book.txt"));
	system("pause");
	return 0;
}