//pow(第一个数,第二个数)
//上面这是3次方根

//语法：头文件：#include<cmath>
//pow(第一个数,第二个数)--------翻译为第一个数的第二个数幂次方（ps开根号第2个数字就是分数）


#include<iostream>
#include<cmath>//头文件

using namespace std;
int main()
{
    int n = 0;
    cin >> n;
    double a;
    a = pow(n, 1.0/3.0);
    cout << a << endl;
    
    return 0;
}