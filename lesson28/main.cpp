#include <Windows.h>
#include"resource.h"


//hDlg表示当前对话框的句柄 uMsg表示当前消息的类型如按钮点击、鼠标移动等
INT_PTR CALLBACK MainDlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	BOOL bRet = TRUE;

	static HWND hButton;
	static HWND hCheckBox;
	static HWND hRadioButton;

	static int iCheck;
	static TCHAR pszBuffer[128];

	/*
	WM_COMMAND 是 Windows 操作系统中用于处理菜单项、工具栏按钮等用户界面元素的消息
	wParam: 低位字节包含了来自控件的通知代码，高位字节包含了控件标识符。
	lParam: 包含了指向控件的句柄的指针，如果消息是由加速键生成的，则为 NULL。
	*/

	switch (uMsg) {


	case WM_COMMAND://用于处理菜单项、工具栏按钮等用户界面元素的消息
		hButton = GetDlgItem(hDlg, IDC_BUTTON1);//获取对话框中的控件句柄
		hCheckBox = GetDlgItem(hDlg, IDC_CHECK1);
		hRadioButton = GetDlgItem(hDlg, IDC_RADIO1);
		switch (LOWORD(wParam))//低位字节包含了来自控件的通知代码
		{
		case IDC_BUTTON1:
			MessageBox(hDlg, TEXT("Hello Button1"), TEXT("Test"), MB_OK);
			break;
		case IDC_BUTTON2:
			/*
			LRESULT SendMessage(
			  HWND   hWnd,//目标窗口或控件的句柄
			  UINT   Msg,//要发送的消息类型。
			  WPARAM wParam,
			  LPARAM lParam  //wParam 和 lParam：这两个参数的具体含义取决于所发送的消息类型 Msg。
			);
			*/
			//BM_SETCHECK设置复选框状态的消息
			//1 是 wParam，表示将单选按钮设置为选中状态。
			//0 是 lParam，这里没有特殊含义，因为 BM_SETCHECK 不需要用到 lParam。
			SendMessage(hCheckBox, BM_SETCHECK, 1, 0);
			SendMessage(hRadioButton, BM_SETCHECK, 1, 0);
			break;

		case IDC_BUTTON3:                     //0为未选中状态
			SendMessage(hCheckBox, BM_SETCHECK, 0, 0);
			SendMessage(hRadioButton, BM_SETCHECK, 0, 0);
			break;

		case IDC_BUTTON4:                     //BM_GETCHECK为得到状态
			iCheck = (int)SendMessage(hCheckBox,BM_GETCHECK, 0, 0);
			if (iCheck)
				MessageBox(hDlg, TEXT("CheckBox选中了"), TEXT("TEST"), MB_OK);
			else
				MessageBox(hDlg, TEXT("CheckBox没选中"), TEXT("TEST"), MB_OK);

         case IDC_BUTTON5:
			 SetWindowText(hButton, TEXT("Hello")); //设置工具栏按钮上的文字
			 break;

		 case IDC_BUTTON6:
			 GetWindowText(hButton,pszBuffer, 128); //得到工具栏按钮上的文字
			 MessageBox(hDlg, pszBuffer, TEXT("TEST"), MB_OK);
			 break;

		 case IDC_BUTTON7:
			 if (IsWindowVisible(hButton))  
				 ShowWindow(hDlg, SW_HIDE); //ShowWindow设置显示或者隐藏窗口,或控件
			 else
				 ShowWindow(hDlg, SW_SHOW);
			 break;

		 case IDC_BUTTON8:
			 //if (IsWindowEnabled(hButton))
				// EnableWindow(hButton, FALSE);// EnableWindow设置控件禁用或启用
			 //else
				// EnableWindow(hButton, TRUE);

			 IsWindowEnabled(hButton) ? EnableWindow(hButton, FALSE) : EnableWindow(hButton, TRUE);
			 IsWindowEnabled(hCheckBox) ? EnableWindow(hCheckBox, FALSE) : EnableWindow(hCheckBox, TRUE);
			 IsWindowEnabled(hRadioButton) ? EnableWindow(hRadioButton, FALSE) : EnableWindow(hRadioButton, TRUE);
			 break;

		default:
			//对于其他控件的通知，或者未处理的情况，调用默认的消息处理函数
			return DefWindowProc(hDlg, uMsg, wParam, lParam);
		}
		break;

	case WM_CLOSE:
		EndDialog(hDlg, 0);
		break;

	default:
		bRet = FALSE;
		break;
	}

	return bRet; //默认返回真

}

int APIENTRY WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInStance,
	LPSTR lpCmdLine,
	int nCmdShow)//指定应用程序窗口的显示状态
{
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_MAIN), NULL, MainDlgProc);


	return 0;
}