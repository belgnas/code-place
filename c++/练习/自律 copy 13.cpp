#include <iostream>
#include <vector>

using namespace std;

int main()
{
    long long n;
    cin >> n;
    vector<long long> h(n + 1);
    for (long long i = 1; i <= n; i++)
    {
        cin >> h[i];
    }
        
    long long res = 0;
    for (long long mid = 2, l, r; mid < n; mid++)
    {
        l = r = 0;
        for (long long i = 1; i < mid; i++)
        {
            l = max(l, (mid - i) * min(h[i], h[mid]));
        }
            
        for (long long i = mid + 1; i <= n; i++)
        {
            r = max(r, (i - mid) * min(h[i], h[mid]));
        }

        res = max(res, l + r);
    }
    cout << res << "\n";
    return 0;
}
