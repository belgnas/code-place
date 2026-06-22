// STL 容器 (5) — 迭代器体系与函数对象
//
// 【迭代器 Iterator】
//   迭代器是 STL 的"胶水"——连接容器和算法的桥梁
//   每个容器都有自己的迭代器类型，但接口统一
//
//   迭代器类别（从弱到强）：
//   - 输入迭代器:   只能读，只能向前，只能单遍（如 istream_iterator）
//   - 输出迭代器:   只能写，只能向前，只能单遍（如 ostream_iterator）
//   - 前向迭代器:   可读写，只能向前，可多遍（如 forward_list）
//   - 双向迭代器:   可读写，可前后移动（如 list, set, map）
//   - 随机访问迭代器: 可读写，支持 +n -n [] 比较（如 vector, deque, array）
//
//   容器 → 迭代器类型:
//   vector, deque, array, string → 随机访问
//   list, set, map, multiset, multimap → 双向
//   forward_list → 前向
//   unordered_set, unordered_map → 前向（单链表）或双向（取决于实现）
//
// 【函数对象 Functor】
//   重载了 operator() 的类/结构体，可以像函数一样调用
//   比普通函数优点：可以保存状态，可以内联优化
//
// 【Lambda 表达式】(C++11)
//   匿名函数对象的语法糖，编译器自动生成一个仿函数类


#include<iostream>
#include<vector>
#include<list>
#include<set>
#include<map>
#include<algorithm>  // sort, find, copy, for_each, transform, count_if
#include<numeric>    // accumulate, iota
#include<iterator>   // back_inserter, front_inserter, inserter
#include<functional> // less, greater, plus, function, bind
using namespace std;


// ==================== 第一部分：迭代器深入 ====================

void test01_iterator_categories()
{
    cout << "\n========== 迭代器类别演示 ==========" << endl;

    // ---- 随机访问迭代器（vector） ----
    vector<int> v = {10, 20, 30, 40, 50};
    auto vit = v.begin();

    cout << "vector 迭代器支持的操作:" << endl;
    cout << "  *vit     = " << *vit << endl;
    cout << "  vit[2]   = " << vit[2] << endl;    // 随机访问特有！
    cout << "  *(vit+3) = " << *(vit + 3) << endl; // 指针算术！
    cout << "  end-begin = " << (v.end() - v.begin()) << endl; // 距离

    // vit < v.end() 也可以比较（随机访问迭代器支持 < > <= >=）
    // 但通常还是用 != ，因为对所有迭代器通用

    // ---- 双向迭代器（list） ----
    list<int> l = {10, 20, 30, 40, 50};
    auto lit = l.begin();

    cout << "\nlist 迭代器支持的操作:" << endl;
    cout << "  *lit   = " << *lit << endl;
    ++lit;
    cout << "  ++lit  = " << *lit << endl;
    --lit;
    cout << "  --lit  = " << *lit << endl;
    // lit + 3  ← 编译错误！list 不支持随机访问
    // lit[0]   ← 编译错误！

    // 所以 advance(lit, 3) 可以帮你前进 3 步
    // 对随机访问是 O(1)，对双向/前向是 O(n)
    advance(lit, 3);
    cout << "  advance(lit, 3) = " << *lit << endl;

    // distance(first, last): 计算两个迭代器之间的距离
    cout << "  distance(l.begin(), l.end()) = "
         << distance(l.begin(), l.end()) << endl;
}

void test02_iterator_adapters()
{
    cout << "\n========== 迭代器适配器 ==========" << endl;

    // back_inserter: 在容器尾部插入
    // 内部调用 push_back()，不需要预分配空间
    {
        vector<int> src = {1, 2, 3, 4, 5};
        vector<int> dst;

        // 不用 back_inserter 的话，copy 要求目标有足够空间
        // dst.resize(src.size());  // 必须提前分配！
        // copy(src.begin(), src.end(), dst.begin());

        // 用 back_inserter，自动扩容
        copy(src.begin(), src.end(), back_inserter(dst));
        // 等价于 for (int x : src) dst.push_back(x);

        cout << "back_inserter: ";
        for (int x : dst) cout << x << " ";
        cout << endl;
    }

    // front_inserter: 在容器头部插入（需要容器有 push_front）
    {
        vector<int> src = {1, 2, 3};
        list<int> dst;                   // vector 没有 push_front，用 list

        copy(src.begin(), src.end(), front_inserter(dst));
        cout << "front_inserter: ";
        for (int x : dst) cout << x << " ";
        cout << "  (注意：顺序反了！)" << endl;
    }

    // inserter: 在指定位置插入
    {
        vector<int> src = {99, 100, 101};
        vector<int> dst = {1, 2, 3, 4, 5};

        // 在索引 2 前插入
        copy(src.begin(), src.end(), inserter(dst, dst.begin() + 2));

        cout << "inserter(begin+2): ";
        for (int x : dst) cout << x << " ";
        cout << endl;
    }

    // 流迭代器（了解即可）
    // istream_iterator<int>(cin): 从标准输入读 int
    // ostream_iterator<int>(cout, " "): 输出 int，用空格分隔
}

