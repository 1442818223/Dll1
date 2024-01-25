
// lesson60Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "lesson60.h"
#include "lesson60Dlg.h"
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


// Clesson60Dlg 对话框



Clesson60Dlg::Clesson60Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LESSON60_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Clesson60Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(Clesson60Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &Clesson60Dlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// Clesson60Dlg 消息处理程序

BOOL Clesson60Dlg::OnInitDialog()
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

void Clesson60Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void Clesson60Dlg::OnPaint()
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
HCURSOR Clesson60Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Clesson60Dlg::OnBnClickedButton1()
{
	// 打开剪贴板
	if (OpenClipboard()) {
		// 从编辑框获取文本
		CString str;
		GetDlgItemText(IDC_EDIT1, str);

		// 清空剪贴板
		EmptyClipboard();

		// 分配内存并锁定
		HANDLE hClip;  // 定义句柄变量，用于存储剪贴板数据的内存块的句柄
		hClip = GlobalAlloc(GMEM_MOVEABLE, str.GetLength() + 1);  // 通过 GlobalAlloc 函数分配可移动内存，长度为文本长度加 1（为字符串结束符 '\0' 留空间）
		
		TCHAR* pBuf;  // 定义字符指针，用于指向分配的内存块
		pBuf = (TCHAR*)GlobalLock(hClip);  // 通过 GlobalLock 函数锁定内存块，返回指向内存块的指针
#pragma warning(disable:4996)
		_tcscpy(pBuf, str);  // 使用 _tcscpy 函数将 CString 对象中的文本复制到分配的内存块中
#pragma warning(default:4996)

		GlobalUnlock(hClip);  // 通过 GlobalUnlock 函数解锁内存块，表示操作完成


		// 将数据设置到剪贴板
		SetClipboardData(CF_TEXT, hClip);

		// 关闭剪贴板
		CloseClipboard();
	}
}

