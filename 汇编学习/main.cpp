#include<stdio.h>
#include<windows.h>
#include<iostream>
using namespace std;



//__try __except��windows ϵͳ���е��쳣����ģ�ͣ���ΪSEH
int main() {


	__try {//SEH����Ƕ��

		__try {
			char* str = NULL;
			str[0] = 'a';
		}
		__except (0) {//1:�����쳣	0:�������쳣�����쳣������һ��ȥ����   -1:����ִ��
			printf("�����쳣��! \n");
		}

	}
	__except (1) {
		printf("�����쳣��2! \n");
	}



	printf("hello\n");
	system("pause");
	return 0;
}