#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

#define int long long

#define IOS ios::sync_with_stdio(0), cin.tie(nullptr), cout.tie(nullptr);

struct moving{
    int op = 1;
    int x = 1;
    int y = 1;
    int len = 1;
};

signed main() {

    IOS;

    int n;
    cin >> n;
    int q;
    cin >> q;
    vector<moving> vec(q);
    for (int i = 0; i < q; i++) {
        cin >> vec[i].op >> vec[i].x >> vec[i].y >> vec[i].len;
        // vec[i].op = 1;
        // vec[i].x = 1;
        // vec[i].y = 1;
        // vec[i].len = 1;
    }

    int d;
    cin >> d;
    while (d--) {
        int dx, dy;
        cin >> dx >> dy;
        // cout << dx << " " << dy << endl;
        for (int i = q - 1; i >= 0; i--) {
            int x1 = vec[i].x;
            int y1 = vec[i].y;
            int x2 = x1 + vec[i].len - 1;
            int y2 = y1 + vec[i].len - 1;
            // cout << x1 << " " << y1 << " " << x2 << " " << y2 << endl;

            if (dx >= x1 && dx <= x2 && dy >= y1 && dy <= y2) {
                if (vec[i].op == 2) {
                    // 需要执行一个逆时针来抵消
                    int hen = dx - x1;
                    int shu = dy - y1;
                    dy = y2 - hen;
                    dx = x1 + shu;
                }
                else {
                    // 需要执行一个顺时针来抵消
                    int hen = dx - x1;
                    int shu = dy - y1;
                    dy = y1 + hen;
                    dx = x2 - shu;
                }
            }

            // cout << dx << " " << dy << endl;
        }

        // cout << dx << " " << dy << endl;

        cout << (dx - 1) * n + dy << endl;
    }
    

    return 0;
}