
#include<bits/stdc++.h>

using namespace std;

#define IOS ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

int main()
{
    IOS;
    
    long long T;
    cin >> T;
    while(T--)
    {
        long long n;
        cin >> n;
        long long arr[n + 1];
        arr[0] = 0;
        for(long long i = 1; i <= n; i++)
            cin >> arr[i];
        
        sort(arr, arr + n + 1);

        // for(long long i = 0; i <= n; i++)
        // {
        //     cout << arr[i] << " ";
        // }
        // cout << endl;

        long long cnt[n + 1];
        cnt[0] = 0;
        for(long long i = 1; i <= n; i++)
        {
            cnt[i] = arr[i] - arr[i - 1];
        }

        // for(long long i = 0; i <= n; i++)
        // {
        //     cout << cnt[i] << " ";
        // }
        // cout << endl;

        // cout << *max_element(cnt + 1, cnt + n + 1) << endl;\

        long long max = -1;
        long long num = n;
        for(long long i = 1; i <= n; i++)
        {

            // cout << cnt[i] << " " << num << endl;

            if(max < cnt[i] * num)
                max = cnt[i] * num;
            num--;
        }
        cout << max << endl;
    }
    
    
    return 0;
}
