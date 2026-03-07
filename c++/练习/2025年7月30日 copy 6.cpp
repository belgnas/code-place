#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 偏移量：处理负差值（神气总和-魔气总和可能为负）
const int OFFSET = 10000;
// 最大可能差值范围：-10000 ~ 10000 → 映射为0 ~ 20000
const int MAX_RANGE = 20000;

int main() {
    int n;
    cin >> n;
    
    vector<int> a(n), b(n);
    for (int i = 0; i < n; ++i) cin >> a[i];  // 神气数组
    for (int i = 0; i < n; ++i) cin >> b[i];  // 魔气数组
    
    // dp[i]表示：神气总和-魔气总和 = (i - OFFSET) 时的最大神气总和
    // 初始状态：不选任何草，差值为0，神气总和为0
    vector<int> dp(MAX_RANGE + 1, -1);
    dp[OFFSET] = 0;  // 差值0对应的索引是OFFSET
    
    for (int i = 0; i < n; ++i) {
        int ai = a[i];   // 当前草的神气
        int bi = b[i];   // 当前草的魔气
        int delta = ai - bi;  // 选当前草后，差值的变化量
        
        // 临时数组：保存选当前草后的状态（避免重复选择同一株草）
        vector<int> new_dp = dp;
        
        // 遍历所有可能的前态差值
        for (int prev_idx = 0; prev_idx <= MAX_RANGE; ++prev_idx) {
            // 前态不可达，跳过
            if (dp[prev_idx] == -1) continue;
            
            // 计算前态的实际差值
            int prev_diff = prev_idx - OFFSET;
            // 选当前草后的新差值
            int new_diff = prev_diff + delta;
            // 新差值对应的索引（确保在有效范围）
            int new_idx = new_diff + OFFSET;
            if (new_idx < 0 || new_idx > MAX_RANGE) continue;
            
            // 选当前草后的神气总和 = 前态神气总和 + 当前草的神气
            int new_a_sum = dp[prev_idx] + ai;
            // 更新新状态（取更大的神气总和）
            if (new_a_sum > new_dp[new_idx]) {
                new_dp[new_idx] = new_a_sum;
            }
        }
        
        // 更新dp为包含当前草选择结果的新状态
        dp = move(new_dp);
    }
    
    // 最大战力 = 差值为0时的神气总和（此时神气=魔气），至少为0（不选任何草）
    cout << max(dp[OFFSET], 0) << endl;
    
    return 0;
}