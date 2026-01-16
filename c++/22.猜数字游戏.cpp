//猜数字游戏

#include<iostream>
using namespace std;
//time系统时间头文件包含
#include<ctime>

int main()
{
    //添加随机数种子，利用当前系统时间生成随机数，防止一样
    srand((unsigned int)time(NULL));

    int number=rand()%100+1;//rand()生成随机数
    //原理是先随机一个数，通过100取余数来后再加1来生成1-100的随机数
    cout<<number<<endl;

    int data=0;

    while (1)
    {
        cin>>data;
    if (data>number)
    {
        cout<<"有点大了"<<endl;
    }
    else if (data<number)
    {
        cout<<"有点小了"<<endl;
    }
    else
    {
        cout<<"大小刚刚好"<<endl;
        break;//break可以退出当前循环
    }
    }
    
    
    

    system("pause");

    return 0;   
}