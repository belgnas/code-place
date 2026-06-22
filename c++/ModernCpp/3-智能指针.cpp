// Modern C++ (3) — 智能指针
//
// 【为什么需要智能指针】
//   原始指针 (new/delete) 的三大问题：
//   1. 忘记 delete → 内存泄漏
//   2. 重复 delete → 未定义行为（崩溃）
//   3. 异常安全 → 异常抛出时跳过 delete
//
//   回顾：你的「电脑组装」案例中就有 double-delete bug！
//   类和对象-多态-案例3-电脑组装.cpp 第 216 行：
//   delete computer2;  // 应该是 delete computer3！
//   这种错误编译器不会报错，但运行时会崩溃。智能指针可以杜绝此类问题。
//
// 【三种智能指针】（都在 <memory> 中）
//   unique_ptr: 独占所有权，不能拷贝，只能移动
//   shared_ptr: 共享所有权，引用计数，最后一个析构时释放
//   weak_ptr:   不控制生命周期，用于打破循环引用


#include<iostream>
#include<memory>     // unique_ptr, shared_ptr, weak_ptr, make_unique, make_shared
#include<string>
#include<vector>
using namespace std;


// ==================== 第一部分：unique_ptr ====================

// 演示类：打印构造/析构过程
class Resource
{
public:
    Resource(const string& name = "unnamed") : m_Name(name)
    {
        cout << "  [构造] " << m_Name << endl;
    }
    ~Resource()
    {
        cout << "  [析构] " << m_Name << endl;
    }
    void use() const { cout << "  使用资源: " << m_Name << endl; }
    string getName() const { return m_Name; }

private:
    string m_Name;
};

void test01_unique_ptr_basics()
{
    cout << "\n========== unique_ptr 基础 ==========" << endl;

    // ---- 创建 unique_ptr ----
    // 方式 1: make_unique (C++14，推荐！)
    {
        auto p1 = make_unique<Resource>("R1");

        // 方式 2: 用原始指针构造
        unique_ptr<Resource> p2(new Resource("R2"));

        // 方式 3: C++14 之前的 make_unique 实现
        // unique_ptr<Resource> p3(new Resource("R3"));

        p1->use();
        p2->use();

        // ---- 不能拷贝！ ----
        // auto p3 = p1;                  // 编译错误！拷贝构造被删除
        // unique_ptr(const unique_ptr&) = delete;

        // ---- 可以移动 ----
        auto p3 = move(p1);              // 所有权转移
        // p1 现在是 nullptr，不要再用它！
        if (!p1)
        {
            cout << "  p1 已为空（所有权已转移给 p3）" << endl;
        }
        p3->use();

        // 离开作用域自动释放（RAII）
        cout << "  离开作用域..." << endl;
    }
    cout << "  作用域结束，所有 unique_ptr 自动释放！" << endl;
}

void test02_unique_ptr_advanced()
{
    cout << "\n========== unique_ptr 高级用法 ==========" << endl;

    // ---- 自定义删除器 ----
    // 默认删除器：delete ptr
    // 可以自定义：用于 FILE*, 数组, 或其他资源类型

    // 数组版本
    {
        auto arr = make_unique<int[]>(5);  // unique_ptr<int[]>
        arr[0] = 10; arr[1] = 20;
        cout << "数组: " << arr[0] << " " << arr[1] << endl;
        // 自动调用 delete[]
    }

    // ---- 从函数返回 unique_ptr ----
    auto createResource = [](const string& name) -> unique_ptr<Resource>
    {
        return make_unique<Resource>(name);
        // RVO / move 语义自动生效，不需要 std::move
    };

    auto r = createResource("FactoryR");
    r->use();
    // 返回 unique_ptr 是安全的！不会拷贝，直接移动

    // ---- 放入容器 ----
    vector<unique_ptr<Resource>> resources;

    // 方式 1: push_back + move
    resources.push_back(make_unique<Resource>("V1"));

    // 方式 2: emplace_back
    resources.emplace_back(make_unique<Resource>("V2"));

    for (const auto& r : resources)
    {
        r->use();
    }

    // ---- release() vs reset() ----
    auto p = make_unique<Resource>("Temp");
    // release(): 放弃所有权，返回原始指针（不 delete！）
    // Resource* raw = p.release();       // 现在需要手动 delete！
    // reset(): 释放当前对象，接管新对象
    p.reset(new Resource("NewTemp"));     // 旧的 Resource("Temp") 被释放
}

