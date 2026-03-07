// 2025/3/7

// 离散化

// 题目描述：
// 假定有一个无限长的数轴，数轴上每个坐标上的数都是0。
// 现在，我们首先进行 n 次操作，每次操作将某一位置x上的数加c。
// 近下来，进行 m 次询问，每个询问包含两个整数l和r，你需要求出在区间[l, r]之间的所有数的和。

// 输入格式
// 第一行包含两个整数n和m。
// 接下来 n 行，每行包含两个整数x和c。
// 再接下里 m 行，每行包含两个整数l和r。

// 输出格式
// 共m行，每行输出一个询问中所求的区间内数字和。

// 数据范围
// -10^9 ≤ x ≤ 10^9,
// 1 ≤ n, m ≤ 10^5,
// -10^9 ≤ l ≤ r ≤ 10^9,
// -10000 ≤ c ≤ 10000

// 输入样例：
// 3 3
// 1 2
// 3 6
// 7 5
// 1 3
// 4 6
// 7 8
// 输出样例：
// 8
// 0
// 5

// 分析：
// 本题操作的数可能在-10^9到10^9之间，如果开数组的话便过于庞大了，但是操作的次数n在十万以内，意味着最终出现的非0的数字会不超过十万，考虑采取离散化，将每次操作的数离散化为一个较小的数。
// 第一步：将待离散化的一组数存入向量；
// 第二步：去重，对向量进行排序，之后用unique函数去重，unique函数是将不重复的元素都移动到向量前面，向量后面的元素维持不变，然后返回不重复序列的后一个位置，所以可以用alls.erase(unique(alls.begin(),alls.end()), alls.end());语句来实现对向量alls去重的目的；
// 第三步：离散化，利用二分将向量中的元素映射为其在向量中的位置，这里第一个位置从1开始，为了后续前缀和的使用方便。
// 离散化完数组后直接用前缀和即可求得指定区间内数的和了。这里离散化过程中为什么要每次都二分去查找元素映射的值，而不是一劳永逸的用哈希表存储下映射关系呢？因为元素过大，使用哈希表的话效率很低，而二分查找一个的速度为log100000，最多十几次二分操作即可得到元素映射的位置，速度非常快。

#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

typedef pair<int, int> PII;

const int N = 300010;

int n, m;
int a[N], s[N];
vector<int>alls;
vector<PII>add, query;

int find(int x)
{
    int l = 0;
    int r = alls.size() - 1;

    while(l < r)
    {
        int mid = (l + r) >> 1;
        if(alls[mid] < x) l = mid + 1;
        else r = mid;
    }

    return l + 1;
}

int main()
{
    cin >> n >> m;

    for(int i = 0; i < n; i++)
    {
        int x, c;
        cin >> x >> c;
        add.push_back({x, c});
        alls.push_back(x);
    }

    for(int i = 0; i < m; i++)
    {
        int l, r;
        cin >> l >> r;
        query.push_back({l, r});
        alls.push_back(l);
        alls.push_back(r);
    }

    sort(alls.begin(), alls.end());
    alls.erase(unique(alls.begin(), alls.end()), alls.end());

    for(auto item : add)
    {
        int x = find(item.first);
        a[x] += item.second;
    }

    for(int i = 1; i <= static_cast<int>(alls.size()); i++)
        s[i] = s[i - 1] + a[i];

    for(auto item : query)
    {
        int l = find(item.first);
        int r = find(item.second);

        cout << s[r] - s[l - 1] << endl;
    }
    
    return 0;
}