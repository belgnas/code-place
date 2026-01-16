#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
    // 线段树节点
    struct Node {
        int cnt;        // 覆盖计数：有多少个正方形覆盖了这个区间
        long long len;  // 覆盖长度：这个区间内实际被覆盖的长度
    } tree[400005];     // 4倍空间定理由来：节点数最多是坐标数的4倍

    // 存储所有去重后的 X 坐标
    vector<int> X;

    // 扫描线事件
    struct Event {
        int y;
        int type;   // +1 表示正方形下底，-1 表示正方形上顶
        int x1, x2; // 正方形的左右边界

        // 排序规则：按 y 从低到高
        bool operator<(const Event& other) const {
            return y < other.y;
        }
    };

    // 线段树核心逻辑：向上更新信息
    // node: 当前节点索引, l: 对应 X 数组的左下标, r: 对应 X 数组的右下标
    void pushup(int node, int l, int r) {
        if (tree[node].cnt > 0) {
            // 只要被覆盖次数 > 0，那么这段物理长度就完全算作被覆盖
            // 物理长度 = 右边界坐标 - 左边界坐标
            tree[node].len = (long long)X[r + 1] - X[l];
        } else {
            // 如果 cnt == 0，说明没有正方形完全覆盖这一整段
            // 那么覆盖长度就等于左孩子覆盖的 + 右孩子覆盖的
            if (l == r) {
                tree[node].len = 0; // 叶子节点，没有孩子，长度为0
            } else {
                tree[node].len = tree[2 * node].len + tree[2 * node + 1].len;
            }
        }
    }

    // 线段树更新操作
    // [L, R] 是我们要修改的区间（对应 X 数组的下标）
    // val 是 +1 或 -1
    void update(int node, int l, int r, int L, int R, int val) {
        // 如果当前区间完全被包含在修改范围内
        if (L <= l && r <= R) {
            tree[node].cnt += val;
            pushup(node, l, r);
            return;
        }
        int mid = (l + r) / 2;
        if (L <= mid) update(2 * node, l, mid, L, R, val);
        if (R > mid) update(2 * node + 1, mid + 1, r, L, R, val);
        pushup(node, l, r);
    }

public:
    double separateSquares(vector<vector<int>>& squares) {
        vector<Event> events;
        X.clear();

        // 步骤 1: 构建事件和收集 X 坐标
        for (const auto& sq : squares) {
            int x = sq[0];
            int y = sq[1];
            int l = sq[2];
            X.push_back(x);
            X.push_back(x + l);
            // 记录下底（入边）和上底（出边）
            events.push_back({y, 1, x, x + l});
            events.push_back({y + l, -1, x, x + l});
        }

        // 步骤 2: X 坐标离散化（排序+去重）
        sort(X.begin(), X.end());
        X.erase(unique(X.begin(), X.end()), X.end());

        // 事件按 Y 排序
        sort(events.begin(), events.end());

        // 初始化线段树（清空）
        for(int i=0; i < 400005; ++i) {
            tree[i].cnt = 0;
            tree[i].len = 0;
        }

        // 结构体用来记录每一层的状态，方便最后计算
        struct LayerInfo {
            long long y_start; // 这一层的起始 y
            long long height;  // 这一层的高度 (下一层y - 这一层y)
            long long width;   // 这一层的有效覆盖宽度
        };
        vector<LayerInfo> layers;
        
        long long total_area = 0;
        int m = X.size(); 
        
        // 步骤 3: 扫描线移动
        // prev_y 记录上一次扫描线停下的位置
        int prev_y = events[0].y; 

        // 遍历所有事件
        for (int i = 0; i < events.size(); ) {
            int curr_y = events[i].y;
            

            if (curr_y > prev_y) {

                long long h = curr_y - prev_y;
                long long w = tree[1].len;

                total_area += h * w;
                layers.push_back({(long long)prev_y, h, w});
            }
            

            while (i < events.size() && events[i].y == curr_y) {

                int x_l_idx = lower_bound(X.begin(), X.end(), events[i].x1) - X.begin();
                int x_r_idx = lower_bound(X.begin(), X.end(), events[i].x2) - X.begin();
                
                if (x_l_idx < x_r_idx) {
                    update(1, 0, m - 2, x_l_idx, x_r_idx - 1, events[i].type);
                }
                i++;
            }
            prev_y = curr_y;
        }

        // 步骤 4: 找到一半面积的位置
        double target = (double)total_area / 2.0;
        double current_sum = 0;

        for (const auto& layer : layers) {
            double layer_area = (double)layer.height * layer.width;
            
            // 如果加上这一层就超过或等于目标了，说明分割线在这一层里
            if (current_sum + layer_area >= target) {
                double needed_area = target - current_sum;
                // 此时宽度必然不为0（否则面积不会增加），计算需要的高度
                double extra_h = needed_area / layer.width;
                return layer.y_start + extra_h;
            }
            current_sum += layer_area;
        }

        return prev_y; // 理论上不会到这里
    }
};