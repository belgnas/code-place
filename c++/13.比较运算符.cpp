//比较运算符

//作用：用于表达式的比较，并返回一个真值或假值

//==、!=、<、>、<=、>=
//分别叫做：相等于、不等于、小于、大于、小于等于、大于等于

#include<iostream>
using namespace std;

int main()
{
    int a=10;
    int b=20;

    cout<<(a==b)<<endl;//注意要连接一个括号，否则无法确定优先级
    cout<<(a!=b)<<endl;
    cout<<(a<b)<<endl;
    cout<<(a>b)<<endl;
    cout<<(a<=b)<<endl;
    cout<<(a>=b)<<endl;

    system("pause");
    return 0;
}
