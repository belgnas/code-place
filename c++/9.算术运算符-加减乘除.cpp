//算术运算符-加减乘除
//+-*/

#include<iostream>
using namespace std;

int main()
{
    int a=4;
    int b=3;

    cout<<a+b<<"\n";
    cout<<a-b<<"\n";
    cout<<a*b<<"\n";
    cout<<a/b<<"\n";//2个整数相除，结果依然是整数，因为小数部分被去除了
    //ps:错误：2个数字相除，除数不能为0

    double c=0.4;
    double d=0.3;

    cout<<c+d<<"\n";
    cout<<c-d<<"\n";
    cout<<c*d<<"\n";
    cout<<c/d<<"\n";

    system("pause");
    return 0;
}