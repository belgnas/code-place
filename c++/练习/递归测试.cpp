#include<iostream>
using namespace std;

int test(int n)
{
    int num = 0;
    if(n==1)
    {
        num = 0;
    }
    else if(n==2)
    {
        num = 1;
    }
    else if(n==3)
    {
        num = 1;
    }
    else
    {
        num = test(n-3) + 2*test(n-2) + test(n-1);
    }

    return num;
}

int main()
{
    int a;
    cin >> a;
    cout << test(a) << endl;
    
    return 0;
}