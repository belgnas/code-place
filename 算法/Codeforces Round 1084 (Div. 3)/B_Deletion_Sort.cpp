#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);

#define int long long

signed main()
{
    IOS;

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        // 本题定义非递减为：所有元素都小于等于前一个元素（感觉这个定义和递增一样）
        // 我要尽可能阻止这种趋势
        // 也就是说，我尽可能要让他没有规律或者递减
        // 每次可以删除一个元素
        int ans = 0;
        bool flat = false;
        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                if (a[j] < a[i]) {
                    flat = true;
                    break;
                }
            }
            if (flat) {
                break;
            }
        }

        if (flat) {
            ans = 1;
        }
        else {
            ans = n;
        }
        
        cout << ans << endl;
    }

    return 0;
}
