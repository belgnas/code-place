// 6122. 农夫约翰的奶酪块

// 知识点：模拟

// 难度：简单

// https://www.acwing.com/problem/content/6125/


#include<iostream>

using namespace std;

const int N = 1010;

int n, Q;
int xy[N][N], xz[N][N], yz[N][N];

int main()
{
    cin >> n >> Q;
    int res = 0;
    for(int i = 0; i < Q; i++)
    {
        int x, y, z;
        cin >> x >> y >> z;
        xy[x][y] ++;
        xz[x][z] ++;
        yz[y][z] ++;
        if(xy[x][y] >= n) res++;
        if(xz[x][z] >= n) res++;
        if(yz[y][z] >= n) res++;
        
        cout << res << endl;
    }
    
    
    return 0;
}
