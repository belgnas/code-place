// STL 容器 (1) — string 与 vector
//
// 【string】C++ 标准字符串类
//   - C 风格字符串 char[] 需要手动管理内存、用 strcpy/strcmp 等函数操作
//   - std::string 封装了内存管理，支持 + 拼接、== 比较、.find() 查找等
//   - 内部是动态数组，自动扩容
//
// 【vector】动态数组（向量）
//   - 连续内存存储，支持 O(1) 随机访问
//   - 尾部插入 O(1) 均摊，中间插入 O(n)
//   - 是 C++ 中最常用的容器，替代 C 风格的 new[] 数组
//
//   vector 内存模型：
//   [已用元素][未用空间………………]
//   size()     capacity() - size()
//   当 size() == capacity() 时，push_back 触发扩容（通常是 2 倍）


#include<iostream>
#include<string>    // string 类
#include<vector>    // vector 容器
#include<algorithm> // sort, find 等算法
using namespace std;


// ==================== 第一部分：string ====================

void test01_string_basics()
{
    cout << "\n========== string 基础操作 ==========" << endl;

    // ---- 构造 ----
    string s1;                          // 空字符串 ""
    string s2 = "Hello";                // C 风格字符串初始化
    string s3("World");                 // 构造函数初始化
    string s4(s2);                      // 拷贝构造
    string s5(5, 'A');                  // 5 个 'A' → "AAAAA"

    cout << "s1 = \"" << s1 << "\"" << endl;
    cout << "s2 = \"" << s2 << "\"" << endl;
    cout << "s3 = \"" << s3 << "\"" << endl;
    cout << "s4 = \"" << s4 << "\"" << endl;
    cout << "s5 = \"" << s5 << "\"" << endl;

    // ---- 拼接 ----
    string s6 = s2 + " " + s3;          // + 运算符拼接
    s6 += "!!";                         // += 追加
    cout << "\ns6 (拼接) = \"" << s6 << "\"" << endl;

    // s2.append(s3) 等价于 s2 += s3
    // s2.append(" World", 3) 追加前 3 个字符 → " Wo"

    // ---- 长度和判空 ----
    cout << "\ns6.length() = " << s6.length() << endl;   // 等价于 s6.size()
    cout << "s1.empty()   = " << (s1.empty() ? "true" : "false") << endl;

    // ---- 访问字符 ----
    cout << "s6[0]  = '" << s6[0]  << "'" << endl;     // 下标访问（无边界检查）
    cout << "s6.at(0) = '" << s6.at(0) << "'" << endl; // at() 有边界检查，越界抛异常
    cout << "s6.front() = '" << s6.front() << "'" << endl; // 首字符
    cout << "s6.back()  = '" << s6.back()  << "'" << endl; // 尾字符

    // ---- 查找 ----
    size_t pos = s6.find("World");       // 返回第一次出现的位置（size_t = unsigned long long）
    if (pos != string::npos)             // npos = 查找失败标志（实际上是 -1 转成 size_t）
    {
        cout << "\n\"World\" 在 s6 中的位置: " << pos << endl;
    }

    // rfind: 从右向左查找
    // find_first_of: 查找"任意一个字符"出现的位置
    // find_first_not_of: 查找"第一个不匹配字符"的位置
}

void test02_string_substr_convert()
{
    cout << "\n========== string 截取与转换 ==========" << endl;

    string s = "Hello,World,C++";

    // ---- 截取子串 ----
    // substr(pos, len): 从 pos 开始截取 len 个字符
    string sub1 = s.substr(0, 5);        // "Hello"
    string sub2 = s.substr(6, 5);        // "World"
    string sub3 = s.substr(12);          // 从 12 到末尾 → "C++"
    cout << "substr(0,5)  = \"" << sub1 << "\"" << endl;
    cout << "substr(6,5)  = \"" << sub2 << "\"" << endl;
    cout << "substr(12)   = \"" << sub3 << "\"" << endl;

    // ---- 比较 ----
    // string 直接支持 == != < > <= >=
    string a = "abc";
    string b = "abd";
    cout << "\n\"abc\" < \"abd\" ? " << (a < b ? "true" : "false") << endl;

    // a.compare(b) 返回: 0(相等), <0(a<b 字典序), >0(a>b)
    cout << "\"abc\".compare(\"abd\") = " << a.compare(b) << endl;

    // ---- 插入和删除 ----
    string s2 = "Hello World";
    s2.insert(5, " dear");              // 在位置 5 插入 → "Hello dear World"
    cout << "\ninsert(5, \" dear\"): \"" << s2 << "\"" << endl;

    s2.erase(5, 5);                     // 从位置 5 删除 5 个字符 → "Hello World"
    cout << "erase(5, 5):        \"" << s2 << "\"" << endl;

    // ---- 替换 ----
    string s3 = "I like Java";
    s3.replace(7, 4, "C++");            // 从位置 7 替换 4 个字符 → "I like C++"
    cout << "replace:             \"" << s3 << "\"" << endl;

    // ---- 数字与字符串互转 ----
    // to_string: 数字 → 字符串
    int    num1 = 42;
    double num2 = 3.14159;
    string numStr1 = to_string(num1);   // "42"
    string numStr2 = to_string(num2);   // "3.141590"
    cout << "\nto_string(42)      = \"" << numStr1 << "\"" << endl;
    cout << "to_string(3.14159) = \"" << numStr2 << "\"" << endl;

    // stoi / stod: 字符串 → 数字
    string sNum = "12345";
    int    val1 = stoi(sNum);           // "12345" → 12345
    double val2 = stod("3.14");         // "3.14"  → 3.14
    cout << "stoi(\"12345\") = " << val1 << endl;
    cout << "stod(\"3.14\")  = " << val2 << endl;
    // 还有 stoll(string → long long), stof(string → float)

    // ---- 获取 C 风格字符串 ----
    // 当调用需要 const char* 的 API 时使用 .c_str()
    const char* cstr = s.c_str();
    printf("c_str(): %s\n", cstr);      // C 风格输出
}


