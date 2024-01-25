
// lesson57Dlg.h: 头文件
//

#pragma once


// Clesson57Dlg 对话框
class Clesson57Dlg : public CDialogEx
{
// 构造
public:
	Clesson57Dlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LESSON57_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString m_strUserMsg;
	CString m_strRegMsg;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
};
