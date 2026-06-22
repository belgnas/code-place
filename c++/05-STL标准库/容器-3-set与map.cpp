// STL 容器 (3) — set 与 map（有序关联容器）
//
// 【set】集合 — 元素唯一，自动排序
//   - 底层：红黑树（自平衡二叉搜索树）
//   - 插入/删除/查找：O(log n)
//   - 元素不可修改（修改会破坏排序），只能删了再插
//   - 默认从小到大排序（std::less）
//
// 【multiset】多重集合 — 允许重复元素
//
// 【map】映射（键值对）— key 唯一，按 key 排序
//   - 每个元素是 pair<const Key, Value>
//   - key 不可修改，value 可修改
//   - operator[]：如果 key 不存在 → 自动插入默认值！
//
// 【multimap】多重映射 — 允许重复 key


#include<iostream>
#include<set>
#include<map>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;


// ==================== 第一部分：set ====================

void test01_set_basics()
{
    cout << "\n========== set 基础操作 ==========" << endl;

    // ---- 构造 ----
    set<int> s1;                         // 空集合
    set<int> s2 = {3, 1, 4, 1, 5, 9};   // 初始化列表（重复的 1 只会保留一个）
    // 结果自动排序: {1, 3, 4, 5, 9}

    cout << "s2 内容（自动去重+排序）: ";
    for (int x : s2) cout << x << " ";
    cout << endl;

    // ---- 插入 ----
    set<int> s;
    s.insert(5);
    s.insert(2);
    s.insert(8);
    s.insert(2);                         // 重复插入 — 静默忽略！
    s.insert(1);

    // insert 返回 pair<iterator, bool>
    // iterator: 指向插入元素（或已存在元素）的迭代器
    // bool: true=插入成功, false=元素已存在
    auto result = s.insert(8);
    if (!result.second)
    {
        cout << "8 已存在，插入失败" << endl;
    }

    cout << "set 内容: ";
    for (int x : s) cout << x << " ";
    cout << endl;

    // ---- 查找 ----
    // find(key): 返回迭代器，找不到返回 end()
    auto it = s.find(5);
    if (it != s.end())
    {
        cout << "\n找到 " << *it << endl;
    }

    // count(key): 返回出现次数（对 set 只能是 0 或 1）
    cout << "s.count(5) = " << s.count(5) << endl;
    cout << "s.count(9) = " << s.count(9) << endl;

    // ---- 删除 ----
    s.erase(2);                          // 按值删除
    cout << "\nerase(2) 后: ";
    for (int x : s) cout << x << " ";
    cout << endl;

    // erase(iterator): 按迭代器删除（效率更高，不需要先查找）
    it = s.find(8);
    if (it != s.end())
    {
        s.erase(it);
    }
    cout << "erase(8) 后: ";
    for (int x : s) cout << x << " ";
    cout << endl;
}

void test02_set_advanced()
{
    cout << "\n========== set 高级操作 ==========" << endl;

    set<int> s = {1, 3, 5, 7, 9, 11, 13};

    // lower_bound(key): 第一个 >= key 的元素
    auto lb = s.lower_bound(6);
    cout << "lower_bound(6) = " << *lb << " (第一个 >= 6 的元素)" << endl;

    // upper_bound(key): 第一个 > key 的元素
    auto ub = s.upper_bound(7);
    cout << "upper_bound(7) = " << *ub << " (第一个 > 7 的元素)" << endl;

    // equal_range(key): 返回 pair<lower_bound, upper_bound>
    auto range = s.equal_range(7);
    cout << "equal_range(7): [" << *range.first << ", " << *range.second << ")" << endl;

    // ---- 自定义排序规则 ----
    // 默认是 less<int>（从小到大），改为 greater<int>（从大到小）
    set<int, greater<int>> s2 = {1, 3, 5, 7, 9};
    cout << "\n从大到小排序: ";
    for (int x : s2) cout << x << " ";
    cout << endl;

    // 自定义比较器（用仿函数）
    struct AbsCompare
    {
        bool operator()(int a, int b) const
        {
            return abs(a) < abs(b);      // 按绝对值排序
        }
    };
    set<int, AbsCompare> s3 = {1, -3, 5, -2, 4};
    cout << "按绝对值排序: ";
    for (int x : s3) cout << x << " ";
    cout << endl;
    // 注意：-3 和 3 的绝对值相同，后插入的会被视为重复而忽略

    // ---- set 存自定义类型 ----
    cout << "\nset 存自定义类型:" << endl;
    struct Student
    {
        string name;
        int    score;

        // set 需要比较运算符来确定元素顺序
        bool operator<(const Student& other) const
        {
            // 按成绩从高到低
            return score > other.score;
        }
    };

    set<Student> students;
    students.insert({"张三", 85});
    students.insert({"李四", 92});
    students.insert({"王五", 78});
    students.insert({"赵六", 92});       // 和"李四"同分 — 被视为重复！

    for (const auto& stu : students)
    {
        cout << "  " << stu.name << ": " << stu.score << endl;
    }
    cout << "  注意：赵六(92) 被忽略了，因为和李四同分。" << endl;
    cout << "  解决方案：用 multiset，或在比较函数中区分同分的人。" << endl;
}

