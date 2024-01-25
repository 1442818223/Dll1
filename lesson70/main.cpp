#include<Windows.h>
#include "resource.h"
#include <strsafe.h>
#include <tchar.h>


PTSTR BigNumToString(LONG lNum, LPTSTR szBuf, DWORD chBufSize) {
	TCHAR szNum[100];

	//c库sprintf  =  win库StringCchPrintf
	StringCchPrintf(szNum, _countof(szNum), TEXT("%d"), lNum);
	                      //_countof 是一个宏，通常用于获取数组的元素个数
/*
*  Windows API 函数，用于将数字格式化为字符串，以便于显示。
int GetNumberFormat(
  LCID             Locale,//一个标识区域设置的标识符（LCID），用于确定格式规则。
  DWORD            dwFlags,// 格式化选项的标志，可以指定各种选项，例如使用货币符号。
  LPCWSTR          lpValue,//要格式化的数字的字符串表示。通常，这是一个以 null 结尾的字符串。
  const NUMBERFMT *lpFormat,//一个指向 NUMBERFMT 结构的指针，该结构定义了数字格式的各种属性，例如小数点符号和千位分隔符。
  LPWSTR           lpNumberStr,//用于接收格式化后的数字字符串的缓冲区。
  int              cchNumber//缓冲区的大小，以字符数（包括 null 终止符）表示。
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
	case WM_INITDIALOG://初始化

		//1,内存部分
		SYSTEM_INFO sinf;//是一个结构体，用于获取系统的信息。
		GetSystemInfo(&sinf);

		TCHAR szBuf[50];                                   //系统的页面大小，通常用于虚拟内存管理。 至少要一页4k
		SetDlgItemText(hDlg, IDC_STATIC14, BigNumToString(sinf.dwPageSize, szBuf, _countof(szBuf)) );
		                                                   //用户模式应用程序地址空间的最小地址。
		StringCchPrintf(szBuf, _countof(szBuf), TEXT("%p"),sinf.lpMinimumApplicationAddress);
		SetDlgItemText(hDlg, IDC_STATIC16, szBuf);
		                                                    //用户模式应用程序地址空间的最大地址。
		StringCchPrintf(szBuf, _countof(szBuf), TEXT("%p"), sinf.lpMaximumApplicationAddress);
		SetDlgItemText(hDlg, IDC_STATIC18, szBuf);
		                                                  //系统的内存分配粒度。64K的整数倍的位置开始要内存     
		SetDlgItemText(hDlg, IDC_STATIC12, BigNumToString(sinf.dwAllocationGranularity, szBuf, _countof(szBuf)));

		//CPU部分
		                                                 //cpu个数
		SetDlgItemText(hDlg, IDC_STATIC8, BigNumToString(sinf.dwNumberOfProcessors, szBuf, _countof(szBuf)));
		                                                                    //cpu掩码(可以确认cpu是否忙)
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
