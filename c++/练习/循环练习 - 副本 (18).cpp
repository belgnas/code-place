#include<iostream>
#include<iomanip>
using namespace std;

int main()
{
    int a,b,c;
    cin >> a >> b >> c;
    int num1 = a*(1+a)/2;
    int num2 = b*(b+1)*(2*b+1)/6;
    double num3 = 0.0;
    for(int i=1; i<=c; i++)
    {
        num3 += 1/i;
    }
    cout << fixed << setprecision(2) << num1+num2+num3;
    
    return 0;
}