// Modern C++ (4) — 移动语义与右值引用
//
// 【左值 vs 右值】
//   左值 (lvalue):  有名字、能取地址的对象，可以出现在赋值号左边
//   右值 (rvalue):  临时对象、字面量，不能取地址
//   例: int a = 10;  // a 是左值，10 是右值
//       a + b       // 表达式结果是右值（临时值）
//
//   C++11 进一步细分：
//   - 左值 (lvalue): 常规变量
//   - 纯右值 (prvalue): 字面量、临时表达式结果
//   - 亡值 (xvalue): 即将被销毁的右值（如 std::move 的结果）
//
// 【左值引用 vs 右值引用】
//   左值引用 & : 绑定左值                int&  r = x;  // OK
//   右值引用 &&: 绑定右值（临时对象）     int&& r = 10; // OK
//   常量左值引用 const&: 万能引用        const int& r = 10; // OK
//
// 【移动语义】
//   "偷"即将销毁的对象的资源，避免昂贵拷贝
//   移动构造 / 移动赋值 = 浅拷贝指针 + 置空源对象
//
// 【std::move】
//   将左值转为右值引用（只是类型转换，不移动任何东西！）
//   相当于："我要放弃这个对象了，请随意掠夺它的资源"
//
// 【std::forward】
//   完美转发：保留参数的值类别（左值保持左值，右值保持右值）


#include<iostream>
#include<string>
#include<vector>
#include<cstring>    // strlen
#include<chrono>     // 计时
#include<memory>     // make_unique, make_shared
#include<utility>    // swap
#include<cstdlib>    // system  (用于设置控制台代码页)
using namespace std;


// ==================== 第一部分：左值/右值概念 ====================

void test01_lvalue_rvalue()
{
    cout << "\n========== 左值 vs 右值 ==========" << endl;

    int x = 10;                          // x 是左值，10 是右值（字面量）
    int y = 20;

    // 左值引用
    int& lref = x;                       // OK: 左值引用绑定左值
    // int& lref2 = 10;                  // 错误！左值引用不能绑定右值
    const int& clref = 10;               // OK: const 左值引用可以绑定右值
    (void)clref;                         // 消除未使用警告

    // 右值引用
    // int&& rref1 = x;                  // 错误！右值引用不能绑定左值
    int&& rref2 = 10;                    // OK: 右值引用绑定右值
    int&& rref3 = x + y;                 // OK: x + y 是临时结果（右值）

    // 右值引用本身是左值！（有名字，能取地址）
    // int&& rref4 = rref2;              // 错误！rref2 虽然是右值引用类型，但它是左值
    int&& rref4 = move(rref2);           // OK: move 把左值转成右值
    (void)rref4;                         // 消除未使用警告

    cout << "x (左值)       = " << x << endl;
    cout << "lref (左值引用) = " << lref << endl;
    cout << "rref2 (右值引用) = " << rref2 << endl;
    cout << "rref3 (x+y)     = " << rref3 << endl;

    cout << "\n关键：右值引用变量本身是左值（有名字）！" << endl;
    cout << "      要用 std::move 才能把它变成右值。" << endl;
}


// ==================== 第二部分：移动语义实战 ====================

// 一个用原始指针管理内存的类（模拟大资源）
class MyString
{
public:
    // ---- 普通构造 ----
    MyString(const char* str = "")
    {
        m_Size = strlen(str);
        m_Data = new char[m_Size + 1];
        strcpy(m_Data, str);
        cout << "  [构造] \"" << m_Data << "\"" << endl;
    }

    // ---- 拷贝构造（深拷贝） ----
    MyString(const MyString& other)
    {
        m_Size = other.m_Size;
        m_Data = new char[m_Size + 1];
        strcpy(m_Data, other.m_Data);
        cout << "  [拷贝构造] \"" << m_Data << "\" (慢！需要分配+复制)" << endl;
    }

    // ---- 拷贝赋值 ----
    MyString& operator=(const MyString& other)
    {
        if (this != &other)
        {
            delete[] m_Data;
            m_Size = other.m_Size;
            m_Data = new char[m_Size + 1];
            strcpy(m_Data, other.m_Data);
        }
        cout << "  [拷贝赋值] \"" << m_Data << "\"" << endl;
        return *this;
    }

    // ---- * 移动构造（C++11 新增） ----
    // 参数是右值引用，表示"我要偷这个即将消亡的对象"
    MyString(MyString&& other) noexcept
        : m_Size(other.m_Size)
        , m_Data(other.m_Data)           // 直接"偷"走指针！
    {
        // 置空源对象，防止析构时 delete 我们偷走的资源
        other.m_Size = 0;
        other.m_Data = nullptr;
        cout << "  [移动构造] (快！只偷指针，O(1))" << endl;
    }

    // ---- * 移动赋值（C++11 新增） ----
    MyString& operator=(MyString&& other) noexcept
    {
        if (this != &other)
        {
            delete[] m_Data;             // 释放自己的旧数据

            m_Size = other.m_Size;
            m_Data = other.m_Data;       // 偷走指针

            other.m_Size = 0;
            other.m_Data = nullptr;
        }
        cout << "  [移动赋值] (快！O(1))" << endl;
        return *this;
    }

