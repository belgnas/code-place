// 异常处理与 RAII (1) — 异常处理与资源管理
//
// 【为什么需要异常处理】
//   传统错误处理方式的问题：
//   1. 返回错误码 — 调用者可能忘记检查，且不能用于构造函数
//   2. assert      — 只在 Debug 模式生效，Release 被移除
//   3. exit()      — 直接终止程序，没有恢复机会
//   异常机制：将错误检测与错误处理分离，强制处理或传播
//
// 【异常处理语法】
//   try { 可能出错的代码 }
//   catch (异常类型& e) { 处理 }
//   栈展开 (stack unwinding): 异常发生时，函数栈逐层退出，
//   所有局部对象的析构函数被调用 → RAII 自然保证资源释放
//
// 【RAII】"资源获取即初始化" (Resource Acquisition Is Initialization)
//   C++ 最重要的资源管理原则：
//   - 资源在构造时获取
//   - 资源在析构时释放
//   - 生命周期绑定到作用域
//
//   例子：lock_guard, unique_ptr, fstream, string


#include<iostream>
#include<string>
#include<vector>
#include<stdexcept>  // 标准异常类
#include<memory>     // unique_ptr
#include<mutex>      // lock_guard, unique_lock
#include<fstream>    // fstream
#include<utility>    // swap
using namespace std;


// ==================== 第一部分：异常基础 ====================

void test01_exception_basics()
{
    cout << "\n========== 异常基础 ==========" << endl;

    // ---- 抛出和捕获 ----
    auto divide = [](int a, int b) -> double
    {
        if (b == 0)
        {
            throw runtime_error("除数不能为零！");
            // throw 后面的代码不会执行
        }
        return (double)a / b;
    };

    // 正常情况
    try
    {
        cout << "10 / 3 = " << divide(10, 3) << endl;
    }
    catch (const exception& e)
    {
        cout << "异常: " << e.what() << endl;
    }

    // 异常情况
    try
    {
        cout << "10 / 0 = " << divide(10, 0) << endl;
        cout << "这行不会执行" << endl;   // never reached
    }
    catch (const exception& e)           // 按引用捕获！避免切片
    {
        cout << "捕获到异常: " << e.what() << endl;
    }
    // 程序继续执行

    cout << "\n异常处理后程序继续运行" << endl;
}

void test02_exception_hierarchy()
{
    cout << "\n========== 标准异常类层次 ==========" << endl;

    // exception  ← 所有标准异常的基类
    // ├── logic_error      (逻辑错误，可预防)
    // │   ├── invalid_argument
    // │   ├── out_of_range
    // │   └── length_error
    // ├── runtime_error    (运行时错误，不可预防)
    // │   ├── range_error
    // │   ├── overflow_error
    // │   └── underflow_error
    // └── bad_alloc, bad_cast, bad_typeid, ...

    // 自定义异常
    class DatabaseException : public runtime_error
    {
    public:
        DatabaseException(const string& msg, int errorCode)
            : runtime_error(msg), m_ErrorCode(errorCode) {}

        int getErrorCode() const { return m_ErrorCode; }

    private:
        int m_ErrorCode;
    };

    try
    {
        throw DatabaseException("连接数据库失败", 1001);
    }
    catch (const DatabaseException& e)
    {
        cout << "数据库异常: " << e.what()
             << " (错误码: " << e.getErrorCode() << ")" << endl;
    }
    catch (const runtime_error& e)
    {
        cout << "运行时异常: " << e.what() << endl;
    }
    catch (const exception& e)           // 兜底捕获
    {
        cout << "未知异常: " << e.what() << endl;
    }

    cout << "\n捕获顺序: 先子类后父类 (和继承顺序一致)" << endl;
}

// 演示栈展开
class Tracker
{
public:
    Tracker(const string& name) : m_Name(name)
    {
        cout << "  [构造] " << m_Name << endl;
    }
    ~Tracker()
    {
        cout << "  [析构] " << m_Name << " ← RAII 保证被调用！" << endl;
    }
private:
    string m_Name;
};

void level3()
{
    Tracker t("level3 局部对象");

    throw runtime_error("从 level3 抛出异常！");
    // t 的析构函数被自动调用 ← 栈展开
}

void level2()
{
    Tracker t2("level2 局部对象");
    level3();
}

void level1()
{
    Tracker t1("level1 局部对象");
    level2();
}

void test03_stack_unwinding()
{
    cout << "\n========== 栈展开 (Stack Unwinding) ==========" << endl;

    try
    {
        level1();
    }
    catch (const exception& e)
    {
        cout << "捕获: " << e.what() << endl;
    }

    cout << "\n观察: 所有层次的局部对象都被正确析构了！" << endl;
    cout << "这就是 RAII 的力量 — 异常安全自动保证。" << endl;
}


// ==================== 第二部分：RAII ====================

// RAII 文件句柄包装器
class FileHandle
{
public:
    FileHandle(const string& filename, const string& mode = "r")
        : m_File(nullptr)
    {
        // fopen_s 是 Windows 安全版本
        if (fopen_s(&m_File, filename.c_str(), mode.c_str()) != 0 || !m_File)
        {
            throw runtime_error("无法打开文件: " + filename);
        }
        cout << "  [RAII] 文件 \"" << filename << "\" 已打开" << endl;
    }

    // 禁止拷贝（资源独占）
    FileHandle(const FileHandle&) = delete;
    FileHandle& operator=(const FileHandle&) = delete;

    // 允许移动
    FileHandle(FileHandle&& other) noexcept
        : m_File(other.m_File)
    {
        other.m_File = nullptr;
    }

    ~FileHandle()
    {
        close();
    }

