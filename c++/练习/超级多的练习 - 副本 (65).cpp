#include<iostream>
#include<algorithm>
#include<queue>
#include<stack>
#include<cstring>
#include<cmath>
#include<string>

using namespace std;

int main()
{
    int n, m, k;
    cin >> n >> m >> k;
    queue<int> q;
    stack<int> stk;
    while(n--)
    {
        int x;
        cin >> x;
        q.push(x);
    }
    while(q.size() || stk.size())
    {
        int cnt = 0, last = 101;
        while(cnt < k)
        {
            if(stk.size() && stk.top() <= last)
            {
                cout << stk.top() << " ";
                last = stk.top();
                stk.pop();
                cnt++;
            }
            else if(q.size())
            {
                int t = q.front();
                if(t <= last)
                {
                    cout << t << " ";
                    last = t;
                    q.pop();
                    cnt++;
                }
                else if(stk.size() < m)
                {
                    stk.push(t);
                    q.pop();
                }
                else break;
            }
            else break;
        }
        cout << endl;
    }
    

    return 0;
}