// 刷题-codeforces 2069B B. Set of Strangers

// 知识点：模拟、贪心、思维、矩阵

// 难度：简单

// https://codeforces.com/contest/2069/problem/B

#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>
using namespace std;

#define IOS ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

const int N = 710, M = N * N;

int arr[N][N];

int num[M];

int main()
{
    IOS;

    int t;
    cin >> t;
    while(t--)
    {
        int n, m;
        cin >> n >> m;

        memset(arr, 0, sizeof arr);
        memset(num, 0, sizeof num);

        bool flat = true;
        for(int i = 1; i <= n; i++)
        {
            for(int j = 1; j <= m; j++)
            {
                cin >> arr[i][j];
                num[arr[i][j]] = 1;

                flat = true;
            }
        }

        for(int i = 1; i <= n; i++)
        {
            for(int j = 1; j <= m; j++)
            {
                if(arr[i][j] == arr[i + 1][j] || arr[i][j] == arr[i - 1][j] || arr[i][j] == arr[i][j + 1] || arr[i][j] == arr[i][j - 1])
                {
                    num[arr[i][j]] = 2;

                    flat = false;
                }
            }
        }

        int ans = 0;

        for(int i = 0; i < M; i++)
        {
            ans += num[i];
            // cout << num[i] << " ";
        }
        // cout << endl;

        if(flat)
        {
            ans -= 1;
        }
        else
        {
            ans -= 2;
        }

        if(ans < 0) ans = 0;

        cout << ans << endl;
        

    }

    return 0;
}