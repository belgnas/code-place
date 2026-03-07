// 高精度减法

#include<iostream>
#include<vector>
#include<string>

using namespace std;

vector<int> sub(vector<int> &A, vector<int> &B)
{
    // if(A.size() < B.size()) return sub(B, A); // 确保是数位多的减去数位少的

    vector<int> C;
    int t = 0; // t 表示的是计算中的退位，初始值设定为0
    for(int i = 0; i < static_cast<int>(A.size()); i++)
    {
        t = A[i] - t; // 可以理解成 A[i] 先减去 上一次计算中的退位
        if(i < static_cast<int>(B.size()))
        {
            t -= B[i];
        }
        C.push_back((t + 10) % 10); // +10 是为了确保填入 C 中的数字是正数
        if(t < 0) t = 1; // 如果 t 再减去 B[i] 后变成了负数，就将 t 退位成更高一位的 1；
        else t = 0; // 意味着减去 退位t 后的 A[i] 再减去 B[i] 也大于等于 0，下次计算中不需要额外的退位，将 退位t 设为 0。
    }

    while(C.size() > 1 && C.back() == 0) C.pop_back(); // 需要弹出可能出现的最高位为 0。

    return C;
}

void print(vector<int> &num)
{
    for(int i = static_cast<int>(num.size() - 1); i >= 0; i--)
    {
        cout << num[i];
    }
    cout << endl;
}

int main()
{
    string a, b;
    cin >> a >> b;

    vector<int> A, B;
    for(int i = a.size() - 1; i >= 0; i--) A.push_back(a[i] - '0');
    for(int i = b.size() - 1; i >= 0; i--) B.push_back(b[i] - '0');

    // 测试代码
    // for(int n : A)
    // {
    //     cout << n << " ";
    // }
    // cout << endl;
    // for(int n : B)
    // {
    //     cout << n << " ";
    // }
    // cout << endl;

    vector<int> answer = sub(A, B);

    print(answer);

    return 0;
}