
// lesson27Dlg.cpp: 实现文件

#include "pch.h"
#include "framework.h"
#include "lesson27.h"
#include "lesson27Dlg.h"
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


// Clesson27Dlg 对话框



Clesson27Dlg::Clesson27Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LESSON27_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Clesson27Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(Clesson27Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &Clesson27Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &Clesson27Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &Clesson27Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &Clesson27Dlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// Clesson27Dlg 消息处理程序

BOOL Clesson27Dlg::OnInitDialog()
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

void Clesson27Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void Clesson27Dlg::OnPaint()
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
HCURSOR Clesson27Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Clesson27Dlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码

	long lRet;
	HKEY hKey;
	TCHAR tchData[64];
	DWORD dwSize;
	       //1,打开
	lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE,//注册表主目录
		_T("HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0"),//注册表子目录路径
		0,
		KEY_QUERY_VALUE, //读取属性
		&hKey);
	dwSize = sizeof(tchData);
	if (lRet == ERROR_SUCCESS) {
               //2,读取
		/*RegQueryValueEx 是Windows API函数之一，
		用于从注册表中检索特定键的值。
		该函数允许你读取注册表中指定键的数值、字符串、二进制数据等类型的数据。*/
		lRet = RegQueryValueEx(hKey,
			_T("ProcessorNameString"),//要读的值的名字
			NULL,
			NULL,
			(LPBYTE)tchData, //out
			&dwSize);        //in
		
		if (lRet == ERROR_SUCCESS) {
			SetDlgItemText(IDC_STATIC, tchData);
		}
		else {
			AfxMessageBox(_T("RegQueryValueEx failed."));
		}

	}
	else {
		AfxMessageBox(_T("RegOpenKeyEx failed."));
	}
	RegCloseKey(hKey);


}


void Clesson27Dlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	HKEY hKey;                         
	RegCreateKey(HKEY_LOCAL_MACHINE, _T("SOFTWARE\\MyAppTest"), &hKey);//创建一个表  64位下使用
	
/*
LONG RegSetValue(
  HKEY   hKey,           // 注册表项的句柄
  LPCTSTR lpSubKey,      // 要设置的键值的名称 //NULL为默认
  DWORD  dwType,         // 要设置的键值的数据类型
  LPCTSTR lpData,        // 包含键值数据的缓冲区
  DWORD  cbData          // 缓冲区的大小（字节数）
);
*/
	RegSetValue(hKey, NULL, REG_SZ,_T("LieBao"), 6);//注册写值  RegSetValue只能写默认名的值
	
/*	
  LONG RegSetValueEx(
  HKEY       hKey,          // 注册表项的句柄
  LPCTSTR    lpValueName,   // 要设置的键值的名称
  DWORD      Reserved,      // 保留，必须为0
  DWORD      dwType,        // 要设置的键值的数据类型
  const BYTE *lpData,       // 包含键值数据的缓冲区
  DWORD      cbData         // 缓冲区的大小（字节数）
 );
*/
	DWORD dwAge = 30;
	RegSetValueEx(hKey,_T("age"),0,REG_DWORD, (CONST BYTE*) &dwAge, 4);//再在表项中添加参数用RegSetValueEx

	RegCloseKey(hKey); 
}

void Clesson27Dlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	LONG lValue;                                               //第一次out地址为NULL,只为计算长度
	RegQueryValue(HKEY_LOCAL_MACHINE, _T("SOFTWARE\\MyAppTest"), NULL, &lValue); //RegQueryValue只能读默认名的值

	TCHAR* pBuf = new TCHAR[lValue];
	RegQueryValue(HKEY_LOCAL_MACHINE, _T("SOFTWARE\\MyAppTest"), pBuf, &lValue);
	AfxMessageBox(pBuf);

}


void Clesson27Dlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码

	HKEY hKey;
	RegOpenKey(HKEY_LOCAL_MACHINE,_T("SOFTWARE\\MyAppTest"), &hKey);
	
/*    
    // RegQueryValueEx 函数用于检索注册表中指定键的值
	LONG RegQueryValueEx(
  HKEY    hKey,          // 注册表项的句柄
  LPCTSTR lpValueName,   // 要检索的键值的名称
  LPDWORD lpReserved,    // 保留，必须为NULL
  LPDWORD lpType,        // 接收键值类型的变量，可以为NULL
  LPBYTE  lpData,        // 接收键值数据的缓冲区
  LPDWORD lpcbData       // 输入为缓冲区大小，输出为实际读取的字节数
  );
 */
	DWORD dwType;
	DWORD dwValue;
	DWORD dwAge;
	RegQueryValueEx(hKey, _T("age"), 0, &dwType, (LPBYTE)&dwAge, &dwValue);
	CString str;
	str.Format(_T("age = %d"),dwAge); //
	AfxMessageBox(str);

}
