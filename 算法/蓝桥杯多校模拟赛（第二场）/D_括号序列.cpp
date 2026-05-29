#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stack>
using namespace std;

#define int long long

int test01(vector<char> &st) {
    // for (int i = 0; i < st.size(); i++) {
    //     cout << st[i];
    // }
    // cout << endl;

    int sum = 0;
    int temp = 0;
    for (int i = 0; i < st.size(); i++) {
        if (st[i] == '(' || st[i] == ')') {
            continue;
        }
        if (st[i] == '.') {
            sum += temp;
            temp = 0;
        }
        if (st[i] >= '0' && st[i] <= '9') {
            temp *= 10;
            temp += (st[i] - '0');
        }
    }

    if (temp > 0) {
        sum += temp;
    }

    return sum;
}

signed main() {

    string s;
    cin >> s;
    int ans = 0;
    vector<char> st;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '(') {
            st.clear();
            st.push_back('(');
        }
        else if (s[i] == ')') {
            if (!st.empty() && st.front() == '(') {
                st.push_back(')');
                ans = max(ans, test01(st));
                st.clear();
            }
        }
        else {
            if (!st.empty() && st.front() == '(') {
                st.push_back(s[i]);
            }
        }
    }

    cout << ans << endl;

    return 0;
}