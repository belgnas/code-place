// 复习-基础回顾-动态数组包装类
//
// 【诊断目标】
// 通过实现一个自定义动态数组类，检验以下知识的掌握程度：
//   1. 指针操作 — new[] / delete[] 管理堆内存
//   2. 深拷贝 — 拷贝构造 vs 浅拷贝的区别
//   3. 赋值运算符重载 — operator= 的正确写法
//   4. const 正确性 — const 成员函数 / const 参数
//   5. this 指针 — 自赋值检查 / 返回 *this
//   6. 引用传参 — 避免不必要的拷贝
//
// 【项目描述】
// 实现一个简化版的 MyArray 类，功能类似 std::vector 的子集：
//   - 动态分配内存，支持自动扩容
//   - 深拷贝（拷贝构造 + 赋值运算符）
//   - 下标访问 + 边界检查
//   - 遍历打印
//
// 完成后可与 C++ 标准库的 std::vector 对比理解。


#include<iostream>
#include<string>
#include<stdexcept>  // std::out_of_range
using namespace std;


// ==================== MyArray 动态数组类 ====================

class MyArray
{
public:
    // ---- 构造函数 ----

    // 默认构造 — 分配初始容量
    MyArray()
    {
        m_Capacity = 4;                     // 初始容量：4
        m_Size = 0;                         // 当前元素数：0
        m_Data = new int[m_Capacity];       // 在堆上分配 int 数组
        cout << "[构造] 默认构造 — 容量=" << m_Capacity << endl;
    }

    // 带参构造 — 指定初始容量
    MyArray(int capacity)
    {
        if (capacity <= 0)
        {
            capacity = 1;  // 最小容量为 1
        }
        m_Capacity = capacity;
        m_Size = 0;
        m_Data = new int[m_Capacity];
        cout << "[构造] 带参构造 — 容量=" << m_Capacity << endl;
    }

    // 拷贝构造 — 深拷贝！
    // 如果不写拷贝构造，编译器自动生成的会做浅拷贝（只拷贝指针值）
    // 后果：两个对象的 m_Data 指向同一块内存 → 析构时 double delete → 崩溃！
    MyArray(const MyArray& other)
    {
        m_Capacity = other.m_Capacity;
        m_Size = other.m_Size;
        // 深拷贝的关键：分配新的独立内存
        m_Data = new int[m_Capacity];
        for (int i = 0; i < m_Size; i++)
        {
            m_Data[i] = other.m_Data[i];  // 逐个拷贝元素值
        }
        cout << "[构造] 拷贝构造 — 深拷贝了 " << m_Size << " 个元素" << endl;
    }


    // ---- 析构函数 ----

    ~MyArray()
    {
        if (m_Data != nullptr)
        {
            delete[] m_Data;   // 释放数组（必须用 delete[]，不能 delete）
            m_Data = nullptr;  // 置空，防止野指针
        }
        cout << "[析构] 销毁 — 曾容纳 " << m_Size << " 个元素" << endl;
    }


    // ---- 赋值运算符重载 — operator= ----

    // 返回 MyArray& 以支持链式赋值：a = b = c;
    MyArray& operator=(const MyArray& other)
    {
        // 【关键】自赋值检查：防止 a = a 时把自己释放了
        if (this == &other)
        {
            cout << "  [=] 检测到自赋值，跳过" << endl;
            return *this;
        }

        // 1. 释放旧内存
        delete[] m_Data;

        // 2. 分配新内存，拷贝数据
        m_Capacity = other.m_Capacity;
        m_Size = other.m_Size;
        m_Data = new int[m_Capacity];
        for (int i = 0; i < m_Size; i++)
        {
            m_Data[i] = other.m_Data[i];
        }

        cout << "[=] 赋值运算符 — 深拷贝了 " << m_Size << " 个元素" << endl;

        // 3. 返回自身的引用
        return *this;
    }


    // ---- 元素访问 ----

