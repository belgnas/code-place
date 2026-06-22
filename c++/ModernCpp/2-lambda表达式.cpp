// Modern C++ (2) — Lambda 表达式
//
// 【Lambda 是什么】
//   一种创建匿名函数对象的语法糖
//   编译器自动生成一个重载了 operator() 的类（仿函数）
//
// 【语法】
//   [capture](params) mutable -> return_type { body }
//     ↑        ↑       ↑          ↑           ↑
//     捕获列表  参数    可变修饰   返回类型     函数体
//     (必须)   (可选)   (可选)    (可选)       (必须)
//
// 【捕获方式】
//   []      不捕获任何外部变量
//   [=]     按值捕获所有（拷贝）
//   [&]     按引用捕获所有
//   [x]     按值捕获 x
//   [&x]    按引用捕获 x
//   [this]  捕获当前对象的 this 指针
//   [=, &x] 默认按值，x 按引用
//   [&, x]  默认按引用，x 按值
//
// 【Lambda vs 仿函数 vs 函数指针】
//   - Lambda 可以捕获局部变量（函数指针做不到）
//   - Lambda 比仿函数更简洁（不需要定义类）
//   - Lambda 可以被内联优化（函数指针不容易内联）


#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
#include<functional>  // std::function
#include<memory>     // make_unique
using namespace std;


// ==================== 第一部分：Lambda 基础语法 ====================

void test01_lambda_basics()
{
    cout << "\n========== Lambda 基础语法 ==========" << endl;

    // ---- 最简单的 Lambda ----
    []() { cout << "Hello Lambda!" << endl; }(); // 定义 + 立即调用

    // ---- 存储 Lambda ----
    auto sayHi = []() { cout << "Hi!" << endl; };
    sayHi();                             // 像函数一样调用

    // ---- 带参数的 Lambda ----
    auto add = [](int a, int b) -> int   // -> int 可以省略（自动推导）
    {
        return a + b;
    };
    cout << "add(3, 5) = " << add(3, 5) << endl;

    // ---- 简化写法（省略返回类型） ----
    auto multiply = [](int a, int b) { return a * b; };
    cout << "multiply(4, 5) = " << multiply(4, 5) << endl;

    // ---- 一行 Lambda（省略 return 和 {}） ----
    auto square = [](int x) { return x * x; };
    cout << "square(6) = " << square(6) << endl;
}


// ==================== 第二部分：捕获列表 ====================

void test02_capture_modes()
{
    cout << "\n========== 捕获列表 ==========" << endl;

    int x = 10, y = 20, z = 30;

    // ---- [=] 按值捕获所有 ----
    auto byValue = [=]()
    {
        // x++;  ← 错误！按值捕获的变量默认是 const
        return x + y + z;                // 只能读
    };
    cout << "[=] byValue() = " << byValue() << endl;

    // ---- [&] 按引用捕获所有 ----
    auto byRef = [&]()
    {
        x = 100;                         // 可以修改！
        y = 200;
    };
    byRef();
    cout << "[&] byRef() 后: x=" << x << ", y=" << y << endl;

    // ---- 选择性捕获 ----
    int a = 1, b = 2, c = 3;
    auto selective = [a, &b]()
    {
        // a++;  ← 错误！a 是 const 拷贝
        b++;                             // b 是引用，可以改
        return a + b;                    // c 没有捕获，不能用
    };
    cout << "\n[a, &b] selective() = " << selective() << endl;
    cout << "  b 被修改: " << b << endl;

    // ---- 混合捕获 ----
    auto mixed = [=, &c]()              // 默认按值，c 按引用
    {
        c = 99;
        return a + b + c;
    };
    cout << "\n[=, &c] mixed() = " << mixed() << endl;
    cout << "  c 被修改: " << c << endl;
    // [&, a] 表示默认引用，a 按值

    // ---- mutable：允许修改按值捕获的副本 ----
    int count = 0;
    auto counter = [count]() mutable     // 必须加 mutable
    {
        count++;                         // 修改的是 count 的副本
        return count;
    };
    cout << "\n[mutable] counter(): " << counter() << endl;
    cout << "          counter(): " << counter() << endl;
    cout << "  原始 count 不变: " << count << endl;
    // 每次调用修改的是 lambda 内部的成员变量（编译器生成的类成员）
}