    // ---- 析构 ----
    ~MyString()
    {
        if (m_Data)
        {
            cout << "  [析构] \"" << m_Data << "\"" << endl;
        }
        delete[] m_Data;
    }

    void print() const
    {
        if (m_Data)
            cout << "\"" << m_Data << "\"";
        else
            cout << "(null)";
    }

private:
    size_t m_Size;
    char*  m_Data;
};

void test02_move_demo()
{
    cout << "\n========== 移动语义演示 ==========" << endl;

    // ---- 场景 1：从临时对象构造（自动使用移动构造） ----
    cout << "场景1: MyString s2 = MyString(\"临时字符串\");" << endl;
    MyString s2 = MyString("临时字符串");
    // 编译器知道 MyString("临时字符串") 是右值（临时对象）
    // → 自动调用移动构造！
    cout << "结果: s2 = ";
    s2.print();
    cout << endl;

    // ---- 场景 2：主动使用 std::move ----
    cout << "\n场景2: std::move" << endl;
    MyString s3("原始数据");
    cout << "s3 = "; s3.print(); cout << endl;

    MyString s4 = move(s3);              // move 把 s3 变成右值
    cout << "move 后 s4 = "; s4.print(); cout << endl;
    cout << "move 后 s3 = "; s3.print(); cout << " ← 已被掏空" << endl;
    // ⚠ move 后不要再使用 s3！除非先给它赋新值

    // ---- 场景 3：放入 vector ----
    cout << "\n场景3: vector::push_back" << endl;
    vector<MyString> vec;
    vec.push_back(MyString("Hello"));    // 临时对象 → 移动
    vec.push_back(MyString("World"));

    cout << "\nvector 内容: ";
    for (const auto& s : vec) { s.print(); cout << " "; }
    cout << endl;
}

void test03_copy_vs_move()
{
    cout << "\n========== 拷贝 vs 移动 性能对比 ==========" << endl;

    const int N = 10000;
    const int STR_SIZE = 10000;  // 10KB 字符串

    // 构造一个包含大量数据的字符串
    string bigStr(STR_SIZE, 'A');

    // --- 拷贝：每次都要分配+复制 ---
    auto copyStart = chrono::high_resolution_clock::now();
    vector<string> copyVec;
    copyVec.reserve(N);
    for (int i = 0; i < N; i++)
    {
        copyVec.push_back(bigStr);       // 拷贝 10KB × 10000 = 100MB 复制
    }
    auto copyEnd = chrono::high_resolution_clock::now();
    auto copyTime = chrono::duration_cast<chrono::milliseconds>(copyEnd - copyStart);

    // --- 移动：只交换指针 ---
    vector<string> tempVec(N, bigStr);   // 先创建 N 个副本

    auto moveStart = chrono::high_resolution_clock::now();
    vector<string> moveVec;
    moveVec.reserve(N);
    for (int i = 0; i < N; i++)
    {
        moveVec.push_back(move(tempVec[i])); // 移动 O(1)
    }
    auto moveEnd = chrono::high_resolution_clock::now();
    auto moveTime = chrono::duration_cast<chrono::milliseconds>(moveEnd - moveStart);

    cout << "操作: push_back " << N << " 个 " << STR_SIZE << " 字节字符串" << endl;
    cout << "  拷贝: " << copyTime.count() << "ms" << endl;
    cout << "  移动: " << moveTime.count() << "ms" << endl;
    cout << "  (移动只需交换内部指针，与字符串大小无关！)" << endl;
}


// ==================== 第三部分：五法则 ====================

void test04_rule_of_five()
{
    cout << "\n========== 五法则 ==========" << endl;

    // 五法则：如果你需要自定义以下任一函数，通常也需要定义所有 5 个
    // 1. 析构函数
    // 2. 拷贝构造函数
    // 3. 拷贝赋值运算符
    // 4. 移动构造函数       (C++11 新增)
    // 5. 移动赋值运算符     (C++11 新增)

    // 编译器生成规则：
    // - 声明移动操作 → 不自动生成拷贝操作（已弃用）
    // - 声明拷贝操作 → 不自动生成移动操作
    // - 声明析构函数 → 不自动生成移动操作（拷贝操作仍生成但是已弃用）

    // 最佳实践：用 = default 显式声明
    // 如果类只管理使用智能指针的资源，用"零法则"
    // （编译器自动生成的都是正确的）

    cout << "五法则速查表:" << endl;
    cout << "┌──────────────────┬──────────────────────────┐" << endl;
    cout << "│ 管理原始资源      │ 写全五法则               │" << endl;
    cout << "│ 只管理智能指针    │ 零法则 (= default 即可)  │" << endl;
    cout << "│ 不可拷贝资源      │ 删除拷贝，保留移动       │" << endl;
    cout << "└──────────────────┴──────────────────────────┘" << endl;

    // 不可拷贝的例子：unique_ptr 模式
    class NonCopyable
    {
    public:
        NonCopyable(int val) : data(new int(val)) {}

        // 删除拷贝
        NonCopyable(const NonCopyable&) = delete;
        NonCopyable& operator=(const NonCopyable&) = delete;

        // 允许移动
        NonCopyable(NonCopyable&& other) noexcept
            : data(other.data)
        {
            other.data = nullptr;
        }
        NonCopyable& operator=(NonCopyable&& other) noexcept
        {
            if (this != &other)
            {
                delete data;
                data = other.data;
                other.data = nullptr;
            }
            return *this;
        }

        ~NonCopyable() { delete data; }
        int getValue() const { return *data; }

    private:
        int* data;
    };

    NonCopyable a(10);
    // NonCopyable b = a;                  // 编译错误！拷贝被删除
    NonCopyable b = move(a);               // OK，移动构造
    cout << "\nNonCopyable: b.getValue() = " << b.getValue() << endl;
}


