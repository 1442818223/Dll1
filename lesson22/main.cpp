//GetFileAttributes和SetFileAttributes修改文件属性

#include<Windows.h>
#include<stdio.h>

DWORD SetFileHiddenAndReadOnly(LPCTSTR szFileName) {
	DWORD dwFileAttributes = GetFileAttributes(szFileName);
	//关键步骤
	dwFileAttributes |= FILE_ATTRIBUTE_READONLY;//只读
	dwFileAttributes |= FILE_ATTRIBUTE_HIDDEN;//隐藏
	if (SetFileAttributes(szFileName,dwFileAttributes)) {
		printf("文件%s的只读和隐藏属性设置成功\n", szFileName);
	}
	else {
		printf("属性设置失败:%d\n", GetLastError());
	}

	return 0;
}


int main() {
	SetFileHiddenAndReadOnly(TEXT("C:\\Users\\a0916\\Desktop\\book.txt"));
	system("pause");
	return 0;
}