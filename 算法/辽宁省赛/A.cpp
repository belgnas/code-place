#include <iostream>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <string>
#include <vector>
#include <cstring>
#include <set>
#include <tuple>
#include <bitset>
#include <utility>
#include <queue> // 队列
#include <deque> // 双端队列

using namespace std;

#define IOS ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
#define endl '\n'

const int INF = 0x3f3f3f3f;

signed main()
{
    IOS;
    
    string s;
    getline(cin, s);
    // cout << s << endl;
    int n;
    cin >> n;
    vector<string> srr(n);
    for(int i = 0; i < n; i++)
        cin >> srr[i];
    
    string temp = "";
    int ans = 0;
    for(int i = 0; i < s.size(); i++)
    {
        if(s[i] >= 'A' && s[i] <= 'Z') s[i] += 32;

        if(s[i] >= 'a' && s[i] <= 'z')
        {
            temp += s[i];
        }
        else
        {
            bool flat = false;
            for(int i = 0; i < srr.size(); i++)
            {
                if(srr[i] == temp)
                {
                    flat = true;
                    break;
                }
            }
            if(!flat && temp != "")
            {
                srr.push_back(temp);
                ans++;
            }
            temp = "";
        }
    }

    cout << ans << endl;
    
    
    return 0;
}