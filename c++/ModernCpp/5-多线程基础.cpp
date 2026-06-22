// Modern C++ (5) — 多线程基础
//
// 【C++11 线程库】<thread>, <mutex>, <condition_variable>, <atomic>, <future>
//
// 【核心组件】
//   std::thread:           线程对象
//   std::mutex:            互斥锁（基础锁）
//   std::lock_guard:       RAII 锁（自动加锁/解锁）
//   std::unique_lock:      更灵活的 RAII 锁（可延迟加锁、可转移）
//   std::condition_variable: 条件变量（等待-通知机制）
//   std::atomic:           原子操作（免锁的线程安全变量）
//   std::async / future:   异步任务 + 获取结果
//
// 【线程安全原则】
//   1. 多个线程同时访问共享数据，至少一个是写 → 必须同步
//   2. 只读不写 → 不需要同步
//   3. 能用 atomic 就不用 mutex（性能更好）
//   4. 能用 lock_guard 就不手动 lock/unlock（异常安全）


#include<iostream>
#include<thread>
#include<mutex>
#include<condition_variable>
#include<atomic>
#include<future>
#include<chrono>
#include<vector>
#include<string>
using namespace std;


// ==================== 第一部分：std::thread ====================

void sayHello(int id)
{
    cout << "线程 " << id << ": Hello from thread!" << endl;
}

void test01_thread_basics()
{
    cout << "\n========== std::thread 基础 ==========" << endl;

    // ---- 创建线程 ----
    thread t1(sayHello, 1);              // 传递函数 + 参数
    thread t2([](int id)
    {
        cout << "线程 " << id << ": Lambda in thread!" << endl;
    }, 2);

    // 也可以传成员函数（需要传对象指针/引用）

    // ---- join vs detach ----
    // join():  等待线程结束（阻塞）
    // detach(): 分离线程（后台运行，不能再 join）

    t1.join();                           // 等待 t1 结束
    t2.join();

    cout << "两个线程都结束了" << endl;

    // ⚠ 线程对象析构前必须 join 或 detach，否则 std::terminate！
}

void test02_multi_thread_calc()
{
    cout << "\n========== 多线程并行计算 ==========" << endl;

    // 练习：多线程计算数组的和
    const int N = 10000000;
    vector<int> arr(N);
    for (int i = 0; i < N; i++) arr[i] = i + 1;

    // 单线程版本
    auto start = chrono::high_resolution_clock::now();
    long long sum1 = 0;
    for (int x : arr) sum1 += x;
    auto end = chrono::high_resolution_clock::now();
    auto singleTime = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "单线程: sum = " << sum1
         << ", 耗时 " << singleTime.count() << "ms" << endl;

    // 多线程版本（4 个线程，各算 1/4）
    auto mtStart = chrono::high_resolution_clock::now();
    long long partial[4] = {0};

    auto worker = [&](int tid)
    {
        int chunk = N / 4;
        int start = tid * chunk;
        int end = (tid == 3) ? N : start + chunk;
        for (int i = start; i < end; i++)
        {
            partial[tid] += arr[i];      // 各自写不同位置，无需加锁
        }
    };

    thread threads[4];
    for (int i = 0; i < 4; i++)
        threads[i] = thread(worker, i);
    for (int i = 0; i < 4; i++)
        threads[i].join();

    long long sum2 = partial[0] + partial[1] + partial[2] + partial[3];
    auto mtEnd = chrono::high_resolution_clock::now();
    auto mtTime = chrono::duration_cast<chrono::milliseconds>(mtEnd - mtStart);

    cout << "4线程:   sum = " << sum2
         << ", 耗时 " << mtTime.count() << "ms"
         << " (结果" << (sum1 == sum2 ? "正确" : "错误") << ")" << endl;

    // 获取硬件线程数
    cout << "\n硬件线程数: " << thread::hardware_concurrency() << endl;
}


// ==================== 第二部分：互斥量 ====================

mutex g_coutMutex;  // 保护 cout 的全局锁（cout 不是线程安全的）