    // 非 const 版本 — 可用于修改
    int& operator[](int index)
    {
        if (index < 0 || index >= m_Size)
        {
            throw out_of_range("下标越界！index=" + to_string(index)
                               + " size=" + to_string(m_Size));
        }
        return m_Data[index];
    }

    // const 版本 — 只能读取，不能修改
    // 为什么需要两个版本？const 对象只能调用 const 成员函数
    const int& operator[](int index) const
    {
        if (index < 0 || index >= m_Size)
        {
            throw out_of_range("下标越界！index=" + to_string(index)
                               + " size=" + to_string(m_Size));
        }
        return m_Data[index];
    }


    // ---- 增删操作 ----

    // 尾部添加元素
    // 参数用 const 引用：不修改原值 + 避免不必要的拷贝
    void push_back(const int& value)
    {
        // 容量满了就扩容
        if (m_Size >= m_Capacity)
        {
            expand();
        }
        m_Data[m_Size] = value;
        m_Size++;
    }

    // 尾部弹出元素
    void pop_back()
    {
        if (m_Size > 0)
        {
            m_Size--;  // 不需要真的删除，size-- 后该位置会被新数据覆盖
        }
    }

    // 获取大小/容量
    int size()     const { return m_Size; }
    int capacity() const { return m_Capacity; }
    bool empty()   const { return m_Size == 0; }

    // 打印所有元素
    void print() const
    {
        cout << "[ ";
        for (int i = 0; i < m_Size; i++)
        {
            cout << m_Data[i];
            if (i != m_Size - 1) cout << ", ";
        }
        cout << " ]  (size=" << m_Size << ", cap=" << m_Capacity << ")" << endl;
    }

private:
    // 扩容（容量翻倍）
    void expand()
    {
        int newCapacity = m_Capacity * 2;
        int* newData = new int[newCapacity];

        // 拷贝旧数据到新数组
        for (int i = 0; i < m_Size; i++)
        {
            newData[i] = m_Data[i];
        }

        // 释放旧数组，指向新数组
        delete[] m_Data;
        m_Data = newData;
        m_Capacity = newCapacity;

        cout << "  [扩容] → 新容量=" << m_Capacity << endl;
    }

    int* m_Data;       // 指向堆上数组的指针
    int  m_Size;       // 当前元素个数
    int  m_Capacity;   // 数组总容量
};


// ==================== 测试函数 ====================

// 测试 1：基本操作（构造 / push_back / 访问）
void test01_basic_ops()
{
    cout << "\n========== 测试1：基本操作 ==========" << endl;

    MyArray arr;
    cout << "初始状态: ";
    arr.print();

    // 添加元素
    for (int i = 1; i <= 8; i++)
    {
        arr.push_back(i * 10);
        cout << "添加 " << (i * 10) << " → ";
        arr.print();
    }

    // 下标访问（读写）
    cout << "\n修改前 arr[0] = " << arr[0] << endl;
    arr[0] = 999;
    cout << "修改后 arr[0] = " << arr[0] << endl;

    // pop_back
    arr.pop_back();
    cout << "pop_back 后: ";
    arr.print();
}

// 测试 2：拷贝构造（深拷贝验证）
void test02_copy_constructor()
{
    cout << "\n========== 测试2：拷贝构造（深拷贝） ==========" << endl;

    MyArray arr1;
    arr1.push_back(100);
    arr1.push_back(200);
    arr1.push_back(300);

    cout << "arr1: ";
    arr1.print();

    // 拷贝构造
    MyArray arr2(arr1);
    cout << "arr2 (拷贝后): ";
    arr2.print();

    // 核心验证：修改 arr2 是否影响 arr1？
    // 如果是浅拷贝，两者共享同一块内存 → 修改 arr2 也会影响 arr1
    cout << "\n修改 arr2[0] = 777..." << endl;
    arr2[0] = 777;

    cout << "arr1: ";
    arr1.print();  // 应该还是 [100, 200, 300]
    cout << "arr2: ";
    arr2.print();  // 应该是 [777, 200, 300]

    if (arr1[0] == 100 && arr2[0] == 777)
    {
        cout << "  [✓] 深拷贝验证通过！修改 arr2 不影响 arr1。" << endl;
    }
    else
    {
        cout << "  [✗] 浅拷贝问题！两个对象共享同一块内存。" << endl;
    }
}

