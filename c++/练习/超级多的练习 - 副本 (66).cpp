#include <bits/stdc++.h>
using namespace std;

int main()
{
    long long n;
    cin >> n;
    vector<long long> res;

    for (long long x = 1; x < n; x++)
    {
        if ((x * x) % n == 1)
        {
            res.push_back(x);
        }
    }

    
    if (res.empty())
    {
        cout << "None" << endl;
    }
    else
    {
        sort(res.begin(), res.end());
        for (long long x : res)
        {
            cout << x << endl;
        }
    }

    return 0;
}