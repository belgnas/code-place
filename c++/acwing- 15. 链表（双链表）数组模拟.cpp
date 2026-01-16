// 链表

// 一.单链表（邻接表）：存储图和树
// 个人理解：节点1（索引为0） -> 节点2（"索引为1，ne[0] = 1"，"e[0] = 一个值"） -> 节点3（"索引为2，ne[1] = 2"，"e[1] = 一个值"） -> 节点4（"索引为3，ne[2] = 3"，"e[2] = 一个值"） -> 节点5（"索引为4，ne[3] = 4"，"e[3] = 一个值"）
//                                        
// 二.双链表：优化某些问题（ps: 本小节讲的是双链表）
// 个人理解：双链表有2个指针，一个指向前，一个指向后。


//这里偷个懒不定义头结点了，用下标为0的点表示头结点，用下标为1的点表示尾结点

#include <iostream>
using namespace std;

const int N = 100010; // 定义一个较大的数组长度，可根据实际需求调整

// 存储节点的值
int e[N];
// 存储节点的前驱索引，l[i]表示索引为i的节点的前驱节点索引
int l[N];
// 存储节点的后继索引，r[i]表示索引为i的节点的后继节点索引
int r[N];
// 记录当前可用的节点索引，相当于链表节点的个数
int idx;

// 初始化双向链表
void init()
{
    // 0表示左端点（虚拟头节点），1表示右端点（虚拟尾节点）
    r[0] = 1;
    l[1] = 0;
    idx = 2;
}

// 在节点k的右边插入一个值为x的新节点
void add_right(int k, int x) // 如果要改成在双链表的左边插入一个数的话，就把 传入函数时 把传入函数的k改成l[k]就好了
{
    e[idx] = x;
    r[idx] = r[k];
    l[idx] = k;
    // 下面这2不可以调换顺序
    l[r[k]] = idx; // 当前节点的右边节点的左边指向新建节点
    r[k] = idx; // 当前节点的右边指向新建节点
    idx++;
}

// 在节点k的左边插入一个值为x的新节点
void add_left(int k, int x)
{
    // 先获取节点k的前驱节点索引
    int prev_k = l[k];
    // 在节点k的前驱节点prev_k的右边插入新节点（等同于在节点k的左边插入）
    add_right(prev_k, x);
}

// 在链表头部插入一个值为x的新节点（等同于在虚拟头节点0的右边插入）
void add_to_head(int x)
{
    add_right(0, x);
}

// 在链表尾部插入一个值为x的新节点（等同于在虚拟尾节点1的左边插入，即虚拟尾节点1的前驱节点右边插入）
void add_to_tail(int x)
{
    add_right(l[1], x);
    //  或
    // add_left(1, x);
}

// 删除索引为k的节点
void remove(int k)
{
    r[l[k]] = r[k]; // 左边节点的右边指向当前节点的右边
    l[r[k]] = l[k]; // 右边节点的左边指向当前节点的左边
}

// 专门用于删除虚拟头节点后的第一个普通节点，使得头结点直接指向尾节点（保留虚拟头、尾节点）
void remove_whole()
{
    while(r[0] != 1)
    {
        r[0] = r[r[0]];
        l[r[0]] = 0;
    }
    idx = 2;
}

// 遍历并输出链表中的节点值（不包含虚拟头节点和虚拟尾节点）
void printList()
{
    for (int i = r[0]; i != 1; i = r[i])
    {
        cout << e[i] << " ";
    }
    cout << endl;
}

int main()
{
    init();
    cout << r[0] << endl;
    cout << l[1] << endl;

    add_to_head(5);
    add_to_tail(10);
    add_right(2, 8); // 在索引为2的节点（这里是值为5的节点）右边插入值为8的节点
    add_left(2, 6); // 在索引为2的节点（值为5的节点）左边插入值为6的节点
    printList();

    remove(2); // 删除索引为2的节点（即值为8的节点）
    
    cout << "1. After deleting: ";
    printList();

    remove_whole();

    cout << "2. After deleting: ";
    printList();

    cout << r[0] << endl;
    cout << l[1] << endl;

    return 0;
}