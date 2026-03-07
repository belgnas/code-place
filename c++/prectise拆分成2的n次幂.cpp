//如果这个正整数可以拆分成若干个不同的 2 的正整数次幂，从大到小输出这个拆分中的每一个数，相邻两个数之间用一个空格隔开。如果不存在这样的拆分，输出-1。

#include <iostream>
using namespace std;

int main() 
{ 
    int num;
    cin >> num;

    // 如果输入的数是奇数，直接输出 -1
    if (num % 2!= 0) 
    {
        cout << "-1" << endl;
        return 0;
    }

    bool found = false;
    int power = 1 << 30;

    while (num > 0) {
        if (num >= power) {
            num -= power;
            cout << power << " ";
            found = true;
        }
        power >>= 1;
    }

    if (!found) 
    {
        cout << "-1";
    }
    cout << endl;

    return 0;
}