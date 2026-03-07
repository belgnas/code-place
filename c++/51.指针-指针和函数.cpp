//指针-指针和函数

//作用：利用指针作函数的值，可以修改实参的值

#include<iostream>
using namespace std;

void swap01(int a, int b)
{
    int temp = a;
    a = b;
    b = temp;

    cout << "swap01 a = " << a << endl;
    cout << "swap01 b = " << b << endl;
}

void swap02(int * p1, int * p2)
{
    int temp = * p1;
    * p1 = * p2;
    * p2 = temp;
}

int main()
{
    //1.值传递:
    //值传递时，如果形参发生改变，并不会影响实参
    int a = 10;
    int b = 20;
    swap01(a,b);

    cout << "a = " << a << endl;
    cout << "b = " << b << endl;  

    //2.地址传递:
    //可以修改实参
    //个人理解：
    //其实是将a和b的地址分别赋给*p1和*p2，然后通过运行自己定义的函数将*p1和*p2置换，本质上是主函数中的a和b的内存地址发生了交换

    swap02(&a,&b);


    cout << "a = " << a << endl;
    cout << "b = " << b << endl;    


    return 0;   
}