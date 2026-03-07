// 保留小数

// 头文件：
// #include<iomanip>

// 代码：
// cout<<fixed<<setprecision(填需要保留多少位小数)<<要保留多少位+小数的数字<<endl;

#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    double a = 0;
    cin >> a;
    cout << fixed << setprecision(2) << a << endl;

    system("pause");

    return 0;
}