void test03_mutex()
{
    cout << "\n========== std::mutex ==========" << endl;

    // ---- 问题：竞态条件 ----
    int counter = 0;                     // 共享变量
    const int N = 100000;

    auto unsafeIncrement = [&]()
    {
        for (int i = 0; i < N; i++)
        {
            counter++;                   // ⚠ 不是原子操作！（读-改-写三步）
        }
    };

    thread t1(unsafeIncrement);
    thread t2(unsafeIncrement);
    t1.join();
    t2.join();

    cout << "无锁: counter = " << counter
         << " (期望 " << (2 * N) << ")" << endl;

    // ---- 解决方案 1：手动 lock/unlock（不推荐） ----
    counter = 0;
    mutex mtx;

    auto manualLockIncrement = [&]()
    {
        for (int i = 0; i < N; i++)
        {
            mtx.lock();
            counter++;
            mtx.unlock();
            // ⚠ 如果 counter++ 抛异常，unlock 不会执行 → 死锁！
        }
    };

    thread t3(manualLockIncrement);
    thread t4(manualLockIncrement);
    t3.join();
    t4.join();

    cout << "手动锁: counter = " << counter << endl;

    // ---- 解决方案 2：lock_guard（推荐） ----
    counter = 0;

    auto safeIncrement = [&]()
    {
        for (int i = 0; i < N; i++)
        {
            lock_guard<mutex> guard(mtx); // RAII: 构造时 lock，析构时 unlock
            counter++;
            // 即使抛异常，guard 析构也会自动 unlock
        }
    };

    thread t5(safeIncrement);
    thread t6(safeIncrement);
    t5.join();
    t6.join();

    cout << "lock_guard: counter = " << counter << " ← 正确！" << endl;
}

void test04_unique_lock()
{
    cout << "\n========== std::unique_lock ==========" << endl;

    // unique_lock 比 lock_guard 更灵活
    // - 可以延迟加锁
    // - 可以提前解锁
    // - 可以转移所有权
    // - 配合条件变量使用（lock_guard 不行）

    mutex mtx;

    {
        unique_lock<mutex> lock(mtx, defer_lock);  // 延迟加锁
        cout << "锁还未获取..." << endl;

        lock.lock();                     // 手动加锁
        cout << "临界区..." << endl;
        lock.unlock();                   // 提前解锁

        cout << "锁已释放..." << endl;

        lock.lock();                     // 重新加锁
        cout << "再次进入临界区..." << endl;
        // 析构时自动 unlock
    }

    // 开销: lock_guard < unique_lock ≈ 手动 lock/unlock
    // 优先用 lock_guard，需要灵活操作用 unique_lock
}


// ==================== 第三部分：条件变量 ====================

mutex g_mtx;
condition_variable g_cv;
bool g_ready = false;                    // 条件标志
int  g_data = 0;                         // 共享数据

void producer_thread()
{
    this_thread::sleep_for(chrono::milliseconds(100));
    cout << "  生产者: 开始准备数据..." << endl;

    {
        lock_guard<mutex> lock(g_mtx);
        g_data = 42;                     // 生产数据
        g_ready = true;
    }

    g_cv.notify_one();                   // 通知一个等待的消费者

    // notify_all(): 通知所有等待的消费者
}

void consumer_thread(int id)
{
    cout << "  消费者 " << id << ": 等待数据..." << endl;

    unique_lock<mutex> lock(g_mtx);

    // wait 做的事：
    // 1. 检查条件 (g_ready)
    // 2. 如果条件不满足 → 解锁 + 阻塞等待
    // 3. 被 notify 唤醒 → 重新加锁 + 重新检查条件
    // 使用 lambda 防止虚假唤醒（spurious wakeup）
    g_cv.wait(lock, [] { return g_ready; });

    cout << "  消费者 " << id << ": 收到数据 = " << g_data << endl;
}

