// 2025/2/25

// 高精度加法

#include<iostream>
#include<vector>
#include<string>

using namespace std;

vector<int> add(vector<int> &A, vector<int> &B)
{
    if(A.size() < B.size()) // 我们要保证让A是数位大的数字，B是数位小的数字
    {
        return add(B, A);
    }

    vector<int> C; // C 储存答案
    int t = 0;
    for(int i = 0; i < static_cast<int>(A.size()); i++) // A是数位大的数字
    {
        t += A[i];
        if(i < static_cast<int>(B.size()))
        {
            t += B[i];
        }
        C.push_back(t % 10);
        t /= 10;
    }
    if(t != 0)
    {
        C.push_back(t);
    }

    return C;
}

void print(vector<int> &num)
{
    for(int i = static_cast<int>(num.size() - 1); i >= 0; i--) // 因为前面填入的是个位，所以个位在num[0]（前面），我们要从高位到低位打印
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
    for(int i = a.size() - 1; i >= 0; i--) // 因为个位在字符串的末尾（最右边），我们需要先读入个位，也就是先读入最右边末尾的字符
    {
        A.push_back(a[i] - '0');
    }
    for(int i = b.size() - 1; i >= 0; i--)
    {
        B.push_back(b[i] - '0');
    }

    vector<int> answer = add(A, B);

    print(answer);

    return 0;
}