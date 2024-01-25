#include<stdio.h>
#include<windows.h>



int main() {

	DWORD g_unhookfun = NULL;
	char g_oldcode[5] = { 0 };

	HMODULE hModule = LoadLibraryA("user32.dll");  // 加载user32.dll
	if (hModule == NULL) {
		return FALSE;
	}

	g_unhookfun = (DWORD)GetProcAddress(hModule, "MessageBoxW");  // 获取MessageBoxW函数的地址
	if (g_unhookfun == NULL) {
		FreeLibrary(hModule);
		return FALSE;
	}

	memcpy(g_oldcode, (char*)g_unhookfun, 5);



	int arr[10] = { 1,2,3,4,5,6,7,8,9,10 };
	int b = 2[arr];
	printf("%d",b);


	const wchar_t* pszText = L"警方对抗赛录放机看大理寺风景点可罗斯福即可的松连脚裤";
	wprintf(L"%s\n", pszText);
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);//相当于Linux的文件描述符0,1,2  这里对应1,是拿到了标准输出句柄
	WriteConsole(hOut, pszText, wcslen(pszText), NULL, NULL); //winAPI打印函数


	system("pause");
}