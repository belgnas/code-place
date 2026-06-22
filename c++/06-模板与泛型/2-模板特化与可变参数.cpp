// 模板与泛型 (2) — 模板特化与可变参数模板
//
// 编译需要 C++17: g++ -std=c++17 2-模板特化与可变参数.cpp -o output.exe
//
// 【模板特化】
//   为特定类型提供不同于通用模板的实现
//   全特化: 对所有模板参数指定具体类型
//   偏特化: 只特化部分模板参数
//
// 【非类型模板参数】
//   模板参数不一定是类型，也可以是值：
//   template<typename T, int N>  → N 是编译期常量
//   典型: std::array<int, 5>
//
// 【可变参数模板】(C++11)
//   template<typename... Args>
//   Args... = 参数包（parameter pack），可以包含零个或多个类型
//   这是现代 C++ 库的核心技术（tuple, make_shared, emplace_back 都依赖它）


#include<iostream>
#include<string>
#include<vector>
#include<type_traits>
#include<stdexcept>  // runtime_error
using namespace std;


// ==================== 第一部分：模板特化 ====================

// 通用模板：打印类型名
template<typename T>
struct TypeName
{
    static const char* get() { return "未知类型"; }
};

// 全特化：为 int 提供特定版本
template<>
struct TypeName<int>
{
    static const char* get() { return "int"; }
};

// 全特化：为 double
template<>
struct TypeName<double>
{
    static const char* get() { return "double"; }
};

// 全特化：为 string
template<>
struct TypeName<string>
{
    static const char* get() { return "string"; }
};

void test01_full_specialization()
{
    cout << "\n========== 模板全特化 ==========" << endl;

    cout << "TypeName<int>::get()    = " << TypeName<int>::get() << endl;
    cout << "TypeName<double>::get() = " << TypeName<double>::get() << endl;
    cout << "TypeName<string>::get() = " << TypeName<string>::get() << endl;
    cout << "TypeName<char>::get()   = " << TypeName<char>::get()
         << "  ← 走通用模板" << endl;
}

// ---- 偏特化 ----

// 通用模板：判断是否为指针
template<typename T>
struct IsPointer
{
    static const bool value = false;
};

// 偏特化：T* 版本（T 仍是模板参数）
template<typename T>
struct IsPointer<T*>
{
    static const bool value = true;
};

// 偏特化：const T* 版本
template<typename T>
struct IsPointer<const T*>
{
    static const bool value = true;
};

// 偏特化：两个类型相同？
template<typename T, typename U>
struct IsSame
{
    static const bool value = false;
};

template<typename T>
struct IsSame<T, T>                      // 两个参数相同的时候匹配
{
    static const bool value = true;
};

void test02_partial_specialization()
{
    cout << "\n========== 模板偏特化 ==========" << endl;

    cout << "IsPointer<int>::value    = " << IsPointer<int>::value << endl;
    cout << "IsPointer<int*>::value   = " << IsPointer<int*>::value << endl;
    cout << "IsPointer<const int*>::value = " << IsPointer<const int*>::value << endl;

    cout << "\nIsSame<int, int>::value   = " << IsSame<int, int>::value << endl;
    cout << "IsSame<int, double>::value = " << IsSame<int, double>::value << endl;

    // C++ 标准库有 std::is_pointer, std::is_same 等 trait
    cout << "\n标准库版本:" << endl;
    cout << "  is_pointer<int>::value = " << is_pointer<int>::value << endl;
    cout << "  is_pointer<int*>::value = " << is_pointer<int*>::value << endl;
    cout << "  is_same<int, int>::value = " << is_same<int, int>::value << endl;
}


// ==================== 第二部分：非类型模板参数 ====================

// 编译期定长数组
template<typename T, size_t N>
class FixedArray
{
public:
    FixedArray() = default;

    FixedArray(initializer_list<T> init)
    {
        size_t i = 0;
        for (const auto& val : init)
        {
            if (i < N) m_Data[i++] = val;
        }
    }

    T& operator[](size_t index) { return m_Data[index]; }
    const T& operator[](size_t index) const { return m_Data[index]; }

    size_t size() const { return N; }

    T* begin() { return m_Data; }
    T* end()   { return m_Data + N; }
    const T* begin() const { return m_Data; }
    const T* end()   const { return m_Data + N; }

private:
    T m_Data[N];                         // 编译期确定大小，栈上分配
    // 对比 vector<T> 在堆上分配，FixedArray 零开销！
};

void test03_non_type_param()
{
    cout << "\n========== 非类型模板参数 ==========" << endl;

    FixedArray<int, 5> arr = {1, 2, 3, 4, 5};

    cout << "FixedArray<int, 5>: ";
    for (size_t i = 0; i < arr.size(); i++)
        cout << arr[i] << " ";
    cout << endl;

    // 类型不同就是不同类！
    // FixedArray<int, 5> 和 FixedArray<int, 10> 是不同的类型

    // C++ 标准库: std::array<T, N>
    cout << "\n非类型模板参数可以是:" << endl;
    cout << "  整数 (int, size_t, ...)" << endl;
    cout << "  枚举" << endl;
    cout << "  指针 / 引用 (C++17 前有限制)" << endl;
    cout << "  auto (C++17)" << endl;
}


