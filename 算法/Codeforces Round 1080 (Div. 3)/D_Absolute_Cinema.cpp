#include <iostream>
#include <vector>
using namespace std;

#define int long long

int calculate(int idx, vector<int>& f, vector<int>& vec) {
    int n = vec.size();
    int w = f[idx];

    for (int i = 1; i < n - 1; i++) {
        w = w - vec[i] * abs(i - idx);
    }

    return w;
}


vector<int> solve(vector<int>& f) {
    int n = f.size();
    vector<int> vec(n, 0);

    // 计算中间的 vec[i]
    for (int i = 1; i < n - 1; i++) {
        int delta = f[i + 1] + f[i - 1] - 2 * f[i];
        // if (delta % 2 != 0) {
        //     return {}; // 返回一个空容器（这里是vector）
        // }

        vec[i] = delta / 2;
        
        // // 题目保证对于所有 1≤i≤n，都有 ∣a_i∣≤1000 
        // if (abs(vec[i]) > 1000) {
        //     return {}; // 返回一个空容器（这里是vector）
        // }
    }
    
    // 计算第一个和最后一个 的
    int first = calculate(0, f, vec);
    int last = calculate(n - 1, f, vec);

    // // 检查第一个和最后一个 vec[i] 是否能被 (n - 1) 整除
    // if (first % (n - 1) != 0) {
    //     return {};
    // }
    // if (last % (n - 1) != 0) {
    //     return {};
    // }

    vec[0] = last / (n - 1); // 用最后一个位置的结果算第一个
    vec[n - 1] = first / (n - 1); // 同理
    
    // if (abs(vec[0]) > 1000 || abs(vec[n - 1]) > 1000) {
    //     return {};
    // }

    return vec;
}

signed main() {

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> f(n, 0);
        for (int i = 0; i < n; i++) cin >> f[i];
        
        auto ans = solve(f);

        for (int i = 0; i < n; i++) {
            cout << ans[i] << " ";
        }
        cout << endl;
    }
}