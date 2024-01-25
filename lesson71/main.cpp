#include<Windows.h>
#include "resource.h"
#include <strsafe.h>
#include<Psapi.h>
#pragma comment (lib,"psapi.lib")

#define IDT_UPDATE 1 //���嶨ʱ���ı�ʶ��

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
		SendMessage(hDlg, WM_TIMER, IDT_UPDATE, 0); //�ֶ����� WM_TIMER ��Ϣ��������WM_TIMER�¼�,ͷһ�β��õ�������ʾ
		break;

	case WM_TIMER:
		GetProcessMemoryInfo(GetCurrentProcess(), (PPROCESS_MEMORY_COUNTERS)&pmc, sizeof(pmc));//

		StringCchPrintf(szData, _countof(szData), TEXT("%I64d K\n%I64d K"),
		(__int64) pmc.WorkingSetSize / 1024, //���̵ĵ�ǰ��������С������ǰ���������ڴ���ʹ�õ��ڴ�ҳ�Ĵ�С��
 			(__int64)pmc.PrivateUsage / 1024);//���̵�ר�ù�������С�������̶�ռ�Ĺ�������С��ֻ���ڸý��̵Ĳ��֡�
		                                           //PrivateUsage��WorkingSetSize���Ӽ�
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
