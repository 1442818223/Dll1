
// lesson46Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "lesson46.h"
#include "lesson46Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif




// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Clesson46Dlg 对话框

BOOL g_bRunningA;  //判断线程是否执行的标志位
CWinThread* g_pThreadA;//对话框类 Clesson46Dlg 的构造函数中初始化函数中初始化为NULL
//话框类 Clesson46Dlg 的构造函数。
Clesson46Dlg::Clesson46Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LESSON46_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);//通过获取应用程序对象的指针，调用 LoadIcon 函数加载应用程序的主图标。
	g_pThreadA = NULL;  
	g_bRunningA = false;  //初始化为false 为线程未运行
}

void Clesson46Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(Clesson46Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &Clesson46Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &Clesson46Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &Clesson46Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &Clesson46Dlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &Clesson46Dlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &Clesson46Dlg::OnBnClickedButton6)
END_MESSAGE_MAP()


// Clesson46Dlg 消息处理程序

BOOL Clesson46Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void Clesson46Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void Clesson46Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR Clesson46Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}











void Clesson46Dlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码

	for (int i = 1; i <= 100; i++) {
		
     		/*   WinAPI 函数
       BOOL SetDlgItemInt(             
       HWND hDlg,     // 对话框句柄
       int  nIDDlgItem, // 控件的 ID
       UINT uValue,    // 要设置的整数值
       BOOL bSigned    // 是否为有符号整数
     );
		*/

/*      MFC 函数  (参数3可省略)
void SetDlgItemInt(int nID, UINT nValue, BOOL bSigned = TRUE);
*/
		SetDlgItemInt(IDC_STATIC1,i);  //MFC 作用域下的SetDlgItemInt函数

		Sleep(1000);                  //单线程这么操作会阻塞
	}
}

UINT DemoB(LPVOID pParam) {    //MFC中调用线程函数,必须这么写
	for (int m = 100; m >= 1; m--) {
		SetDlgItemInt(AfxGetApp()->m_pMainWnd->m_hWnd, IDC_STATIC3, m, false);//API作用域下的SetDlgItemInt函数
		//AfxGetApp() 是 MFC 中的一个函数，用于获取当前应用程序对象的指针。

		Sleep(1000);
	}
	return 0;
}
void Clesson46Dlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	AfxBeginThread(DemoB, NULL);
}




UINT DemoA(LPVOID pParam)   //需要在lesson46Dlg.h中声明 为全局函数,不一定为 Clesson46Dlg的类函数
{
	for (int m = 1; m <= 100; m++) {
		if (!g_bRunningA)//标志位为假就终止
		{
			break;
		}
		SetDlgItemInt(AfxGetApp()->m_pMainWnd->m_hWnd, IDC_STATIC2, m, false);//API作用域下的SetDlgItemInt函数
		               //AfxGetApp() 是 MFC 中的一个函数，用于获取当前应用程序对象的指针。
		Sleep(500);
	}
	g_pThreadA = NULL;
	g_bRunningA = FALSE;

	return 0;
}
void Clesson46Dlg::OnBnClickedButton2()
{
	//AfxBeginThread 是 MFC 框架中的函数，用于创建并启动一个新的线程。
	if (g_pThreadA == NULL) {
			g_pThreadA = AfxBeginThread(DemoA, NULL);//DemoA 是线程函数的指针。NULL 是线程函数的参数。
			g_bRunningA = TRUE;  //线程启动时标记为真
	}
	else {
		AfxMessageBox(_T("线程已经启动")); 
	}
}

void Clesson46Dlg::OnBnClickedButton4()
{
	if (g_pThreadA == NULL) {
		AfxMessageBox(_T("线程不存在"));
	}
	else {
		g_pThreadA->SuspendThread(); //通过线程句柄 暂停，挂起
	}
}

void Clesson46Dlg::OnBnClickedButton5()
{
	if (g_pThreadA == NULL) {
		AfxMessageBox(_T("线程不存在"));
	}
	else {
		g_pThreadA->ResumeThread();//通过线程句柄 继续执行
	}
}

void Clesson46Dlg::OnBnClickedButton6()
{
	if (g_pThreadA == NULL) {
		AfxMessageBox(_T("线程不存在"));
	}
	else {
		g_bRunningA = FALSE;   //标志位为假就终止
	}
}
