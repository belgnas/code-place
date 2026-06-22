// STL 容器 (4) — 无序容器 + 适配器
//
// 【无序关联容器】unordered_set / unordered_map
//   - 底层：哈希表（Hash Table）
//   - 插入/删除/查找：平均 O(1)，最坏 O(n)（哈希冲突）
//   - 元素不排序！遍历顺序不可预测
//   - 自定义类型做 key 需要提供 hash 函数 + == 运算符
//
//   unordered_set  vs  set:
//   - set:    有序，O(log n)，基于红黑树，内存开销较小
//   - unordered_set: 无序，O(1) 平均，基于哈希表，内存开销较大
//   - 不需要排序 → 用 unordered 版本更快
//
// 【容器适配器】stack / queue / priority_queue
//   - 适配器 = 包装底层容器，提供受限的接口
//   - stack:   后进先出（LIFO），默认底层用 deque
//   - queue:   先进先出（FIFO），默认底层用 deque
//   - priority_queue: 每次取最大（或最小）元素，默认底层用 vector


#include<iostream>
#include<string>
#include<unordered_set>
#include<unordered_map>
#include<set>         // 用于对比
#include<map>         // 用于对比
#include<stack>
#include<queue>       // 包含 queue 和 priority_queue
#include<vector>
#include<ctime>
using namespace std;


// ==================== 第一部分：unordered_set ====================

void test01_unordered_set()
{
    cout << "\n========== unordered_set 基础 ==========" << endl;

    unordered_set<int> us = {3, 1, 4, 1, 5, 9, 2, 6};
    // 自动去重，但顺序不可预测（哈希表顺序）

    cout << "unordered_set 内容: ";
    for (int x : us) cout << x << " ";
    cout << "\n  (顺序不可预测，取决于 hash 值)" << endl;

    // ---- 基本操作和 set 一样 ----
    us.insert(7);
    auto it = us.find(5);
    if (it != us.end())
        cout << "找到: " << *it << endl;

    us.erase(3);
    cout << "erase(3) 后: ";
    for (int x : us) cout << x << " ";
    cout << endl;

    // ---- 哈希相关 ----
    cout << "\n桶信息:" << endl;
    cout << "  bucket_count = " << us.bucket_count() << endl;   // 桶的数量
    cout << "  load_factor  = " << us.load_factor() << endl;    // 负载因子 = size/bucket_count
    cout << "  max_load_factor = " << us.max_load_factor() << endl; // 最大负载因子（默认 1.0）

    // rehash(n): 设置桶数（至少 n 个）
    // reserve(n): 设置容量（至少能存 n 个元素不 rehash）
    us.reserve(100);
    cout << "  reserve(100) 后 bucket_count = " << us.bucket_count() << endl;

    // ---- 自定义类型做 key ----
    // 需要提供两个东西：hash 函数 + operator==
    struct Point
    {
        int x, y;

        // 必须定义 == ，哈希表需要判断 key 是否相同
        bool operator==(const Point& other) const
        {
            return x == other.x && y == other.y;
        }
    };

    // 自定义 hash 函数（用仿函数特化 std::hash）
    // 另一种方式：写一个仿函数传给 unordered_set
    struct PointHash
    {
        size_t operator()(const Point& p) const
        {
            // 简单 hash: x * 31 + y (类似 Java String 的 hash)
            return hash<int>()(p.x) * 31 + hash<int>()(p.y);
        }
    };

    unordered_set<Point, PointHash> points;
    points.insert({1, 2});
    points.insert({3, 4});
    points.insert({1, 2});               // 重复，不会插入

    cout << "\nPoint 集合大小: " << points.size() << endl;
}


// ==================== 第二部分：unordered_map ====================

void test02_unordered_map()
{
    cout << "\n========== unordered_map 基础 ==========" << endl;

    // 和 map 接口几乎一样，只是不排序
    unordered_map<string, int> um;

    um["Alice"] = 85;
    um["Bob"]   = 92;
    um["Carol"] = 78;
    um.insert({"David", 88});

    // 遍历（顺序不可预测）
    cout << "unordered_map 内容:" << endl;
    for (const auto& kv : um)
    {
        cout << "  " << kv.first << " → " << kv.second << endl;
    }

    // 查找 O(1) 平均
    auto it = um.find("Bob");
    if (it != um.end())
        cout << "\n找到 Bob: " << it->second << endl;
}

