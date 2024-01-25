// zijian.cpp: 实现文件
//

#include "pch.h"
#include "MFCDLL.h"
#include "afxdialogex.h"
#include "zijian.h"


// zijian 对话框

IMPLEMENT_DYNAMIC(zijian, CDialogEx)

zijian::zijian(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

zijian::~zijian()
{
}

void zijian::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(zijian, CDialogEx)
END_MESSAGE_MAP()


// zijian 消息处理程序