// 测试 3：赋值运算符
void test03_assignment_op()
{
    cout << "\n========== 测试3：赋值运算符 ==========" << endl;

    MyArray arr1;
    arr1.push_back(10);
    arr1.push_back(20);
    arr1.push_back(30);

    MyArray arr2;
    arr2.push_back(999);  // arr2 有自己的数据

    cout << "赋值前:" << endl;
    cout << "  arr1: "; arr1.print();
    cout << "  arr2: "; arr2.print();

    // 赋值操作
    arr2 = arr1;
    cout << "赋值后 (arr2 = arr1):" << endl;
    cout << "  arr1: "; arr1.print();
    cout << "  arr2: "; arr2.print();

    // 验证独立性
    arr2[0] = 555;
    cout << "修改 arr2[0] = 555 后:" << endl;
    cout << "  arr1: "; arr1.print();
    cout << "  arr2: "; arr2.print();

    // 自赋值测试
    cout << "\n自赋值测试 (arr1 = arr1):" << endl;
    arr1 = arr1;  // 应该不出错
    cout << "  arr1: "; arr1.print();

    // 链式赋值
    MyArray arr3;
    arr3.push_back(1);
    arr3 = arr2 = arr1;  // 等价于 arr3 = (arr2 = arr1)
    cout << "\n链式赋值后:" << endl;
    cout << "  arr3: "; arr3.print();
}

// 测试 4：const 正确性
void test04_const_correctness()
{
    cout << "\n========== 测试4：const 正确性 ==========" << endl;

    MyArray arr;
    arr.push_back(5);
    arr.push_back(10);
    arr.push_back(15);

    // 创建 const 引用 — 只能调用 const 成员函数
    const MyArray& constRef = arr;

    // 下面这些都能正常调用（都是 const 成员函数）
    cout << "constRef.size()     = " << constRef.size() << endl;
    cout << "constRef.capacity() = " << constRef.capacity() << endl;
    cout << "constRef[0]         = " << constRef[0] << endl;
    cout << "constRef 内容: ";
    constRef.print();

    // 下面这行如果取消注释，编译器会报错：
    // constRef[0] = 100;  // 错误！返回的是 const int&，不能修改

    cout << "  [✓] const 正确性验证通过" << endl;
}

// 测试 5：边界检查
void test05_bounds_check()
{
    cout << "\n========== 测试5：边界检查 ==========" << endl;

    MyArray arr;
    arr.push_back(1);
    arr.push_back(2);

    try
    {
        cout << "尝试访问 arr[5]..." << endl;
        cout << arr[5] << endl;  // 应该抛异常
    }
    catch (const out_of_range& e)
    {
        cout << "  [!] 捕获异常: " << e.what() << endl;
        cout << "  [✓] 边界检查正常工作" << endl;
    }
}


// ==================== 主函数 ====================

int main()
{
    cout << "========================================" << endl;
    cout << "|   C++ 复习诊断 — 动态数组包装类    |" << endl;
    cout << "========================================" << endl;

    test01_basic_ops();
    test02_copy_constructor();
    test03_assignment_op();
    test04_const_correctness();
    test05_bounds_check();

    cout << "\n[诊断完成] 如果以上测试都能理解，说明指针/内存管理基础扎实。" << endl;
    cout << "           如果拷贝构造/深拷贝的部分感到吃力，需要重点复习。" << endl;

    system("pause");
    return 0;
}

// 完结撒花*
