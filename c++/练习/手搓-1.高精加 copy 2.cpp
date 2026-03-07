// 2025/3/3

// 高精度加法

#include<iostream>
#include<string>
#include<vector>
using namespace std;

vector<int> add(vector<int> &A, vector<int> &B)
{
    if(A.size() < B.size()) return add(B, A);

    vector<int> C;
    int t = 0;
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
    for(int i = num.size() - 1; i >= 0; i--)
    {
        printf("%d", num[i]);
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
    
    vector<int> answer = add(A, B);

    print(answer);

    return 0;
}