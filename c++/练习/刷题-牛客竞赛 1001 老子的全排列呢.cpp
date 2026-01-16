// 牛客竞赛 1001 老子的全排列呢

// 知识点：dfs、枚举

// 难度：简单

// https://ac.nowcoder.com/acm/contest/23156/1001

#include<iostream>
using namespace std;

const int N = 10;

int n;
int path[N];
bool st[N];

void dfs(int u)
{
    if(u == n)
    {
        for(int i = 0; i < n; i++) printf("%d ", path[i]);
        puts("");
        return;
    }

    for(int i = 1; i <= n; i++)
    {
        if(!st[i])
        {
            path[u] = i;
            st[i] = true;
            
            dfs(u + 1);
            
            path[u] = 0;
            st[i] = false;
        }
    }
}


int main()
{
    n = 8;

    dfs(0);


    return 0;
}