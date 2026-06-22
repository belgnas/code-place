// 模板与泛型 (1) — 函数模板与类模板
//
// 【为什么需要模板】
//   没有模板时，同一逻辑需要为不同数据类型写多份代码：
//     int    max_int(int a, int b)    { return a > b ? a : b; }
//     double max_double(double a, double b) { ... }
//     string max_string(string a, string b) { ... }
//   → 逻辑重复，维护噩梦！
//
//   模板 = 泛型编程的基础，让你"一次编写，任意类型使用"
//   C++ 的模板是编译期泛型：编译器为每种使用到的类型生成一份具体代码
//
// 【函数模板】
//   template<typename T>  或  template<class T>
//   T 是"模板参数"，编译时被替换为具体类型
//
// 【类模板】
//   整个类的定义参数化
//   template<typename T> class Stack { ... };
//   使用时: Stack<int> intStack;


#include<iostream>
#include<string>
#include<vector>
#include<stdexcept>
using namespace std;


// ==================== 第一部分：函数模板 ====================

// 函数模板：最大值
template<typename T>
T myMax(T a, T b)
{
    return (a > b) ? a : b;
    // 要求类型 T 支持 operator>
}

// 函数模板：交换两个值
template<typename T>
void mySwap(T& a, T& b)
{
    T temp = a;
    a = b;
    b = temp;
}

// 函数模板：打印数组
template<typename T>
void printArray(const T* arr, int size)
{
    cout << "[ ";
    for (int i = 0; i < size; i++)
    {
        cout << arr[i];
        if (i != size - 1) cout << ", ";
    }
    cout << " ]" << endl;
}

// 多个模板参数
template<typename T1, typename T2>
auto add(T1 a, T2 b) -> decltype(a + b)  // C++11 尾置返回类型
{
    return a + b;
}
// C++14 可以更简洁: auto add14(T1 a, T2 b) { return a + b; }

void test01_func_template()
{
    cout << "\n========== 函数模板基础 ==========" << endl;

    // 模板参数自动推导
    cout << "myMax(3, 5)     = " << myMax(3, 5) << endl;
    cout << "myMax(3.14, 2.7) = " << myMax(3.14, 2.7) << endl;
    cout << "myMax('a', 'z')  = " << myMax('a', 'z') << endl;
    // myMax(3, 3.14) ← 错误！T 无法同时推导为 int 和 double
    // 解决方案: myMax<double>(3, 3.14) 显式指定类型

    // mySwap
    int a = 10, b = 20;
    mySwap(a, b);
    cout << "mySwap 后: a=" << a << ", b=" << b << endl;

    string s1 = "Hello", s2 = "World";
    mySwap(s1, s2);
    cout << "mySwap 后: s1=" << s1 << ", s2=" << s2 << endl;

    // 多模板参数
    cout << "\nadd(3, 4.5)   = " << add(3, 4.5) << endl;   // int + double
    cout << "add(3.14, 10)  = " << add(3.14, 10) << endl;    // double + int
    cout << "add(\"Hello \", string(\"World\")) = "
         << add("Hello ", string("World")) << endl;
}

void test02_template_deduction()
{
    cout << "\n========== 模板参数推导规则 ==========" << endl;

    // ---- 规则 1：值传递会退化 ----
    // template<typename T> void byValue(T t)
    // const 会被剥离、数组退化为指针、函数退化为函数指针
    //
    // ---- 规则 2：引用传递保留类型 ----
    // template<typename T> void byRef(T& t)
    // T 会包含 const/volatile 修饰符

    // ---- 显式指定模板参数 ----
    cout << "myMax<int>(3, 5)           = " << myMax<int>(3, 5) << endl;
    cout << "myMax<double>(3.14, 2.72)  = " << myMax<double>(3.14, 2.72) << endl;

    // 必须显式指定的情况：参数类型不匹配
    // cout << myMax(3, 4.5) << endl;    // 错误！推导冲突
    cout << "myMax<double>(3, 4.5)       = " << myMax<double>(3, 4.5) << endl;
    // 显式指定 T=double，3 自动转为 double

    // ---- 普通函数 vs 函数模板 ----
    // 如果同时存在，普通函数优先匹配
    // 也可以用 myMax<>(3, 5) 强制使用模板版本
}


