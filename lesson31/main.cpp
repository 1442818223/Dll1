//list book列表框
#include <Windows.h>
#include"resource.h"

//hDlg表示当前对话框的句柄 uMsg表示当前消息的类型如按钮点击、鼠标移动等
INT_PTR CALLBACK MainDlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	/*
	WM_COMMAND 是 Windows 操作系统中用于处理菜单项、工具栏按钮等用户界面元素的消息
	wParam: 低位字节包含了来自控件的通知代码，高位字节包含了控件标识符。
	lParam: 包含了指向控件的句柄的指针，如果消息是由加速键生成的，则为 NULL。
	*/
	BOOL bRet = TRUE;

	int wmId,wmEvent;
	static HWND hwndList1, hwndList2, hwndList3;

	switch (uMsg) {
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		hwndList1 = GetDlgItem(hDlg, IDC_LIST1);
		hwndList2 = GetDlgItem(hDlg, IDC_LIST2);
		hwndList3 = GetDlgItem(hDlg, IDC_LIST3);

		int iIndex,iLength, iCount,iSelect;
		TCHAR* pVarText;

		switch (wmId) {//低位字节包含了来自控件的代码
		case IDC_LIST1:
			//if (wmEvent == LBN_SELCHANGE) {//LBN_SELCHANGE为选中IDC_LIST1的某一行
			if (wmEvent == LBN_DBLCLK){// LBN_DBLCLK为双击

			iIndex = SendMessage(hwndList1, LB_GETCURSEL, 0, 0);// 获取当前选中项的索引 
				iLength = SendMessage(hwndList1, LB_GETTEXTLEN,iIndex, 0) + 1; // 获取选中项文本的长度
				pVarText = (TCHAR*)calloc(iLength, sizeof(TCHAR));
				SendMessage(hwndList1, LB_GETTEXT, iIndex, (LPARAM)pVarText);//获取选中项的文本。
				MessageBox(hDlg, pVarText, TEXT("TEST"), MB_OK);
			}
			break;
	
		case IDC_BUTTON1:
			                      // LB_ADDSTRING增加字符串
			SendMessage(hwndList1, LB_ADDSTRING, 0, (LPARAM)TEXT("Hello"));
			SendMessage(hwndList1, LB_ADDSTRING, 0, (LPARAM)TEXT("Hello1"));
			SendMessage(hwndList1, LB_ADDSTRING, 0, (LPARAM)TEXT("Hello2"));
			break;

		case IDC_BUTTON2:          //LB_DELETESTRING,2删除第二个
			SendMessage(hwndList1, LB_DELETESTRING, 2, 0);
			break;

		case IDC_BUTTON3:          //LB_RESETCONTENT为重置
			SendMessage(hwndList1, LB_RESETCONTENT, 0, 0);
			break;

		case IDC_BUTTON4:
			SendMessage(hwndList1, LB_SETCURSEL, 2, 0); // LB_SETCURSEL,2为选中IDC_LIST1的第1行
			break;

		case IDC_BUTTON5:
			SendMessage(hwndList1, LB_SETCURSEL, -1, 0);//没有-1这一行,所以为取消选中IDC_LIST1的选中行
			break;

		case IDC_BUTTON7:    //将 IDC_LIST1中选中行的字符串传送到IDC_LIST2中(必须选中某行)
			iIndex = SendMessage(hwndList1, LB_GETCURSEL, 0, 0);
			iLength = SendMessage(hwndList1, LB_GETTEXTLEN, iIndex, 0) + 1; 
			pVarText = (TCHAR*)calloc(iLength, sizeof(TCHAR));
			SendMessage(hwndList1, LB_GETTEXT,iIndex, (LPARAM)pVarText); 
			SendMessage(hwndList2, LB_INSERTSTRING, -1,(LPARAM)pVarText);//-1: 表示在列表框的末尾插入新字符串
			SendMessage(hwndList1, LB_DELETESTRING, iIndex, 0);
			break;

		case IDC_BUTTON6: //插入
			SendMessage(hwndList2, LB_INSERTSTRING, -1,(LPARAM)TEXT("one"));
			SendMessage(hwndList2, LB_INSERTSTRING, -1,(LPARAM)TEXT("t wo"));
			SendMessage(hwndList2, LB_INSERTSTRING, - 1,(LPARAM)TEXT("three"));
			break;

		case IDC_BUTTON8://插入在下标2的位置
			SendMessage(hwndList2, LB_INSERTSTRING, 2, (LPARAM)TEXT("二"));
			break;

		case IDC_BUTTON9: //前提是资源编辑框里面把listbox2的属性设置多选
			SendMessage(hwndList2, LB_SETSEL, 1, 2); //设置listbox2的第二,第五行为选中状态
			SendMessage(hwndList2, LB_SETSEL, 1, 5);
			break;

		case IDC_BUTTON10:
			SendMessage(hwndList2, LB_SETSEL, 0, 2); //设置listbox2的第二,第五行为非选中状态
			SendMessage(hwndList2, LB_SETSEL, 0, 5);
			break;

		case IDC_BUTTON11:
			SendMessage(hwndList2, LB_SETSEL, 1, -1); //-1为全部,1为选中
			break;

		case IDC_BUTTON12://将listbox2中选中的项向listbox3传送
			// 计算列表框2的项总数
			iCount = SendMessage(hwndList2, LB_GETCOUNT, 0, 0);
			// 从最后开始遍历列表框2的项
			for (iIndex = iCount - 1; iIndex >= 0; iIndex--){//从后往前遍历是因为删除后的下标前移问题
				// 检查当前项是否被选中
				iSelect = SendMessage(hwndList2, LB_GETSEL, iIndex, 0);
				if (iSelect != 0) {// 如果为非零，表示当前项被选中
					// 获取当前选中项的文本长度
					iLength = SendMessage(hwndList2, LB_GETTEXTLEN, iIndex, 0);
					// 分配内存，获取当前选中项的文本
					pVarText = (TCHAR*)calloc(iLength + 1, sizeof(TCHAR));
					SendMessage(hwndList2, LB_GETTEXT, iIndex, (LPARAM)pVarText);
					// 向列表框3中插入选中项的文本
					SendMessage(hwndList3, LB_INSERTSTRING, -1, (LPARAM)pVarText);
					// 从列表框2中删除选中项
					SendMessage(hwndList2, LB_DELETESTRING, iIndex, 0);
				}
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