    void close()
    {
        if (m_File)
        {
            fclose(m_File);
            cout << "  [RAII] 文件已关闭" << endl;
            m_File = nullptr;
        }
    }

    // 读取一行
    string readLine()
    {
        char buffer[256];
        if (fgets(buffer, sizeof(buffer), m_File))
        {
            string line(buffer);
            // 去除换行符
            while (!line.empty() && (line.back() == '\n' || line.back() == '\r'))
                line.pop_back();
            return line;
        }
        return "";
    }

    bool isOpen() const { return m_File != nullptr; }
    FILE* get() const { return m_File; }

private:
    FILE* m_File;
};

void test04_raii_demo()
{
    cout << "\n========== RAII 演示 ==========" << endl;

    // 正常路径
    try
    {
        // 先创建一个测试文件
        {
            FILE* f;
            fopen_s(&f, "temp_test.txt", "w");
            if (f)
            {
                fputs("第一行数据\n第二行数据\n第三行数据\n", f);
                fclose(f);
            }
        }

        FileHandle file("temp_test.txt", "r");
        // 离开作用域时自动关闭，即使下面抛异常也不怕

        string line = file.readLine();
        cout << "读取: " << line << endl;

        // 即使在这里抛出异常，文件也会被关闭
        // throw runtime_error("模拟异常");

    }
    catch (const exception& e)
    {
        cout << "异常: " << e.what() << endl;
    }

    cout << "\nRAII 原则:" << endl;
    cout << "  1. 构造函数获取资源" << endl;
    cout << "  2. 析构函数释放资源" << endl;
    cout << "  3. 资源生命周期 = 对象作用域" << endl;
    cout << "  4. 异常安全自然保证" << endl;

    // 清理测试文件
    remove("temp_test.txt");
}

// 演示: 不用 RAII 的危险代码
void dangerousCode()
{
    cout << "\n【不用 RAII 的危险代码】" << endl;

    int* data = new int[100];            // 1. 分配内存
    // ... 复杂操作 ...
    // 如果这里抛异常 → delete[] 不会执行 → 内存泄漏！

    delete[] data;                       // 2. 可能永远到不了这里
    cout << "  (如果异常，这行不会执行)" << endl;
}

void safeCode()
{
    cout << "\n【使用 RAII 的安全代码】" << endl;

    auto data = make_unique<int[]>(100); // RAII: 构造时获取
    // ... 复杂操作 ...
    // 即使异常，unique_ptr 析构也会释放内存
    cout << "  (异常安全！内存一定被释放)" << endl;
}

void test05_raii_comparison()
{
    cout << "\n========== RAII vs 手动管理 ==========" << endl;

    dangerousCode();
    safeCode();

    cout << "\nC++ 标准库中的 RAII 典范:" << endl;
    cout << "  unique_ptr / shared_ptr → 管理动态内存" << endl;
    cout << "  lock_guard / unique_lock → 管理互斥锁" << endl;
    cout << "  fstream                  → 管理文件" << endl;
    cout << "  string / vector          → 管理字符串/数组内存" << endl;
}


// ==================== 第三部分：noexcept ====================

// noexcept: 声明函数不会抛出异常
// 编译器可以据此优化，移动操作通常声明为 noexcept

class NoexceptDemo
{
public:
    NoexceptDemo() = default;

    // 移动构造声明 noexcept → vector 扩容时会优先使用移动而非拷贝
    NoexceptDemo(NoexceptDemo&&) noexcept
    {
        cout << "  noexcept 移动构造" << endl;
    }

    // 如果移动不是 noexcept，vector 会退化到拷贝（更安全）
    // NoexceptDemo(NoexceptDemo&&)  // 没有 noexcept
    // {
    //     cout << "  非 noexcept 移动构造" << endl;
    // }

    NoexceptDemo(const NoexceptDemo&)
    {
        cout << "  拷贝构造" << endl;
    }
};

void test06_noexcept()
{
    cout << "\n========== noexcept ==========" << endl;

    // noexcept 说明符
    auto safeFunc = []() noexcept { return 42; };
    // auto unsafeFunc = []() noexcept { throw 1; };
    // ↑ 声明了 noexcept 但抛异常 → std::terminate！

    cout << "noexcept(safeFunc) = "
         << (noexcept(safeFunc()) ? "true" : "false") << endl;

    // vector 扩容时的移动优化
    cout << "\nvector 扩容: noexcept 移动 vs 拷贝" << endl;
    vector<NoexceptDemo> v;
    v.reserve(2);
    v.emplace_back();
    v.emplace_back();
    cout << "push_back 第三个元素 → 触发扩容:" << endl;
    v.emplace_back();
    // 扩容时旧元素需要移动到新内存
    // 如果移动构造是 noexcept → 使用移动（快）
    // 如果不 noexcept → 使用拷贝（安全但慢）

    cout << "\n何时使用 noexcept:" << endl;
    cout << "  ✓ 移动构造/赋值（强烈推荐！）" << endl;
    cout << "  ✓ swap 函数" << endl;
    cout << "  ✓ 析构函数（隐式 noexcept）" << endl;
    cout << "  ✓ 简单的 getter/setter" << endl;
    cout << "  ✗ 可能抛异常的函数（不要欺骗）" << endl;
}


int main()
{
    cout << "========================================" << endl;
    cout << "|  异常处理与RAII(1) — 异常安全编程  |" << endl;
    cout << "========================================" << endl;

    test01_exception_basics();
    test02_exception_hierarchy();
    test03_stack_unwinding();
    test04_raii_demo();
    test05_raii_comparison();
    test06_noexcept();

    system("pause");
    return 0;
}

// 完结撒花*