// ==================== 第二部分：类模板 ====================

// 类模板：通用栈
template<typename T>
class Stack
{
public:
    Stack() = default;
    Stack(int capacity) : m_Capacity(capacity) { m_Data.reserve(capacity); }

    void push(const T& value)
    {
        m_Data.push_back(value);
    }

    void push(T&& value)                 // 移动版本（右值引用）
    {
        m_Data.push_back(move(value));
    }

    T pop()
    {
        if (m_Data.empty())
            throw out_of_range("Stack::pop(): 栈为空！");
        T val = move(m_Data.back());
        m_Data.pop_back();
        return val;
    }

    T& top()
    {
        if (m_Data.empty())
            throw out_of_range("Stack::top(): 栈为空！");
        return m_Data.back();
    }

    const T& top() const
    {
        if (m_Data.empty())
            throw out_of_range("Stack::top(): 栈为空！");
        return m_Data.back();
    }

    bool empty() const { return m_Data.empty(); }
    size_t size() const { return m_Data.size(); }

private:
    vector<T> m_Data;
    int m_Capacity = 0;
};

void test03_class_template()
{
    cout << "\n========== 类模板基础 ==========" << endl;

    // 使用类模板：必须指定类型参数
    Stack<int> intStack;
    intStack.push(1);
    intStack.push(2);
    intStack.push(3);

    cout << "intStack: ";
    while (!intStack.empty())
    {
        cout << intStack.top() << " ";
        intStack.pop();
    }
    cout << endl;

    // 字符串栈
    Stack<string> strStack;
    strStack.push("Hello");
    strStack.push("World");

    cout << "strStack: ";
    while (!strStack.empty())
    {
        cout << strStack.top() << " ";
        strStack.pop();
    }
    cout << endl;
}

// 类模板：简单的 Pair
template<typename T1, typename T2>
class Pair
{
public:
    Pair() = default;
    Pair(const T1& first, const T2& second)
        : first(first), second(second) {}

    T1 first;
    T2 second;
};

void test04_multi_param_template()
{
    cout << "\n========== 多参数类模板 ==========" << endl;

    Pair<string, int> p1("Alice", 85);
    Pair<string, double> p2("Pi", 3.14159);
    Pair<int, string> p3(404, "Not Found");

    cout << "Pair<string, int>:    " << p1.first << " → " << p1.second << endl;
    cout << "Pair<string, double>: " << p2.first << " → " << p2.second << endl;
    cout << "Pair<int, string>:    " << p1.first << " → " << p1.second << endl;

    // C++11 也有 std::pair，比我们的手写版更完善
    // std::pair 有 make_pair, 比较运算符, swap 等
}

// 类模板：成员函数在类外定义
template<typename T>
class MyVector
{
public:
    MyVector() = default;
    void push_back(const T& value);
    size_t size() const { return m_Data.size(); }
    T& operator[](size_t index) { return m_Data[index]; }

private:
    vector<T> m_Data;
};

// 类模板的成员函数在类外定义时，每个函数前都要写 template<typename T>
template<typename T>
void MyVector<T>::push_back(const T& value)  // 注意 MyVector<T> 不是 MyVector
{
    m_Data.push_back(value);
}

void test05_member_out_of_class()
{
    cout << "\n========== 类模板成员函数类外定义 ==========" << endl;

    MyVector<double> v;
    v.push_back(1.1);
    v.push_back(2.2);
    v.push_back(3.3);

    cout << "MyVector: ";
    for (size_t i = 0; i < v.size(); i++)
        cout << v[i] << " ";
    cout << endl;

    cout << "\n注意：类模板的声明和定义通常放在同一个 .h 文件中。" << endl;
    cout << "      分离到 .cpp 会导致链接错误（模板需要编译期实例化）。" << endl;
}


int main()
{
    cout << "========================================" << endl;
    cout << "|  模板与泛型(1) — 函数模板与类模板   |" << endl;
    cout << "========================================" << endl;

    test01_func_template();
    test02_template_deduction();
    test03_class_template();
    test04_multi_param_template();
    test05_member_out_of_class();

    system("pause");
    return 0;
}

// 完结撒花*
