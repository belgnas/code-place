#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define int long long

signed main() {

    int t;
    cin >> t;
    while (t--) {
        int p, q;
        cin >> p >> q;
        int sum = p + q * 2;
        vector<pair<int, int>> maybe;
        int left = 3;
        int right = 1;
        while (left + right <= sum) {
            if (right * (right + 1) * 2 > sum) {
                break;
            }
            int chang = sum / left;
            int kuan = right;
            if (sum % left == right) {
                maybe.push_back({chang, kuan});
            }
            left += 2;
            right ++;
        }

        // for (int i = 0; i < maybe.size(); i++) {
        //     cout << maybe[i].first << " " << maybe[i].second << endl;
        // }
        // cout << "--------" << endl;

        bool flat = false;
        int ans_chang = 0;
        int ans_kuan = 0;
        for (int i = 0; i < maybe.size(); i++) {
            int chang = maybe[i].first;
            int kuan = maybe[i].second;

            if (chang == kuan) {
                flat = true;
                ans_chang = chang;
                ans_kuan = kuan;
                break;
            }
            else {
                int temp = chang - kuan;
                if (p >= temp) {
                    flat = true;
                    ans_chang = chang;
                    ans_kuan = kuan;
                    break;
                }
            }
        }

        if (flat) {
            cout << ans_kuan << " " << ans_chang << endl;
        }
        else {
            cout << "-1" << endl;
        }
    }


    return 0;
}