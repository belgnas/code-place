// 2025/2/25

// 高精度加法

#include<iostream>
#include<string>
#include<vector>

using namespace std;

vector<int> add(vector<int> &A, vector<int> &B)
{
    if(A.size() < B.size()) return add(B, A);

    int t = 0;
    vector<int> C;
    for(int i = 0; i < static_cast<int>(A.size()); i++)
    {
        t += A[i];
        if(i < static_cast<int>(B.size()))
        {
            t += B[i];
        }
        C.push_back(t % 10);
        t /= 10;
    }
    if(t != 0) C.push_back(t);

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
    for(int i = static_cast<int>(a.size() - 1); i >= 0; i--)
    {
        A.push_back(a[i] - '0');
    }
    for(int i = static_cast<int>(b.size() - 1); i >= 0; i--)
    {
        B.push_back(b[i] - '0');
    }

    vector<int> C = add(A, B);

    print(C);


    return 0;
}