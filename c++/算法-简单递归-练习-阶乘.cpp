//阶乘

#include<iostream>
using namespace std;

int jiecheng(int a)
{
    int numble = 0;
    if(a==1)
    {
        numble = 1;
    }
    else
    {
        numble = jiecheng(a-1)*a;
    }
    
    return numble;
}

int main()
{
    int n;
    cin >> n;
    cout << jiecheng(n) << endl;   

    return 0;
}