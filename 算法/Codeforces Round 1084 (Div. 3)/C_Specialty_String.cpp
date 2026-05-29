#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);

#define int long long

bool solve(string s) {
    vector<char> st;
    for (char c : s) {
        if (!st.empty() && st.back() == c) {
            st.pop_back(); // 只要相同就消掉，因为这样会让剩下的字符更有机会碰到相同的
        }
        else {
            st.push_back(c); // 不相同就只能进栈挡在中间
        }
    }
    return st.empty(); // 如果最后栈空了，说明全部消掉了
}



signed main()
{
    IOS;

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        string s;
        cin >> s;
        // 怎么有点像回文串的拼接？
        bool ans = solve(s);

        cout << (ans ? "YES" : "NO") << endl;
    }

    return 0;
}
