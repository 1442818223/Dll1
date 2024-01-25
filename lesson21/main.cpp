//获取文件属性
#include<Windows.h>
#include <stdio.h>


DWORD ShowFileAttrInfo(DWORD dwAttribute) {

	printf("文件属性:\t");
	if (dwAttribute & FILE_ATTRIBUTE_ARCHIVE)
		printf("<ARCHIVE>\n");//可以存档文件
	if (dwAttribute & FILE_ATTRIBUTE_COMPRESSED)
		printf("<压缩>\n");
	if (dwAttribute & FILE_ATTRIBUTE_READONLY)
		printf("<只读>\n");
	if (dwAttribute & FILE_ATTRIBUTE_DIRECTORY)
		printf("<目录>\n");
	if (dwAttribute & FILE_ATTRIBUTE_ENCRYPTED)
		printf("<加密>\n");
	if (dwAttribute & FILE_ATTRIBUTE_HIDDEN)
		printf("<隐藏>\n");
	if (dwAttribute & FILE_ATTRIBUTE_NORMAL)
		printf("<NORMAL>\n");
	if (dwAttribute & FILE_ATTRIBUTE_OFFLINE)
		printf("<OFFLINE>\n");
	if (dwAttribute & FILE_ATTRIBUTE_SYSTEM)
		printf("<系统文件>\n");
	if (dwAttribute & FILE_ATTRIBUTE_TEMPORARY)
		printf("<临时文件>\n");

		return 0; 
}

                       //高32位            //低32位
DWORD ShowFileSize(DWORD dwFileSizeHigh,DWORD dwFileSizeLow) {
	ULONGLONG liFileSize;
	liFileSize = dwFileSizeHigh;
	liFileSize <<= 32;
	liFileSize += dwFileSizeLow;
	printf("文件大小:\t%I64u字节\n",liFileSize);
	return 0;
}

DWORD ShowFileTime(PFILETIME lptime)
{
	FILETIME ftLocal;
	SYSTEMTIME st;
	FileTimeToLocalFileTime(lptime, &ftLocal);
	FileTimeToSystemTime(&ftLocal, &st);

	printf("%4d年%#02d月%#02d日，%#02d:%#02d:%#O2d\n",
		st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
	return 0;
}

DWORD ShowFileAttributes(LPCTSTR szPath)
{
	WIN32_FILE_ATTRIBUTE_DATA wfad;
	printf("文件:%s\n", szPath);     //GetFileExInfoStandard:检索标准信息
	if (!GetFileAttributesEx(szPath, GetFileExInfoStandard, &wfad)) {
		printf("获取文件属性失败:%d\n", GetLastError());
		return 1;
	}

	printf("创建时间:\t");
	ShowFileTime(&(wfad.ftCreationTime));
	printf("访问时间:\t");
	ShowFileTime(&(wfad.ftLastAccessTime));
	printf("修改时间:\t");
	ShowFileTime(&(wfad.ftLastWriteTime));

	ShowFileSize(wfad.nFileSizeHigh, wfad.nFileSizeLow);

	ShowFileAttrInfo(wfad.dwFileAttributes); 

}
int main() {
	ShowFileAttributes(TEXT("C:\\Users\\a0916\\Desktop\\book.txt"));
	system("pause");
	return 0;
}