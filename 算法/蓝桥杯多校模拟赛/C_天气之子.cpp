#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    if (n == 0) {
        cout << 0 << "\n";
        return 0;
    }

    // cnt[weather] = weather在前i-1天出现的次数
    // firstPos[weather] = weather首次出现的位置
    unordered_map<int, int> cnt;
    unordered_map<int, int> firstPos;

    // 第一天固定预测天气类型1（即值为1的天气）
    int predict = 1;
    cnt[a[1]]++;
    firstPos[a[1]] = 1;
    int ans = (predict == a[1]) ? 1 : 0;

    for (int i = 2; i <= n; i++) {
        // 判断前一天是否预测成功（predict vs a[i-1]）
        if (predict != a[i - 1]) {
            // 前一天预测失败，重新统计前i-1天的众数
            int bestWeather = a[1];
            for (const auto &p : cnt) {
                int weather = p.first;
                int c = p.second;
                int first = firstPos[weather];

                int bestCnt = cnt[bestWeather];
                int bestFirst = firstPos[bestWeather];

                if (c > bestCnt || (c == bestCnt && first > bestFirst)) {
                    bestWeather = weather;
                }
            }
            predict = bestWeather;
        }
        // 如果前一天预测成功，predict保持不变

        // 判断当天预测是否成功
        if (predict == a[i]) {
            ans++;
        }

        // 更新统计，加入当天实际天气a[i]
        cnt[a[i]]++;
        if (firstPos.find(a[i]) == firstPos.end()) {
            firstPos[a[i]] = i;
        }
    }

    cout << ans << "\n";
    return 0;
}