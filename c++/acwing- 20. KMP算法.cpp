// KMP 算法

// 题目来源：AcWing 831. KMP字符串

// 一、题目描述
// 给定一个模式串 S ，以及一个模板串 P ，所有字符串中只包含大小写英文字母以及阿拉伯数字。
// 模板串 P 在模式串 S 中多次作为子串出现。
// 求出模板串 P 在模式串 S 中所有出现的位置的起始下标。

// 输入格式
// 第一行输入整数 N ，表示字符串 P 的长度。
// 第二行输入字符串 P。
// 第三行输入整数 M ，表示字符串 S 的长度。
// 第四行输入字符串 S。

// 输出格式
// 共一行，输出所有出现位置的起始下标（下标从 0 开始计数），整数之间用空格隔开。

// 数据范围
// 1 ≤ N ≤ 10^5
// 1 ≤ M ≤ 10^6

// 输入样例：
// 3
// aba
// 5
// ababa

// 输出样例：
// 0 2

#include<iostream>
using namespace std;

const int N = 100010;

int n, m;
int ne[N]; // next数组简写
char s[N], p[N];

int main()
{
    cin >> n >> (p + 1) >> m >> (s + 1); // 下标从 1 开始

    // 求 next 的过程
    for(int i = 2, j = 0; i <= n; i++)
    {
        while(j && p[i] != p[j + 1]) j = ne[j];
        if(p[i] == p[j + 1]) j++;
        ne[i] = j;
    }
    
    // KMP 匹配过程
    for(int i = 1, j = 0; i <= m; i++)
    {
        while(j && s[i] != p[j + 1]) j = ne[j];
        if(s[i] == p[j + 1]) j++;
        if(j == n)
        {
            // 匹配成功
            printf("%d ", i - n);
            j = ne[j];
        }
    }
    cout << endl;

    // for(int i = 0 ;i <= 130; i++)
    // {
    //     cout << ne[i] << "   ";
    // }


    return 0;
}