void test03_ordered_vs_unordered()
{
    cout << "\n========== map vs unordered_map 性能对比 ==========" << endl;
    const int N = 100000;

    // 插入
    {
        clock_t start, end;

        start = clock();
        map<int, int> m;
        for (int i = 0; i < N; i++)
            m.insert({i, i * 2});
        end = clock();
        cout << "插入 " << N << " 条:" << endl;
        cout << "  map:           " << (double)(end - start) / CLOCKS_PER_SEC
             << "s (O(log n))" << endl;

        start = clock();
        unordered_map<int, int> um;
        um.reserve(N);                   // 预分配空间，减少 rehash
        for (int i = 0; i < N; i++)
            um.insert({i, i * 2});
        end = clock();
        cout << "  unordered_map: " << (double)(end - start) / CLOCKS_PER_SEC
             << "s (O(1) 平均)" << endl;
    }

    // 查找
    {
        clock_t start, end;

        map<int, int> m;
        unordered_map<int, int> um;
        for (int i = 0; i < N; i++)
        {
            m[i] = i;
            um[i] = i;
        }

        start = clock();
        long long sum1 = 0;
        for (int i = 0; i < N; i++)
        {
            auto it = m.find(i);
            if (it != m.end()) sum1 += it->second;
        }
        end = clock();
        cout << "\n查找 " << N << " 次:" << endl;
        cout << "  map:           " << (double)(end - start) / CLOCKS_PER_SEC << "s" << endl;

        start = clock();
        long long sum2 = 0;
        for (int i = 0; i < N; i++)
        {
            auto it = um.find(i);
            if (it != um.end()) sum2 += it->second;
        }
        end = clock();
        cout << "  unordered_map: " << (double)(end - start) / CLOCKS_PER_SEC << "s" << endl;
    }

    cout << "\n结论: 不需要排序时，unordered_map 明显更快。" << endl;
    cout << "      但需要有序遍历/范围查询（lower_bound）时只能用 map。" << endl;
}


// ==================== 第三部分：stack ====================

void test04_stack()
{
    cout << "\n========== stack（栈） ==========" << endl;

    // 默认底层容器是 deque（也可以换成 vector 或 list）
    stack<int> st;

    // 基本操作
    st.push(1);                          // 入栈
    st.push(2);
    st.push(3);

    cout << "栈顶 = " << st.top() << endl; // 3
    cout << "大小 = " << st.size() << endl;

    st.pop();                            // 出栈（不返回值）
    cout << "pop 后栈顶 = " << st.top() << endl; // 2

    // 遍历栈（只能逐个 pop）
    cout << "逐个出栈: ";
    while (!st.empty())
    {
        cout << st.top() << " ";
        st.pop();
    }
    cout << endl;

    // ---- 应用：括号匹配 ----
    cout << "\n应用: 括号匹配" << endl;
    string expr = "{[()()]}";

    stack<char> bracketStack;
    bool valid = true;

    for (char ch : expr)
    {
        if (ch == '(' || ch == '[' || ch == '{')
        {
            bracketStack.push(ch);
        }
        else if (ch == ')' || ch == ']' || ch == '}')
        {
            if (bracketStack.empty())
            {
                valid = false;
                break;
            }
            char top = bracketStack.top();
            bracketStack.pop();
            if ((ch == ')' && top != '(') ||
                (ch == ']' && top != '[') ||
                (ch == '}' && top != '{'))
            {
                valid = false;
                break;
            }
        }
    }

    if (!bracketStack.empty()) valid = false;

    cout << "表达式 \"" << expr << "\" "
         << (valid ? "合法 ✓" : "不合法 ✗") << endl;
}


// ==================== 第四部分：queue ====================

