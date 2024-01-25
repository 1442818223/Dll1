// MFCDLL.cpp: 定义 DLL 的初始化例程。
//

#include "pch.h"
#include "framework.h"
#include "MFCDLL.h"

#include"zijian.h"                                      //先点资源添加窗口,再在窗口中点右键添加窗口类
                                                        //在窗口上绑定类时才出现的zijian.h和zijian.cpp
                                                        //1,包含自己的资源头文件

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO:  如果此 DLL 相对于 MFC DLL 是动态链接的，
//		则从此 DLL 导出的任何调入
//		MFC 的函数必须将 AFX_MANAGE_STATE 宏添加到
//		该函数的最前面。
//
//		例如: 
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// 此处为普通函数体
//		}
//
//		此宏先于任何 MFC 调用
//		出现在每个函数中十分重要。  这意味着
//		它必须作为以下项中的第一个语句:
//		出现，甚至先于所有对象变量声明，
//		这是因为它们的构造函数可能生成 MFC
//		DLL 调用。
//
//		有关其他详细信息，
//		请参阅 MFC 技术说明 33 和 58。
//

// CMFCDLLApp

BEGIN_MESSAGE_MAP(CMFCDLLApp, CWinApp)
END_MESSAGE_MAP()


zijian* pZJ{};                                               //2,资源类起名为zijian
 
// CMFCDLLApp 构造

CMFCDLLApp::CMFCDLLApp()
{
	// TODO:  在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的 CMFCDLLApp 对象

CMFCDLLApp theApp;



DWORD WINAPI ShowWindow(LPVOID lparam) {

	pZJ->DoModal();//调用一个对话框的模态对话框框架。  //模态会阻塞
	delete pZJ;
	
	return 0;
}
// CMFCDLLApp 初始化
BOOL CMFCDLLApp::InitInstance()
{
	CWinApp::InitInstance();

	pZJ = new zijian;
	//m_pMainWnd指向主窗口对象的指针                                 //3,new一个对象挂载在this->m_pMainWnd上
	this->m_pMainWnd = pZJ;


	::CreateThread(NULL,0, (LPTHREAD_START_ROUTINE)ShowWindow,0,0,NULL);//创建线程执行,避免阻塞

	

	return TRUE;
}
                                                                          //4,添加类,封装好类
                                                                          //5,窗口上添加按钮,创建对象,写调用逻辑