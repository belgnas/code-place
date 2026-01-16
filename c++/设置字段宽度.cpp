//设置最小字段长度

//注意头文件：#include<iomanip>
//setw(“数字”)<<“这里填内容”

//ps：如果设置的最小字段长度小于输入的字段长度，那么字符仍会正常输出字符本身的长度。
//意思就是：我设置4个字段长度，但是我输入了5个长度的字段，于是正常输出5个长度，不会被设置的最小字段长度影响

#include <iostream>
#include <iomanip>//头文件

using namespace std;

int main() 
{
    int numbers[] = {1, 12, 123, 1234, 12345};
    for (int num : numbers) 
    {
        cout << right << setw(4) << num << " ";//使用案例
    }
    cout << endl;

    for (int num : numbers) 
    {
        cout << left << setw(4) << num << " ";
    }
    cout << endl;

    return 0;
}