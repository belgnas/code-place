// Modern C++ (1) — 类型推导与统一初始化
//
// 【auto】自动类型推导
//   编译器根据初始化表达式自动推断变量类型
//   优点：减少冗长类型名，避免类型不匹配
//   注意：auto 会剥离 const 和引用（除非用 auto&）
//
// 【decltype】获取表达式的类型
//   编译期获取表达式类型，不计算表达式
//   常用于模板编程和 auto 无法处理的场景
//
// 【nullptr】空指针字面量
//   C++11 引入，替代 NULL 和 0
//   NULL = 0 (整数)，可能导致重载解析错误
//   nullptr = std::nullptr_t 类型，只能赋给指针
//
// 【统一初始化】{}
//   大括号初始化，防止窄化转换（narrowing）
//   int x{3.14} → 编译错误！（double → int 会丢失精度）
//
// 【range-for】范围 for 循环
//   简洁遍历容器，不需要手动管理索引或迭代器


#include<iostream>
#include<vector>
#include<map>
#include<string>
#include<typeinfo>   // typeid
#include<type_traits>// is_same
#include<utility>    // std::move
using namespace std;


// ==================== 第一部分：auto ====================

// 辅助函数：打印变量类型（编译期）
template<typename T>
void printType(const char* name)
{
    cout << "  " << name << " 的类型: " << typeid(T).name() << endl;
    // typeid 返回的名字因编译器而异（g++ 可能显示 i, d, PKc 等）
    // 这里用 is_same 做精确判断更可靠
}

void test01_auto_basics()
{
    cout << "\n========== auto 基础 ==========" << endl;

    // ---- 基本用法 ----
    auto i = 42;                         // int
    auto d = 3.14;                       // double
    auto c = 'A';                        // char
    auto s = "Hello";                    // const char*
    auto str = string("World");          // string
    auto b = true;                       // bool

    cout << "i = " << i << ", d = " << d << ", c = " << c << endl;
    cout << "s = " << s << ", str = " << str << endl;

    cout << "\n类型判断 (is_same):" << endl;
    cout << "  auto i=42:     " << (is_same<decltype(i), int>::value ? "int" : "?") << endl;
    cout << "  auto d=3.14:   " << (is_same<decltype(d), double>::value ? "double" : "?") << endl;
    cout << "  auto s=\"Hello\": " << (is_same<decltype(s), const char*>::value ? "const char*" : "?") << endl;

    // ---- auto 的实用场景 ----
    // 场景 1：迭代器（最常用！）
    vector<int> v = {1, 2, 3, 4, 5};
    // 不用 auto:
    // for (vector<int>::iterator it = v.begin(); it != v.end(); ++it)
    // 用 auto:
    for (auto it = v.begin(); it != v.end(); ++it)
    {
        *it *= 10;
    }
    cout << "\n迭代器 (auto it): ";
    for (auto x : v) cout << x << " ";

    // 场景 2：map 遍历
    map<string, int> m = {{"a", 1}, {"b", 2}};
    for (auto kv : m)  // kv 是 pair<const string, int>
    {
        cout << "\n  {" << kv.first << ":" << kv.second << "}";
    }
    cout << endl;

    // 场景 3：复杂类型简化
    auto lambda = [](int x) { return x * x; }; // lambda 类型无法手写

    // 场景 4：避免类型不匹配
    auto len = v.size();  // size_t（64位系统下 unsigned long long）
    // 如果写 int len = v.size()，可能有警告
}

void test02_auto_pitfalls()
{
    cout << "\n========== auto 的注意事项 ==========" << endl;

    // ---- 坑 1：auto 会剥离 const 和引用 ----
    const int ci = 10;
    auto a1 = ci;                        // int（const 被剥离！）
    a1 = 20;                             // OK

    auto& a2 = ci;                       // const int&（保留 const）
    // a2 = 20;                          // 错误！const 引用不能修改

    const auto& a3 = ci;                 // const int&（显式声明 const）

    cout << "const int ci = 10;" << endl;
    cout << "  auto a1 = ci;   → int (const 被剥离)" << endl;
    cout << "  auto& a2 = ci;  → const int& (保留 const)" << endl;

    // ---- 坑 2：auto&& 是万能引用 ----
    int x = 42;
    auto&& r1 = x;                       // int&（左值引用）
    auto&& r2 = 42;                      // int&&（右值引用）
    auto&& r3 = move(x);                 // int&&
    // 万能引用：能绑定左值也能绑定右值（引用折叠规则）

    // ---- 坑 3：代理类的 auto ----
    // vector<bool> 的 operator[] 返回的不是 bool&，而是代理对象
    vector<bool> vb = {true, false, true};
    auto b1 = vb[0];                     // 代理对象！（不是 bool）
    bool b2 = vb[0];                     // bool（隐式转换）
    // 解决方案：用 auto&& 或显式写 bool
    cout << "\nvector<bool> 陷阱:" << endl;
    cout << "  auto b = vb[0]  → 代理对象（不是 bool&）" << endl;
    cout << "  bool b = vb[0]  → bool（OK）" << endl;
}


