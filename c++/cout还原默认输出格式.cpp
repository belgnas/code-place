#include<iostream>
#include<iomanip>
using namespace std;
int main()
{
    double a = 10;
    double b = 3;
    cout << int(a / b) << endl;
    cout << fixed << setprecision(3) << a / int(b) << endl;
    cout << fixed << setprecision(8) << a / int(b) << endl;
    
    //还原默认输出格式
    cout.unsetf(ios::fixed);
    cout.precision(6);
    
    cout << scientific << a / int(b) << endl;
    
    return 0;
}