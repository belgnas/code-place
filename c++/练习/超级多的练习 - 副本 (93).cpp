#include<bits/stdc++.h>
using namespace std;
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)

int main()
{
    IOS;
    
    int n, m;
    cin >> n >> m;
    int arr[n];
    int a, b;
    for(int i = 0; i < m; i++)
    {
        cin >> a >> b;
        arr[a - 1] ++;
        arr[b - 1] ++;
    }

    int num = 0;
    vector<int> brr;
    for(int i = 0; i < n; i++)
    {
        if(arr[i] % 2 == 1)
        {
            brr.push_back(i + 1);
            num++;
        }
    }
    cout << num / 2 << endl;

    for(int i = 0; i < brr.size(); i += 2)
    {
        cout << brr[i] << " " << brr[i + 1] << endl;
    }
    
    return 0;
}