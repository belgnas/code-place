#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <unordered_map>
#include <iomanip>

using namespace std;

#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
#define int long long

signed main() {
    IOS;
    
    int x1, y1;
    cin >> x1 >> y1;
    int x2, y2;
    cin >> x2 >> y2;
    
    // 特判1：A、B都在x轴上，无解
    if (y1 == 0 && y2 == 0) {
        cout << "no answer" << endl;
        return 0; // 终止程序，避免后续执行
    }
    
    int k = y2 - y1;
    int m = x2 * y1 - x1 * y2;
    
    // 特判2：k=0（AB平行x轴）
    if (k == 0) {
        if (abs(m) == 4) {
            cout << fixed << setprecision(3) << 0.0 << endl;
        } else {
            cout << "no answer" << endl;
        }
        return 0; // 关键修改：终止程序，避免执行后面的除以零代码
    }
    
    // 只有k≠0时才执行这里，无除以零风险
    double ans = (4.0 - m) / k; // 4.0转double，避免整数除法
    cout << fixed << setprecision(3) << ans << endl;
    
    return 0;
}