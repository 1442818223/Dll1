#include <iostream>

// 定义函数类型
using MyFunctionType = void (*)(int);

// 实现一个函数，与定义的函数类型相匹配
void MyFunctionImplementation(int value) {
    std::cout << "MyFunctionImplementation: " << value << std::endl;
}

int main() {
    // 声明一个函数指针变量，类型为 MyFunctionType
    MyFunctionType myFunctionPointer = &MyFunctionImplementation;

    // 使用函数指针调用函数
    myFunctionPointer(42);

    return 0;
}
