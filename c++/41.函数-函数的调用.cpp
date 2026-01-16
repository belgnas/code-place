//函数-函数的调用

//功能：使用定义好的函数
//语法：函数名(参数)

#include <iostream>
using namespace std;

//定义加法函数
//定义中的num1，num2称为形式参数，简称形参
int add(int num1,int num2)
{
    int sum = num1 + num2;

    return sum;
}


int main()
{
    int a = 10;
    int b = 20;

    //调用add函数
    //调用时的啊，b称为实际参数，简称实参
    //当调用函数的时候，实参的值会传递给形参 
    int sum = add(a,b);
    cout << "sum = " << sum << endl;

    system("pause");

    return 0;
}