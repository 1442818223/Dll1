#include <Windows.h>
#include"resource.h"

//hDlg表示当前对话框的句柄 uMsg表示当前消息的类型如按钮点击、鼠标移动等
INT_PTR CALLBACK MainDlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	BOOL bRet = TRUE;

	static HWND hwndEdit1,hwndEdit2;
	static TCHAR pszBuffer[1024];

/*
WM_COMMAND 是 Windows 操作系统中用于处理菜单项、工具栏按钮等用户界面元素的消息
wParam: 低位字节包含了来自控件的通知代码，高位字节包含了控件标识符。
lParam: 包含了指向控件的句柄的指针，如果消息是由加速键生成的，则为 NULL。
*/
	switch (uMsg) {

	case WM_COMMAND:
		hwndEdit1 = GetDlgItem(hDlg, IDC_EDIT1);
		hwndEdit2 = GetDlgItem(hDlg, IDC_EDIT2);

		switch (LOWORD(wParam)) {//低位字节包含了来自控件的代码

		case IDC_EDIT1:
			switch (HIWORD(wParam)) {
			case EN_MAXTEXT:
				break;
			case EN_ERRSPACE:
				break;
			case EN_UPDATE: //刷新编辑框1
				GetWindowText(hwndEdit1, pszBuffer, 1024); //和到编辑框1的文本
				SetWindowText(hwndEdit2, pszBuffer); //将文本放置到编辑框2
				break;
			}
			break;

		case IDC_BUTTON2:
			switch (HIWORD(wParam)) {
				case BN_CLICKED :
					SendMessage(hwndEdit1, WM_COPY, 0, 0); //把编辑框1选中的复制到粘贴板
					break;
			}
			break;

		case IDC_BUTTON3:
			SendMessage(hwndEdit2, WM_PASTE, 0, 0);//把粘贴板上的内容复制到编辑框2
			break;

		case IDC_BUTTON4:
			GetWindowText(hwndEdit1, pszBuffer, 1024);   //从编辑框1中得到字符放进pszBuffer数组
			MessageBox(hDlg, pszBuffer, TEXT("TEST"), MB_OK);
			break;

		case IDC_BUTTON5:
			SetWindowText(hwndEdit2,TEXT("this is set window text"));//将文本写入编辑框2
			break;

		case IDC_BUTTON1:
			switch ((HIWORD(wParam))) {//高位字节包含了控件消息标识符 
				                     //本来需要对控件的消息种类做判断,但一般都是对控件点击,所以可以省略对高位的选择
			case BN_CLICKED: //点击事件
				SendMessage(hwndEdit1,WM_CLEAR, 0, 0);//将选中的文本清除
				break;
			case BN_SETFOCUS:
				break;
			}
			break;
			 
		default:
			//对于其他控件的通知，或者未处理的情况，调用默认的消息处理函数
			return DefWindowProc(hDlg, uMsg, wParam, lParam);
			break;
		}
		break;

	case WM_CLOSE:
		EndDialog(hDlg, 0);
		break;

	default:
		bRet = FALSE;//系统回调函数需要处理剩下没处理的消息
		break;
	}

	return bRet; //默认返回真,不处理,因为已经在默认中处理了

}

int APIENTRY WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInStance,
	LPSTR lpCmdLine,
	int nCmdShow)//指定应用程序窗口的显示状态
{
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_MAIN), NULL, MainDlgProc);

	return 0;
}