void test03_unique_ptr_refactor()
{
    cout << "\n========== 实战：用 unique_ptr 重写电脑组装 ==========" << endl;

    // 原始代码的问题：
    // 1. 手动 new/delete，容易忘记或写错（第 216 行 delete computer2 应为 computer3）
    // 2. 异常不安全（如果 work() 抛异常，delete 不会执行）
    // 3. Computer 析构里也要 delete 零件（职责不清）

    // 【新版本：全部用 unique_ptr】
    // 抽象基类（和原来一样）
    class CPU
    {
    public:
        virtual void calculate() = 0;
        virtual ~CPU() = default;
    };

    class VideoCard
    {
    public:
        virtual void display() = 0;
        virtual ~VideoCard() = default;
    };

    class Memory
    {
    public:
        virtual void storage() = 0;
        virtual ~Memory() = default;
    };

    // 电脑类 — 用 unique_ptr 管理零件
    class Computer
    {
    public:
        Computer(unique_ptr<CPU> cpu,
                 unique_ptr<VideoCard> vc,
                 unique_ptr<Memory> mem)
            : m_cpu(move(cpu))
            , m_vc(move(vc))
            , m_mem(move(mem))
        {
        }

        void work()
        {
            m_cpu->calculate();
            m_vc->display();
            m_mem->storage();
        }

        // 不需要析构函数了！unique_ptr 自动释放
        // ~Computer() = default;  // 编译器自动生成，正确！

    private:
        unique_ptr<CPU>       m_cpu;
        unique_ptr<VideoCard> m_vc;
        unique_ptr<Memory>    m_mem;
    };

    // 具体厂商实现
    class IntelCPU : public CPU
    {
    public:
        void calculate() override { cout << "  Intel CPU 计算中..." << endl; }
    };
    class IntelVideoCard : public VideoCard
    {
    public:
        void display() override { cout << "  Intel 显卡 显示中..." << endl; }
    };
    class IntelMemory : public Memory
    {
    public:
        void storage() override { cout << "  Intel 内存 存储中..." << endl; }
    };

    class AMDCPU : public CPU
    {
    public:
        void calculate() override { cout << "  AMD CPU 计算中..." << endl; }
    };
    class AMDVideoCard : public VideoCard
    {
    public:
        void display() override { cout << "  AMD 显卡 显示中..." << endl; }
    };
    // 【修正】原类名为 "AMD Memory"（含空格），现改为合法名称
    class AMDMemory : public Memory
    {
    public:
        void storage() override { cout << "  AMD 内存 存储中..." << endl; }
    };

    // 组装电脑 — 不需要 new，不需要 delete！
    cout << "电脑 1 (全 Intel):" << endl;
    auto computer1 = make_unique<Computer>(
        make_unique<IntelCPU>(),
        make_unique<IntelVideoCard>(),
        make_unique<IntelMemory>()
    );
    computer1->work();

    cout << "\n电脑 2 (全 AMD):" << endl;
    auto computer2 = make_unique<Computer>(
        make_unique<AMDCPU>(),
        make_unique<AMDVideoCard>(),
        make_unique<AMDMemory>()          // 修正为合法类名
    );
    computer2->work();

    cout << "\n电脑 3 (混搭):" << endl;
    auto computer3 = make_unique<Computer>(
        make_unique<IntelCPU>(),
        make_unique<AMDVideoCard>(),
        make_unique<IntelMemory>()
    );
    computer3->work();

    cout << "\n✓ 没有一行 new 或 delete！所有资源自动管理。" << endl;
    cout << "  double-delete bug 从根本上被杜绝。" << endl;
}


// ==================== 第二部分：shared_ptr ====================

void test04_shared_ptr_basics()
{
    cout << "\n========== shared_ptr 基础 ==========" << endl;

    // shared_ptr: 共享所有权，引用计数
    // 当最后一个 shared_ptr 析构时，释放资源

    {
        auto sp1 = make_shared<Resource>("Shared1");
        cout << "use_count = " << sp1.use_count() << endl; // 1

        {
            auto sp2 = sp1;              // 拷贝 → 引用计数 +1
            cout << "拷贝后 use_count = " << sp1.use_count() << endl; // 2

            auto sp3 = sp1;              // 再加一个
            cout << "再拷贝 use_count = " << sp1.use_count() << endl; // 3

            // sp3 离开作用域，计数 -1
        }
        cout << "sp3 离开后 use_count = " << sp1.use_count() << endl; // 2
    }
    cout << "所有 shared_ptr 离开，资源释放" << endl;

    // ---- shared_ptr 的使用场景 ----
    // 多个对象共享同一个资源，且无法确定哪个对象最后使用完
    // 例如：多个窗口共享同一个纹理、多个请求共享同一个数据库连接

    // ---- make_shared vs new ----
    // make_shared: 一次分配（对象 + 控制块在一起）→ 更高效
    // shared_ptr<T>(new T): 两次分配（对象 + 控制块分开）→ 稍慢
    // 始终优先使用 make_shared！
}

