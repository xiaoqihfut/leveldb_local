1、左值右值
2、const 引用
3、衍生的各种构造函数，拷贝构造，拷贝复制，带const和不带const的函数
4、std::forward std::function std::bind
5、各种xx_cast 转换函数
6、constexpr
7、匿名命名空间的作用: 主要是对于当前文件可见，其他文件不可见
8、operator() 可调用对象等
9、std::for_each
10、复习shared_ptr和weak_ptr
11、std::move


12、（x）表示x的引用
a) 如果 表达式 的值类别是亡值，则 decltype 产生 T&&；
b) 如果 表达式 的值类别是左值，则 decltype 产生 T&；
c) 如果 表达式 的值类别是纯右值，则 decltype 产生 T。
<!-- https://zh.cppreference.com/w/cpp/language/decltype -->