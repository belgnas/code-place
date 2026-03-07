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
    int a, b, c;
    cin >> a >> b >> c;
    vector<int> x(n), y(n);
    for(int i = 0; i < n; i++)
        cin >> x[i] >> y[i];
    int d;
    cin >> d;
    int ans = 0;
    for(int i = 0; i < n; i++)
    {
        if(x[i] + y[i] >= c)
        {
            continue;
        }
        
        x[i] += d;
        if(x[i] > a) x[i] = a;

        if(x[i] + y[i] >= c)
        {
            ans ++;
        }
    }

    cout << ans << endl;

    
    
    return 0;
}