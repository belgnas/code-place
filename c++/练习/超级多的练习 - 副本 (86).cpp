// 小嗷犬与目标检测

// 知识点：快速幂、模逆元、费马小定理

// 难度：难

// https://ac.nowcoder.com/acm/contest/104296/F

#include <bits/stdc++.h>
// 定义一个宏 ll，代表 long long 类型，方便后续使用长整型处理可能出现的大整数
#define ll long long
using namespace std;
// 定义常量 mod 为 1e9 + 7，用于后续的取模运算，防止结果溢出
const int mod = 1e9 + 7;

// 快速幂函数，用于计算 x 的 y 次幂对 mod 取模的结果
// 时间复杂度为 O(log y)
ll fp(ll x, ll y)
{
    // 初始化结果为 1
    ll res = 1;
    // 当指数 y 大于 0 时，持续进行运算
    while (y > 0)
    {
        // 判断 y 的二进制表示的最低位是否为 1
        // 如果为 1，说明当前这一位对应的 x 的幂需要乘入结果
        if (y & 1)
            res = res * x % mod;
        // 将 y 右移一位，相当于 y 除以 2
        y >>= 1;
        // 将 x 平方并对 mod 取模
        x = x * x % mod;
    }
    return res;
}

// 求模逆元函数
// 根据费马小定理，若 mod 为质数，且 x 与 mod 互质，则 x 在模 mod 意义下的逆元为 x^(mod - 2) % mod
ll inv(ll x)
{
    return fp(x, mod - 2);
}

// 计算两个矩形框重叠部分面积的函数
// 参数分别为第一个矩形框的左上角和右下角坐标 (x1, y1) 和 (x2, y2)
// 以及第二个矩形框的左上角和右下角坐标 (x3, y3) 和 (x4, y4)
ll co(ll x1, ll y1, ll x2, ll y2, ll x3, ll y3, ll x4, ll y4)
{
    // 计算交集矩形的左上角横坐标，取两个矩形框左上角横坐标的最大值
    ll lx = max(x1, x3);
    // 计算交集矩形的左上角纵坐标，取两个矩形框左上角纵坐标的最大值
    ll ly = max(y1, y3);
    // 计算交集矩形的右下角横坐标，取两个矩形框右下角横坐标的最小值
    ll rx = min(x2, x4);
    // 计算交集矩形的右下角纵坐标，取两个矩形框右下角纵坐标的最小值
    ll ry = min(y2, y4);
    // 判断两个矩形框是否有重叠部分
    // 若右下角坐标大于左上角坐标，则存在重叠部分
    if (rx > lx && ry > ly)
    {
        // 计算重叠部分的面积并对 mod 取模
        return ((rx - lx) % mod) * ((ry - ly) % mod) % mod;
    }
    // 若不存在重叠部分，返回 0
    return 0;
}

int main()
{
    // 解除标准输入输出流与 C 标准输入输出流的同步，加快输入输出速度
    ios::sync_with_stdio(0);
    // 解除 cin 和 cout 的绑定，使它们可以独立进行输入输出操作，提高效率
    cin.tie(0);
    cout.tie(0);

    // 定义变量存储两个矩形框的左上角和右下角坐标
    ll x1, y1, x2, y2, x3, y3, x4, y4;
    // 从标准输入读取两个矩形框的坐标
    cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;

    // 调用 co 函数计算两个矩形框的重叠部分面积
    ll s = co(x1, y1, x2, y2, x3, y3, x4, y4);
    // 计算第一个矩形框的面积并对 mod 取模
    ll s1 = (y2 - y1) * (x2 - x1) % mod;
    // 计算第二个矩形框的面积并对 mod 取模
    ll s2 = (y4 - y3) * (x4 - x3) % mod;

    // 根据交并比公式 IoU = S_overlap / S_union
    // 由于要对结果取模，将除法转换为乘以分母的逆元
    // 计算并输出交并比结果对 mod 取模的值
    cout << s * inv(s1 + s2 - s) % mod << endl;
    return 0;
}