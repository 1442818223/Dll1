
// lesson23Dlg.h: 头文件
//

#pragma once


// Clesson23Dlg 对话框
class Clesson23Dlg : public CDialogEx
{
// 构造
public:
	Clesson23Dlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LESSON23_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数

	BOOL LoadFile(CString strFileName);//

	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CString m_strText; //点到可拖拽面板 选择文本编辑框 点右键点添加变量
};
