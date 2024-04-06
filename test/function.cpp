// function
#include <functional>
#include <iostream>
#include <memory>
// 【伪代码】std::function<returnType(argType, argType，...)> func;

// 【常规情况】std::function<int(int, int)> func;

// 它与 std::function 不同的是，function 是模板类，bind 是模板函数，
// 而 bind 返回的可调用对象可以直接给 function 进行包装并保存。


// int Add(int a, int b) {
//     return a + b;
// }

// /* --- 普通函数 --- */ 
// 【伪代码】std::bind(&funcName, std::placeholders::_1, ...);

// 【常规情况】std::bind(&Add, std::placeholders::_1, std::placeholders::_2);

// /* --- 类成员函数 --- */
// 【伪代码】std::bind(&className::funcName, classPtr, std::placeholders::_1, ...);

// 【常规情况】std::bind(&BrainToolBox::Add, brain, std::placeholders::_1, std::placeholders::_2);


class BrainToolBox
{
public:
    int Add(int a, int b) { return a + b; };
};

int main()
{
    // int a = 4;
    // int b = 6;

    // std::shared_ptr<BrainToolBox> brain = std::make_shared<BrainToolBox>();
    // std::function<int(int, int)> addFunc = std::bind(&BrainToolBox::Add, brain, std::placeholders::_1, std::placeholders::_2);
    
    // int c = addFunc(a, b);
    // std::cout << "c Value: " << c << std::endl;


    // int x = 1; int y = 2;
    // auto plus = [=] (int a, int b) -> int { return x + y + a + b; };
    // int c = plus(1, 2);
    // std::cout << c << "\n";

    // 值捕获时，编译器会把捕获到的值作为类的成员变量，并且变量是以值的方式传递的。
    // 需要注意的时，如果所有的参数都是值捕获的方式，那么生成的operator()函数是const函数的，
    // 是无法修改捕获的值的，哪怕这个修改不会改变lambda表达式外部的变量，
    // 如果想要在函数内修改捕获的值，需要加上关键字 mutable。向下面这样的形式。
    // https://zhuanlan.zhihu.com/p/384314474
    // int x = 1; int y = 2;
    // auto plus = [=] (int a, int b) mutable -> int { x++; return x + y + a + b; };
    // int c = plus(1, 2);
    // std::cout << c << " " << x <<"\n"; // 7 1

    int x = 1; int y = 2;
    auto plus = [&] (int a, int b) -> int { x++; return x + y + a + b;};
    int c = plus(1, 2);
    std::cout << c << " " << x <<"\n";
    return EXIT_SUCCESS;
}
