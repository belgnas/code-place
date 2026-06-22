// STL 容器 (2) — deque 与 list
//
// 【deque】双端队列（double-ended queue）
//   - 分段连续存储（不是一整块连续内存！）
//   - 头尾插入/删除 O(1)，中间插入 O(n)
//   - 支持随机访问（比 vector 稍慢，多一次间接寻址）
//   - 扩容时不需要整体复制 → 不会让迭代器全部失效
//
// 【deque vs vector】
//   - vector: 一整块连续内存，尾插 O(1)，头插 O(n)
//   - deque:  分段连续，头尾插 O(1)，内存利用率稍低
//   - 选 deque 的理由：需要在头部频繁操作
//
// 【list】双向链表
//   - 非连续存储，每个节点有 prev 和 next 指针
//   - 任意位置插入/删除 O(1)（已有迭代器的前提下）
//   - 不支持随机访问（没有 operator[]）
//   - 额外内存开销：每个节点 2 个指针（前驱+后继）
//
// 【list vs vector/deque】
//   - 频繁随机访问 → vector
//   - 频繁头尾操作 → deque
//   - 频繁中间插入/删除 → list
//   - 大多数情况 vector 是最优选择（CPU 缓存友好）


#include<iostream>
#include<deque>
#include<list>
#include<vector>    // 用于性能对比
#include<ctime>     // clock()
#include<algorithm> // sort, find
using namespace std;


// ==================== 第一部分：deque ====================

void test01_deque_basics()
{
    cout << "\n========== deque 基础操作 ==========" << endl;

    // ---- 构造 ----
    deque<int> d1;                       // 空 deque
    deque<int> d2(5);                    // 5 个 0
    deque<int> d3(5, 10);                // 5 个 10
    deque<int> d4 = {1, 2, 3, 4, 5};    // 初始化列表

    // ---- 头尾操作（deque 的独门优势！） ----
    deque<int> d = {2, 3, 4};

    // push_front / pop_front — vector 没有这些！
    d.push_front(1);                     // 头部插入
    d.push_back(5);                      // 尾部插入
    cout << "头尾插入后: ";
    for (int x : d) cout << x << " ";    // {1, 2, 3, 4, 5}
    cout << endl;

    d.pop_front();                       // 头部删除
    d.pop_back();                        // 尾部删除
    cout << "头尾删除后: ";
    for (int x : d) cout << x << " ";    // {2, 3, 4}
    cout << endl;

    // ---- 访问元素 ----
    cout << "\nd[0]     = " << d[0] << endl;      // 支持随机访问（但比 vector 慢一点）
    cout << "d.at(1)  = " << d.at(1) << endl;
    cout << "d.front() = " << d.front() << endl;
    cout << "d.back()  = " << d.back() << endl;

    // ---- 中间插入（和 vector 一样 O(n)） ----
    d.insert(d.begin() + 1, 99);
    cout << "\ninsert(begin+1, 99): ";
    for (int x : d) cout << x << " ";
    cout << endl;

    // ---- 扩容特点 ----
    // deque 扩容分配新的 block，不需要复制所有旧元素
    // 因此 insert 不会让所有迭代器失效，只会让插入点附近的失效
    cout << "\n[deque扩容] 不需要整体复制，迭代器不会全部失效" << endl;
}

void test02_deque_use_cases()
{
    cout << "\n========== deque 应用场景 ==========" << endl;

    // 场景 1：滑动窗口（经典算法题）
    // 维护一个大小固定的窗口，窗口滑动时：去掉头部 + 添加尾部
    cout << "场景1: 滑动窗口" << endl;
    deque<int> window;
    int arr[] = {1, 3, -1, -3, 5, 3, 6, 7};
    int k = 3;  // 窗口大小

    for (int i = 0; i < 8; i++)
    {
        window.push_back(arr[i]);
        if ((int)window.size() > k)
        {
            window.pop_front();
        }
        if ((int)window.size() == k)
        {
            cout << "  窗口 [";
            for (int x : window) cout << x << " ";
            cout << "]" << endl;
        }
    }

    // 场景 2：用 deque 实现单调队列
    // 求滑动窗口最大值
    // (这里只演示 deque 用法，完整单调队列见算法模板)
    cout << "\n场景2: deque 实现单调队列（存下标）" << endl;
    deque<int> dq;
    int nums[] = {1, 3, -1, -3, 5, 3, 6, 7};
    k = 3;

    for (int i = 0; i < 8; i++)
    {
        // 维护递减队列：新元素进来，把队尾比它小的都弹出
        while (!dq.empty() && nums[dq.back()] <= nums[i])
            dq.pop_back();
        dq.push_back(i);

        // 移除窗口外的元素
        if (!dq.empty() && dq.front() <= i - k)
            dq.pop_front();

        if (i >= k - 1)
            cout << "  窗口 max = " << nums[dq.front()] << endl;
    }
}


