// 6123. 哞叫时间

// 知识点：枚举

// 难度：简单

// https://www.acwing.com/problem/content/6126/

#include<iostream>
#include<cstring>
#include<algorithm>

using namespace std;

const int N = 20010, M = 26;

int n, f;
char s[N];
int cnt[M][M];
bool st[M][M]; // st表示每个子串有没有可能大于 f 次

void updata(int l, int r, int v)
{
    l = max(l, 0), r = min(r, n - 1);
    
    for(int i = l; i + 2 <= r; i++)
    {
        int a = s[i], b = s[i + 1], c = s[i + 2];
        if(a != b && b == c)
        {
            cnt[a][b] += v;
            if(cnt[a][b] >= f) st[a][b] = true;
        }
    }
}

int main()
{
    scanf("%d%d", &n, &f);
    scanf("%s", s); // 读入字符串
    
    for(int i = 0; i < n; i++) s[i] -= 'a';
    
    updata(0, n - 1, 1);
    
    for(int i = 0; i < n; i++)
    {
        char t = s[i];
        updata(i - 2, i + 2, -1);
        for(int j = 0; j < M; j++)
            if(j != t)
            {
                s[i] = j;
                updata(i - 2, i + 2, 1);
                updata(i - 2, i + 2, -1);
            }
        s[i] = t;
        updata(i - 2, i + 2, 1);
    }
    
    int res = 0;
    for(int i = 0; i < M; i++)
        for(int j = 0; j < M; j++)
            if(st[i][j]) res++;
    
    printf("%d\n", res);
    
    for(int i = 0; i < M; i++)
        for(int j = 0; j < M; j++)
            if(st[i][j]) printf("%c%c%c\n", i + 'a', j + 'a', j + 'a');
    
    return 0;
}