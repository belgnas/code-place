#include <iostream>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <string>
#include <vector>
#include <cstring>
#include <set>
#include <tuple>
#include <bitset>
#include <utility>
#include <queue>
#include <deque>
#include <numeric>

using namespace std;

#define IOS ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
#define endl '\n'

// g[x][y][0] 表示偶数秒幽灵位置
// g[x][y][1] 表示奇数秒幽灵位置
bool g[1005][1005][2];

// d[x][y][state]
// state 定义:
// 0: 技能可用，当前时间偶数 (下一次去奇数)
// 1: 技能可用，当前时间奇数 (下一次去偶数)
// 2: 技能刚使用(冻结中)，锁定在偶数 (下一次还查偶数)
// 3: 技能刚使用(冻结中)，锁定在奇数 (下一次还查奇数)
// 4: 技能已用，当前时间偶数 (下一次去奇数)
// 5: 技能已用，当前时间奇数 (下一次去偶数)
int d[1005][1005][6];

struct Node {
    int x, y, state;
};

int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};

signed main() {
    IOS;

    int n, m, k;
    if (!(cin >> n >> m >> k)) return 0;

    for (int i = 0; i < k; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        g[x1][y1][1] = true; // 奇数秒
        g[x2][y2][0] = true; // 偶数秒
    }

    memset(d, -1, sizeof(d));
    queue<Node> q;

    // 初始状态：(1,1), 时间0(偶数), 技能可用
    d[1][1][0] = 0;
    q.push({1, 1, 0});

    while (!q.empty()) {
        Node cur = q.front();
        q.pop();

        int x = cur.x;
        int y = cur.y;
        int state = cur.state;
        int dist = d[x][y][state];

        if (x == n && y == m) {
            cout << dist << endl;
            return 0;
        }

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx < 1 || nx > n || ny < 1 || ny > m) continue;

            // 1. 普通移动
            // 如果 state 是 0, 1, 4, 5，则是正常时间流逝
            if (state == 0 || state == 1 || state == 4 || state == 5) {
                int next_parity; 
                int next_state;

                // 当前偶(0/4) -> 下一刻奇(1)
                // 当前奇(1/5) -> 下一刻偶(0)
                if (state == 0) { next_parity = 1; next_state = 1; }
                else if (state == 1) { next_parity = 0; next_state = 0; }
                else if (state == 4) { next_parity = 1; next_state = 5; }
                else { next_parity = 0; next_state = 4; } // state == 5

                if (!g[nx][ny][next_parity]) {
                    if (d[nx][ny][next_state] == -1) {
                        d[nx][ny][next_state] = dist + 1;
                        q.push({nx, ny, next_state});
                    }
                }
            }
            
            // 2. 冻结状态下的移动 (State 2, 3)
            // 这是一个“缓冲”状态，代表使用了技能后的第1秒。
            // 这一秒结束后，时间恢复流动（但相对于原始时间轴平移了）。
            // 比如：锁定偶数 -> 下一步去奇数状态（正常流逝）
            else if (state == 2 || state == 3) {
                // 2 (锁定偶) -> 恢复正常流逝 -> 下一步应该变成 奇数时刻(5)
                // 3 (锁定奇) -> 恢复正常流逝 -> 下一步应该变成 偶数时刻(4)
                
                int next_state = (state == 2) ? 5 : 4;
                int check_parity = (state == 2) ? 1 : 0; 
                // 等等，如果恢复正常流逝。
                // 状态2意味着：我们在T时刻(偶)冻结了。现在是T+1时刻，幽灵仍然是偶。
                // 下一步是T+2时刻。
                // 如果“冻结2秒”意味着跳过1次变换：
                // T(E) -> T+1(E) -> T+2(O).
                // 所以从 状态2(已经经历了一次E->E) 出发，下一步应该是 奇数(O)。
                // 所以 check_parity 应该是 1 (奇数)。
                
                if (!g[nx][ny][check_parity]) {
                    if (d[nx][ny][next_state] == -1) {
                        d[nx][ny][next_state] = dist + 1;
                        q.push({nx, ny, next_state});
                    }
                }
            }

            // 3. 发动技能 (仅从 0 或 1)
            if (state == 0 || state == 1) {
                // 发动技能！
                // 0 (当前偶) -> 下一刻仍然查 偶
                // 1 (当前奇) -> 下一刻仍然查 奇
                
                int lock_parity = (state == 0) ? 0 : 1;
                int next_state = (state == 0) ? 2 : 3;

                if (!g[nx][ny][lock_parity]) {
                    if (d[nx][ny][next_state] == -1) {
                        d[nx][ny][next_state] = dist + 1;
                        q.push({nx, ny, next_state});
                    }
                }
            }
        }
    }

    cout << -1 << endl;

    return 0;
}