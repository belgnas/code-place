#include <iostream>
#include <vector>
#include <string>
#include <set>
using namespace std;

#define IOS ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

#define int long long

int find_mex(vector<int>& a, int idx1, int idx2) {
    int len = a.size();
    int idx_mid = (idx1 + idx2) / 2;
    int l = idx_mid;
    int r = idx_mid;
    // cout << "idx1: " << idx1 << endl;
    // cout << "idx2: " << idx2 << endl;
    // cout << "idx_mid: " << idx_mid << endl;
    if (idx_mid * 2 != idx1 + idx2) {
        r++;
    }
    // cout << "l: " << l << endl;
    // cout << "r: " << r << endl;
    int mex_num = 0;
    set<int> set;
    while (l >= 0 && r <= len - 1) {
        if (a[l] != a[r]) {
            break;
        }
        else {
            set.insert(a[l]);
            l--;
            r++;
        }
    }
    for (auto it : set) {
        if (it == mex_num) {
            mex_num++;
        }
        else {
            break;
        }
    }
    return mex_num;
}

signed main() {

    IOS;

    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        vector<int> a(2 * n);
        int idx_first_0 = -1;
        int idx_second_0 = -1;
        for (int i = 0; i < 2 * n; i++) {
            cin >> a[i];
            if (a[i] == 0) {
                if (idx_first_0 == -1) {
                    idx_first_0 = i;
                }
                else {
                    idx_second_0 = i;
                }
            }
        }

        int mex_num1 = find_mex(a, idx_first_0, idx_first_0);
        // cout << "mex_num1: " << mex_num1 << endl;
        int mex_num2 = find_mex(a, idx_second_0, idx_second_0);
        // cout << "mex_num2: " << mex_num2 << endl;
        int mex_num3 = find_mex(a, idx_first_0, idx_second_0);
        // cout << "mex_num3: " << mex_num3 << endl;

        int ans = max(mex_num1, max(mex_num2, mex_num3));
        cout << ans << endl;
    }


    return 0;
}