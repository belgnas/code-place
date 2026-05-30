// P1002 [NOIP2002 普及组] 过河卒

#include<iostream>
#include<vector>
using namespace std;


int main()
{
    //为什么要低下头
    //为什么要放弃
    long long n,m;
    cin >> n >> m;

    vector<vector<long long>> arr(n+1, vector<long long>(m+1, 1));// n行 m列 初始值为-1

    long long h_n, h_m;
    cin >> h_n >> h_m;
    arr[h_n][h_m] = 0;
    if(h_n + 2 <= n && h_m - 1 >= 0) arr[h_n + 2][h_m - 1] = 0;
    if(h_n + 2 <= n && h_m + 1 <= m) arr[h_n + 2][h_m + 1] = 0;
    if(h_n + 1 <= n && h_m + 2 <= m) arr[h_n + 1][h_m + 2] = 0;
    if(h_n - 1 >= 0 && h_m + 2 <= m) arr[h_n - 1][h_m + 2] = 0;
    if(h_n - 2 >= 0 && h_m + 1 <= m) arr[h_n - 2][h_m + 1] = 0;
    if(h_n - 2 >= 0 && h_m - 1 >= 0) arr[h_n - 2][h_m - 1] = 0;
    if(h_n - 1 >= 0 && h_m - 2 >= 0) arr[h_n - 1][h_m - 2] = 0;
    if(h_n + 1 <= n && h_m - 2 >= 0) arr[h_n + 1][h_m - 2] = 0;
    
    for(long long i = 0; i <= n; i++)
    {
        for(long long j = 0; j <= m; j++)
        {
            if(i == 0 && j == 0)
            {
                continue;
            }
            if(arr[i][j] == 0)
            {
                continue;
            }
            if(i == 0 && j != 0)
            {
                arr[i][j] = arr[i][j-1];
            }
            else if(i != 0 && j == 0)
            {
                arr[i][j] = arr[i-1][j];
            }
            else
            {
                arr[i][j] = arr[i-1][j] + arr[i][j-1];
            }
        }
        
    }




    // for(long long i = 0; i <= n; i++)
    // {
    //     for(long long j = 0; j <= m; j++)
    //     {
    //         cout << arr[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    cout << arr[n][m] << endl;


    return 0;
}