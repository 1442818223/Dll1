// lesson45.cpp : 定义应用程序的入口点。
//

#include "framework.h"
#include "lesson45.h"

#include <process.h> //c语言方法创建多线程需要的头文件


#define MAX_LOADSTRING 100

// 全局变量:
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名
HWND hWnd;
int cxClient, cyClient;


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
    LoadStringW(hInstance, IDC_LESSON45, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 执行应用程序初始化:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LESSON45));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LESSON45));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName = NULL;// MAKEINTRESOURCEW(IDC_LESSON45);
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

    hWnd=CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}





//线程函数
VOID ThreadA(PVOID pvoid) {
    HDC hdc;
    HBRUSH hBrush;
    int xLeft, xRight, yTop, yBottom,iRed, iGreen, iBlue;
    while (TRUE)
    {
        if (cxClient != 0 || cyClient != 0) {
            xLeft = rand() % cxClient;
            xRight = rand() % cxClient;
            yTop = rand() % cyClient;
            yBottom = rand()% cyClient;
            iRed = rand() % 255;
            iGreen = rand() % 255;
            iBlue = rand() % 255;
            
            hdc = GetDC(hWnd);

            hBrush = CreateSolidBrush (RGB(iRed, iGreen, iBlue));
            SelectObject(hdc, hBrush);

            Rectangle(hdc,
                min(xLeft, xRight), min(yTop, yBottom), 
                max(xLeft, xRight), max(yTop, yBottom));

            Sleep(1000);

            ReleaseDC(hWnd, hdc);
            DeleteObject(hBrush);
        }
    }
}
VOID ThreadB(PVOID pvoid) {
    HDC hdc;
    HBRUSH hBrush;
    int xLeft, xRight, yTop, yBottom, iRed, iGreen, iBlue;
    while (TRUE)
    {
        if (cxClient != 0 || cyClient != 0) {
            xLeft = rand() % cxClient;
            xRight = rand() % cxClient;
            yTop = rand() % cyClient;
            yBottom = rand() % cyClient;
            iRed = rand() % 255;
            iGreen = rand() % 255;
            iBlue = rand() % 255;

            hdc = GetDC(hWnd);

            hBrush = CreateSolidBrush(RGB(iRed, iGreen, iBlue));
            SelectObject(hdc, hBrush);

            Ellipse(hdc,
                min(xLeft, xRight), min(yTop, yBottom),
                max(xLeft, xRight), max(yTop, yBottom));

            Sleep(600);

            ReleaseDC(hWnd, hdc);
            DeleteObject(hBrush);
        }
    }
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
             




    case WM_CREATE:
        //用c语言创建线程 ,而不是用API创建线程
        _beginthread(ThreadA, 0, NULL);//#include <process.h> 
/*      
    uintptr_t _beginthread(
    void (*start_address)(void*),  //指向新线程要执行的函数的指针，该函数应该有一个 void* 类型的参数。
    unsigned stack_size, //新线程的堆栈大小，通常为 0 表示使用默认堆栈大小。
    void* arglist //传递给新线程函数的参数。
    );
*/
        _beginthread(ThreadB, 0, NULL);
        return 0;
        //WM_CREATE 是一个比较特殊的消息，返回 0 是为了表示窗口创建成功，并没有错误发生。
    case WM_SIZE:
        cxClient = LOWORD(lParam); //通过lParam保存窗口区的长和宽
        cyClient = HIWORD(lParam);
        return 0;





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
