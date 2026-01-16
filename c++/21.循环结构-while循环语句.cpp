//循环结构-while循环语句

//！！！小心死循环！！！
//作用：满足循环条件，执行循环语句
//语法：while（循环条件）{循环语句}
//个人理解：只要循环条件为真，那么就执行循环语句

#include<iostream>
using namespace std;

int main()
{
    //在屏幕上打印0~9这10个数字
    int number=0;
    
    while(number<10)
    {
        cout<<number<<endl;
        number++;
    }

    system("pause");

    return 0;
}