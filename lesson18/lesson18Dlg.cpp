
// lesson18Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "lesson18.h"
#include "lesson18Dlg.h"
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


// Clesson18Dlg 对话框



Clesson18Dlg::Clesson18Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LESSON18_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Clesson18Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(Clesson18Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &Clesson18Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON6, &Clesson18Dlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &Clesson18Dlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &Clesson18Dlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &Clesson18Dlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON10, &Clesson18Dlg::OnBnClickedButton10)
END_MESSAGE_MAP()


// Clesson18Dlg 消息处理程序

BOOL Clesson18Dlg::OnInitDialog()
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

void Clesson18Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void Clesson18Dlg::OnPaint()
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
HCURSOR Clesson18Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Clesson18Dlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	LPTSTR szDirPath = TEXT("c:\\dog");  //CreateDirectory不指定目录就在当前目录下创建文件夹
	if (!CreateDirectory(szDirPath, NULL)) {  //参数二安全属性，一般传入 NULL
		MessageBox(TEXT("在指定目录下创建新目录失败。"));
		return;
	}
	SetDlgItemText(IDC_STATIC, TEXT("在指定目录下创建新目录成功。"));

}


void Clesson18Dlg::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
		LPTSTR szDirPath = TEXT("cat");  //CreateDirectory不指定目录就在当前目录下创建文件夹
	if (!CreateDirectory(szDirPath, NULL)) {
		MessageBox(TEXT("在当前目录下创建新目录失败。"));
		return;
	}
	SetDlgItemText(IDC_STATIC, TEXT("在当前目录下创建新目录成功。"));
}


void Clesson18Dlg::OnBnClickedButton7()
{
	// TODO: 在此添加控件通知处理程序代码

	TCHAR szCurrentDirectory[MAX_PATH];
	DWORD dwCurDirPathLen;  //GetCurrentDirectory获取当前所在目录
	dwCurDirPathLen = GetCurrentDirectory(MAX_PATH, szCurrentDirectory);
	if (dwCurDirPathLen == 0)
	{
		MessageBox(TEXT("获取当前目录失败。"));
		return;
	}
		SetDlgItemText(IDC_STATIC, szCurrentDirectory);

}


void Clesson18Dlg::OnBnClickedButton8()
{
	// TODO: 在此添加控件通知处理程序代码
	    //设置当前目录为c盘下  然后不管是创建文件删除文件,就相当于CMD切换到c盘下是一样的
	if(!SetCurrentDirectory(TEXT("C:\\"))){
		MessageBox(TEXT("设置当前目录失败。"));
		return;
	}
		SetDlgItemText(IDC_STATIC,TEXT("当前目录被设置为C:\\"));

}


void Clesson18Dlg::OnBnClickedButton9()
{
	// TODO: 在此添加控件通知处理程序代码

	TCHAR szModulePath[MAX_PATH];
 
/*
  DWORD GetModuleFileName(
  HMODULE hModule,    // 模块句柄，一般为 NULL 表示获取当前模块
  LPTSTR  lpFilename, // 用于存储文件名的缓冲区
  DWORD   nSize        // 缓冲区的大小
  );
 */
	if (!GetModuleFileName(NULL, szModulePath, MAX_PATH)) {
		MessageBox(TEXT("获取主模块路径失败。"));
		return;
	}
		SetDlgItemText(IDC_STATIC,szModulePath); 
}


void Clesson18Dlg::OnBnClickedButton10()
{
	// TODO: 在此添加控件通知处理程序代码

	HMODULE hKernel32;
	TCHAR szModulePath[MAX_PATH];

	hKernel32 = LoadLibrary(TEXT("kernel32.dll")); //LoadLibrary  加载模块

	if (!GetModuleFileName(hKernel32, szModulePath,MAX_PATH)) {
		MessageBox(TEXT("获取DLL模块路径失败。"));
		return;
	}
	SetDlgItemText(IDC_STATIC, szModulePath);
}