void test03_iterator_helpers()
{
    cout << "\n========== 迭代器辅助函数 ==========" << endl;

    vector<int> v = {1, 2, 3, 4, 5};

    // next(it, n): 返回 it 前进 n 步后的迭代器（不修改 it）
    auto it = v.begin();
    auto it2 = next(it, 2);
    cout << "next(begin, 2) = " << *it2 << endl;
    cout << "原迭代器不变    = " << *it << endl;

    // prev(it, n): 返回 it 后退 n 步后的迭代器
    auto it3 = prev(v.end(), 1);
    cout << "prev(end, 1) = " << *it3 << endl;

    // distance: 两个迭代器之间的距离
    cout << "distance(begin, end) = " << distance(v.begin(), v.end()) << endl;
}


// ==================== 第二部分：函数对象（Functor） ====================

void test04_functors()
{
    cout << "\n========== 函数对象（仿函数） ==========" << endl;

    // ---- 什么是仿函数？ ----
    // 重载了 operator() 的类，可以像函数一样调用
    struct Add
    {
        int operator()(int a, int b) const
        {
            return a + b;
        }
    };

    Add add;
    cout << "仿函数 add(3, 5) = " << add(3, 5) << endl;
    // 看起来像函数调用，实际上是 add.operator()(3, 5)

    // ---- 仿函数 vs 普通函数 ----
    // 仿函数可以携带状态！
    struct Counter
    {
        int count = 0;
        void operator()(int x)
        {
            count++;
            cout << "  第 " << count << " 次调用, 参数 = " << x << endl;
        }
    };

    Counter counter;
    counter(10);
    counter(20);
    counter(30);                         // count 保持为 3

    // ---- STL 内置仿函数 ----
    // less<int>():     a < b（默认排序用）
    // greater<int>():  a > b
    // plus<int>():     a + b
    // multiplies<int>(): a * b
    // modulus<int>():  a % b

    // transform + plus: 两个数组对应位置相加
    vector<int> a = {1, 2, 3, 4, 5};
    vector<int> b = {10, 20, 30, 40, 50};
    vector<int> result(5);

    transform(a.begin(), a.end(), b.begin(),
              result.begin(), plus<int>());

    cout << "\ntransform + plus: ";
    for (int x : result) cout << x << " ";
    cout << endl;
}

void test05_algorithm_functor()
{
    cout << "\n========== STL 算法 + 函数对象 ==========" << endl;

    vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // ---- 遍历：for_each ----
    cout << "for_each: ";
    for_each(v.begin(), v.end(),
             [](int x) { cout << x << " "; });  // 这里用了 lambda（见下一节）
    cout << endl;

    // ---- 条件计数：count_if ----
    // 统计偶数个数
    int evenCount = count_if(v.begin(), v.end(),
        [](int x) { return x % 2 == 0; });
    cout << "偶数个数: " << evenCount << endl;

    // ---- 条件查找：find_if ----
    auto it = find_if(v.begin(), v.end(),
        [](int x) { return x > 7; });
    if (it != v.end())
        cout << "第一个 >7 的元素: " << *it << endl;

    // ---- 变换：transform ----
    // 所有元素 * 2
    vector<int> v2(v.size());
    transform(v.begin(), v.end(), v2.begin(),
        [](int x) { return x * 2; });
    cout << "transform *2: ";
    for (int x : v2) cout << x << " ";
    cout << endl;

    // ---- 条件复制：copy_if ----
    vector<int> evenNums;
    copy_if(v.begin(), v.end(), back_inserter(evenNums),
        [](int x) { return x % 2 == 0; });
    cout << "copy_if (偶数): ";
    for (int x : evenNums) cout << x << " ";
    cout << endl;

    // ---- 替换：replace_if ----
    vector<int> v3 = v;
    replace_if(v3.begin(), v3.end(),
        [](int x) { return x < 5; }, 0); // 把 <5 的替换成 0
    cout << "replace_if (<5→0): ";
    for (int x : v3) cout << x << " ";
    cout << endl;

    // ---- 全判断：all_of / any_of / none_of ----
    bool allPositive = all_of(v.begin(), v.end(),
        [](int x) { return x > 0; });
    bool anyLarge = any_of(v.begin(), v.end(),
        [](int x) { return x > 9; });
    bool noneNegative = none_of(v.begin(), v.end(),
        [](int x) { return x < 0; });

    cout << "\nall_of (全>0):  " << (allPositive ? "true" : "false") << endl;
    cout << "any_of (有>9):  " << (anyLarge ? "true" : "false") << endl;
    cout << "none_of (无<0): " << (noneNegative ? "true" : "false") << endl;

    // ---- 累计：accumulate ----
    int sum = accumulate(v.begin(), v.end(), 0);
    cout << "\naccumulate (和): " << sum << endl;

    // accumulate 也可以自定义操作
    int product = accumulate(v.begin(), v.end(), 1,
        multiplies<int>());
    cout << "accumulate (积): " << product << " (即 10!)" << endl;
}

