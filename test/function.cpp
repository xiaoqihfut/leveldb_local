// function
#include <functional>

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
    int a = 4;
    int b = 6;

    std::shared_ptr<BrainToolBox> brain = std::make_shared<BrainToolBox>();
    std::function<int(int, int)> addFunc = std::bind(&BrainToolBox::Add, brain, std::placeholders::_1, std::placeholders::_2);
    
    int c = addFunc(a, b);
    std::cout << "c Value: " << c << std::endl;

    return EXIT_SUCCESS;
}
