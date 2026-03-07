#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

#define IOS ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
#define endl '\n'

struct Event {
    int time;
    int type; // 0:指令, 1:查询
    int param; // 指令:目标楼层; 查询:索引
    Event(int t, int ty, int p) : time(t), type(ty), param(p) {}
    bool operator<(const Event& other) const {
        if (time != other.time) return time < other.time;
        return type < other.type; // 同时间先处理指令
    }
};

signed main() {
    IOS;
    int T;
    cin >> T;
    while (T--) {
        int n, q;
        cin >> n >> q;
        vector<Event> events;

        // 读取指令
        for (int i = 0; i < n; ++i) {
            int t, f;
            cin >> t >> f;
            events.emplace_back(t, 0, f);
        }

        // 读取查询
        vector<int> queries(q);
        for (int i = 0; i < q; ++i) {
            int Q;
            cin >> Q;
            events.emplace_back(Q, 1, i);
        }

        sort(events.begin(), events.end());

        // 电梯状态
        int current_time = 0;
        int current_floor = 1;
        int direction = 0; // 1:上, -1:下, 0:静止
        multiset<int> pending;
        int next_target = -1;
        vector<int> ans(q);

        for (const auto& event : events) {
            int t = event.time;
            int type = event.type;
            int param = event.param;

            // 1. 模拟从current_time到t的移动（核心修正区域）
            while (current_time < t) {
                if (direction == 0) {
                    // 静止时不移动，直接跳转到事件时间
                    current_time = t;
                    break;
                }

                // 确定下一个目标
                if (next_target == -1) {
                    if (direction == 1) { // 向上：找≥当前楼层的最大目标
                        if (pending.empty()) {
                            direction = 0;
                            current_time = t;
                            break;
                        }
                        int max_p = *pending.rbegin();
                        if (max_p >= current_floor) {
                            next_target = max_p;
                        } else {
                            direction = -1; // 切换向下
                            continue;
                        }
                    } else { // 向下：找≤当前楼层的最小目标
                        if (pending.empty()) {
                            direction = 0;
                            current_time = t;
                            break;
                        }
                        int min_p = *pending.begin();
                        if (min_p <= current_floor) {
                            next_target = min_p;
                        } else {
                            direction = 1; // 切换向上
                            continue;
                        }
                    }
                }

                // 计算移动距离和到达时间
                int distance = abs(next_target - current_floor);
                int arrival_time = current_time + distance;

                if (arrival_time <= t) { // 到达目标
                    current_floor = next_target;
                    current_time = arrival_time;
                    // 移除目标指令
                    auto it = pending.find(next_target);
                    if (it != pending.end()) pending.erase(it);
                    next_target = -1; // 重置目标
                    // 检查是否还有指令，否则静止
                    if (pending.empty()) direction = 0;
                } else { // 未到达目标，移动到事件时间
                    int move = t - current_time;
                    current_floor += direction * move;
                    current_time = t;
                }
            }

            // 2. 处理当前事件
            if (type == 0) { // 指令
                int f = param;
                if (f != current_floor) {
                    pending.insert(f);
                    if (direction == 0) direction = 1; // 静止时向上
                }
            } else { // 查询
                ans[param] = current_floor;
            }
        }

        for (int x : ans) cout << x << '\n';
    }
    return 0;
}