//跳转语句-continue语句

//作用：在循环语句中，跳过本次循环中尚未执行的语句，继续执行下一次循环

#include<iostream>
using namespace std;

int main()
{
    for (int i = 1; i <= 100; i++)
    {
        //如果是奇数输出，偶数不输出
        if (i%2==0)
        {
            continue;//可以筛选条件，执行到此就不再向下循环，而是执行下一次循环
            //break会退出循环，但是continue不会
        }
        
        cout<<i<<endl;
    }
       
    
    system("pause");

    return 0;   
}