// ==================== 第二部分：list ====================

void test03_list_basics()
{
    cout << "\n========== list 基础操作 ==========" << endl;

    // ---- 构造 ----
    list<int> l1;                        // 空链表
    list<int> l2(5, 10);                 // 5 个 10
    list<int> l3 = {1, 2, 3, 4, 5};     // 初始化列表

    // ---- 头尾操作（和 deque 一样） ----
    list<int> l;
    l.push_back(3);
    l.push_back(4);
    l.push_front(2);
    l.push_front(1);

    cout << "链表内容: ";
    for (int x : l) cout << x << " ";    // {1, 2, 3, 4}
    cout << endl;

    // ---- 访问首尾（没有 operator[]！） ----
    cout << "l.front() = " << l.front() << endl;
    cout << "l.back()  = " << l.back()  << endl;
    // l[2]  ← 编译错误！list 不支持随机访问

    // ---- 插入和删除 ----
    // insert(pos, val): 在 pos 前插入，O(1)（已有迭代器）
    auto it = l.begin();
    ++it; ++it;                          // 指向 3（list 的迭代器只能 ++ 不能 +2）
    l.insert(it, 99);
    cout << "\n在 3 前插入 99: ";
    for (int x : l) cout << x << " ";    // {1, 2, 99, 3, 4}
    cout << endl;

    // erase(pos): 删除，O(1)
    // 注意：l.erase(it) 后 it 失效！要用返回值
    it = l.begin();
    ++it;                                // 指向 2
    it = l.erase(it);                    // 删除 2，返回下一个元素的迭代器
    cout << "删除 2 后: ";
    for (int x : l) cout << x << " ";
    cout << endl;

    // remove(val): 删除所有等于 val 的元素
    l.push_back(99);
    l.remove(99);                        // 删除所有 99（比 find+erase 方便！）
    cout << "remove(99) 后: ";
    for (int x : l) cout << x << " ";
    cout << endl;

    // ---- 特殊操作 ----
    // splice: 将另一个 list 的元素移动到指定位置（O(1)！）
    list<int> lA = {1, 2, 3};
    list<int> lB = {10, 20, 30};
    auto pos = lA.begin();
    ++pos;                               // 指向 lA 的 2
    lA.splice(pos, lB);                  // 把 lB 全部移到 lA 的 pos 前
    cout << "\nsplice 后 lA: ";
    for (int x : lA) cout << x << " ";
    cout << "| lB 是否为空: " << (lB.empty() ? "是" : "否") << endl;
    // splice 是 O(1) 的，只修改指针，没有拷贝！

    // reverse: 反转链表
    lA.reverse();
    cout << "reverse 后: ";
    for (int x : lA) cout << x << " ";
    cout << endl;

    // unique: 删除连续重复元素（需要先排序）
    list<int> lC = {1, 1, 2, 2, 2, 3, 1, 1};
    lC.unique();                         // 删除连续重复 → {1, 2, 3, 1}
    cout << "\nunique 后: ";
    for (int x : lC) cout << x << " ";
    cout << endl;

    // sort: list 自己的 sort（不能用 std::sort，因为 list 没有随机访问）
    list<int> lD = {5, 2, 8, 1, 9, 3};
    lD.sort();                           // list::sort（归并排序，稳定）
    cout << "sort 后: ";
    for (int x : lD) cout << x << " ";
    cout << endl;

    // merge: 合并两个有序链表
    list<int> lX = {1, 3, 5, 7};
    list<int> lY = {2, 4, 6, 8};
    lX.merge(lY);                        // 合并后 lY 为空
    cout << "merge 后: ";
    for (int x : lX) cout << x << " ";
    cout << endl;
}


// ==================== 第三部分：性能对比 ====================

