#include<stdio.h>
#include<windows.h>
#include <locale.h>
#include <tchar.h>
//%c��ʽ��Ӧ���ǵ����ַ���
//%s��ʽ��Ӧ�����ַ�����

int main() {
	//���ñ��ػ�ǰ
	printf("Locale is %s\n", setlocale(LC_ALL, NULL));

	//�����ػ���Ϣ����Ϊ�û�������Ĭ�ϱ��ػ���Ϣ��
	//����ζ�ų���ʹ�ò���ϵͳ���������õı��ػ���Ϣ���Ա���ȷ���������Ժ�������صĹ��ܣ������ַ����롢����ʱ���ʽ�ȡ�
	setlocale(LC_ALL, "");

	//���ñ��ػ���
	printf("Locale is %s\n", setlocale(LC_ALL, NULL));


	char n = 'A';
	printf("%c\n", n);

	wchar_t n1 = L'��';
	wprintf(L"%c\n", n1);


	char s[] = "hello";
	wchar_t s2[] = L"�л����񹲺͹�";
	printf("%s\n", s);
	wprintf(L"%s\n", s2);

	printf("%d\n", strlen(s));
	printf("%d\n", wcslen(s2));


	char c;
	CHAR c2;

	wchar_t c3;
	WCHAR c4;
	TCHAR c5; //��T�Ķ��ǻ������Ŀѡ����ַ����Զ��仯


	PCHAR a;
	PWCHAR a2;
	PTCHAR a3;
	//PSTR �� PCHAR ��ʹ���ϻ������ǵ�Ч�ģ������ڱ�ʾָ���� null ��β�� ANSI �ַ�����ָ�롣
	PSTR b;
	LPSTR b2 = (LPSTR)"string"; //ͷ����L�ĺͲ���L�Ķ�һ��
	PWSTR b3;
	LPWSTR b4 = (LPWSTR)L"string";
	PTSTR b5;
	LPTSTR b6 = (LPTSTR)TEXT("string");//LPTSTR b6 = (LPTSTR)_T("string");_TҪ��ͷ�ļ�#include <tchar.h>

	PCSTR d; //PSTR��PCSTR��������C  C����const �����޸� �ַ���ָ��ͨ��
	PCWSTR d2;
	PCTSTR d3;

	MessageBoxW(NULL, L"����W���MessageBox", L"Test", MB_OK); //L��ʾ���ַ�
	MessageBoxA(NULL, "����A���MessageBox", "Test", MB_OK);
	MessageBoxW(NULL, TEXT("����T���MessageBox"), TEXT("Test"), MB_OK);

	system("pause");
	return 0;
}