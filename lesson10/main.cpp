#include <Windows.h>
#include <stdio.h>
#include <locale.h>
int main()
{


	DWORD dwNum;
	setlocale(LC_ALL, "");
	char sText[] = "多字节字符串转宽字符串";

/*
  int MultiByteToWideChar(
  UINT     CodePage,          // 指定字符编码集的标识符，例如 CP_UTF8、CP_ACP 等  (源类型)
  DWORD    dwFlags,           // 指定转换行为的标志
  LPCSTR   lpMultiByteStr,    // 指向要转换的多字节字符串的指针
  int      cbMultiByte,       // 指定要转换的多字节字符串的字节数，-1 表示字符串以 null 终止
  LPWSTR   lpWideCharStr,     // 指向接收宽字符字符串的缓冲区的指针
  int      cchWideChar        // 指定缓冲区中宽字符字符串的字符数，包括 null 终止符
);
*/

	//计算宽字符字符串所需的缓冲区大小（包括结尾的 null 字符）
	dwNum = MultiByteToWideChar(CP_ACP,  //CP_ACP源类型为ascall 
		0, 
		sText,  //源指针
		-1,     //源多字节字符串的字节数，-1 表示字符串以 null 终止 
		NULL,   //目的地指针    
		0);     //宽字符字符串的字符数，包括 null 终止符
	                        
 	wchar_t* pwText;
	//分配内存用于存储宽字符字符串
	pwText = new wchar_t[dwNum];
	if (!pwText)
	{
		delete[] pwText;
		return 0;
	}
	//将宽字符字符串转换为多字节字符串
	MultiByteToWideChar(CP_ACP, 0, sText, -1, pwText, dwNum);
	wprintf(L"M->W: %s\n", pwText);
	MessageBoxW(NULL, pwText, L"Test", MB_OK);
	delete[] pwText;
	
	wchar_t wTest[] = L"宽字符串转多字节字符串";                  //后面两个参数用不到,不用管
	dwNum = WideCharToMultiByte(CP_OEMCP, 0, wTest, -1, NULL, 0,         NULL, NULL);
                               //源为CP_OEMCP(宽字符集)	
	char* psText;
	psText = new char[dwNum]; 
	if (!psText)
	{
		delete[] psText;
		return 2;
	}
	WideCharToMultiByte(CP_OEMCP, 0, wTest, -1, psText, dwNum,    NULL, NULL);

	printf("%s\n", psText);
	MessageBoxA(NULL, psText, "Test", MB_OK); 
	delete[] psText;


	system("pause");
	return 0;
}