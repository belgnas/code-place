#include<iostream>

using namespace std;

int add(int a, int b)
{
    int num = 0;
    num = a + b;
    
    return 0;
}

int main()
{
    int n1,n2;
    cin >> n1 >> n2;
    cout << add(n1, n2);
    
    return 0;
}