
// lesson64Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "lesson64.h"
#include "lesson64Dlg.h"
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


// Clesson64Dlg 对话框



Clesson64Dlg::Clesson64Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LESSON64_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Clesson64Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(Clesson64Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &Clesson64Dlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// Clesson64Dlg 消息处理程序

BOOL Clesson64Dlg::OnInitDialog()
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

void Clesson64Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void Clesson64Dlg::OnPaint()
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
HCURSOR Clesson64Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}







void Clesson64Dlg::OnBnClickedButton1()
{
	// 声明用于读取和写入的管道句柄
	HANDLE hPWrite, hPRead;

	// 设置安全属性，使得管道句柄可以被继承
	SECURITY_ATTRIBUTES sa = { 0 };
	sa.nLength = sizeof(sa);
	sa.bInheritHandle = TRUE;
	sa.lpSecurityDescriptor = NULL;

	BOOL bCreate;

/*
BOOL CreatePipe(
  PHANDLE               hReadPipe,      // 读取管道的句柄
  PHANDLE               hWritePipe,     // 写入管道的句柄
  LPSECURITY_ATTRIBUTES lpPipeAttributes, // 安全属性，用于控制管道的访问权限
  DWORD                 nSize           // 缓冲区大小，以字节为单位
);
*/
	// 创建管道
	bCreate = CreatePipe(&hPRead, &hPWrite, &sa, 0);
	if (!bCreate)
	{
		MessageBox(_T("创建管道失败!"));
		return;
	}

	// 存储创建后的进程的信息结构体
	PROCESS_INFORMATION pi = { 0 };
	// 用于启动新进程的信息结构体
	STARTUPINFO si = { 0 };
	si.cb = sizeof(si);
	// 设置标准输入输出和错误句柄为管道的写入端
	si.hStdInput = GetStdHandle(STD_INPUT_HANDLE);//设置子进程的输入为标准输入设备
	si.hStdOutput = si.hStdError = hPWrite;//设置管道写端句柄为标准输出和错误输出************************
	si.wShowWindow = SW_HIDE; //隐藏新进程
	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
	//STARTF_USESHOWWINDOW：指定 wShowWindow 字段包含有效数据。
	//STARTF_USESTDHANDLES：指定 hStdInput、hStdOutput 和 hStdError 字段包含有效数据。

	// 获取用户输入的命令
	TCHAR szCmd[MAX_PATH * 2] = { 0 };
	GetDlgItemText(IDC_EDIT1, szCmd, MAX_PATH * 2);

	// 创建新进程           //参数一:可执行文件路径,如果为 NULL，则使用 lpCommandLine。  参数二:命令行参数。
	bCreate = CreateProcess(NULL, szCmd, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi);
	// 关闭不需要的进程句柄
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);

	if (!bCreate)
	{
		CloseHandle(hPWrite);
		CloseHandle(hPRead);
		MessageBox(_T("创建进程失败!"));
	}
	else
	{
		CString str;
		// 关闭写入端，因为已经不再需要向新进程写入数据
		CloseHandle(hPWrite);

		TCHAR szBuff[4096];
		DWORD dwRead;

		// 读取新进程的输出
		while (TRUE)
		{
			memset(szBuff, 0, sizeof(szBuff));
			if (!ReadFile(hPRead, szBuff, 4096, &dwRead, NULL))
				break;

			str += szBuff;
			// 将读取的内容显示在界面上
			SetDlgItemText(IDC_EDIT2, str);
		}

		// 关闭读取端
		CloseHandle(hPRead);
	}
}

