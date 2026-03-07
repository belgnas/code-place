#include <iostream>
#include <string>
using namespace std;

string dectobin(int n) 
{
    if (n == 0) return "0";
    // 如果输入的整数 n 为 0，直接返回字符串 "0"，因为 0 的二进制就是 0。

    string binary = "";
    // 创建一个空字符串 binary，用于存储转换后的二进制结果。

    while (n > 0) {
    // 当 n 大于 0 时进入循环，不断将 n 转换为二进制。

        binary = to_string(n % 2) + binary;
        // 将 n 对 2 取余得到当前二进制位（0 或 1），转换为字符串后添加到 binary 的开头。
        // 这样做是因为二进制的低位在后面，而我们是从低位开始生成二进制的，
        // 所以每次新生成的位要添加到前面。

        n /= 2;
        // 将 n 除以 2，为下一次循环处理更高位做准备。

    }
    return binary;
    // 返回最终生成的二进制字符串。
}

int main() {
    int num = 0;
    // 定义一个整数 num 并初始化为 0，这里可以根据需要修改输入的整数。

    cin >> num;

    string binary = dectobin(num);
    // 调用 dectobin 函数将 num 转换为二进制字符串，并存储在 binary 中。

    cout << "十进制 " << num << " 的二进制为（以字符串的形式表示）：" << binary << endl;
    // 输出结果，显示输入的十进制数及其对应的二进制表示。

    return 0;
    // 表示程序正常结束，返回值为 0。
}