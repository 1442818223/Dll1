
// lesson56Dlg.h: 头文件
//

#pragma once


// Clesson56Dlg 对话框
class Clesson56Dlg : public CDialogEx
{
// 构造
public:
	Clesson56Dlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LESSON56_DIALOG };
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

	//方法一:
	afx_msg LRESULT OnUserReceiveMsg(WPARAM wParam, LPARAM lParam);  //定义接收到消息的处理函数
	//方法二:
	afx_msg LRESULT OnRegReceiveMsg(WPARAM wParam, LPARAM lParam);  //定义接收到消息的处理函数


	DECLARE_MESSAGE_MAP()
public:
	CString m_strUserMsd;
	CString m_strRegMsg;
};
