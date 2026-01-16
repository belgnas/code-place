// 2025/2/26

// ¸ß¾«³ýµÍ¾«

#include<iostream>
#include<algorithm>
#include<string>
#include<vector>

using namespace std;

vector<int> div(vector<int> &A, int b, int &r)
{
    vector<int> C;

    for(int i = A.size() - 1; i >= 0; i--)
    {
        r = r * 10 + A[i];
        C.push_back(r / b);
        r %= b;
    }
    reverse(C.begin(), C.end());

    while(static_cast<int>(C.size()) > 1 && C.back() == 0) C.pop_back();

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
    for(int i = static_cast<int>(a.size() - 1); i >= 0; i--)
    {
        A.push_back(a[i] - '0');
    }

    int r = 0;
    vector<int> answer = div(A, b, r);

    print(answer);

    cout << r << endl;

    return 0;
}