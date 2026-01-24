#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

const int INF = 0x3f3f3f3f;

// dp[mask][current_node][used_zero][used_double]
// mask: 二进制状态，表示走过的点
// current_node: 当前所在的点 (0 ~ n-1)
// used_zero: 0表示没用过重力加速，1表示用过
// used_double: 0表示没用过反重力加速，1表示用过
int dp[1 << 16][16][2][2];
int p[20][20]; // 存储图的边权

int main() {
    // 优化输入输出
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> p[i][j];
        }
    }

    // 初始化 DP 数组为无穷大
    memset(dp, 0x3f, sizeof(dp));

    // 初始化起点
    // 题目说可以任意选择出发点，所以每个点作为起点的代价都是 0
    // mask 对应只把第 i 位置 1 (1 << i)
    // 此时两个技能都还没用 (0, 0)
    for (int i = 0; i < n; i++) {
        dp[1 << i][i][0][0] = 0;
    }

    // 开始状压 DP
    // 第一层枚举状态 mask
    for (int mask = 1; mask < (1 << n); mask++) {
        // 第二层枚举当前所在的点 u
        for (int u = 0; u < n; u++) {
            // 如果 u 不在 mask 里，说明状态不合法，跳过
            if (!((mask >> u) & 1)) continue;

            // 第三层枚举两个技能的使用状态
            for (int z = 0; z <= 1; z++) {
                for (int d = 0; d <= 1; d++) {
                    // 如果当前状态不可达，跳过
                    if (dp[mask][u][z][d] == INF) continue;

                    // 枚举下一个要去的点 v
                    for (int v = 0; v < n; v++) {
                        // 如果 v 已经在 mask 里了，不能重复走，跳过
                        if ((mask >> v) & 1) continue;

                        int next_mask = mask | (1 << v);

                        // 1. 普通跳跃 (不使用新技能)
                        // 这是一个 min 更新操作，取更小值
                        dp[next_mask][v][z][d] = min(dp[next_mask][v][z][d],
                                                     dp[mask][u][z][d] + p[u][v]);

                        // 2. 使用重力加速 (变0)
                        // 前提：之前没用过 (z == 0)
                        if (z == 0) {
                            dp[next_mask][v][1][d] = min(dp[next_mask][v][1][d], dp[mask][u][0][d] + 0);
                        }

                        // 3. 使用反重力加速 (乘2)
                        // 前提：之前没用过 (d == 0)
                        if (d == 0) {
                            dp[next_mask][v][z][1] = min(dp[next_mask][v][z][1],
                                                         dp[mask][u][z][0] + p[u][v] * 2);
                        }
                    }
                }
            }
        }
    }

    // 寻找答案
    // 目标 mask 是所有位都为 1，即 (1 << n) - 1
    // 且两个技能必须都使用过，即状态为 [1][1]
    int full_mask = (1 << n) - 1;
    int ans = INF;

    for (int i = 0; i < n; i++) {
        ans = min(ans, dp[full_mask][i][1][1]);
    }

    cout << ans << endl;

    return 0;
}