//算术运算符-递增递减(递减和递增同理，故省略)
//++
//--

#include<iostream>
using namespace std;

int main()
{
    //1.前置递增
    int a=10;
    ++a;
    cout<<"a="<<a<<"\n";

    //2.后置递增
    int b=10;
    b++;
    cout<<"b="<<b<<"\n";

    //3.前置递增和后置递增的区别
    //前置递增：先让变量+1，然后进行运算
    int a1=10;
    int b1=++a1*10;//相当于括号括起来
    cout<<"a1="<<a1<<"\n";//这个时候a1的值已经加了1，被改变了
    cout<<"b1="<<b1<<"\n";
    //后置变量：先进行运算，然后让变量+1
    int a2=10;
    int b2=b++*10;//相当于括号括起来
    cout<<"a2="<<a2<<"\n";
    cout<<"b2="<<b2<<"\n";

    system("pause");
    
    return 0;
}