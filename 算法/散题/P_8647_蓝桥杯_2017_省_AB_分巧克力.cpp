#include <iostream>
#include <vector>
using namespace std;

#define int long long

int test01(int len, vector<int> &H, vector<int> &W) {
    int n = H.size();
    int num = 0;
    for (int i = 0; i < n; i++) {
        if (H[i] < len || W[i] < len) {
            continue;
        }
        num += ((H[i] / len) * (W[i] / len));
    }

    return num;
}

signed main() {

    int n, k;
    cin >> n >> k;
    vector<int> H(n, 0);
    vector<int> W(n, 0);

    for (int i = 0; i < n; i++) {
        cin >> H[i] >> W[i];
    }

    int l = 0, r = 1e5;
    while (l < r) {
        int mid = (l + r + 1) >> 1;
        int num = test01(mid, H, W);
        if (num < k) {
            r = mid - 1;
        }
        else {
            l = mid;
        }
    }

    cout << l << endl;


    return 0;
}