void test05_condition_var()
{
    cout << "\n========== condition_variable ==========" << endl;

    thread consumer1(consumer_thread, 1);
    thread consumer2(consumer_thread, 2);
    thread producer(producer_thread);

    consumer1.join();
    consumer2.join();
    producer.join();

    cout << "\n条件变量典型用法:" << endl;
    cout << "  生产者: { lock; 修改数据; 修改条件; unlock; notify_one(); }" << endl;
    cout << "  消费者: { unique_lock; cv.wait(lock, 条件); 使用数据; }" << endl;
}


// ==================== 第四部分：atomic ====================

atomic<int> g_atomicCounter(0);
atomic<bool> g_done(false);

void test06_atomic()
{
    cout << "\n========== std::atomic ==========" << endl;

    // atomic: 免锁的线程安全操作
    // 支持的类型: int, long, bool, pointer 等（必须是 trivially copyable）

    const int N = 100000;

    auto atomicIncrement = [&]()
    {
        for (int i = 0; i < N; i++)
        {
            g_atomicCounter++;           // 原子操作！不需要 mutex
            // 等价于 g_atomicCounter.fetch_add(1)
        }
    };

    thread t1(atomicIncrement);
    thread t2(atomicIncrement);
    t1.join();
    t2.join();

    cout << "atomic counter = " << g_atomicCounter.load()
         << " (期望 " << (2 * N) << ")" << endl;

    // 常见原子操作:
    // load():    读取值
    // store(x):  写入值
    // exchange(x): 交换值，返回旧值
    // compare_exchange_strong(expected, desired): CAS 操作
    // fetch_add(n), fetch_sub(n): 加减

    // atomic vs mutex:
    // atomic: 非常快（CPU 指令级别），适合简单计数器/标志位
    // mutex:   更通用，适合保护复杂数据结构

    cout << "\natomic vs mutex 选择:" << endl;
    cout << "  atomic → 简单变量（int, bool, pointer）" << endl;
    cout << "  mutex  → 复合操作、多个变量、数据结构" << endl;
}


// ==================== 第五部分：async 和 future ====================

// 模拟耗时计算
int heavyCompute(int x)
{
    this_thread::sleep_for(chrono::milliseconds(200));
    return x * x;
}

void test07_async_future()
{
    cout << "\n========== async 和 future ==========" << endl;

    // ---- async: 异步执行任务，返回 future ----
    cout << "启动异步任务..." << endl;

    future<int> result1 = async(launch::async, heavyCompute, 10);
    // launch::async: 强制新线程执行
    // launch::deferred: 延迟执行（在 get() 时在当前线程执行）
    // 默认 (async | deferred): 由实现决定

    // 主线程可以做其他事
    cout << "主线程做其他工作..." << endl;

    // get(): 等待任务完成，获取结果（只能调用一次）
    int value = result1.get();
    cout << "异步结果: " << value << endl;

    // ---- promise + future: 在线程间传递值 ----
    promise<int> prom;
    future<int> fut = prom.get_future();

    thread worker([&prom]()
    {
        this_thread::sleep_for(chrono::milliseconds(100));
        prom.set_value(42);              // 设置结果
        // prom.set_exception(...) 也可以传异常
    });

    cout << "等待 worker 结果..." << endl;
    cout << "promise 结果: " << fut.get() << endl;
    worker.join();

    // ---- packaged_task: 打包任务 ----
    // 把函数包装成可以异步获取结果的形式
    packaged_task<int(int, int)> task([](int a, int b)
    {
        return a + b;
    });

    future<int> result2 = task.get_future();
    thread t(move(task), 3, 5);          // packaged_task 只能移动
    cout << "packaged_task 结果: " << result2.get() << endl;
    t.join();
}


int main()
{
    cout << "========================================" << endl;
    // 显示硬件线程数
    unsigned int hw = thread::hardware_concurrency();
    cout << "|  Modern C++(5) — 多线程基础  (" << hw << " 核)  |" << endl;
    cout << "========================================" << endl;

    test01_thread_basics();
    test02_multi_thread_calc();
    test03_mutex();
    test04_unique_lock();
    test05_condition_var();
    test06_atomic();
    test07_async_future();

    system("pause");
    return 0;
}

// 完结撒花*
