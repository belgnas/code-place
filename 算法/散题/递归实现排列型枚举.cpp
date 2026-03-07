#include <iostream>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <string>
#include <vector>
#include <cstring>
#include <set>
#include <tuple>
#include <bitset>
#include <utility>
#include <queue> // 队列
#include <deque> // 双端队列

using namespace std;

#define IOS ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
#define endl '\n'

const int INF = 0x3f3f3f3f;

void dp(int n, vector<int> &arr)
{
    // 退出条件
    if(arr.size() == n)
    {
        for(int i = 0; i < n; i++)
        {
            cout << arr[i] << " ";
        }
        cout << endl;
        return;
    }

    for(int i = 1; i <= n; i++)
    {
        bool flat = false;
        for(int j = 0; j < arr.size(); j++)
        {
            
            if(i == arr[j])
            {
                flat = true;
                break;
            }
        }
        if(!flat)
        {
            arr.push_back(i);
            dp(n, arr);
            arr.pop_back();
        }
        
    }
}

signed main()
{
    IOS;
    
    int n;
    cin >> n;

    vector<int> arr;

    dp(n, arr);
    
    return 0;
}