
// lesson62Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "lesson62.h"
#include "lesson62Dlg.h"
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


// Clesson62Dlg 对话框



Clesson62Dlg::Clesson62Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LESSON62_DIALOG, pParent)
	, m_strSend(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Clesson62Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_strSend);
}

BEGIN_MESSAGE_MAP(Clesson62Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &Clesson62Dlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// Clesson62Dlg 消息处理程序

BOOL Clesson62Dlg::OnInitDialog()  //初始化
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







	// TODO: 在此添加额外的初始化代码                                   //1,
/*
* 创建或打开文件映射对象的 Windows API 函数
HANDLE CreateFileMapping(
  HANDLE                hFile,//文件句柄，可以是已经打开的文件、设备或者 INVALID_HANDLE_VALUE（表示创建一个不与具体文件相关的映射对象）。
  LPSECURITY_ATTRIBUTES lpFileMappingAttributes,// 一个指向 SECURITY_ATTRIBUTES 结构的指针，用于设置映射对象的安全性。可以为 NULL，表示使用默认安全性。
  DWORD                 flProtect,// 内存保护级别，指定了映射对象的页面保护。常见的值包括 PAGE_READWRITE、PAGE_READONLY 等。
  DWORD                 dwMaximumSizeHigh,//文件映射对象的最大大小（高位 DWORD）。通常设置为 0。
  DWORD                 dwMaximumSizeLow,// 文件映射对象的最大大小（低位 DWORD）。指定为文件大小，0 表示映射整个文件。
  LPCTSTR               lpName//文件映射对象的名称，用于多个进程之间共享。可以为 NULL。
);
*/
	//m_hMapObject和m_pszMapView需要在Clesson62Dlg::类里面声明
	m_hMapObject = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, 0x1000, TEXT("shared_memory"));
	//INVALID_HANDLE_VALUE 是一个特殊的值，它表示无效的句柄。
	// 在这种情况下，CreateFileMapping 函数会创建一个不与任何具体文件相关联的内存映射对象，
	// 而是在系统的页文件中分配一块内存。这种用法通常用于创建共享内存，供多个进程之间进行通信。
	if (!m_hMapObject)
	{
		AfxMessageBox(TEXT("Unable to create shared memory file."));
		return FALSE;
	}

/*
* 用于将文件映射对象映射到调用进程的地址空间。
LPVOID MapViewOfFile(
  HANDLE hFileMappingObject,//要映射的文件映射对象的句柄。
  DWORD  dwDesiredAccess,//访问权限，指定映射视图的访问方式。
  DWORD  dwFileOffsetHigh,//  dwFileOffsetHigh 和 dwFileOffsetLow: 文件偏移，指定要映射的文件开始处的偏移量。
  DWORD  dwFileOffsetLow,//
  SIZE_T dwNumberOfBytesToMap//映射到调用进程的字节数。
);
*/
	m_pszMapView = (LPTSTR)MapViewOfFile(m_hMapObject, FILE_MAP_WRITE, 0, 0, 0);
	if (!m_pszMapView)
	{
		AfxMessageBox(TEXT("Unbable to map shared memory file."));
		return FALSE;
	}







	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void Clesson62Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void Clesson62Dlg::OnPaint()
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
HCURSOR Clesson62Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}











void Clesson62Dlg::OnBnClickedButton1()                                //2,
{
	// TODO: 在此添加控件通知处理程序代码

	UpdateData();
	//lstrcpy 是一个字符串处理函数，用于将一个字符串（以 null 终止的字符串）复制到另一个字符串的缓冲区。
	lstrcpy(m_pszMapView, m_strSend);

}
