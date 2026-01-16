#include <iostream>
#include <vector>

using namespace std;

bool canSort = false;

void dfs(int index, vector<int> &a, const vector<int> &b)
{
    int n = a.size();
    if (index == n)
    {
        bool isNonDecreasing = true;
        for (int i = 1; i < n; ++i)
        {
            if (a[i] < a[i - 1])
            {
                isNonDecreasing = false;
                break;
            }
        }
        if (isNonDecreasing)
        {
            canSort = true;
        }
        return;
    }

    dfs(index + 1, a, b);

    for (int j = 0; j < b.size(); ++j)
    {
        int original = a[index];
        a[index] = b[j] - a[index];
        dfs(index + 1, a, b);
        a[index] = original;
    }
}

int main()
{
    int t;
    cin >> t;

    while (t--)
    {
        int n, m;
        cin >> n >> m;

        vector<int> a(n);
        for (int i = 0; i < n; ++i)
        {
            cin >> a[i];
        }

        vector<int> b(m);
        for (int i = 0; i < m; ++i)
        {
            cin >> b[i];
        }

        canSort = false;
        dfs(0, a, b);

        if (canSort)
        {
            cout << "YES" << endl;
        }
        else
        {
            cout << "NO" << endl;
        }
    }

    return 0;
}