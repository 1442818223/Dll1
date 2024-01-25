#include <iostream>
#include <windows.h>
//#pragma comment(linker ,"/subsystem:\"windows\"/entry:\"mainCRTStartup\"")

//可以用字符数组定义二进制代码段,然后通过宏定义一个段,给这个段可执行权限,再去调用


//注意要点  设置->c/c++ ->优化 ->禁用   x86release版本调试
//原理就是改ret的返回地址

#pragma optimize(" ",off)   //" "记得要加空格

//void MsgBox() {
//	int ary[2];
//	ary[4] = ary[3];//将ret指令的二进制赋值给4号位
//	ary[3] = (int)MessageBoxA;//栈里面看见地址就会当做函数调用,参数就走栈里面前面压进来的参数传递
//	ary[5] = 0;
//	ary[6] = (int)"NO_CALL";
//	ary[7] = (int)"NO_CALL";
//	ary[8] = MB_OK;//ret
//}


//方法二:利用函数自身参数占位栈空间
void MsgBox(int a,int b, int c ,int d,int e) {//参数当提前开辟空间
	int ary[2];
	ary[4] = ary[3]+3;//略过返回后的add esp,14的3字节(这条指令本身占3字节)
	ary[3] = (int)MessageBoxA;//栈里面看见地址就会当做函数调用,参数就走栈里面前面压进来的参数传递
	ary[5] = 0;
	ary[6] = (int)"NO_CALL";
	ary[7] = (int)"NO_CALL";
	ary[8] = MB_OK;//ret
}
  


//平栈方法一:提前用寄存器占位栈空间
//void fzMsgBox() {
//	_asm push esp
//	_asm push esp
//	_asm push esp
//	_asm push esp
//	_asm push esp
//	/*_asm push ebp
//	_asm push ebp
//	_asm push ebp
//	_asm push ebp*/
//
//	MsgBox();
//
//}


int main()
{
	
	MsgBox(0,0,0,0,0);
	/*fzMsgBox();*/
	//MessageBoxA(0, "恭喜你, 你已经", "你", MB_OK);//
}


#pragma optimize(" ",on)