// ==================== 第二部分：vector ====================

void test03_vector_basics()
{
    cout << "\n========== vector 基础操作 ==========" << endl;

    // ---- 构造 ----
    vector<int> v1;                      // 空 vector
    vector<int> v2(5);                   // 5 个元素，值都为 0
    vector<int> v3(5, 10);               // 5 个元素，值都为 10
    vector<int> v4 = {1, 2, 3, 4, 5};   // 初始化列表
    vector<int> v5(v4);                  // 拷贝构造

    cout << "v3 (5个10): ";
    for (int x : v3) cout << x << " ";
    cout << endl;

    // ---- 容量相关 ----
    cout << "\nv4.size()     = " << v4.size() << endl;      // 元素个数
    cout << "v4.capacity() = " << v4.capacity() << endl;    // 容量（>= size）
    cout << "v4.empty()    = " << (v4.empty() ? "true" : "false") << endl;

    // ---- 添加元素 ----
    vector<int> v;
    v.push_back(10);                     // 尾部添加（拷贝）
    v.push_back(20);
    v.emplace_back(30);                  // 尾部原地构造（C++11，比 push_back 高效）
    // emplace_back 直接传入构造参数，省去一次拷贝/移动

    cout << "\n添加后: ";
    for (int x : v) cout << x << " ";
    cout << endl;

    // ---- 访问元素 ----
    cout << "v[0]     = " << v[0] << endl;     // 不检查边界
    cout << "v.at(1)  = " << v.at(1) << endl;  // 检查边界（越界抛异常）
    cout << "v.front() = " << v.front() << endl; // 第一个元素
    cout << "v.back()  = " << v.back() << endl;  // 最后一个元素

    // v.data() 返回底层数组指针，用于和 C API 交互

    // ---- 删除元素 ----
    v.pop_back();                        // 尾部删除（O(1)）
    cout << "\npop_back 后: ";
    for (int x : v) cout << x << " ";
    cout << endl;

    // ---- 插入和删除（中间位置） ----
    vector<int> v6 = {1, 2, 3, 4, 5};

    // insert(pos, value): 在 pos 位置前插入（O(n)）
    v6.insert(v6.begin() + 2, 99);      // 在索引 2 前插入 99
    cout << "\ninsert(索引2, 99)后: ";
    for (int x : v6) cout << x << " ";
    cout << endl;

    // erase(pos): 删除 pos 位置的元素（O(n)）
    v6.erase(v6.begin() + 2);            // 删除刚插入的 99
    cout << "erase(索引2)后:     ";
    for (int x : v6) cout << x << " ";
    cout << endl;

    // 区间删除: erase(first, last) 删除 [first, last)
    v6.erase(v6.begin() + 1, v6.begin() + 3); // 删除索引 1,2 的元素
    cout << "erase(1, 3)后:       ";
    for (int x : v6) cout << x << " ";
    cout << endl;

    // clear(): 清空所有元素（size 变 0，capacity 不变）
    v6.clear();
    cout << "clear 后 size=" << v6.size() << ", capacity=" << v6.capacity() << endl;
}

void test04_vector_memory()
{
    cout << "\n========== vector 扩容机制 ==========" << endl;

    // 观察 capacity 如何变化
    vector<int> v;
    cout << "初始: size=" << v.size() << ", capacity=" << v.capacity() << endl;

    for (int i = 1; i <= 20; i++)
    {
        v.push_back(i);
        // 当 size > capacity 时触发扩容
        if (v.size() > v.capacity() / 2)  // 仅在可能扩容时打印
        {
            cout << "push_back(" << i << ") → size=" << v.size()
                 << ", capacity=" << v.capacity() << endl;
        }
    }
    cout << "...中间略..." << endl;

    // reserve(n): 预留容量，避免频繁扩容
    vector<int> v2;
    v2.reserve(100);                     // 提前分配 100 个元素的空间
    cout << "\nreserve(100) 后: capacity=" << v2.capacity() << endl;
    // 这样 push_back 100 次也不会触发扩容

    // shrink_to_fit(): 释放多余容量
    vector<int> v3;
    v3.reserve(100);
    v3.push_back(1);
    v3.push_back(2);
    cout << "shrink_to_fit 前: size=" << v3.size()
         << ", capacity=" << v3.capacity() << endl;
    v3.shrink_to_fit();                  // capacity 缩减到接近 size
    cout << "shrink_to_fit 后: size=" << v3.size()
         << ", capacity=" << v3.capacity() << endl;

    // resize(n): 改变 size
    // resize(n, val): size < n 用 val 填充；size > n 截断
    vector<int> v4 = {1, 2, 3};
    v4.resize(5, 0);                     // 扩充到 5，新位置填 0
    cout << "\nresize(5,0): ";
    for (int x : v4) cout << x << " ";   // {1, 2, 3, 0, 0}
    cout << endl;
}

