//指针-指针所占用内存空间

//指针也是一种数据类型，这种数据类型在不同的系统下占据不同字节的内存空间
//32位的操作系统：占用4个字节空间(不管是什么数据类型)
//64位的操作系统：占用8个字节空间(不管是什么数据类型)

#include<iostream>
using namespace std;

int main()
{
    int a = 10;

//  int *p;
//  p = &a;
//    或者(上下这两者是等价的)
    int * p = &a;

    cout << "sizeof(p) = " << sizeof(p) << endl;
    cout << "sizeof (int *) = " << sizeof(int *) << endl;
    cout << "sizeof(float *) = " << sizeof(float *) << endl;
    cout << "sizeof(double *) = " << sizeof(double *) << endl;
    cout << "sizeof (char *) = " << sizeof(char *) << endl;


    system("pause");

    return 0;
}