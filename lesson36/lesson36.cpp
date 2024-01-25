// lesson36.cpp : 定义应用程序的入口点。
//

#include "framework.h"
#include "lesson36.h"

#define MAX_LOADSTRING 100

// 全局变量:
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名

// 此代码模块中包含的函数的前向声明:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: 在此处放置代码。

	// 初始化全局字符串
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_LESSON36, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 执行应用程序初始化:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LESSON36));

	MSG msg;

	// 主消息循环:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}



//
//  函数: MyRegisterClass()
//
//  目标: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LESSON36));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;//MAKEINTRESOURCEW(IDC_LESSON36);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目标: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // 将实例句柄存储在全局变量中

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目标: 处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// 分析菜单选择:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: 在此处添加使用 hdc 的任何绘图代码...
		TCHAR p[] = _T("It was a wet night. The rain was falling fast, but the streets were full of people.\n Paris is never more lively than on a wet night. We walked through the streets, happy to be together.");
		TCHAR pt[] = _T("It was\t a wet night.\t The rain was falling fast,\t but the streets were full \tof people.\n Paris is never more \tlively than on a wet night. We walked through the streets,\t happy to be together.");
		RECT rect;
		rect.left = 10;
		rect.top = 10;
		rect.right = rect.left + 300;
		rect.bottom = rect.top + 200;
		Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);

		/*
		int DrawText(
			HDC         hdc,        // 目标设备上下文的句柄，表示绘制文本的目标画布。
			LPCTSTR     lpchText,   // 要输出的文本字符串，可以是以空字符结尾的字符串。
			int         cchText,    // 要绘制的字符数。如果为 -1，则 lpchText 是以空字符结尾的字符串，函数会一直绘制到字符串的结尾。
			LPRECT      lprc,       // 指向 RECT 结构的指针，表示用于绘制文本的矩形区域。
			UINT        format      // 控制文本的格式和对齐方式的标志，如 DT_CENTER、DT_VCENTER、DT_SINGLELINE 等。
		);
		*/
		DrawText(hdc, p, -1, &rect, DT_LEFT | DT_WORDBREAK | DT_EXTERNALLEADING);
		//DT_LEFT: 将文本左对齐。
		//DT_WORDBREAK: 在单词之间换行，而不是等到达到矩形边界才换行。
		//DT_EXTERNALLEADING:用于指定在计算文本行高时包括外部行间距。

		rect.left = 10;
		rect.top = 260;
		rect.right = rect.left + 300;
		rect.bottom = rect.top + 200;
		DrawText(hdc, pt, -1, &rect, DT_LEFT | DT_WORDBREAK | DT_EXTERNALLEADING | DT_EXPANDTABS);
		//DT_EXPANDTABS: 扩展文本中的制表符（Tab）字符为相应数量的空格。


		rect.left = 350;
		rect.top = 260;
		rect.right = rect.left + 300;
		rect.bottom = rect.top + 100;
		Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
		DrawText(hdc, p, -1, &rect, DT_LEFT | DT_NOCLIP);
		//DT_NOCLIP:超出边框继续往外画


		rect.left = 350;
		rect.top = 360;
		rect.right = rect.left + 300;
		rect.bottom = rect.top + 100;
		Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
		TCHAR p2[] = _T("Hello world");
		DrawText(hdc, p2, -1, &rect, DT_LEFT | DT_SINGLELINE);
		// DT_SINGLELINE:单行输出
		//DT_VCENTER:垂直方向的居中



		//DrawTextEx可以用DRAWTEXTPARAMS结构体对制表符和边距宽度进一步调控
		DRAWTEXTPARAMS param;
		param.cbSize = sizeof(DRAWTEXTPARAMS);
		param.iTabLength = 10;
		param.iLeftMargin = 12;
		param.iRightMargin = 0;
		param.uiLengthDrawn = 0;

		rect.left = 400;
		rect.top = 500;
		rect.right = rect.left + 300;
		rect.bottom = rect.top + 200;
		Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);                   //DT_TABSTOP:在计算文本时将制表符字符（Tab）视为制表位
		DrawTextEx(hdc, pt, -1, &rect, DT_LEFT | DT_EXPANDTABS | DT_WORDBREAK | DT_EXTERNALLEADING|DT_TABSTOP ,&param);
		
		
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
