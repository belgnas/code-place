#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

const long long mod = 998244353;

int main()
{
    long long t;
    cin >> t;
    while(t--)
    {
        long long n;
        cin >> n;
        long long arr[n];
        bool flat = true;
        for(long long i = 0; i < n; i++)
        {
            cin >> arr[i];
        }
        
        if(arr[n - 1] != 1)
        {
            flat = false;
        }
        long long k = 1;
        for(long long i = n - 1; i >= 1; i--)
        {
            if(arr[i] > arr[i - 1])
            {
                flat = false;
                break;
            }
        }
        for(long long i = n - 1; i >= 0; i--)
        {
            if(arr[i] > k)
            {
                flat = false;
                break;
            }
            k++;
        }
        if(!flat)
        {
            cout << "0" << endl;
            continue;
        }
        
        
        long long num = n - 1;
        for(long long i = 0; i < n - 1; i++)
        {
            if(arr[i] != arr[i + 1])
            {
                num--;
            }
        }
        
        long long ans = 1;
        if(num == 0) ans = 1;
        else
        {
            long long numble = num;
            for(long long i = 1; i <= num; i++)
            {
                ans = (ans * numble) % mod;
                numble--;
            }
        }
        
        cout << ans << endl;
        
    }
    
    
    
    return 0;
}