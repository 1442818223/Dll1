#include<Windows.h>
#include "resource.h"
#include <strsafe.h>
#include<Psapi.h>
#pragma comment (lib,"psapi.lib")

#define IDT_UPDATE 1 //定义定时器的标识符

INT_PTR CALLBACK MainDlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	BOOL bRet = TRUE;

	TCHAR szData[512] = { 0 };
	MEMORYSTATUS ms = { sizeof(ms) };
	PROCESS_MEMORY_COUNTERS_EX pmc = { sizeof(pmc) };

	switch (uMsg)
	{
	case WM_INITDIALOG:
		SetTimer(hDlg, IDT_UPDATE, 1000, NULL);
		SendMessage(hDlg, WM_TIMER, IDT_UPDATE, 0); //手动发送 WM_TIMER 消息，触发了WM_TIMER事件,头一次不用等立即显示
		break;

	case WM_TIMER:
		GetProcessMemoryInfo(GetCurrentProcess(), (PPROCESS_MEMORY_COUNTERS)&pmc, sizeof(pmc));//

		StringCchPrintf(szData, _countof(szData), TEXT("%I64d K\n%I64d K"),
		(__int64) pmc.WorkingSetSize / 1024, //进程的当前工作集大小。即当前正在物理内存中使用的内存页的大小。
 			(__int64)pmc.PrivateUsage / 1024);//进程的专用工作集大小，即进程独占的工作集大小。只属于该进程的部分。
		                                           //PrivateUsage是WorkingSetSize的子集
		SetDlgItemText(hDlg, IDC_STATIC2, szData);
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
