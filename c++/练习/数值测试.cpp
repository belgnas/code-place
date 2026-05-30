#include <bits/stdc++.h>
using namespace std;

#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)

bool test(long long a, long long b)
{
    if(a > b) swap(a, b);
    
    bool flat = false;
    if(__gcd(a, b) == 1)
    {
        flat = true;
    }
    
    return flat;
}

signed main()
{
    IOS;
    
    long long T;
    cin >> T;
    while(T--)
    {
        long long n;
        cin >> n;
        vector<long long> arr(n);
        long long ans = 0;
        for(long long i = 0; i < n; i++)
        {
            cin >> arr[i];
            if(arr[i] == 1)
            {
                ans ++;
            }
        }
        
        long long cnt = 1;
//         cout << n << endl;
        if(arr[0] == 1)
        {
            ans ++;
        }
        while(cnt < n)
        {
//             cout << "cnt(1):" << cnt << endl;
//             cout << "ans:" << ans << endl;
            if(arr[cnt] == 1)
            {
                cnt += 2;
                continue;
            }
            
            if(test(arr[cnt], arr[cnt - 1]))
            {
                cnt += 1;
            }
            else
            {
                ans++;
                cnt += 2;
            }
//             cout << "cnt(2):" << cnt << endl;
        }
        
        cout << ans << endl;
    }
    

    return 0;
}