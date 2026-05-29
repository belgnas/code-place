#include <iostream>
#include <vector>
#include <string>
using namespace std;

#define IOS ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

#define int long long

signed main()
{
    IOS;

    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        int num1 = 0;
        int mod_2 = 0;
        vector<int> mod_2_vec;
        int mod_3 = 0;
        vector<int> mod_3_vec;
        int mod_6 = 0;
        vector<int> mod_6_vec;
        int mod_else_1 = 0;
        vector<int> mod_else_1_vec;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            if (a[i] == 1) {
                num1++;
            }
            else if (a[i] % 6 == 0) {
                mod_6++;
                mod_6_vec.push_back(a[i]);
            }
            else if (a[i] % 2 == 0) {
                mod_2++;
                mod_2_vec.push_back(a[i]);
            }
            else if (a[i] % 3 == 0) {
                mod_3++;
                mod_3_vec.push_back(a[i]);
            }
            else {
                mod_else_1++;
                mod_else_1_vec.push_back(a[i]);
            }
        }

        // cout << "num1: " << num1 << endl;
        // cout << "mod_2: " << mod_2 << endl;
        // cout << "mod_3: " << mod_3 << endl;
        // cout << "mod_6: " << mod_6 << endl;
        // cout << "mod_else_1: " << mod_else_1 << endl;
        // cout << endl;

        vector<int> ans;
        ans.insert(ans.end(), mod_6_vec.begin(), mod_6_vec.end());
        ans.insert(ans.end(), mod_2_vec.begin(), mod_2_vec.end());
        for (int i = 0; i < num1; i++) {
            ans.push_back(1);
        }
        ans.insert(ans.end(), mod_else_1_vec.begin(), mod_else_1_vec.end());
        ans.insert(ans.end(), mod_3_vec.begin(), mod_3_vec.end());
        
        
        for (int i = 0; i < n; i++) {
            cout << ans[i];
            if (i != n - 1) {
                cout << " ";
            }
        }
        cout << endl;
    }


    return 0;
}