// Modern C++ (5+) — 多线程实战：生产者-消费者模型
//
// 【生产者-消费者问题】
//   经典并发编程模式：一个或多个线程生产数据，一个或多个线程消费数据
//   核心：共享缓冲区，使用条件变量协调生产和消费
//
// 【实现方式】
//   1. 互斥锁 + 条件变量（最灵活，最常用）
//   2. 信号量（C++20 std::counting_semaphore）
//   3. 无锁队列（高级，lock-free programming）
//
// 【本文件实现】
//   1. 基础版：单生产者 + 单消费者 + 有界队列
//   2. 进阶版：多生产者 + 多消费者 + 线程安全阻塞队列


#include<iostream>
#include<thread>
#include<mutex>
#include<condition_variable>
#include<queue>
#include<vector>
#include<chrono>
#include<string>
#include<random>
#include<functional>  // std::function
#include<atomic>      // atomic
#include<future>      // future, promise
using namespace std;


// ==================== 第一部分：简单生产者消费者 ====================

void test01_simple_producer_consumer()
{
    cout << "\n========== 简单：单生产者 + 单消费者 ==========" << endl;

    mutex mtx;
    condition_variable cv;
    queue<int> buffer;
    const int MAX_SIZE = 5;              // 缓冲区最大容量

    bool producerDone = false;           // 生产者是否完成

    // 生产者
    auto producer = [&]()
    {
        for (int i = 1; i <= 10; i++)
        {
            unique_lock<mutex> lock(mtx);

            // 缓冲区满了就等待
            cv.wait(lock, [&]() { return buffer.size() < MAX_SIZE; });

            buffer.push(i);
            cout << "  [生产] " << i
                 << " (缓冲区: " << buffer.size() << "/" << MAX_SIZE << ")" << endl;

            lock.unlock();
            cv.notify_one();             // 通知消费者有新数据
            // (有数据了，可能唤醒等待的消费者)

            this_thread::sleep_for(chrono::milliseconds(50));
        }

        // 标记生产完成
        {
            lock_guard<mutex> lock(mtx);
            producerDone = true;
        }
        cv.notify_all();                 // 唤醒所有消费者检查完成标志
    };

    // 消费者
    auto consumer = [&]()
    {
        while (true)
        {
            unique_lock<mutex> lock(mtx);

            // 等待：缓冲区有数据 或 生产者完成
            cv.wait(lock, [&]()
            {
                return !buffer.empty() || producerDone;
            });

            // 检查退出条件
            if (buffer.empty() && producerDone)
            {
                break;                   // 生产者完成且缓冲区空 → 退出
            }

            int item = buffer.front();
            buffer.pop();
            cout << "  [消费] " << item
                 << " (缓冲区: " << buffer.size() << "/" << MAX_SIZE << ")" << endl;

            lock.unlock();
            cv.notify_one();             // 通知生产者有空位
            // (有空位了，可能唤醒等待的生产者)

            this_thread::sleep_for(chrono::milliseconds(80));
        }
        cout << "  消费者退出" << endl;
    };

    thread prod(producer);
    thread cons(consumer);

    prod.join();
    cons.join();

    cout << "\n✓ 简单生产者消费者完成" << endl;
}


// ==================== 第二部分：线程安全阻塞队列 ====================

// 通用阻塞队列模板
template<typename T>
class BlockingQueue
{
public:
    explicit BlockingQueue(size_t maxSize = 10) : m_MaxSize(maxSize) {}

    // 生产（阻塞直到有空位）
    void push(T item)
    {
        unique_lock<mutex> lock(m_Mutex);

        // 队列满时等待
        m_NotFull.wait(lock, [this]() { return m_Queue.size() < m_MaxSize; });

        m_Queue.push(move(item));

        lock.unlock();
        m_NotEmpty.notify_one();         // 通知一个等待的消费者
    }

    // 消费（阻塞直到有数据）
    T pop()
    {
        unique_lock<mutex> lock(m_Mutex);

        // 队列空时等待
        m_NotEmpty.wait(lock, [this]()
        {
            return !m_Queue.empty() || m_Done;
        });

        if (m_Queue.empty())
        {
            return T{};                  // 已结束，返回默认值
        }

        T item = move(m_Queue.front());
        m_Queue.pop();

        lock.unlock();
        m_NotFull.notify_one();          // 通知一个等待的生产者

        return item;
    }

    // 标记完成（不再有新数据）
    void setDone()
    {
        lock_guard<mutex> lock(m_Mutex);
        m_Done = true;
        m_NotEmpty.notify_all();         // 唤醒所有等待的消费者
    }

    size_t size() const
    {
        lock_guard<mutex> lock(m_Mutex);
        return m_Queue.size();
    }

private:
    mutex m_Mutex;
    condition_variable m_NotEmpty;      // 非空条件变量
    condition_variable m_NotFull;       // 非满条件变量
    queue<T> m_Queue;
    size_t m_MaxSize;
    bool m_Done = false;
};