// ==================== 第二部分：decltype ====================

// 【修正】将嵌套函数移到全局作用域，保留原注释
int& getRef(int& val) { return val; }   // 原在 test03_decltype 内部定义

void test03_decltype()
{
    cout << "\n========== decltype ==========" << endl;

    int x = 10;
    const int& rx = x;

    // decltype(变量名): 得到变量的声明类型（包括 const 和引用）
    decltype(x)  d1 = 20;                // int
    decltype(rx) d2 = x;                 // const int&
    // decltype(rx) d3 = 42;             // 错误！const int& 不能绑定字面量

    // decltype(表达式): 得到表达式的结果类型
    // 如果表达式是左值 → 得到引用类型
    decltype((x)) d4 = x;                // int&（加括号表示左值表达式）
    decltype(x + 1) d5 = 30;            // int（右值表达式）

    cout << "int x = 10;  const int& rx = x;" << endl;
    cout << "  decltype(x)   → int" << endl;
    cout << "  decltype(rx)  → const int&" << endl;
    cout << "  decltype((x)) → int&  (加括号 = 左值表达式)" << endl;
    cout << "  decltype(x+1) → int   (右值表达式)" << endl;

    // ---- 实用场景：尾置返回类型 ----
    // 当返回类型依赖于模板参数时
    // template<typename T, typename U>
    // auto add(T t, U u) -> decltype(t + u)  // C++11 风格
    // {
    //     return t + u;
    // }

    // C++14 简化：auto 就能推断返回类型
    auto add14 = [](auto t, auto u) { return t + u; };
    cout << "\nadd14(3, 4.5) = " << add14(3, 4.5) << endl;

    // decltype(auto): C++14，保留引用和 const
    // auto 会剥离引用，decltype(auto) 不会
    // 注意：getRef 已移为全局函数
    auto           r1 = getRef(x);       // int（引用被剥离）
    decltype(auto) r2 = getRef(x);       // int&（引用保留）
    r2 = 99;                             // 修改了 x!
    cout << "\nauto vs decltype(auto):" << endl;
    cout << "  auto r1 = getRef(x) → int  (x = " << x << ", 未变)" << endl;
    cout << "  decltype(auto) r2 → int& (x = " << x << ", 被修改)" << endl;
}


// ==================== 第三部分：nullptr ====================

void test04_nullptr()
{
    cout << "\n========== nullptr ==========" << endl;

    // ---- 问题：NULL 的本质 ----
    // #define NULL 0  （大多数实现）
    // 所以 NULL 实际上是个整数 0，不是指针类型！

    // 这导致重载解析问题：
    auto overloaded = [](int x)
    {
        cout << "  called overloaded(int) with " << x << endl;
    };
    auto overloadedPtr = [](void* p)
    {
        cout << "  called overloaded(void*) with " << (p ? "non-null" : "null") << endl;
    };

    overloaded(0);                       // 调用 int 版本（没问题）
    // overloaded(NULL);                 // 也是调用 int 版本！（可能不是想要的）
    overloadedPtr(nullptr);              // 明确调用 void* 版本

    cout << "结论:" << endl;
    cout << "  NULL  = 整数 0 → 可能匹配到 int 重载" << endl;
    cout << "  nullptr = std::nullptr_t 类型 → 只能匹配指针" << endl;
    cout << "  → 永远用 nullptr，不要用 NULL！" << endl;

    // ---- nullptr 的类型安全 ----
    int* p1 = nullptr;                   // OK
    // int  n1 = nullptr;                // 错误！不能把 nullptr 赋给 int

    // nullptr 可以参与条件判断
    if (!p1)
    {
        cout << "nullptr 在条件中隐式转为 false" << endl;
    }
}


// ==================== 第四部分：统一初始化 {} ====================

