#include <bits/stdc++.h>

using namespace std;

using pii = pair<int, int>;

bool cmp(const pii &x, const pii &y)
{
    if (x.second != y.second)
        return x.second < y.second;
    return x.first < y.first;
}

int main()
{
    int n, res = 0, sum = 0;
    cin >> n;
    vector<pii> f(n);
    for (auto &[a, b] : f)
        cin >> a >> b, sum += b;

    { // 删掉无法被炸死的
        vector<pii> g;
        queue<int> q;
        q.push(0);
        for (auto it : f)
        {
            if (it.first > sum - it.second)
                res++, q.back() += it.second;
            else
                g.push_back(it);
        }
        f = move(g);
        while (not q.empty())
        {
            int x = q.front();
            q.pop();
            vector<pii> g;
            for (auto &it : f)
            {
                it.first -= x;
                if (it.first <= 0)
                    q.push(it.second);
                else
                    g.push_back(it);
            }
            f = move(g);
        }
    }
    while (not f.empty())
    {
        res++;
        queue<int> q;
        sort(f.begin(), f.end(), cmp);
        q.push(f.back().second), f.pop_back();
        while (not q.empty())
        {
            int x = q.front();
            q.pop();
            vector<pii> g;
            for (auto &it : f)
            {
                it.first -= x;
                if (it.first <= 0)
                    q.push(it.second);
                else
                    g.push_back(it);
            }
            f = move(g);
        }
    }
    cout << res << "\n";

    return 0;
}
