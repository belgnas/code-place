//四舍五入

#include<iostream>
using namespace std;

int main()
{
    double a=0;
    double b=0;

    cin>>a;

    //四舍五入（对小数部分）

    if (a>=0)
    {
        a=(a-int(a)>=0.5?int(a)+1:int(a));

    }
    else
    {
        a=-a-int(-a)>=0.5?-(int(-a)+1):-int(-a);
    }
    

    cout<<a<<endl;
    
    system("pause");

    return 0;   
}