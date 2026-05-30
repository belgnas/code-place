#include<iostream>
using namespace std;
int main()
{
    double a,money;
    char ar;
    cin >> a >> ar;
    if(a<=1000)
    {
        money = 8;
    }
    else
    {
        if(double((a-1000)/500)==int((a-1000)/500))
        {
            money = 8 + int((a-1000)/500)*4;
        }
        else
        {
            money = 8 + (int((a-1000)/500)+1)*4;
        }
    }
   if(ar=='y')
    {
        money = money + 5;
    }
    else if(ar=='n')
    {
        money = money;
    }
    cout << money;
    
    return 0;
}