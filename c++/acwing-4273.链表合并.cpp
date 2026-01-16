// acwing
// 4273. 链表合并

// 题目来源：https://www.acwing.com/problem/content/4276/


#include<iostream>
#include<cstring>
#include<vector>
#include<algorithm>

#define x first
#define y second

using namespace std;

typedef pair<int, int> PII;

const int N = 100010;

int n;
int h1, h2;
int v[N], ne[N];

int main()
{
    scanf("%d%d%d", &h1, &h2, &n);
    while(n--)
    {
        int addr, val, next;
        scanf("%d%d%d", &addr, &val, &next);
        v[addr] = val;
        ne[addr] = next;
    }
    
    vector<PII> a, b;
    for(int i = h1; i != -1; i = ne[i])
    {
        a.push_back({i, v[i]});
    }
    for(int i = h2; i != -1; i = ne[i])
    {
        b.push_back({i, v[i]});
    }
    
    if(a.size() < b.size())
    {
        swap(a, b);
    }
    
    vector<PII> c;
    for(int i = 0, j = b.size() - 1; i < static_cast<int>(a.size()); i += 2, j --)
    {
        c.push_back(a[i]);
        if(i + 1 < static_cast<int>(a.size()))
        {
            c.push_back(a[i + 1]);
        }
        if(j >= 0)
        {
            c.push_back(b[j]);
        }
        
    }
    
    for(int i = 0; i < static_cast<int>(c.size()); i ++)
    {
        printf("%05d %d ", c[i].x, c[i].y);
        if(i + 1 < static_cast<int>(c.size()))
        {
            printf("%05d\n", c[i + 1].x);
        }
        else
        {
            puts("-1");
        }
    }
    
    
    return 0;
}