void test03_multiset()
{
    cout << "\n========== multiset ==========" << endl;

    // multiset：允许重复元素
    multiset<int> ms = {1, 1, 2, 3, 5, 8};

    ms.insert(1);                        // 允许再插入一个 1
    cout << "multiset 内容: ";
    for (int x : ms) cout << x << " ";
    cout << endl;

    // count 可能有多个
    cout << "count(1) = " << ms.count(1) << endl;

    // erase(key): 删除所有等于 key 的元素！
    ms.erase(1);
    cout << "erase(1) 后（删除了所有 1）: ";
    for (int x : ms) cout << x << " ";
    cout << endl;

    // 只删一个：erase(iterator)
    ms.insert(3);
    ms.insert(3);
    auto it = ms.find(3);                // 找到第一个 3
    if (it != ms.end())
    {
        ms.erase(it);                    // 只删一个
    }
    cout << "erase(第一个3) 后: ";
    for (int x : ms) cout << x << " ";
    cout << endl;

    // 应用：multiset 维护动态中位数
    // (频繁插入删除时比排序数组高效)
}


// ==================== 第二部分：map ====================

void test04_map_basics()
{
    cout << "\n========== map 基础操作 ==========" << endl;

    // ---- 构造 ----
    map<string, int> m1;                 // 空 map
    map<string, int> m2 =
    {
        {"Alice", 85},
        {"Bob",   92},
        {"Carol", 78}
    };
    // key 按字典序排序: Alice, Bob, Carol

    // ---- 插入 ----
    map<int, string> m;

    // 方式 1：pair
    m.insert(pair<int, string>(1, "one"));

    // 方式 2：make_pair
    m.insert(make_pair(2, "two"));

    // 方式 3：直接用 {}（C++11）
    m.insert({3, "three"});

    // 方式 4：operator[]（最方便）
    m[4] = "four";
    m[5] = "five";

    // ⚠ operator[] 的秘密：如果 key 不存在，自动插入默认值！
    cout << "m[6] 的值为: \"" << m[6] << "\"" << endl;
    cout << "  m[6] 即使之前不存在，访问它也会创建！现在 m[6]=\"\" (空字符串)" << endl;

    // 遍历
    cout << "\nmap 内容 (按键自动排序):" << endl;
    for (const auto& kv : m)
    {
        cout << "  " << kv.first << " → \"" << kv.second << "\"" << endl;
    }

    // ---- 查找 ----
    // find(key): 返回迭代器
    auto it = m.find(3);
    if (it != m.end())
    {
        cout << "\n找到 key=3, value=\"" << it->second << "\"" << endl;
    }

    // count(key): 0 或 1（对 map 而言）
    cout << "count(3) = " << m.count(3) << endl;

    // ---- 修改 ----
    m[3] = "THREE";                      // 修改已存在的 value
    cout << "修改后 m[3] = \"" << m[3] << "\"" << endl;

    // ---- 删除 ----
    m.erase(4);                          // 按 key 删除
    cout << "erase(4) 后: ";
    for (const auto& kv : m) cout << "{" << kv.first << "} ";
    cout << endl;
}

