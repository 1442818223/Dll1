#include<Windows.h>
#include "resource.h"
#include <strsafe.h>
#include <tchar.h>


PTSTR BigNumToString(LONG lNum, LPTSTR szBuf, DWORD chBufSize) {
	TCHAR szNum[100];

	//c��sprintf  =  win��StringCchPrintf
	StringCchPrintf(szNum, _countof(szNum), TEXT("%d"), lNum);
	                      //_countof ��һ���꣬ͨ�����ڻ�ȡ�����Ԫ�ظ���
/*
*  Windows API ���������ڽ����ָ�ʽ��Ϊ�ַ������Ա�����ʾ��
int GetNumberFormat(
  LCID             Locale,//һ����ʶ�������õı�ʶ����LCID��������ȷ����ʽ����
  DWORD            dwFlags,// ��ʽ��ѡ��ı�־������ָ������ѡ�����ʹ�û��ҷ��š�
  LPCWSTR          lpValue,//Ҫ��ʽ�������ֵ��ַ�����ʾ��ͨ��������һ���� null ��β���ַ�����
  const NUMBERFMT *lpFormat,//һ��ָ�� NUMBERFMT �ṹ��ָ�룬�ýṹ���������ָ�ʽ�ĸ������ԣ�����С������ź�ǧλ�ָ�����
  LPWSTR           lpNumberStr,//���ڽ��ո�ʽ����������ַ����Ļ�������
  int              cchNumber//�������Ĵ�С�����ַ��������� null ��ֹ������ʾ��
);
*/
	NUMBERFMT nf;
	nf.NumDigits = 0;
	nf.LeadingZero = FALSE;
	nf.Grouping = 3;
	nf.lpDecimalSep = TEXT(LPSTR)(".");
	nf.lpThousandSep = TEXT(LPSTR)(",");
	nf.NegativeOrder = 0;
	GetNumberFormat(LOCALE_USER_DEFAULT, 0, szNum, &nf, szBuf, chBufSize);
	return szBuf;
}


void ShowCPUInfo(HWND hWnd,
	WORD wProcessorArchitecture,
	WORD wProcessorLevel,
	WORD wProcessorRevision)
{
	TCHAR szCPUArch[64] = TEXT("unknown");
	TCHAR szCPULevel[64] = TEXT("unknown");
	TCHAR szCPURev[64] = TEXT("unknown");

	switch (wProcessorArchitecture) {
	case PROCESSOR_ARCHITECTURE_INTEL:
		_tcscpy_s(szCPUArch, _countof(szCPUArch), TEXT("Intel"));
		break;
	case PROCESSOR_ARCHITECTURE_IA64:
		_tcscpy_s(szCPUArch, _countof(szCPUArch), TEXT("IA-64"));
		break;
	case PROCESSOR_ARCHITECTURE_AMD64:
		_tcscpy_s(szCPUArch, _countof(szCPUArch), TEXT("AMD64"));
		break;
	case PROCESSOR_ARCHITECTURE_UNKNOWN:
	default:
		_tcscpy_s(szCPUArch, _countof(szCPUArch), TEXT("Unknown"));
		break;
	}

	SetDlgItemText(hWnd, IDC_STATIC2, szCPUArch);
	SetDlgItemText(hWnd, IDC_STATIC4, szCPULevel);
	SetDlgItemText(hWnd, IDC_STATIC6, szCPURev);

}

INT_PTR CALLBACK MainDlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	BOOL bRet = TRUE;
	switch (uMsg)
	{
	case WM_INITDIALOG://��ʼ��

		//1,�ڴ沿��
		SYSTEM_INFO sinf;//��һ���ṹ�壬���ڻ�ȡϵͳ����Ϣ��
		GetSystemInfo(&sinf);

		TCHAR szBuf[50];                                   //ϵͳ��ҳ���С��ͨ�����������ڴ���� ����Ҫһҳ4k
		SetDlgItemText(hDlg, IDC_STATIC14, BigNumToString(sinf.dwPageSize, szBuf, _countof(szBuf)) );
		                                                   //�û�ģʽӦ�ó����ַ�ռ����С��ַ��
		StringCchPrintf(szBuf, _countof(szBuf), TEXT("%p"),sinf.lpMinimumApplicationAddress);
		SetDlgItemText(hDlg, IDC_STATIC16, szBuf);
		                                                    //�û�ģʽӦ�ó����ַ�ռ������ַ��
		StringCchPrintf(szBuf, _countof(szBuf), TEXT("%p"), sinf.lpMaximumApplicationAddress);
		SetDlgItemText(hDlg, IDC_STATIC18, szBuf);
		                                                  //ϵͳ���ڴ�������ȡ�64K����������λ�ÿ�ʼҪ�ڴ�     
		SetDlgItemText(hDlg, IDC_STATIC12, BigNumToString(sinf.dwAllocationGranularity, szBuf, _countof(szBuf)));

		//CPU����
		                                                 //cpu����
		SetDlgItemText(hDlg, IDC_STATIC8, BigNumToString(sinf.dwNumberOfProcessors, szBuf, _countof(szBuf)));
		                                                                    //cpu����(����ȷ��cpu�Ƿ�æ)
		StringCchPrintf(szBuf, _countof(szBuf), TEXT("0x%016I64X"), (__int64)sinf.dwActiveProcessorMask);
		SetDlgItemText(hDlg, IDC_STATIC10, szBuf);

		ShowCPUInfo(hDlg,sinf.wProcessorArchitecture, sinf.wProcessorLevel,sinf.wProcessorRevision);

		
		break;



	case WM_CLOSE:
		EndDialog(hDlg, 0);
		break;

	default:
		bRet = FALSE;
		break;
	}

	return bRet;
}

int APIENTRY WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR lpCmdLine,
	int nCmdShow)
{
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_MAIN), NULL, MainDlgProc);
	return 0;
}
