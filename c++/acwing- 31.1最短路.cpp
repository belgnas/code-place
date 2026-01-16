// 最短路


// 我们学编程不会让我们去数学证明，我们只需要知道结论，然后用代码去“实现”就好了，实际上就比的是记忆能力。

//（在每种情况下，都有各自的最优抉择）
// 分类：
//  1.单源最短路（求的是一个点到其他所有点的最短距离）
//      (1).所有边的权重都是正数
//          (a).朴素Dijkstra算法        O(n^2)
//              比较适合 稠密图
//          (b).堆优化版的Dijkstra算法  O(mlogn)
//              比较适合 稀疏图
//      (2).存在负权边
//          **(a).Bellman-Ford算法        O(nm)  // ps：如果能求出来最短路，那么这个图里是没有负权回路的 所以会限制循环的次数，也就是最多走多少次
//              比较适合 存在负权边 的图
//          (b).SPFA算法                O(m)
//              一般 O(m), 最坏 O(nm)
//  2.多源汇最短路（求的是任意两点之间的最短距离）
//      (1).Floyd算法                   O(n^3)

// 我们在讲最短路算法的时候，都是针对有向图的
// 如果遇到无向图，我们一般会把无向图转化成有向图来处理
// 例如：把 a - b 无向边 转化成 a -> b 和 b -> a 两条有向边



//      Dijkstra-朴素O(n^2)

// 1.初始化距离数组, dist[1] = 0, dist[i] = inf;
// 2.for n次循环 每次循环确定一个min加入S集合中，n次之后就得出所有的最短距离
// 3.将不在S中dist_min的点->t
// 4.t->S加入最短路集合
// 5.用t更新到其他点的距离

//      Dijkstra-堆优化O(mlogm)

// 1.利用邻接表，优先队列
// 2.在priority_queue[HTML_REMOVED], greater[HTML_REMOVED] > heap;中将返回堆顶
// 3.利用堆顶来更新其他点，并加入堆中类似宽搜

//      Bellman_fordO(nm)

// 1.注意连锁想象需要备份, struct Edge{inta,b,c} Edge[M];
// 2.初始化dist, 松弛dist[x.b] = min(dist[x.b], backup[x.a]+x.w);
// 3.松弛k次，每次访问m条边

//      Spfa O(n)~O(nm)

// 1.利用队列优化仅加入修改过的地方
// 2.for k次
// 3.for 所有边利用宽搜模型去优化bellman_ford算法
// 4.更新队列中当前点的所有出边

//      Floyd O(n^3)

// 1.初始化d
// 2.k, i, j 去更新d


#include<iostream>

using namespace std;

int main()
{

    return 0;
}