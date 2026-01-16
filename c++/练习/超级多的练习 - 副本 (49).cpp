#include<iostream>
#include<string>
#include<vector>
using namespace std;
#define LL long long

int main()
{
    LL n;
    string s;
    cin >> n;
    cin >> s;

    vector<vector<LL>> arr(n, vector<LL>(26, 0));

    for(LL i = n - 1; i >= 0; i--)
    {
        for(LL j = 0; j < 26; j++)
        {
            arr[i][j] = arr[i + 1][j];
        }
        arr[i][s[i] - 'a']++;
    }

    LL sum = 0;
    for(LL i = 0; i < n; i++)
    {
        for(LL j = 0; j < 26; j++)
        {
            if(j!= (s[i] - 'a'))
            {
                sum += arr[i + 1][j] * (  (arr[i + 1][j]-1) / 2);
            }
        }
    }

    cout << sum << endl;
}