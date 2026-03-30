#include <iostream>
#include <vector>
#include <map>
using namespace std;
int main() {

    int n, x;
    cin >> n >> x;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    map<int, int> cnt;
    for (int i = 0; i < n; ++i) {
        cnt[a[i]]++;
    }
    int ans = 0;
    int mx = 0;
    int mxx = 0;
    for (auto [k, v] : cnt) {
        if (v > mx) {
            mx = v;
        }
        if (k == x) {
            mxx = v;
        }
    }
    ans = mx - mxx;

    cout << ans << endl;

    return 0;
}