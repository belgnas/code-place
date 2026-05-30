// 4.堆区：由程序员分配和释放，若程序员不释放，程结束时由操作系统回收

// 在C++中主要利用 new 在堆区开辟内存

#include <iostream>
using namespace std;

int *func()
{
    // 利用new关键字  可以将数据开辟到堆区
    // 指针 本质也是局部变量，放在栈上，指针保存的数据放在堆区
    int *p = new int(10);
    return p;
}

int main()
{
    // 在堆区开辟数据
    int *p = func();

    cout << *p << end; // 回顾知识点：* p：对p解引用

    return 0;
}