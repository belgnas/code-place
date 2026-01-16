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
    // mex = 0 情况
    int t;
    cin >> t;
    while(t--)
    {
        int n;
        cin >> n;
        vector<int> a(n);
        for(int i = 0; i < n; i++) cin >> a[i];
        sort(a.begin(), a.end());
        int num = a[n - 1];
        for(int i = 0; i < n; i++)
        {
            if(a[i] == -1)
            {
                a[i] = num;
            }
        }

        // 相同但是不是全0(-1相当于一个相同数)
        bool flat1 = false;
        for(int i = 0; i < n - 2; i++)
        {
            if(a[i] == a[i + 1] && a[i + 1] == a[i + 2] && a[i] != 0)
            {
                flat1 = true;
            }
            else
            {
                flat1 = false;
                break;
            }

        }
        if(flat1)
        {
            cout << "YES" << endl;
        }
        else
        {
            cout << "NO" << endl;
        }


    }
    return 0;
}