// 牛客竞赛 I love you

// 知识点：背包问题、思维题

// https://ac.nowcoder.com/acm/problem/201612

#include<iostream>
#include<string>
#include<algorithm>
using namespace std;
const int mod = 20010905;

int main()
{
    int dp[8];
    fill(dp, dp + 8, 0);
    
    string ar;
    cin >> ar;
    
    for(int i = 0; i < static_cast<int>(ar.length()); i++)
    {
        ar[i] = tolower(ar[i]);
        
        if(ar[i] == 'i') dp[0]++;
        if(ar[i] == 'l') dp[1] = (dp[0] + dp[1]) % mod;
        if(ar[i] == 'o') dp[2] = (dp[1] + dp[2]) % mod;
        if(ar[i] == 'v') dp[3] = (dp[2] + dp[3]) % mod;
        if(ar[i] == 'e') dp[4] = (dp[3] + dp[4]) % mod;
        if(ar[i] == 'y') dp[5] = (dp[4] + dp[5]) % mod;
        if(ar[i] == 'o') dp[6] = (dp[5] + dp[6]) % mod;
        if(ar[i] == 'u') dp[7] = (dp[6] + dp[7]) % mod;
    }
    
    cout << dp[7] << endl;
    
    return 0;
}