void test03_capture_timing()
{
    cout << "\n========== 捕获的时机 ==========" << endl;

    // ⚠ 关键：按值捕获发生在 Lambda 定义时，不是调用时！

    int x = 10;
    auto f = [x]() { return x; };        // 此时 x 的值是 10 被拷贝进去

    x = 999;                             // 修改外部的 x
    cout << "定义时 x=10, 之后改成 999" << endl;
    cout << "  f() = " << f() << endl;   // 还是 10！不是 999！

    // 按引用捕获发生在调用时（自然，因为存的是引用）
    auto g = [&x]() { return x; };
    cout << "  g() (引用捕获) = " << g() << endl; // 999

    // ---- 陷阱：悬垂引用 ----
    // 如果 Lambda 的生命周期比捕获的变量长 → 悬垂引用！
    auto createLambda = []() -> function<int()>
    {
        int local = 42;
        // return [&local]() { return local; };  // 危险！local 已经析构了
        return [local]() { return local; };       // 安全！按值拷贝
    };

    auto func = createLambda();
    cout << "\n安全: func() = " << func() << endl;
}


// ==================== 第三部分：Lambda 与 STL 算法 ====================

void test04_lambda_with_stl()
{
    cout << "\n========== Lambda 与 STL 算法 ==========" << endl;

    vector<int> v = {5, 2, 8, 1, 9, 3, 7, 4, 6};

    // ---- sort：自定义排序规则 ----
    // 从小到大
    sort(v.begin(), v.end());
    cout << "默认排序: ";
    for (int x : v) cout << x << " ";

    // 从大到小
    sort(v.begin(), v.end(), [](int a, int b) { return a > b; });
    cout << "\n从大到小: ";
    for (int x : v) cout << x << " ";
    cout << endl;

    // ---- 按自定义规则排序 ----
    vector<string> names = {"banana", "apple", "cherry", "date"};
    // 按字符串长度排序，长度相同按字母序
    sort(names.begin(), names.end(),
        [](const string& a, const string& b)
        {
            if (a.length() != b.length())
                return a.length() < b.length();
            return a < b;
        });

    cout << "\n按长度排序: ";
    for (const auto& s : names) cout << s << " ";
    cout << endl;

    // ---- find_if：条件查找 ----
    auto it = find_if(v.begin(), v.end(),
        [](int x) { return x > 5 && x % 2 == 0; });
    if (it != v.end())
        cout << "\n第一个 >5 的偶数: " << *it << endl;

    // ---- count_if：条件计数 ----
    int count = count_if(v.begin(), v.end(),
        [](int x) { return x >= 3 && x <= 7; });
    cout << "在 [3, 7] 范围内的元素个数: " << count << endl;

    // ---- remove_if：条件删除 ----
    vector<int> v2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    v2.erase(
        remove_if(v2.begin(), v2.end(), [](int x) { return x % 2 == 0; }),
        v2.end()
    );
    cout << "删除偶数后: ";
    for (int x : v2) cout << x << " ";
    cout << endl;

    // ---- for_each：遍历操作 ----
    cout << "for_each: ";
    for_each(v.begin(), v.end(), [](int x) { cout << x << " "; });
    cout << endl;

    // ---- transform：变换 ----
    vector<int> squares(v.size());
    transform(v.begin(), v.end(), squares.begin(),
        [](int x) { return x * x; });
    cout << "transform (平方): ";
    for (int x : squares) cout << x << " ";
    cout << endl;
}


// ==================== 第四部分：泛型 Lambda (C++14) ====================

