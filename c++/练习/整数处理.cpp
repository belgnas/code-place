#include<iostream>
using namespace std;

int main()
{
    // 从标准输入读取一个整数 n
    int n;
    cin >> n;

    // 循环变量 i，初始值为 1，用于遍历从 1 到 n 的整数
    int i = 1;
    while(i <= n)
    {
        // Four 标记当前整数是否包含数字 4，初始值为 false
        bool Four = false;

        // 如果当前整数不是 4 的倍数
        if(i % 4!= 0)
        {
            // c 用于存储当前正在检查的整数 i 的副本
            int c = i;
            while(c)
            {
                // 检查当前整数 c 的最后一位数字是否为 4
                if(c % 10 == 4)
                {
                    // 如果是，将 Four 标记为 true，表示当前整数包含数字 4
                    Four = true;
                }
                // 将 c 除以 10，去掉最后一位数字，继续检查下一位
                c = c / 10;
            }
            // 如果当前整数不包含数字 4
            if(!Four)
            {
                // 输出当前整数
                cout << i << endl;
            }
        }
        // 循环变量 i 递增，继续检查下一个整数
        i++;
    }    
    return 0;
}
