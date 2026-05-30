//敲桌子游戏
//带7的数字和7的倍数就敲桌子

#include<iostream>
using namespace std;

int main()
{
    for(int i=1;i<=100;i++)
    {
        if(i%7==0||i%10==7||i/10==7)
        {
            cout<<"敲桌子"<<"\n";
        }
        else 
        {
            cout<<i<<"\n";
        }
    }
    

    system("pause");

    return 0;
}