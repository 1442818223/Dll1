#include <iostream>

// ���庯������
using MyFunctionType = void (*)(int);

// ʵ��һ���������붨��ĺ���������ƥ��
void MyFunctionImplementation(int value) {
    std::cout << "MyFunctionImplementation: " << value << std::endl;
}

int main() {
    // ����һ������ָ�����������Ϊ MyFunctionType
    MyFunctionType myFunctionPointer = &MyFunctionImplementation;

    // ʹ�ú���ָ����ú���
    myFunctionPointer(42);

    return 0;
}
