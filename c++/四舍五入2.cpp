//利用内置函数round

#include <iostream>
#include <cmath>//必要头文件
using namespace std;

int main() {
    double num = 3.14159;
    double rounded_num = round(num);
    cout << rounded_num << endl;

    double num2 = 3.678;
    double rounded_num2 = round(num2);
    cout << rounded_num2 << endl;

    // 四舍五入到指定小数位数（先放大，在缩小）
    double num3 = 3.14159;
    double multiplier = 100.0;
    double temp = num3 * multiplier;
    double rounded_temp = round(temp);
    double rounded_num3 = rounded_temp / multiplier;
    cout << rounded_num3 << endl;

    return 0;
}

