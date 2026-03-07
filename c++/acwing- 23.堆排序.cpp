// 题目描述
// 输入一个长度为 n 的整数数列，从小到大输出前 m 小的数。

// 输入格式
// 第一行包含整数 n 和 m。

// 第二行包含 n 个整数，表示整数数列。

// 输出格式
// 共一行，包含 m 个整数，表示整数数列中前 m 小的数。

// 数据范围
// 1 ≤ m ≤ n ≤ 10^5，
// 1 ≤ 数列中元素 ≤ 10^9
// 输入样例：
// 5 3
// 4 5 1 3 2
// 输出样例：
// 1 2 3


#include<iostream>
#include<algorithm>
using namespace std;

const int N = 100010;

int n, m;
int h[N], size;// size是储存我当前这个h[]数组中有多少元素

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
        swap(h[u], h[t]);

        down(t); // 递归调用 down 函数，继续向下调整交换后的节点，确保堆的性质。
    }
}

void up(int u)
{
    while(u / 2 && h[u / 2] > h[u]) // 当u节点的上面还有节点 同时u的父节点大于u节点本身时，交换2者的位置，u也随之更新
    {
        swap(h[u / 2], h[u]);
        u /= 2;
    }
}

int main()
{
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++) scanf("%d", &h[i]);
    size = n;

    for(int i = n / 2; i; i--) down(i);

    while(m--)
    {
        printf("%d ", h[1]);

        h[1] = h[size];
        size--;
        down(1);
    }
    


    return 0;
}