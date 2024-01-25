// lesson33.cpp : 定义应用程序的入口点。
//

#include "framework.h"
#include "lesson33.h"

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
    LoadStringW(hInstance, IDC_LESSON33, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 执行应用程序初始化:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LESSON33));

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

    return (int) msg.wParam;
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

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LESSON33));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName = NULL;//MAKEINTRESOURCEW(IDC_LESSON33);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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
                         //位置                         //11个字符
            TextOut(hdc, 100, 20, _T("Hello world"), 11);//将指定的文本字符串从给定坐标开始输出到设备上下文

            MoveToEx(hdc, 100, 100, NULL);  // 移动画笔到起始点 (100, 100)
            LineTo(hdc, 600, 100);          // 从起始点画直线到 (600, 100)
            LineTo(hdc, 600, 300);          // 画直线到 (600, 300)
            LineTo(hdc, 100, 300);          // 画直线到 (100, 300)
            LineTo(hdc, 100, 100);          // 闭合矩形，画直线回到起始点 (100, 100)

            SetTextAlign(hdc, TA_LEFT | TA_TOP);  // 设置文本对齐方式为左对齐和顶部对齐(不写也可以,因为是默认这么设置的)
            TextOut(hdc, 100, 100, _T("Hello world"), 11);  // 在设备上下文上绘制文本

            SetTextAlign(hdc, TA_RIGHT); //设置为右边对齐 ,默认是还以顶部对齐
            TextOut(hdc, 600, 100, _T("Hello world"), 11);

            SetTextAlign(hdc, TA_CENTER|TA_TOP); //设置文本对齐方式为中间对齐和顶部对齐
            TextOut(hdc, 350, 100, _T("Hello world"), 11);

            SetTextAlign(hdc, TA_BOTTOM | TA_LEFT);
            TextOut(hdc, 100, 300, _T("Hello world"), 11);


            SetTextAlign(hdc, TA_BOTTOM | TA_CENTER);
            TextOut(hdc, 350, 300, _T("Hello world"), 11);

            
            SetTextAlign(hdc, TA_BOTTOM | TA_RIGHT);
            TextOut(hdc, 600, 300, _T("Hello world"), 11);
            
            SetTextAlign(hdc, TA_LEFT | TA_BASELINE);
            TextOut(hdc, 100, 200, _T("Hello world"), 11);
            
            SetTextAlign(hdc, TA_CENTER | TA_BASELINE); 
            TextOut(hdc, 350, 200, _T("Hello world"), 11);

            SetTextAlign(hdc, TA_RIGHT | TA_BASELINE);
            TextOut(hdc, 600, 200, _T("Hello world"), 11);

            MoveToEx(hdc, 100, 400, NULL);
            SetTextAlign(hdc, TA_LEFT | TA_TOP | TA_UPDATECP); //TA_UPDATECP适用于指定一个点之后连续输出,
            TextOut(hdc, 0, 0, _T("Hello world"), 11);         //因此 TextOut不需要起始点
            TextOut(hdc, 0, 0, _T("Hello world"), 11);
            TextOut(hdc, 0, 0,_T("Hello world"), 11);


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
