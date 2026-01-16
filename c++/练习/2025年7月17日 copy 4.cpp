#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

#define IOS ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define endl "\n"
#define int long long

signed main()
{
    IOS;

    int T;
    cin >> T;
    while(T--)
    {
        int n, k;
        cin >> n >> k;
        vector<int> h(n + 1);
        for(int i = 1; i <= n; i++)
            cin >> h[i];
        int max_h = *max_element(h.begin() + 1, h.end());

        if(h[k] == max_h)
        {
            cout << "YES" << endl;
            continue;
        }

        int now_time = 1;
        int now_tower = k;

        set<int> visited; // 防止又走回来了

        bool ans = false;
        while(true)
        {
            if(h[now_tower] == max_h)
            {
                ans = true;
                break;
            }

            if(visited.count(now_tower))
                break;
            visited.insert(now_tower);

            int next_tower = -1;
            int zuigao = -1;

            for(int j = 1; j <= n; j ++)
            {
                if(j == now_tower)
                    continue;
                
                int cast_time = abs(h[now_tower] - h[j]);

                bool safe_time = (now_time + cast_time - 1 <= h[now_tower]);
                bool safe_daoda = (now_time + cast_time <= h[j]);

                if(safe_time && safe_daoda)
                {
                    if (h[j] > zuigao)
                    {
                        zuigao = h[j];
                        next_tower = j;
                    }
                }
            }

            if(next_tower == -1)
                break;

            now_time += abs(h[now_tower] - h[next_tower]);
            now_tower = next_tower;
        }
        cout << (ans ? "YES" : "NO") << endl;
    }

    return 0;
}