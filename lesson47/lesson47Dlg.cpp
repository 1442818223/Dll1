
// lesson47Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "lesson47.h"
#include "lesson47Dlg.h"
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


// Clesson47Dlg 对话框











void Clesson47Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(Clesson47Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &Clesson47Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &Clesson47Dlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// Clesson47Dlg 消息处理程序

BOOL Clesson47Dlg::OnInitDialog()
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

void Clesson47Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void Clesson47Dlg::OnPaint()
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
HCURSOR Clesson47Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




//
//MFC线程同步的四中方法
//

CCriticalSection* g_pCS;    //临界区对象,需要在构造函数中创建  1,
CMutex* g_pMutex;          //互斥量对象                       2,
CSemaphore* g_pSemaphore; //信号量对象                        3,
CEvent* g_pEvent;        //事件对象                           4,
Clesson47Dlg::Clesson47Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LESSON47_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	
	//1,
	g_pCS = new CCriticalSection(); //有构造 就要有析构,自己在头文件中声明析构函数
	//2,
	g_pMutex = new CMutex();
	//3,
	g_pSemaphore = new CSemaphore(1, 1); //初始计数值和最大计数值都设置为 1
	//4,
	g_pEvent = new CEvent(TRUE);   //事件对象 刚刚创建时就有信号
}
Clesson47Dlg::~Clesson47Dlg() { //析构函数需要再Clesson47Dlg::类中声明
	//1,
	delete g_pCS;
	g_pCS = NULL;
	//2,
	delete g_pMutex;
	g_pMutex = NULL;
	//3,
	delete g_pSemaphore;
	g_pSemaphore = NULL;
	//4,
	delete g_pEvent;
	g_pEvent = NULL;
}

int k = 1;
int total = 0;
UINT ThreadProcA(LPVOID pParam) {
//方法一:
	//for (int i = 1; i <= 100000000; i++) {	
	//	//使用临界区对象锁
	//	g_pCS->Lock();
	//	k = k * 2;
	//	k = k / 2;
	//	total += k;
	//	g_pCS->Unlock();
	//}

//方法二:
	//CSingleLock singleLock(g_pMutex); //利用互斥量创建一把锁
	//for (int i = 1; i <= 1000000; i++) {
	//	singleLock.Lock();  //加锁
	//	if (singleLock.IsLocked()) {
	//		k = k * 2;
	//		k = k / 2;
	//		total += k;
	//		singleLock.Unlock();//解锁
	//	}
	//}

//方法三:
	//CSingleLock singleLock(g_pSemaphore);//用信号量创建锁
	//for (int i = 1; i <= 100000000; i++) {
	//	singleLock.Lock();  //加锁
	//	k = k * 2;
	//	k = k / 2;
	//	total += k;
	//	singleLock.Unlock();//解锁
	//}

//方法四:
	CSingleLock singleLock(g_pEvent); //用事件对象创建锁
	for (int i = 1; i <= 100000000; i++) {
		singleLock.Lock();  //加锁
		k = k * 2;
		k = k / 2;
		total += k;
		singleLock.Unlock();//解锁
		g_pEvent->SetEvent();//事件对象发信号告诉其他线程可以使用了
	}

	SetDlgItemInt(AfxGetApp()->m_pMainWnd->m_hWnd, IDC_STATIC1, total, false);
	return 0;
}
UINT ThreadProcB(LPVOID pParam) {
//方法一:
	//for (int i = 1; i <= 100000000; i++) {
	//	//使用临界区对象锁
	//	g_pCS->Lock();
	//	k = k * 2;
	//	k = k / 2;
	//	total += k;
	//	g_pCS->Unlock();
	//}

//方法二:
	//CSingleLock singleLock(g_pMutex); //利用互斥量创建一把锁
	//for (int i = 1; i <= 1000000; i++) {
	//	singleLock.Lock();  //加锁
	//	if (singleLock.IsLocked()) {
	//		k = k * 2;
	//		k = k / 2;
	//		total += k;
	//		singleLock.Unlock();//解锁
	//	}
	//}

//方法三:
	//CSingleLock singleLock(g_pSemaphore);//用信号量创建锁
	//	for (int i = 1; i <= 100000000; i++) {	
	//		singleLock.Lock();  //加锁
	//		k = k * 2;
	//		k = k / 2;
	//		total += k;
	//		singleLock.Unlock();//解锁
	//	}

//方法四:
	CSingleLock singleLock(g_pEvent); //用事件对象创建锁
		for (int i = 1; i <= 100000000; i++) {	
			singleLock.Lock();  //加锁
			k = k * 2;
			k = k / 2;
			total += k;
			singleLock.Unlock();//解锁
			g_pEvent->SetEvent();//事件对象发信号告诉其他线程可以使用了
		}
	SetDlgItemInt(AfxGetApp()->m_pMainWnd->m_hWnd, IDC_STATIC1, total, false);
	return 0;
}
void Clesson47Dlg::OnBnClickedButton1()
{
	AfxBeginThread(ThreadProcA, NULL);
}
void Clesson47Dlg::OnBnClickedButton2()
{
	AfxBeginThread(ThreadProcB, NULL);
}
