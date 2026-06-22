// 注意：本文件中 if constexpr 需要 C++17。编译命令:
//   g++ -std=c++17 3-类型萃取与constexpr.cpp -o output.exe
//   MSVC: cl /std:c++17 3-类型萃取与constexpr.cpp
// 模板与泛型 (3) — SFINAE、类型萃取、constexpr
//
// 【SFINAE】"替换失败不是错误" (Substitution Failure Is Not An Error)
//   编译期选择模板的原理：如果某个模板特化的参数替换失败，
//   不会报错，而是从候选集中移除该特化，尝试其他重载。
//   这是 C++ 模板元编程的基石。
//
// 【类型萃取 Type Traits】(<type_traits>)
//   编译期查询/修改类型信息的工具集
//   is_integral, is_floating_point, is_pointer, is_same, ...
//   remove_const, add_pointer, decay, conditional, ...
//
//   C++20: concepts 提供了更友好的替代方案
//
// 【constexpr】编译期计算
//   让函数/变量在编译期求值，零运行时开销
//   C++11: constexpr 函数只能有 return 语句
//   C++14: 放宽限制，支持 if/for/局部变量
//   C++17: constexpr if — 编译期条件分支


#include<iostream>
#include<string>
#include<vector>
#include<type_traits>  // is_same, enable_if, decay, ...
using namespace std;


// ==================== 第一部分：type_traits ====================

void test01_type_traits()
{
    cout << "\n========== type_traits 基础 ==========" << endl;

    // ---- 类型查询 ----
    cout << "【查询 traits】" << endl;
    cout << "is_integral<int>::value       = " << is_integral<int>::value << endl;
    cout << "is_integral<double>::value    = " << is_integral<double>::value << endl;
    cout << "is_floating_point<double>::value = " << is_floating_point<double>::value << endl;
    cout << "is_pointer<int*>::value       = " << is_pointer<int*>::value << endl;
    cout << "is_pointer<int>::value        = " << is_pointer<int>::value << endl;
    cout << "is_const<const int>::value    = " << is_const<const int>::value << endl;
    cout << "is_same<int, int>::value      = " << is_same<int, int>::value << endl;
    cout << "is_same<int, long>::value     = " << is_same<int, long>::value << endl;

    // C++17 变量模板版本: is_integral<int>::value (不需要 ::value)
    cout << "\nis_integral<int>::value = " << is_integral<int>::value << endl;

    // ---- 类型修改 ----
    cout << "\n【修改 traits】" << endl;
    cout << "remove_const<const int>::type → int: "
         << is_same<remove_const<const int>::type, int>::value << endl;

    cout << "add_pointer<int>::type → int*: "
         << is_same<add_pointer<int>::type, int*>::value << endl;

    cout << "decay<int[5]>::type → int*: "
         << is_same<decay<int[5]>::type, int*>::value << endl;
    // decay: 模拟函数参数传值时的类型退化

    // ---- conditional: 编译期 if-else ----
    // conditional<条件, 类型A, 类型B>::type
    using IntOrDouble = conditional<true, int, double>::type;
    cout << "\nconditional<true, int, double> → int: "
         << is_same<IntOrDouble, int>::value << endl;
}


// ==================== 第二部分：enable_if 与 SFINAE ====================

// 场景：一个函数对整数类型用一种实现，对浮点类型用另一种实现

// 版本 A：仅对整数类型有效
template<typename T>
typename enable_if<is_integral<T>::value, void>::type
process(T value)
{
    cout << "  整数处理: " << value << " (位运算, 模运算等)" << endl;
}

// 版本 B：仅对浮点类型有效
template<typename T>
typename enable_if<is_floating_point<T>::value, void>::type
process(T value)
{
    cout << "  浮点处理: " << value << " (sqrt, sin, cos等)" << endl;
}

// enable_if 工作原理：
//   enable_if<true, T>::type  → T
//   enable_if<false, T>::type → 替换失败 → 从候选集移除 → 尝试其他重载

void test02_enable_if()
{
    cout << "\n========== enable_if 与 SFINAE ==========" << endl;

    process(42);                         // 匹配整数版本
    process(3.14);                       // 匹配浮点版本
    // process("hello");                 // 两个都不匹配 → 编译错误！

    cout << "\nSFINAE 原理:" << endl;
    cout << "  1. 编译器尝试所有可能的重载" << endl;
    cout << "  2. 替换失败的不是错误，只是移除此候选项" << endl;
    cout << "  3. 如果没有候选项留下，才报错误" << endl;
    cout << "  4. 用 enable_if 可以在编译期「选择」不同的实现" << endl;
}

// ---- 用 enable_if 做更精确的匹配 ----

// 工具 trait：判断类型 T 是否能打印（有 operator<<）
// 这里简化：只要不是 void 就认为可打印

// 通用 print 函数：仅对可打印类型
template<typename T>
auto printValue(const T& val)
    -> enable_if_t<!is_same<T, void>::value, void>
{
    cout << val << " ";
}

// C++20 可以用 concepts 更简洁地实现类似功能：
// template<typename T> requires (!is_same<T, void>::value)
// void printValue(T val) { ... }


// ==================== 第三部分：constexpr 编译期计算 ====================

// constexpr 函数：可以在编译期执行
constexpr int factorial(int n)
{
    // C++14 起允许 if 和局部变量
    int result = 1;
    for (int i = 1; i <= n; i++)
    {
        result *= i;
    }
    return result;
}

