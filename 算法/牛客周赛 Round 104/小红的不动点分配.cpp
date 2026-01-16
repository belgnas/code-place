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
    
    int n;
    cin >> n;
    vector<int> a(n * 2);
    vector<int> num(2e5 + 10, 0);
    int ans = 0;
    for(int i = 0; i < 2 * n; i++)
    {
        cin >> a[i];
        if(a[i] <= n)
        {
            if(num[a[i]] < 2)
            {
                num[a[i]]++;
                ans ++;
            }
            else
            {
                num[a[i]] = 2;
            }
        }
        
    }

    cout << ans << endl;


    
    return 0;
}