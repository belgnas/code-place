//赋值运算符

//=、+=、-=、*=、/=、%=
//分别叫做：赋值、加等于、减等于、乘等于、除等于、模等于
//可以直接理解成将运行+、-、*、/、%的结果赋值给原来的数

#include<iostream>
using namespace std;

int main()
{
    int a = 10;
    a = 100;
    cout << "a = "<< a << endl;

    
    a = 10;
    a += 2;//a（新的值）=a（旧的值）+2
    cout << "a = "<< a << endl;

    a = 10;
    a -= 2;
    cout << "a = "<< a << endl;

    a = 10;
    a *= 2;
    cout << "a = "<< a << endl;

    a = 10;
    a /= 2;
    cout << "a = "<< a << endl;

    a = 10;
    a %= 2;
    cout << "a = "<< a << endl;


    system("pause");
    return 0;
}