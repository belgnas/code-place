// #include <iostream>
// #include <vector>
// #include <algorithm>
// #include <string>
// using namespace std;

// // 核心修复：tie的参数改为nullptr，解决编译错误
// #define IOS ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr)

// // 方向数组（注释反了不影响编译，可按需修正，这里保留你的写法）
// const int move1[4][2] {
//     {1, 0},  // 上（实际是下，不影响逻辑）
//     {-1, 0}, // 下（实际是上）
//     {0, 1},  // 左（实际是右）
//     {0, -1}  // 右（实际是左）
// };

// // signed main()多数OJ支持，这里保留，无需改int
// signed main() {
//     IOS; // 现在编译无错
    
//     int t;
//     cin >> t;
//     while (t--) {
//         int n, m;
//         cin >> n >> m;
//         vector<string> arr(n); // 修复：移除冗余的""初始化
//         for (int i = 0; i < n; i++) {
//             cin >> arr[i];
//         }
        
//         vector<string> res(n, string(m, 'Y'));
//         for (int i = 0; i < n; i++) {
//             for (int j = 0; j < m; j++) {
//                 bool flat = false; // true=满足条件，输出Y
//                 for (int mv1 = 0; mv1 < 4; mv1++) {
//                     // 计算当前点的相邻点p(px,py)，保存原始坐标（核心修复：不修改x/y）
//                     int px = i + move1[mv1][0];
//                     int py = j + move1[mv1][1];
                    
//                     // 越界判断（已修复分号问题）
//                     if (px < 0 || px >= n || py < 0 || py >= m) {
//                         continue;
//                     }
                    
//                     // 条件1：有相邻点相同，长度2回文，直接Y
//                     if (arr[px][py] == arr[i][j]) {
//                         flat = true;
//                         break;
//                     }
                    
//                     // 遍历p的4个邻居q，判断长度3回文
//                     for (int mv2 = 0; mv2 < 4; mv2++) {
//                         // 核心修复：基于p的原始坐标计算q，不叠加修改
//                         int qx = px + move1[mv2][0];
//                         int qy = py + move1[mv2][1];
                        
//                         if (qx < 0 || qx >= n || qy < 0 || qy >= m) {
//                             continue;
//                         }
//                         // q不能是起点(i,j)，且值相同 → 长度3回文
//                         if (arr[qx][qy] == arr[i][j] && (qx != i || qy != j)) {
//                             flat = true;
//                             goto end_check; // 跳出所有循环
//                         }
//                     }
//                 }
//             end_check: // 修复：goto标记放在循环内，语法正确
//                 if (!flat) { // 无满足条件的路径，输出N
//                     res[i][j] = 'N';
//                 }
//             }
//         }
//         // 核心修复：输出移到外层，每组数据处理完后只输出一次
//         for (const string& s : res) {
//             cout << s << '\n'; // 修复：endl→'\n'，避免超时
//         }
//     }
//     return 0;
// }


// #include <iostream>
// #include <vector>
// #include <string>
// #include <numeric>

// using namespace std;

// #define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
// #define endl '\n'

// // 并查集结构
// struct DSU {
//     vector<int> parent;
//     vector<int> size;
//     // 辅助数组：记录该连通块接触了多少个不同的异色邻居
//     vector<int> touch_count;
//     // 辅助数组：记录上一次接触的异色邻居ID，防止重复计数同一个点
//     vector<int> last_touched_node;

//     DSU(int n) {
//         parent.resize(n);
//         iota(parent.begin(), parent.end(), 0);
//         size.assign(n, 1);
//         touch_count.assign(n, 0);
//         last_touched_node.assign(n, -1);
//     }

//     int find(int x) {
//         if (parent[x] == x) return x;
//         return parent[x] = find(parent[x]);
//     }

//     void unite(int x, int y) {
//         int rootX = find(x);
//         int rootY = find(y);
//         if (rootX != rootY) {
//             parent[rootX] = rootY;
//             size[rootY] += size[rootX];
//         }
//     }
// };

// const int moves[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

// void solve() {
//     int n, m;
//     cin >> n >> m;
//     vector<string> grid(n);
//     for (int i = 0; i < n; i++) {
//         cin >> grid[i];
//     }

//     // 将二维坐标转换为一维ID: id = i * m + j
//     int total_nodes = n * m;
//     DSU dsu(total_nodes);

//     // 第一步：构建同色连通块
//     for (int i = 0; i < n; i++) {
//         for (int j = 0; j < m; j++) {
//             int u = i * m + j;
//             for (int k = 0; k < 4; k++) {
//                 int ni = i + moves[k][0];
//                 int nj = j + moves[k][1];
//                 if (ni >= 0 && ni < n && nj >= 0 && nj < m) {
//                     int v = ni * m + nj;
//                     // 如果颜色相同，合并
//                     if (grid[i][j] == grid[ni][nj]) {
//                         dsu.unite(u, v);
//                     }
//                 }
//             }
//         }
//     }

//     // 第二步：统计每个连通块接触了多少个不同的异色点
//     // 遍历所有相邻的【异色】边 (u, v)
//     for (int i = 0; i < n; i++) {
//         for (int j = 0; j < m; j++) {
//             int u = i * m + j;
//             for (int k = 0; k < 4; k++) {
//                 int ni = i + moves[k][0];
//                 int nj = j + moves[k][1];
//                 if (ni >= 0 && ni < n && nj >= 0 && nj < m) {
//                     int v = ni * m + nj;
//                     if (grid[i][j] != grid[ni][nj]) {
//                         // grid[i][j] (点u) 是 grid[ni][nj] (点v) 的一个异色邻居
//                         // 我们要给 v 所在的连通块增加计数
//                         int rootV = dsu.find(v);
                        