void test05_uniform_init()
{
    cout << "\n========== 统一初始化 {} ==========" << endl;

    // ---- 为什么需要 {}？ ----
    // 旧式初始化的问题：
    // int x();    // 这声明了一个函数！不是默认初始化！
    // vector<int> v(10, 20);  // 10个20，还是 {10, 20}？取决于括号

    // {} 解决这些问题：
    // 1. 不允许窄化转换
    int a = 3.14;                        // OK，丢失精度但只有警告
    // int b{3.14};                      // 编译错误！narrowing conversion

    // 2. 避免最令人烦恼的解析 (most vexing parse)
    // int func();   ← 这是函数声明还是变量定义？搞不清楚
    int val{42};                         // 明确是变量

    // 3. 统一初始化语法
    int n1{10};                          // 基本类型
    int n2 = {20};                       // 也可以用 = {}
    int arr[]{1, 2, 3, 4, 5};           // 数组
    vector<int> v{1, 2, 3, 4, 5};       // 容器
    struct Point { int x, y; };
    Point p{3, 5};                       // 结构体

    cout << "n1=" << n1 << ", n2=" << n2 << endl;
    cout << "arr: ";
    for (int x : arr) cout << x << " ";
    cout << endl;
    cout << "Point: (" << p.x << ", " << p.y << ")" << endl;

    // ---- {} vs () 的区别 ----
    // vector<int> v1(5, 10);   // () : 5 个元素，每个值为 10 → {10,10,10,10,10}
    // vector<int> v2{5, 10};   // {} : 两个元素 {5, 10}
    // {} 优先匹配 initializer_list 构造函数

    // ---- 类的成员初始化 ----
    struct Config
    {
        int port{8080};                  // 默认值
        string host{"localhost"};
        bool debug{false};
    };

    Config cfg;
    cout << "\n成员默认初始化: port=" << cfg.port
         << ", host=" << cfg.host
         << ", debug=" << (cfg.debug ? "true" : "false") << endl;

    // C++20 指定初始化器（需 -std=c++20）
    Config cfg2{.port = 3000, .debug = true};
    cout << "指定初始化: port=" << cfg2.port << ", debug=" << cfg2.debug << endl;
}


// ==================== 第五部分：range-for ====================

void test06_range_for()
{
    cout << "\n========== range-for 深入 ==========" << endl;

    vector<int> v = {1, 2, 3, 4, 5};

    // ---- 基本用法 ----
    // for (类型 变量 : 容器)

    // 只读遍历（拷贝，不修改原数据）
    cout << "for (int x : v)         拷贝遍历: ";
    for (int x : v)     // x 是 v[i] 的拷贝
    {
        x *= 2;                          // 修改拷贝，不影响原数据
        cout << x << " ";
    }
    cout << "\n  原数据未变: ";
    for (int x : v) cout << x << " ";
    cout << endl;

    // 可修改遍历（引用）
    cout << "for (int& x : v)        引用遍历: ";
    for (int& x : v)    // x 是 v[i] 的引用
    {
        x *= 2;                          // 直接修改原数据！
    }
    for (int x : v) cout << x << " ";
    cout << endl;

    // 只读 + 避免拷贝（const 引用）
    cout << "for (const auto& x : v) auto&只读: ";
    for (const auto& x : v)              // 最佳实践：不修改 + 不拷贝
    {
        cout << x << " ";
    }
    cout << endl;

    // ---- range-for 的原理 ----
    // for (int x : v) 等价于:
    // for (auto it = begin(v); it != end(v); ++it)
    // { int x = *it; ... }
    //
    // 所以 range-for 要求容器有 begin() 和 end()
    // 也可以通过非成员函数 begin()/end() 支持

    // ---- 陷阱：遍历时修改容器 ----
    // for (auto& x : v) { v.push_back(0); }  // 危险！可能死循环或崩溃
    // 不要在 range-for 中改变容器大小！
    cout << "\n⚠ 不要在 range-for 中修改容器大小（增删元素）！" << endl;
    cout << "  会导致迭代器失效，可能崩溃。" << endl;
}


int main()
{
    cout << "========================================" << endl;
    cout << "| Modern C++(1) — 类型推导与初始化    |" << endl;
    cout << "========================================" << endl;

    test01_auto_basics();
    test02_auto_pitfalls();
    test03_decltype();
    test04_nullptr();
    test05_uniform_init();
    test06_range_for();

    system("pause");
    return 0;
}

// 完结撒花*