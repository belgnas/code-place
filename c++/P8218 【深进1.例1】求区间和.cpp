// 前缀和(一维)

// P8218 【深进1.例1】求区间和

#include<iostream>
#include<vector>
using namespace std;
int main()
{
    int n;
    cin >> n;
    vector<int> arr (n + 1, 0);
    vector<int> sum (n + 1, 0);
    for(int i = 1; i <= n; i++)
    {
        cin >> arr[i];
        sum[i] = sum[i - 1] + arr[i];
    }
    // for(int i = 0; i < n; i++)
    // {
    //     cout << arr[i] << " ";
    // }
    // cout << endl;
    // for(int i = 0; i < n; i++)
    // {
    //     cout << sum[i] << " ";
    // }
    // cout << endl;

    int m;
    cin >> m;
    int l, r;
    while(m--)
    {
        cin >> l >> r;
        cout << sum[r] - sum[l - 1] << endl; 
    }

    

    return 0;
}