#include<stdio.h>
#include<windows.h>
#include <locale.h>
#include <tchar.h>
//%c格式对应的是单个字符。
//%s格式对应的是字符串。

int main() {
	//设置本地化前
	printf("Locale is %s\n", setlocale(LC_ALL, NULL));

	//将本地化信息设置为用户环境的默认本地化信息。
	//这意味着程序将使用操作系统环境中配置的本地化信息，以便正确处理与语言和区域相关的功能，例如字符编码、日期时间格式等。
	setlocale(LC_ALL, "");

	//设置本地化后
	printf("Locale is %s\n", setlocale(LC_ALL, NULL));


	char n = 'A';
	printf("%c\n", n);

	wchar_t n1 = L'中';
	wprintf(L"%c\n", n1);


	char s[] = "hello";
	wchar_t s2[] = L"中华人民共和国";
	printf("%s\n", s);
	wprintf(L"%s\n", s2);

	printf("%d\n", strlen(s));
	printf("%d\n", wcslen(s2));


	char c;
	CHAR c2;

	wchar_t c3;
	WCHAR c4;
	TCHAR c5; //带T的都是会根据项目选择的字符集自动变化


	PCHAR a;
	PWCHAR a2;
	PTCHAR a3;
	//PSTR 和 PCHAR 在使用上基本上是等效的，都用于表示指向以 null 结尾的 ANSI 字符串的指针。
	PSTR b;
	LPSTR b2 = (LPSTR)"string"; //头部带L的和不带L的都一样
	PWSTR b3;
	LPWSTR b4 = (LPWSTR)L"string";
	PTSTR b5;
	LPTSTR b6 = (LPTSTR)TEXT("string");//LPTSTR b6 = (LPTSTR)_T("string");_T要加头文件#include <tchar.h>

	PCSTR d; //PSTR和PCSTR的区别是C  C代表const 不可修改 字符串指针通用
	PCWSTR d2;
	PCTSTR d3;

	MessageBoxW(NULL, L"这是W版的MessageBox", L"Test", MB_OK); //L表示宽字符
	MessageBoxA(NULL, "这是A版的MessageBox", "Test", MB_OK);
	MessageBoxW(NULL, TEXT("这是T版的MessageBox"), TEXT("Test"), MB_OK);

	system("pause");
	return 0;
}