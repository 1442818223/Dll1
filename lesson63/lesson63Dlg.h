
// lesson63Dlg.h: 头文件
//

#pragma once


// Clesson63Dlg 对话框
class Clesson63Dlg : public CDialogEx
{
// 构造
public:
	Clesson63Dlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LESSON63_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;


	HANDLE m_hMapObject;                       //1,
	LPTSTR m_pszMapView;




	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString m_strText;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
