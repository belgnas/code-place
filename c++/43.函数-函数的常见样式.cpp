//函数-函数的常见样式

//常见的函数样式有4种(参：函数输入/返：函数输出)
//1.无参无返
//2.有参无返
//3.无参有返
//4.有参有返

#include<iostream>
using namespace std;

//1.无参无返
void test01()//无参
{
    cout << "这是第一个测试函数" << endl;
}

//2.有参无返
void test02(int a)//有参
{
    cout << "这是第二个测试函数" << endl;
    cout << "a=" << a << endl;
}

//3.无参有返
int test03()//无参
{
    cout << "这是第三个测试函数" << endl;
    return 1000;
}

//4.有参有返  
int test04(int a)//无参
{
    cout << "这是第四个测试函数" << endl;
    return ++a;
}

 
int main()
{

    //1.无参无返函数调用
    //个人理解：就是把这个函数抄一遍
    test01();

    //2.无参无返函数调用
    test02(100);

    //3.无参有返函数调用
    int num1 = test03();
    cout << "num1 = " << num1 << endl;

    //4.有参有反函数调用
    int num2 = test04(10000);
    cout << "num2 = " << num2 << endl;



    system("pause");

    return 0;   
}