// 6118. 蛋糕游戏

// 知识点：前缀和，贪心，枚举

// 难度：中等（不好想，但是想明白了很好写）

// https://www.acwing.com/problem/content/6121/


#include<iostream>

using namespace std;

typedef long long LL;
const int N = 500010;

int n;
LL s[N];

int main()
{
    int T;
    scanf("%d", &T);
    
    while(T--)
    {
        scanf("%d", &n);
        
        LL a = 1e15; // 这里的a只要大于题目中的N的个数乘于a的最大值，也就是大于 5*1e5 * 1e9，即我们设一个大于它的数：1e15就可以了

        int l = n / 2 + 1;
        
        for(int i = 1; i <= n; i++)
        {
            int x;
            scanf("%d", &x);
            s[i] = s[i - 1] + x;
            if(i >= l) a = min(a, s[i] - s[i - l]);
        }
        
        printf("%lld %lld\n", a, s[n] - a);
        
    }
    
    return 0;
}