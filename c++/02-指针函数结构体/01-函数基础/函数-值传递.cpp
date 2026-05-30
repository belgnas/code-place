//函数-值传递

//解释：函数调用时实参将数值传入给形参
//值传递时，如果形参发生改变，并不会影响实参

#include<iostream>
using namespace std;

//定义一个函数，实现2个数字进行交换函数

//如果函数不需要返回值，那么声明的时候可以写void

void swap(int &num1,int &num2)
{
    cout << "交换前：" << endl;
    cout << "num1 = " << num1 << endl;
    cout << "num2 = " << num2 << endl;

    int temp = num1;
    num1 = num2;
    num2 = temp;

    cout << "交换后：" << endl;
    cout << "num1 = " << num1 << endl;
    cout << "num2 = " << num2 << endl;

    //返回值不需要时，可以不写return
}

int main()
{
    int a = 10;
    int b = 20;
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;

    swap(a,b);
    //值传递时，如果形参发生改变，并不会影响实参
    //个人理解：
    //其实是将a和b的值分别赋给num1和num2，然后通过运行自己定义的函数将num1和num2置换，最终在自己新增的函数中打印调换顺序后的num1和num2，本质上和主函数中的a和b没有直接影响

    cout << "a = " << a << endl;
    cout << "b = " << b << endl;

    
    system("pause");

    return 0;   
}