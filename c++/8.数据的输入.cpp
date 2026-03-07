//数据的输入

//cin>>#

// 当输入输出超过100万量级的时候，为了提升效率，应该尽可能使用scanf和printf

#include<iostream>
using namespace std;

int main()
{
    //1.整型
    int a=0;
    cout<<"请给整型变量a赋值："<<"\n";
    cin>>a;
    cout<<"整型变量a="<<a<<"\n";

    //2.浮点型
    float f=0.1f;
    cout<<"请给浮点型变量f赋值："<<"\n";
    cin>>f;
    cout<<"浮点型变量f="<<f<<"\n";

    //3.字符型
    char ch='b';
    cout<<"请给字符型变量ch赋值："<<"\n";
    cin>>ch;
    cout<<"字符型变量ch="<<ch<<"\n";

    //4.字符串型
    char str[]="12345";
    cout<<"请给字符串str赋值："<<"\n";
    cin>>str;
    cout<<"字符串str="<<str<<"\n";

    //5.布尔类型
    bool flag=false;
    cout<<"当前赋值："<<flag<<"\n"<<"请给布尔类型flag赋值："<<"\n";
    cin>>flag;/*ps：0代表假“0”，除此之外非0的数字都代表真“1”*/
    cout<<"布尔类型变量flag="<<flag<<"\n";

    system("pause");
    return 0;
}