void test04_performance_compare()
{
    cout << "\n========== 性能对比：vector vs deque vs list ==========" << endl;
    const int N = 100000;

    // --- 尾部插入对比 ---
    {
        clock_t start, end;

        start = clock();
        vector<int> v;
        for (int i = 0; i < N; i++) v.push_back(i);
        end = clock();
        cout << "尾部插入 (N=" << N << "):" << endl;
        cout << "  vector: " << (double)(end - start) / CLOCKS_PER_SEC << "s" << endl;

        start = clock();
        deque<int> d;
        for (int i = 0; i < N; i++) d.push_back(i);
        end = clock();
        cout << "  deque:  " << (double)(end - start) / CLOCKS_PER_SEC << "s" << endl;

        start = clock();
        list<int> l;
        for (int i = 0; i < N; i++) l.push_back(i);
        end = clock();
        cout << "  list:   " << (double)(end - start) / CLOCKS_PER_SEC << "s" << endl;
    }

    // --- 头部插入对比 ---
    {
        clock_t start, end;
        cout << "\n头部插入 (N=" << N/10 << "):" << endl;

        start = clock();
        deque<int> d;
        for (int i = 0; i < N/10; i++) d.push_front(i);
        end = clock();
        cout << "  deque: " << (double)(end - start) / CLOCKS_PER_SEC << "s (O(1))" << endl;

        start = clock();
        list<int> l;
        for (int i = 0; i < N/10; i++) l.push_front(i);
        end = clock();
        cout << "  list:  " << (double)(end - start) / CLOCKS_PER_SEC << "s (O(1))" << endl;

        // vector 没有 push_front！用 insert(begin) 模拟
        start = clock();
        vector<int> v;
        for (int i = 0; i < N/10; i++) v.insert(v.begin(), i);
        end = clock();
        cout << "  vector:" << (double)(end - start) / CLOCKS_PER_SEC
             << "s (O(n) — 每次都要移动所有元素！)" << endl;
    }

    // --- 随机访问对比 ---
    {
        clock_t start, end;
        const int M = 10000;

        vector<int> v(N);
        deque<int>  d(N);

        start = clock();
        long long sum1 = 0;
        for (int i = 0; i < M; i++)
        {
            for (int j = 0; j < N; j++)
                sum1 += v[j];            // O(1) 随机访问
        }
        end = clock();
        cout << "\n随机访问 (M=" << M << " 次遍历):" << endl;
        cout << "  vector: " << (double)(end - start) / CLOCKS_PER_SEC << "s" << endl;

        start = clock();
        long long sum2 = 0;
        for (int i = 0; i < M; i++)
        {
            for (int j = 0; j < N; j++)
                sum2 += d[j];            // O(1) 但多一次间接寻址
        }
        end = clock();
        cout << "  deque:  " << (double)(end - start) / CLOCKS_PER_SEC << "s" << endl;

        // list 无法随机访问
        cout << "  list:   不支持 operator[]" << endl;
    }
}

void test05_selection_guide()
{
    cout << "\n========== 容器选型指南 ==========" << endl;
    cout << "┌─────────────┬──────────┬──────────┬──────────┐" << endl;
    cout << "│  操作        │ vector   │ deque    │ list     │" << endl;
    cout << "├─────────────┼──────────┼──────────┼──────────┤" << endl;
    cout << "│  随机访问    │ O(1) *   │ O(1)     │ ✗ 不支持  │" << endl;
    cout << "│  尾部插入    │ O(1)*    │ O(1)     │ O(1)     │" << endl;
    cout << "│  头部插入    │ O(n)     │ O(1) *   │ O(1)     │" << endl;
    cout << "│  中间插入    │ O(n)     │ O(n)     │ O(1) *   │" << endl;
    cout << "│  内存连续性  │ 连续 *   │ 分段连续  │ 非连续    │" << endl;
    cout << "│  迭代器失效  │ 扩容全失 │ 部分失效  │ 不失效 *  │" << endl;
    cout << "│  内存开销    │ 最小     │ 中等     │ 大(2指针) │" << endl;
    cout << "└─────────────┴──────────┴──────────┴──────────┘" << endl;
    cout << "\n* = 该场景下最优选择" << endl;
    cout << "* vector 尾部插入 O(1) 是均摊的，扩容时单次为 O(n)" << endl;
    cout << "\n默认选 vector，特殊需求再换。" << endl;
}


int main()
{
    cout << "========================================" << endl;
    cout << "|     STL 容器(2) — deque 与 list     |" << endl;
    cout << "========================================" << endl;

    // deque
    test01_deque_basics();
    test02_deque_use_cases();

    // list
    test03_list_basics();

    // 性能对比
    test04_performance_compare();
    test05_selection_guide();

    system("pause");
    return 0;
}

// 完结撒花*