void test05_vector_iterators()
{
    cout << "\n========== vector 迭代器与遍历 ==========" << endl;

    vector<int> v = {10, 20, 30, 40, 50};

    // 方式 1：传统 for + 下标
    cout << "方式1 (下标):    ";
    for (size_t i = 0; i < v.size(); i++)
        cout << v[i] << " ";
    cout << endl;

    // 方式 2：范围 for（C++11，最简洁）
    cout << "方式2 (范围for):  ";
    for (int x : v) cout << x << " ";
    cout << endl;

    // 方式 3：迭代器
    cout << "方式3 (迭代器):   ";
    for (auto it = v.begin(); it != v.end(); ++it)
        cout << *it << " ";
    cout << endl;

    // 方式 4：反向迭代器
    cout << "方式4 (反向):     ";
    for (auto it = v.rbegin(); it != v.rend(); ++it)
        cout << *it << " ";
    cout << endl;

    // ---- 迭代器类型 ----
    // begin()  → 指向第一个元素
    // end()    → 指向最后一个元素的下一个位置（哨兵）
    // rbegin() → 指向最后一个元素（反向开始）
    // rend()   → 指向第一个元素的前一个位置（反向结束）
    //
    // vector 的迭代器是"随机访问迭代器"，支持 it + n, it - n, it[n]

    // ---- 迭代器失效 ----
    // 当 vector 扩容时，所有迭代器失效（内存重新分配了）
    // 当在中间 insert/erase 时，插入/删除点之后的迭代器失效
    cout << "\n⚠ 迭代器失效示例:" << endl;
    vector<int> v2 = {1, 2, 3, 4, 5};
    auto it = v2.begin() + 2;           // 指向 3
    cout << "插入前 *it = " << *it << endl;

    // v2.push_back(6);                  // 可能触发扩容 → it 失效！
    v2.insert(it, 99);                   // 在 it 前插入 → it 可能失效
    // 此时 it 已经不安全了！

    // 正确做法：用 insert 的返回值更新迭代器
    it = v2.begin();                     // 重新获取
    cout << "插入后: ";
    for (int x : v2) cout << x << " ";
    cout << endl;
}

void test06_vector_practice()
{
    cout << "\n========== vector 实战 ==========" << endl;

    // 练习 1：去重 + 排序
    vector<int> v = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
    cout << "原始数组: ";
    for (int x : v) cout << x << " ";
    cout << endl;

    sort(v.begin(), v.end());
    // unique 把重复元素移到末尾，返回新末尾的迭代器
    auto last = unique(v.begin(), v.end());
    v.erase(last, v.end());

    cout << "去重排序: ";
    for (int x : v) cout << x << " ";
    cout << endl;

    // 练习 2：二维 vector（邻接表存图）
    cout << "\n二维 vector (邻接表):" << endl;
    int n = 5;  // 5 个节点
    vector<vector<int>> graph(n);        // n 个空 vector

    // 添加边: 0→1, 0→2, 1→3, 2→3, 3→4
    graph[0].push_back(1);
    graph[0].push_back(2);
    graph[1].push_back(3);
    graph[2].push_back(3);
    graph[3].push_back(4);

    for (int i = 0; i < n; i++)
    {
        cout << "节点 " << i << " 的邻接点: ";
        for (int neighbor : graph[i])
            cout << neighbor << " ";
        cout << endl;
    }

    // 练习 3：vector 存自定义类型
    struct Student
    {
        string name;
        int    score;
        Student(string n, int s) : name(n), score(s) {}
    };

    vector<Student> students;
    students.emplace_back("张三", 85);   // emplace_back 直接在 vector 内部构造
    students.emplace_back("李四", 92);
    students.emplace_back("王五", 78);

    // 按成绩排序（lambda 表达式，后面 ModernCpp 会详细学）
    sort(students.begin(), students.end(),
         [](const Student& a, const Student& b)
         {
             return a.score > b.score;   // 从高到低
         });

    cout << "\n学生成绩排名:" << endl;
    for (const auto& s : students)
        cout << "  " << s.name << ": " << s.score << endl;
}


int main()
{
    cout << "========================================" << endl;
    cout << "|     STL 容器(1) — string 与 vector  |" << endl;
    cout << "========================================" << endl;

    // string
    test01_string_basics();
    test02_string_substr_convert();

    // vector
    test03_vector_basics();
    test04_vector_memory();
    test05_vector_iterators();
    test06_vector_practice();

    system("pause");
    return 0;
}

// 完结撒花*
