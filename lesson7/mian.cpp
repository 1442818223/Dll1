//使用 资源文件 和 封装了画图过程的DialogBox函数 创建对话框
#include<Windows.h>
#include"resource.h"

INT_PTR CALLBACK MainDlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	BOOL bRet = TRUE;
	switch (uMsg)
	{
		
	//部件消息派发	 
	case WM_COMMAND:
		switch (LOWORD(wParam)) { // 钮按消息的处理(检查消息的低位字就是按钮ID)
		case IDC_BUTTON1:
			MessageBox(hDlg, L"Hello Button 1", L"Demo", MB_OK); break;
		case IDC_BUTTON2:
			MessageBox(hDlg, L"Hello Button 2", L"Demo", MB_OK); break;
		default:
			bRet = FALSE;
			break;
		}

	case WM_LBUTTONDOWN:
		MessageBox(hDlg, L"Hello窗口!", L"Demo", MB_OK);
		break;
	case WM_CLOSE:
		EndDialog(hDlg, 0);
		break;
	default:
		bRet = FALSE;   //其他的消息转去windows处理
		break;    
	}

	return bRet;      //其他的消息转去windows处理
}


int APIENTRY WinMain(HINSTANCE hinstance,//是当前程序实例的句柄
	HINSTANCE hPrevInstance,//始终为 NULL,不再支持多个实例的应用程序
	LPSTR lpCmdLine,// 是命令行参数，允许你从命令行获取程序运行时传递的额外信息
	int nCmdshow)//它通常用于控制窗口最初是正常、最小化还是最大化显示。
{

	DialogBox(hinstance, MAKEINTRESOURCE(IDD_MIAN), NULL, MainDlgProc); //只用处理窗口过程,不用在去画窗口了
	                     //使用宏标识资源类窗口


}