// constexpr 也能用于类
class Point
{
public:
    constexpr Point(double x, double y) : m_X(x), m_Y(y) {}
    constexpr double getX() const { return m_X; }
    constexpr double getY() const { return m_Y; }
    constexpr double distance() const
    {
        // sqrt 在 C++14 后可以是 constexpr（gcc/clang)
        return m_X * m_X + m_Y * m_Y;
    }

private:
    double m_X, m_Y;
};

// 编译期斐波那契
constexpr int fib(int n)
{
    if (n <= 1) return n;
    int a = 0, b = 1;
    for (int i = 2; i <= n; i++)
    {
        int c = a + b;
        a = b;
        b = c;
    }
    return b;
}

void test03_constexpr_basics()
{
    cout << "\n========== constexpr 编译期计算 ==========" << endl;

    // 编译期计算
    constexpr int fact5 = factorial(5);  // 编译期算出 120！
    cout << "factorial(5) = " << fact5 << "  (编译期计算！)" << endl;
    cout << "fib(10)      = " << fib(10) << " (编译期计算！)" << endl;

    // 运行时也能用同一个函数
    int n;
    cout << "输入 n 求阶乘: ";
    cin >> n;
    cout << "factorial(" << n << ") = " << factorial(n)
         << " (运行时计算)" << endl;

    // constexpr 类
    constexpr Point p(3.0, 4.0);
    constexpr double dist = p.distance(); // 编译期计算！
    cout << "Point(3,4).distance() = " << dist << " (编译期！)" << endl;

    // 编译期保证：constexpr 变量会强制编译期求值
    // constexpr int bad = factorial(-1); // 编译错误！编译器能检测
}

// ---- 实战：编译期素数判断 ----
constexpr bool isPrime(int n)
{
    if (n < 2) return false;
    for (int i = 2; i * i <= n; i++)
    {
        if (n % i == 0) return false;
    }
    return true;
}

void test04_constexpr_practice()
{
    cout << "\n========== constexpr 实战 ==========" << endl;

    // 编译期判断，零运行时开销
    constexpr bool p7  = isPrime(7);
    constexpr bool p10 = isPrime(10);
    constexpr bool p97 = isPrime(97);

    cout << "isPrime(7)  = " << (p7  ? "是" : "否") << endl;
    cout << "isPrime(10) = " << (p10 ? "是" : "否") << endl;
    cout << "isPrime(97) = " << (p97 ? "是" : "否") << endl;

    // 可以在 static_assert 中使用（编译期断言）
    static_assert(isPrime(2), "2 必须是素数");
    static_assert(!isPrime(1), "1 不是素数");
    // static_assert(isPrime(4), "编译失败！"); // 这行会编译错误
    cout << "\nstatic_assert 验证通过（如果上面有错误编译会失败）" << endl;
}


// ==================== 第四部分：if constexpr (C++17) ====================

// if constexpr: 编译期条件分支
// 只有满足条件的分支会被编译，不满足的直接丢弃

template<typename T>
auto getValueDescription(const T& val)
{
    if constexpr (is_integral<T>::value)
    {
        return to_string(val) + " (整数类型)";
    }
    else if constexpr (is_floating_point<T>::value)
    {
        return to_string(val) + " (浮点类型)";
    }
    else if constexpr (is_same<T, string>::value)
    {
        return val + " (字符串类型)";
    }
    else
    {
        return string("(其他类型)");
    }
}

// 为什么不用普通 if？
// 普通 if 要求所有分支都能编译通过
// 例如: if (is_integral<T>::value) { return val + 0; }
// 如果 T=string，val+0 无法编译 → 即使这个分支不会执行，也会编译错误
// if constexpr 解决了这个问题：不满足条件的分支直接不编译

void test05_if_constexpr()
{
    cout << "\n========== if constexpr (C++17) ==========" << endl;

    cout << "42:       " << getValueDescription(42) << endl;
    cout << "3.14:     " << getValueDescription(3.14) << endl;
    cout << "\"Hello\": " << getValueDescription(string("Hello")) << endl;
    cout << "'A':      " << getValueDescription('A') << endl;

    cout << "\nif constexpr vs 普通 if:" << endl;
    cout << "  普通 if:  所有分支都编译，必须对所有 T 合法" << endl;
    cout << "  if constexpr: 只编译满足条件的分支（编译期分支）" << endl;
    cout << "  优势: 可以在不同分支做对 T 可能不合法的操作" << endl;
}

// ---- 编译期类型分派 ----
template<typename T>
void processContainer(const T& container)
{
    if constexpr (is_same<T, vector<int>>::value)
    {
        cout << "vector<int> 特化处理: sum = ";
        int sum = 0;
        for (int x : container) sum += x;
        cout << sum << endl;
    }
    else
    {
        cout << "通用处理: size = " << container.size() << endl;
    }
}

void test06_compile_time_dispatch()
{
    cout << "\n========== 编译期类型分派 ==========" << endl;

    vector<int> v = {1, 2, 3, 4, 5};
    string s = "Hello";

    processContainer(v);                 // 走特化分支
    processContainer(s);                 // 走通用分支
}


int main()
{
    cout << "========================================" << endl;
    cout << "| 模板与泛型(3) — 类型萃取与constexpr |" << endl;
    cout << "========================================" << endl;

    test01_type_traits();
    test02_enable_if();
    test03_constexpr_basics();
    test04_constexpr_practice();
    test05_if_constexpr();
    test06_compile_time_dispatch();

    system("pause");
    return 0;
}

// 完结撒花*
