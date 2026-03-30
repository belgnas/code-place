#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, x1, x2, y1, y2;
    cin >> n >> x1 >> y1 >> x2 >> y2;
    string ans;

    if ((x1 + y1) % 2 == (x2 + y2) % 2 || (y1 == y2 && abs(x1 - x2) <= 1 && y1 != 1 && y1 != n)) {
        ans += "-1";
        cout << ans << endl;
        return 0;
    }

    bool swap_dir = (y2 <= y1);
    if (swap_dir) {
        y1 = n - y1 + 1;
        y2 = n - y2 + 1;
    }

    for (int i = 1; i < y1; i++)  {
        ans += (swap_dir ? 'R' : 'L');
    }

    if (x1 == 1) {
        ans += 'D';
    }
    else {
        ans += 'U';
    }

    for (int i = 1; i < y1; i++)  {
        ans += (swap_dir ? 'L' : 'R');
    }

    string s = "RURD";
    if (x1 == 2) {
        s = "RDRU";
    }
    s[0] = s[2] = (swap_dir ? 'L' : 'R');

    for (int i = 0; i < (y2 - y1 - 1) / 2; i++)  {
        ans += s;
    }

    if (y1 == y2) {
        cout << ans << endl;
        return 0;
    }

    if ((y2 - y1) % 2 == 0 && y1 != y2) {
        if (x1 == 1) {
            ans += (swap_dir ? 'L' : 'R');
            ans += 'U';
        }
        else {
            ans += (swap_dir ? 'L' : 'R');
            ans += 'D';
        }
    }

    for (int i = y2; i <= n; i++) {
        ans += (swap_dir ? 'L' : 'R');
    }

    if (x2 == 1) {
        ans += 'U';
    }
    else {
        ans += 'D';
    }

    for (int i = y2; i < n; i++) {
        ans += (swap_dir ? 'R' : 'L');
    }

    cout << ans << endl;
    return 0;
}