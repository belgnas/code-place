// 单调栈

// 例题：找到一个数列中每个数离这个数最近且比它小的数并返回这个数，若没有，则返回-1

// 输入格式：第一行包含一个整数 N, 表示数组长度
//          第二行包含 N 个整数，表示整数数列

// 输出格式：共一行，包含 N 个整数，其中第i个数表示第i个数左边第一个比它小的数，如果不存在则输出-1；

// 输入样例：5
//          3 4 2 7 5

// 输出样例：-1 3 -1 2 2

// 个人理解：如果右边的数小于左边的数，那么左边的数就没有意义了（可以删去），最终留下来的数组是一个从左到右，从大到小的单调栈


// 本题中输入输出的压力较大，建议使用 scanf 和 printf 。
//     或
//  加上
//  ios::sync_with_stdio(false);    // 关闭iostream与stdio的同步，提高输入输出效率
//  cin.tie(0); // 解除cin与cout的绑定，进一步提高输入输出效率
//  cout.tie(0);    // 解除cout与cin的绑定，进一步提高输入输出效率
#include<iostream>
using namespace std;

const int N = 1000010;

int n;
int stk[N], tt;

int main()
{
    cin >> n;
    for(int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        while(tt && stk[tt] >= x) tt--;
        if(tt) cout << stk[tt] << " ";
        else cout << -1 << " ";

        stk[++tt] = x;

    }

    return 0;
}