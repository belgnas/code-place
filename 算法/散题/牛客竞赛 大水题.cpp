// 牛客竞赛 大水题

// 知识点：递归

// https://ac.nowcoder.com/acm/contest/21763/A

#include<iostream>
using namespace std;

void test(int num)
{
    if(num < 10)
    {
        cout << num << endl;
    }
    else
    {
        int num2 = 0;
        while(num > 0)
        {
            num2 += (num % 10);
//             cout << "已执行！" << endl;
            num /= 10;
        }
//         cout << "喵" << num2 << endl;
        test(num2);
    }
}

int main()
{
    
    int n;
    cin >> n;
    
    test(n);
    
    return 0;
}