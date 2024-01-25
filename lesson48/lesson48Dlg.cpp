
// lesson48Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "lesson48.h"
#include "lesson48Dlg.h"
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


// Clesson48Dlg 对话框



Clesson48Dlg::Clesson48Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LESSON48_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Clesson48Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(Clesson48Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &Clesson48Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &Clesson48Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &Clesson48Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON5, &Clesson48Dlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON4, &Clesson48Dlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON6, &Clesson48Dlg::OnBnClickedButton6)
END_MESSAGE_MAP()


// Clesson48Dlg 消息处理程序

BOOL Clesson48Dlg::OnInitDialog()
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

void Clesson48Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void Clesson48Dlg::OnPaint()
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
HCURSOR Clesson48Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Clesson48Dlg::OnBnClickedButton1()
{

	/*          WINDOWS的API创建子进程
	BOOL CreateProcess(
	  LPCWSTR               lpApplicationName,//可执行文件的名称。
	  LPWSTR                lpCommandLine,//命令行参数。
	  LPSECURITY_ATTRIBUTES lpProcessAttributes,//用于指定新进程和新线程的安全性属性。通常为 NULL。
	  LPSECURITY_ATTRIBUTES lpThreadAttributes,//用于指定新进程和新线程的安全性属性。通常为 NULL。
	  BOOL                  bInheritHandles,//指定新进程是否继承调用进程的句柄。
	  DWORD                 dwCreationFlags,//指定创建进程的标志，例如创建一个新控制台窗口、挂起进程等。
	  LPVOID                lpEnvironment,//指定新进程的环境块。如果为 NULL，则使用调用进程的环境。
	  LPCWSTR               lpCurrentDirectory,//指定新进程的当前工作目录。
	  LPSTARTUPINFO         lpStartupInfo,//一个 STARTUPINFO 结构，包含有关新进程的一些属性，如窗口标题、标准输入输出等。
	  LPPROCESS_INFORMATION lpProcessInformation//一个 PROCESS_INFORMATION 结构，用于接收新进程的句柄等信息。
	);
	*/

	STARTUPINFO si;  //TARTUPINFO 结构，包含有关新进程的一些属性，如窗口标题、标准输入输出等。
	PROCESS_INFORMATION pi;//PROCESS_INFORMATION 结构，用于接收新进程的句柄等信息。

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);

	ZeroMemory(&pi, sizeof(pi));

	if (!CreateProcess(TEXT("C:\\Program Files\\WindowsApps\\Microsoft.WindowsCalculator_11.2307.4.0_x64__8wekyb3d8bbwe\\CalculatorApp.exe"),
		NULL,
		NULL,
		NULL,
		false,
		0,
		NULL,
		NULL,
		&si,
		&pi
	))//函数返回非零值表示成功，零表示失败。
	{
		CString s;
		s.Format(TEXT("创建进程失败:%d"), GetLastError());
		MessageBox(s);
		return;
	}



}


STARTUPINFO si;  //TARTUPINFO 结构，包含有关新进程的一些属性，如窗口标题、标准输入输出等。
PROCESS_INFORMATION pi;//PROCESS_INFORMATION 结构，用于接收新进程的句柄等信息。
void Clesson48Dlg::OnBnClickedButton2()
{
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);

	ZeroMemory(&pi, sizeof(pi));

	if (!CreateProcess(TEXT("D:\\VS_PROJECT\\Dll1\\x64\\Debug\\lesson49.exe"),
		TEXT(" -a apple -b big -c cat"),  //命令行参数前一定要加一个空格
		NULL,
		NULL,
		false,
		0,
		NULL,
		NULL,
		&si,
		&pi
	))//函数返回非零值表示成功，零表示失败。
	{
		CString s;
		s.Format(TEXT("创建进程失败:%d"), GetLastError());
		MessageBox(s);
		return;
	}
}


void Clesson48Dlg::OnBnClickedButton3()
{
	TerminateProcess(pi.hProcess, 0); //通过句柄结束进程

}


void Clesson48Dlg::OnBnClickedButton5()
{
	CString s;
	s.Format(TEXT("父进程PID:%d"), GetCurrentProcessId()); // GetCurrentProcessId()得到自身PID
	MessageBox(s);
}


void Clesson48Dlg::OnBnClickedButton4()
{
	CString s;
	s.Format(TEXT("自己建的进程PID: %d"), pi.dwProcessId); // 通过PROCESS_INFORMATION 结构得到自己建的进程PID
	MessageBox(s);
}


void Clesson48Dlg::OnBnClickedButton6()
{

	STARTUPINFO si;  //TARTUPINFO 结构，包含有关新进程的一些属性，如窗口标题、标准输入输出等。
	PROCESS_INFORMATION pi;//PROCESS_INFORMATION 结构，用于接收新进程的句柄等信息。

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);

	ZeroMemory(&pi, sizeof(pi));

	if (!CreateProcess(TEXT("C:\\Program Files\\WindowsApps\\Microsoft.WindowsNotepad_11.2310.13.0_x64__8wekyb3d8bbwe\\Notepad\\Notepad.exe"),
		TEXT(" C:\\Users\\a0916\\Desktop\\book.txt"), //命令行参数,***(一定要带空格)
		NULL,
		NULL,
		false,
		0,
		NULL,
		NULL,
		&si,
		&pi
	))//函数返回非零值表示成功，零表示失败。
	{
		CString s;
		s.Format(TEXT("创建进程失败:%d"), GetLastError());
		MessageBox(s);
		return;
	}


}
