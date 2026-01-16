// 变量

#include <iostream>
using namespace std;

int main()
{
    int a = 1; // ps：变量不要重复申明
    // 变量创建的语法：数据类型+变量名=变量初始值
    /*代表整数的数据类型（简称为整型）：(int最常用)
    short（短整型，2字节）（范围：-2^15~2^15-1）
    int（整型，4字节）（范围：-2^31~2^31-1)
    long（长整型，Windous为4字节，Lunix为4字节（32位）或8字节（64位））（范围：-2^31~2^31-1)
    long long（长长整型，4字节）。（范围：-2^33~2^33-1)*/

    // 无符号整数类型:
    // size_t、unsigned short、unsigned int、unsigned long、unsigned long long
    // 个人理解：（去掉数字前的负号“-”，使其能表示整数的范围增大）
    // 通常用于表示对象的大小、数组的索引等

    cout << "a=" << a << "\n";

    // ps：数据类型占用的内存大小是可以用关键词sizeof算出来的
    // sizeof语法结构为：sizeof(数据类型或变量)

    cout << "int占用的内存大小为：" << sizeof(int) << "\n";

    system("pause");

    return 0;
}