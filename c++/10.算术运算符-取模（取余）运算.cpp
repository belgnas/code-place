//算术运算符-取模（取余）运算
//%

//就是求余数

#include<iostream>
using namespace std;

int main()
{
    int a=1;
    int b=2;

    cout<<a%b<<"\n";
    //ps：错误：2个数字相除，除数不可以为0
    //ps：2个小数之间不可以做取模运算（c++的规定）
 
    system("pause");
    return 0;
}