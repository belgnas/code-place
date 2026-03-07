

// Trie树的作用:用来高效地存储和查找字符串集合的数据结构
//   Trie 树是一种树形结构，用于存储字符串集合，特别适用于存储大量具有公共前缀的字符串，能够高效地实现字符串的插入和查询操作。

// 一般来说存储的字符串中的字符种类一般不会太多，但是会重复出现

// 题目来源：AcWing 835. Trie字符串统计
// 一、题目描述
// 维护一个字符串集合，支持两种操作：

// 1. I x 向集合中插入一个字符串 x；
// 2. Q x 询问一个字符串在集合中出现了多少次。
// 共有 N 个操作，输入的字符串总长度不超过 10^5，字符串仅包含小写英文字母。

// 输入格式
// 第一行包含整数 N，表示操作数。

// 接下来 N 行，每行包含一个操作指令，指令为 I x 或 Q x 中的一种。

// 输出格式
// 对于每个询问指令 Q x，都要输出一个整数作为结果，表示 x 在集合中出现的次数。
// 每个结果占一行。

// 数据范围
// 1 ≤ N ≤ 2?10^4

// 输入样例：
// 5
// I abc
// Q abc
// Q ab
// I ab
// Q ab

// 输出样例：
// 1
// 0
// 1

// 二、Trie字典树思想
// 字典树是用来高效地存储和查找字符串集合的数据结构。使用要求：所存储的字符串要么都是小写、要么都是大写、要么都是数字，反正字符的种类不会很多。

// 例如：一棵字典树如图所示：存储 abcdef、abdef 、abc 、acef 、bcdf、bcdc、bcff、cdaa等字符如图所示，字符串存储的时候，要将每一个字符串结尾打上一个标记，如下图中的三角形。

//         ________root_____
//        /          |      |
//       a           b      c 
//     /   \         |      | 
//     b    c        c      d
//   /  \   |       /  \    | 
//  c*  d   e     d     f   a
//  |   |   |    / \    |   | 
//  d   e   f*  f*  c*  f*  a*
//  |   | 
//  e   f*
//  |
//  f*

#include<iostream>
using namespace std;

const int N = 100010;

int son[N][26], cnt[N], idx;
// // 下标是0的点既是根节点，又是空节点
// // son[][]存储树中每个节点的子节点
// // cnt[]存储以每个节点结尾的单词有多少个
// // idx 用于为新节点分配编号，从 1 开始，因为根节点编号为 0。
char str[N];

// 第一个操作：插入操作（存储）
void insert(char str[])
{
    int p = 0; // 从根节点0开始
    for(int i = 0; str[i]; i++) // 因为在 C++ 中，字符串的结尾是 \0 ，所以可以用 str[i] 来判断
    {
        int u = str[i] - 'a'; // 这步的目的是把 小写字母a~z 映射成 数字0~25
        if(!son[p][u]) son[p][u] = ++ idx; // 如果这个节点不存在的话，就把它创建出来
        p = son[p][u];
    }
    cnt[p]++;

}

// 第二个操作：查询操作
int query(char str[]) // 查询操作和插入操作是类似的
{
    int p = 0; // 从根节点0开始
    for(int i = 0; str[i]; i++)
    {
        int u = str[i] - 'a';
        if(!son[p][u]) return 0; // 如果不存在的话，直接return0
        p = son[p][u];
    }
    return cnt[p];
}

int main()
{
    int n;
    scanf("%d", &n);
    while(n--)
    {
        char op[2];
        scanf("%s%s", op, str); // 先读入操作类型，再读入字符串
        if(op[0] == 'I') insert(str);
        else printf("%d\n", query(str));
    }

    return 0;
}


// Trie树 —— 模板题 AcWing 835. Trie字符串统计

// int son[N][26], cnt[N], idx;
// // 0号点既是根节点，又是空节点
// // son[][]存储树中每个节点的子节点
// // cnt[]存储以每个节点结尾的单词数量

// // 插入一个字符串
// void insert(char *str)
// {
//     int p = 0;
//     for (int i = 0; str[i]; i ++ )
//     {
//         int u = str[i] - 'a';
//         if (!son[p][u]) son[p][u] = ++ idx;
//         p = son[p][u];
//     }
//     cnt[p] ++ ;
// }

// // 查询字符串出现的次数
// int query(char *str)
// {
//     int p = 0;
//     for (int i = 0; str[i]; i ++ )
//     {
//         int u = str[i] - 'a';
//         if (!son[p][u]) return 0;
//         p = son[p][u];
//     }
//     return cnt[p];
// }

