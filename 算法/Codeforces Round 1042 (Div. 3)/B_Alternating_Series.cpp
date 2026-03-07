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
#include <queue>
#include <deque>

using namespace std;

#define IOS ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
#define endl '\n'

const int INF = 0x3f3f3f3f;

signed main()
{
    IOS;

    int t;
    cin >> t;
    while(t--)
    {
        int n;
        cin >> n;
        
        vector<int> arr;
        
        if(n == 1)
        {
            arr = {0};
        }
        else
        {
            // 先生成基础序列：偶数索引(-1)，奇数索引(3)
            for(int i = 0; i < n; i++)
            {
                arr.push_back( (i % 2 == 0) ? -1 : 3 );  // 关键修正：奇数索引用3，而非1
            }
            
            // 偶数长度：最后一个元素改为2（覆盖原3）
            if(n % 2 == 0)
            {
                arr[n-1] = 2;
            }
            // 奇数长度：无需额外修改（倒数第二个已是3，最后一个是-1）
        }

        for(auto x : arr)
        {
            cout << x << " ";
        }
        cout << endl;
    }

    return 0;
}