#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

// 检查在最大差距为 X 时，能否将短数组的所有元素匹配到长数组中
bool check(int X, vector<int>& a, vector<int>& b) {
    int j = 0;                     // 指向长数组 b 的指针
    for (int i = 0; i < a.size(); ++i) {
        // 跳过所有比 a[i] - X 小的元素
        while (j < b.size() && b[j] < a[i] - X) ++j;
        // 如果当前 b[j] 在允许范围内，则匹配，指针后移
        if (j < b.size() && b[j] <= a[i] + X) ++j;
        else return false;         // 无法匹配当前 a[i]
    }
    return true;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> l(n), r(m);
    for (int i = 0; i < n; ++i) cin >> l[i];
    for (int i = 0; i < m; ++i) cin >> r[i];

    sort(l.begin(), l.end());
    sort(r.begin(), r.end());

    // 让 a 为较短的数组，b 为较长的数组
    if (n > m) swap(l, r);

    // 二分答案
    int left = 0, right = 1e9, ans = 0;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (check(mid, l, r)) {
            ans = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    cout << ans << endl;
    return 0;
}