// ==================== 第四部分：完美转发 ====================

// ---- 辅助重载函数（用于演示完美转发） ----
void inner(int& x)
{
    (void)x;  // 消除未使用参数警告
    cout << "  inner 收到 左值引用" << endl;
}
void inner(int&& x)
{
    (void)x;  // 消除未使用参数警告
    cout << "  inner 收到 右值引用" << endl;
}

void test05_perfect_forward()
{
    cout << "\n========== 完美转发 ==========" << endl;

    // 问题：把参数从外层函数传到内层函数时，如何保留值类别？

    // ---- 没有完美转发 ----
    // 错误的外层函数：参数永远是左值！
    auto outer_bad = [&](int&& x)
    {
        // inner(x);                     // 错误！x 是左值（有名字）且无法区分
        // 用 move — 但这样无论传进来的是左值还是右值都被当成右值
        inner(move(x));                 // 强制移动 → 不安全（丢失左值信息）
    };
    (void)outer_bad;                     // 消除未使用变量警告

    // ---- 完美转发：forward ----
    auto outer_good = [&](auto&& x)      // auto&& = 万能引用（转发引用）
    {
        // forward 根据 x 的实际类型决定转发为左值还是右值
        inner(forward<decltype(x)>(x));
        // 如果传入的是左值 → forward 为左值引用 → 匹配 inner(int&)
        // 如果传入的是右值 → forward 为右值引用 → 匹配 inner(int&&)
    };

    cout << "传入左值:" << endl;
    int val = 42;
    outer_good(val);                      // val 是左值 → inner(int&)

    cout << "传入右值:" << endl;
    outer_good(42);                       // 42 是右值 → inner(int&&)
    outer_good(move(val));                // move(val) 是右值 → inner(int&&)

    // ---- 完美转发的典型应用 ----
    // make_unique, make_shared, vector::emplace_back 都用了完美转发
    // 把构造参数原封不动地传给对象的构造函数

    cout << "\n完美转发的典型应用:" << endl;
    cout << "  emplace_back(args...): 把参数完美转发给构造函数" << endl;
    cout << "  make_unique<T>(args...): 同理" << endl;
    cout << "  make_shared<T>(args...): 同理" << endl;
}

void test06_move_usage()
{
    cout << "\n========== std::move 使用场景 ==========" << endl;

    // 场景 1：把对象放入容器（不再需要原对象）
    string s = "Hello World";
    vector<string> v;
    v.push_back(move(s));                // 移动而非拷贝
    // s 现在是空字符串（被掏空但有效）
    cout << "move 后 s = \"" << s << "\"" << endl;

    // 场景 2：交换两个对象（高效）
    string a = "first";
    string b = "second";
    swap(a, b);                          // swap 内部使用移动
    cout << "swap 后: a=\"" << a << "\", b=\"" << b << "\"" << endl;

    // 场景 3：unique_ptr 所有权转移
    auto p1 = make_unique<int>(10);
    auto p2 = move(p1);                  // p1 是左值，move 后才能转移
    // p1 现在是 nullptr

    // ⚠ 不要 move 的场景
    // - 不确定源对象是否还会被使用
    // - 函数返回值：return local_var; 自动使用移动，不要 return move(local_var)!

    cout << "\n⚠ 不要 move 的情况:" << endl;
    cout << "  1. return local_var;  编译器自动优化，不要写 return move(local_var)" << endl;
    cout << "  2. 不确定原对象后续是否还会被使用" << endl;
    cout << "  3. const 对象 move 无效（const 对象不可修改，退化为拷贝）" << endl;
}


int main()
{
    // 设置控制台代码页为 UTF-8（Windows），避免中文乱码
    system("chcp 65001 > nul");

    cout << "========================================" << endl;
    cout << "| Modern C++(4) — 移动语义与右值引用  |" << endl;
    cout << "========================================" << endl;

    test01_lvalue_rvalue();
    test02_move_demo();
    test03_copy_vs_move();
    test04_rule_of_five();
    test05_perfect_forward();
    test06_move_usage();

    system("pause");
    return 0;
}

// 完结撒花*