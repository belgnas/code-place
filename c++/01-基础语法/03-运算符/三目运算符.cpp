//三目运算符

//表达式1  ?  表达式2  ：  表达式3

//解释：
//如果表达式1为真，执行表达式2，并返回表达式2的结果
//如果表达式1为假，执行表达式3，并返回表达式3的结果


#include<iostream>
using namespace std;

int main()
{
    //创建3个变量，例如：a b c
    //将a和b作比较，将变量大的值赋值给变量c
    int a=10;
    int b=20;
    int c=0;

    c=(a>b ? a : b);

    cout<<"c="<<c<<"\n";

    //在c++中三目运算符返回的是变量，可以继续赋值
    (a<b ? a : b)=100;//a和b作比较，因为a<b为真，所以返回a的值，随后a被赋值为100

    cout<<"a="<<a<<"\n";
    cout<<"b="<<b<<"\n";

    
    system("pause");

    return 0;   
}