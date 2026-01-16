//位运算

// 返回n的最后一位1：lowbit(x) = x & -x;


//例题：
//返回一个数字二进制中有多少个1
#include<iostream>
using namespace std;

int lowbit(int x)
{
    return x & -x;
}

int main()
{
    int n; // n组测试数据
    cin >> n;
    while(n--)
    {
        int x;
        cin >> x;

        int res = 0;
        while(x) x -= lowbit(x), res++; // 每次减去x的最后一位，每减一次res（计数器）就加1
    
        cout << res << endl;
    }
    
    return 0;
}