void test05_map_advanced()
{
    cout << "\n========== map 进阶技巧 ==========" << endl;

    // ---- 技巧 1：at() vs operator[] ----
    map<string, int> m = {{"a", 1}, {"b", 2}};

    // operator[]: key 不存在时自动插入
    // cout << m["c"] << endl;           // 会插入 {"c", 0}！

    // at(): key 不存在时抛出异常（更安全）
    try
    {
        cout << "m.at(\"a\") = " << m.at("a") << endl;
        cout << "m.at(\"c\") = " << m.at("c") << endl; // 抛出 std::out_of_range
    }
    catch (const out_of_range& e)
    {
        cout << "  [!] at(\"c\") 抛出异常: " << e.what() << endl;
    }

    // ---- 技巧 2：检查 key 是否存在 ----
    // 方法 1: find
    if (m.find("a") != m.end())
        cout << "\"a\" 存在" << endl;

    // 方法 2: count (对 map 来说等价)
    if (m.count("b") > 0)
        cout << "\"b\" 存在" << endl;

    // 方法 3: contains (C++20，当前可能不支持)
    // if (m.contains("a")) ...

    // ---- 技巧 3：lower_bound / upper_bound ----
    map<int, string> m2 =
    {
        {1, "one"}, {3, "three"}, {5, "five"}, {7, "seven"}
    };

    auto lb = m2.lower_bound(4);
    cout << "\nlower_bound(4): " << lb->first << " → \"" << lb->second << "\"" << endl;

    // ---- 技巧 4：遍历时修改 value ----
    // key 不可修改（const），value 可修改
    for (auto& kv : m)
    {
        kv.second *= 10;                 // 修改 value
    }
    cout << "\nvalue * 10 后: ";
    for (const auto& kv : m) cout << "{" << kv.first << ":" << kv.second << "} ";
    cout << endl;

    // ---- 技巧 5：map 存自定义 key ----
    struct Point
    {
        int x, y;
        // 必须定义 operator<，map 需要排序
        bool operator<(const Point& other) const
        {
            if (x != other.x) return x < other.x;
            return y < other.y;
        }
    };

    map<Point, string> grid;
    grid[{0, 0}] = "原点";
    grid[{1, 2}] = "A点";
    grid[{3, 1}] = "B点";
    cout << "\nmap 自定义 key:" << endl;
    for (const auto& kv : grid)
    {
        cout << "  (" << kv.first.x << ", " << kv.first.y << ") → "
             << kv.second << endl;
    }
}

void test06_map_practice()
{
    cout << "\n========== map 实战练习 ==========" << endl;

    // 练习 1：单词频率统计
    cout << "练习1: 单词频率统计" << endl;
    string text = "apple banana apple orange banana apple";
    map<string, int> wordCount;

    // 简单的分割和统计
    string word;
    for (char ch : text)
    {
        if (ch == ' ')
        {
            if (!word.empty())
            {
                wordCount[word]++;       // operator[] 自动处理首次出现
                word.clear();
            }
        }
        else
        {
            word += ch;
        }
    }
    if (!word.empty()) wordCount[word]++;

    for (const auto& kv : wordCount)
    {
        cout << "  " << kv.first << ": " << kv.second << endl;
    }

    // 练习 2：找出现次数最多的单词
    // (可以用 priority_queue，这里演示 map 遍历)
    auto maxIter = max_element(wordCount.begin(), wordCount.end(),
        [](const auto& a, const auto& b)
        {
            return a.second < b.second;
        });
    cout << "  最高频: \"" << maxIter->first << "\" (" << maxIter->second << "次)" << endl;

    // 练习 3：成绩排名（同分不覆盖）
    // multimap: key = 分数, value = 姓名
    cout << "\n练习3: 成绩排名 (multimap)" << endl;
    multimap<int, string, greater<int>> scores;
    // greater<int> 使 key 从大到小排序（高分在前）
    scores.insert({92, "张三"});
    scores.insert({85, "李四"});
    scores.insert({92, "王五"});         // 同分不会覆盖！
    scores.insert({78, "赵六"});
    scores.insert({85, "孙七"});

    for (const auto& kv : scores)
    {
        cout << "  分数 " << kv.first << ": " << kv.second << endl;
    }

    // multimap 没有 operator[]，因为同 key 有多个 value
    // 查找某个 key 的所有 value：
    auto range = scores.equal_range(92);
    cout << "  分数 92 的人: ";
    for (auto it = range.first; it != range.second; ++it)
    {
        cout << it->second << " ";
    }
    cout << endl;
}


int main()
{
    cout << "========================================" << endl;
    cout << "|    STL 容器(3) — set 与 map         |" << endl;
    cout << "========================================" << endl;

    // set
    test01_set_basics();
    test02_set_advanced();
    test03_multiset();

    // map
    test04_map_basics();
    test05_map_advanced();
    test06_map_practice();

    system("pause");
    return 0;
}

// 完结撒花*