void test05_queue()
{
    cout << "\n========== queue（队列） ==========" << endl;

    queue<int> q;

    q.push(1);                           // 入队
    q.push(2);
    q.push(3);

    cout << "队首 = " << q.front() << endl; // 1
    cout << "队尾 = " << q.back()  << endl; // 3
    cout << "大小 = " << q.size()  << endl;

    q.pop();                             // 出队（队首）
    cout << "pop 后队首 = " << q.front() << endl;

    // ---- 应用：BFS 宽度优先搜索 ----
    cout << "\n应用: BFS 遍历" << endl;

    // 简单图的邻接表
    vector<vector<int>> graph =
    {
        {1, 2},     // 节点 0 的邻居
        {0, 3, 4},  // 节点 1 的邻居
        {0, 4},     // 节点 2 的邻居
        {1},        // 节点 3 的邻居
        {1, 2}      // 节点 4 的邻居
    };

    vector<bool> visited(graph.size(), false);
    queue<int> bfsQ;

    // 从节点 0 开始 BFS
    bfsQ.push(0);
    visited[0] = true;

    cout << "BFS 遍历顺序: ";
    while (!bfsQ.empty())
    {
        int cur = bfsQ.front();
        bfsQ.pop();
        cout << cur << " ";

        for (int neighbor : graph[cur])
        {
            if (!visited[neighbor])
            {
                visited[neighbor] = true;
                bfsQ.push(neighbor);
            }
        }
    }
    cout << endl;
}


// ==================== 第五部分：priority_queue ====================

void test06_priority_queue()
{
    cout << "\n========== priority_queue（优先队列） ==========" << endl;

    // ---- 默认：大顶堆（最大的在顶上） ----
    priority_queue<int> pq;
    pq.push(3);
    pq.push(1);
    pq.push(5);
    pq.push(2);

    cout << "大顶堆 逐个弹出: ";
    while (!pq.empty())
    {
        cout << pq.top() << " ";         // 每次取最大
        pq.pop();
    }
    cout << endl;

    // ---- 小顶堆 ----
    // 方式 1: greater<int>
    priority_queue<int, vector<int>, greater<int>> minPq;
    minPq.push(3);
    minPq.push(1);
    minPq.push(5);
    minPq.push(2);

    cout << "小顶堆 逐个弹出: ";
    while (!minPq.empty())
    {
        cout << minPq.top() << " ";      // 每次取最小
        minPq.pop();
    }
    cout << endl;

    // ---- 自定义比较（存 pair，按第二个元素排序） ----
    // 小顶堆: 按 pair.second 从小到大
    using PII = pair<int, int>;

    auto cmp = [](const PII& a, const PII& b)
    {
        return a.second > b.second;      // 注意：greater 才能得到小顶堆！
        // priority_queue 的比较方向和 sort 相反：
        // return true → a 排在 b 后面（优先级更低）
    };

    priority_queue<PII, vector<PII>, decltype(cmp)> customPq(cmp);
    customPq.push({1, 50});
    customPq.push({2, 10});
    customPq.push({3, 30});

    // 也可以直接用 greater<PII>（按 first 比较）
    // priority_queue<PII, vector<PII>, greater<PII>>

    cout << "自定义比较 逐个弹出: ";
    while (!customPq.empty())
    {
        auto top = customPq.top();
        cout << "{" << top.first << "," << top.second << "} ";
        customPq.pop();
    }
    cout << endl;

    // ---- 应用：Top-K 问题 ----
    cout << "\n应用: Top-3 最小元素" << endl;
    vector<int> arr = {7, 10, 4, 3, 20, 15, 8, 1, 12};
    int k = 3;

    // 大顶堆维护最小的 k 个
    priority_queue<int> maxHeap;
    for (int x : arr)
    {
        maxHeap.push(x);
        if ((int)maxHeap.size() > k)
        {
            maxHeap.pop();               // 弹出最大的，保留小的
        }
    }

    cout << "最小的 " << k << " 个元素: ";
    while (!maxHeap.empty())
    {
        cout << maxHeap.top() << " ";
        maxHeap.pop();
    }
    cout << endl;

    // 注：如果要 Top-K 最大元素，用小顶堆
}


int main()
{
    cout << "========================================" << endl;
    cout << "|  STL 容器(4) — 无序容器与适配器     |" << endl;
    cout << "========================================" << endl;

    // 无序容器
    test01_unordered_set();
    test02_unordered_map();
    test03_ordered_vs_unordered();

    // 适配器
    test04_stack();
    test05_queue();
    test06_priority_queue();

    system("pause");
    return 0;
}

// 完结撒花*
