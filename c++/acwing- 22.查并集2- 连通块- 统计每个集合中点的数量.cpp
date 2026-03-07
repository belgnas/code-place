// AcWing 837. 连通块中点的数量

// 1、题目（来源于AcWing）：
// 给定一个包含n个点（编号为1~n）的无向图，初始时图中没有边。
// 现在要进行m个操作，操作共有三种：
// 1. “C a b”，在点a和点b之间连一条边，a和b可能相等；
// 2. “Q1 a b”，询问点a和点b是否在同一个连通块中，a和b可能相等；
// 3. “Q2 a”，询问点a所在连通块中点的数量；

// 输入格式
// 第一行输入整数n和m。
// 接下来m行，每行包含一个操作指令，指令为“C a b”，“Q1 a b”或“Q2 a”中的一种。

// 输出格式
// 对于每个询问指令”Q1 a b”，如果a和b在同一个连通块中，则输出“Yes”，否则输出“No”。
// 对于每个询问指令“Q2 a”，输出一个整数表示点a所在连通块中点的数量
// 每个结果占一行。

// 数据范围
// 1  ≤ n, m ≤ 10^5

// 输入样例：
// 5 5
// C 1 2
// Q1 1 2
// Q2 1
// C 2 5
// Q2 5

// 输出样例：
// Yes
// 2
// 3

// 2、基本思想：
// 与AcWing 836. 合并集合类似，但是加上一个size_表示每个连通块中点的数量，仅有根节点的size_存储了该块中点的个数。

// 3、步骤：
// 与AcWing 836. 合并集合类似，求每个连通块中点的数量时
// size_[find(a)] += size_[find(b)]。

#include<iostream>
using namespace std;

const int N = 100010;

int n, m;
int p[N], size[N];
// 怎么样让size有意义，那就是只看根节点的size
// 根节点的size怎么更新？
// 比如把a的根节点连到b上，那么就让 size[b] += size[a];

int find(int x) // 返回x的祖宗节点 + 路径压缩优化
{
    if(p[x] != x) p[x] = find(p[x]); // 并查集最关键的两行
    return p[x];
}

int main()
{
    scanf("%d%d", &n, &m);
    
    for(int i = 1; i <= n; i++)
    {
        p[i] = i;
        size[i] = 1; // 一开始每个集合只有一个元素，所以 size = 1 
    }

    while(m--)
    {
        char op[2];
        int a, b;
        scanf("%s", op);

        if(op[0] == 'C')
        {
            scanf("%d%d", &a, &b);
            // // 特别是带有size这种附加属性的问题，一定要注意防止重复合并
            if(find(a) == find(b)) continue;
            else
            {
                size[find(b)] += size[find(a)]; // 这行是用来维护size所添加的代码，解释见 size[N] 数组定义处
                p[find(a)] = find(b);
            }
        }
        else if(op[1] == '1')
        {
            scanf("%d%d", &a, &a);
            if(find(a) == find(b)) puts("Yes");
            else puts("No");
        }
        else
        {
            scanf("%d", &a);
            printf("%d\n", size[find(a)]); // size打印代码
        }
    }

    return 0;
}