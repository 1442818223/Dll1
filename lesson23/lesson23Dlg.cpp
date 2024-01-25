
// lesson23Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "lesson23.h"
#include "lesson23Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Clesson23Dlg 对话框



Clesson23Dlg::Clesson23Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LESSON23_DIALOG, pParent)
	, m_strText(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Clesson23Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_strText);
}

BEGIN_MESSAGE_MAP(Clesson23Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &Clesson23Dlg::OnBnClickedOk)
END_MESSAGE_MAP()


// Clesson23Dlg 消息处理程序

BOOL Clesson23Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码



	 LoadFile(TEXT("book.txt"));  //初始化就加载
	 UpdateData(FALSE); //跟新数据


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void Clesson23Dlg::OnPaint()
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
HCURSOR Clesson23Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Clesson23Dlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}



//BOOL LoadFile(CString strFileName) ;的实现
BOOL Clesson23Dlg::LoadFile(CString strFileName) {
	/*
内存映射文件是一种将文件内容映射到进程地址空间的机制，
使得应用程序能够直接读取或写入磁盘上的文件，而无需显式的文件 I/O 操作。
在内存映射文件的情境下，文件的内容会被映射到一段虚拟内存区域，使得应用程序可以像访问内存一样访问文件数据。

内存映射文件
第1步:创建文件对象
第2步:创建文件映射对象
第3步:将文件的数据映射到进程的地址空间
第4步:从进程的地址空间撤消对文件数据的映射
第5步:关闭文件映射对象
第6步:关闭文件对象
*/

	HANDLE hFile ,hMapping;
	void* basepointer;

	if ((hFile = CreateFile(strFileName, GENERIC_READ, FILE_SHARE_READ, 0,
		OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, 0)) == INVALID_HANDLE_VALUE) 
	{	               //指定顺序读取
		AfxMessageBox(TEXT("Could not open file."));
		return FALSE;
	}

/*
  HANDLE CreateFileMapping(
  HANDLE                hFile,           // 文件句柄，用于指定要映射的文件
  LPSECURITY_ATTRIBUTES lpAttributes,    // 安全属性，通常为 NULL
  DWORD                 flProtect,       // 内存保护标志，指定对映射对象的访问方式
  DWORD                 dwMaximumSizeHigh,// 文件映射对象的大小（高32位）
  DWORD                 dwMaximumSizeLow, // 文件映射对象的大小（低32位）
  LPCTSTR               lpName           // 映射对象的名称，可以为 NULL //多进程间使用的话是需要的
  );
*/                                                           //0表示从头开始
	if (!(hMapping = CreateFileMapping(hFile, 0, PAGE_READONLY, 0, 0, NULL)))
	{
		AfxMessageBox(TEXT("Mapping failed."));
		
		CloseHandle(hFile);
		return FALSE;
	}

/*
  LPVOID MapViewOfFile(
  HANDLE hFileMappingObject,  // 文件映射对象的句柄
  DWORD  dwDesiredAccess,     // 映射视图的访问方式
  DWORD  dwFileOffsetHigh,    // 文件偏移的高32位
  DWORD  dwFileOffsetLow,     // 文件偏移的低32位
  SIZE_T dwNumberOfBytesToMap // 映射的字节数（0 表示映射整个文件）
  );
*/                                                            //0表示从头开始
	if (!(basepointer = MapViewOfFile(hMapping, FILE_MAP_READ, 0, 0, 0)))
	{
		
		AfxMessageBox(TEXT("View failed."));

		CloseHandle(hMapping);
		CloseHandle(hFile);
		return FALSE;
	}

	m_strText = (LPTSTR)basepointer;
	
	UnmapViewOfFile(basepointer);
	CloseHandle(hMapping);
	CloseHandle(hFile);



}

