#include <Windows.h>

HINSTANCE hinst;//实例句柄
HWND hwnd;//窗口句柄

LRESULT CALLBACK MainWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
int APIENTRY WinMain(HINSTANCE hinstance,//是当前程序实例的句柄
	HINSTANCE hPrevInstance,//始终为 NULL,不再支持多个实例的应用程序
	LPSTR lpCmdLine,// 是命令行参数，允许你从命令行获取程序运行时传递的额外信息
	int nCmdshow)//它通常用于控制窗口最初是正常、最小化还是最大化显示。
{
	//保存实例句柄
	hinst = hinstance;

	//定义窗口类
	WNDCLASSEX wcx;


/*
typedef struct tagMSG {
  HWND   hwnd;//指定接收消息的窗口句柄。
  UINT   message;//指定消息的类型。
  WPARAM wParam;//wParam 和 lParam: 用于传递额外的消息信息，具体含义取决于消息类型。
  LPARAM lParam;//
  DWORD  time;//指定消息被产生的时间。
  POINT  pt;//指定鼠标指针的屏幕坐标。
  DWORD  lPrivate;//保留字段。
} MSG, *PMSG, *LPMSG;
*/
	//消息
	MSG msg;
	BOOL fGotMessage;

	wcx.cbSize = sizeof(wcx);
	wcx.style = CS_HREDRAW | CS_VREDRAW; //窗口宽度和高度发生变化就重新画
	wcx.lpfnWndProc = MainWndProc; //**************窗口过程
	wcx.lpszClassName = "MainWClass";// 窗口类的名称
	wcx.cbClsExtra = 0;//不使用额外的内存保存信息
	wcx.cbWndExtra = 0;//不使用额外的内存保存窗口信息
	wcx.hInstance = hinstance;//窗口类所属的实例句柄
	wcx.hIcon = LoadIcon(NULL, IDI_APPLICATION); //加载图标 默认  (大图标)
	wcx.hCursor = LoadCursor(NULL, IDC_ARROW); //加载鼠标指针形状 默认
	wcx.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);//使用白色的画刷创建背景
	wcx.lpszMenuName = NULL;//窗口菜单 没设置
	//加载(小图标)
	wcx.hIconSm = (HICON)LoadImage(hinstance, // 是应用程序实例的句柄，用于指定包含图标资源的模块
		MAKEINTRESOURCE(5), //是资源的标识符。这里使用 MAKEINTRESOURCE 宏将整数 5 转换为资源标识符字符串。
		IMAGE_ICON,//表示加载的是图标类型的资源
		GetSystemMetrics(SM_CXSMICON), //GetSystemMetrics 函数获取了系统定义的小图标的标准大小,加载图标的宽度和高度
		GetSystemMetrics(SM_CYSMICON),
		LR_DEFAULTCOLOR);//使用图像的默认颜色


	//注册窗口
	if (!RegisterClassEx(&wcx)) {
		return 1;
	}
	
	//创建窗口
	hwnd = CreateWindow(
			"MainWClass",
			"Hello",//窗口名
			WS_OVERLAPPEDWINDOW, //窗口样式 
		    CW_USEDEFAULT,//位置
			CW_USEDEFAULT,
			CW_USEDEFAULT,//宽度
		    CW_USEDEFAULT,//高度
			(HWND)NULL,//无父窗口
			(HMENU)NULL,//菜单
			hinstance,
			(LPVOID)NULL);
		if (!hwnd)
		{
			return 1;
		}

    // 显示窗口
		ShowWindow(hwnd, nCmdshow);
		UpdateWindow(hwnd);

	//处理消息
		/*
		BOOL GetMessage(
        LPMSG lpMsg,  // 指向MSG结构的指针，用于存储消息信息
        HWND hWnd,     // 等待消息的窗口句柄，如果为NULL，则获取任何线程的消息
        UINT wMsgFilterMin,  // 指定最小的消息值
         UINT wMsgFilterMax   // 指定最大的消息值
         );
		*/
		while ((fGotMessage = GetMessage(&msg,(HWND)NULL, 0, 0)) != 0) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);   //***消息首先是是发给系统的***
		}

		return msg.wParam;//msg.wParam 存储的是消息循环结束的退出码
}


//MainWndProc 是窗口过程函数，用于处理窗口消息。
LRESULT CALLBACK MainWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_LBUTTONDOWN: //点击鼠标左键
		MessageBox(hwnd,"Hello窗口!","hello", MB_OK); return 0;
	case WM_DESTROY:  //左上角点×时 
		PostQuitMessage(0);  //销毁窗口
		return 0;
	default: //默认
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}
