//循环结构-do...while结构

//！！！小心陷入死循环！！！
//作用：满足循环条件，执行循环语句
//语法：do{循环结构}while(循环条件)
//与while的区别：do...while会先执行一次循环语句，再判断循环条件

#include<iostream>
using namespace std;


int main()
{

    int number=0;

    do
    {
        cout<<number<<endl;
        number++;
    }
    while(number<10);
    
    system("pause");

    return 0;   
}