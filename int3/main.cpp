#include <iostream>
#include <windows.h>
//#pragma comment(linker ,"/subsystem:\"windows\"/entry:\"mainCRTStartup\"")

//�������ַ����鶨������ƴ����,Ȼ��ͨ���궨��һ����,������ο�ִ��Ȩ��,��ȥ����


//ע��Ҫ��  ����->c/c++ ->�Ż� ->����   x86release�汾����
//ԭ����Ǹ�ret�ķ��ص�ַ

#pragma optimize(" ",off)   //" "�ǵ�Ҫ�ӿո�

//void MsgBox() {
//	int ary[2];
//	ary[4] = ary[3];//��retָ��Ķ����Ƹ�ֵ��4��λ
//	ary[3] = (int)MessageBoxA;//ջ���濴����ַ�ͻᵱ����������,��������ջ����ǰ��ѹ�����Ĳ�������
//	ary[5] = 0;
//	ary[6] = (int)"NO_CALL";
//	ary[7] = (int)"NO_CALL";
//	ary[8] = MB_OK;//ret
//}


//������:���ú����������ռλջ�ռ�
void MsgBox(int a,int b, int c ,int d,int e) {//��������ǰ���ٿռ�
	int ary[2];
	ary[4] = ary[3]+3;//�Թ����غ��add esp,14��3�ֽ�(����ָ���ռ3�ֽ�)
	ary[3] = (int)MessageBoxA;//ջ���濴����ַ�ͻᵱ����������,��������ջ����ǰ��ѹ�����Ĳ�������
	ary[5] = 0;
	ary[6] = (int)"NO_CALL";
	ary[7] = (int)"NO_CALL";
	ary[8] = MB_OK;//ret
}
  


//ƽջ����һ:��ǰ�üĴ���ռλջ�ռ�
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
	//MessageBoxA(0, "��ϲ��, ���Ѿ�", "��", MB_OK);//
}


#pragma optimize(" ",on)