void test05_shared_ptr_pitfalls()
{
    cout << "\n========== shared_ptr 陷阱 ==========" << endl;

    // ---- 陷阱 1：不要从同一个原始指针创建多个 shared_ptr ----
    {
        // 错误示范：
        // auto* raw = new Resource("Bad");
        // shared_ptr<Resource> sp1(raw);
        // shared_ptr<Resource> sp2(raw);   // 两个独立的控制块！
        // → 各自引用计数为 1 → 都会 delete → double delete！

        cout << "⚠ 不要用同一个原始指针创建多个 shared_ptr！" << endl;
    }

    // ---- 陷阱 2：循环引用 ----
    // 两个 shared_ptr 互相引用 → 引用计数永远不会归零 → 内存泄漏！
    struct Node
    {
        string name;
        shared_ptr<Node> next;           // 这会导致循环引用！

        Node(const string& n) : name(n)
        {
            cout << "  [Node] " << name << " 创建" << endl;
        }
        ~Node() { cout << "  [Node] " << name << " 销毁" << endl; }
    };

    {
        auto node1 = make_shared<Node>("A");
        auto node2 = make_shared<Node>("B");

        node1->next = node2;
        node2->next = node1;             // 循环引用！

        // 离开作用域：
        // node1 析构 → 引用计数 -1（但 node2->next 还指向它 → 计数 > 0）
        // node2 析构 → 引用计数 -1（但 node1->next 还指向它 → 计数 > 0）
        // → 两个 Node 都无法释放！内存泄漏！
    }
    cout << "  ⚠ 上面没有析构消息！循环引用导致内存泄漏！" << endl;

    // 解决方案：weak_ptr（见下一节）
}


// ==================== 第三部分：weak_ptr ====================

void test06_weak_ptr()
{
    cout << "\n========== weak_ptr ==========" << endl;

    // weak_ptr: 不控制生命周期，不增加引用计数
    // 用来解决 shared_ptr 的循环引用问题

    struct Node
    {
        string name;
        weak_ptr<Node> next;             // ← 用 weak_ptr 替代 shared_ptr！

        Node(const string& n) : name(n)
        {
            cout << "  [Node] " << name << " 创建" << endl;
        }
        ~Node() { cout << "  [Node] " << name << " 销毁" << endl; }

        // 使用 weak_ptr 时需要 lock()
        void showNext() const
        {
            if (auto sp = next.lock())   // lock() 返回 shared_ptr
            {
                cout << "  " << name << " → " << sp->name << endl;
            }
            else
            {
                cout << "  " << name << " → (已释放)" << endl;
            }
        }
    };

    {
        auto node1 = make_shared<Node>("A");
        auto node2 = make_shared<Node>("B");

        node1->next = node2;             // weak_ptr 不增加引用计数
        node2->next = node1;

        node1->showNext();
        node2->showNext();

        // 离开作用域：两个 Node 都能正常释放！
    }
    cout << "  ✓ 没有循环引用，两个 Node 都正常销毁！" << endl;

    // ---- weak_ptr 的 API ----
    // lock():     返回 shared_ptr（如果资源还存在），否则返回空
    // expired():  资源是否已被释放
    // use_count(): 返回 shared_ptr 的引用计数
    // reset():    放弃对资源的观察

    // weak_ptr 本质上是"观察者"——能看但不能拥有
}


// ==================== 第四部分：智能指针选型指南 ====================

void test07_selection_guide()
{
    cout << "\n========== 智能指针选型指南 ==========" << endl;

    cout << "┌──────────────┬──────────────────────────────────┐" << endl;
    cout << "│  unique_ptr  │ 默认选择！独占所有权，零开销      │" << endl;
    cout << "│              │ 不能拷贝，只能移动                │" << endl;
    cout << "│              │ 适用: 工厂函数、容器、PIMPL       │" << endl;
    cout << "├──────────────┼──────────────────────────────────┤" << endl;
    cout << "│  shared_ptr  │ 共享所有权，引用计数              │" << endl;
    cout << "│              │ 有额外开销（控制块+原子操作）     │" << endl;
    cout << "│              │ 适用: 多个对象共享同一资源        │" << endl;
    cout << "├──────────────┼──────────────────────────────────┤" << endl;
    cout << "│  weak_ptr    │ 打破循环引用，观察者模式          │" << endl;
    cout << "│              │ 配合 shared_ptr 使用              │" << endl;
    cout << "│              │ 适用: 缓存、观察者、树结构父指针  │" << endl;
    cout << "└──────────────┴──────────────────────────────────┘" << endl;

    cout << "\n核心原则:" << endl;
    cout << "  1. 默认用 unique_ptr，需要共享才换 shared_ptr" << endl;
    cout << "  2. 不要用 new/delete！用 make_unique / make_shared" << endl;
    cout << "  3. 原始指针只用于「不拥有所有权」的参数传递" << endl;
    cout << "  4. 绝对不要手动 delete 智能指针管理的对象" << endl;
}


int main()
{
    cout << "========================================" << endl;
    cout << "|   Modern C++(3) — 智能指针          |" << endl;
    cout << "========================================" << endl;

    cout << "\n提示：回顾你的电脑组装案例中存在 double-delete bug" << endl;
    cout << "     类和对象-多态-案例3-电脑组装.cpp 第 216 行" << endl;
    cout << "     delete computer2; → 应为 delete computer3;" << endl;
    cout << "     如果用智能指针，这类 bug 完全不会发生。" << endl;

    test01_unique_ptr_basics();
    test02_unique_ptr_advanced();
    test03_unique_ptr_refactor();
    test04_shared_ptr_basics();
    test05_shared_ptr_pitfalls();
    test06_weak_ptr();
    test07_selection_guide();

    system("pause");
    return 0;
}

// 完结撒花*