#include <Windows.h>
#include <stdio.h>
#include <locale.h>
int main()
{


	DWORD dwNum;
	setlocale(LC_ALL, "");
	char sText[] = "���ֽ��ַ���ת���ַ���";

/*
  int MultiByteToWideChar(
  UINT     CodePage,          // ָ���ַ����뼯�ı�ʶ�������� CP_UTF8��CP_ACP ��  (Դ����)
  DWORD    dwFlags,           // ָ��ת����Ϊ�ı�־
  LPCSTR   lpMultiByteStr,    // ָ��Ҫת���Ķ��ֽ��ַ�����ָ��
  int      cbMultiByte,       // ָ��Ҫת���Ķ��ֽ��ַ������ֽ�����-1 ��ʾ�ַ����� null ��ֹ
  LPWSTR   lpWideCharStr,     // ָ����տ��ַ��ַ����Ļ�������ָ��
  int      cchWideChar        // ָ���������п��ַ��ַ������ַ��������� null ��ֹ��
);
*/

	//������ַ��ַ�������Ļ�������С��������β�� null �ַ���
	dwNum = MultiByteToWideChar(CP_ACP,  //CP_ACPԴ����Ϊascall 
		0, 
		sText,  //Դָ��
		-1,     //Դ���ֽ��ַ������ֽ�����-1 ��ʾ�ַ����� null ��ֹ 
		NULL,   //Ŀ�ĵ�ָ��    
		0);     //���ַ��ַ������ַ��������� null ��ֹ��
	                        
 	wchar_t* pwText;
	//�����ڴ����ڴ洢���ַ��ַ���
	pwText = new wchar_t[dwNum];
	if (!pwText)
	{
		delete[] pwText;
		return 0;
	}
	//�����ַ��ַ���ת��Ϊ���ֽ��ַ���
	MultiByteToWideChar(CP_ACP, 0, sText, -1, pwText, dwNum);
	wprintf(L"M->W: %s\n", pwText);
	MessageBoxW(NULL, pwText, L"Test", MB_OK);
	delete[] pwText;
	
	wchar_t wTest[] = L"���ַ���ת���ֽ��ַ���";                  //�������������ò���,���ù�
	dwNum = WideCharToMultiByte(CP_OEMCP, 0, wTest, -1, NULL, 0,         NULL, NULL);
                               //ԴΪCP_OEMCP(���ַ���)	
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