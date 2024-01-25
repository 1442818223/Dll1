
// lesson32Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "lesson32.h"
#include "lesson32Dlg.h"
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


// Clesson32Dlg 对话框



Clesson32Dlg::Clesson32Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LESSON32_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Clesson32Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(Clesson32Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &Clesson32Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &Clesson32Dlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// Clesson32Dlg 消息处理程序

BOOL Clesson32Dlg::OnInitDialog()
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

void Clesson32Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void Clesson32Dlg::OnPaint()
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
HCURSOR Clesson32Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// 该函数用于在指定的设备上下文（hdc）上进行图形输出
VOID GdiOut(HDC hdc) {
	// 定义画笔和画刷的句柄
	HPEN hpen, hpenOld;
	HBRUSH hbrush, hbrushOld;

	// 定义颜色值（这里设置了一个黑色的画笔和紫色的画刷）
	BYTE bRed = 0;
	BYTE bGreen = 0;
	BYTE bBlue = 0;
	COLORREF cPen = RGB(bRed, bGreen, bBlue); // 创建颜色值
	COLORREF cBrush = RGB(233, 0, 255);

	// 创建画笔和画刷对象
	hpen = CreatePen(PS_SOLID, 10, cPen); // 创建一个黑色的实线画笔，粗细为 10 个逻辑单位
	hbrush = CreateSolidBrush(cBrush);    // 创建一个紫色的实心画刷

	// 保存并选择画笔和画刷
	hpenOld = (HPEN)SelectObject(hdc, hpen);    // 选择新的画笔，注意:hpenOld *****并保存之前的画笔句柄*****
	hbrushOld = (HBRUSH)SelectObject(hdc, hbrush); // 选择新的画刷，并保存之前的画刷句柄

	// 在设备上下文上绘制直线和矩形
	::LineTo(hdc, 500, 500); // 从当前位置绘制一条到指定坐标的直线
	::Rectangle(hdc, 200, 200, 500, 500); // 绘制一个矩形

	// 恢复原先的画笔和画刷，并删除创建的对象
	SelectObject(hdc, hpenOld);   // 恢复之前的画笔
	DeleteObject(hpen);           // 删除创建的画笔
	SelectObject(hdc, hbrushOld); // 恢复之前的画刷
	DeleteObject(hbrush);         // 删除创建的画刷
}


void Clesson32Dlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码

	HWND hwnd = GetSafeHwnd();// 获取当前对话框的窗口句柄
	HDC hdc = ::GetDC(hwnd); // 获取当前对话框的设备上下文
	GdiOut(hdc);
	// 注意：在使用完设备上下文后，应该及时释放
	::ReleaseDC(hwnd, hdc);
}


void Clesson32Dlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	HDC hdc = ::GetDC(NULL);//NUL表示得到桌面的HDC
	GdiOut(hdc);
	::ReleaseDC(NULL, hdc);

}
