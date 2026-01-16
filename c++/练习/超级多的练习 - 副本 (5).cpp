#include<bits/stdc++.h>

using namespace std;

#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);

int main()
{
    IOS;
    
    int T;
    cin >> T;
    
    while(T--)
    {
        int A, B, n;
        cin >> A >> B >> n;
        
        int a[A], b[B];
        for(int i = 0; i < A; i++) cin >> a[i];
        for(int i = 0; i < B; i++) cin >> b[i];
        
        if(A * 2 < n) // 4 2  5 3 
        {
            cout << "-1" << endl;
            continue;
        }
        
        sort(a, a + A, greater<int>());
        sort(b, b + B, greater<int>());
        
        int S_a[A + 1], S_b[B + 1];
        S_a[0] = 0, S_b[0] = 0;
        
        for(int i = 0; i < A; i++)
        {
            S_a[i + 1] =  S_a[(i + 1) - 1] + a[i];
        }
        for(int i = 0; i < B; i++)
        {
            S_b[i + 1] =  S_b[(i + 1) - 1] + b[i];
        }
        
        int sum_a = 0, sum_b = 0; // 5  3 2  4 1  5 0
        int num_a = (n + 1) / 2; // 3  4  5
        int num_b = n - num_a; // 2  1  0
        
        int max = 0;

        while(num_a != n)
        {
            if(num_b < 0 || num_b > (n / 2)) break;

            sum_a = S_a[num_a];
            sum_b = S_b[num_b];
            if(sum_a + sum_b > max) max = sum_a + sum_b; 
            num_a ++;
            num_b --;
        }

        cout << max << endl;

        
        
        
//         int ans = 0;
//         int num = n;
//         int weizi = 0;
//         while(n--)
//         {
//             if(n % 2 == 0) // 0 2 4
//             {
//                 ans += a[weizi];
//             }
//             else
//             {
//                 ans += b[weizi];
//                 weizi ++;
//             }
//         }
        
//         cout << ans << endl;
        
    }
    
    return 0;
}