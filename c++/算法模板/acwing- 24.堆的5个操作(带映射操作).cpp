// 题目来源：AcWing 839. 模拟堆

// 一、题目描述
// 维护一个集合，初始时集合为空，支持如下几种操作：
// I x，插入一个数 x；
// PM，输出当前集合中的最小值；
// DM，删除当前集合中的最小值（数据保证此时的最小值唯一）；
// D k，删除第 k 个插入的数；
// C k x，修改第 k 个插入的数，将其变为 x；
// 现在要进行 N 次操作，对于所有第 2 个操作，输出当前集合的最小值。

// 输入格式
// 第一行包含整数 N NN。

// 接下来 N 行，每行包含一个操作指令，操作指令为 I x，PM，DM，D k 或 C k x 中的一种。

// 输出格式
// 对于每个输出指令 PM，输出一个结果，表示当前集合中的最小值。

// 每个结果占一行。

// 数据范围
// 1 ≤ N ≤ 10^5
// -10^9 ≤ x ≤ 10^9
// 数据保证合法。

// 输入样例：
// 8
// I -10
// PM
// I -10
// D 1
// C 2 8
// I 6
// PM
// DM

// 输出样例：
// -10
// 6

// 二、算法思路
// 本题的基本操作依然还是来自基础堆，现在需要做的额外的工作是如何维护第 k 次插入的数与堆中结点下标 i 的映射关系。

// 首先我们定义两个数组 hp[] 和 ph[]，我们需要明白这两个数组的关系和作用： hp 是 heap to pointer 的缩写，hp[i] = k表示堆数组中的下标 i 所指的结点是第 k 次插入的。
// ph 是 pointer to heap 的缩写，ph[k] = i表示第 k 次插入的元素在堆数组中对应的结点下标 i。
// 因此， hp 和 ph 是反函数。

// 为什么要使用 ph 和 hp 数组呢？
// 原因在于删除第 k 次插入的元素时，我们必须知道第 k 次插入的元素在堆数组中的下标 i，因此使用 ph 数组可以方便查找。

// // 删除第k次插入的元素
// if (op == "D")
// {
// 	int k;
// 	cin >> k;
// 	k = ph[k]; // 找到第k次插入的元素在堆中的下标
// 	heap_swap(k, n); // 第k次插入的元素和堆尾元素交换
// 	n--; // 删除堆尾元素
// 	up(k), down(k);
// }

// 插入时需要完成的操作：

// if (op == "I")
// {
// 	int x;
// 	cin >> x;
// 	n++, m++; // n代表堆中元素总数, m代表插入的次数
// 	ph[m] = n, hp[n] = m;
// 	h[n] = x; // 在结尾处插入新元素
// 	up(n);
// }
// 这样看起来，似乎有了 ph 数组就可以完成所有操作了，但是为什么还要有一个 hp 数组呢？
// 原因在于才简单的堆的交换操作中，我们使用的是 swap(h[a],h[b])，传入的参数 a ，b 都是堆中的下标，但是无法知道每个堆数组的下标所对应的是第几次插入，因此需要引入 hp，便于查找.
// 本质上来说 hp 的存在是为了实现交换堆中 a, b 下标元素时，交换 ph[a] 和 ph[b]。

// // 所有堆内下标的交换都换成这个
// void heap_swap(int a, int b)
// {
// 	swap(ph[hp[a]], ph[hp[b]]);
// 	swap(hp[a], hp[b]);
// 	swap(h[a], h[b]);
// }

#include<iostream>
#include<algorithm>
#include<string.h>
using namespace std;

const int N = 100010;

int h[N], size;// size是储存我当前这个h[]数组中有多少元素

int ph[N], hp[N];
// ph 数组是 pointer to heap 的缩写，表示第 k 次插入的元素在堆数组中对应的节点下标；
// hp 数组是 heap to pointer 的缩写，表示堆数组中的下标 i 所指的节点是第 k 次插入的，
// 它们是相互映射的关系，用于辅助堆操作。

void heap_swap(int a, int b)
{
    swap(ph[hp[a]], ph[hp[b]]);
    swap(hp[a], hp[b]);
    swap(h[a], h[b]);
}

// 时间复杂度看上去是O(logn)，实际上是小于并且很接近O(n)的
void down(int u)
{
    int t = u;

    // 这两行的目的是使 t 成为左右子节点中的更小的那个
    // 如果左子节点存在且小于当前最小元素，更新 t 为左子节点。
    if(u * 2 <= size && h[u * 2] < h[t]) t = u * 2;
    // 果右子节点存在且小于当前最小元素，更新 t 为右子节点。
    if(u * 2 + 1 <= size && h[u * 2 + 1] < h[t]) t = u * 2 + 1;

    if(u != t) // 如果上面2行代码被执行了，那么 u 就会不等于 t ，也就是说此时 t 和 u 相比，u 更小，应该交换位置
    {
        heap_swap(u, t);

        down(t); // 递归调用 down 函数，继续向下调整交换后的节点，确保堆的性质。
    }
}

void up(int u)
{
    while(u / 2 && h[u / 2] > h[u]) // 当u节点的上面还有节点 同时u的父节点大于u节点本身时，交换2者的位置，u也随之更新
    {
        heap_swap(u / 2, u);
        u /= 2;
    }
}

int main()
{
    int n, m = 0;
    scanf("%d", &n);
    while(n--)
    {
        char op[10];
        int k, x;

        scanf("%s", op);
        if(!strcmp(op, "I"))
        {
            scanf("%d", &x);
            size++;
            m++;
            ph[m] = size, hp[size] = m;
            h[size] = x;
            up(size);
        }
        else if(!strcmp(op, "PM")) printf("%d\n", h[1]);
        else if(!strcmp(op, "DM"))
        {
            heap_swap(1, size);
            size--;
            down(1);
        }
        else if(!strcmp(op, "D"))
        {
            scanf("%d", &k);
            k = ph[k];
            heap_swap(k, size);
            size --;
            down(k), up(k);
        }
        else
        {
            scanf("%d%d", &k, &x);
            k = ph[k];
            h[k] = x;
            down(k), up(k);
        }
    }


    return 0;
}