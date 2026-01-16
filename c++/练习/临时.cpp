#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>
using namespace std;

const int N = 710, M = N * N;

int arr[N][N];

int num[M];

int main()
{
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