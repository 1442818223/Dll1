
// lesson57Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "lesson57.h"
#include "lesson57Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



//方法一:
#define WM_COMM WM_USER+100                                 //1,先定义消息编号
//方法二:
const UINT wn_nRegMsg = RegisterWindowMessage(_T("reg_data"));  //用RegisterWindowMessage函数注册一个消息编号
//函数用于注册一个全局唯一的消息字符串，并返回该消息的消息值（UINT）。




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


// Clesson57Dlg 对话框



Clesson57Dlg::Clesson57Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LESSON57_DIALOG, pParent)
	, m_strUserMsg(_T(""))
	, m_strRegMsg(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Clesson57Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_strUserMsg);
	DDX_Text(pDX, IDC_EDIT2, m_strRegMsg);
}

BEGIN_MESSAGE_MAP(Clesson57Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &Clesson57Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &Clesson57Dlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// Clesson57Dlg 消息处理程序

BOOL Clesson57Dlg::OnInitDialog()
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

void Clesson57Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void Clesson57Dlg::OnPaint()
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
HCURSOR Clesson57Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}







//方法一:
void Clesson57Dlg::OnBnClickedButton1()                                     //2,
{
	//1,先定义消息编号

/*
UpdateData(TRUE)：将控件的当前值更新到关联的成员变量中。这通常用于从界面更新数据模型。
UpdateData(FALSE)：将关联的成员变量的值更新到对应的控件上。这通常用于将数据模型的值更新到界面上。
*/
		UpdateData();  //一定要及时更新编辑框绑定的变量    如果省略参数，MFC 将默认为 UpdateData(TRUE)，即从控件更新到变量。


	//2,得到窗口句柄
	CWnd* pWnd = CWnd::FindWindow(NULL, _T("接收端")); 
	if (pWnd == NULL)
	{
		AfxMessageBox(TEXT("Unableto find 接收端."));
		return;
	}

	UINT uMsg;
/*
_ttoi 是一个宏，根据项目配置的字符集（Unicode 或者多字节字符集）选择对应的函数，
它的作用是将字符串转换为整数。如果 _UNICODE 被定义，它会使用 _wtoi，否则使用 atoi。
*/
	
	uMsg = _ttoi(m_strUserMsg);//3,将编辑框绑定的变量m_strUserMsg拿到转换为UINT
	pWnd->SendMessage(WM_COMM, NULL, (LPARAM)uMsg);
}
//方法二:
void Clesson57Dlg::OnBnClickedButton2()
{
	UpdateData();  

	CWnd* pWnd = CWnd::FindWindow(NULL, _T("接收端"));
	if (pWnd == NULL)
	{
		AfxMessageBox(TEXT("Unableto find 接收端."));
		return;
	}

	UINT uMsg;
	uMsg = _ttoi(m_strRegMsg);
	
	pWnd->SendMessage(wn_nRegMsg, NULL, (LPARAM)uMsg);
}
