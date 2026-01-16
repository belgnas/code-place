#include<iostream>
#include<algorithm>
using namespace std;

typedef pair<int, int> PII;

int main()
{
    int t;
    cin >> t;
    while(t--)
    {
        int n, m;
        cin >> n >> m;
        int arr[n][m];

        PII sum[n]; // PII.first是sum, PII.second是index

        for(int i = 0; i < n; i++)
        {
            sum[i].first = 0;
            sum[i].second = i;
            for(int j = 0; j < m; j++)
            {
                cin >> arr[i][j];
                sum[i].first += arr[i][j];
            }
        }

        sort(sum, sum + n, greater<PII>()); // 对sum从大到小排序
        for(int i = 0; i < n; i++)
        {
            cout << "喵" << sum[i].first << " " << sum[i].second << endl;
        }

        int answer = 0;
        for(int i = 0; i < n; i++)
        {
            int index = sum[i].second;
            for(int j = 0; j < m; j++)
            {
                for(int k = 0; k < j; k++)
                {
                    answer += arr[index][k]; // 把index行的前j列加起来
                }
            }
        }

        cout << answer << endl;

    }

    return 0;
}