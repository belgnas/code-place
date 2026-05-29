#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
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
        int x, y;
        cin >> x >> y;
        vector<int> p(n);
        for (int i = 0; i < n; i++) {
            cin >> p[i];
        }
        vector<int> num1;
        vector<int> num2;
        for (int i = 0; i < n; i++) {
            if (i < x || i >= y) {
                num1.push_back(p[i]);
            }
            else {
                num2.push_back(p[i]);
            }
        }
        int move_len_res_1 = 0;
        if (num1.size() > 0) {
            // j 表示偏移量
            for (int i = 0; i < num1.size(); i++) {
                // 逐个位置判断（共有 num1.size() 个位置）
                for (int j = 0; j < num1.size(); j++) {
                    int idx_prev = (move_len_res_1 + j) % num1.size();
                    int idx_now = (i + j) % num1.size();
                    if (num1[idx_prev] > num1[idx_now]) {
                        move_len_res_1 = i;
                        break;
                    }
                }
            }
            cout << "move_len_res_1 = " << move_len_res_1 << endl;
        }

        int move_len_res_2 = 0;
        if (num2.size() > 0) {
            // j 表示偏移量
            
            for (int i = 0; i < num2.size(); i++) {
                // 逐个位置判断（共有 num2.size() 个位置）
                for (int j = 0; j < num2.size(); j++) {
                    int idx_prev = (move_len_res_2 + j) % num2.size();
                    int idx_now = (i + j) % num2.size();
                    if (num2[idx_prev] > num2[idx_now]) {
                        move_len_res_2 = i;
                        break;
                    }
                }
            }
            cout << "move_len_res_2 = " << move_len_res_2 << endl;
        }

        // for (int i = 0; i < num1.size(); i++) {
        //     int idx = (0 - move_len_res_1 + i) % num1.size();
        //     cout << num1[idx] << " ";
        // }
        // cout << endl;

        // for (int i = 0; i < num2.size(); i++) {
        //     int idx = (0 - move_len_res_2 + i) % num2.size();
        //     cout << num2[idx] << " ";
        // }
        // cout << endl;

        int idx1 = (0 - move_len_res_1) % num1.size();
        int idx2 = (0 - move_len_res_2) % num2.size();
        for (int i = 0; i < n; i++) {
            if (i < x || i >= y) {
                cout << num1[idx1] << " ";
                idx1++;
                idx1 %= num1.size();
            }
            else {
                cout << num2[idx2] << " ";
                idx2++;
                idx2 %= num2.size();
            }
        }
        cout << endl;
    }
    

    return 0;
}