//                         // 如果这个连通块上次记录的不是点 u，说明这是个新的异色邻居
//                         if (dsu.last_touched_node[rootV] != u) {
//                             dsu.touch_count[rootV]++;
//                             dsu.last_touched_node[rootV] = u;
//                         }
//                     }
//                 }
//             }
//         }
//     }

//     // 第三步：输出结果
//     for (int i = 0; i < n; i++) {
//         string res_row = "";
//         for (int j = 0; j < m; j++) {
//             int u = i * m + j;
//             int root = dsu.find(u);

//             // 情况1: 自身所在的同色连通块大小 > 1 (即存在相邻相同字符，"00" 或 "11")
//             if (dsu.size[root] > 1) {
//                 res_row += 'Y';
//             } 
//             else {
//                 // 情况2: 是孤立点，检查是否可以通过相邻的异色连通块到达另一个同色点
//                 // 只要相邻的任意一个异色连通块接触的同色点数量 >= 2 (其中一个是自己，另一个是目标)
//                 bool possible = false;
//                 for (int k = 0; k < 4; k++) {
//                     int ni = i + moves[k][0];
//                     int nj = j + moves[k][1];
//                     if (ni >= 0 && ni < n && nj >= 0 && nj < m) {
//                         int v = ni * m + nj;
//                         // 必定是异色，因为如果是同色，size早就>1了
//                         int rootV = dsu.find(v);
//                         // 如果邻居所在的异色连通块连接了至少2个同色点(自己和其他人)
//                         if (dsu.touch_count[rootV] >= 2) {
//                             possible = true;
//                             break;
//                         }
//                     }
//                 }
//                 if (possible) res_row += 'Y';
//                 else res_row += 'N';
//             }
//         }
//         cout << res_row << endl;
//     }
// }

// signed main() {
//     IOS;
//     int t;
//     cin >> t;
//     while (t--) {
//         solve();
//     }
//     return 0;
// }


#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
// 引入队列用于BFS
#include <queue> 

using namespace std;

#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
#define endl '\n'

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
        int n, m;
        cin >> n >> m;
        
        vector<string> arr(n);  
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
        }
        
        // --- 修改开始 ---
        
        // 1. 标记连通块并计算每个块的大小
        // ids[i][j] 存储 (i,j) 属于哪个连通块的编号
        vector<vector<int>> ids(n, vector<int>(m, -1));
        vector<int> comp_size; // 存储每个连通块的大小
        int comp_cnt = 0;      // 连通块总数
        
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                if(ids[i][j] == -1){
                    // 开始 BFS 标记连通块
                    int current_id = comp_cnt++;
                    int size = 0;
                    queue<pair<int,int>> q;
                    q.push({i, j});
                    ids[i][j] = current_id;
                    
                    while(!q.empty()){
                        pair<int,int> curr = q.front();
                        q.pop();
                        size++;
                        int cx = curr.first;
                        int cy = curr.second;
                        
                        for(int k=0; k<4; k++){
                            int nx = cx + move1[k][0];
                            int ny = cy + move1[k][1];
                            if(nx >=0 && nx < n && ny >=0 && ny < m && 
                               ids[nx][ny] == -1 && arr[nx][ny] == arr[cx][cy]){
                                ids[nx][ny] = current_id;
                                q.push({nx, ny});
                            }
                        }
                    }
                    comp_size.push_back(size);
                }
            }
        }
        
        // 2. 统计每个连通块接触了多少个 *不同* 的异色点
        // touches[k] 表示第 k 个连通块接触了多少个不同的异色点
        vector<int> touches(comp_cnt, 0);
        // last_seen[k] 记录第 k 个连通块上一次是被哪个点接触的（防止同一个点重复计数）
        vector<int> last_seen(comp_cnt, -1);
        
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                // 把二维坐标转成一维数字作为唯一标识
                int u = i * m + j; 
                
                for(int k = 0; k < 4; k++){
                    int ni = i + move1[k][0];
                    int nj = j + move1[k][1];
                    
                    // 如果邻居在界内且颜色不同
                    if(ni >= 0 && ni < n && nj >= 0 && nj < m && arr[ni][nj] != arr[i][j]){
                        int neighbor_comp_id = ids[ni][nj];
                        // 如果这个异色连通块还没记录过当前点 u
                        if(last_seen[neighbor_comp_id] != u){
                            touches[neighbor_comp_id]++;
                            last_seen[neighbor_comp_id] = u;
                        }
                    }
                }
            }
        }
        
        // 3. 生成结果
        vector<string> res(n, string(m, ' '));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                int my_id = ids[i][j];
                
                // 情况1: 自己所在的连通块大小 > 1 (即有相邻同色，如 "00" 或 "11")
                if(comp_size[my_id] > 1){
                    res[i][j] = 'Y';
                } else {
                    // 情况2: 自己是孤立点，看周围的异色连通块是否连接了 >= 2 个同色点
                    // (其中一个是自己，另一个是远处的同色点)
                    bool ok = false;
                    for(int k=0; k<4; k++){
                        int ni = i + move1[k][0];
                        int nj = j + move1[k][1];
                        if(ni >= 0 && ni < n && nj >= 0 && nj < m){
                            // 必定是异色，因为如果是同色，情况1就满足了
                            int neighbor_id = ids[ni][nj];
                            if(touches[neighbor_id] >= 2){
                                ok = true;
                                break;
                            }
                        }
                    }
                    res[i][j] = ok ? 'Y' : 'N';
                }
            }
        }
        // --- 修改结束 ---

        for (int i = 0; i < n; i++) {
            cout << res[i] << endl;
        }
    }
    
    return 0;
}