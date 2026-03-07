#include <iostream>
#include <ctime>

using namespace std;

int main()
{
    // 添加随机数种子，利用当前系统时间生成随机数，防止一样
    srand((unsigned int)time(NULL));

    int number = rand() % 100 + 1; // rand()生成随机数
    // 原理是先随机一个数，通过100取余数来后再加1来生成1-100的随机数
    cout << number << endl;

    return 0;
}