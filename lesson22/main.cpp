//GetFileAttributes��SetFileAttributes�޸��ļ�����

#include<Windows.h>
#include<stdio.h>

DWORD SetFileHiddenAndReadOnly(LPCTSTR szFileName) {
	DWORD dwFileAttributes = GetFileAttributes(szFileName);
	//�ؼ�����
	dwFileAttributes |= FILE_ATTRIBUTE_READONLY;//ֻ��
	dwFileAttributes |= FILE_ATTRIBUTE_HIDDEN;//����
	if (SetFileAttributes(szFileName,dwFileAttributes)) {
		printf("�ļ�%s��ֻ���������������óɹ�\n", szFileName);
	}
	else {
		printf("��������ʧ��:%d\n", GetLastError());
	}

	return 0;
}


int main() {
	SetFileHiddenAndReadOnly(TEXT("C:\\Users\\a0916\\Desktop\\book.txt"));
	system("pause");
	return 0;
}