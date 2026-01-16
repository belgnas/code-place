// 2025/2/26

// 高精除低精

#include<iostream>
#include<vector>
#include<string>
#include<algorithm>

using namespace std;

vector<int> div(vector<int> &A, int b, int &r) // 传入 A 和 r 的地址，传入 A 的地址是为了节省内存，传入 r 的地址目的是使 r 的值不用返回也可以被改变
{
    vector<int> C;

    for(int i = A.size() - 1; i >= 0; i--) // 这里和 高精度加/减/乘 反过来，因为我们要先处理位于 A数组 末尾的数位更高的数字
    {
        r = r * 10 + A[i]; // 先把前一位的余数*10后，加上被除数的当前位上的数字，接着将计算出来的值赋给 t
        C.push_back(r / b);
        r %= b;
    }
    reverse(C.begin(), C.end()); // 这行代码的作用是将存储结果的向量 C 进行反转

    while(C.size() > 1 && C.back() == 0) C.pop_back();

    return C;
}

void print(vector<int> &num)
{
    for(int i = static_cast<int>(num.size() - 1); i >= 0; i--) // 此时 num数组 对应的数字使 倒序 的
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
    for(int i = a.size() - 1; i >= 0; i--)
    {
        A.push_back(a[i] - '0');
    }

    int r = 0; // 定义一个余数
    vector<int> answer = div(A, b, r);

    print(answer);

    cout << "余数是：" << r << endl;

    return 0;
}