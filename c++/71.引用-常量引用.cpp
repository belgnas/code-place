//引用-常量引用

//作用：常量引用主要用来修饰形参，防止误操作

//在航叔形参列表中，可以加入 const 修饰形参，防止形参改变实参

#include<iostream>

using namespace std;

//打印数据函数
void showValue(const int &val)
{
    //val = 1000; // const修饰了val，防止修改
    cout << "val = " << val << endl;
}

int main()
{
    //常量引用
    // 用来修饰形参，防止误操作


    //加上 const 之后，编译器将代码修改成了 
    // int temp = 10;
    // const int & ref = temp;

    
    const int & ref = 10;//引用必须引用一块合法的内存空间
    //ref = 20;  //const修饰了ref，不可以修改
    cout << ref << endl;

    int a = 10;
    showValue(a);

    return 0;
}