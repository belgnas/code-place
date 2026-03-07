#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define int long long

// 长方形
struct Rect {
    int h, w;
};

int n, k;
vector<Rect> choc;

// 边长为 len 时，是否能切出至少 k 块
bool check(int len) {
    if (len == 0) return true;
    int cnt = 0;
    for (const auto& rect : choc) {
        // 行能切几段 * 列能切几段
        cnt += (rect.h / len) * (rect.w / len);
    }
    return cnt >= k;
}

signed main() {

    ios::sync_with_stdio(false);
    cin.tie(0);

    if (!(cin >> n >> k)) return 0;

    choc.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> choc[i].h >> choc[i].w;
    }

    int l = 1, r = 100000; 
    while (l < r) {
        int mid = (l + r + 1) >> 1;
        if (check(mid)) {
            // 如果 mid 能切够 K 块，说明 mid 是可行的，
            // 但可能还有更大的，所以答案在 [mid, r]
            l = mid;
        } else {
            // 如果 mid 切不够，说明 mid 太大了，
            // 答案在 [l, mid - 1]
            r = mid - 1;
        }
    }

    cout << l << endl;

    return 0;
}