void test02_blocking_queue()
{
    cout << "\n========== 进阶：多生产者 + 多消费者 ==========" << endl;

    const int NUM_PRODUCERS = 3;
    const int NUM_CONSUMERS = 2;
    const int ITEMS_PER_PRODUCER = 5;

    BlockingQueue<int> bq(4);            // 容量 4 的有界队列

    // 随机延迟模拟
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> delay(20, 100);

    // 生产者
    auto producer = [&](int id)
    {
        for (int i = 1; i <= ITEMS_PER_PRODUCER; i++)
        {
            int item = id * 100 + i;
            bq.push(item);
            cout << "  [P" << id << "] 生产 " << item << endl;
            this_thread::sleep_for(chrono::milliseconds(delay(gen)));
        }
        cout << "  [P" << id << "] 完成生产" << endl;
    };

    // 消费者
    atomic<int> consumedCount(0);
    auto consumer = [&](int id)
    {
        while (true)
        {
            int item = bq.pop();
            if (item == 0 && consumedCount.load() >=
                NUM_PRODUCERS * ITEMS_PER_PRODUCER)
            {
                break;                   // 所有数据已消费完
            }
            consumedCount++;
            cout << "  [C" << id << "] 消费 " << item
                 << " (已消费 " << consumedCount.load() << " 个)" << endl;
            this_thread::sleep_for(chrono::milliseconds(delay(gen)));
        }
        cout << "  [C" << id << "] 退出" << endl;
    };

    // 启动所有线程
    vector<thread> producers, consumers;

    for (int i = 1; i <= NUM_PRODUCERS; i++)
        producers.emplace_back(producer, i);

    for (int i = 1; i <= NUM_CONSUMERS; i++)
        consumers.emplace_back(consumer, i);

    // 等待生产者完成
    for (auto& t : producers) t.join();

    // 标记完成，通知消费者
    bq.setDone();

    // 等待消费者完成
    for (auto& t : consumers) t.join();

    cout << "\n✓ 多生产者多消费者完成" << endl;
    cout << "  共生产: " << (NUM_PRODUCERS * ITEMS_PER_PRODUCER)
         << " 个, 共消费: " << consumedCount.load() << " 个" << endl;
}


// ==================== 第三部分：并行归并排序 ====================

void test03_parallel_mergesort()
{
    cout << "\n========== 实战：多线程并行归并排序 ==========" << endl;

    const int N = 20;

    // 准备随机数据
    vector<int> arr(N);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(1, 100);
    for (int i = 0; i < N; i++) arr[i] = dist(gen);

    cout << "排序前: ";
    for (int x : arr) cout << x << " ";
    cout << endl;

    // 并行归并排序
    function<void(int, int, int)> parallelMergeSort;
    parallelMergeSort = [&](int left, int right, int depth)
    {
        if (left >= right) return;

        int mid = (left + right) / 2;

        // 深度限制：递归太深时不创建新线程（避免线程爆炸）
        if (depth < 2 && (right - left) > 5)
        {
            // 左右各用新线程
            thread leftThread(parallelMergeSort, left, mid, depth + 1);
            thread rightThread(parallelMergeSort, mid + 1, right, depth + 1);
            leftThread.join();
            rightThread.join();
        }
        else
        {
            // 串行递归
            parallelMergeSort(left, mid, depth + 1);
            parallelMergeSort(mid + 1, right, depth + 1);
        }

        // 归并（和普通归并排序一样）
        vector<int> temp(right - left + 1);
        int i = left, j = mid + 1, k = 0;
        while (i <= mid && j <= right)
        {
            if (arr[i] <= arr[j]) temp[k++] = arr[i++];
            else                 temp[k++] = arr[j++];
        }
        while (i <= mid)  temp[k++] = arr[i++];
        while (j <= right) temp[k++] = arr[j++];
        for (int p = 0; p < k; p++) arr[left + p] = temp[p];
    };

    parallelMergeSort(0, N - 1, 0);

    cout << "排序后: ";
    for (int x : arr) cout << x << " ";
    cout << endl;

    // 验证有序
    bool sorted = true;
    for (int i = 1; i < N; i++)
        if (arr[i] < arr[i - 1]) sorted = false;
    cout << "结果: " << (sorted ? "✓ 排序正确" : "✗ 排序错误") << endl;
}


int main()
{
    cout << "========================================" << endl;
    cout << "| Modern C++(5+) — 多线程实战         |" << endl;
    cout << "========================================" << endl;

    test01_simple_producer_consumer();
    test02_blocking_queue();
    test03_parallel_mergesort();

    cout << "\n多线程学习路线建议:" << endl;
    cout << "  入门: thread + mutex + lock_guard" << endl;
    cout << "  进阶: condition_variable + 生产者消费者" << endl;
    cout << "  熟练: atomic + async/future + 并行算法" << endl;
    cout << "  高级: memory_order + lock-free (后续学习)" << endl;

    system("pause");
    return 0;
}

// 完结撒花*
