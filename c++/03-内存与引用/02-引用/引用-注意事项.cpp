//引用-注意事项

//1.引用必须初始化
//  int &b;
  /*这样是错误的*/

//2.引用在初始化后，不可以改变
//别名不可以更改，b为a的别名后，不可以更改为c的别名

#include<iostream>
using namespace std;

int main()
{
    int a = 10;


    // 引用必须要初始化
    //int &b;
    /* 不可以这样 ↑ */

    int &b = a;

    //引用在初始化后，不可以改变
    //int c = 20;
    //int &b = c;

    int c;
    c = b;// 赋值操作，而不是更改引用

    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "c = " << c << endl;

    return 0;
}
