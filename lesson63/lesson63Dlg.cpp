
// lesson63Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "lesson63.h"
#include "lesson63Dlg.h"
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


// Clesson63Dlg 对话框



Clesson63Dlg::Clesson63Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LESSON63_DIALOG, pParent)
	, m_strText(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Clesson63Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_STATIC1, m_strText);
}

BEGIN_MESSAGE_MAP(Clesson63Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// Clesson63Dlg 消息处理程序

BOOL Clesson63Dlg::OnInitDialog()
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









	// TODO: 在此添加额外的初始化代码                                                        //1,
/*
*  Windows API 函数，用于打开一个已存在的文件映射对象。
HANDLE OpenFileMapping(
  DWORD   dwDesiredAccess,//打开文件映射对象的访问权限。
  BOOL    bInheritHandle,// 指定返回的句柄是否可以由子进程继承。
  LPCTSTR lpName//文件映射对象的名称。如果是本地对象，则形式为 "Local\\Name"；如果是全局对象，则形式为 "Global\\Name"。
);
*/
	m_hMapObject = OpenFileMapping(FILE_MAP_READ,FALSE,TEXT("shared_memory"));
	if (!m_hMapObject) {
		AfxMessageBox(TEXT("Can't open shared memory file."));
		return FALSE;
	}

/*
* Windows API 函数，用于将一个文件映射对象映射到调用进程的地址空间，从而允许对文件内容进行直接的内存访问。
LPVOID MapViewOfFile(
  HANDLE hFileMappingObject,// 要映射的文件映射对象的句柄，通常由 CreateFileMapping 或 OpenFileMapping 返回。
  DWORD  dwDesiredAccess,// 对映射区域的访问权限。
  DWORD  dwFileOffsetHigh,//dwFileOffsetHigh 和 dwFileOffsetLow: 文件偏移量的高位和低位。指定文件中的起始位置，从这个位置开始映射。
  DWORD  dwFileOffsetLow,//
  SIZE_T dwNumberOfBytesToMap// 映射的字节数。如果为 0，则映射整个文件。
);
*/
	m_pszMapView = (LPTSTR)MapViewOfFile(m_hMapObject,FILE_MAP_READ, 0, 0, 0); 
	if (!m_pszMapView)
	{
		AfxMessageBox(TEXT("Can't map view of shared memory file."));
		return FALSE;
	}

/*
* MFC下的SetTimer设置定时器。
UINT_PTR SetTimer(
UINT_PTR nIDEvent,//定时器的标识符，用于区分不同的定时器。如果 nIDEvent 不为零，则它必须是唯一的。如果 nIDEvent 为零，系统会为您分配一个唯一的标识符。
UINT nElapse,// 定时器的超时值，以毫秒为单位。
TIMERPROC lpfnTimer = NULL);//指向计时器回调函数的指针。如果为 NULL，则表示不使用回调函数。
*/
	SetTimer(0x10,500, NULL);












	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void Clesson63Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void Clesson63Dlg::OnPaint()
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
HCURSOR Clesson63Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}






void Clesson63Dlg::OnTimer(UINT_PTR nIDEvent)                                   //2,
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	//1,先在项目图形控制界面,点主窗口右键,找到消息,选择WM_TIMER 点<ADD>就增加了消息处理函数
	//2,
	m_strText = m_pszMapView;
	UpdateData(FALSE);
	
	CDialogEx::OnTimer(nIDEvent);
}
