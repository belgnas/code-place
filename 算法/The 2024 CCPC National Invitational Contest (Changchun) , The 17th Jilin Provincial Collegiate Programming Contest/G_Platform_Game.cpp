#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

#define int long long
#define endl '\n'

#define IOS ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

struct Plat {
    int l, r, y;
};

bool compare(Plat a, Plat b) {
    return a.y > b.y;
}

signed main()
{
    IOS;
    
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<Plat> p(n);
        for (int i = 0; i < n; i++) {
            cin >> p[i].l >> p[i].r >> p[i].y;
        }

        int cur_x, cur_y;
        cin >> cur_x >> cur_y;

        sort(p.begin(), p.end(), compare);

        
        for (int i = 0; i < n; i++) {
            if (p[i].y < cur_y && cur_x > p[i].l && cur_x < p[i].r) {
                cur_x = p[i].r;
                cur_y = p[i].y;
            }
        }

        cout << cur_x << endl;
    }



    return 0;
}