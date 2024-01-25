#include<stdio.h>
#include<windows.h>
#include<iostream>
using namespace std;



//__try __except是windows 系统独有的异常处理模型，称为SEH
int main() {


	__try {//SEH可以嵌套

		__try {
			char* str = NULL;
			str[0] = 'a';
		}
		__except (0) {//1:处理异常	0:不处理异常交给异常链的下一个去处理   -1:继续执行
			printf("触发异常了! \n");
		}

	}
	__except (1) {
		printf("触发异常了2! \n");
	}



	printf("hello\n");
	system("pause");
	return 0;
}