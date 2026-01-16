#include<iostream>
using namespace std;

int Fibonacci(int n)
{
    int a = 1;
    int b = 1;
    if(n==1)
    {
        return 1;
    }
    if(n==2)
    {
        return 1;
    }
    int space = a + b;
    for(int k=2; k<n; k++)
    {
        space = a + b;
        a = b;
        b = space;
    }
    return b;
}

int main()
{
    int T;
    int arr[T];
    for(int i=0; i<T; i++)
    {
        cin >> arr[i];
    }
    for(int j=0; j<T; j++)
    {
        cout << Fibonacci(arr[j]) <<endl;
        
    }
    
    system("pause");

    return 0;   
}