void test06_algorithm_composition()
{
    cout << "\n========== 算法组合练习 ==========" << endl;

    // 练习：从一个数组中找到所有偶数，排序后输出前 3 个
    vector<int> nums = {7, 2, 9, 4, 1, 8, 6, 3, 5, 10};

    // 1. 筛选偶数
    vector<int> evens;
    copy_if(nums.begin(), nums.end(), back_inserter(evens),
        [](int x) { return x % 2 == 0; });

    // 2. 排序
    sort(evens.begin(), evens.end());

    // 3. 取前 3 个
    vector<int> top3;
    auto end = evens.size() < (size_t)3 ? evens.end() : evens.begin() + 3;
    copy(evens.begin(), end, back_inserter(top3));

    cout << "原始数组: ";
    for (int x : nums) cout << x << " ";
    cout << "\n偶数排序后取前 3: ";
    for (int x : top3) cout << x << " ";
    cout << endl;

    // 练习：移除 vector 中所有特定值
    // erase-remove 惯用法（C++ 经典模式！）
    vector<int> v = {1, 2, 3, 2, 4, 2, 5};

    // remove 并不真的删除，而是把不等于 2 的元素移到前面
    // 返回新的"逻辑末尾"迭代器
    // erase 再真正删除末尾的垃圾数据
    v.erase(remove(v.begin(), v.end(), 2), v.end());

    cout << "\nerase-remove 惯用法（移除所有 2）: ";
    for (int x : v) cout << x << " ";
    cout << endl;

    // 同样适用于 remove_if
    vector<int> v2 = {1, 2, 3, 4, 5, 6, 7, 8};
    v2.erase(remove_if(v2.begin(), v2.end(),
        [](int x) { return x % 2 == 0; }),  // 移除所有偶数
        v2.end());
    cout << "remove_if (移除偶数): ";
    for (int x : v2) cout << x << " ";
    cout << endl;
}


// ==================== 第三部分：std::function 与 std::bind ====================

void test07_function_bind()
{
    cout << "\n========== std::function 与 std::bind ==========" << endl;

    // ---- std::function：通用的函数包装器 ----
    // 可以存储函数指针、仿函数、lambda 表达式

    // 存储普通函数
    function<int(int, int)> func1 = [](int a, int b)
    {
        return a + b;
    };
    cout << "lambda: " << func1(3, 5) << endl;

    // 存储仿函数
    struct Multiply
    {
        int operator()(int a, int b) const { return a * b; }
    };
    function<int(int, int)> func2 = Multiply();
    cout << "仿函数: " << func2(4, 5) << endl;

    // ---- std::bind：绑定参数 ----
    // 把多参数函数"绑定"部分参数，生成少参数的函数

    // 原函数：3 个参数
    auto add3 = [](int a, int b, int c) { return a + b + c; };

    // bind 第一个参数为 10: 新函数只需要 2 个参数
    // placeholders::_1, _2 表示新函数的第 1、2 个参数
    using namespace placeholders;
    auto add3With10 = bind(add3, 10, _1, _2);
    cout << "\nbind(add3, 10, _1, _2) → add3(10, 20, 30) = "
         << add3With10(20, 30) << endl;

    // 绑定到成员函数
    struct Printer
    {
        void print(const string& msg)
        {
            cout << "  Printer: " << msg << " (times called: " << ++count << ")" << endl;
        }
        int count = 0;
    };

    Printer p;
    auto boundPrint = bind(&Printer::print, &p, _1);
    boundPrint("Hello");
    boundPrint("World");

    cout << "\n注: bind 在 C++11 中较常用，但现在更推荐 lambda 来替代。" << endl;
    cout << "    例如 bind(add3, 10, _1, _2) 等价于 [add3](int b, int c) { return add3(10, b, c); }" << endl;
}


int main()
{
    cout << "========================================" << endl;
    cout << "| STL 容器(5) — 迭代器与函数对象     |" << endl;
    cout << "========================================" << endl;

    // 迭代器
    test01_iterator_categories();
    test02_iterator_adapters();
    test03_iterator_helpers();

    // 函数对象
    test04_functors();
    test05_algorithm_functor();
    test06_algorithm_composition();

    // function/bind
    test07_function_bind();

    system("pause");
    return 0;
}

// 完结撒花*
