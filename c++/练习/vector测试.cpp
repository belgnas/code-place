#include<bits/stdc++.h>
using namespace std;

#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);

int test01(vector<int> &arr)
{
    int len = arr.size();
    if(len < 2)
    {
        return 0;
    }

    int min_buy = arr[0];
    int ans = 0;

    for(int i = 1; i < len; i++)
    {
        min_buy = min(min_buy, arr[i]);
        int money = arr[i] - min_buy;
        if(money > ans) ans = money;
    }

    return ans;
}

int main()
{
    IOS;

    int n;
    cin >> n;

    vector<int> arr(n);
    for(int i = 0; i < n; i++)
        cin >> arr[i];

    cout << test01(arr) << endl;

    return 0;
}