#include <iostream>
#include <queue>
#include <string>
using namespace std;

// 功能：打印队列核心信息（简洁对齐版）
void printQueue(const queue<int>& q, const string& title) {
    cout << "【" << title << "】" << endl;
    cout << "  - 是否为空：" << (q.empty() ? "是" : "否") << endl;
    cout << "  - 元素个数：" << q.size() << endl;
    if (!q.empty()) {
        cout << "  - 队头元素：" << q.front() << endl;
        cout << "  - 队尾元素：" << q.back() << endl;
    }
    cout << "----------------------------------------" << endl;
}

// 功能：模拟排队叫号（队列经典应用）
void simulateQueueCall() {
    queue<string> q;
    // 入队（排队）
    q.push("用户A");
    q.push("用户B");
    q.push("用户C");

    cout << "【模拟排队叫号】" << endl;
    while (!q.empty()) {
        cout << "  叫号：" << q.front() << endl;
        q.pop(); // 叫号后出队
    }
    cout << "----------------------------------------" << endl;
}

int main() {
    // ======================================
    // 模块1：队列基础初始化
    // ======================================
    queue<int> q; // 核心：空队列初始化（最常用）
    printQueue(q, "初始化空队列");

    // ======================================
    // 模块2：队列核心操作（push/front/back/pop）
    // ======================================
    // 1. 入队（push）
    q.push(10);
    q.push(20);
    q.push(30);
    printQueue(q, "入队 10/20/30 后");

    // 2. 访问队头/队尾
    int frontVal = q.front();
    int backVal = q.back();
    cout << "单独获取队头：" << frontVal << "，队尾：" << backVal << endl;
    cout << "----------------------------------------" << endl;

    // 3. 出队（pop）：仅删除队头，无返回值
    q.pop(); // 删除10
    printQueue(q, "弹出队头（10）后");
    q.pop(); // 删除20
    printQueue(q, "再次弹出队头（20）后");

    // ======================================
    // 模块3：队列遍历（弹出式遍历，会清空）
    // ======================================
    // 重新填充数据
    q.push(5);
    q.push(15);
    q.push(25);
    cout << "【遍历队列（弹出所有元素）】" << endl;
    cout << "  弹出顺序：";
    while (!q.empty()) {
        cout << q.front() << " ";
        q.pop();
    }
    cout << "\n----------------------------------------" << endl;
    printQueue(q, "遍历后（队列清空）");

    // ======================================
    // 模块4：经典应用 - 模拟排队叫号
    // ======================================
    simulateQueueCall();

    return 0;
}