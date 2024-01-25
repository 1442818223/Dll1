#include <Windows.h>
#include"resource.h"

/*
注意:多个Radio放在了Group中后,只需要对首个Radio的分组属性设置为TRUE  即可分为一组
*/


void PaintTheBlock(HWND hwnd,int iFigure, COLORREF drawColor) {
/*	
HDC 是 Windows 编程中用于表示设备上下文（Device Context）的句柄类型。
它通常用于绘图操作，包括在窗口或图形表面上绘制图形、文本等。
*/
	HDC hdc;
	HBRUSH hBrush;
	
	RECT rect; //RECT 是 Windows API 中的一个结构体，用于表示矩形的坐标
	GetClientRect(hwnd, &rect);//GetClientRect 是一个 Windows API 函数，用于获取指定窗口客户区的矩形坐标。

	InvalidateRect(hwnd, NULL, TRUE); //先让先前的控件窗口失效后刷新才会重画
	UpdateWindow(hwnd); 


	// 获取窗口的绘图上下文
	hdc = GetDC(hwnd);

	// 创建一个实心画刷，并设置颜色为 drawColor
	hBrush = CreateSolidBrush(drawColor);

	// 将画刷选入绘图上下文，并保存先前的画刷句柄
	hBrush = (HBRUSH)SelectObject(hdc, hBrush);


	if(iFigure== IDC_RADIO10)
	//Ellipse 函数在窗口 hwnd 的客户区绘制一个椭圆（椭圆的位置和大小由客户区的矩形坐标定义）
	Ellipse(hdc, rect.left, rect.top, rect.right, rect.bottom); 
	else
    //Rectangle画方块
	Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);


	// 删除新创建的画刷，并恢复先前的画刷
	DeleteObject(SelectObject(hdc, hBrush));

	// 释放绘图上下文
	ReleaseDC(hwnd, hdc);
}


//hDlg表示当前对话框的句柄 uMsg表示当前消息的类型如按钮点击、鼠标移动等
INT_PTR CALLBACK MainDlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	/*
	WM_COMMAND 是 Windows 操作系统中用于处理菜单项、工具栏按钮等用户界面元素的消息
	wParam: 低位字节包含了来自控件的通知代码，高位字节包含了控件标识符。
	lParam: 包含了指向控件的句柄的指针，如果消息是由加速键生成的，则为 NULL。
	*/
	BOOL bRet = TRUE;

	static HWND hCtrlBlock;
	static int iFigure;
	static COLORREF drawColor;

	switch (uMsg) {

	case WM_INITDIALOG: //初始化对话框消息时就得到静态文本框句柄
		hCtrlBlock = GetDlgItem(hDlg,IDC_STATIC3);
		iFigure = IDC_RADIO9;  //刚开始默认为画方块
		drawColor = RGB(0, 0, 0); //颜色默认设置为黑色
		//SendMessage(GetDlgItem(hDlg, IDC_RADIO1), BM_SETCHECK, 1, 0); 设置黑色和方框为选中状态
		//SendMessage(GetDlgItem(hDlg, IDC_RADIO9), BM_SETCHECK, 1, 0);
		SendDlgItemMessage(hDlg, IDC_RADIO1, BM_SETCHECK, 1, 0); //这样写相当于上面的两个API合成
		SendDlgItemMessage(hDlg, IDC_RADIO9, BM_SETCHECK, 1, 0);
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam)) {//低位字节包含了来自控件的代码

		case IDC_RADIO1:
			drawColor = RGB(0, 0, 0);
			break;

		case IDC_RADIO2:
			drawColor = RGB(0, 0, 255);
			break;

		case IDC_RADIO3:
			drawColor = RGB(0, 255,0);
			break;

		case IDC_RADIO4:
			drawColor = RGB(0, 255, 255);
			break;

		case IDC_RADIO5:
			drawColor = RGB(255,0,0);
			break;

		case IDC_RADIO6:
			drawColor = RGB(255 , 0, 255);
			break;

		case IDC_RADIO7:
			drawColor = RGB(255,255,0);
			break;

		case IDC_RADIO8:
			drawColor = RGB(255, 255, 255);
			break;


		case IDC_RADIO9:
			iFigure = IDC_RADIO9;
			break;

		case IDC_RADIO10:
			iFigure = IDC_RADIO10;
			break;
			
		default:
			//对于其他控件的通知，或者未处理的情况，调用默认的消息处理函数
			return DefWindowProc(hDlg, uMsg, wParam, lParam);
			break;
		}
		PaintTheBlock(hCtrlBlock, iFigure, drawColor);
		break;

	case WM_PAINT: //设置刚开始就有画好的图形
		PaintTheBlock(hCtrlBlock, iFigure, drawColor);
		bRet = FALSE;
		//具体来说，bRet = FALSE; 这一行代码是在告诉系统：“我已经处理了 WM_PAINT 消息，
		// 不需要系统再做额外的默认处理，直接返回即可。”
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