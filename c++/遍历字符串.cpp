// 遍历字符串

#include <iostream>
#include <string>

using namespace std;

int main()
{
    // 标准for循环

    string str = "Hello";
    for (size_t i = 0; i < str.length(); i++)
    // ps：size_t是一种无符号整数类型，通常用于表示对象的大小、数组的索引等。
    // ps：unsigned int也是一个道理
    // 个人理解:（去掉数字前的负号“-”，使其能表示整数的范围增大）
    {
        cout << str[i] << " ";
    }
    cout << endl;

    return 0;
}