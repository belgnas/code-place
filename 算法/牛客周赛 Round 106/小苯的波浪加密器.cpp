#include <bits/stdc++.h>
using namespace std;

#define IOS ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
#define endl '\n'
typedef pair<int, int> PII;

const int INF = 0x3f3f3f3f;
const int MOD = 1e9 + 7;

// 快速幂（保留你的原有实现，虽本题用不到）
int fast_pow(int a, int b, int mod)
{
    int res = 1 % mod;
    while (b)
    {
        if (b & 1)
            res = res * 1ll * a % mod;
        a = a * 1ll * a % mod;
        b >>= 1;
    }
    return res;
}

// 手动实现 gcd（保留）
int gcd(int a, int b)
{
    while (b != 0)
    {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// 手动实现 lcm（保留）
int lcm(int a, int b)
{
    if (a == 0 || b == 0)
        return 0;
    return a / gcd(a, b) * b;
}

signed main()
{
    IOS;

    int t;
    cin >> t;
    while (t--)
    {
        int n, l1, r1, l2, r2;
        // 1. 修正：将 n 和 l1/r1/l2/r2 按题目格式读取（通常一行输入，避免解析错位）
        cin >> n >> l1 >> r1 >> l2 >> r2;

        vector<int> arr(n + 1, -1);
        for (int i = 3; i <= n; i++)
            cin >> arr[i];

        // 新增：存储正确的结果（完整数字 i 和 j），避免覆盖 arr
        int ans1 = -1, ans2 = -1;

        for (int i = l1; i <= min(r1, l1 + 10); i++)
        {
            for (int j = l2; j <= min(r2, l2 + 10); j++)
            {
                if ((i % 10) * (j % 10) % 10 == arr[3])
                {
                    if (n >= 4)
                    {
                        // 2. 修正：j%10 而非 j（因为条件是“j的个位 * arr[3] %10”，不是“j完整值”）
                        if ((j % 10) * arr[3] % 10 == arr[4])
                        {
                            ans1 = i; // 3. 修正：存储完整数字 i
                            ans2 = j; // 3. 修正：存储完整数字 j
                            goto flat;
                        }
                    }
                    else
                    {
                        ans1 = i; // 3. 修正：存储完整数字 i
                        ans2 = j; // 3. 修正：存储完整数字 j
                        goto flat;
                    }
                }
            }
        }
    flat:
        // 输出完整数字，而非个位数
        cout << ans1 << " " << ans2 << endl;
    }

    return 0;
}