#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
#define endl '\n'
#define int long long

const int move1[4][2] {
    {1, 0},  // 上
    {-1, 0}, // 下
    {0, 1},  // 左
    {0, -1}  // 右
};

signed main() {
    IOS;
    
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        int k = 1;
        while (n & (n << k)) {
            k++;
        }
        int x = n << k;
        int y = x + n;
        cout << x << " " << y << endl;
        
    }

    return 0;
}