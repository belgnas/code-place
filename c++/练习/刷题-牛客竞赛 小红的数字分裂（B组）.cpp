// 牛客竞赛 小红的数字分裂（B组）

// 知识点：数论、贪心

// 难度：易

// https://ac.nowcoder.com/acm/contest/72647/C

// 思路：一个比较显然的结论是，最终需要将数组的元素变成所有元素的gcd（最大公约数）。因此每个元素需要分裂的次数可以直接O(1)求出来。这个结论的证明可以结合辗转相除法的性质，请大家自行思考。

#include <iostream>
#include <numeric>

using namespace std;

const int N = 101010;
int a[N];

int main()
{
    int n;
    cin >> n;

    int g = 0;
    for (int i = 0; i < n; ++i)
    {
        cin >> a[i];
        g = gcd(a[i], g);
    }

    long long s = 0;
    for (int i = 0; i < n; ++i)
    {
        s += a[i] / g - 1;
    }

    cout << s << endl;
    return 0;
}
