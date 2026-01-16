#include<bits/stdc++.h>

using namespace std;

#define IOS ios::sync_with_stdio(false), cout.tie(0), cin.tie(0);

int main()
{
    IOS;

    int n;
    cin >> n;

    int arr[n];
    for(int i = 0; i < n; i++)
        cin >> arr[i];
    
    int max = 0;
    for(int i = 0; i < n - 1; i++)
    {
        for(int j = i + 2; j < n; j++)
        {
            if(max < arr[i] + arr[j])
            {
                max = arr[i] + arr[j];
            }
        }
    }

    cout << max << endl;

    return 0;
}