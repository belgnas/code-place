//引用-引用做函数参数

//作用：函数传参时，可以利用引用的技术让形参修饰实参

//优点：可以简化指针修改实参

#include<iostream>
using namespace std;

//交换函数

//1.值传递
void mySwap01(int a, int b)
{
    int temp = a;
    a = b;
    b = temp;

    cout << "mySwap01 a = " << a << endl;
    cout << "mySwap01 b = " << b << endl;
}

//2.地址传递
void mySwap02(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;

    cout << "mySwap02 a = " << *a << endl;
    cout << "mySwap02 b = " << *b << endl;
}

//3.引用传递
void mySwap03(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;

    cout << "mySwap03 a = " << a << endl;
    cout << "mySwap03 b = " << b << endl;
}


int main()
{
    int a = 10;
    int b = 20;

    cout << "交换前:" << endl;
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;

    cout << "交换后:" << endl;

    //值传递：形参不会修饰实参
    mySwap01(a, b);

    cout << "a = " << a << endl;
    cout << "b = " << b << endl;

    //地址传递：形参会修饰实参
    mySwap02(&a, &b);

    cout << "a = " << a << endl;
    cout << "b = " << b << endl;

    //引用传递：形参会修饰实参
    mySwap03(a, b);

    cout << "a = " << a << endl;
    cout << "b = " << b << endl;


    return 0;   
}