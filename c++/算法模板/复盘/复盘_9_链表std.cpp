#include <iostream>
#include <list>   // std::list 必备头文件
#include <vector> // 用于初始化示例
using namespace std;

// 辅助函数：打印链表内容（避免重复代码）
void printList(const list<int>& lst, const string& desc) {
    cout << desc << ": ";
    if (lst.empty()) { // 判断链表是否为空
        cout << "空链表" << endl;
        return;
    }
    // 范围for遍历（C++11+ 简洁写法）
    for (int num : lst) {
        cout << num << " ";
    }
    cout << endl;
}

int main() {
    // ===================== 1. 初始化方式 =====================
    cout << "===== 1. 链表初始化 =====" << endl;
    // 1.1 空链表
    list<int> lst1;
    printList(lst1, "lst1（空链表）");

    // 1.2 n个相同值的元素
    list<int> lst2(5, 10); // 5个10
    printList(lst2, "lst2（5个10）");

    // 1.3 用数组初始化
    int arr[] = {1, 2, 3, 4};
    list<int> lst3(arr, arr + 4);
    printList(lst3, "lst3（数组初始化）");

    // 1.4 用vector初始化
    vector<int> vec = {5, 6, 7};
    list<int> lst4(vec.begin(), vec.end());
    printList(lst4, "lst4（vector初始化）");

    // 1.5 拷贝初始化
    list<int> lst5(lst3);
    printList(lst5, "lst5（拷贝lst3）");

    // ===================== 2. 元素增删 =====================
    cout << "\n===== 2. 元素增删 =====" << endl;
    list<int> lst = {1, 2, 3, 4};
    printList(lst, "初始lst");

    // 2.1 头部/尾部添加
    lst.push_front(0);  // 头部加0
    lst.push_back(5);   // 尾部加5
    printList(lst, "push_front(0)+push_back(5)");

    // 2.2 指定位置插入（迭代器定位）
    auto it = lst.begin();
    ++it; // 迭代器移到第二个元素（0之后的位置）
    lst.insert(it, 9); // 插入9
    printList(lst, "在第二个位置插入9");

    // 2.3 删除指定值的元素（所有匹配项）
    lst.remove(3); // 删除所有值为3的元素
    printList(lst, "remove(3) 删除所有3");

    // 2.4 删除指定迭代器位置的元素
    for (auto i = lst.begin(); i != lst.end(); ++i) {
        if (*i == 9) {
            lst.erase(i); // 删除9
            break; // erase后迭代器失效，必须break
        }
    }
    printList(lst, "erase删除元素9");

    // 2.5 头部/尾部删除
    lst.pop_front(); // 删除头部
    lst.pop_back();  // 删除尾部
    printList(lst, "pop_front()+pop_back()");

    // 2.6 清空链表
    lst.clear();
    printList(lst, "clear() 清空后");

    // ===================== 3. 遍历方式 =====================
    cout << "\n===== 3. 遍历方式 =====" << endl;
    list<int> lst_traverse = {10, 20, 30, 40};
    
    // 3.1 普通迭代器遍历
    cout << "普通迭代器遍历: ";
    for (list<int>::iterator it = lst_traverse.begin(); it != lst_traverse.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    // 3.2 反向迭代器遍历
    cout << "反向迭代器遍历: ";
    for (list<int>::reverse_iterator it = lst_traverse.rbegin(); it != lst_traverse.rend(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    // 3.3 范围for遍历（推荐）
    cout << "范围for遍历: ";
    for (int num : lst_traverse) {
        cout << num << " ";
    }
    cout << endl;

    // ===================== 4. 查询/修改操作 =====================
    cout << "\n===== 4. 查询/修改操作 =====" << endl;
    list<int> lst_modify = {5, 2, 9, 1, 3};
    printList(lst_modify, "初始lst_modify");

    // 4.1 获取头部/尾部元素
    cout << "头部元素: " << lst_modify.front() << endl;
    cout << "尾部元素: " << lst_modify.back() << endl;
    cout << "元素个数: " << lst_modify.size() << endl;

    // 4.2 排序（list专属sort，不能用std::sort）
    lst_modify.sort(); // 升序排序
    printList(lst_modify, "sort() 升序排序后");

    // 4.3 反转链表
    lst_modify.reverse(); // 反转
    printList(lst_modify, "reverse() 反转后");

    // ===================== 5. 特殊操作：拼接/合并 =====================
    cout << "\n===== 5. 拼接/合并操作 =====" << endl;
    list<int> lst_a = {1, 2, 3};
    list<int> lst_b = {4, 5, 6};
    printList(lst_a, "拼接前lst_a");
    printList(lst_b, "拼接前lst_b");

    // 5.1 splice：拼接（O(1)，仅移动指针）
    lst_a.splice(lst_a.begin(), lst_b); // 把lst_b拼到lst_a开头
    printList(lst_a, "splice后lst_a");
    printList(lst_b, "splice后lst_b（空）");

    // 5.2 merge：合并两个已排序的链表
    list<int> lst_c = {1, 3, 5};
    list<int> lst_d = {2, 4, 6};
    printList(lst_c, "合并前lst_c（已排序）");
    printList(lst_d, "合并前lst_d（已排序）");
    lst_c.merge(lst_d); // 合并后仍有序
    printList(lst_c, "merge后lst_c");
    printList(lst_d, "merge后lst_d（空）");

    return 0;
}