// ==================== 第三部分：可变参数模板 ====================

// ---- 基础：递归展开 ----

// 递归终止条件（零参数）
void printAll()
{
    cout << endl;                        // 换行
}

// 递归展开：每次处理第一个参数，剩下的递归
template<typename T, typename... Args>
void printAll(const T& first, const Args&... rest)
{
    cout << first;
    if constexpr (sizeof...(rest) > 0)   // C++17: 编译期 if
        cout << ", ";
    printAll(rest...);                   // 递归调用，rest... 展开剩余参数
}

void test04_variadic_basics()
{
    cout << "\n========== 可变参数模板基础 ==========" << endl;

    printAll(1, 2.5, "Hello", 'A');
    // 展开过程:
    // printAll(1, 2.5, "Hello", 'A')
    //   → cout << 1; printAll(2.5, "Hello", 'A')
    //     → cout << 2.5; printAll("Hello", 'A')
    //       → cout << "Hello"; printAll('A')
    //         → cout << 'A'; printAll() → 结束

    cout << "\n参数个数: " << endl;
    cout << "  printAll(1, 2, 3) → sizeof...(args) = "
         << ([] { /* 无法在非模板中获取，演示用 */ return 3; })() << endl;
}

// ---- 实战：类型安全的 printf ----

// 递归终止
void formatPrint(const char* format)
{
    while (*format)
    {
        if (*format == '%')
        {
            throw runtime_error("format 参数数量不匹配！");
        }
        cout << *format;
        format++;
    }
}

// 每次处理一个格式化占位符
template<typename T, typename... Args>
void formatPrint(const char* format, const T& value, const Args&... rest)
{
    while (*format)
    {
        if (*format == '%')
        {
            cout << value;               // 打印当前值
            formatPrint(format + 1, rest...);  // 递归处理剩余
            return;
        }
        cout << *format;
        format++;
    }
    // format 用完但还有参数 → 忽略（或报错）
}

void test05_safe_printf()
{
    cout << "\n========== 实践：类型安全的 printf ==========" << endl;

    formatPrint("姓名: %, 年龄: %, 成绩: %\n", "张三", 20, 92.5);

    // 对比 C 语言的 printf，模板版本是类型安全的
    // printf("%s %d %f\n", 42, "wrong", 3.14);  // ⚠ 不匹配但编译器不报错！
    // formatPrint("%, %", 42, "wrong");        // 安全的！类型自动匹配

    cout << "\n优点: 完全类型安全，没有 %d/%s/%f 的匹配问题" << endl;
}

// ---- 折叠表达式 (C++17) ----

// C++17 折叠表达式语法:
// (... op args)       → (a1 op a2) op a3 ...
// (args op ...)       → a1 op (a2 op a3) ...
// (init op ... op args)

template<typename... Args>
auto sum_fold(Args... args)
{
    return (... + args);                 // 一元左折叠: ((a1 + a2) + a3) + ...
}

template<typename... Args>
auto product_fold(Args... args)
{
    return (1 * ... * args);             // 二元左折叠: (((1 * a1) * a2) * a3) ...
}

template<typename... Args>
bool allTrue(Args... args)
{
    return (... && args);                // (a1 && a2) && a3 ...
}

template<typename... Args>
bool anyTrue(Args... args)
{
    return (... || args);                // (a1 || a2) || a3 ...
}

void test06_fold_expressions()
{
    cout << "\n========== 折叠表达式 (C++17) ==========" << endl;

    cout << "sum_fold(1, 2, 3, 4, 5)    = " << sum_fold(1, 2, 3, 4, 5) << endl;
    cout << "product_fold(1, 2, 3, 4, 5) = " << product_fold(1, 2, 3, 4, 5) << endl;

    cout << "allTrue(true, true, false)  = "
         << (allTrue(true, true, false) ? "true" : "false") << endl;
    cout << "anyTrue(false, false, true) = "
         << (anyTrue(false, false, true) ? "true" : "false") << endl;

    cout << "\n折叠表达式 vs 递归展开:" << endl;
    cout << "  折叠表达式更简洁，但只能用于运算符" << endl;
    cout << "  递归展开更灵活，可以做任意操作" << endl;
}

// ---- 可变参数模板的应用 ----
// emplace_back 的实现原理示意:
template<typename Container, typename... Args>
void emplace_demo(Container& c, Args&&... args)
{
    // 完美转发所有参数给容器元素的构造函数
    // c.emplace_back(forward<Args>(args)...);
    // 这里无法真正调用（没有对应类定义），仅做原理示意
    cout << "  emplace_back 通过可变参数模板 + 完美转发实现" << endl;
    cout << "  参数个数: " << sizeof...(args) << endl;
}


int main()
{
    cout << "========================================" << endl;
    cout << "| 模板与泛型(2) — 特化与可变参数      |" << endl;
    cout << "========================================" << endl;

    test01_full_specialization();
    test02_partial_specialization();
    test03_non_type_param();
    test04_variadic_basics();
    test05_safe_printf();
    test06_fold_expressions();

    system("pause");
    return 0;
}

// 完结撒花*
