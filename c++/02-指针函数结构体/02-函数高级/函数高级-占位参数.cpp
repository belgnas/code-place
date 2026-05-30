//函数高级-占位参数

// C++中函数的形参列表里可以有占位参数，用来做占位，调用函数时必须填补该位置

//语法：返回值类型 函数名(数据类型){}

// ps：在现阶段函数的占位参数存在意义不大，但是后面的课程中会用到该技术

#include<iostream>
using namespace std;

//占位参数
//语法：返回值类型 函数名(数据类型){}
//占位参数 还可以有默认参数
void func(int a, int = 10)
{
    cout << "a = " << a << endl;
    cout << "this is func" << endl;
}

int main()
{

    func(10, 10);
    //这里也可以改成 func(10);
    //  因为定义函数时有定义默认参数

    return 0;
}