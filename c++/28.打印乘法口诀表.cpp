//打印乘法口诀表

#include<iostream>
using namespace std;

int main()
{
    cout<<"       ";
     for (int k = 1; k <= 9; k++)
     {
        cout<<"第"<<k<<"列  ";
     }
     cout<<endl;
     

     for (int i = 1; i <= 9; i++)
     {
        cout<<"第"<<i<<"行  ";
        for (int j = 1; j <= i; j++)
        {
            cout<<j<<"×"<<i<<"="<<j*1<<"  ";
        }
        cout<<endl;
        
     }     
    

    system("pause");

    return 0;   
}