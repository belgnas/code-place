#include<iostream>
#include<algorithm>
using namespace std;
int main()
{
    int n, m; // n is the number of elements, m is the maximum value
    cin >> n >> m;
    int a[1000];
    for (int i = 0; i < n; i++)
        cin >> a[i];
    sort(a, a + n);
    int ans = 0;
    for (int i = 0; i < n; i++)
        if (a[i] <= m)
            ans++;
        else
            break;
    cout << ans << endl;
    
}