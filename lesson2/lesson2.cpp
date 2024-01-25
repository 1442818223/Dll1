// lesson2.cpp : 定义应用程序的入口点。
//

#include "framework.h"
#include "lesson2.h"

#define MAX_LOADSTRING 100

// 全局变量:
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名
HWND hWnd;                                      //窗口句柄


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
    UNREFERENCED_PARAMETER(hPrevInstance); //通常用于防止编译器发出关于未使用参数的警告。
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 在此处放置代码。

    // 初始化全局字符串
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_LESSON2, szWindowClass, MAX_LOADSTRING);

    //定义窗口类并注册
    MyRegisterClass(hInstance);

    // 执行应用程序初始化,   保存实例句柄并创建主窗口
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    //这行代码的作用是加载资源中标识符为 IDC_LESSON2 的加速器表。
    //这个加速器表通常包含了键盘快捷键和相应的命令标识符，用于处理在应用程序窗口中的键盘输入。
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LESSON2));

    MSG msg;



//***PeekMessage 是 Windows API 中的函数之一，用于从消息队列中检查是否有消息，并将消息存储在指定的消息结构中。
    // 主消息循环:
    while (GetMessage(&msg, nullptr, 0, 0))       //GetMessage是阻塞函数    
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))//如果函数成功翻译了消息，返回非零值；否则返回零。
        {                              //让加速键和菜单项的ID一样即可,这里TranslateAccelerator会继续将加速键消息转换为普通消息继续加入队列
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LESSON2));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName = NULL;// MAKEINTRESOURCEW(IDC_LESSON2); //菜单项设置为空
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

    hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW, //创建主窗口
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
    AllocConsole(); //增加DOS窗口
    
    LPCWSTR msgText = L"Hello Meessage";  // LPCWSTR宽字符指针
    LPCWSTR msgTile = L"Demo";


    switch (message)
    {

    case WM_SYSCOMMAND:
        /*
        用于通知窗口过程（Window Procedure）有关系统命令的信息。
        这个消息通常在用户点击窗口标题栏上的控制按钮（最小化、最大化、关闭等）或者执行系统菜单项时被发送。
        */
        break;
    case WM_CREATE:
        /*
        主窗口创建之前接收到的消息,可以在主窗口创建之前做一些其他操作
        */
        break;
    case WM_LBUTTONDOWN:
        InvalidateRect(hWnd, NULL, TRUE); //使窗口失效重画
        break;


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
