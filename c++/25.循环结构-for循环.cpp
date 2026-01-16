//循环结构-for循环

//作用：满足循环条件，执行循环语句
//语法：for(起始表达式;条件表达式;末尾循环体){循环语句;}
//执行顺序1.起始表达式；2.条件表达式；3.循环语句；4.末尾循环体；
//    就是：1 2 3 4 234 234...

//示例：从数字0打印到数字9
#include<iostream>
using namespace std;

int main()
{
    for(int i=0;i<10;i++)
    {
        cout<<i<<"\n";
    }
/*for循环中括号内语句可以提出来
但是分号不能去掉；
相当于下面这样：

    int i=0；
    for(;;)
    {
        if（i>=10)
        {
            break;
        }
        cout<<i<<"\n";
        i++
    }


*/


    system("pause");

    return 0;
}