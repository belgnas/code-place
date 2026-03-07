// 2025/3/3

// 高精度减法

#include<iostream>
#include<string>
#include<vector>
using namespace std;

vector<int> sub(vector<int> A, vector<int> B)
{
    if(A.size() < B.size()) return sub(B, A);

    vector<int> C;
    int t = 0;
    for(int i = 0; i < static_cast<int>(A.size()); i++)
    {
        t = A[i] - t;
        if(i < static_cast<int>(B.size()))
        {
            t -= B[i];
        }
        C.push_back((t + 10) % 10);
        if(t < 0) t = 1;
        else t = 0;
    }
    
    while(C.size() > 1 && C.back() == 0) C.pop_back();

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

    vector<int> answer = sub(A, B);
    
    print(answer);

    return 0;
}