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

signed main()
{
    IOS;
    
    int n, k;
    cin >> n >> k;
    if(n == k + 1)
    {
        cout << "-1" << endl;
    }
    else
    {
        vector<int> arr (n + 1);
        for(int i = 1; i <= k; i++)
        {
            arr[i] = i;
        }
        
        if(k != n)
        {
            arr[k + 1] = n;
            for(int i = k + 2; i <= n; i++)
            {
                arr[i] = i - 1;
            }
        }

        for(int i = 1; i <= n; i++)
        {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
    
    return 0;
}