void test05_generic_lambda()
{
    cout << "\n========== 泛型 Lambda (C++14) ==========" << endl;

    // C++14: 参数类型可以是 auto
    auto add = [](auto a, auto b) { return a + b; };

    cout << "add(3, 5)       = " << add(3, 5) << endl;
    cout << "add(3.14, 2.86) = " << add(3.14, 2.86) << endl;
    cout << "add(string(\"Hello \"), string(\"World\")) = "
         << add(string("Hello "), string("World")) << endl;

    // 泛型 lambda 等价于模板函数
    // 编译器为每种参数组合生成一个具体的 operator()

    // ---- 实际应用：通用比较器 ----
    auto descending = [](const auto& a, const auto& b) { return a > b; };

    vector<int>    vi = {3, 1, 4, 1, 5};
    vector<double> vd = {3.14, 1.41, 2.72};
    vector<string> vs = {"cat", "apple", "bee"};

    sort(vi.begin(), vi.end(), descending);
    sort(vd.begin(), vd.end(), descending);
    sort(vs.begin(), vs.end(), descending);

    cout << "\n通用降序排列:" << endl;
    cout << "  int:    "; for (auto x : vi) cout << x << " "; cout << endl;
    cout << "  double: "; for (auto x : vd) cout << x << " "; cout << endl;
    cout << "  string: "; for (auto x : vs) cout << x << " "; cout << endl;

    // ---- 初始化捕获 (C++14) ----
    // 允许在捕获列表中使用表达式
    // [var = expr] 创建并初始化一个捕获变量
    int base = 10;
    auto addBase = [sum = base + 5](int x) { return sum + x; };
    cout << "\n初始化捕获 [sum = base + 5]: " << addBase(3) << endl;

    // 移动捕获（把 unique_ptr 移进 lambda）
    auto p = make_unique<int>(42);
    auto lambda = [ptr = move(p)]() { return *ptr; };
    // p 现在是 nullptr，所有权转移到了 lambda 内部
    cout << "移动捕获: " << lambda() << endl;
}


// ==================== 第五部分：Lambda 原理揭秘 ====================

void test06_lambda_internals()
{
    cout << "\n========== Lambda 原理揭秘 ==========" << endl;

    // Lambda 本质：编译器自动生成的仿函数类
    // 这个 lambda:
    auto f = [x = 10](int y) { return x + y; };

    // 等价于编译器生成了这样的类：
    // class __lambda_123
    // {
    //     int x;  // 捕获的变量成为成员
    // public:
    //     __lambda_123(int _x) : x(_x) {}
    //     auto operator()(int y) const { return x + y; }
    // };

    cout << "Lambda = 匿名仿函数类" << endl;
    cout << "  捕获变量 → 成员变量" << endl;
    cout << "  函数体   → operator()" << endl;
    cout << "  () 调用  → 调用 operator()" << endl;

    // ---- std::function：存储任意可调用对象 ----
    // 可以存储 Lambda、函数指针、仿函数

    function<int(int, int)> func;

    // 存储 lambda
    func = [](int a, int b) { return a + b; };
    cout << "\nstd::function: " << func(3, 5) << endl;

    // 存储普通函数
    int (*ptr)(int, int) = [](int a, int b) { return a * b; };
    // 注意：只有无捕获的 Lambda 才能转为函数指针！

    // std::function 有额外开销（类型擦除），性能敏感场景用 auto
    cout << "\n性能提示: auto 存储 Lambda 无额外开销（编译器完全内联）" << endl;
    cout << "          std::function 有虚函数调用开销，仅在需要时使用" << endl;
}


int main()
{
    cout << "========================================" << endl;
    cout << "|   Modern C++(2) — Lambda 表达式     |" << endl;
    cout << "========================================" << endl;

    test01_lambda_basics();
    test02_capture_modes();
    test03_capture_timing();
    test04_lambda_with_stl();
    test05_generic_lambda();
    test06_lambda_internals();

    system("pause");
    return 0;
}

// 完结撒花*
