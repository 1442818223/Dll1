// pch.h: 这是预编译标头文件。
// 下方列出的文件仅编译一次，提高了将来生成的生成性能。
// 这还将影响 IntelliSense 性能，包括代码完成和许多代码浏览功能。
// 但是，如果此处列出的文件中的任何一个在生成之间有更新，它们全部都将被重新编译。
// 请勿在此处添加要频繁更新的文件，这将使得性能优势无效。

//#ifndef PCH_H
//#define PCH_H
#include<Windows.h>
//// 添加要在此处预编译的标头

//
//
//#endif //PCH_H
  

#ifdef __cplusplus//如果是c++环境
#define EXPORT extern"C" __declspec (dllexport)  //就将extern "C" __declspec (dllexport)重命名为EXPORT
#else
#define EXPORT __declspec (dllexport)   //不是c++环境将__declspec (dllexport)重命名为EXPORT
#endif

EXPORT BOOL CALLBACK EdrCenterTextA(HDC hdc,PRECT prc,PCSTR pString);
EXPORT BOOL CALLBACK EdrCenterTextW(HDC hdc,PRECT prc,PCWSTR pString);

EXPORT DWORD DemoA();
EXPORT DWORD Demow();


#ifdef UNICODE  //如果编译环境是UNICODE
#define EdrCenterText EdrCenterTextW  //就重命名EdrCenterTextW为EdrCenterText
#define Demo          Demow     //一样的道理
#else
#define EdrCenterText EdrCenterTextA
#define Demo          DemoA
#endif
