#include<stdio.h>
#include<windows.h>



int main() {

	DWORD g_unhookfun = NULL;
	char g_oldcode[5] = { 0 };

	HMODULE hModule = LoadLibraryA("user32.dll");  // ����user32.dll
	if (hModule == NULL) {
		return FALSE;
	}

	g_unhookfun = (DWORD)GetProcAddress(hModule, "MessageBoxW");  // ��ȡMessageBoxW�����ĵ�ַ
	if (g_unhookfun == NULL) {
		FreeLibrary(hModule);
		return FALSE;
	}

	memcpy(g_oldcode, (char*)g_unhookfun, 5);



	int arr[10] = { 1,2,3,4,5,6,7,8,9,10 };
	int b = 2[arr];
	printf("%d",b);


	const wchar_t* pszText = L"�����Կ���¼�Ż��������·羰�����˹�����ɵ������ſ�";
	wprintf(L"%s\n", pszText);
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);//�൱��Linux���ļ�������0,1,2  �����Ӧ1,���õ��˱�׼������
	WriteConsole(hOut, pszText, wcslen(pszText), NULL, NULL); //winAPI��ӡ����


	system("pause");
}