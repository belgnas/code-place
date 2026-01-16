// 高精度乘低精度

#include<iostream>
#include<vector>
#include<string>

using namespace std;

vector<int> mul(vector<int> &A, int b)
{
    vector<int> C; // C 储存答案
    int t; // t 储存进位（通常都会出现大于 10 的情况）
    
    // 原理是：让 大整数A 的每一位（从个位开始）都乘一次 低精数b，每次提取 t的各位
    for(int i = 0; i < static_cast<int>(A.size()) || t; i++)
    {
        if(i < static_cast<int>(A.size())) // A 的每一位都乘一次 b
        {
            t += A[i] * b;
        }
        C.push_back(t % 10);
        t /= 10;
    }

    while(C.size() > 1 && C.back() == 0) C.pop_back(); // 删去可能出现在计算结果最高位上的 0 （当乘数为 0 的时候就会在最高位上出现 0 了）。

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
    string a;
    int b;
    cin >> a >> b;

    vector<int> A;
    for(int i = a.size() - 1; i >= 0; i--) A.push_back(a[i] - '0');

    vector<int> answer = mul(A, b);

    print(answer);

    return 0;
}