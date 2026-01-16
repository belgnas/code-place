#include <iostream>
#include <vector>
#include <climits>

using namespace std;

long long calculateValue(const vector<int> &a, const vector<int> &b, const vector<int> &indices, int m)
{
    long long sumA = 0;
    long long sumB = 0;
    for (int i = 0; i < m; ++i)
    {
        sumA += a[indices[i]];
    }
    for (int i = m; i < 2 * m; ++i)
    {
        sumB += b[indices[i]];
    }
    return sumA + sumB;
}

int main()
{
    int n, m;
    cin >> n >> m;

    vector<int> a(n);
    vector<int> b(n);

    for (int i = 0; i < n; ++i)
    {
        cin >> a[i];
    }
    for (int i = 0; i < n; ++i)
    {
        cin >> b[i];
    }

    long long minValue = LLONG_MAX;

    for (int mask = 0; mask < (1 << n); ++mask)
    {
        if (__builtin_popcount(mask) == 2 * m)
        {
            vector<int> indices;
            for (int i = 0; i < n; ++i)
            {
                if (mask & (1 << i))
                {
                    indices.push_back(i);
                }
            }
            long long currentValue = calculateValue(a, b, indices, m);
            minValue = min(minValue, currentValue);
        }
    }

    cout << minValue << endl;

    return 0;
}